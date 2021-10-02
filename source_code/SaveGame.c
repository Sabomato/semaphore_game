// João Silva nº 2019134449 - Engenharia Informática - I.S.E.C - 2021

#include "SaveGame.h"

bool fileExists(){

    FILE * f = NULL;   

    f = fopen(SAVE_FILE_PATH,"rb");

    if(errno == ENOENT)
        return false;

    if(f == NULL){
        perror("Error loading game file(loadGame(fopen))");
        return false;
    }
    fclose(f);
    return true;
}   


bool saveGame(GameController * gameController){

    FILE * f = NULL;   

    f = fopen(SAVE_FILE_PATH,"wb");

    if(f == NULL){
        perror("Error saving game file(saveGame(fopen))");
        return false;
    }

    if(!saveGameController(gameController,&f))
    {
        perror("Error saving game file(saveGame(saveGameController))");
        if(remove(SAVE_FILE_PATH))
            perror("Error removing failed save file");
        fclose(f);

        return false;
    }

    
    fclose(f);
   
    return true;
}

GameController* loadGame(){

    FILE * f = NULL;   
    GameController* gameController = NULL;
    
    if((f = fopen(SAVE_FILE_PATH, "rb")) == NULL){
        perror("Error loading game file(loadGame(fopen))");
        return NULL;
    }

    if((gameController = loadGameController(&f)) == NULL)
    {   
        fclose(f);
        if (remove(SAVE_FILE_PATH))
            perror("Error removing failed save file");
        return NULL;
    }

    fclose(f);
    return gameController;
}