/*
** Projeto de Algoritmos Paralelos
** Testes com entradas variadas
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include "timer.hpp"
#include "lsh_superbit.hpp"

#ifdef USE_GPU
#include "gpu.hpp"
#endif

using namespace std;

void help(const char* execname) {
    cout << "Sintaxe de comando invalida. Use: " << execname << " #numbuckets #numlines #dimensions" << endl;
}

int main(int argc, const char* argv[]) {
    int buckets, dimensions;
    long size;
    Timer* timer;
    double** entradas;
    std::default_random_engine generator(time(NULL));
    std::normal_distribution<long double> distribution(0.0, 1.0);


    //Analisa os parametros da linha de comando
    if (argc < 4) {
        help(argv[0]);
        exit(EXIT_FAILURE);
    }
    buckets = atoi(argv[1]);
    size = atol(argv[2]);
    dimensions = atoi(argv[3]);
    timer = new Timer();

    #ifdef USE_GPU
    GPU* gpu = new GPU;
    #endif

    //Gera entradas aleatórias
    //usando distribuição normal
    entradas = new double*[size];
    for (long i = 0; i < size; i++) {
        entradas[i] = new double[dimensions];
        for (int j = 0; j < dimensions; j++)
          entradas[i][j] = distribution(generator);
    }

    //Processa o índice LSH
    timer->begin();

    LSH_Superbit* lsh = new LSH_Superbit(buckets, 10, dimensions);
    for (long i = 0; i < size; i++)
        lsh->hash(i, entradas[i]);

    //Tempo gasto
    timer->end();
    cout << buckets << ' ' << dimensions << ' '<< size << ' ';
    timer->show();

    //Limpa a memória
    delete timer;
    for (long i = 0; i < size; i++)
        delete[] entradas[i];
    delete[] entradas;
    delete lsh;

    #ifdef USE_GPU
    delete gpu;
    #endif

    exit(EXIT_SUCCESS);
}