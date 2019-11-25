/*
** Projeto de Algoritmos Paralelos
** Manipulação de vetores
*/

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstring>
#include <iostream>

using namespace std;

namespace Array {
    inline double* alloc2d(int row, int col) {
        double* ad;
        unsigned int tam = row * col * sizeof(double);

        cudaMalloc((void**)&ad, tam);

        return ad;
    }

    inline void dealloc2d(double** vector) {
        double* v = *vector;
        cudaFree(v);
    }

    inline void copy(double* source, double* dest, int n) {
        memcpy(dest, source, n * sizeof(source[0]));
    }

    inline void show(double* v, int n) {
        for (int i = 0; i < n; i++)
            cout << v[i] << " ";
        cout << endl;
    }
}
#endif //ARRAY_HPP
