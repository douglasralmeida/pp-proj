/*
** Projeto de Algoritmos Paralelos
** Objeto GPU
*/

#include <iostream>
#include <cuda_profiler_api.h>
#include "gpu.hpp"

using namespace std;

//GPU com capacidade computacional 5.2
#define TAM_BLOCO 32

GPU::GPU() {
    int count;
    cudaError_t error;

    cout << "Inicializando GPU..." << endl;
    cudaProfilerStart();
    error = cudaGetDeviceCount(&count);
    if (error != cudaSuccess)
        exitWithFailure(error);
    cout << "Numero de dispositivos disponíveis: " << count << endl;
    error = cudaGetDeviceProperties(&deviceProp, 0);
    if (error != cudaSuccess) 
        exitWithFailure(error);
    cout << "Dispositivo 0 tem a capacidade computacional " << deviceProp.major << '.' << deviceProp.minor << endl;
}

GPU::~GPU() {
    cudaDeviceReset();
}

void GPU::exitWithFailure(cudaError_t error) {
    cout << "Erro de processamento na GPU: " << cudaGetErrorString(error) << endl;
    exit(EXIT_FAILURE);
}
