/*
** Projeto de Algoritmos Paralelos
** Algoritmo Superbit - Cabeçalho
*/

#ifndef SUPERBIT_HPP
#define SUPERBIT_HPP

typedef struct hpbuilder_s {
    int superbit;
    int length;
    int seed;
    double** v;
    double** w;
} hpbuilder_t;

class Superbit {
    private:
        double** hyperplanes;

        int dimensions;

        int hyperp_length;

        __device__ void buildHyperplanes(hpbuilder_t *builderdata);
    public:
        __host__ Superbit(const int _dimensions, int _superbit, int _length, int _seed);

        __host__ Superbit(const int _dimensions, int _superbit, int _length);

        __host__ ~Superbit();

        __host__ bool* computeSignature(double* v);

        __host__ int getSignatureLength();

        __host__ double similarity(bool* s1, bool* s2);
};
#endif //SUPERBIT_HPP