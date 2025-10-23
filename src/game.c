#include "game.h"
#include <ncurses.h>

void start_game(Maze maze, Config config, GameState *state) {
  (void)maze;
  (void)config;
  *state = EXITED;
}
