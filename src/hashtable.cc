/*
** Projeto de Algoritmos Paralelos
** Objeto DataSet - Implementação
*/

#include "hashtable.hpp"

Hashtable::Hashtable(long _length, int _hashsize) {
    items = new int[_length*_hashsize];
    hashsize = _hashsize;
    length = _length;
}

Hashtable::~Hashtable() {
    delete items;
}

int* Hashtable::getItem(long key) {
    return items + (key*hashsize);
}

long Hashtable::getHashsize() {
    return hashsize;
}

long Hashtable::getLength() {
    return length;
}