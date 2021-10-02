// João Silva nº 2019134449 - Engenharia Informática - I.S.E.C - 2021

#include "Board.h"

typedef struct Board
{
    unsigned short nRows, nCols;
    char** board;

}Board;


unsigned short getNRows(Board* board) {

    return board->nRows;
}

char getPieceByPos(Board* board,unsigned short row,unsigned short col) {

    return board->board[row][col];
}

unsigned short getNCols(Board* board) {

    return board->nCols;
}

Board* Board_create(){

    Board * board = (Board*) malloc(sizeof(Board));

    if (board == NULL) {
        perror("Error allocating memory (copyBoard)");
        return NULL;
    }

    board->nCols =  board->nRows = intUniformRnd(MIN_ROWS_INIT,MAX_ROWS_INIT);
    
    allocBoard(board);
    return board;
}

Board * copyBoard(const Board* orig) {

    if (orig == NULL) {
        fprintf(stderr, "board was null (copyBoard)\n");
        return NULL;
    }

    Board* new = (Board *) malloc(sizeof(Board));
    if (new == NULL) {
        perror("Error allocating memory (copyBoard)");
        return NULL;
    }

    new->board = (char**) malloc(sizeof(char*) * MAX_ROWS);
    
    if (new->board == NULL) {

        perror("Error allocating memory (copyBoard)");
        return NULL;
    }

    new->nCols = orig->nCols;
    new->nRows = orig->nRows;

    for (short i = 0; i < MAX_ROWS; ++i) {

        new->board[i] = (char*) malloc(sizeof(char) * (MAX_COLS + 1));

        if (new->board[i] == NULL) {

            perror("Error allocating memory (copyBoard)");
            freeFailedBoard(new, i - 1);
            return NULL;
        } 
        for (short j = 0; j < MAX_COLS; ++j) {

            new->board[i][j] = orig->board[i][j];
        }
    }
    return new;

}

void allocBoard(Board* board) {

    board->board = (char**) malloc(sizeof(char*) * MAX_ROWS/* getNRows(board)*/);

    if (board->board == NULL) {

        perror("Error allocating memory (allocBoard)");
        exit(EXIT_FAILURE);
    }

    for (short i = 0; i < MAX_ROWS/*board->nCols*/; ++i) {

        board->board[i] = (char*) malloc(sizeof(char) * (MAX_COLS/*board->nCols*/ + 1));

        if (board->board[i] == NULL) {
            perror("Error allocating memory (allocBoard)");
            exit(EXIT_FAILURE);
            return;
        }

        memset(board->board[i], INITIALIZER, sizeof(char) * MAX_COLS/*board->nCols*/);
        board->board[i][MAX_COLS] = '\0';
    }

}

void freeFailedBoard(Board* board, short i) {

    for (; i >= 0; --i)
        free(board->board[i]);
    

}

short PlayPiece(Board* board, short nColumn, short nRow, char piece){

    char auxPiece = toupper(piece);
    if(!isValidPlay(board,nColumn,nRow,auxPiece))
        return INVALID_PLAY;

    board->board[nRow][nColumn] = auxPiece;
    
    if(checkWin(board))
        return WON;

    return VALID_PLAY; 

}

bool isValidPlayRock(Board* board, short nColumn, short nRow) {
    
    if (nColumn > board->nCols || nRow > board->nRows || nColumn < 0 || nRow < 0)
        return false;

    if (board->board[nRow][nColumn] == ' ')
        return true;
    return false;

}

bool playRockB(Board* board, short nColumn, short nRow) {

    if (!isValidPlayRock(board, nColumn, nRow))
        return false;
    board->board[nRow][nColumn] = 'O';
    return true;
}

bool isValidPlay(Board* board, short nColumn, short nRow, char piece){

    if( nColumn > board->nCols || nRow > board->nRows || nColumn < 0 || nRow < 0)
        return false;

    
    switch(piece){

    case 'G': 
        if(board->board[nRow][nColumn] == ' ')
            return true;
        return false;

    case 'Y':
        if(board->board[nRow][nColumn] == 'G')
            return true;    
        return false;
    
    case 'R':
        if(board->board[nRow][nColumn] == 'Y')
            return true;    
        return false;
    
      
    }
        
    return false;   
}

bool checkWin(Board * board ){
    
    static short i, j;
    static char aux;
    
    //Vertical check
    for(i = 0; i < board->nCols;++i){
        
        aux = board->board[0][i];
        if (aux == ' ')
            continue;

        for(j = 0; j < board->nRows; ++j)
            if(aux !=  board->board[j][i])
                break;
        
        if(j == board->nRows)
            return true;
    }

    //Horizontal check
    for(i = 0; i < board->nRows;++i){
        
        aux = board->board[i][0];
        if (aux == ' ')
            continue;

        for(j = 0; j < board->nCols; ++j)
            if(aux !=  board->board[i][j])
                break;


        if(j == board->nCols)// Só saiu do loop quando j == board->nCols
            return true;
    }

    if(board->nCols == board ->nRows){
        
        aux = board->board [0][0];

        if (aux != ' '){           
            for( i = 0; i < board->nCols; ++i)
                if(aux !=  board->board[i][i])
                    break;

            if( i == board->nCols)
                return true;
        }

        aux = board ->board[board->nCols - 1][0];

        if (aux != ' ') {

            for (i = board->nCols - 1, j = 0; i >= 0; --i, ++j)
                if (aux != board->board[i][j])
                    break;

            if (i == -1)
                return true;
        }
    }

    return false;

}

bool increaseBoardNRows(Board* board){

    ++(board->nRows);
    /*
    short newNRows = board->nRows + 1;
 
    char ** aux = (char **)  realloc(board->board, sizeof(char *) * newNRows);

    if(aux == NULL){
        perror("Error reallocating memory (increaseBoardNColumns)");
        return false;
    }

    board->board = aux;

    board -> board[board->nRows] = (char *) malloc(sizeof(char) * board->nCols);
          
    if(board->board[board->nRows] == NULL){
        perror("Error allocating memory (increaseBoardNRows)");
        return false;
    } 

    memset(board->board[board->nRows], INITIALIZER, sizeof(char) * board->nCols);

    
    board->nRows= newNRows;
*/
    return true;
}

bool increaseBoardNColumns(Board* board){

    ++(board->nCols);
    /*
    short i;

    short newNCols = board->nCols + 1;

    char ** aux = (char **)  malloc(sizeof(char *) * board->nRows);   

    if(aux == NULL){
        perror("Error allocating memory (increaseBoardNRows)");
        return false;
    }

    //board->board = aux;

    for(i = 0; i < board->nRows; ++i){

        aux[i] = (char *) realloc(board->board[i],sizeof(char) * newNCols);
          
        if(aux[i] == NULL){
            perror("Error reallocating memory (increaseBoardNColumns)");
       
            break;
        } 
        //printf("char:|%c|\n",aux[i][board->nRows]);
        memset(&aux[i][board->nRows], INITIALIZER, sizeof(char) * (newNCols - board->nCols) );
        //printf("char:|%c|\n",board->board[i][0]);
    }
    
    if( i != board->nRows)
    {       
        for(short j = 0; j < i; ++j)
            free(aux[j]);
        free(aux);
        
        return false;
    }
    
    board->board = aux;
    
    board->nCols = newNCols;
*/
    return true;


}

char * printBoard(Board* board){
    int n = 0;
    static char buffer[MAX_BOARD_CHARS];
    buffer[0]='\0';

    if(board == NULL)
        return NULL; 


    //n += 3;
    sprintf_s(buffer + strlen(buffer),sizeof(buffer) - strlen(buffer) - 1,"\n  ");

    for(int j = 1; j <= board->nCols; ++j/*,n+=6*/)
            sprintf_s(buffer + strlen(buffer),sizeof(buffer) - strlen(buffer) - 1,"   %d  ",j);

    sprintf_s(buffer + strlen(buffer),sizeof(buffer) - strlen(buffer) - 1,"\n  _");

    //n += 4;
    for(int j = 0; j < board->nCols; ++j/*,n+=6*/)
        sprintf_s(buffer + strlen(buffer),sizeof(buffer) - strlen(buffer) - 1,"______");

    sprintf_s(buffer + strlen(buffer),sizeof(buffer) - strlen(buffer) - 1,"\n");
    /*n += 1;*/
    for(int i = 0; i < board->nRows; ++i/*,n += 5*/){
       

        sprintf_s(buffer + strlen(buffer),sizeof(buffer),"%d |  ",i+1);
        for(int j = 0; j < board->nCols; ++j,n += 6){

            sprintf_s(buffer + strlen(buffer),sizeof(buffer) - strlen(buffer) -1,"%c  |  ",
                board->board[i][j]);
        
        }
        
        sprintf_s(buffer + strlen(buffer),sizeof(buffer) - strlen(buffer) - 1,"\n  |");
        
        n += 4;
        for(int j = 0; j < board->nCols; ++j,n += 6)
            sprintf_s(buffer + strlen(buffer),sizeof(buffer) - strlen(buffer) - 1,"_____|");
        sprintf_s(buffer + strlen(buffer),sizeof(buffer) - strlen(buffer) - 1,"\n");
        n += 1;
       
    }

    sprintf_s(buffer + strlen(buffer),sizeof(buffer) - strlen(buffer) - 1,"\n");
    
    n += 1;

    //printf("\nn=%d strlen(buffer) = %zu",n,strlen(buffer));
    //printf("%s",buffer);
    return buffer;

}

bool saveBoard(FILE** f, Board* board) {

    if (fwrite(&board->nCols, sizeof(board->nCols), 1, *f) != 1)
    {
        perror("Error writing nCols in file (saveBoard)");
        return false;
    }
    if (fwrite(&board->nRows, sizeof(board->nRows), 1, *f) != 1)
    {
        perror("Error writing nCols in file (saveBoard)");
        return false;
    }
    for (short i = 0; i < board->nRows; ++i) {

        if (fwrite(board->board[i],board->nCols, sizeof(char), *f) != 1)
        {
            perror("Error writing board in file (saveBoard)");
            return false;
        }
    }

    return true;
    
}

Board * loadBoard(FILE** f) {

    Board* board = (Board*) malloc(sizeof(Board));
    if (board == NULL) {
        perror("Error allocating memory (LoadBoard)");
        return NULL;
    }

    if (fread(&board->nCols, sizeof(board->nCols), 1, *f) != 1 && ferror(*f)) {
        perror("Error reading nCols from file (loadBoard)");
        return NULL;
    }
    if (fread(&board->nRows, sizeof(board->nRows), 1, *f) != 1 && ferror(*f)) {
        perror("Error reading nRows from file (loadBoard)");
        return NULL;
    }

    allocBoard(board);

    for (short i = 0; i < board->nRows; ++i) {

        if (fread(board->board[i], board->nCols, sizeof(char), *f) != 1)
        {
            freeFailedBoard(board, i);
            free(board);

            perror("Error reading board from file (loadBoard)");
            return NULL;
        }

    }
    return board;
}

void Board_destroy(Board* board) {

    if (board == NULL){
        fprintf(stderr, "board was null (Board_destroy)\n");
         return;
    }
    for (short j = 0; j < MAX_ROWS; ++j)
        free(board->board[j]);
    free(board);

}

