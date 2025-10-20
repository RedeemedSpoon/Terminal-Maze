#include "game.h"
#include <stdlib.h>
#include <time.h>

static Seed get_random(Seed seed) {
  srand((Seed)seed);
  return rand();
}

static Seed random_within(Seed *seed, Coordinate max_value) {
  *seed = get_random(*seed);
  return *seed % max_value;
}

Seed generate_seed(void) {
  time_t current_time = time(NULL);
  return get_random(current_time);
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

  int start_y = random_within(&seed, height);
  int start_x = random_within(&seed, width);
  maze[start_y][start_x].visited = true;

  int remaining = width * height - 1;
  while (remaining > 0) {
    // Code goes here
  }

  return maze;
}
