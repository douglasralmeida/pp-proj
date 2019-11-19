/*
** Projeto de Algoritmos Paralelos
** LSH para CPU
*/

#include <iostream>
#include <cstdlib>
#include "dataset.hpp"

using namespace std;

void help(const char* execname) {
    cout << "Wrong command syntax. Usage: " << execname << " #datasetfile #points-in-dataset #num-of-dimensions" << endl;
}

int main(int argc, const char* argv[]) {
    Dataset* dataset;

    if (argc < 4) {
        help(argv[0]);
        exit(EXIT_FAILURE);
    }

    //Analisa os parametros da linha de comando
    const char* datafile = argv[1];
    const int numPoints = atoi(argv[2]);
    const int numDim = atoi(argv[3]);

    //Carrega os dados para a memória
    dataset = new Dataset(numPoints, numDim);
    if (dataset->loadFromFile(datafile)) {
        dataset->show();
    }
    else {
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}