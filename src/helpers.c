#include "game.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

Position get_terminal_size(void);

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
