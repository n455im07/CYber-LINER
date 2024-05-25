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
    printf("\x1B[34m╔════════════════════════════════════════════════════╗\n");
    printf("\x1B[34m║\x1B[35m   === Select Number of Players (2-6) ===\x1B[34m           ║\n");
    printf("\x1B[34m║\x1B[36m           [2] [3] [4] [5] [6]                      \x1B[34m║\n");
    printf("\x1B[34m╚════════════════════════════════════════════════════╝\n\x1B[35m");
    printf("\x1B[36mYour choice:\n\n \x1B[37m");
    scan = scanf("%1d%c", &nbPlayers, &a);
    if(nbPlayers < 2 || nbPlayers > 6 || scan != 2 || a!= '\n'){
      printf("Wrong input\n");
        empty_buffer();
    }
    
  } while (nbPlayers < 2 || nbPlayers > 6 || scan != 2 || a!= '\n'); // Loop until the number of player is valid (2-6)
  return nbPlayers;
}

int chooseRounds() { // User choose the maximum number of rounds
  int maxRounds = 0;
  int scan = 0;
  do {
    printf("\x1B[34m╔══════════════════════════════════════════════════════════╗\n");
    printf("\x1B[34m║\x1B[35m             === Select Number of Rounds ===              \x1B[34m║\n");
    printf("\x1B[34m║\x1B[36m               Enter the number of rounds (1-20):         \x1B[34m║\n");
    printf("\x1B[34m╚══════════════════════════════════════════════════════════╝\n\x1B[35m");
    printf("\x1B[36mYour choice: \x1B[37m");
    scan = scanf("%d", &maxRounds);
      if(scan != 1 || maxRounds <= 0 || maxRounds>20 ){
        printf("Wrong input\n");
          empty_buffer();
      }
  
  }while( scan != 1 || maxRounds <= 0 || maxRounds>20); // Loop until the maximum number of rounds is valid (1-20) 
  empty_buffer();
  return maxRounds;
 }

int chooseDifficulty() { // User choose the difficulty level
  int difficulty = 0;
  int scan = 0;
  printf("\n");
  printf("\x1B[34mThere are 3 differents levels of difficulty : \n");
printf("\n");
  printf("\x1B[32m"); // Set text color to green
  printf("1 => [Easy]\n");
  printf("\x1B[33m"); // Set text color to yellow
  printf("2 => [Medium]\n");
  printf("\x1B[31m"); // Set text color to red
  printf("3 => [Hard]\n");
printf("\n");
  do {
    printf("\x1B[34mChoose game difficulty (1,2 or 3) ? : \n\x1B[35m");
    scan = scanf("%d", &difficulty);
   if ( difficulty != 3 && difficulty != 2 && difficulty != 1 || scan != 1 ){
    printf("Wrong input\n");
     empty_buffer();
   }
  } while (difficulty != 3 && difficulty != 2 && difficulty != 1 || scan != 1); // Loop until difficulty level is valid (1,2,3)
  empty_buffer();
  printf("\n");
  do{ // Display the difficulty level choosen
    printf("\x1B[34m╔══════════════════════════════════════════════════════════╗\n");
    printf("\x1B[34m║\x1B[35m        === Difficulty Gauge ===                          \x1B[34m║\n");
    printf("\x1B[34m║                                                          ║\n");
    printf("\x1B[34m║\x1B[35m");
    for (int i = 0; i < 3; ++i) {
      if (i < difficulty) {
            printf("\x1B[31m█"); // Red for high difficulty
        } else {
            printf("\x1B[37m█"); // White for low difficulty
        }
    }
    printf("\x1B[34m                                                       ║\n");
    printf("\x1B[34m║                                                          ║\n");
    printf("\x1B[34m╚══════════════════════════════════════════════════════════╝\n\x1B[35m");
  } while (difficulty <= 0); 
  return difficulty;
}


int *randomChoice(Box **grid, int size) { 
  int *choice = NULL;
  if(grid==NULL){
    printf("Error: malloc failed\n");
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
  displayRobot(idRobot); // Display the caracter in colors depending on the id
  printf("\x1B[37m\nYour target is :");
  displayTarget( numTarget); // Display the target caracter depending on the number
  printf("\n");
  choice[0] = idRobot; 
  choice[1] = numTarget;
  return choice; // Return array with robot id and target id
}