#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>

static void do_grep(regex_t *pat, FILE *f);

int
main(int argc, char *argv[])
{
  if (argc < 2) {
    perror(argv[1]);
    exit(1);
  }
  regex_t pat;
  int error = regcomp(&pat, argv[1], REG_EXTENDED);
  if (error != 0) {
    char errbuf[1024];
    regerror(error, &pat, errbuf, sizeof errbuf);
    puts(errbuf);
    exit(1);
  }

  if (argc == 2) {
    do_grep(&pat, stdin);
  } else {
    int i;
    for (i = 2; i < argc; i++) {
      FILE *f;
      f = fopen(argv[i], "r");
      do_grep(&pat, f);
      fclose(f);
    }
  }
  regfree(&pat);
  exit(0);
}

static void
do_grep(regex_t *pat, FILE *f)
{
  char buf[2048];
  while (fgets(buf, sizeof buf, f) != NULL) {
    if (regexec(pat, buf, 0, NULL, 0) == 0) {
      fputs(buf, stdout);
    }
  }
}
