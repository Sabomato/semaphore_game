// João Silva nº 2019134449 - Engenharia Informática - I.S.E.C - 2021

#include "Interface.h" 


void run(GameController * gameController){


    do{

        if (checkPreviousGameFile()) {
            if ((gameController = loadGame(gameController)) == NULL)
            {
                fprintf(stderr, "Error loading game file. New game started\n");
                wantsVirtualAdversary(&gameController);
            }
        }            
        else
            wantsVirtualAdversary(&gameController);

        while(PlayGame(gameController));

        askFileName(gameController);

        puts("Do you want to play again?");
   
    } while(getYesOrNoAnswer());


}

bool PlayGame(GameController * gameController){

    printf("%s",printGameController(gameController));

    switch (getState(gameController))
    {
    case PLAY_HUMAN:
        return PlayHuman(gameController);
   
    case PLAY_VIRTUAL:
        playVirtualG(gameController);
        break;
    case GAME_OVER:

        return false;
    }
    return true;

}

bool PlayHuman(GameController * gameController){

    static short nColumn, nRow;
    static char piece;
    static short answer;

    do{
        printf("\nPlay a Piece(%d)\nWatch previous plays(%d)\n",PLAY_PIECE_HUMAN,WATCH_PREVIOUS);
        printf("Increase board(%d)\nPlay Rock(%d)\nLeave(%d)\n",INC_BOARD_HUMAN,PLAY_ROCK_HUMAN,LEAVE);
        
        answer = getAnswerBetweenXandY(PLAY_PIECE_HUMAN,LEAVE);

    }while(answer == -1);
        
    switch(answer){

    case PLAY_PIECE_HUMAN:

        if(getPieceToPlay( gameController,&nColumn,&nRow,& piece))
            playPieceHumanG(gameController,nColumn,nRow,piece);

        break;

    case WATCH_PREVIOUS:

        answer = getAnswerBetweenXandY(1,getTurn(gameController));

        if(answer == -1)
            break;
        printf("answer:%d", answer);
        char * aux = printPreviousPlays(gameController,answer);
        printf("%s",aux == NULL ? "No plays available\n":aux);

        free(aux);

        break;
    
    case INC_BOARD_HUMAN:
        printf("Increase Rows(%d)\nIncrease Columns(%d)\n",ROWS,COLUMNS);
        answer = getAnswerBetweenXandY(0,1);

        if(answer == -1)
            break;

        if(answer == ROWS){
            if(!increaseRowG(gameController))
                puts("You don't have more BoardIncreases");   
            
        }
        else if( answer == COLUMNS)
            if(!increaseColumnG(gameController))
                puts("You don't have more BoardIncreases");               
        
        break;

    case PLAY_ROCK_HUMAN:
        if (!getPositionToPlay( &nColumn, &nRow))
            break;

        if (!PlayRockG(gameController, nColumn, nRow))
            printf("Invalid Play\n"); 
       
        break;

    case LEAVE:
        saveGame(gameController);
        
        return false;

    }          
    
    return true;   

      
}

bool getPositionToPlay( short* nColumn, short* nRow) {

    puts("Where do you wanna play?");

    printf("\nColumn:");
    scanf("%hd", nColumn);


    printf("\nnRow:");
    scanf("%hd", nRow);
    


    if (!cleanStdin()) {
        puts("Invalid position.");
        return false;
    }   
        

    --(*nColumn);
    --(*nRow);
    return true;

}

bool getPieceToPlay(GameController* gameController,short* nColumn,short* nRow,char* piece){

    if(!getPositionToPlay(nColumn, nRow))
        return false;

    printf("\npiece:"); 

    scanf("%c",piece);

    *piece = toupper(*piece);
    
    if(isValidPlayG(gameController,*nColumn,*nRow,*piece) && cleanStdin())
        return true;

    puts("Invalid play. Try again");
    return false;
    
}

bool checkPreviousGameFile(){

    if(fileExists() == false){
        puts("No previous game file save found.\n Starting new save file");
        return false;
    }

    puts("Previous game file save found.\n Do you want to load it?");
          
    return getYesOrNoAnswer();
            
}

void wantsVirtualAdversary(GameController ** gameController){

    puts("Do you want to play against a virtual player?");

    short playerType;
    if(getYesOrNoAnswer())
        playerType = VIRTUAL;
    else
        playerType = HUMAN;

    if ((*gameController = GameController_create(playerType)) == NULL) {

        fprintf(stderr, "Error initializing GameController\n");
        exit(EXIT_FAILURE);
    }
    

}

void askFileName(GameController* gameController) {

    static char fileName[STATE_NAME_SIZE + 4 + 30] = STATES_SAVE_PATH;
    
    printf("State sucession file name(max %d charac.):",STATE_NAME_SIZE);
    scanf("%24s", fileName + strlen(fileName));
    strcpy_s(fileName + strlen(fileName), STATE_NAME_SIZE + 4, ".txt");
    cleanStdin();

    if (!saveSnapshotG(gameController, fileName))
        fprintf(stderr, "Error saving game states in file.\n");

    GameController_destroy(gameController);

}

bool getYesOrNoAnswer(){

    static short answer;

    answer = -1;  
    while(1){  

        puts("Yes(1)\nNo (0)"); 
        putchar('>');   
        scanf("%hd",&answer);

        if( cleanStdin() == true && (answer == 1 || answer == 0))
            break;

        //printf("answer:%d\n",answer);    
        puts("Wrong answer.");
        

    }
    return answer;    
}

short getAnswerBetweenXandY(short x, short y){

    static short answer;

    answer = -1;  
    putchar('>');          
    scanf("%hd",&answer);

    if(cleanStdin() == true && (answer >= x && answer <= y))
        return answer;
     puts("Invalid answer.");   
    return -1;    
}

bool cleanStdin()
{
	static char c;
	
	if(getchar()=='\n')
		return true;
	while((c = getchar()) != '\n' && c != EOF);
	return false;

}

