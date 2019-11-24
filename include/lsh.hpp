/*
** Projeto de Algoritmos Paralelos
** LSH - Cabeçalho
*/

#ifndef LSH_HPP
#define LSH_HPP

#include "hashtable.hpp"

class LSH {
    protected:
        int buckets;

        int stages;

        void hashSign(long id, bool* attributes, int n);

        Hashtable* table;
    public:
        LSH(int nbuckets, int nstages);

        ~LSH();

        void showCounts();
};
#endif //LSH_HPP