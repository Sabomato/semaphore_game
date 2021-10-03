# semaphore_game
This project is an implementation of the traditional game "Semaphore", in C language, with a object oriented approach.

In the original version, there is only green, yellow and red pieces. In this version, it was added a rock piece, that blocks the row, column and diagonal where it was placed, meaning the players can't win in those directions.
Each player can also increment the board twice per game, horizontally or vertically; save the state of the game (in a binary file, containing information about the players and the current/previous board states), and a succession of states of the board in each turn. 

Can be played "player vs player" or "player vs computer", but the algoritm is pretty simple, there is no A.I involved.




The implementation is divided in interface, which is text-based, and controller, the wrapping structure for all the logic.




