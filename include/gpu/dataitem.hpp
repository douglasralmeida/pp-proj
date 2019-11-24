/*
** Projeto de Algoritmos Paralelos
** Objeto DataItem - Cabeçalho
*/

#ifndef DATAITEM_HPP
#define DATAITEM_HPP

#include "datatype.hpp"

class Dataitem {
    private:
        Datatype* attributes;
    public:       
        Datatype* getAttributes();

        void setAttributes(FILE* file, int dimension);
};

#endif //DATAITEM_HPP