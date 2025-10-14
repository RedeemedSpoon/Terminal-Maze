#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <stddef.h>

#define VERSION "0.0.1"
#define DEFAULT_WIDTH 80
#define DEFAULT_HEIGHT 25
#define DEFAULT_COLOR 3

enum Direction { UP, DOWN, LEFT, RIGHT };

enum GameState { PLAYING, WON, EXITED };

enum Color {
  RED = 1,
  BLUE = 2,
  GREEN = 3,
  YELLOW = 4,
  MAGENTA = 5,
  CYAN = 6,
  WHITE = 7,
  RESET = 0
};

typedef unsigned long Seed;

typedef unsigned short Coordinate;

typedef struct position {
  unsigned short x, y;
} Position;

typedef struct cell { } Cell;

typedef struct maze { } Maze;

typedef struct config {
  Seed seed;
  Coordinate width;
  Coordinate height;
  enum Color color;
  bool has_trail;
} Config;

Config parse_args(int argc, char *argv[]);
Position get_terminal_size(void);
void signal_handler(int signal);

Seed generate_seed(void);
Maze generate_maze(Seed seed);

void start_game(Maze *maze);
void draw_maze(Maze *maze);
void listen_inputs(void);
void update_maze(Maze *maze, Position *position, enum Direction direction);

void win_game(void);
void exit_game(void);
void replay_game(void);

// Possible Arg :
// -h | --help
// -v | --version
// -c | --color
// -s | --seed
// -w | --window
// -t | --trail

#endif
