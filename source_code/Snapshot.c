// João Silva nº 2019134449 - Engenharia Informática - I.S.E.C - 2021
#include "Snapshot.h"

typedef struct Snapshot {

    unsigned short turn;
    short result;
    Board* b;
    Player* p;
    Snapshot* pNext;

}Snapshot;

Snapshot * Snapshots_create(const Board* board, const  Player* player, unsigned short turn,short result){

    Snapshot* snapshots = NULL;
    
    
    return addSnapshot(&snapshots, board, player, turn, result) ? snapshots : NULL;

}

void Snapshots_destroy(Snapshot* snapshots) {

    if (snapshots == NULL)
        return;

    Snapshot* current = snapshots;
    Snapshot* next = NULL;

    while (current != NULL) {
        next = current->pNext;
        
        Board_destroy(current->b);
        Player_destroy(current->p);
        free(current);
        current = next;
        

    } 
}

bool addSnapshot(Snapshot ** snapshots, const Board * board,const Player* player,unsigned short turn,short result){

    Snapshot* aux = (Snapshot*) malloc(sizeof(Snapshot));
    Snapshot* iterator = *snapshots;
    
    if(aux == NULL){
        perror("Error allocating memory (addSnapshot)");
        return false;
    }
    
    if ((aux->b = copyBoard(board)) == NULL)
    {
        free(aux);
        return false;
    }

    if ((aux->p = copyPlayer(player)) == NULL)
    {
        Board_destroy(aux->b);
        free(aux);
        return false;
    }

    aux->turn = turn;
    aux->result = result;
    aux->pNext = NULL;
    
    if (*snapshots == NULL) {
        (*snapshots) = aux;       
        aux->pNext = NULL;
        return true;
    }
 
    while (iterator->pNext != NULL) 
        iterator = iterator->pNext;
   
    
    iterator->pNext = aux;
    
    return true;
    
}

static char* printSnapshot(const Snapshot* snapshot) {

    if (snapshot == NULL)
        return NULL;

    static char buffer[MAX_SNAPSHOT_CHARS];
    buffer[0] = '\0';


    size_t size = sizeof(buffer) - strlen(buffer) - 1;

    if (sprintf_s(buffer, size, "%sTurn: %d\n"
        , printBoard(snapshot->b), snapshot->turn) == -1) {
        perror("Error copying to buffer (printSnapshot)");
        return NULL;
    }

    size = sizeof(buffer) - strlen(buffer) - 1;


    switch (snapshot->result) {

    case TIE:
        if (sprintf_s(buffer + strlen(buffer), size, "Tie: ") == -1)
        {
            perror("Error copying to buffer (printSnapshot)");
            return NULL;
        }
        break;

    case WIN:
        if (sprintf_s(buffer + strlen(buffer), size, "Winner: ") == -1)
        {
            perror("Error copying to buffer (printSnapshot)");
            return NULL;
        }
        break;
    case PLAYING:

        if (sprintf_s(buffer + strlen(buffer), size, "Current player: ") == -1)
        {
            perror("Error copying to buffer (printSnapshot)");
            return NULL;
        }
        break;
    }

    size = sizeof(buffer) - strlen(buffer) - 1;

    if (sprintf_s(buffer + strlen(buffer), size, "%s ", printPlayer(snapshot->p)) == -1)
    {
        perror("Error copying to buffer (printSnapshot)");
        return NULL;
    }

    return buffer;
}

bool saveSnapshotAsString(Snapshot * snapshots,char*  filename){

    if(snapshots == NULL)
        return false;

    FILE * f = fopen(filename, "w");

    if(f == NULL){
        perror("Error saving game info in text file(saveSnapshotAsString(fopen))");
        return false;
    }
   
    do{
        fprintf(f,"%s",printSnapshot(snapshots));

        snapshots = snapshots->pNext;
        
    }while(snapshots!= NULL);
    
    fclose(f);
    return true;

}

static Snapshot* loadSnapshot(FILE** f) {

    Snapshot* snapshot = (Snapshot*)malloc(sizeof(Snapshot));
    if (snapshot == NULL)
    {
        perror("Error allocating memory to save snapshot (loadSnapshot)");
        return NULL;
    }
    snapshot->pNext = NULL;
    size_t size = sizeof(snapshot->turn);

    if (fread(&snapshot->turn, size, 1, *f) != 1 && ferror(*f))
    {
        perror("Error reading turn in file (loadSnapshot)");
        return NULL;
    }

    size = sizeof(snapshot->result);
    if (fread(&snapshot->result, size, 1, *f) != 1 && ferror(*f))
    {
        perror("Error reading turn in file (loadSnapshot)");
        return NULL;
    }

    ;
    if ((snapshot->b = loadBoard(f)) == NULL)
    {
        perror("Error reading board in file (loadSnapshot)");
        return NULL;
    }


    if ((snapshot->p = LoadPlayer(f)) == NULL)
    {
        perror("Error reading Player in file (loadSnapshot)");
        return NULL;
    }

    return snapshot;
}

Snapshot* loadSnapshots(FILE** f, short turns) {

    Snapshot * snapshots = (Snapshot*) malloc(sizeof(Snapshot));
 
    if (snapshots == NULL)
    {
        perror("Error allocating memory to save snapshots (loadSnapshots)");
        return NULL;
    }

    if ((snapshots = loadSnapshot(f)) == NULL)
    {
        Snapshots_destroy(snapshots);
        return NULL;
    }

    Snapshot* iterator = snapshots;
    
   
    for (short i = 1; i < turns ; ++i)
    {
              
        iterator->pNext = loadSnapshot(f);
        if (iterator->pNext == NULL)
        {
            perror("Error allocating memory to save snapshots (loadSnapshots)");
            Snapshots_destroy(snapshots);
            return NULL;
        }

        if (feof(*f))
        {
            fprintf(stderr, "file ended sooner than expected\n");
            Snapshots_destroy(snapshots);
            return NULL;
        }
        iterator = iterator->pNext;
        
    }

    iterator->pNext = NULL;

    return snapshots;

}

bool saveSnapshots(FILE** f, Snapshot* snapshots) {

    if (snapshots == NULL)
        return true;
    size_t size;
   
    while (snapshots != NULL) {

        size = sizeof(snapshots->turn);
        if(fwrite(&snapshots->turn,size,1,*f)!= 1)
        {
            perror("Error writing turn in file (saveSnapshots)");
            return false;
        }

        size = sizeof(snapshots->result);
        if (fwrite(&snapshots->result, size, 1, *f) != 1)
        {
            perror("Error writing turn in file (saveSnapshots)");
            return false;
        }

        if (!saveBoard(f,snapshots->b))
        {
            perror("Error writing board in file (saveSnapshots)");
            return false;
        }

        if (!SavePlayer(f,snapshots->p))
        {
            perror("Error writing player in file (saveSnapshots)");
            return false;
        }

        snapshots = snapshots->pNext;
    } 

    return true;

}

char * getNSnapshots(const Snapshot * snapshots,short turn,short nSnapshots){

    if (snapshots == NULL)
        return NULL;

    size_t size = MAX_SNAPSHOT_CHARS * nSnapshots,sizeLeft;

    char * buffer = (char*) malloc(size);
    if (buffer == NULL) {
        perror("Error allocating memory to print snapshots(getNSnapshots)");
        return NULL;
    }


    buffer[0] = '\0';
    while (snapshots != NULL){
        if (snapshots->turn == turn)
            break;
        snapshots = snapshots->pNext;
    }
    

    if (snapshots == NULL)
        return NULL;
    while (snapshots != NULL) {
        sizeLeft = size - strlen(buffer);
        
        if (sprintf_s(buffer + strlen(buffer),sizeLeft , "%s",printSnapshot(snapshots)) == -1){
            perror("Error copying between buffers (printSnapshot)");
            return NULL;
        }
        snapshots = snapshots->pNext;

    };

    return buffer;
}