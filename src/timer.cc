/*
** Projeto de Algoritmos Paralelos
** Temporizador - Implementação
*/

#include <iostream>
#include "timer.hpp"

Timer::Timer() {
    starttime = 0;
    endtime = 0;
}

void Timer::begin() {
    starttime = clock();
}

void Timer::end() {
    endtime = clock();
}

void Timer::show() {
    double elapsed_secs = double(endtime - starttime) / CLOCKS_PER_SEC;

    std::cout << elapsed_secs << "s";
}