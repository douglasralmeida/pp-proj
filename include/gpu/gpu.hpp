/*
** Projeto de Algoritmos Paralelos
** Objeto GPU - Cabeçalho
*/

#ifndef GPU_HPP
#define GPU_HPP

class GPU {
    protected:
        cudaDeviceProp deviceProp;

        __host__ void exitWithFailure();
    public:
        __host__ GPU();

        __host__ ~GPU();
};
#endif //GPU_HPP