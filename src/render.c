#include "game.h"
#include <ncurses.h>

const char *WALLS = "═║╔╗╚╝╦╩╠╣╬";
typedef signed short Shr;

static int match_nearby_walls(Maze maze, Shr y, Shr x, Shr width, Shr height) {
  Shr connections = 0;
  if (y > 0 && y <= height && x > 0 && x <= width) {
    if (maze[y - 1][x - 1].walls & EAST)
      connections |= NORTH;
    if (maze[y][x - 1].walls & EAST)
      connections |= SOUTH;
    if (maze[y - 1][x - 1].walls & SOUTH)
      connections |= WEST;
    if (maze[y - 1][x].walls & SOUTH)
      connections |= EAST;
  }

  int vertical_connections = 0;
  if (connections & NORTH) vertical_connections++;
  if (connections & SOUTH) vertical_connections++;

  int horizontal_connections = 0;
  if (connections & WEST) horizontal_connections++;
  if (connections & EAST) horizontal_connections++;

  if (vertical_connections > horizontal_connections) {
    return 1; // '║'
  } else {
    return 0; // '═'
  }
}

static int get_wall_index(Maze maze, Shr y, Shr x, Shr width, Shr height) {
  Shr connections = 0;

  if (y == 0 && x == 0) {
    connections = SOUTH | EAST;
  } else if (y == 0 && x == width) {
    connections = SOUTH | WEST;
  } else if (y == height && x == 0) {
    connections = NORTH | EAST;
  } else if (y == height && x == width) {
    connections = NORTH | WEST;
  } else if (y == 0) {
    connections = WEST | EAST;
    if (maze[0][x - 1].walls & EAST)
      connections |= SOUTH;
  } else if (y == height) {
    connections = WEST | EAST;
    if (maze[height - 1][x - 1].walls & EAST)
      connections |= NORTH;
  } else if (x == 0) {
    connections = NORTH | SOUTH;
    if (maze[y - 1][0].walls & SOUTH)
      connections |= EAST;
  } else if (x == width) {
    connections = NORTH | SOUTH;
    if (maze[y - 1][width - 1].walls & SOUTH)
      connections |= WEST;
  } else {
    if (maze[y - 1][x - 1].walls & EAST)
      connections |= NORTH;
    if (maze[y][x - 1].walls & EAST)
      connections |= SOUTH;
    if (maze[y - 1][x - 1].walls & SOUTH)
      connections |= WEST;
    if (maze[y - 1][x].walls & SOUTH)
      connections |= EAST;
  }

  switch (connections) {
  case WEST | EAST:
    return 0; // ═
  case NORTH | SOUTH:
    return 1; // ║
  case SOUTH | EAST:
    return 2; // ╔
  case SOUTH | WEST:
    return 3; // ╗
  case NORTH | EAST:
    return 4; // ╚
  case NORTH | WEST:
    return 5; // ╝
  case SOUTH | WEST | EAST:
    return 6; // ╦
  case NORTH | WEST | EAST:
    return 7; // ╩
  case NORTH | SOUTH | EAST:
    return 8; // ╠
  case NORTH | SOUTH | WEST:
    return 9; // ╣
  case NORTH | SOUTH | WEST | EAST:
    return 10; // ╬
  default:
    return match_nearby_walls(maze, y, x, width, height);
  }
}

void draw_maze(Maze maze, Coordinate width, Coordinate height) {
  for (int y = 0; y <= height; y++) {
    for (int x = 0; x <= width; x++) {
      int wall_index = get_wall_index(maze, y, x, width, height);
      printw("%.3s", &WALLS[wall_index * 3]);

      if (x < width) {
        bool is_internal_row = (y > 0 && y < height);
        bool has_wall = is_internal_row ? (maze[y - 1][x].walls & SOUTH) : true;

        printw(has_wall ? "═══" : "   ");
      }
    }
    printw("\n");

    if (y < height) {
      for (int x = 0; x < width; x++) {
        bool vertical_wall_left = (x == 0) || (maze[y][x - 1].walls & EAST);
        printw(vertical_wall_left ? "║   " : "    ");
      }
      printw("║\n");
    }
  }
}

void update_maze(Maze maze, Position *position, Direction direction) {
  (void)maze;
  (void)position;
  (void)direction;
}
