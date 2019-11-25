/*
** Projeto de Algoritmos Paralelos
** Algoritmo Superbit - Cabeçalho
*/

#ifndef SUPERBIT_HPP
#define SUPERBIT_HPP

typedef struct hpbuilder_s {
    long superbit;
    int length;
    int seed;
    double* v;
    double* w;
} hpbuilder_t;

class Superbit {
    private:
        double* hyperplanes;

        int dimensions;

        long hyperp_length;

        void buildHyperplanes(hpbuilder_t *builderdata);
    public:
        Superbit(const int _dimensions, int _superbit, long _length, int _seed);

        Superbit(const int _dimensions, int _superbit, long _length);

        ~Superbit();

        bool* computeSignature(double* v);

        long getSignatureLength();

        double similarity(bool* s1, bool* s2);
};
#endif //SUPERBIT_HPP