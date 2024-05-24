#ifndef SEARCH_H
#define SEARCH_H

#include "struct.h"

int isValid(Position, Box **, int, int );
Position searchRobot(Box**, int, int);
Position searchTarget(Box**, int, int);
int searchDistance(Box **, int, Position, int);

#endif /* SEARCH_H */