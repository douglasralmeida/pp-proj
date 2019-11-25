/*
** Projeto de Algoritmos Paralelos
** LSH Superbit - TESTE
*/

#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>
#include "gpu.hpp"
#include "math.hpp"
#include "array.hpp"
#include "lsh_superbit.hpp"

#define ARRAY_SIZE 100
#define ARRAY_COUNT 100000
//define ARRAY_SIZE 3
//efine ARRAY_COUNT 100

using namespace std;

int main() {
    double** mm;
    GPU* gpu;
    std::default_random_engine generator(time(NULL));
    std::normal_distribution<long double> distribution(0.0, 1.0);

    cout << "LSH SUPERBIT" << endl;
    cout << "============" << endl << endl;
    gpu = new GPU;
    int stages = 100; //2
    int buckets = 100;//4

    cout << "Gerando entradas aleatorias..." << endl;
    mm = new double*[ARRAY_COUNT];
    for (long i = 0; i < ARRAY_COUNT; i++) {
        mm[i] = new double[ARRAY_SIZE];
        for (int j = 0; j < ARRAY_SIZE; j++)
          mm[i][j] = distribution(generator);  
    }
    int* tables = new int[buckets];
    for (int i = 0; i < buckets; i++)
        tables[i] = 0;

    //começa a medir o tempo aqui
    clock_t begin = clock();

    LSH_Superbit* lsh = new LSH_Superbit(buckets, stages, ARRAY_SIZE);
    cout << "Processando entradas..." << endl;
    for (long i = 0; i < ARRAY_COUNT; i++) {
        for (long j = 0; j < ARRAY_SIZE; j++) {
            //if (mm[i][j] >= 0.0)
            //    cout << ' ';
            //cout << fixed << setprecision(4) << mm[i][j] << '\t';
        }
        lsh->hash(i, mm[i]);
        delete mm[i];
    }

    //termina aqui
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    cout << endl << "Distribution: ";
    lsh->showCounts();

    cout << endl << "Tempo gasto: " << elapsed_secs << endl << endl;
    
    cout << endl << "Finalizando..." << endl;

    delete gpu;
    delete tables;
    delete mm;
    delete lsh;
	exit(EXIT_SUCCESS);
}