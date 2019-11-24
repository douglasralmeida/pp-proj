/*
** Projeto de Algoritmos Paralelos
** LSH Superbit - Implementação
*/

#include <iostream>
#include "superbit.hpp"
#include "lsh_superbit.hpp"

LSH_Superbit::LSH_Superbit(int nbuckets, int nstages, int ndimensions):LSH(nbuckets, nstages) {
    int length = stages * buckets / 2;
    dimensions = ndimensions;
    int superbit = computeSuperbit(stages, buckets);

    sb = new Superbit(dimensions, superbit, length / superbit, length / superbit);
}

LSH_Superbit::LSH_Superbit(int nbuckets, int nstages, int ndimensions, int seed):LSH(nbuckets, nstages) {
    int length = stages * buckets / 2;
    dimensions = ndimensions;
    int superbit = computeSuperbit(stages, buckets);

    sb = new Superbit(dimensions, superbit, length / superbit, seed);
}

LSH_Superbit::~LSH_Superbit() {
    delete sb;
}

int LSH_Superbit::computeSuperbit(int stages, int buckets) {
    int superbit;
    int length = stages * buckets / 2;
    
    for (superbit = dimensions; superbit >= 1; superbit--)
        if (length % superbit == 0)
            break;
    if (superbit == 0) {
        std::cout << "Erro. Superbit é igual a 0." << std::endl;
        exit(EXIT_FAILURE);
    }

    return superbit;
}

void LSH_Superbit::hash(long id, double* attributes) {
    bool* sig = sb->computeSignature(attributes);
    int siglen = sb->getSignatureLength();
    
    hashSign(id, sig, siglen);
}