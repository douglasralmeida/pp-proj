/*
** Projeto de Algoritmos Paralelos
** Objeto DataItem - Implementação
*/
#include "datatype.hpp"
#include "dataitem.hpp"

Dataitem::Dataitem(Datatype* newattributes) {
    attributes = newattributes;
}

Datatype* Dataitem::getAttributes() {
    return attributes;
}