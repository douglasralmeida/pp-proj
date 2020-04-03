/*
** Projeto de Algoritmos Paralelos
** Objeto DataItem - Cabeçalho
*/

#ifndef DATAITEM_HPP
#define DATAITEM_HPP

#include "datatype.hpp"

// Classe para encapsular o tipo de dado utilizado no dataset
class Dataitem {
    private:
        Datatype* attributes;
    public:       
        Datatype* getAttributes();

        void setAttributes(FILE* file, int dimension);
};

#endif //DATAITEM_HPP