#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define VERSION "0.0.1"
#define MAX_HEIGHT 256
#define MAX_WIDTH 512

typedef enum { 
  PLAYING = 0, 
  WON = 1, 
  EXITED = 2
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
  unsigned char walls;
  Direction walk_direction;
} Cell;

typedef Cell **Maze;

typedef unsigned long Seed;

typedef unsigned short Coordinate;

typedef struct {
  Seed seed;
  Coordinate width;
  Coordinate height;
  Color color;
  bool has_trail;
} Config;

Config parse_args(int argc, char *argv[]);
Position parse_window(char *window, Position window_size);
Color parse_color(char *color);
Seed parse_seed(char *seed);

void free_maze(Maze maze, Coordinate height);
Position get_terminal_size(void);
void signal_handler(int signal);
void print_help(void);

Seed generate_seed(void);
Maze generate_maze(Seed seed, Coordinate width, Coordinate height);

void listen_inputs(void);
void draw_maze(Maze maze);
void update_maze(Maze maze, Position position, Direction direction);

void start_game(Maze maze, GameState *state);
void win_game(GameState *state);
void exit_game(GameState *state);
void replay_game(GameState *state);

#endif
