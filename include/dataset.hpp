/*
** Projeto de Algoritmos Paralelos
** Objeto DataSet - Cabeçalho
*/

#ifndef DATASET_HPP
#define DATASET_HPP

#include <fstream>
#include <iostream>
#include "datatype.hpp"

class Dataset {
    private:
        int length;
        
        int dimensions;
        
        Datatype* items;

        void add(FILE* file);
    public:
        Dataset(int _length, int _dimension);

        Dataset(const char* filename);

        ~Dataset();

        int getLength();

        int getDimensions();

        bool loadFromFile(std::ifstream stream);

        void show();
};

#endif //DATASET_HPP