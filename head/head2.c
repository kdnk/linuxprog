#include <stdio.h>
#include <stdlib.h>

static void do_head(FILE *f, long nlines);

int
main(int argc, char const *argv[]) {
  long nlines = atol(argv[1]);
  if (argc == 2) {
    do_head(stdin, nlines);
  } else {
    int i;
    for (i = 2; i < argc; i++) {
      FILE *f = fopen(argv[i], "r");
      if (f < 0) exit(1);
      do_head(f, nlines);
      fclose(f);
    }
  }
}

static void
do_head(FILE *f, long nlines) {
  int c;
  long count = nlines;
  for (;;) {
    if ((c = fgetc(f)) == EOF) exit(1);
    if (fputc(c, stdout) == EOF) exit(1);
    if (c == '\n') {
      count--;
    }
    if (count == 0) {
      exit(0);
    }
  }
}
