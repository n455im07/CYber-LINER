#include <stdio.h>
#include <stdlib.h>

#include "Headers/struct.h"
#include "Headers/search.h"

int isValid(Position position, Box **grid, int type, int type2) {
  if (grid == NULL) {
    printf("Allocation failed");
    exit(6);
  }
  int x = position.x;
  int y = position.y;
  if (grid[x][y].robot.id == 0 &&
      (grid[x][y].wall.type != type || grid[x][y].wall.type != type2)) {
    return 1;
  }
  return 0;
}

Position searchRobot(Box **grid, int size, int id) { // Search for robot coordinate in the grid
  if (grid == NULL) { // Verify if memory is allocated
    printf("Allocation problem");
    exit(3);
  }
  if(id<1 || id>4){
    exit(1);
  }
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (grid[i][j].robot.id == id) 
        return grid[i][j].position; // Return the (i,j) coordinates of the robot
    }
  }
  return (Position){-1, -1}; // Return (-1,-1) if robot not found
}

Position searchTarget(Box **grid, int size, int numTarget) { // Search for target coordinate in the grid
  if (grid == NULL) { // Verify if memory is allocated
    printf("Allocation problem");
    exit(3);
  }
  if(numTarget<1 || numTarget>18){
    exit(1);
  }
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (grid[i][j].target == numTarget)
        return grid[i][j].position; // Return the (i,j) coordinates of the target
    }
  }
  return (Position){-1, -1}; // Return (-1,-1) if target not found
}

int searchDistance(Box **grid, int size, Position posRobot, int direction) { // Search for distance between robot and next obstacle
  if (grid == NULL) { // Verify if memory is allocated
    printf("Allocation failed");
    exit(7);
  }
  if(posRobot.x<0 || posRobot.x>size-1){
    exit(1);
  }
  if(direction != 'z' && direction != 'q' && direction != 's' && direction != 'd'){
    exit(1);
  }
  int distance = 0;
  switch (direction) { // Check if the next box is valid depending on the direction
  case 'z':
    for (int i = 0; i < posRobot.x; i++) {
      if (isValid(grid[posRobot.x - i][posRobot.y].position, grid, 4, 1)) { 
        distance++; // Add one to distance if robot can go ot next box 
      }
    }
    break;
  case 'q':
    for (int i = 0; i < posRobot.y; i++) {
      if (isValid(grid[posRobot.x][posRobot.y - i].position, grid, 2, 3)) {
        distance++; // Add one to distance if robot can go ot next box 
      }
    }
    break;
  case 'd':
    for (int i = 0; i < size - posRobot.y; i++) {
      if (isValid(grid[posRobot.x][posRobot.y + i].position, grid, 3, 2)) {
        distance++; // Add one to distance if robot can go ot next box 
      }
    }
    break;
  case 's':
    for (int i = 0; i < size - posRobot.x; i++) {
      if (isValid(grid[posRobot.x + i][posRobot.y].position, grid, 1, 4)) {
        distance++; // Add one to distance if robot can go ot next box 
      }
    }
  }
  printf("\x1B[30m\n DISTANCE %d\n", distance);
  return distance;
}