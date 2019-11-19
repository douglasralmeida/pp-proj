/*
** Projeto de Algoritmos Paralelos
** LSH Superbit - Cabeçalho
*/

#ifndef LSHSUPERBIT_HPP
#define LSHSUPERBIT_HPP

#include "lsh.hpp"
#include "superbit.hpp"

class LSH_Superbit: public LSH {
    private:
        Superbit* sb;

        int computeSuperbit(int stages, int buckets, int dimensions);

        int* hash(float* attributes, int n);

        int* hash(int* attributes, int n);
    public:
        LSH_Superbit(int nbuckets, int nstages, int dimensions);

        LSH_Superbit::LSH_Superbit(int nbuckets, int nstages, int dimensions, int seed);

        ~LSH_Superbit();

        bool createIndex();
};
#endif //LSHSUPERBIT_HPP