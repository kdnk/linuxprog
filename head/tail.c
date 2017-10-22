#include <stdio.h>
#include <stdlib.h>

static long count_newline(char *path);
static void do_tail(char *path, long nlines, long display_lines);

int
main(int argc, char *argv[])
{
  if (argc < 2) {
    perror(argv[0]);
    exit(1);
  } else {
    int i;
    long nlines;
    for (i = 1; i < argc; i++) {
      char *path = argv[i];
      nlines = count_newline(path);
      do_tail(path, nlines, 10);
    }
    exit(0);
  }
}

static long
count_newline(char *path)
{
  long nlines = 0;
  int c;
  FILE *f = fopen(path, "r");
  if (!f) {
    perror(path);
    exit(1);
  }
  while((c = fgetc(f)) != -1) {
    if (c == '\n') {
      nlines += 1;
    }
  }
  fclose(f);
  return nlines;
}

static void
do_tail(char *path, long nlines, long display_lines)
{
  int c;
  long count = 0;
  FILE *f = fopen(path, "r");
  if (!f) {
    perror(path);
    exit(1);
  }
  while((c = fgetc(f)) != -1) {
    if (c == '\n') {
      count++;
    }
    if (nlines <= count + display_lines) {
      fputc(c, stdout);
    }
    if (nlines == count) {
      break;
    }
  }
  fclose(f);
  return;
}
