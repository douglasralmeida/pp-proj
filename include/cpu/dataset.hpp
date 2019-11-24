/*
** Projeto de Algoritmos Paralelos
** Objeto DataSet - Cabeçalho
*/

#ifndef DATASET_HPP
#define DATASET_HPP

#include "datatype.hpp"
#include "hashtable.hpp"
#include "lsh_superbit.hpp"

class Dataset {
    private:
        long length;
        
        int dimensions;

        bool hasHashTables;
        
        Datatype* items;

        LSH_Superbit* lsh;
    public:
        Dataset(long _length, int _dimensions);

        Dataset(const char* filename);

        ~Dataset();

        void computeHashTables(int stages, int buckets);

        long getLength();

        int getDimensions();

        void show();
};

#endif //DATASET_HPP