/*
** Projeto de Algoritmos Paralelos
** LSH - Implementação
*/

#include <algorithm>
#include <climits>
#include "lsh.hpp"

int LARGE_PRIME = 433494437; //2147483647; //2^31-1

LSH::LSH(int nbuckets, int nstages) {
    buckets = nbuckets;
    stages = nstages;
    table = new Hashtable(buckets, stages);
}

LSH::~LSH() {
    if (table)
        delete table;
}

void LSH::hashSign(long id, bool* attributes, int n) {
    int i, j;
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
    table->setHash(id, r);

    delete[] acc;
}

void LSH::showCounts() {
    if (table)
        table->showCounts();
}