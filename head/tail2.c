#include <stdio.h>
#include <stdlib.h>

static void tail(FILE *f);

#define N_LINES 10
#define MAX_LINE_LENGTH 1024

int
main(int argc, char const *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s\n", argv[0]);
    exit(1);
  }
  FILE *f = fopen(argv[1], "r");
  tail(f);
  fclose(f);
  exit(0);
}

static char ring_buffer[N_LINES][MAX_LINE_LENGTH];

static void
tail(FILE *f) {
  long curr = 0; // current
  long n_read_lines = 0;
  while (fgets(ring_buffer[curr], MAX_LINE_LENGTH, f) != NULL) {

    curr++;
    if (curr >= N_LINES) {
      curr = 0;
    }

    n_read_lines++;
  }

  if (n_read_lines < N_LINES) {
    curr = 0;
  }

  int n;
  for (n = N_LINES; n > 0; n--) {
    printf("%s", ring_buffer[curr]);

    curr++;
    if (curr >= N_LINES) {
      curr = 0;
    }

  }
}
