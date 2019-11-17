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
    
    cuda_olamundo<<<1,1>>>();
    
    cudaProfilerStart();
    erro = cudaGetDeviceCount(&count);
    if (erro != cudaSuccess) {
        printf("Error: %s\n", cudaGetErrorString(erro));
        exit(-1);
    }
    printf("Number of devices: %d\n", count);
    erro = cudaGetDeviceProperties(&deviceProp, 0);
    if (erro != cudaSuccess) {
        printf("Error: %s\n", cudaGetErrorString(erro));
        exit(-1);
    }
    printf("\nDevice %d has compute capability %d.%d.\n", 0, deviceProp.major, deviceProp.minor);
    exit(EXIT_SUCCESS);
}
