/*
** Projeto de Algoritmos Paralelos
** Multiplicação de Matrizes
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <cuda_profiler_api.h>

#define TAM_BLOCO 16

__global__ void cuda_multiplicarmatriz(float* M, float* N, float* R, int tamM, int tamN) {

    //índice do bloco
    int bx = blockIdx.x;
    int by = blockIdx.y; 
 
    // índice da thread
    int tx = threadIdx.x;
    int ty = threadIdx.y; 

    // índice da primeira submatriz de M processado pelo bloco
    int mComeco = tamM * TAM_BLOCO * by; 
 
    // índice da última submatriz de M processada pelo bloco
    int mFim   = mComeco + tamM - 1;
 
    // Tamanho do passo utilizado para interar através das submatrizes de M
    int mPasso  = TAM_BLOCO; 
 
    // Índice da primeira submatriz de N processada pelo bloco
    int nComeco = TAM_BLOCO * bx; 
 
    // Tamanho do passo utilizado para interar através das submatrizes de N
    int nPasso  = TAM_BLOCO * tamN;
 
    // O elemento computado pela thread
    float rRes = 0; 

    // Varre por todas as submatrizes de M e N requeridas
    // para computar o bloco de submatriz
    for (int m = mComeco, n = nComeco; m <= mFim; m += mPasso, n += nPasso) { 
 
        // Memoria compartilhada para a submatriz de M
        __shared__ float Msub[TAM_BLOCO][TAM_BLOCO]; 
 
        // Memoria compartilhada para a submatriz de N
        __shared__ float Nsub[TAM_BLOCO][TAM_BLOCO]; 
 
        // Carrega as matrizes da memória global para a memória
        // compartilhada. Cada thread carreg um elemento de cada
        // matriz
        Msub[ty][tx] = M[m + tamM * ty + tx];
        Nsub[ty][tx] = N[n + tamN * ty + tx];
 
        // Sincroniza para garantir que todas as matrizes foram
        // carregadas
        __syncthreads();
 
        // Multiplica as duas matrizes.
        // Cada thread computa um elemento
        // do bloco da submatriz
        for (int i = 0; i < TAM_BLOCO; ++i)
            rRes += Msub[ty][i] * Nsub[i][tx];
        
        // Sincroniza para grantir que a computação de multiplicação
        // está feita antes de carregar duas novas submatrizes de 
        // M e N na próxima interação
        __syncthreads();
    }
     // Esscre o bloco da sumatriz na memória global
     // Cada thread escreve  um único elemento
     int r = tamN * TAM_BLOCO * by + TAM_BLOCO * bx;
     R[r + tamN * ty + tx] = rRes;
}

// Função para rodar na CPU
// Computa R = M * N
//   aM é a altura de M
//   lM é a largura de M
//   lN é a largura de N
void multiplicar(const float* M, const float* N, int aM, int lM, int lN, float* R) {
    int tam;
 
    // Carrega M e N para a GPU
    float* Md;
    tam = aM * lM * sizeof(float);
    cudaMalloc((void**)&Md, tam);
    cudaMemcpy(Md, M, tam, cudaMemcpyHostToDevice);
    float* Nd;
    tam = lM * lN * sizeof(float);
    cudaMalloc((void**)&Nd, tam);
    cudaMemcpy(Nd, N, tam, cudaMemcpyHostToDevice); 
 
    // Aloca R na GPU
    float* Rd;
    tam = aM * lN * sizeof(float);
    cudaMalloc((void**)&Rd, tam); 
 
    // Computa a configuração da execução assumindo que
    // as dimensões das matrizes são múltiplos de TAM_BLOCO
    dim3 dimBlock(TAM_BLOCO, TAM_BLOCO);
    dim3 dimGrid(lN / dimBlock.x, aM / dimBlock.y); 
 
    // Processa a computação na GPU
    cuda_multiplicarmatriz<<<dimGrid, dimBlock>>>(Md, Nd, lM, lN, Rd); 
 
    // Carrega R da GPU
    cudaMemcpy(R, Rd, tam, cudaMemcpyDeviceToHost);  
 
    // Limpa a memória da GPU
    cudaFree(Md);
    cudaFree(Nd);
    cudaFree(Rd); 
} 

int checkGpu() {
    int count;
    cudaError_t erro;
    
    cudaProfilerStart();
    erro = cudaGetDeviceCount(&count);
    if (erro != cudaSuccess) {
        printf("Erro: %s\n", cudaGetErrorString(erro));
        return 0;
    }
    if (count < 1) {
        printf("Erro: %s\n", "Este computador não possui um dispositivo com GPU compatível com CUDA disponível.");
        return 0;
    }

    return 1;
}

void matriz_preencher(float* A, int tam) {
    for (int i = 0; i < tam*tam; i++)
        A[i] = rand() % 100;
}

void matriz_exibir(float* A, int tam) {
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            printf("%d ", A[tam*i+j]);
        }
        printf("\n");
    }
}

int main(int argc, const char * argv[]){
    float A[TAM_BLOCO*TAM_BLOCO];
    float B[TAM_BLOCO*TAM_BLOCO];
    float C[TAM_BLOCO*TAM_BLOCO];
    int aA = TAM_BLOCO;
    int lA = TAM_BLOCO;
    int lB = TAM_BLOCO;

    if (!checkGpu())
        exit(EXIT_FAILURE);
    srand(time(NULL));

    matriz_preencher(A, aA);
    matriz_preencher(B, aA);
    printf("Matriz A\n");
    matriz_exibir(A, aA);
    printf("Matriz B\n");
    matriz_exibir(B, aA);
    multiplicar(A, B, aA, lA, lB, C);
    printf("RESULTADO\n");
    matriz_exibir(C, aA);

    cudaDeviceReset();
    exit(EXIT_SUCCESS);
}