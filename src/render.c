#include "game.h"
#include <ncurses.h>

static const char *WALLS = "═║╔╗╚╝╦╩╠╣╬";
static bool trail_on = false;
static int start_x = 0;
static int start_y = 0;
static int height = 0;
static int width = 0;

static int match_nearby_walls(Maze maze, Shr y, Shr x) {
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
  if (connections & NORTH)
    vertical_connections++;
  if (connections & SOUTH)
    vertical_connections++;

  int horizontal_connections = 0;
  if (connections & WEST)
    horizontal_connections++;
  if (connections & EAST)
    horizontal_connections++;

  return vertical_connections > horizontal_connections;
}

static int get_wall_index(Maze maze, Shr y, Shr x) {
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
    return match_nearby_walls(maze, y, x);
  }
}

static void set_center_coordinates(Shr width, Shr height) {
  int term_h, term_w;
  getmaxyx(stdscr, term_h, term_w);

  int maze_char_width = (width * 4) + 1;
  int maze_char_height = (height * 2) + 1;

  start_y = (term_h - maze_char_height) / 2;
  start_x = (term_w - maze_char_width) / 2;
}

static void draw_symbol(char symbol[], Shr y, Shr x) {
  int screen_y = start_y + (y * 2) + 1;
  int screen_x = start_x + (x * 4) + 2;

  mvprintw(screen_y, screen_x, "%s", symbol);
}

void draw_maze(Maze maze, Config config) {
  set_center_coordinates(config.width, config.height);
  trail_on = config.has_trail;
  height = config.height;
  width = config.width;
  clear();

  for (int y = 0; y <= height; y++) {
    move(start_y + (y * 2), start_x);

    for (int x = 0; x <= width; x++) {
      int wall_index = get_wall_index(maze, y, x);
      printw("%.3s", &WALLS[wall_index * 3]);

      if (x < width) {
        bool is_internal_row = (y > 0 && y < height);
        bool has_wall = is_internal_row ? (maze[y - 1][x].walls & SOUTH) : true;
        printw(has_wall ? "═══" : "   ");
      }
    }
    printw("\n");

    if (y < height) {
      move(start_y + (y * 2) + 1, start_x);

      for (int x = 0; x < width; x++) {
        bool vertical_wall_left = (x == 0) || (maze[y][x - 1].walls & EAST);
        printw(vertical_wall_left ? "║   " : "    ");
      }
      printw("║\n");
    }
  }

  draw_symbol(GOAL_SYMBOL, 0, width - 1);
  draw_symbol(PLAYER_SYMBOL, height - 1, 0);
}

void update_maze(Maze maze, Position *position, Direction direction) {
  if (trail_on) attron(COLOR_PAIR(1));
  draw_symbol(" ", position->y, position->x);
  if (trail_on) attroff(COLOR_PAIR(1));

  int walls = maze[position->y][position->x].walls;

  switch (direction) {
  case NORTH:
    if (position->y != 0 && walls % 2 != 1) {
      position->y--;
    }
    break;

  case SOUTH:
    if (position->y <= height - 2 && (walls & 2) == 0) {
      position->y++;
    }
    break;

  case EAST:
    if ((walls & 4) == 0) {
      position->x++;
    }
    break;

  case WEST:
    if ((position->x <= (width)) && (walls < 8)) {
      position->x--;
    }
    break;
  }

  draw_symbol(PLAYER_SYMBOL, position->y, position->x);
}
