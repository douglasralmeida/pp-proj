/*
** Projeto de Algoritmos Paralelos
** Objeto DataSet - TESTE
*/

#include <iostream>
#include "dataitem.hpp"
#include "dataset.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Argumentos incompletos." << endl;
        exit(EXIT_FAILURE);
    }
    const char* arquivo = argv[1];
    Dataset* dataset = new Dataset(3, 5);
    if (dataset->loadFromFile(arquivo)) {
        dataset->show();
        delete dataset;
    }
    else {
        cout << "Arquivo não encontrado ou inválido." << endl;
        exit(EXIT_FAILURE);
    }

	exit(EXIT_SUCCESS);
}