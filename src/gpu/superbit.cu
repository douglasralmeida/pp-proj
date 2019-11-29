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

#define THREADS_PER_BLOCK 512

__global__ void cudaComputeSignature(double* hyperplanes, double* v, int* dimensions, bool* sig, long* hyperp_length) {
    long pos = (threadIdx.x + blockDim.x * blockIdx.x) * (*dimensions);
    double sum = 0.0;

    for (int i=0; i < (*dimensions); i++)
        sum += hyperplanes[i+pos] * v[i];}
    sig[threadIdx.x + blockDim.x * blockIdx.x] = (sum>=0);
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

    cudaMalloc(&d_v,sizeof(double)*dimensions);
    cudaMalloc(&d_sig,sizeof(bool)*hyperp_length);
    cudaMalloc(&d_hyperplanes,sizeof(double)*(hyperp_length*dimensions));
    cudaMalloc(&d_hyperp_length,sizeof(long));
    cudaMalloc(&d_dimensions,sizeof(int));
    cudaMemcpy(d_hyperp_length,&hyperp_length,sizeof(long),cudaMemcpyHostToDevice);
    cudaMemcpy(d_dimensions,&dimensions,sizeof(int),cudaMemcpyHostToDevice);
    cudaMemcpy(d_hyperplanes,hyperplanes,sizeof(double)*(hyperp_length * dimensions),cudaMemcpyHostToDevice);
}

Superbit::Superbit(const int _dimensions, int _superbit, long _length):
    Superbit(_dimensions, _superbit, _length, time(NULL)) {}

Superbit::~Superbit() {
    Array::dealloc2d(&hyperplanes);
}

void Superbit::buildHyperplanes(hpbuilder_t *builderdata) {
    long i, j, k;
    std::default_random_engine generator(builderdata->seed);
    std::normal_distribution<long double> distribution(0.0, 1.0);
    double* v = builderdata->v;
    double* w = builderdata->w;

    for (i = 0; i < hyperp_length; i++) {
        long x = i * dimensions;
        for (j = 0; j < dimensions; j++)
            v[x + j] = distribution(generator);
        Math::normalize(v + x, dimensions);
    }

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
    bool* sig = new bool[hyperp_length];
    bool* sigaux = new bool[hyperp_length];
    
    int NUM_OF_BLOCKS = (hyperp_length + THREADS_PER_BLOCK - 1)/THREADS_PER_BLOCK;

    cudaMemcpy(d_v,v,sizeof(double)*dimensions,cudaMemcpyHostToDevice);
    cudaComputeSignature<<<NUM_OF_BLOCKS,THREADS_PER_BLOCK>>>(d_hyperplanes,d_v,d_dimensions,d_sig,d_hyperp_length);
    cudaMemcpy(sig,d_sig,sizeof(bool)*hyperp_length,cudaMemcpyDeviceToHost);

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