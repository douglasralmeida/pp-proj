/*
** Projeto de Algoritmos Paralelos
** Objeto DataSet - Implementação
*/

#include <iostream>
#include "datatype.hpp"
#include "dataitem.hpp"
#include "dataset.hpp"

using namespace std;

Dataset::Dataset(int newcapacity, int newdimension) {
    items = new Dataitem[newcapacity];
    capacity = newcapacity;
    dimension = newdimension;
    size = 0;
}

Dataset::~Dataset() {
    delete items;
}

int Dataset::getCapacity() {
    return capacity;
}

int Dataset::getDimension() {
    return dimension;
}

int Dataset::getSize() {
    return size;
}

void Dataset::add(FILE* file) {
    new(items+size) Dataitem;
    items[size].setAttributes(file, dimension);
    size++;
}

bool Dataset::loadFromFile(const char* filename) {
    FILE* f = fopen(filename, "rt");
    if (f == NULL) {
        cout << "Erro ao abrir arquivo " << filename << "." << endl;
        return false;
    }
    for (int i = 0; i < capacity; i++)
        add(f);
    return true;
}

void Dataset::show() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < dimension; j++)
            datatype_show(items[i].getAttributes() + j);
        cout << endl;
    }
    cout << endl;
}