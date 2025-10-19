#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool arg_matches(char *arg, char *short_form, char *long_form) {
  return strcmp(arg, short_form) == 0 || strcmp(arg, long_form) == 0;
}

Config parse_args(int argc, char *argv[]) {
  Config config = {0};
  Position window_size = get_terminal_size();

  config.color = WHITE;
  config.has_trail = false;
  config.width = window_size.x;
  config.height = window_size.y;
  config.seed = generate_seed();

  for (int i = 1; i < argc; i++) {
    if (arg_matches(argv[i], "-c", "--color")) {
      config.color = parse_color(argv[i + 1]);
      i++;
    }

    else if (arg_matches(argv[i], "-s", "--seed")) {
      config.seed = parse_seed(argv[i + 1]);
      i++;
    }

    else if (arg_matches(argv[i], "-w", "--window")) {
      Position window = parse_window(argv[i + 1], window_size);
      config.width = window.x;
      config.height = window.y;
      i++;
    }

    else if (arg_matches(argv[i], "-t", "--trail")) {
      config.has_trail = true;
    }

    else if (arg_matches(argv[i], "-h", "--help")) {
      print_help();
      exit(0);
    }

    else if (arg_matches(argv[i], "-v", "--version")) {
      printf("version: %s\n", VERSION);
      exit(0);
    }

    else {
      fprintf(stderr, "Unrecognized argument: %s\n", argv[i]);
      exit(1);
    }
  }

  return config;
}
