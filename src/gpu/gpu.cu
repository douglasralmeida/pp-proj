/*
** Projeto de Algoritmos Paralelos
** Objeto GPU
*/

#include <iostream>
#include <cuda_profiler_api.h>

#define GPU_ERROR "Erro de processamento na GPU:";

__host__ GPU::GPU() {
    int count;
    cudaError_t error;

    cout << "Inicializando GPU..." << endl;
    cudaProfilerStart();
    error = cudaGetDeviceCount(&count);
    if (error != cudaSuccess)
        exitWithFailure();
    cout << "Numero de dispositivos disponíveis: " << count << endl;
    error = cudaGetDeviceProperties(&deviceProp, 0);
    if (error != cudaSuccess) 
        exitWithFailure();
    cout << "Dispositivo 0 tem a capacidade computacional " << deviceProp.major << '.' << deviceProp.minor << endl;
}

__host__ GPU::~GPU() {
    cudaDeviceReset();
}

__host__ void GPU::exitWithFailure() {
    cout << GPU_ERROR << ' ' << cudaGetErrorString(erro) << endl;
    exit(EXIT_FAILURE);
}