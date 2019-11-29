/*
** Projeto de Algoritmos Paralelos
** Namespace Array - TESTE
*/

#include <iostream>
#include "array.hpp"

#define ARRAY_SIZE 10

using namespace std;

int main() {
    double* source;
    double* dest;

    cout << "Teste de alocacao de vetores" << endl;
    cout << "============================" << endl << endl;

    cout << "Alocando vetor1..." << endl;

    source = new double[ARRAY_SIZE];
    dest = new double[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++)
        source[i] = (double)2*i;

    cout << endl << "Vetor de origem:" << endl;
    Array::show(source, ARRAY_SIZE);
    
    cout << endl << "Copiando vetor1 para vetor2..." << endl;

    for (int i = 0; i < ARRAY_SIZE; i++)
        Array::copy(source, dest, ARRAY_SIZE);

    cout << endl << "Vetor de destino:" << endl;
    Array::show(dest, ARRAY_SIZE);

    cout << endl << "Finalizando..." << endl;

    delete source;
    delete dest;
	exit(EXIT_SUCCESS);
}