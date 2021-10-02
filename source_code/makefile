# João Silva nº 2019134449 - Engenharia Informática - I.S.E.C - 2021
OBJ=$(wildcard *.o)


main: main.o Board.o utils.o Player.o Snapshot.o GameController.o SaveGame.o Interface.o
	gcc main.o Board.o utils.o Snapshot.o Player.o GameController.o SaveGame.o Interface.o -std=c99 -Wall -Wextra  -pedantic -o  main	


main.o: main.c
	gcc main.c -c -std=c99 -Wall -Wextra  -pedantic

Interface.o: Interface.c  Interface.h 
	gcc   Interface.c   -c -std=c99 -Wall -Wextra  -pedantic


Board.o: Board.c  Board.h 
	gcc   Board.c   -c -std=c99 -Wall -Wextra  -pedantic

utils.o: utils.c  utils.h 
	gcc  utils.c   -c -std=c99  -Wall -Wextra  -pedantic

Snapshot.o: Snapshot.c  Snapshot.h 
	gcc   Snapshot.c   -c -std=c99 -Wall -Wextra  -pedantic

Player.o: Player.c  Player.h 
	gcc  Player.c   -c -std=c99  -Wall -Wextra  -pedantic

GameController.o: GameController.c  GameController.h 
	gcc  GameController.c   -c -std=c99  -Wall -Wextra  -pedantic	

SaveGame.o: SaveGame.c  SaveGame.h 
	gcc  SaveGame.c   -c -std=c99  -Wall -Wextra  -pedantic


#clean
clean:
	rm $(OBJ) 
