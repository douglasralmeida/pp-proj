/*
** Projeto de Algoritmos Paralelos
** Objeto DataSet - Implementação
*/

#include <iostream>
#include "dataitem.hpp"
#include "dataset.hpp"

using namespace std;

Dataset::Dataset(int newcapacity) {
    items = (Dataitem*)malloc(sizeof(Dataitem) * newcapacity;
    capacity = newcapacity;
    size = 0;
}

int Dataset::getCapacity() {
    return capacity;
}

int Dataset::getSize() {
    return size;
}

void Dataset::add(FILE* file) {
    Dataitem di;
    for (int i = 0; i < dimmension; i++) {
        
    }
    items[0] = 
}

bool Dataset::openFile(const char* filename) {
    
}
