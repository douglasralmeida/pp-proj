/*
** Projeto de Algoritmos Paralelos
** Objeto GPU - Cabeçalho
*/

#ifndef GPU_HPP
#define GPU_HPP

#include <cuda_runtime_api.h>

class GPU {
    protected:
        cudaDeviceProp deviceProp;

        void exitWithFailure(cudaError_t error);
    public:
        GPU();

        ~GPU();
};
#endif //GPU_HPP
