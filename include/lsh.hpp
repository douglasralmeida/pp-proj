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

        int* hashSign(bool* attributes, int n);
    public:
        LSH(int nbuckets, int nstages);

        ~LSH();
};
#endif //LSH_HPP