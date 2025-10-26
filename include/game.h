#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define VERSION "0.0.1"
#define MAX_HEIGHT 256
#define MAX_WIDTH 512
#define PLAYER_SYMBOL "●"
#define GOAL_SYMBOL "⊛"

typedef enum { 
  PLAYING = 0,
  EXITED = 1, 
} GameState;

typedef enum { 
  NORTH = 1,
  SOUTH = 2,
  EAST = 4,
  WEST = 8
} Direction;

typedef enum {
  RED = 1,
  BLUE = 2,
  GREEN = 3,
  YELLOW = 4,
  MAGENTA = 5,
  CYAN = 6,
  WHITE = 7,
  RESET = 0
} Color;

typedef struct {
  unsigned short x, y;
} Position;

typedef struct {
  bool visited;
  unsigned short walls;
  Direction walk_direction;
} Cell;

typedef struct {
  Cell *cell;
  short x, y;
} CellPosition;

typedef Cell **Maze;

typedef signed short Shr;

typedef unsigned long Seed;

typedef unsigned short Coordinate;

typedef struct {
  Seed seed;
  Coordinate width;
  Coordinate height;
  Color color;
  bool has_trail;
} Config;

Position parse_window(char *window, Position window_size);
Config parse_args(int argc, char *argv[]);
Color parse_color(char *color);
Seed parse_seed(char *seed);

void free_maze(Maze maze, Coordinate height);
Position get_terminal_size(void);
void signal_handler(int signal);
void print_help(void);

Seed generate_seed(void);
Maze generate_maze(Seed seed, Coordinate width, Coordinate height);

void draw_maze(Maze maze, Coordinate width, Coordinate height);
void update_maze(Maze maze, Position *position, Direction direction);
void start_game(Maze maze, Config config, GameState *state);

#endif
