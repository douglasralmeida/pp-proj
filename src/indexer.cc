/*
** Projeto de Algoritmos Paralelos
** LSH para CPU
*/

#include <iostream>
#include <cstdlib>
#include "timer.hpp"
#include "dataset.hpp"

#ifdef USE_GPU
#include "gpu.hpp"
#endif


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

    #ifdef USE_GPU
    GPU* gpu = new GPU(true);
    #endif

    const char* datafile = argv[1];
    timer = new Timer();

    //Carrega os dados para a memória
    cout << "Carregando conjunto de dados..." << endl;
    dataset = new Dataset(datafile);

    //Gera o índice LSH
    cout << "Gerando indice de consulta..." << endl;
    cout << "Dataset com tamanho " << dataset->getLength() << "x" << dataset->getDimensions() << "." << endl;
    cout << "Tabela hash com " << buckets << " entradas." << endl;
    timer->begin();
    dataset->computeHashTables(50, buckets);
    timer->end();

    //Tempo
    cout << "Tempo gasto: ";
    timer.show();
    cout << endl;

    //Limpa a memória
    cout << "Encerrando..." << endl;
    delete dataset;
    delete timer;

    #ifdef USE_GPU
    delete gpu;
    #endif

    exit(EXIT_SUCCESS);
}