// João Silva nº 2019134449 - Engenharia Informática - I.S.E.C - 2021

#ifndef BOARD
#define BOARD

#include "utils.h"
#include <ctype.h>

#define MIN_ROWS_INIT 3
#define MAX_ROWS_INIT 5
#define MAX_BOARD_CHARS 800
#define MAX_ROWS MAX_COLS
#define MAX_COLS 7
#define INITIALIZER ' '

#define VALID_PLAY 2
#define WON 3
#define INVALID_PLAY (-1)

typedef struct Board Board;

Board* Board_create();

bool checkWin(Board * board );

char getPieceByPos(Board* board, unsigned short row, unsigned short col);

unsigned short getNRows(Board* board);

unsigned short getNCols(Board* board);

void allocBoard(Board* board);

Board* copyBoard(const Board* orig);

void Board_destroy(Board* board);

bool playRockB(Board* board, short nColumn, short nRow);

bool isValidPlayRock(Board* board, short nColumn, short nRow);

void freeFailedBoard(Board* board, short i);

bool saveBoard(FILE** f, Board* board);

Board * loadBoard(FILE** f);

short PlayPiece(Board* board, short nColumn, short nRow, char piece);

bool isValidPlay(Board* board, short nColumn, short nRow, char piece);

bool increaseBoardNColumns(Board* board);

bool increaseBoardNRows(Board* board);

char * printBoard(Board* board);





#endif 