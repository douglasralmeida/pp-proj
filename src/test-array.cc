/*
** Projeto de Algoritmos Paralelos
** Namespace Array - TESTE
*/

#include <iostream>
#include "array.hpp"
#include "math.hpp"

#define ARRAY_SIZE 10

using namespace std;

int main() {
    double* source;
    double* dest;

    source = new double[ARRAY_SIZE];
    dest = new double[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++)
        source[i] = (double)2*i;
    for (int i = 0; i < ARRAY_SIZE; i++)
        Array::copy(source, dest, ARRAY_SIZE);

    cout << "Source array" << endl;
    Array::show(source, ARRAY_SIZE);

    cout << "Dest array" << endl;
    Array::show(dest, ARRAY_SIZE);

    delete source;
    delete dest;
	exit(EXIT_SUCCESS);
}