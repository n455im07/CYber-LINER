#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "create.h"
#include "display.h"

void displayRobot(int id) { // Display robots colors depending on their id
  if (id < 1 || id > 4) {
    exit(1);
  }
  switch (id) {
  case 1:
    printf("\033[1;31m ⚇ "); // Red
    break;
  case 2:
    printf("\033[1;32m ⚇ "); //  Green
    break;
  case 3:
    printf("\033[1;33m ⚇ "); // Yellow
    break;
  case 4:
    printf("\033[1;35m ⚇ "); // Pink
    break;
  default:
    break;
  }
}

void displayColor(int id) { // Change the colors depending of the robot id
  if (id < 1 || id > 4) {
    exit(1);
  }
  switch (id) {
  case 1:
    printf("\x1B[31m");
    break;
  case 2:
    printf("\x1B[32m");
    break;
  case 3:
    printf("\x1B[33m");
    break;
  case 4:
    printf("\x1B[35m");
    break;
  default:
    printf("\x1B[37m");
    break;
  }
}

void displayTarget(int target) { // Display the target depending on it's number
  if (target < 1 || target > 18) {
    exit(1);
  }
  printf("\033[1;97m"); // Sets the color to dark white
  switch (target) {
  case 1:
    printf(" ⑴ ");
    break;
  case 2:
    printf(" ⑵ ");
    break;
  case 3:
    printf(" ⑶ ");
    break;
  case 4:
    printf(" ⑷ ");
    break;
  case 5:
    printf(" ⑸ ");
    break;
  case 6:
    printf(" ⑹ ");
    break;
  case 7:
    printf(" ⑺ ");
    break;
  case 8:
    printf(" ⑻ ");
    break;
  case 9:
    printf(" ⑼ ");
    break;
  case 10:
    printf(" ⑽ ");
    break;
  case 11:
    printf(" ⑾ ");
    break;
  case 12:
    printf(" ⑿ ");
    break;
  case 13:
    printf(" ⒀ ");
    break;
  case 14:
    printf(" ⒁ ");
    break;
  case 15:
    printf(" ⒂ ");
    break;
  case 16:
    printf(" ⒃ ");
    break;
  case 17:
    printf(" ⒄ ");
    break;
  case 18:
    printf(" ⒅ ");
    break;
  default:
    break;
  }
  printf("\x1B[0m");
}

void displayOccupiedWall(
    Box **grid, int x,
    int y) { // Display wall occupied by a robot depending on wall type
  if (grid == NULL) {
    free(grid);
    exit(1);
  }

  displayColor(
      grid[x][y].robot.id); // Change the color depending on the robot id
  switch (grid[x][y].wall.type) {
  case 1:
    printf("▁⚇▁");
    break;
  case 2:
    printf(" ▏⚇");
    break;
  case 3:
    printf("⚇▕ ");
    break;
  case 4:
    printf("▔⚇▔");
    break;
  default:
    break;
  }
}

void displayWall(Box **grid, int x,
                 int y) { // Display wall depending on wall type
  if (grid == NULL) {
    free(grid);
    exit(1);
  }

  printf("\x1B[34m"); // Sets the color to blue
  switch (grid[x][y].wall.type) {
  case 1:
    printf("▁▁▁");
    break;
  case 2:
    printf(" ▏ ");
    break;
  case 3:
    printf(" ▕ ");
    break;
  case 4:
    printf("▔▔▔");
    break;
  default:
    break;
  }
  printf("\x1B[0m");
}

int convertGrid(Box **grid, int size) {
  int fullSize = size * 2 + 1 ;
  int **prtGrid = malloc(fullSize * sizeof(int *));
  for (int k = 0; k < fullSize; k++) {
    prtGrid[k] = calloc(fullSize, sizeof(int));
  }
  for (int i = 0; i < fullSize; i++) {
    for (int j = 0; j < fullSize; j++) {
      if ((i == 2 && j<fullSize-3 && j>2)|| (j == 2 && i>2 && i<fullSize-3) || (i == fullSize - 3 && j<fullSize-3 && j>2) || (j == fullSize - 3 && i<fullSize-3 && i>2))  {
        prtGrid[i][j] = 1;
      }
    }
  }
  int rbCount = 4;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if(grid[i][j].wall.type!=0 && i==1 && j!= 0 && j!= size -2){
        prtGrid[2*i+1][j*2+1]=1;
      }
      if(grid[i][j].wall.type!=0 && i ==size-2 && j!= 0 && j!= size -2 ){
        prtGrid[2*i+1][j*2]=1;
        
      }
      if(grid[i][j].wall.type!=0 && j==1 && i!= 0 && i!=size-2) {
        prtGrid[2*i+1][j*2+1]=1;
        
      }
      if(grid[i][j].wall.type!=0 && j==size-2 && i!= 0 && i!=size-2) {
        prtGrid[2*i+1][j*2+1]=1;
  
      }
      if (grid[i][j].target != 0 && grid[i][j].robot.id == 0) { //TARGET WALLS
        prtGrid[i * 2 + 1][j * 2 + 1] = 2;
        switch (grid[i][j].angle) {
        case 1:
          prtGrid[i * 2][j * 2 + 1] = 3;
          prtGrid[i * 2 + 1][j * 2] = 3;
          prtGrid[i * 2][j * 2] = 3;
          break;
        case 2:
          prtGrid[i * 2][j * 2 + 1] = 3;
          prtGrid[i * 2 + 1][j * 2 + 2] = 3;
          prtGrid[i * 2][j * 2 + 2] = 3;
          break;
        case 3:
          prtGrid[i * 2 + 1][j * 2 + 2] = 3;
          prtGrid[i * 2 + 2][j * 2 + 1] = 3;
          prtGrid[i * 2 + 2][j * 2 + 2] = 3;
          break;
        case 4:
          prtGrid[i * 2 + 1][j * 2] = 3;
          prtGrid[i * 2 + 2][j * 2 + 1] = 3;
          prtGrid[i * 2 + 2][j * 2] = 3;
          break;
        }
      }

      if (grid[i][j].robot.id != 0) { // ROBOTS
        switch (grid[i][j].robot.id) {
        case 1:
          prtGrid[i * 2 + 1][j * 2 + 1] = 4;
          break;
        case 2:
          prtGrid[i * 2 + 1][j * 2 + 1] = 5;
          break;
        case 3:
          prtGrid[i * 2 + 1][j * 2 + 1] = 6;
          break;
        case 4:
          prtGrid[i * 2 + 1][j * 2 + 1] = 7;
          break;
        }
      }
    }
  }
  for (int i = 0; i < fullSize; i++) {
    for (int j = 0; j < fullSize; j++) {
      switch (prtGrid[i][j]) {
      case 0:
        printf("  ");
        break;
      case 1:
        printf("🟫");
        break;
      case 2:
        printf("🟥");
        break;
      case 3:
        printf("⬜");
        break;
      case 4:
        printf("🎃");
        break;
      case 5:
        printf("🤖");
        break;
      case 6:
        printf("👻");
        break;
      case 7:
        printf("👽");
        break;
      }
    }
    printf("\n");
  }
  return 0;
}

void displayGrid(Box **grid, int size) {
  convertGrid(grid, size);
  printf("\n\n");
  // Display the whole grid
  if (grid == NULL) { // Verify if memory is allocated
    printf("Allocation failed");
    exit(1);
  }
  int targetCount = 1;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      int id = grid[i][j].robot.id;
      if (grid[i][j].wall.type != 0 &&
          grid[i][j].robot.id == 0) { // Box with a wall and no robot
        displayWall(grid, i, j);
      } else if (grid[i][j].wall.type != 0 &&
                 grid[i][j].robot.id != 0) { // Box with a wall and a robot
        displayOccupiedWall(grid, i, j);
      } else if (grid[i][j].wall.type == 0 && grid[i][j].robot.id == 0 &&
                 grid[i][j].target ==
                     0) { // Box with no robot, no target and no wall
        printf("\x1b[0m");
        printf("\x1B[0m - ");
      } else if (grid[i][j].target != 0 &&
                 grid[i][j].robot.id == 0) { // Box with a target and no robot
        displayTarget(grid[i][j].target);
        targetCount++; // Allow the target to have different id's
      } else {         // Box with a robot and nothing else
        displayRobot(grid[i][j].robot.id);
      }
    }
    printf("\n");
  }
}