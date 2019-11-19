/*
** Projeto de Algoritmos Paralelos
** Objeto DataSet - Cabeçalho
*/

#ifndef DATASET_HPP
#define DATASET_HPP

#include "dataitem.hpp"
#include "datatype.hpp"

class Dataset {
    private:
        int capacity;
        
        int dimension;
        
        Dataitem* items;
        
        int size;

        void add(FILE* file);
    public:
        Dataset(int newcapacity, int newdimension);

        ~Dataset();

        int getCapacity();

        int getDimension();
        
        int getSize();

        bool loadFromFile(const char* filename);

        void show();
};

#endif //DATASET_HPP