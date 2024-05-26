#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Headers/gameplay.h"
#include "Headers/utilities.h"
#include "Headers/search.h"
#include "Headers/display.h"

void pointsCalculator(int nummovements, int target, Player *player, int nbPlayers, int minMovementsPlayers, int minIndex) { // Calculate the points of the players depending of the customers conditions
  if(player==NULL){
    printf("Error: player malloc failed \n");
    exit(1);
  }
  if(nbPlayers<MIN_PLAYERS || nbPlayers>MAX_PLAYERS){
    printf("Error : number of players is not between %d and %d\n",MIN_PLAYERS,MAX_PLAYERS);
    exit(1);
  }
  if(nummovements<=0){
    printf("Number of movements cannot be negative or 0\n");
    exit(1);
  }
  if (target == 0) { // if the target is not reach then you give 0 points to the player but you give 1 point to the others;
    for (int i = 0; i < nbPlayers; i++) {
      if (player[i].id == player[minIndex].id) {
        player[i].score = player[i].score + 0;
      } else {
        player[i].score = player[i].score + 1;
      }
    }
  } else if (target == 1 && nummovements == minMovementsPlayers) { // if the target is reach with the exact ammount of movements that the actual player gived, then you give 2 point to him and 0 to the others
    player[minIndex].score = player[minIndex].score + 2;
  } else {
    player[minIndex].score = player[minIndex].score - 1; // if the target is reached but with less movements that the actual player gived, then you substract 1 point to the actual player and give 0 to the others.
  }
  for (int i = 0; i < nbPlayers; i++) {
    printf("\x1B[34m|Score player %d : (%d)|\n", player[i].id,
           player[i].score);
  printf("\n");
  }
printf("\n");
}

void countdown(int difficulty, Box** grid, int size, int r, int maxRound,int *choice,int artStyle){ // Stopwatch depeding on the difficulty choosed
    if(difficulty!=1 && difficulty!=2 && difficulty!=3){
    printf("Error : difficulty is not between 1 and 3\n");
    exit(1);
  }
  if(grid==NULL){
    printf("Error: malloc failed\n");
    exit(1);
  }
  if(size<MIN_GRID_SIZE || size>MAX_GRID_SIZE){
    printf("Error : grid size is not between %d and %d\n",MIN_GRID_SIZE,MAX_GRID_SIZE);
    exit(1);
  }
  if(r<=0 || r > maxRound){
    printf("Error : round is not between 1 and %d\n",maxRound);
    exit(1);
  }
  if(maxRound<=0 || maxRound > MAX_ROUNDS ){
    printf("Error : max round is not between 1 and %d\n",MAX_ROUNDS);
    exit(1);
  }
  if(choice==NULL){
    printf("Error: malloc failed\n");
    exit(1);
  }
  if(artStyle<0 || artStyle>1){
    printf("Error : art style is not between 0 and 1\n");
    exit(1);
  }
  int x = 0;
  switch (difficulty){
    case 1:
    x=45; // easy
    break;
    case 2:
    x=25; // medium
    break;
    case 3:
    x=15; // hard
    break;
  }
  printf("\x1B[37m\nLook closely, you will only have few seconds to create a path to the target !");
  sleep (1);
  printf("\n");
  printf("3\n");
  sleep(1);
  printf("2\n");
  sleep(1);
  printf("1\n");
  sleep(1);
  printf("GO !\n");
  sleep(1);
  displayCountdown(x, grid, size, r, maxRound,choice,artStyle);
  int clear = system("clear");
    clearScreen(clear);
  printf("TIMES UP !! \n");
}

void move(Box **grid, Position position, int choice, int direction) {// Moove the choosen robot depending of the obstacles on the grid
  
  if (grid == NULL) { 
    printf("Allocation failed");
    exit(4);
  }
  if(direction != 'z' && direction != 'q' && direction != 's' && direction != 'd'){
    exit(1);
  }
  int x = position.x;
  int y = position.y;
  int idRobot = choice; // contains the id of the robot choosed randomly
  switch (direction) {
  case 'z':
    if (grid[x][y].wall.type != 4 && grid[x - 1][y].robot.id == 0 &&
        grid[x - 1][y].wall.type != 1) { // Check if  the robot can move up, if it can, then move it up and update the grid

      grid[x][y].robot.id = 0;
      grid[x - 1][y].robot.id = idRobot;
    }
    break;
  case 'q':
    if (grid[x][y].wall.type != 2 && grid[x][y - 1].robot.id == 0 &&
        grid[x][y - 1].wall.type != 3) {// Check if  the robot can move left, if it can, then move it up and update the grid

      grid[x][y].robot.id = 0;
      grid[x][y - 1].robot.id = idRobot;
    }
    break;
  case 's':
    if (grid[x][y].wall.type != 1 && grid[x + 1][y].robot.id == 0 &&
        grid[x + 1][y].wall.type != 4) {// Check if  the robot can move down, if it can, then move it up and update the grid

      grid[x][y].robot.id = 0;
      grid[x + 1][y].robot.id = idRobot;
    }
    break;
  case 'd':
    if (grid[x][y].wall.type != 3 && grid[x][y + 1].robot.id == 0 &&
        grid[x][y + 1].wall.type != 2) {// Check if  the robot can move rigth, if it can, then move it up and update the grid
      grid[x][y].robot.id = 0;
      grid[x][y + 1].robot.id = idRobot;
    }
    break;
  }
}

void playRound(Box **grid, Player *player, int difficulty, int nbPlayers,int size, int *choice, int r, int maxRound, int artStyle) {
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
    if(nbPlayers<MIN_PLAYERS || nbPlayers>MAX_PLAYERS){
      printf("Error : number of players is not between %d and %d\n",MIN_PLAYERS,MAX_PLAYERS);
      exit(1);
  }
  if(difficulty < 1 || difficulty > 3){
    printf("Error : difficulty is not between 1 and 3\n");
    exit(2);
  }
    if(size<MIN_GRID_SIZE || size>MAX_GRID_SIZE){
    printf("Error : grid size is not between %d and %d\n",MIN_GRID_SIZE,MAX_GRID_SIZE);
    exit(1);
  }
  if(r<=0){
    printf("Error : round is not between 1 and %d\n",maxRound);
    exit(1);
  }
  if(maxRound>MAX_ROUNDS){
    printf("Error : max round is not between 1 and %d\n",MAX_ROUNDS);
    exit(1);
  }
  if(artStyle<0 || artStyle>1){
    printf("Error : art style is not between 0 and 1\n");
    exit(1);
  }
  countdown(difficulty,grid,size, r, maxRound, choice,artStyle);
  int movements[MAX_PLAYERS] = {0};
  int scan = 0; char a;
  for (int i = 0; i < nbPlayers; i++) { //ask the players about their movements
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
  int numMovements = 0; //number of movements 
  for (int i = 0; i < nbPlayers; i++) { // the player who indicate the less number of movements is choosen as the actual player
    if (movements[i] <= min) {
      min = movements[i];
      minIndex = i;
    }
  }

  printf("\x1B[34m\nThe minimun number of movements in this round is %d so the ""player ",min);
  printf("%d\x1B[34m play !\n", player[minIndex].id); // minimum of movements this round
  printf("%d\x1B[34m play !\n", player[minIndex].id); // the actual player
  displayGrid(grid, size,r,maxRound,choice,artStyle);  // displaying the grid
  int target = 0;
  int minMovementsPlayers = min; char b;
  
  while (min > 0 && target == 0) { // loop until the target is reached or the player run out of movements
    char direction;
    do { // ask the player to choose a direction
      printf("\x1B[37mChoose a direction using z-q-s-d\n");
      scan = scanf("%1c%c", &direction, &b);
      if ( direction != 'd' && direction != 's' && direction != 'q' && direction != 'z' ||  scan != 2 || b!= '\n'){
      printf("Wrong input\n");
      empty_buffer(); 
      }
    } while (direction != 'd' && direction != 's' && direction != 'q' && direction != 'z' ||  scan != 2 || b!= '\n');
    
    numMovements++; // increment the movements ( used to calculate the points at the end of the round);

    int idRobot = choice[0];
    int numTarget = choice[1];

    Position posRobot = searchRobot(grid, size, idRobot); // give the position of the choosen robot
    Position posTarget = searchTarget(grid, size, numTarget); // give the position of the choosen target
    Position previousPosRobot = posRobot; // previous position of the robot
    for (int i = 0; i < size; i++){ // loop compared to the size of the grid (just to loop since in all cases the loop in most cases breaks before the end of it)
      int clear = system("clear");
      clearScreen(clear);
      move(grid, posRobot, idRobot, direction);
      displayGrid(grid, size,r,maxRound,choice,artStyle);
      usleep(80000);
      posRobot = searchRobot(grid, size, idRobot);
      if (posRobot.x == posTarget.x && posRobot.y == posTarget.y) {
        target = 1;
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
  pointsCalculator(numMovements, target, player, nbPlayers, minMovementsPlayers,minIndex);

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
