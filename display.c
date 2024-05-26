#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Headers/display.h"
#include "Headers/create.h"
#include "Headers/utilities.h"

void displayCountdown(int x,Box** grid, int size, int r, int maxRound,int* choice,int artStyle){ // Display a countdown
  if(x<=0){
    printf("Error : time value is negative (displayCountdown)");
    exit(1);
  }
  if(grid==NULL){
      printf("Error : grid is NULL (displayCountdown)");
    exit(1);
  }
  if(r<=0){
    printf("Error : round count is negative (displatCountdown)");
    exit(1);
  }
  if(maxRound<=0){
    printf("Error : max round is negative (displatCountdown)");
    exit(1);
  }
  if(choice==NULL){
      printf("Error : choice is NULL (displatCountdown)");

    exit(1);
  }
  for (int i = x; i>0 ; i--){ // Loop during x seconds
    int clear = system("clear");
  clearScreen(clear); // system("clear") verification
  displayGrid(grid,size, r, maxRound,choice,artStyle); // Displaying the grid for the player to think about a strategy
  switch (i){ // Change the color of the countdown to Yellow for 3, Orange for 2, Red for 1
    case 3:
      printf("\x1B[33m");
      break;
    case 2:
      printf("\x1B[38;5;208m");
      break;
    case 1:
      printf("\x1B[31m");
      break;
    default:
      printf("\x1B[37m"); 
  }
    printf("%ds\n",i); // Print the time left before asking the number of movements
    sleep(1);
     fflush(stdout);
    }
}

void displayWinner(Player *player, int nbPlayers){ // Display the winner of the game
  if(player==NULL){
    exit(1);
  }
  if(nbPlayers<MIN_PLAYERS || nbPlayers>MAX_PLAYERS){
      printf("Error : nbPlayers is not between %d and %d (displayWinner)",MIN_PLAYERS,MAX_PLAYERS);
    exit(1);
  }
  int clear = system("clear");
  clearScreen(clear);
  
 printf("\x1B[34m╔════════════════════════════════════════════╗\n\x1B[0m");
printf("\x1B[36m\x1B[1m                SCOREBOARD           \x1B[0m");
printf("\n");
  printf("\x1B[34m╚════════════════════════════════════════════╝\n\x1B[0m");
  
  printf("\n");
  int maxscore = player[0].score;
  for (int i = 0; i < nbPlayers; i++) { // Search for the player with the highest score
    if (maxscore < player[i].score) {
      maxscore = player[i].score;
    }
  }
  for (int i = 0 ; i < nbPlayers; i++){ // Show the winner's score as well as the score of other players
    if ( player[i].score == maxscore){
      printf("\n\n\n\x1B[36mThe winner is : Player %d his score is %d\n\n",player[i].id ,maxscore);
    }
    printf("\x1B[37m▔▔▔▔▔▔▔▔▔|▔▔▔");
    printf("\nPlayer \x1B[34m%d \x1B[37m| \x1B[35m%d \x1B[37m\n",player[i].id, player[i].score);
    printf("▁▁▁▁▁▁▁▁▁|▁▁▁\n");
    printf("\n");
  }

  printf("\n\n\x1B[36mTHANKS FOR PLAYING ! \n\n");
}

void displayRobot(int id, int artStyle) { // Display robots colors depending on their id and the art style selected
  if (id < MIN_ID || id > MAX_ID) {
      printf("Error : id is not between 1 and 4 (displayRobot)");
    exit(1);
  }
  if (artStyle==1){
    switch (id){
      case 1:
        printf("🎃");
        break;
      case 2:
        printf("🤖");
        break;
      case 3:
        printf("👻");
        break;
      case 4:
        printf("👽");
        break;
    }
  }else if (artStyle==0){
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
}

void displayColor(int id) { // Change the colors depending of the robot id
  if (id < MIN_ID || id > MAX_ID) {
    printf("Error : id is not between 1 and 4 (displayColor)");
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
  if (target < MIN_TARGET || target > MAX_TARGET) {
    exit(1);
  }
  printf("\033[0m"); // Sets the color to default
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

void displayOccupiedWall(Box **grid, int x,int y) { // Display wall occupied by a robot depending on wall type
  if (grid == NULL) {
    free(grid);
    exit(1);
  }
  displayColor(grid[x][y].robot.id); // Change the color depending on the robot id
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

void displayWall(Box **grid, int x,int y) { // Display wall depending on wall type
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
 if (grid==NULL){
    printf("Error : grid is NULL (convertGrid)");
    exit(1);
  }
  if(size<MIN_GRID_SIZE || size>MAX_GRID_SIZE){
    printf("Error : grid size is not between %d and %d (convertGrid)",MIN_GRID_SIZE,MAX_GRID_SIZE);
  }
  int fullSize = size * 2 + 1 ; // Double the size of the grid to display with emojis
  int **prtGrid = malloc(fullSize * sizeof(int *)); // Allocate memory for the grid
  for (int k = 0; k < fullSize; k++) {
    prtGrid[k] = calloc(fullSize, sizeof(int)); // Allocate memory for each line of the grid
  }
  for (int i = 0; i < fullSize; i++) {
    for (int j = 0; j < fullSize; j++) {
      if ((i == 2 && j<fullSize-3 && j>2)|| (j == 2 && i>2 && i<fullSize-3) || (i == fullSize - 3 && j<fullSize-3 && j>2) || (j == fullSize - 3 && i<fullSize-3 && i>2))  {
        prtGrid[i][j] = 1; // Fill borders with 1
      }
    }
  }
  int rbCount = 4;
  //Loop in the small grid to put values in the bigger grid
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if(grid[i][j].wall.type==2 && i==1 && j!= 0 && j!= size -2){
        prtGrid[2*i+1][j*2]=1; // Add spikes on top side of the grid
      }
      if(grid[i][j].wall.type==2 && i ==size-2 && j!= 0 && j!= size -2 ){
        prtGrid[2*i+1][j*2]=1; // Add spikes on bottom side of the grid
        
      }
      if(grid[i][j].wall.type==1 && j==1 && i!= 0 && i!=size-2) {
        prtGrid[2*i+2][j*2+1]=1; // Add spikes on left side of the grid
        
      }
      if(grid[i][j].wall.type==1 && j==size-2 && i!= 0 && i!=size-2) {
        prtGrid[2*i+2][j*2+1]=1; // Add spikes on right side of the grid
  
      }
      if (grid[i][j].target != 0) {
        prtGrid[i * 2 + 1][j * 2 + 1] = -grid[i][j].target; // Place targets on the grid (-1 is for the target number 1 for exemple)
        switch (grid[i][j].angle) { // Put walls arround the targets depending on the angle that should be covered
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

      if (grid[i][j].robot.id != 0) {
        switch (grid[i][j].robot.id) { // Put robots depending on their id 
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
      switch (prtGrid[i][j]) { // Print the grid
      case 0:
        printf("  "); // Nothing
        break;
      case 1:
        printf("🟫"); // Wall
        break;
      case 2:
        printf("🟥"); // Target for testing
        break;
      case 3:
        printf("⬜"); // Wall arround targets
        break;
      case 4:
        printf("🎃"); // Robot 1
        break;
      case 5:
        printf("🤖"); // Robot 2
        break;
      case 6:
        printf("👻"); // Robot 3
        break;
      case 7:
        printf("👽"); // Robot 4
        break;
        //Targets
      case -1:
        printf("01");
        break;
      case -2:
        printf("02");
        break;
      case -3:
        printf("03");
        break;
      case -4:
        printf("04");
        break;
      case -5:
        printf("05");
        break;
      case -6:
        printf("06");
        break;
      case -7:
        printf("07");
        break;
      case -8:
        printf("08");
        break;
      case -9:
        printf("09");
        break;
      case -10:
        printf("10");
        break;
      case -11:
        printf("11");
        break;
      case -12:
        printf("12");
        break;
      case -13:
        printf("13");
        break;
      case -14:
        printf("14");
        break;
      case -15:
        printf("15");
        break;
      case -16:
        printf("16");
        break;
      case -17:
        printf("17");
        break;
      case -18:
        printf("18");
        break;
      }
    }
    printf("\n");
  }
  return 0;
}

void displayGrid(Box **grid, int size,int r,int maxRound, int* choice, int artStyle) { // Display the whole grid
  if(grid==NULL){
    exit(1);
    free(grid);
  }
  if(r<=0){
    printf("Error : round count is negative (displatCountdown)");
    exit(1);
  }
  if(maxRound<=0){
    printf("Error : max round is negative (displatCountdown)");
    exit(1);
  }
  if(choice==NULL){
    exit(1);
  }
    if(size<MIN_GRID_SIZE || size>MAX_GRID_SIZE){
    printf("Error : grid size is not between %d and %d (displayGrid)",MIN_GRID_SIZE,MAX_GRID_SIZE);
  }
  if (grid == NULL) { // Verify if memory is allocated
    printf("Allocation failed");
    exit(1);
  }
  printf("\n\n");
  printf("\x1B[35;1m%d/%d rounds\n", r,maxRound); // Show the current round number and the total number of rounds in magenta
  printf("\x1B[37m\nYour robot is :");
  displayRobot(choice[0],artStyle); // Display the robot in colors depending on the id
  printf("\x1B[37m\nYour target is :"); //
  displayTarget(choice[1]); // Display the target depending on the number
  printf("\n");

  if (artStyle==1){
    convertGrid(grid, size); // Display the grid in emoji style
  }else if (artStyle==0){ // Display the grid in special character style
    int targetCount = 1;
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        int id = grid[i][j].robot.id;
        if (grid[i][j].wall.type != 0 && grid[i][j].robot.id == 0) { // Box with a wall and no robot
          displayWall(grid, i, j);
        } else if (grid[i][j].wall.type != 0 && grid[i][j].robot.id != 0) { // Box with a wall and a robot
          displayOccupiedWall(grid, i, j);
        } else if (grid[i][j].wall.type == 0 && grid[i][j].robot.id == 0 && grid[i][j].target == 0) { // Box with no robot, no target and no wall
          printf("\x1b[0m");
          printf("\x1B[0m - ");
        } else if (grid[i][j].target != 0 && grid[i][j].robot.id == 0) { // Box with a target and no robot
          displayTarget(grid[i][j].target);
          targetCount++; // Allow the target to have different id's
        } else {         // Box with a robot and nothing else
          displayRobot(grid[i][j].robot.id,artStyle);
        }
      }
      printf("\n");
    }
  }
}