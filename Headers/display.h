#ifndef DISPLAY_H
#define DISPLAY_H

#include "struct.h"

void displayWinner(Player *, int);
void displayRobot(int,int);
void displayGrid(Box **, int,int,int,int*,int);
void displayWall(Box **, int, int);
void displayTarget(int);
void displayColor(int);
void displayWinner(Player *, int);
void displayOccupiedWall(Box **, int , int );
void displayCountdown(int, Box **, int, int, int, int *,int);

#endif /* DISPLAY_H */