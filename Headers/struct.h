#ifndef STRUCT_H
#define STRUCT_H

#define MAX_PLAYERS 6
#define MAX_GRID_SIZE 22
#define MIN_GRID_SIZE 16
#define GRID_SIZE 22


/* STRUCTURES CREATION */

typedef struct {
    int x;
    int y;
} UserPosition; // In the menu

typedef struct {
  int x;
  int y;
} Position;

typedef struct {
  int id;    // Each player id
  int score; // Count the player score
} Player;

typedef struct {
  int id;            // Each robot id 1-4
  Position position; // Coordinate of the robot
} Robot;

typedef struct {
  int type; // 0 = No wall | 1 = Bottom | 2 = left | 3 = right | 4 = Top
} Wall;

typedef struct {
  Wall wall;         // Wall type
  Robot robot;       // Robot who occupies the box
  int target;        // Occupied by a Target !=0 ; No target = 0
  int angle;
  Position position; // Coordinate of the box
} Box;

#endif /* STRUCT_H */