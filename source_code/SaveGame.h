// João Silva nº 2019134449 - Engenharia Informática - I.S.E.C - 2021

#ifndef SAVEGAME
#define SAVEGAME

#include "GameController.h"
#include <errno.h>
#define SAVE_FILE_PATH "..//save//save_file.bin"




bool fileExists();

bool saveGame(GameController* GameController);

GameController* loadGame();

#endif