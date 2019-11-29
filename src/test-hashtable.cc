/*
** Projeto de Algoritmos Paralelos
** Hashtable - TESTE
*/

#include <iostream>
#include "hashtable.hpp"

#define HASH_SIZE 3
#define COUNT 5

using namespace std;

int main() {
    Hashtable* ht = new Hashtable(COUNT, HASH_SIZE);

    cout << "TESTE TABELA HASH" << endl;
    cout << "=================" << endl << endl;

    cout << "Gerando tabela hash..." << endl;
    for (long i = 0; i < COUNT; i++) {
        int* r = new int[HASH_SIZE];
        r[0] = i;
        for (long j = 0; j < 4; j++)
          ht->setHash(i, r);
    }

    cout << "Distribuicao da tabela hash:" << endl << endl;
    ht->showCounts();
    
    cout << endl << "Finalizando..." << endl;
    delete ht;
	exit(EXIT_SUCCESS);
}