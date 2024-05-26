#include <stdio.h>
#include <stdlib.h>

#include "Headers/struct.h"
#include "Headers/search.h"

Position searchRobot(Box **grid, int size, int id) { // Search for robot coordinate in the grid
  if (grid == NULL) { // Verify if memory is allocated
    printf("Allocation problem");
    exit(3);
  }
    if(id<MIN_ID || id>MAX_ID){
    printf("Error : id is not between 1 and 4");
    exit(1);
  }
  if(size<MIN_GRID_SIZE || size>MAX_GRID_SIZE){
    printf("Error : grid size is not between %d and %d",MIN_GRID_SIZE,MAX_GRID_SIZE);
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
  if(numTarget<MIN_TARGET || numTarget>MAX_TARGET){
    printf("Error : numTarget is not between 1 and 18");
    exit(1);
  }
    if(size<MIN_GRID_SIZE || size>MAX_GRID_SIZE){
    printf("Error : grid size is not between %d and %d",MIN_GRID_SIZE,MAX_GRID_SIZE);
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
