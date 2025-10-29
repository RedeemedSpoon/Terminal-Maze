#include "game.h"
#include <ctype.h>
#include <locale.h>
#include <ncurses.h>

static void win(GameState *state) {
  int screen_h, screen_w;
  getmaxyx(stdscr, screen_h, screen_w);

  int win_h = 14;
  int win_w = 53;
  int start_y = (screen_h - win_h) / 2;
  int start_x = (screen_w - win_w) / 2;

  WINDOW *win_box = newwin(win_h, win_w, start_y, start_x);
  box(win_box, 0, 0);

  mvwprintw(win_box, 2, 4, " _     _              _  _  _             _ ");
  mvwprintw(win_box, 3, 4, "| |   | |            | || || |           | |");
  mvwprintw(win_box, 4, 4, "| |___| |__  _   _   | || || | ___  ____ | |");
  mvwprintw(win_box, 5, 4, " \\_____/ _ \\| | | |  | ||_|| |/ _ \\|  _ \\|_|");
  mvwprintw(win_box, 6, 4, "   ___| |_| | |_| |  | |___| | |_| | | | |_ ");
  mvwprintw(win_box, 7, 4, "  (___)\\___/ \\____|   \\______|\\___/|_| |_|_|");

  mvwprintw(win_box, 10, 9, "[ Quit (q) ]      [ Restart (r) ]");
  wrefresh(win_box);

  int choice;
  while (true) {
    choice = tolower(getch());
    if (choice == 'r' || choice == 'q') {
      if (choice == 'q')
        *state = EXITED;
      break;
    }
  }

  delwin(win_box);
}

static void init_ncurses(int color) {
  setlocale(LC_ALL, "en_US.UTF-8");
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);

  start_color();
  use_default_colors();
  init_pair(1, -1, 236);
  init_pair(2, color, -1);
}

void start_game(Maze maze, Config config, GameState *state) {
  Position position = {.y = config.height - 1, .x = 0};
  int ch = 0;

  init_ncurses(config.color);
  draw_maze(maze, config);

  while (*state == PLAYING) {
    switch (tolower(ch = getch())) {
    case 'w':
    case KEY_UP:
      update_maze(maze, &position, NORTH);
      break;

    case 's':
    case KEY_DOWN:
      update_maze(maze, &position, SOUTH);
      break;

    case 'a':
    case KEY_LEFT:
      update_maze(maze, &position, WEST);
      break;

    case 'd':
    case KEY_RIGHT:
      update_maze(maze, &position, EAST);
      break;

    case 'q':
      *state = EXITED;
      break;
    }

    if (position.x == config.width - 1 && !position.y) {
      win(state);
      break;
    }

    refresh();
  }

  endwin();
}
