#include <stdio.h>
#include <stdlib.h>

#include "utilities.h"

void empty_buffer() { // Prevent user from entering multiple characters in scanf
int ch = 0;
    while ((ch =getchar()) != '\n' && ch != EOF) {
  }
}

void clearScreen(int clear){ // Verification of system("clear")
    if (clear == -1) {
        perror("system clear failed");
    }
}
