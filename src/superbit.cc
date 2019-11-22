/*
** Projeto de Algoritmos Paralelos
** Algoritmo Superbit - Implementação
*/

#include <cmath>
#include <random>
#include "array.hpp"
#include "math.hpp"
#include "superbit.hpp"

Superbit::Superbit(const int dimensions, int superbit, int length, int seed) {
    int i, j;
    double** v, **w;
    std::default_random_engine generator(seed);
    std::normal_distribution<long double> distribution(0.0, 1.0);

    int code_length = superbit * length;
    
    v = Array::alloc2d(code_length, dimensions);
    for (i = 0; i < code_length; i++) {
        for (j = 0; j < dimensions; j++)
            v[i][j] = distribution(generator);
        Math::normalize(v[i], dimensions);
    }

    w = Array::alloc2d(code_length, dimensions);
    for (i = 0; i <= (length-1); i++) {
        for (j = 1; j <= superbit; j++) {
            int pos = i * superbit + j - 1;
            Array::copy(v[pos], w[pos], dimensions);
            for (int k = 1; k <= (j-1); k++) {
                int wpos = i * superbit + k - 1;
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

Superbit::~Superbit() {
    Array::dealloc2d(&hyperplanes, hyperp_length);
}

bool* Superbit::computeSignature(double* v, int n) {
    bool* sig = new bool[hyperp_length];

    for (int i = 0; i < hyperp_length; i++)
        sig[i] = (Math::dotProduct(hyperplanes[i], v, n) >= 0.0);

    return sig;
}

double Superbit::similarity(bool* s1, bool* s2, int n) {
    double sum = 0;

    for (int i = 0; i < n; i++)
        if (s1[i] == s2[i])
            sum++;
    sum /= n;

    return cos((1 - sum) * acos(-1)); //acos(-1)=pi
}