/*
** Projeto de Algoritmos Paralelos
** Objeto DataSet - Implementação
*/

#include <iostream>
#include "hashtable.hpp"

Hashtable::Hashtable(int _buckets, int _hashsize) {
    items = new hashitem_s[_buckets];
    for (int i = 0; i < _buckets; i++) {
        items[i].index = new long[HASH_CAPACITY];
        items[i].hash = NULL;
        items[i].count = 0;
    }
    hashsize = _hashsize;
    length = _buckets;
}

Hashtable::~Hashtable() {
    for (int i = 0; i < length; i++) {
        delete items[i].index;
        if (items[i].hash)
            delete items[i].hash;
    }
    delete items;
}

void Hashtable::setHash(int key, int* hash) {
    int idx = hash[0];

    if (items[idx].count == 0)
       items[idx].hash = hash;
    items[idx].index[items[idx].count] = key;
    items[idx].count++;
}

int Hashtable::getHashsize() {
    return hashsize;
}

long Hashtable::getLength() {
    return length;
}

void Hashtable::showCounts() {
    for (long i = 0; i < length; i++)
        std::cout << '[' << i << "]=" << items[i].count << " ";
    std::cout << std::endl;
}

void Hashtable::showIds(int hash) {
    for (int i = 0; i < items[hash].count; i++)
        std::cout << items[hash].index[i] << " ";
    std::cout << std::endl;
}