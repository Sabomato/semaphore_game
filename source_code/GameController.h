// João Silva nº 2019134449 - Engenharia Informática - I.S.E.C - 2021

#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER

#include "utils.h"
#include "Board.h"
#include "Player.h"
#include "Snapshot.h"


#define MAX_CONTROLLER_CHARS (MAX_BOARD_CHARS + MAX_PLAYER_CHARS + 28)

typedef enum State{
    PLAY_VIRTUAL = 1,PLAY_HUMAN,GAME_OVER
} State;


typedef struct GameController GameController;



bool isValidPlayG(GameController * gameController, short nColumn, short nRow, char piece);

GameController* GameController_create(short playerType);

void GameController_destroy(GameController* gameController);

void addSnapshotG(GameController * gameController);

bool PlayRockG(GameController* gameController, short nColumn, short nRow);

void playVirtualG(GameController* gameController);

void playPieceVirtualG(GameController* gameController);

bool saveSnapshotG(GameController* gameController, char* filename);

void playPieceHumanG(GameController * gameController,short nColumn, short nRow,char piece);

bool increaseColumnG(GameController * gameController);

bool increaseRowG(GameController * gameController);

bool isValidPlayG(GameController * gameController, short nColumn, short nRow, char piece);

bool existsValidPlay(GameController * gameController);

short getCurrentPlayerType(const GameController * gameController);

char * getWinner(const GameController * gameController);

State getState(GameController * GameController);

unsigned short getTurn(GameController* gameController);

void switchPlayer(GameController * gameController);

void endTurn(GameController * gameController);

char * printGameController(const GameController * gameController);

char * printPreviousPlays(const GameController * gameController, short nPlays);

bool saveGameController(GameController* gameController, FILE** f);

GameController* loadGameController(FILE** f);

#endif