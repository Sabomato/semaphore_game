// João Silva nº 2019134449 - Engenharia Informática - I.S.E.C - 2021

#include "Player.h"


typedef struct Player {

    char name;
    unsigned short nBoardIncreases, nRocks;
    short playerType;

} Player;



char* printPlayer(Player * player){

    static char buffer[MAX_PLAYER_CHARS];

    buffer [0] = '\0';
    sprintf_s(buffer,sizeof(buffer)-1,"Player:%c nRocks:%d nBoardIncreases:%d \n",player->name,player->nRocks,player->nBoardIncreases);
    
    return buffer;

}

Player * Player_create(char name, short playerType){

    Player* player = (Player*) malloc(sizeof(Player));
    if (player == NULL) {
        perror("Error allocating memory (Player_create)");
        return NULL;
    }

    player->nRocks = 1;
    player ->nBoardIncreases = 2;
    player ->name = name; 
    player ->playerType = playerType;

    return player;
}

Player* copyPlayer(const Player* orig) {

    if(orig == NULL) {
        fprintf(stderr, "player was null (copyPlayer)\n");
        return NULL;
    }
    Player *newP = (Player*) malloc(sizeof(Player));
    if (newP == NULL) {
        perror("Error allocating memory (copyPlayer)");
        return NULL;
    }

    newP->name = orig->name;
    newP->nBoardIncreases = orig->nBoardIncreases;
    newP->nRocks = orig->nRocks;
    newP->playerType = orig->playerType;

    return newP;
}

void Player_destroy(Player * player) {

    if (player == NULL) {
        fprintf(stderr,"player was null (Player_destroy)\n");
        return;
    }
    free(player);
}

bool playRock(Player * player){

    if(player->nRocks < 1)
        return false;   

    --(player->nRocks);
    return true;
}

bool IncreaseBoardP(Player * player){

    if(player->nBoardIncreases < 1)
        return false;

    --(player->nBoardIncreases);
    return true;
}


short getPlayerType(Player* player) {

    return player->playerType;
}

unsigned short getNRocks(Player* player) {

    return player->nRocks;
}

unsigned short getNBoardIncreases(Player* player) {

    return player->nBoardIncreases;
}

char getValidPlay(char piece,Player * player){

    switch(piece){

    case ' ':
        return probEvento((float)(1 - PROB_PLAY_ROCK)) || player->nRocks == 0 ? 'G':'O';

    case 'G':        
        return 'Y';
        
    case 'Y':
        return 'R';
    
      
    default:

        if( piece == 'R' || piece ==  'O'){

            if(player->nBoardIncreases == 0)
                return NO_VALID_PLAY;
            else 
                return 'I';    
        }
        
    }
    return NO_VALID_PLAY;    

}

short playVirtualP(Player * player,Board * board){

    unsigned short nRow = intUniformRnd(0,getNRows(board) - 1);
    unsigned short nColumn = intUniformRnd(0,getNCols(board) - 1);

    char randPiece = getPieceByPos(board,nRow,nColumn);
    
    char piece = getValidPlay(randPiece,player);
    
    while( piece == NO_VALID_PLAY){

        nRow = intUniformRnd(1,getNRows(board));
        nColumn = intUniformRnd(1,getNCols(board));

        randPiece = getPieceByPos(board,nRow,nColumn);
       
        piece = getValidPlay(randPiece, player);
    }
    switch (piece) {

    case 'I': 
        if (IncreaseBoardP(player))
           return probEvento(0.5) ? increaseBoardNColumns(board) : increaseBoardNRows(board);
        break;
    case 'O':
        if (playRock(player))
            return playRockB(board, nColumn, nRow);
        break;
    default:
        return PlayPiece(board, nColumn, nRow, piece);

    }
    return false;

}

Player* LoadPlayer(FILE** f) {

    Player* player = (Player*) malloc(sizeof(Player));
    if (player == NULL) {
        perror("Error allocating memory (Player_create)");
        return NULL;
    }

    if (fread(player, sizeof(Player), 1, *f) != 1 && ferror(*f))
    {
        perror("Error reading player in file (loadPlayer)");
        free(player);
        return NULL;
    }
        
    return player;
}

bool SavePlayer(FILE **f,Player *player) {

    
    if (player == NULL) {
        fprintf(stderr,"player was null\n");
        return false;
    }

    if (fwrite(player, sizeof(Player), 1, *f) != 1 && ferror(*f))
    {
        perror("Error writing player in file (SavePlayer)");
        return false;
    }
    return true;
}




