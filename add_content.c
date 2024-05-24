#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "add_content.h"

void addTargets(Box **grid, int size, int nbTargets)
{ // Add all targets on the grid
  int n = 1;
  if (grid == NULL)
  { // Verify if memory has been allocated
    printf("Error: grid malloc failed #1\n");
    exit(1);
  }
  if (nbTargets < 1 || nbTargets > 18)
  {
    exit(1);
  }
  while (nbTargets + 1 > n)
  {                                  // Loop until all targets are added
    int x = rand() % (size - 4) + 2; // Generate random x coordinate
    int y = rand() % (size - 4) + 2; // Generate random y coordinate
    if (grid[x][y].target == 0 && grid[x - 1][y].target == 0 &&
        grid[x + 1][y].target == 0 && grid[x][y - 1].target == 0 &&
        grid[x][y + 1].target == 0 && grid[x - 1][y - 1].target == 0 &&
        grid[x - 1][y + 1].target == 0 && grid[x + 1][y - 1].target == 0 &&
        grid[x + 1][y + 1].target == 0)
    {                           // Verify if there's no target arround the coordinate (x,y) we generated
      grid[x][y].target = n;    // Put the number of the target if there's no target arround the coordinate
      int c = rand() % (4) + 1; // Generate random number (1-4)
      switch (c)
      {       // Put random generated wall arround each target
      case 1: // Add wall in the top left corner
        grid[x - 1][y].wall.type = 1;
        grid[x][y - 1].wall.type = 3;
        grid[x][y].angle=1;
        break;
      case 2: // Add wall in the top right corner
        grid[x - 1][y].wall.type = 1;
        grid[x][y + 1].wall.type = 2;
        grid[x][y].angle=2;
        break;
      case 3: // Add wall in the bottom left corner
        grid[x + 1][y].wall.type = 4;
        grid[x][y - 1].wall.type = 3;
        grid[x][y].angle=4;
        break;
      case 4: // Add wall in the bottom right corner
        grid[x + 1][y].wall.type = 4;
        grid[x][y + 1].wall.type = 2;
        grid[x][y].angle=3;
        break;
      }
      n++;
    }
  }
}

void addRobots(Box **grid, int size)
{ // Generate the 4 robots on the grid and give them their ID between 1 and 4

  if (grid == NULL)
  { // Verify if memory has been allocated
    printf("Error: grid malloc failed #1\n");
    exit(1);
  }
  int n;
  n = 1; // Robot id starts with 1
  while (n < 5)
  {                                  // Loop until all robot are placed
    int x = rand() % (size - 2) + 1; // Generate random x coordinate
    int y = rand() % (size - 2) + 1; // Generate random y coordinate
    if (grid[x][y].target == 0 && grid[x][y].robot.id == 0 &&
        grid[x][y].wall.type == 0)
    { // Verify if there's no target, robot or wall who occupy the box at (x,y)
      grid[x][y].robot.position.x = x;
      grid[x][y].robot.position.y = y;
      grid[x][y].robot.id = n; // Initialize the robot id
      n++;
    }
  }
}

void addSpikes(Box **grid, int size)
{ // Generate the two spikes for each side of the grid
  int n = 0;
  int y = 0;
  int x = 0;
  if (grid == NULL)
  { // Verify if memory has been allocated
    printf("Error: grid malloc failed #1\n");
    exit(1);
  }
  do
  {                              // Add spikes on the top side of the grid
    y = rand() % (size - 2) + 2; // Generate random y coordinate
    if (grid[1][y].wall.type == 0 && y != 1 && y != size - 2 && grid[1][y + 1].wall.type == 0 && grid[1][y - 1].wall.type == 0)
    {
      // Verify if there's no spike on the box,to the left and to the right
      grid[1][y].wall.type = 2; // Place vertical left wall
      n++;
    }
  } while (n < 2); // Loop until two spikes are placed
  n = 0;
  do
  {                              // Add spikes on the bottom side of the grid
    y = rand() % (size - 2) + 2; // Generate random y coordinate
    if (grid[size - 2][y].wall.type == 0 && grid[size - 2][y + 1].wall.type == 0 && grid[size - 2][y - 1].wall.type == 0 && y != 1 && y != size - 2)
    {
      // Verify if there's no spike on the box,to the left and to the right
      grid[size - 2][y].wall.type = 2; // Place vertical left wall
      n++;
    }
  } while (n < 2); // Loop until two spikes are placed
  n = 0;
  do
  {                              // Add spikes on the left side of the grid
    x = rand() % (size - 2) + 2; // Generate random x coordinate
    if (grid[x][1].wall.type == 0 && grid[x + 1][1].wall.type == 0 && grid[x - 1][1].wall.type == 0 && x != 1 && x != size - 2)
    {
      // Verify if there's no spike on the box,just above and under
      grid[x][1].wall.type = 1; // Place horizontal bottom wall
      n++;
    }
  } while (n < 2); // Loop until two spikes are placed
  n = 0;
  do
  {                              // Add spikes on the right side of the grid
    x = rand() % (size - 2) + 2; // Generate random x coordinate
    if (grid[x][size - 2].wall.type == 0 && grid[x + 1][size - 2].wall.type == 0 && grid[x - 1][size - 2].wall.type == 0 && x != 1 && x != size - 2)
    {
      // Verify if there's no spike on the box,just above and under
      grid[x][size - 2].wall.type = 1; // Place horizontal bottom wall
      n++;
    }
  } while (n < 2); // Loop until two spikes are placed
}

void addBoxes(Box **grid, int size)
{ // Create each box within the grid
  if (grid == NULL)
  { // Verify if memory has been allocated
    printf("Error: grid malloc failed #1\n");
    exit(1);
  }
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      if (j == 0)
      {
        grid[i][j] = createBox(3, i, j); // Create walls on the left
      }
      else if (j == size - 1)
      {
        grid[i][j] = createBox(2, i, j); // Create walls on the right
      }
      else if (i == 0)
      {
        grid[i][j] = createBox(1, i, j); // Create walls on the top
      }
      else if (i == size - 1)
      {
        grid[i][j] = createBox(4, i, j); // Create walls on the bottom
      }
      else
      {
        grid[i][j] = createBox(0, i, j); // Create empty boxes
      }
      // Empty all the corners
      grid[0][0].wall.type = 0;
      grid[0][size - 1].wall.type = 0;
      grid[size - 1][0].wall.type = 0;
      grid[size - 1][size - 1].wall.type = 0;
    }
  }
}