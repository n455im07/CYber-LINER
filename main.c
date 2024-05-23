#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "add_content.h"
#include "choices.h"
#include "create.h"
#include "display.h"
#include "utilities.h"
#include "search.h"

#define GRID_SIZE 22
#define MAX_PLAYERS 6

void move(Box **grid, Position position, int *choice, int direction) {// Moove the choosen robot depending of the obstacles on the grid
  
  if (grid == NULL) { 
    printf("Allocation failed");
    exit(4);
  }
  if (choice == NULL) {
    printf("Allocation failed");
    exit(5);
  }

  int x = position.x;
  int y = position.y;
  int numTarget = choice[1];
  int idRobot = choice[0];
  switch (direction) {
  case 'z':
    if (grid[x][y].wall.type != 4 && grid[x - 1][y].robot.id == 0 &&
        grid[x - 1][y].wall.type != 1) {

      grid[x][y].robot.id = 0;
      grid[x - 1][y].robot.id = idRobot;
    }
    break;
  case 'q':
    if (grid[x][y].wall.type != 2 && grid[x][y - 1].robot.id == 0 &&
        grid[x][y - 1].wall.type != 3) {

      grid[x][y].robot.id = 0;
      grid[x][y - 1].robot.id = idRobot;
    }
    break;
  case 's':
    if (grid[x][y].wall.type != 1 && grid[x + 1][y].robot.id == 0 &&
        grid[x + 1][y].wall.type != 4) {

      grid[x][y].robot.id = 0;
      grid[x + 1][y].robot.id = idRobot;
    }
    break;
  case 'd':
    if (grid[x][y].wall.type != 3 && grid[x][y + 1].robot.id == 0 &&
        grid[x][y + 1].wall.type != 2) {
      grid[x][y].robot.id = 0;
      grid[x][y + 1].robot.id = idRobot;
    }
    break;
  }
}

void playRound(Box **grid, Player *player, int difficulty, int nbPlayers,
               int size, int *choice, int r, int maxRound) {
  if (grid == NULL) {
    printf("Allocation failed");
    exit(8);
  }
  if (player == NULL) {
    printf("Allocation failed");
    exit(9);
  }
  if (choice == NULL) {
    printf("Allocation failed");
    exit(10);
  }
 
  int movements[MAX_PLAYERS] = {0};
  int scan = 0;
  for (int i = 0; i < nbPlayers; i++) {
    printf("\x1B[34m Player %d please indicate how many movements you need to reach the target\n\x1B[35m", player[i].id);
    scan = scanf("%d", &movements[i]); 
    empty_buffer();
    while (movements[i] <= 0 || movements[i] > 100 || scan != 1) {
      printf("\x1B[34mInvalid nomber of movements, retry please : \n\x1B[35m");
      scan = scanf("%d", &movements[i]);
      empty_buffer();
    }
  }
  int min = movements[0];
  int minIndex = 0;
  int numMovements = 0;
  for (int i = 0; i < nbPlayers; i++) {
    if (movements[i] <= min) {
      min = movements[i];
      minIndex = i;
    }
  }

  printf("\x1B[34m\nThe minimun number of movements in this round is %d so the "
         "player ",
         min);
  printf("%d\x1B[34m play !\n", player[minIndex].id);

  displayGrid(grid, size);

  int cible = 0;
  int minMovementsPlayers = min;
  
  while (min > 0 && cible == 0) {

    char direction;
    
    do {
      printf("\x1B[37mChoose a direction using z-q-s-d\n");
      scan = scanf(" %c", &direction);
      empty_buffer(); 
    } while (direction != 'd' && direction != 's' && direction != 'q' &&
                 direction != 'z' ||
             scan != 1);

    int idRobot = choice[0];
    int numTarget = choice[1];

    Position posRobot = searchRobot(grid, size, idRobot);
    Position posTarget = searchTarget(grid, size, numTarget);

    int distance = searchDistance(grid, size, posRobot, direction);

    Position previousPosRobot = posRobot;
    numMovements++;
    for (int i = 0; i < size; i++) {
      int clear = system("clear");
      clearScreen(clear);
      move(grid, posRobot, choice, direction);
      displayGrid(grid, size);
      printf("\n\n DISTANCE = %d\n", distance);
      usleep(80000);
      posRobot = searchRobot(grid, size, idRobot);
      printf("Updated Robot Position: (%d, %d)\n", posRobot.x, posRobot.y);
      printf("Updated Target Position: (%d, %d)\n\n", posTarget.x, posTarget.y);

      if (posRobot.x == posTarget.x && posRobot.y == posTarget.y) {
        cible = 1;
        printf("\x1B[36m TARGET REACHED !\n");
        break;
      }
      if (posRobot.x == previousPosRobot.x &&
          posRobot.y == previousPosRobot.y) {
        break;
      }
      previousPosRobot = posRobot;
    }
    min--;
   
    switch(min){
      case 1:
        printf("\x1b[31m");
        printf("Movements lefts : %d\n", min);
         break;
      case 2: 
        printf("\x1b[35m");
        printf("Movements lefts : %d\n", min);
         break;
      case 3 :
         printf("\x1b[33m");
         printf("Movements lefts : %d\n", min);
          break;
      default:
      printf("\x1b[37m");
      printf("Movements lefts : %d\n", min);
       break;
    }
    
  
  }
  printf("\x1b[0m");

}


int main()
{
    int *choice = NULL;
    // srand(time(NULL));
    int size = GRID_SIZE;
    printf("   \x1B[34m_____   __\x1B[35m_                 _    ___ _  _ ___ ___ \n");
    printf(" \x1B[34m / __\\ \\ / /\x1B[35m |__  ___ _ _ ___| |  |_ _| \\| | __| _ \\\n");
    printf("\x1B[34m | (__ \\ V /\x1B[35m| '_ \\/ -_) '_|___| |__ | || .` | _||   /\n");
    printf(" \x1B[34m \\___| |_| \x1B[35m|_.__/\\___|_|     |____|___|_|\\_|___|_|_\\\n");
    printf("\n\n\x1B[34mGRIDSIZE = %d\n", size);

    printf("\x1B[0m");

 // PLAYER BOARD CREATION
  int nbPlayers = ChooseNbPlayers();
  Player *player = createPlayerBoard(nbPlayers, size);

    // GRID CREATION
    Box **grid = createGrid(size);
    addBoxes(grid, size);
    addTargets(grid, size, 18); // Add 18 targets
    addSpikes(grid, size);
    addRobots(grid, size);
    int r=1;
    for (int r = 1; r <= 5; r++) {
        printf("\x1B[35mRound %d/%d\n\n", r, 5);            
        int *choice = randomChoice(grid, size); // Choose choice
        displayGrid(grid, size);
        playRound(grid, player,3, nbPlayers, size, choice, r, 5);
  }
    // Display test
    displayGrid(grid, size);

    // Free all memory
    for (int k = 0; k < size; k++)
    {
        free(grid[k]);
    }
    free(grid);
    free(choice);
    return 0;
}
