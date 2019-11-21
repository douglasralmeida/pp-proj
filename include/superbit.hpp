/*
** Projeto de Algoritmos Paralelos
** Algoritmo Superbit - Cabeçalho
*/

#ifndef SUPERBIT_HPP
#define SUPERBIT_HPP

class Superbit {
    private:
        double** hyperplanes;

        int hyperp_length;

        int DEFAULT_LENGTH = 10000;
    public:
        Superbit(const int dimensions, int superbit, int length, int seed);

        ~Superbit();

        bool* computeSignature(double* v, int n);

        double similarity(bool* s1, bool* s2, int n);
};
#endif //SUPERBIT_HPP