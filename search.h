#ifndef SEARCH_H
#define SEARCH_H

#include "struct.h"

Position searchRobot(Box**, int, int);
Position searchTarget(Box**, int, int);
int searchDistance(Box **, int, Position, int);
int isValid(Position position, Box **grid, int type, int type2);

#endif /* SEARCH_H */