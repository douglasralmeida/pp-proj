/*
** Projeto de Algoritmos Paralelos
** Objeto DataSet - TESTE
*/

#include <iostream>
#include "dataset.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Argumentos incompletos." << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Teste de manipulacao de datasets" << endl;
    cout << "================================" << endl << endl;

    const char* filename = argv[1];
    Dataset* dataset = new Dataset(filename);
    if (dataset) {
        dataset->show();
        delete dataset;
    }
    else {
        cout << "Arquivo não encontrado ou invalido." << endl;
        exit(EXIT_FAILURE);
    }

	exit(EXIT_SUCCESS);
}