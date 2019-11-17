/*
Projeto de Algoritmos Paralelos
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cuda_profiler_api.h>

__global__ void cuda_olamundo(){
  printf("Ola Mundo direto da GPU!\n");
}

int main(int argc, const char * argv[]){
    int count;
    cudaError_t erro;
    cudaDeviceProp deviceProp; 
    
    cudaProfilerStart();
    erro = cudaGetDeviceCount(&count);
    if (erro != cudaSuccess) {
        printf("Erro: %s\n", cudaGetErrorString(erro));
        exit(-1);
    }
    printf("Numero de dispositivos: %d\n", count);
    erro = cudaGetDeviceProperties(&deviceProp, 0);
    if (erro != cudaSuccess) {
        printf("Erro: %s\n", cudaGetErrorString(erro));
        exit(-1);
    }
    printf("Dispositivo %d tem a capacidade computacional %d.%d.\n\n", 0, deviceProp.major, deviceProp.minor);
    
    cuda_olamundo<<<1,1>>>();
    cudaDeviceReset();
    exit(EXIT_SUCCESS);
}
