/*
** Projeto de Algoritmos Paralelos
** Objeto DataItem - Implementação
*/

#include <iostream>
#include "datatype.hpp"
#include "dataitem.hpp"

Datatype* Dataitem::getAttributes() {
    return attributes;
}

void Dataitem::setAttributes(FILE* file, int dimension) {
    attributes = new Datatype[dimension];
    for (int i = 0; i < dimension; i++)
        datatype_fscanf(file, attributes + i);
}