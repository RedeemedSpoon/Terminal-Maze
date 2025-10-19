#include "game.h"
#include <stdlib.h>
#include <time.h>

Seed generate_seed(void) {
  time_t current_time = time(NULL);
  srand((Seed)current_time);
  return rand();
}

Maze generate_maze(Seed seed);
