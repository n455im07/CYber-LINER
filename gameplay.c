#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Headers/gameplay.h"
#include "Headers/utilities.h"
#include "Headers/search.h"
#include "Headers/display.h"

void pointsCalculator(int nummovements, int cible, Player *player, int nbPlayers, int minMovementsPlayers, int minIndex) { // Calculate the points of the players depending of the customers conditions
  if (cible == 0) {
    for (int i = 0; i < nbPlayers; i++) {
      if (player[i].id == player[minIndex].id) {
        player[i].score = player[i].score + 0;
      } else {
        player[i].score = player[i].score + 1;
      }
    }
  } else if (cible == 1 && nummovements == minMovementsPlayers) {
    player[minIndex].score = player[minIndex].score + 2;
  } else {
    player[minIndex].score = player[minIndex].score - 1;
  }
  for (int i = 0; i < nbPlayers; i++) {
    printf("\x1B[34m|Score player %d : (%d)|\n", player[i].id,
           player[i].score);
  printf("\n");
  }
printf("\n");
}

void countdown(int difficulty, Box** grid, int size, int r, int maxRound,int *choice){ // Stopwatch depeding on the difficulty choosed
  printf("\n");
  printf(" The Players choose the difficulty number %d ! \n", difficulty);
  printf("\n");
  usleep(5);
  int x = 0;
  switch (difficulty){
    case 1:
    x=45;
    break;
    case 2:
    x=25;
    break;
    case 3:
    x=15;
    break;
  }
  printf("\e[0;31m WARNING  \e[0;0m players you will have %d seconds to think of how many movement you will need to land on the target we choosed for ",x);
  displayCountdown(x, grid, size, r, maxRound,choice);
  int clear = system("clear");
    clearScreen(clear);
  printf("TIMES UP !! \n");
}


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

void playRound(Box **grid, Player *player, int difficulty, int nbPlayers,int size, int *choice, int r, int maxRound) {
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
  countdown(difficulty,grid,size, r, maxRound, choice);
  int movements[MAX_PLAYERS] = {0};
  int scan = 0; char a;
  for (int i = 0; i < nbPlayers; i++) {
    do{
    printf("\x1B[34m Player %d please indicate how many movements you need to reach the target\n\x1B[35m", player[i].id);
    scan = scanf("%3d%c", &movements[i], &a); 
    if (movements[i] <= 0 || movements[i] > 100 || scan != 2 || a!= '\n'){
      printf("\x1B[34mInvalid nomber of movements bigger than 100, retry please : \n\x1B[35m");
    empty_buffer();
    }   
    }while (movements[i] <= 0 || movements[i] > 100 || scan != 2|| a!='\n');
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

  displayGrid(grid, size,r,maxRound,choice);

  int cible = 0;
  int minMovementsPlayers = min; char b;
  
  while (min > 0 && cible == 0) {
    char direction;
    do {
      printf("\x1B[37mChoose a direction using z-q-s-d\n");
      scan = scanf("%1c%c", &direction, &b);
      if ( direction != 'd' && direction != 's' && direction != 'q' && direction != 'z' ||  scan != 2 || b!= '\n'){
      printf("Wrong input\n");
      empty_buffer(); 
      }
    } while (direction != 'd' && direction != 's' && direction != 'q' && direction != 'z' ||  scan != 2 || b!= '\n');

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
      displayGrid(grid, size,r,maxRound,choice);
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
  pointsCalculator(numMovements, cible, player, nbPlayers, minMovementsPlayers,minIndex);

}

void startGame(){
    printf("\n\n\n");
    printf("\x1B[34m╔════════════════════════════════════════════════════╗\n");
    printf("\x1B[34m║");
    printf("\x1B[35m          ☛ Press ENTER to start the game ☚         ");
    printf("\x1B[34m║\n");
    printf("\x1B[34m╚════════════════════════════════════════════════════╝\n");
    printf("\n\n\n");
    getchar();
    
}
