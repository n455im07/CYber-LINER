#ifndef MENU_H
#define MENU_H

#include "struct.h"

void setup(int ,int , int );
void moveUser(int **, UserPosition *, char );
void printMenu(int **);
int** createMenu(UserPosition );
void displaySelection(int** , UserPosition , int , int , int );
void useMenu();

#endif /* MENU_H */