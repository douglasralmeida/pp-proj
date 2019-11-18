/*
** Projeto de Algoritmos Paralelos
** Objeto DataItem - Cabeçalho
*/

#ifndef DATAITEM_HPP

#define DATAITEM_HPP

class Dataitem {
    private:
        Datatype* attributes;
    public:       
        Datatype* getAttributes();

        void setAttributes(Datatype* attributes);
};

#endif //DATAITEM_HPP