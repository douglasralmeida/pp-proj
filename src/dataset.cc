/*
** Projeto de Algoritmos Paralelos
** Objeto DataSet - Implementação
*/

#include <fstream>
#include <iostream>
#include "datatype.hpp"
#include "dataset.hpp"
#include "lsh_superbit.hpp"

using namespace std;

Dataset::Dataset(long _length, int _dimensions) {
    items = new Datatype[_length*_dimensions];
    length = _length;
    dimensions = _dimensions;
    lsh = NULL;
    hasHashTables = false;
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
    long capacity = length*dimensions;
    for (long i = 0; i < capacity; i++)
        file >> items[i];
    lsh = NULL;
    hasHashTables = false;
}

Dataset::~Dataset() {
    delete items;
    delete lsh;
}

void Dataset::computeHashTables(int stages, int buckets) {
    int *h = NULL;

    lsh = new LSH_Superbit(stages, buckets, dimensions);
    for (long i = 0; i < length; i++) {
        long pos = i * dimensions;
        h = lsh->hash(items + pos);
        if (h)
            delete h;
        else {
            cout << "Erro ao gerar tabela hash." << endl;
            return;
        }
    }
    hasHashTables = true;
}

long Dataset::getLength() {
    return length;
}

int Dataset::getDimensions() {
    return dimensions;
}

void Dataset::show() {
    for (long i = 0; i < length; i++) {
        for (int j = 0; j < dimensions; j++)
            datatype_show(items + (i*dimensions + j));
        cout << endl;
    }
    cout << endl;
}