#include <stdio.h>
#include <stdlib.h>

#define _GNU_SOURCE
#include <getopt.h>

#define DEFAULT_T_LINES 10

static void do_head(FILE *f, long nlines);

int
main(int argc, char *argv[])
{
  struct option longopts[] = {
    {"lines", required_argument, NULL, 'n'},
    {"help", no_argument, NULL, 'h'},
    {0, 0, 0, 0}
  };

  int opt;
  long nlines = DEFAULT_T_LINES;
  while ((opt = getopt_long(argc, argv, "hn:", longopts, NULL)) != -1) {
    switch(opt) {
      case 'n':
        nlines = atol(optarg);
        break;
      case 'h':
        fprintf(stdout, "Usage %s [-n LINES] [FILE ...]\n", argv[0]);
        exit(0);
      case '?':
        fprintf(stderr, "Usage %s [-n LINES] [FILE ...]\n", argv[0]);
        exit(1);
    }
  }

  if (optind == argc) {
    do_head(stdin, nlines);
  } else {
    int i;
    FILE *f;
    for (i = optind; i < argc; i++) {
      f = fopen(argv[i], "r");
      if (f < 0) {
        perror(argv[i]);
        exit(1);
      }
      do_head(f, nlines);
      fclose(f);
    }
  }
  exit(0);
}

static void
do_head(FILE *f, long nlines)
{
  int n;
  long count = nlines;
  while (count > 0) {
    if ((n = fgetc(f)) < 0) exit(1);
    if (fputc(n, stdout) < 0) exit(1);
    if (n == '\n') {
      count--;
    }
  }
  return;
}
