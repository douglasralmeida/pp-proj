/*
** Projeto de Algoritmos Paralelos
** Algoritmo Superbit - Implementação em CPU
*/

#include <curand.h>
#include <curand_kernel.h>

#include <cstdio>

#include <cmath>
#include <random>
#include <ctime>
#include "array.hpp"
#include "math.hpp"
#include "superbit.hpp"

#define THREADS 64
#define BLOCKS 64

__global__ void cuda_rand_init(unsigned long seed, curandState* state) {
    int id = threadIdx.x + blockIdx.x * blockDim.x;

    curand_init(seed, id, 0, &state[id]);
}

__global__ void cuda_distribuition(curandState* state, double* vector) {
    int id = threadIdx.x + blockIdx.x * blockDim.x;

    vector[id] = curand_normal_double(&state[id]);
}

Superbit::Superbit(const int _dimensions, int _superbit, long _length, int _seed):dimensions(_dimensions) {
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
    Array::dealloc2d(&builderdata.v);
}

Superbit::Superbit(const int _dimensions, int _superbit, long _length):
    Superbit(_dimensions, _superbit, _length, time(NULL)) {}

Superbit::~Superbit() {
    Array::dealloc2d(&hyperplanes);
}

void Superbit::buildHyperplanes(hpbuilder_t *builderdata) {
    long i, j, k;
    curandState* devStates;
    double* v = builderdata->v;
    double* w = builderdata->w;

    cudaMalloc((void**)&devStates, THREADS * BLOCKS * sizeof(curandState));
    cuda_rand_init<<<BLOCKS, THREADS>>>(builderdata->seed, devStates);
    cuda_distribuition<<<BLOCKS, THREADS>>>(devStates, v);

    //Normaliza
    double rV;
    cudaMemcpy(&rV, v, sizeof(double), cudaMemcpyDeviceToHost);
    std::cout << rV << endl;

    cudaFree(v);
    exit(0);


    for (i = 0; i <= (builderdata->length-1); i++) {
        for (j = 1; j <= builderdata->superbit; j++) {
            int pos = (i * builderdata->superbit + j - 1)*dimensions;
            Array::copy(v + pos, w + pos, dimensions);
            for (k = 1; k <= (j-1); k++) {
                int wpos = (i * builderdata->superbit + k - 1)*dimensions;
                Math::sub(w + pos,
                    Math::product(
                        Math::dotProduct(w + wpos, v + pos, dimensions),
                        w + wpos,
                        dimensions),
                    dimensions);
            }
            Math::normalize(w + pos, dimensions);
        }
    }
}

bool* Superbit::computeSignature(double* v) {
    long pos;
    bool* sig = new bool[hyperp_length];

    for (long i = 0; i < hyperp_length; i++) {
        pos = i * dimensions;
        sig[i] = (Math::dotProduct(hyperplanes + pos, v, dimensions) >= 0.0);
    }

    return sig;
}

long Superbit::getSignatureLength() {
    return hyperp_length;
}

double Superbit::similarity(bool* s1, bool* s2) {
    double sum = 0;

    for (long i = 0; i < hyperp_length; i++)
        if (s1[i] == s2[i])
            sum++;
    sum /= hyperp_length;

    return cos((1 - sum) * acos(-1)); //acos(-1)=pi
}
