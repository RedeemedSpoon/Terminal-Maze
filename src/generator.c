#include "game.h"
#include <stdlib.h>

static Direction get_opp_direction(Direction dir) {
  switch (dir) {
  case NORTH:
    return SOUTH;
  case SOUTH:
    return NORTH;
  case EAST:
    return WEST;
  case WEST:
    return EAST;
  default:
    return 0;
  }
}

Maze generate_maze(Seed seed, Coordinate width, Coordinate height) {
  Maze maze = malloc(height * sizeof(Cell *));
  for (int y = 0; y < height; y++) {
    maze[y] = malloc(width * sizeof(Cell));
    for (int x = 0; x < width; x++) {
      maze[y][x].walls = NORTH | SOUTH | EAST | WEST;
      maze[y][x].visited = false;
      maze[y][x].walk_direction = 0;
    }
  }

  srand(seed);

  int start_x = rand() % width;
  int start_y = rand() % height;
  maze[start_y][start_x].visited = true;

  int remaining = (width * height) - 1;

  // This code uses Wilson's algorithm to generate a random maze.
  while (remaining > 0) {
    int walk_start_x, walk_start_y;
    bool found_not_visited = false;

    while (!found_not_visited) {
      walk_start_x = rand() % width;
      walk_start_y = rand() % height;
      if (!maze[walk_start_y][walk_start_x].visited) {
        found_not_visited = true;
      }
    }

    int current_x = walk_start_x;
    int current_y = walk_start_y;

    while (!maze[current_y][current_x].visited) {
      Direction directions[] = {NORTH, SOUTH, EAST, WEST};
      Direction dir = directions[rand() % 4];

      int next_x = current_x;
      int next_y = current_y;

      if (dir == NORTH && current_y > 0)
        next_y--;
      else if (dir == SOUTH && current_y < height - 1)
        next_y++;
      else if (dir == EAST && current_x < width - 1)
        next_x++;
      else if (dir == WEST && current_x > 0)
        next_x--;
      else {
        continue;
      }

      maze[current_y][current_x].walk_direction = dir;
      current_x = next_x;
      current_y = next_y;
    }

    current_x = walk_start_x;
    current_y = walk_start_y;
    while (!maze[current_y][current_x].visited) {
      maze[current_y][current_x].visited = true;
      remaining--;

      Direction dir = maze[current_y][current_x].walk_direction;

      int next_x = current_x;
      int next_y = current_y;

      if (dir == NORTH)
        next_y--;
      else if (dir == SOUTH)
        next_y++;
      else if (dir == EAST)
        next_x++;
      else if (dir == WEST)
        next_x--;

      maze[current_y][current_x].walls &= ~dir;
      maze[next_y][next_x].walls &= ~get_opp_direction(dir);

      current_x = next_x;
      current_y = next_y;
    }
  }

  return maze;
}
