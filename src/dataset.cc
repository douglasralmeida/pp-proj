/*
** Projeto de Algoritmos Paralelos
** Objeto DataSet - Implementação
*/

#include <iostream>
#include "datatype.hpp"
#include "dataset.hpp"

using namespace std;

Dataset::Dataset(int _length, int _dimensions) {
    items = new Datatype[_length*_dimensions];
    length = _length;
    dimensions = _dimensions;
}

Dataset::Dataset(const char* filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        cout << "Erro ao abrir arquivo. Ele nao existe ou esta inacessivel." << endl;
        exit(EXIT_FAILURE);
    }
    if (!(file >> length >> dimensions)) {
        cout << "Erro ao abrir arquivo. Ele esta num formato invalido." << endl;
        exit(EXIT_FAILURE);
    }

    items = new Datatype[length*dimensions];
    if (!items) {
        cout << "Erro ao alocar objeto DATASET. Nao ha memoria suficiente." << endl;
        exit(EXIT_FAILURE);
    }
    int capacity = length*dimensions;
    for (int i = 0; i < capacity; i++)
        file >> items[i];
}

Dataset::~Dataset() {
    delete items;
}

int Dataset::getLength() {
    return length;
}

int Dataset::getDimensions() {
    return dimensions;
}

bool Dataset::loadFromFile(std::ifstream stream) {
    return true;
}

void Dataset::show() {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < dimensions; j++)
            datatype_show(items + (i*dimensions + j));
        cout << endl;
    }
    cout << endl;
}