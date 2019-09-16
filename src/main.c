/*
Projeto de Algoritmos Paralelos

Utiliza :
- xxHash  : http://www.xxhash.com/
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xxhash.h"

unsigned long long minhash (char *s, int k, int seed) {
    unsigned long long hash = ULLONG_MAX;
    int tamanho = strlen(s);
    char kmem[k];

    for(int i = 0; i < tamanho-k; i++) {
        memcpy(kmem, &s[i], k); // obtem k-mem como um substring de s
        unsigned long long hsh = XXH64(kmem, k, seed);
        if (hsh < hash) {
          hash = hsh;
        }
    }

    return hash;
}

int main(int argc, const char * argv[]){
    if(argc < 4) {
        printf("Argumentos insuficientes.\n");
        printf("Use: pplsh <string> <k> <semente>\n");
        return EXIT_FAILURE;
    }
    char *t = argv[1];
    int k = atoi(argv[2]);
    int s = atoi(argv[3]);
    unsigned long long res = minhash(t, k, s);
    printf("Hash: %llu\n", res);
    exit(EXIT_SUCCESS);
}