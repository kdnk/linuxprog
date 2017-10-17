#include <stdio.h>
#include <stdlib.h>

static void do_head(FILE *f, long nlines);

int
main(int argc, char const *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "%s\n", "Invalid args number.");
    exit(1);
  }
  FILE *f = stdin;
  long nlines = atol(argv[1]);
  do_head(f, nlines);
  exit(0);
}

static void
do_head(FILE *f, long nlines)
{
  long count = nlines;
  for (;;) {
    int c;
    if ((c = fgetc(f)) == EOF) exit(1);
    if (count > 0) {
      if (c != '\n') {
        if (fputc(c, stdout) < 0) exit(1);
      } else {
        if (fputc(c, stdout) < 0) exit(1);
        count--;
      }
    } else {
      exit(0);
    }
  }
}
