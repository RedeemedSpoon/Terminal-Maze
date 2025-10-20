#include "game.h"

void start_game(Maze maze, GameState *state) {
  (void)maze;
  *state = EXITED;
}

void win_game(GameState *state);

void exit_game(GameState *state);

void replay_game(GameState *state);
