/*
** Projeto de Algoritmos Paralelos
** LSH Superbit - Implementação
*/

#include "superbit.hpp"
#include "lsh_superbit.hpp"

LSH_Superbit::LSH_Superbit(int nbuckets, int nstages, int dimensions):LSH(nbuckets, nstages) {
    int length = stages * buckets / 2;
    int superbit = computeSuperbit(stages, buckets, dimensions);

    sb = new Superbit(dimensions, superbit, length / superbit, length / superbit);
}

LSH_Superbit::LSH_Superbit(int nbuckets, int nstages, int dimensions, int seed):LSH(nbuckets, nstages) {
    int length = stages * buckets / 2;
    int superbit = computeSuperbit(stages, buckets, dimensions);

    sb = new Superbit(dimensions, superbit, length / superbit, seed);
}

LSH::~LSH() {

}

int computeSuperbit(int stages, int buckets, int dimensions) {

}

bool LSH::createIndex() {

}

int* LSH::hash(bool* attributes, int n) {
    int i;
    int j;
    int* r = new int[stages];
    long* acc = new long[stages];

    for (i = 0; i < stages; i++)
        acc[i] = 0;
    int rows = n / stages;
    for (i = 0; i < n; i++) {
        long x = 0;
        if (attributes[i])
            x = (i+1) * LARGE_PRIME;
        j = std::min(i / rows, stages - 1);
        acc[j] = (acc[j] + x) % INT_MAX;
    }
    for (i = 0; i < stages; i++)
        r[i] = (int)(acc[i] % buckets);

    return r;
}

int* LSH::hash(int* attributes, int n) {
    int* result = new int[stages];
    int rows = n / stages;

    for (int i = 0; i < n; i++) {
        int stage = std::min(i /rows, stages - 1);
        result[stage] = (int)((result[stage] + (long)attributes[i] * LARGE_PRIME) % buckets);
    }

    return result;
}