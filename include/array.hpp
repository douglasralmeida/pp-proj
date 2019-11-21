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
    inline double** alloc2d(int row, int col) {
        double** a = new double*[row];

        for (int i = 0; i < row; i++)
            a[i] = new double[col];

        return a;
    }

    inline void dealloc2d(double*** vector, int row) {
        double** v = *vector;

        for (int i = 0; i < row; i++)
            delete[] v[i];
        
        delete[] v;
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