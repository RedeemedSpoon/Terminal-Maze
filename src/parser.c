#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void check_arg(char *arg, char *message) {
  if (arg == NULL) {
    fprintf(stderr, "Missing argument for %s\n", message);
    exit(1);
  }
}

Position parse_window(char *window, Position window_size) {
  check_arg(window, "-w, --window");

  Position parsed_dims = {0, 0};

  if (sscanf(window, "%hux%hu", &parsed_dims.x, &parsed_dims.y) != 2) {
    fprintf(stderr, "Error: Invalid format for --window: '%s'.\n", window);
    exit(1);
  }

  if (parsed_dims.x == 0 || parsed_dims.y == 0) {
    fprintf(stderr, "Error: Window dimensions must be positive numbers.\n");
    exit(1);
  }

  if (parsed_dims.x > window_size.x || parsed_dims.y > window_size.y) {
    fprintf(stderr, "Error: Window size %hux%hu exceeds window size.\n",
            parsed_dims.x, parsed_dims.y);
    exit(1);
  }

  if (parsed_dims.x > MAX_WIDTH || parsed_dims.y > MAX_HEIGHT) {
    fprintf(stderr, "Error: Window size %hux%hu exceeds maximum size.\n",
            parsed_dims.x, parsed_dims.y);
    exit(1);
  }

  return parsed_dims;
}

Seed parse_seed(char *seed) {
  check_arg(seed, "-s, --seed");

  char *endptr;
  Seed parsed_seed = strtoul(seed, &endptr, 10);

  if (*endptr != '\0') {
    fprintf(stderr, "Error: Invalid seed '%s'. Seed must be a number.\n", seed);
    exit(1);
  }

  return parsed_seed;
}

Color parse_color(char *color) {
  check_arg(color, "-c, --color");

  if (strcasecmp(color, "RED") == 0) return RED;
  if (strcasecmp(color, "BLUE") == 0) return BLUE;
  if (strcasecmp(color, "GREEN") == 0) return GREEN;
  if (strcasecmp(color, "YELLOW") == 0) return YELLOW;
  if (strcasecmp(color, "MAGENTA") == 0) return MAGENTA;
  if (strcasecmp(color, "CYAN") == 0) return CYAN;
  if (strcasecmp(color, "WHITE") == 0) return WHITE;

  fprintf(stderr, "Error: Invalid color '%s'.\n", color);
  fprintf(stderr, "Available colors are: RED, BLUE, GREEN, YELLOW, MAGENTA, CYAN, WHITE.\n");
  exit(1);
}
