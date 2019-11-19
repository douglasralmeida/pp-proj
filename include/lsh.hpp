/*
** Projeto de Algoritmos Paralelos
** LSH - Cabeçalho
*/

#ifndef LSH_HPP
#define LSH_HPP

#include "dataset.hpp"

class LSH {
    protected:
        int buckets;

        int stages;

        int threshold;

        int* hash(bool* attributes, int n);

        int* hash(int* attributes, int n);
    public:
        LSH(int nbuckets, int nstages);

        ~LSH();

        bool createIndex();
};
#endif //LSH_HPP