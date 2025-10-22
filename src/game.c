#include "game.h"
#include <stdio.h>

void start_game(Maze maze, Config config, GameState *state) {
  (void)maze;
  (void)config;
  *state = EXITED;
}

void win_game(GameState *state);

void exit_game(GameState *state);

void replay_game(GameState *state);
