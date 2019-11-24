/*
** Projeto de Algoritmos Paralelos
** LSH para CPU
*/

#include <iostream>
#include <cstdlib>
#include "dataset.hpp"


using namespace std;

void help(const char* execname) {
    cout << "Wrong command syntax. Usage: " << execname << " #datasetfile" << endl;
}

int main(int argc, const char* argv[]) {
    Dataset* dataset;

    //Analisa os parametros da linha de comando
    if (argc < 2) {
        help(argv[0]);
        exit(EXIT_FAILURE);
    }
    const char* datafile = argv[1];

    //Carrega os dados para a memória
    cout << "Carregando conjunto de dados..." << endl;
    dataset = new Dataset(datafile);

    //Gera o índice LSH
    cout << "Gerando indice de consulta..." << endl;
    dataset->computeHashTables(2, 2);
    
    //Limpa a memória
    cout << "Encerrando..." << endl;
    delete dataset;

    exit(EXIT_SUCCESS);
}