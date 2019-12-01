/*
** Projeto de Algoritmos Paralelos
** Superbit - TESTE
*/

#include <iomanip>
#include <iostream>
#include "math.hpp"
#include "array.hpp"
#include "timer.hpp"
#include "superbit.hpp"

#ifdef USE_GPU
#include "gpu.hpp"
#endif

#define ARRAY_SIZE 10

using namespace std;

int main() {
    double* v1;
    double* v2;
    Timer* timer = new Timer;


    #ifdef USE_GPU
    cout << "SIMILARIDADE DE COSSENO vs SIMILARIDADE ESTIMADA SUPERBIT VERSAO CUDA" << endl;
    cout << "=====================================================================" << endl << endl;
    GPU* gpu = new GPU(false);
    #else
    cout << "SIMILARIDADE DE COSSENO vs SIMILARIDADE ESTIMADA SUPERBIT" << endl;
    cout << "=========================================================" << endl << endl;
    #endif

    v1 = new double[ARRAY_SIZE];
    v2 = new double[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++)
        v1[i] = (double)(i+1);
    for (int i = 0; i < ARRAY_SIZE; i++)
        Array::copy(v1, v2, ARRAY_SIZE);
    v1[9] = 912.0;
    v2[8] = 0.0;

    cout << "Vetor V1:" << endl;
    Array::show(v1, ARRAY_SIZE);

    cout << endl << "Vetor V2:" << endl;
    Array::show(v2, ARRAY_SIZE);
    cout << endl;

    timer->begin();
    Superbit* sb = new Superbit(ARRAY_SIZE, ARRAY_SIZE, 10000 / ARRAY_SIZE);
    bool* s1 = sb->computeSignature(v1);
    bool* s2 = sb->computeSignature(v2);
    double esti_similarity = sb->similarity(s1, s2);
    timer->end();
    double real_similarity = Math::consineSimilarity(v1, v2, ARRAY_SIZE);

    cout << fixed << setprecision(7) << "Similaridade estimada: " << esti_similarity << endl;
    cout << fixed << setprecision(7) << "Similaridade real: " << real_similarity << endl;

    std::cout << std::endl << "Tempo gasto: ";
    timer->show();
    std:cout << std::endl << std::endl;

    #ifdef USE_GPU
    delete gpu;
    #endif

    delete[] s1;
    delete[] s2;
    delete[] v1;
    delete[] v2;
    delete sb;
    delete timer;

	exit(EXIT_SUCCESS);
}