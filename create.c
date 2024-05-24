#include <stdio.h>
#include <stdlib.h>

#include "Headers/create.h"

// Player creator
Player createPlayer(int id) {
  Player player;
  player.id = id;
  player.score = 0;
  return player;
}

// Robot creator
Robot createRobot() {
  Robot robot;
  robot.id = 0;
  robot.position.x = -1;
  robot.position.y = -1;
  return robot;
}

// Wall creator
Wall createWall(int type) {
  Wall wall;
  wall.type = type;
  return wall;
}

// Box creator
Box createBox(int type, int x, int y) {
  Box box;
  box.position.x = x;
  box.position.y = y;
  box.robot = createRobot();
  box.target = 0;
  box.wall = createWall(type);
  box.angle = 0;
  return box;
}

// Grid creator
Box **createGrid(int size) {
  Box **grid = malloc(size * sizeof(Box *)); // Allocate memory for the grid 
  if (grid == NULL) { // Verify if memory has been allocated
    printf("Error: grid malloc failed #1\n");
    exit(1);
  }
  for (int i = 0; i < size; i++) {
    grid[i] = malloc(size * sizeof(Box)); // Allocate memory of each line
    if (grid[i] == NULL) { // Verify if memory has been allocated for each line
      for (int k = 0; k < size; k++) { // Loop to free each array line if an error occurs
        free(grid[k]);
      }
      printf("Error: grid malloc failed #2\n");
      free(grid);
      exit(1);
    }
  }
  return grid;
}

// Player board creator
Player *createPlayerBoard(int nbPlayers, int size) {
  if(nbPlayers<2 || nbPlayers>6){
    exit(1);
  }
  Player *playerBoard = malloc(nbPlayers * sizeof(Player)); // Allocate memory for player board
  if (playerBoard == NULL) { // Verify if memory has been allocated
    printf("Error: grid malloc failed #3\n");
    exit(1);
  }
  for (int i = 0; i < nbPlayers; i++) {
    playerBoard[i] = createPlayer(i + 1); // Create players with id starting from 1
  }
  return playerBoard;
}