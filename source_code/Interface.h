// João Silva nº 2019134449 - Engenharia Informática - I.S.E.C - 2021

#ifndef INTERFACE
#define INTERFACE

#include "GameController.h"
#include "SaveGame.h"

#define ROWS 0
#define COLUMNS 1
#define STATES_SAVE_PATH "..\\sucession-states-examples\\"
#define STATE_NAME_SIZE 25

typedef enum Option{
    PLAY_PIECE_HUMAN,WATCH_PREVIOUS,INC_BOARD_HUMAN,PLAY_ROCK_HUMAN,LEAVE
} Option;



void askFileName(GameController* gameController);

bool PlayGame(GameController * GameController);

void run(GameController * gameController);

void wantsVirtualAdversary(GameController ** gameController);

bool PlayHuman(GameController * gameController);

bool checkPreviousGameFile();

bool getPositionToPlay( short* nColumn, short* nRow);

bool getPieceToPlay(GameController* gameController,short* nColumn,short* nRow,char* piece);

short getAnswerBetweenXandY(short x, short y);

bool getYesOrNoAnswer();

bool cleanStdin();


#endif