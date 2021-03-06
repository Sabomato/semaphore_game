// João Silva nº 2019134449 - Engenharia Informática - I.S.E.C - 2021

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>


typedef enum Result {
    TIE , WIN, PLAYING
} Result;


// Inicializa o gerador de numeros aleatorios.
// Esta funcao deve ser chamada apenas uma vez no inicio da execucao do programa
void initRandom();

//Devolve um valor inteiro aleatorio distribuido uniformemente entre [a, b]
int intUniformRnd(int a, int b);

// Devolve o valor 1 com probabilidade prob. Caso contrario, devolve 0
int probEvento(float prob);

#endif /* UTILS_H */
