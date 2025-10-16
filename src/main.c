#include "game.h"
#include <signal.h>

int main(int argc, char **argv) {
  signal(SIGSEGV, signal_handler);
  signal(SIGFPE, signal_handler);
  signal(SIGABRT, signal_handler);

  GameState game_state = PLAYING;
  Config config = {0};
  Maze maze;

  while (game_state == PLAYING) {
    config = config.seed ? config : parse_args(argc, argv);
    maze = generate_maze(config.seed);
    start_game(&maze);
  }

  return 0;
}
