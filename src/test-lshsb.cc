/*
** Projeto de Algoritmos Paralelos
** LSH Superbit - TESTE
*/

#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>
#include "math.hpp"
#include "array.hpp"
#include "lsh_superbit.hpp"

#define ARRAY_SIZE 3
#define ARRAY_COUNT 100

using namespace std;

int main() {
    double** mm;
    std::default_random_engine generator(time(NULL));
    std::normal_distribution<long double> distribution(0.0, 1.0);

    cout << "LSH SUPERBIT" << endl;
    cout << "============" << endl << endl;

    int stages = 2;
    int buckets = 4;

    cout << "Gerando entradas aleatorias..." << endl;
    mm = new double*[ARRAY_COUNT];
    for (int i = 0; i < ARRAY_COUNT; i++) {
        mm[i] = new double[ARRAY_SIZE];
        for (int j = 0; j < ARRAY_SIZE; j++)
          mm[i][j] = distribution(generator);  
    }

    LSH_Superbit* lsh = new LSH_Superbit(stages, buckets, ARRAY_SIZE);
    int* tables = new int[buckets];
    for (int i = 0; i < buckets; i++)
        tables[i] = 0;

    cout << "Processando entradas..." << endl;
    for (int i = 0; i < ARRAY_COUNT; i++) {
        for (int j = 0; j < ARRAY_SIZE; j++) {
            if (mm[i][j] >= 0.0)
                cout << ' ';
            cout << fixed << setprecision(4) << mm[i][j] << '\t';
        }
        int* h = lsh->hash(mm[i]);
        if (h) {
            tables[h[0]]++;
            cout << '\t' << h[0] << endl;
            delete h;
        }
        else {
            cout << "Erro." << endl;
            exit(EXIT_FAILURE);
        }
        delete mm[i];
    }
    cout << endl << "Distribution: ";
    for (int i = 0; i < buckets; i++)
        cout << '[' << i << "]=" << tables[i] << ' ';
    
    cout << endl << "Finalizando..." << endl;
    delete tables;
    delete mm;
    delete lsh;
	exit(EXIT_SUCCESS);
}