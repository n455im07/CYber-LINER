#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "struct.h"

void pointsCalculator(int, int, Player *, int, int, int);
void countdown(int , Box** , int , int , int ,int *,int);
void move(Box **, Position , int *, int );
void playRound(Box **, Player *, int , int ,int , int *, int , int,int );
void startGame();

#endif /* GAMEPLAY_H */