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
        int* r = ht->getItem(i);
        for (long j = 0; j < HASH_SIZE; j++)
          r[j] = j;
    }

    cout << "Exibindo tabela hash..." << endl;
    for (long i = 0; i < COUNT; i++) {
        int* r = ht->getItem(i);
        for (long j = 0; j < HASH_SIZE; j++)
          cout << r[j] <<  ' ';
        cout << endl;
    }
    
    cout << endl << "Finalizando..." << endl;
    delete ht;
	exit(EXIT_SUCCESS);
}