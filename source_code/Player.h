// João Silva nº 2019134449 - Engenharia Informática - I.S.E.C - 2021

#ifndef PLAYER
#define PLAYER

#include "utils.h"
#include "Board.h"


#define MAX_PLAYER_CHARS 50
#define HUMAN 1
#define VIRTUAL 2
#define PROB_PLAY_ROCK 0.2
#define PROB_INC_BOARD 0.1

#define INC_BOARD_COLS 2
#define INC_BOARD_ROWS 3
#define PLAY_ROCK 1
#define PLAY_PIECE_VIRTUAL 0

#define NO_VALID_PLAY '0'

typedef struct Player Player;

enum possiblePlays{
    
    ROCK,GREEN,YELLOW,RED,INC_ROW,INC_COLS

};



short getPlayerType(Player* player);

unsigned short getNRocks(Player* player);

unsigned short getNBoardIncreases(Player* player);

char* printPlayer(Player * player);

Player * Player_create( char name, short playerType);

void Player_destroy(Player* player);

Player* copyPlayer(const Player* orig);

bool playRock(Player * player);

bool IncreaseBoardP(Player * player);

short playVirtualP(Player* player, Board* board);

bool playRockVirtualP(Player* player, Board* board);

Player* LoadPlayer(FILE** f);

bool SavePlayer(FILE** f, Player* player);

char getValidPlay(char piece, Player * player);

short choosePlayVirtual(Player * player);


#endif