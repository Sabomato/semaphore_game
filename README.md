# semaphore_game
## Overview
This project is an implementation of the traditional game ["Semaphore"](http://cs.gettysburg.edu/~franpe02/TrafficLightsWeb/), in C language, with a object oriented approach.

In the original version, there is only green, yellow and red pieces. In this version, it was added a rock piece, that blocks the row, column and diagonal where it was placed, meaning the players can't win in those directions.
Each player can also increment the board twice per game, horizontally or vertically; save the state of the game (in a binary file, containing information about the players and the current/previous board states), and a snapshot of the board in each turn. 

Can be played "player vs player" or "player vs computer", but the algoritm is pretty simple, there is no A.I involved.




The implementation is divided in interface, which is text-based, and controller, the wrapping structure for all the logic.

## Implementation

- **R** - Red
- **G** - Green
- **Y** - Yellow
- **O** - Rock
## Usage
I provide two ways of testing the game:

1. Using IDE
  - Dowload the repository as _.zip_
  - Create a project with the source code, in your preferred IDE
  - Build and run the project      
2. Makefile
  - [Install MinGW](https://www.mingw-w64.org/)
  - run the command `mingw32-make` in **/source_code** (In paths with folders having empty spaces `mingw32-make` has some problems, try other path if doesn't work)
  -  run the **game.exe** executable



