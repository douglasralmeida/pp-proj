/*
** Projeto de Algoritmos Paralelos
** LSH - Cabeçalho
*/

#ifndef LSH_HPP
#define LSH_HPP

class LSH {
    protected:
        int buckets;

        int stages;

        int* hashSign(bool* attributes, int n);
    public:
        LSH(int nbuckets, int nstages);

        virtual ~LSH();
};
#endif //LSH_HPP