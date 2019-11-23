/*
** Projeto de Algoritmos Paralelos
** Objeto Hashtable - Cabeçalho
*/

#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

class Hashtable {
    private:
        long hashsize;

        long length;
        
        int *items;
    public:
        Hashtable(long _capacity, int _hashsize);

        ~Hashtable();

        int* getItem(long key);

        long getHashsize();

        long getLength();
};

#endif //HASHTABLE_HPP