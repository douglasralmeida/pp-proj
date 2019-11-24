/*
** Projeto de Algoritmos Paralelos
** Algoritmo Superbit - Implementação em CPU
*/

#include <cmath>
#include <random>
#include <ctime>
#include "array.hpp"
#include "math.hpp"
#include "superbit.hpp"

Superbit::Superbit(const int _dimensions, int _superbit, int _length, int _seed):dimensions(_dimensions) {
    hpbuilder_t builderdata;

    if (_superbit < 1 || _superbit > _dimensions) {
        cout << "Erro. Profundidade N do SuperBit deve estar entre 1 e o número de dimensões." << endl;
        exit(EXIT_FAILURE);
    }
    hyperp_length = _superbit * _length;
    hyperplanes = Array::alloc2d(hyperp_length, dimensions);
    builderdata.v = Array::alloc2d(hyperp_length, dimensions);
    builderdata.superbit = _superbit;
    builderdata.length = _length;
    builderdata.seed = _seed;
    builderdata.w = hyperplanes;
    buildHyperplanes(&builderdata);
    Array::dealloc2d(&builderdata.v, hyperp_length);
}

Superbit::Superbit(const int _dimensions, int _superbit, int _length):
    Superbit(_dimensions, _superbit, _length, time(NULL)) {}

Superbit::~Superbit() {
    Array::dealloc2d(&hyperplanes, hyperp_length);
}

void Superbit::buildHyperplanes(hpbuilder_t *builderdata) {
    int i, j, k;
    std::default_random_engine generator(builderdata->seed);
    std::normal_distribution<long double> distribution(0.0, 1.0);
    double** v = builderdata->v;
    double** w = builderdata->w;

    for (i = 0; i < hyperp_length; i++) {
        for (j = 0; j < dimensions; j++)
            v[i][j] = distribution(generator);
        Math::normalize(v[i], dimensions);
    }
    for (i = 0; i <= (builderdata->length-1); i++) {
        for (j = 1; j <= builderdata->superbit; j++) {
            int pos = i * builderdata->superbit + j - 1;
            Array::copy(v[pos], w[pos], dimensions);
            for (k = 1; k <= (j-1); k++) {
                int wpos = i * builderdata->superbit + k - 1;
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