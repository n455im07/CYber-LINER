#ifndef CREATE_H
#define CREATE_H

#include "struct.h"

Player createPlayer(int);
Robot createRobot();
Wall createWall(int);
Box createBox(int, int, int);
Box **createGrid(int);
Player *createPlayerBoard(int, int);

#endif /* CREATE_H */