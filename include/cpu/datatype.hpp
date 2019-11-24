/*
** Projeto de Algoritmos Paralelos
** Objeto DataType - Cabeçalho
*/

#ifndef DATATYPE_HPP
#define DATATYPE_HPP

#include <iostream>
#include <iomanip>

using namespace std;

typedef double Datatype;

inline void datatype_fscanf(FILE* f, Datatype* item) {
    fscanf(f, "%lf", item);
}

inline void datatype_show(Datatype* item) {
    cout << fixed << setprecision(2) <<  *item << " ";
}

#endif //DATATYPE_HPP