/*
Projeto de Algoritmos Paralelos
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

__global__ void cuda_olamundo(){
    printf("Ola Mundo direto da GPU!\n");
}

int main(int argc, const char * argv[]){
    cuda_olamundo<<<1,1>>>();
    exit(EXIT_SUCCESS);
}