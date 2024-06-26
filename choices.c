#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "Headers/create.h"
#include "Headers/display.h"
#include "Headers/choices.h"
#include "Headers/utilities.h"


int chooseNbPlayers() { // User choose the number of players
  int nbPlayers = 0;
  int scan = 0; char a;
  do {
    printf("\x1B[32m╔════════════════════════════════════════════════════╗\n");
    printf("\x1B[32m║\x1B[0m   === Select Number of Players (2-6) ===\x1B[32m           ║\n");
    printf("\x1B[32m║\x1B[32m           [2] [3] [4] [5] [6]                      \x1B[32m║\n");
    printf("\x1B[32m╚════════════════════════════════════════════════════╝\n\x1B[35m");
    printf("\x1B[32mYour choice:\n\n \x1B[37m");
    scan = scanf("%1d%c", &nbPlayers, &a);
    
    if(nbPlayers < MIN_PLAYERS || nbPlayers > MAX_PLAYERS){
      printf("Wrong input\n");
    }  
    if (scan != 2 || a!= '\n' ){
      empty_buffer(); 
    }
  } while (nbPlayers < MIN_PLAYERS || nbPlayers > MAX_PLAYERS || scan != 2 || a!= '\n'); // Loop until the number of player is valid (2-6)
  return nbPlayers;
}

int chooseRounds() { // User choose the maximum number of rounds
  int maxRounds = 0;
  int scan = 0;char b;
  do {
    printf("\x1B[34m╔══════════════════════════════════════════════════════════╗\n");
    printf("\x1B[34m║\x1B[0m             === Select Number of Rounds ===              \x1B[34m║\n");
    printf("\x1B[34m║\x1B[34m               Enter the number of rounds (1-20):         \x1B[34m║\n");
    printf("\x1B[34m╚══════════════════════════════════════════════════════════╝\n\x1B[34m");
    printf("\x1B[34mYour choice:\n \x1B[37m");
    scan = scanf("%d%c", &maxRounds, &b);
      if( maxRounds <  MIN_ROUNDS || maxRounds > MAX_ROUNDS){
        printf("Wrong input\n");
      }
     if(scan != 2 ||  b!= '\n' ){
         empty_buffer();
     }

  }while( scan != 2 || maxRounds < MIN_ROUNDS  || maxRounds > MAX_ROUNDS || b!= '\n'); // Loop until the maximum number of rounds is valid (1-20) 
  return maxRounds;
 }

int chooseDifficulty() { // User choose the difficulty level
  int difficulty = 0;
  int scan = 0;char b;
  printf("\n");
  printf("\x1B[35mThere are 3 differents levels of difficulty : \n");
printf("\n");
  printf("\x1B[32m"); // Set text color to green
  printf("1 => [Easy]\n");
  printf("\x1B[33m"); // Set text color to yellow
  printf("2 => [Medium]\n");
  printf("\x1B[31m"); // Set text color to red
  printf("3 => [Hard]\n");
printf("\n");
  do {
    printf("\x1B[35mChoose game difficulty (1,2 or 3) ? : \n\x1B[37m");
    scan = scanf("%1d%c", &difficulty, &b);
   if ( difficulty != 3 && difficulty != 2 && difficulty != 1){
     printf("Wrong input\n");
   }
   if ( scan != 2 || b!= '\n'){
       empty_buffer();
   }
  } while (difficulty != 3 && difficulty != 2 && difficulty != 1 || scan != 2 || b!= '\n'); // Loop until difficulty level is valid (1,2,3)
  printf("\n");
  do{ // Display the difficulty level choosen
    printf("\x1B[35m╔══════════════════════════════════════════════════════════╗\n");
    printf("\x1B[35m║\x1B[0m        === Difficulty Gauge ===                          \x1B[35m║\n");
    printf("\x1B[35m║                                                          ║\n");
    printf("\x1B[35m║\x1B[0m");
    for (int i = 0; i < 3; ++i) {
      if (i < difficulty) {
            printf("\x1B[31m█"); // Red for high difficulty
        } else {
            printf("\x1B[37m█"); // White for low difficulty
        }
    }
    printf("\x1B[35m                                                       ║\n");
    printf("\x1B[35m║                                                          ║\n");
    printf("\x1B[35m╚══════════════════════════════════════════════════════════╝\n\x1B[0m");
    sleep(1);
  } while (difficulty <= 0); 
  return difficulty;
}

int *randomChoice(Box **grid, int size,int artStyle) { 
  int *choice = NULL;
  if(grid==NULL){
    printf("Error: malloc failed\n");
    exit(1);
  }
    if(size<MIN_GRID_SIZE || size>MAX_GRID_SIZE){
    printf("Error : grid size is not between %d and %d\n",MIN_GRID_SIZE,MAX_GRID_SIZE);
    exit(1);
  }
  choice = malloc(2 * sizeof(int)); // Allocate memory for choice array
  if (choice == NULL) { // Verify if memory is allocated
    printf("Error: malloc failed #4\n");
    exit(1);
  }
  int idRobot = 0;
  int numTarget = 0;
  int n = 0;
  n = rand() % 4 + 1; // Random number between (1-4) (Robot id)
  int x = rand() % (size - 2) + 1; // Random number between 1 and size - 2
  int y = rand() % (size - 2) + 1; // Random between 1 and size - 2
  while (grid[x][y].robot.id != n) {
    x = rand() % (size - 2) + 1;
    y = rand() % (size - 2) + 1;
  }
  idRobot = grid[x][y].robot.id; // Random robot choosen

  n = rand() % 18 + 1; // Random number between 1 and 18 ( ID'S OF THE TARGETS)
  while (
      grid[x][y].target != n || grid[x][y].robot.id == 1 ||
      grid[x][y].robot.id == 2 || grid[x][y].robot.id == 3 ||
      grid[x][y].robot.id == 4) { // Verify if it's the correct target and if it's not already occupied by a robot 
    x = rand() % (size - 4) + 2;
    y = rand() % (size - 4) + 2;
  }
  numTarget = grid[x][y].target; // Random target choosen

  printf("\x1B[37m\nYour robot is :");
  displayRobot(idRobot,artStyle); // Display the caracter in colors depending on the id
  printf("\x1B[37m\nYour target is :");
  displayTarget( numTarget); // Display the target caracter depending on the number
  printf("\n");
  choice[0] = idRobot; 
  choice[1] = numTarget;
  return choice; // Return array with robot id and target id
}