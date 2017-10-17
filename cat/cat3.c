#include <stdio.h>
#include <stdlib.h>

static void do_cat(FILE *file);

int
main(int argc, char *argv[])
{
  if (argc == 1) {
    perror(argv[1]);
    exit(1);
  } else {
    int i;

    for (i = 1; i < argc; i++) {
      FILE *file = fopen(argv[i], "r");
      if (file == NULL) {
        perror(argv[i]);
        exit(1);
      }
      do_cat(file);
      fclose(file);
    }
  }

}

static void
do_cat(FILE *file)
{
  int c;

  while ((c = fgetc(file)) != EOF) {
    if (c == '\t') {
      if (fputs("\\t", stdout) == EOF) exit(1);
    } else if (c == '\n') {
      if (fputs("$\n", stdout) == EOF) exit(1);
    } else {
      if (putchar(c) == EOF) exit(1);
    }
  }
}
