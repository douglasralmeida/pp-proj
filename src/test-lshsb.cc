/*
** Projeto de Algoritmos Paralelos
** LSH Superbit - TESTE
*/

#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>
#include "timer.hpp"
#include "math.hpp"
#include "array.hpp"
#include "lsh_superbit.hpp"

#ifdef USE_GPU
#include "gpu.hpp"
#endif

#define ARRAY_SIZE 100
#define ARRAY_COUNT 100000
//define ARRAY_SIZE 3
//efine ARRAY_COUNT 100

using namespace std;

int main() {
    int stages = 100; //2
    int buckets = 100;//4
    double** entradas;
    std::default_random_engine generator(time(NULL));
    std::normal_distribution<long double> distribution(0.0, 1.0);
    Timer* timer = new Timer;


    #ifdef USE_GPU
    cout << "LSH SUPERBIT para CUDA" << endl;
    cout << "======================" << endl << endl;
    GPU* gpu = new GPU;
    #else
    cout << "LSH SUPERBIT" << endl;
    cout << "============" << endl << endl;
    #endif


    cout << "Gerando entradas aleatorias..." << endl;
    cout << "Matriz " << ARRAY_COUNT << "x" << ARRAY_SIZE << "." << endl;
    entradas = new double*[ARRAY_COUNT];
    for (long i = 0; i < ARRAY_COUNT; i++) {
        entradas[i] = new double[ARRAY_SIZE];
        for (int j = 0; j < ARRAY_SIZE; j++)
          entradas[i][j] = distribution(generator);  
    }
    int* tables = new int[buckets];
    for (int i = 0; i < buckets; i++)
        tables[i] = 0;

    //começa a medir o tempo aqui
    timer->begin();

    LSH_Superbit* lsh = new LSH_Superbit(buckets, stages, ARRAY_SIZE);
    cout << "Processando entradas..." << endl;
    for (long i = 0; i < ARRAY_COUNT; i++) {
        lsh->hash(i, entradas[i]);
        delete[] entradas[i];
    }

    //termina de medir aqui
    timer->end();

    cout << endl << "Distribuicao: ";
    lsh->showCounts();
    timer->show();
    cout << endl << "Finalizando..." << endl;


    #ifdef USE_GPU
    delete gpu;
    #endif

    
    delete[] tables;
    delete[] entradas;
    delete lsh;
    delete timer;
	exit(EXIT_SUCCESS);
}
