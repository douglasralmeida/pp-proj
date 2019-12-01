/*
** Projeto de Algoritmos Paralelos
** LSH para CPU
*/

#include <iostream>
#include <cstdlib>
#include "timer.hpp"
#include "dataset.hpp"

using namespace std;

void help(const char* execname) {
    cout << "Sintaxe de comando invalida. Use: " << execname << " #datasetfile" << endl;
}

int main(int argc, const char* argv[]) {
    int buckets = 100;
    Timer* timer;
    Dataset* dataset;

    //Analisa os parametros da linha de comando
    if (argc < 2) {
        help(argv[0]);
        exit(EXIT_FAILURE);
    }
    const char* datafile = argv[1];
    timer = new Timer();

    //Carrega os dados para a memória
    cout << "Carregando conjunto de dados..." << endl;
    dataset = new Dataset(datafile);

    //Gera o índice LSH
    cout << "Gerando indice de consulta..." << endl;
    cout << "Indice com " << buckets << " entradas.";
    timer->begin();
    dataset->computeHashTables(3, buckets);
    timer->end();

    timer->show();

    //Limpa a memória
    cout << "Encerrando..." << endl;
    delete dataset;
    delete timer;

    exit(EXIT_SUCCESS);
}