/*
** Projeto de Algoritmos Paralelos
** Objeto Hashtable - Cabeçalho
*/

#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#define HASH_CAPACITY 10000

typedef struct hashitem_s {
    long count;

    long* index;

    int* hash;
} hashitem_t;

class Hashtable {
    private:
        int hashsize;

        long length;
        
        hashitem_t* items;
    public:
        Hashtable(int _buckets, int _hashsize);

        ~Hashtable();

        int getHashsize();

        long getLength();

        void setHash(int key, int* hash);

        void showCounts();

        void showIds(int hash);
};

#endif //HASHTABLE_HPP