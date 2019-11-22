/*
** Projeto de Algoritmos Paralelos
** Algoritmo Superbit - Implementação
*/

#include <cmath>
#include <random>
#include <ctime>
#include "array.hpp"
#include "math.hpp"
#include "superbit.hpp"

Superbit::Superbit(const int _dimensions, int _superbit, int _length, int _seed):dimensions(_dimensions) {
    int i, j, k;
    double** v, **w;
    std::default_random_engine generator(_seed);
    std::normal_distribution<long double> distribution(0.0, 1.0);

    int code_length = _superbit * _length;
    
    v = Array::alloc2d(code_length, dimensions);
    for (i = 0; i < code_length; i++) {
        for (j = 0; j < dimensions; j++)
            v[i][j] = distribution(generator);
        Math::normalize(v[i], dimensions);
    }

    w = Array::alloc2d(code_length, dimensions);
    for (i = 0; i <= (_length-1); i++) {
        for (j = 1; j <= _superbit; j++) {
            int pos = i * _superbit + j - 1;
            Array::copy(v[pos], w[pos], dimensions);
            for (k = 1; k <= (j-1); k++) {
                int wpos = i * _superbit + k - 1;
                w[pos] = Math::sub(w[pos],
                    Math::product(
                        Math::dotProduct(w[wpos], v[pos], dimensions),
                        w[wpos],
                        dimensions),
                    dimensions);
            }
            Math::normalize(w[pos], dimensions);
        }
    }
    hyperplanes = w;
    hyperp_length = code_length;
    Array::dealloc2d(&v, code_length);
}

Superbit::Superbit(const int _dimensions, int _superbit, int _length):
    Superbit(_dimensions, _superbit, _length, time(NULL)) {}

Superbit::~Superbit() {
    Array::dealloc2d(&hyperplanes, hyperp_length);
}

bool* Superbit::computeSignature(double* v) {
    bool* sig = new bool[hyperp_length];

    for (int i = 0; i < hyperp_length; i++)
        sig[i] = (Math::dotProduct(hyperplanes[i], v, dimensions) >= 0.0);

    return sig;
}

int Superbit::getSignatureLength() {
    return hyperp_length;
}

double Superbit::similarity(bool* s1, bool* s2) {
    double sum = 0;

    for (int i = 0; i < hyperp_length; i++)
        if (s1[i] == s2[i])
            sum++;
    sum /= hyperp_length;

    return cos((1 - sum) * acos(-1)); //acos(-1)=pi
}