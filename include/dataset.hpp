/*
** Projeto de Algoritmos Paralelos
** Objeto DataSet - Cabeçalho
*/

#ifndef DATASET_HPP
#define DATASET_HPP

#include "datatype.hpp"

class Dataset {
    private:
        long length;
        
        int dimensions;
        
        Datatype* items;
    public:
        Dataset(long _length, int _dimensions);

        Dataset(const char* filename);

        ~Dataset();

        long getLength();

        int getDimensions();

        void show();
};

#endif //DATASET_HPP