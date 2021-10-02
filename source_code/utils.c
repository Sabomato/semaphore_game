// João Silva nº 2019134449 - Engenharia Informática - I.S.E.C - 2021


#include "utils.h"

void initRandom(){
    srand((unsigned int)time(NULL));
}

int intUniformRnd(int a, int b){
    return a + rand()%(b-a+1);
}

int probEvento(float prob){
    return prob > ((float)rand()/RAND_MAX);
}
