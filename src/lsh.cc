/*
** Projeto de Algoritmos Paralelos
** LSH - Implementação
*/

#include <cstdint>
#include "lsh.hpp"

int LARGE_PRIME = 2147483647; //2^31-1

LSH::LSH(int nbuckets, int nstages) {
    buckets = nbuckets;
    stages = nstages;
    threshold = 0;
}

LSH::~LSH() {

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