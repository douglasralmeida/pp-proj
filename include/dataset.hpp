/*
** Projeto de Algoritmos Paralelos
** Objeto DataSet - Cabeçalho
*/

#ifndef DATASET_HPP

#define DATASET_HPP

class Dataset {
    private:
        int capacity;
        Datatype* items;
        int size;
    public:
        Dataset();

        int getCapacity();
        
        int getSize();

        bool openFile(const char* filename);
};

#endif //DATASET_HPP