/*
** Projeto de Algoritmos Paralelos
** Temporizador - Cabeçalho
*/

#ifndef TIMER_HPP
#define TIMER_HPP

#include <ctime>

class Timer {
    private:
        clock_t starttime;

        clock_t endtime;
    public:
        Timer();

        void begin();

        void end();

        void show();
};

#endif //TIMER_HPP