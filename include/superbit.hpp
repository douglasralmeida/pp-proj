/*
** Projeto de Algoritmos Paralelos
** Algoritmo Superbit - Cabeçalho
*/

#ifndef SUPERBIT_HPP
#define SUPERBIT_HPP

class Superbit {
    private:
        double** hyperplanes;

        int dimensions;

        int hyperp_length;
    public:
        Superbit(const int _dimensions, int _superbit, int _length, int _seed);

        Superbit(const int _dimensions, int _superbit, int _length);

        ~Superbit();

        bool* computeSignature(double* v);

        int getSignatureLength();

        double similarity(bool* s1, bool* s2);
};
#endif //SUPERBIT_HPP