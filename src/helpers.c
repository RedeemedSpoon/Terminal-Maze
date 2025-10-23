#include "game.h"
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

Seed generate_seed(void) {
  Seed current_time = time(NULL);
  return current_time;
}

Position get_terminal_size(void) {
  struct winsize ws;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
  Position size = {.x = ws.ws_col, .y = ws.ws_row};
  return size;
}

void signal_handler(int sig) {
  switch (sig) {
  case SIGSEGV:
    fprintf(stderr, "Caught segmentation fault (SIGSEGV)!\n");
    break;
  case SIGFPE:
    fprintf(stderr, "Caught floating-point error (e.g., division by zero)!\n");
    break;
  case SIGABRT:
    fprintf(stderr, "Caught abort signal (SIGABRT)!\n");
    break;
  default:
    fprintf(stderr, "Caught unknown signal: %d\n", sig);
  }

  exit(1);
}

void print_help(void) {
  const int alignment_width = -30;
  printf("Usage: maze [options]\n\n");
  printf("Options:\n");

  printf("  %*s  Show this help message and exit.\n", alignment_width,
         "-h, --help");
  printf("  %*s  Show the program's version number and exit.\n",
         alignment_width, "-v, --version");
  printf("  %*s  Set the maze path color (e.g., RED, BLUE).\n", alignment_width,
         "-c, --color <COLOR>");
  printf("  %*s  Set the seed for random maze generation.\n", alignment_width,
         "-s, --seed <SEED>");
  printf("  %*s  Set the maze dimensions (e.g., 80x25).\n", alignment_width,
         "-w, --window <WIDTHxHEIGHT>");
  printf("  %*s  Enable a trail showing the player's path.\n", alignment_width,
         "-t, --trail");
}

void free_maze(Maze maze, Coordinate height) {
  for (int y = 0; y < height; y++) free(maze[y]);
  free(maze);
}
