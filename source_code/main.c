// João Silva nº 2019134449 - Engenharia Informática - I.S.E.C - 2021

#include <stdio.h>
#include <stdlib.h>
#include "GameController.h"
#include "Interface.h"


int main(){

    initRandom();

    GameController* gameController = NULL;
    run(gameController);
    
    return 0;

}
