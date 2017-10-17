#include <stdio.h>
#include <stdlib.h>

static void do_count(FILE *file);

int
main(int argc, char const *argv[]) {
  if (argc == 1) {
    perror(argv[1]);
    exit(1);
  }

  int i;

  for (i = 1; i < argc; i++) {
    FILE *file = fopen(argv[i], "r");
    if (file == NULL) {
      perror(argv[i]);
      exit(1);
    }
    do_count(file);
    fclose(file);
  }
}

static void
do_count(FILE *file)
{
  int c;
  int count = 0;
  int prev = '\n';

  while((c = fgetc(file)) != EOF) {
    if (c == '\n') {
      count++;
    }
    prev = c;
  }
  if (prev != '\n') {
    count++;
  }
  printf("line_count = %d\n", count);
}
