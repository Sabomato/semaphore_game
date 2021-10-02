// João Silva nº 2019134449 - Engenharia Informática - I.S.E.C - 2021

#include "GameController.h"

typedef struct GameController {

    unsigned short turn;
    short result;
    Player* A, * B, * current;
    Board* board;
    State state;
    Snapshot* snapshots;

} GameController;

GameController * GameController_create(short playerType){

    GameController* gameController = (GameController*) malloc(sizeof(GameController));

    if (gameController == NULL) {
        perror("Error allocating memory for gameController(GameController_create)");
        exit(EXIT_FAILURE);
    }

    gameController->A = Player_create('A',HUMAN);

    gameController->B = Player_create('B',playerType);
    
    gameController->current = gameController->A;
    gameController->result = PLAYING;
    gameController->turn = 0;
    gameController->state = PLAY_HUMAN;
    
    gameController->board = Board_create();
    gameController->snapshots = NULL;

    gameController->snapshots = Snapshots_create(gameController->board,gameController->current,
        gameController->turn,gameController->result);

    ++gameController->turn;
    return gameController;

}

void checkCreateError(GameController* gameController) {

    if (gameController->A == NULL || gameController->B == NULL)
        exit(EXIT_FAILURE);

    if (gameController->snapshots == NULL || gameController->board == NULL)
        exit(EXIT_FAILURE);

}

void GameController_destroy(GameController* gameController) {

    if (gameController == NULL)
        return;

    Snapshots_destroy(gameController->snapshots);
    Board_destroy(gameController->board);
    Player_destroy(gameController->A);
    Player_destroy(gameController->B);
    free(gameController);
}

void addSnapshotG(GameController * gameController){

    if (!addSnapshot(&gameController->snapshots, gameController->board, gameController->current,
        gameController->turn,gameController->result))
        fprintf(stderr, "Error adding snapshot\n");
}

bool saveSnapshotG(GameController* gameController, char* filename) {

    return saveSnapshotAsString(gameController->snapshots, filename);
}

bool PlayRockG(GameController* gameController, short nColumn,short nRow) {

    if (!isValidPlayRock(gameController->board, nColumn, nRow) || !playRock(gameController->current))
        return false;

    if (!playRockB(gameController->board, nColumn, nRow))
        return false;

    endTurn(gameController);
    return true;
}

void playPieceHumanG(GameController * gameController,short nColumn, short nRow,char piece){

    if(PlayPiece(gameController->board,nColumn,nRow,piece) == WON){

        gameController->state = GAME_OVER;
        gameController->result = WIN;
        addSnapshotG(gameController);
        return;
    }
 
    endTurn(gameController);   
}

State getState(GameController * GameController){

    return GameController->state;
}

void playVirtualG(GameController* gameController) {

    short ret = playVirtualP(gameController->current, gameController->board);
   if(ret == WON){
       gameController->state = GAME_OVER;
       gameController->result = WIN;
       return;
    }
    if (ret == false)
        return;
    endTurn(gameController);

}

void endTurn(GameController * gameController){

    addSnapshotG(gameController);   
    switchPlayer(gameController);
    ++(gameController->turn);

    if (!existsValidPlay(gameController))
    {
        gameController->state = GAME_OVER;
        gameController->result = TIE;

    }
}

bool increaseColumnG(GameController * gameController){

    if (IncreaseBoardP(gameController->current)) {
        
        increaseBoardNColumns(gameController->board);
        endTurn(gameController);
        return true;

    }
    return false;

}

bool increaseRowG(GameController * gameController){

    if (IncreaseBoardP(gameController->current)) {
        
        increaseBoardNRows(gameController->board);
        endTurn(gameController);
        return true;
    }
    return false;
    
}

bool existsValidPlay(GameController * gameController){

    unsigned short maxCols = getNCols(gameController->board);

    unsigned short maxRows = getNRows(gameController->board);

    for( unsigned short i = 0;i < maxCols; ++i)
        for( unsigned short j = 0;i < maxRows; ++j) 
            if(getValidPlay(getPieceByPos(gameController->board,i,j), gameController->current)!= NO_VALID_PLAY)
                return true;

   return false; 


}

bool isValidPlayG(GameController * gameController, short nColumn, short nRow, char piece){

    return isValidPlay(gameController->board,nColumn,nRow,piece);

}

short getCurrentPlayerType(const GameController * gameController){

    return getPlayerType(gameController->current);
}

void switchPlayer(GameController * gameController){

    if(gameController->A == gameController->current)
        gameController->current = gameController->B;
    else
        gameController->current = gameController->A;

    gameController->state = getPlayerType(gameController->current) == HUMAN ? PLAY_HUMAN : PLAY_VIRTUAL;

}

char * getWinner(const GameController * gameController){
   
    return gameController->result == WIN ? printPlayer(gameController->current) : NULL;
}

unsigned short getTurn(GameController* gameController) {
    return gameController->turn;
}

char* printGameController(const GameController* gameController) {

    static char buffer[MAX_CONTROLLER_CHARS];
    buffer[0] = '\0';
    size_t size = sizeof(buffer) - strlen(buffer) - 1;

    if (sprintf_s(buffer, size, "%sTurn: %hd\n"
        , printBoard(gameController->board), gameController->turn) == -1) {
        perror("Error copying to buffer (printGameController)");
        return NULL;
    }

    size = sizeof(buffer) - strlen(buffer) - 1;


    switch (gameController->result) {

    case TIE:
        if (sprintf_s(buffer + strlen(buffer), size, "Tie: ") == -1)
        {
            perror("Error copying to buffer (printGameController)");
            return NULL;
        }
        break;
    
    case WIN:
        if (sprintf_s(buffer + strlen(buffer), size, "Winner: ") == -1)
        {
            perror("Error copying to buffer (printGameController)");
            return NULL;
        }
        break;
    case PLAYING:

        if (sprintf_s(buffer + strlen(buffer), size, "Current player: ") == -1)
        {
            perror("Error copying to buffer (printGameController)");
            return NULL;
        }
        break;
    }
    
    size = sizeof(buffer) - strlen(buffer) - 1;

    if (sprintf_s(buffer + strlen(buffer),size, "%s",printPlayer(gameController->current)) == -1)
    {
        perror("Error copying to buffer (printGameController)");
        return NULL;
    }

    return buffer;

}

char * printPreviousPlays(const GameController * gameController, short nPlays){

    return getNSnapshots(gameController->snapshots,gameController->turn - nPlays,nPlays + 1);

}

bool saveGameController(GameController* gameController, FILE** f) {

    size_t size = sizeof(gameController->turn);

    if (fwrite(&gameController->turn, size, 1, *f) != 1)
    {
        perror("Error writing turn to file (saveGameController)");
        return false;
    }

    size = sizeof(gameController->result);
    if (fwrite(&gameController->result, size, 1, *f) != 1)
    {
        perror("Error writing turn to file (saveGameController)");
        return false;
    }


    if (!SavePlayer(f, gameController->A))
    {
        perror("Error writing player A to file (saveGameController)");
        return false;
    }

    if (!SavePlayer(f, gameController->B))
    {
        perror("Error writing player A to file (saveGameController)");
        return false;
    }

    if(gameController->current == gameController->A)
    {
        if (fwrite("A",1, 1, *f) != 1)
        {
            perror("Error writing current player to file (saveGameController)");
            return false;
        }
    }
    else
        if (fwrite("B", 1, 1, *f) != 1)
        {
            perror("Error writing current player to file (saveGameController)");
            return false;
        }

    size = sizeof(State);
    if (fwrite(&gameController->state, size, 1, *f) != 1)
    {
        perror("Error writing current State to file (saveGameController)");
        return false;
    }

    if(!saveBoard(f,gameController->board))
    {
        perror("Error writing board to file (saveGameController)");
        return false;
    }
    
    if(!saveSnapshots(f, gameController->snapshots))
    {
        perror("Error writing snapshots to file (saveGameController)");
        return false;
    }
    return true;
}

GameController* loadGameController( FILE** f) {

    GameController* gameController = (GameController*) malloc(sizeof(GameController));

    if (gameController == NULL) {
        perror("Error allocating memory for gameController(loadGameController)");
        return NULL;
    }

    char aux;
    size_t size = sizeof(gameController->turn);

    if (fread(&gameController->turn, size, 1, *f) != 1 && ferror(*f))
    {
        perror("Error reading turn from file (saveGameController)");
        return NULL;
    }
    if (feof(*f))
    {
        fprintf(stderr, "file ended sooner than expected\n");
        return NULL;
    }

    size = sizeof(gameController->result);
    if (fread(&gameController->result, size, 1, *f) != 1)
    {
        perror("Error reading result from file (saveGameController)");
        return NULL;
    }

    if (feof(*f))
    {
        fprintf(stderr, "file ended sooner than expected\n");
        return NULL;
    }
    
    if ((gameController->A = LoadPlayer(f)) == NULL)
    {
        perror("Error reading player A from file (saveGameController)");
        return NULL;
    }

    if (feof(*f))
    {
        fprintf(stderr, "file ended sooner than expected\n");
        return NULL;
    }

    if ((gameController->B = LoadPlayer(f)) == NULL)
    {
        perror("Error reading player B from file (saveGameController)");
        return NULL;
    }

    if (feof(*f))
    {
        fprintf(stderr, "file ended sooner than expected\n");
        return NULL;
    }

 
    if (fread(&aux, 1, 1, *f) != 1 && ferror(*f))
    {
        perror("Error reading current player  indicator from file (saveGameController)");
        return NULL;
    }
     
    if (feof(*f))
    {
        fprintf(stderr, "file ended sooner than expected\n");
        return NULL;
    }

    if (aux == 'A')
        gameController->current = gameController->A;
    else if ( aux == 'B')
        gameController->current = gameController->B;
    else
    {
        fprintf(stderr, "Error reading current player: not specified in file(saveGameController)\n");
        return NULL;
    }


    size = sizeof(State);
    if (fread(&gameController->state, size, 1, *f) != 1 && ferror(*f))
    {
        perror("Error reading current State from file (saveGameController)");
        return NULL;
    }

    if (feof(*f))
    {
        fprintf(stderr, "file ended sooner than expected\n");
        return NULL;
    }
    
    if ((gameController->board = loadBoard(f)) == NULL)
    {
        perror("Error reading board from file (saveGameController)");
        return NULL;
    }

    if (feof(*f))
    {
        fprintf(stderr, "file ended sooner than expected\n");
        return NULL;
    }
    ;
    if ((gameController->snapshots = loadSnapshots(f, gameController->turn)) == NULL)
    {
        perror("Error reading snapshots from file (saveGameController)");
        return NULL;
    }
    return gameController;
}