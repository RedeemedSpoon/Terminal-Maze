#include "game.h"
#include <signal.h>

int main(int argc, char **argv) {
  signal(SIGSEGV, signal_handler);
  signal(SIGFPE, signal_handler);
  signal(SIGABRT, signal_handler);

  GameState game_state = PLAYING;
  Config config;
  Maze maze;

  while (game_state == PLAYING) {
    config = parse_args(argc, argv);
    maze = generate_maze(config.seed, config.width, config.height);
    start_game(maze, config, &game_state);
    free_maze(maze, config.height);
  }

  return 0;
}
