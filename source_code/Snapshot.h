// João Silva nº 2019134449 - Engenharia Informática - I.S.E.C - 2021

#ifndef SNAPSHOT
#define SNAPSHOT

#include "utils.h"
//#include "GameController.h"
#include "Player.h"
#include "Board.h"
#define MAX_SNAPSHOT_CHARS (MAX_BOARD_CHARS + MAX_PLAYER_CHARS + 28)

typedef struct Snapshot  Snapshot;



//char * printSnapshot(const Snapshot * snapshot);

bool saveSnapshotAsString(Snapshot* snapshots, char* filename);

bool saveSnapshots(FILE** f, Snapshot* snapshots);

Snapshot* loadSnapshots(FILE** f, short turns);

//Snapshot* loadSnapshot(FILE** f); Declarada como "static" no .c, para impedir outros ficheiros de a aceder

bool addSnapshot(Snapshot ** snapshots, const Board * board, const Player* player, unsigned short turn, short result);

Snapshot * Snapshots_create(const Board * board, const  Player * player, unsigned short turn, short result);

void Snapshots_destroy(Snapshot* snapshots);

char * getNSnapshots(const Snapshot * snapshots, short turn, short nSnapshots);





#endif