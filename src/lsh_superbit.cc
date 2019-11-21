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

LSH_Superbit::~LSH_Superbit() {
    delete sb;
}

int LSH_Superbit::computeSuperbit(int stages, int buckets, int dimensions) {
    int superbit;
    int length = stages * buckets / 2;
    
    for (superbit = dimensions; superbit >= 1; superbit--)
        if (length % superbit == 0)
            break;
    if (superbit == 0) {
        cout << "Erro. Superbit é igual a 0." << endl;
        exit(EXIT_FAILURE);
    }

    return superbit;
}

int* LSH_Superbit::hash(float* attributes, int n) {
    return hashSign(sb->computeSignature(attributes, n), n);
}