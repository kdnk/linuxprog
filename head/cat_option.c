#include <stdio.h>
#include <stdlib.h>

#define _GNU_SOURCE
#include <getopt.h>

static void do_cat(FILE *f, char opt);

int
main(int argc, char *argv[])
{
  struct option longopts[] = {
  };

  int n;
  char opt;
  while((n = getopt_long(argc, argv, "tn", longopts, NULL)) != -1) {
    switch(n) {
      case 't':
        opt = 't';
        break;
      case 'n':
        opt = 'n';
        break;
      case '?':
        exit(1);
    }
  }
  FILE *f;
  int i;
  if (optind == argc) {
    do_cat(stdin, opt);
  } else {
    for (i = optind; i < argc; i++) {
      f = fopen(argv[i], "r");
      do_cat(f, opt);
      fclose(f);
    }
  }
  exit(0);
}

static void
do_cat(FILE *f, char opt)
{
  int c;
  while ((c = fgetc(f)) != -1) {
    if (opt == 't') {
      if (c == '\t') {
        if (fputs("\\n", stdout) == EOF) exit(1);
      }
    } else if (opt == 'n') {
      if (c == '\n') {
        if (fputs("$\n", stdout) == EOF) exit(1);
      }
    }
    if (fputc(c, stdout) < 0) exit(1);
  }
  exit(0);
}
