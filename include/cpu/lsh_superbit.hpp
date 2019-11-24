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
        int dimensions;

        Superbit* sb;

        int computeSuperbit(int stages, int buckets);
    public:
        LSH_Superbit(int _buckets, int _stages, int _dimensions);

        LSH_Superbit(int _buckets, int _stages, int _dimensions, int _seed);

        ~LSH_Superbit();

        void hash(long id, double* attributes);
};
#endif //LSHSUPERBIT_HPP