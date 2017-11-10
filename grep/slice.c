#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>

static void do_grep(FILE *f, regex_t *reg);
static void do_slice(FILE *f, regex_t *reg);

int
main(int argc, char const *argv[]) {

  if (argc < 2) {
    fprintf(stderr, "%s\n", argv[1]);
    exit(1);
  }
  regex_t reg;
  int err = regcomp(&reg, argv[1], REG_EXTENDED);

  if (err != 0) {
    char buf[1024];
    regerror(err, &reg, buf, sizeof(buf));
    fputs(buf, stderr);
    exit(1);
  }

  if (argc == 2) {
    do_grep(stdin, &reg);
  } else {
    int i;
    for (i = 2; i < argc; i++) {
      FILE *f = fopen(argv[i], "r");
      if (!f) {
        perror(argv[i]);
        exit(1);
      }
      do_slice(f, &reg);
      fclose(f);
    }
  }

  regfree(&reg);
}

static void
do_grep(FILE *f, regex_t *reg)
{
  char buf[4096];
  while (fgets(buf, sizeof(buf), f) != NULL) {
    if (regexec(reg, buf, 0, NULL, 0) == 0) {
      fputs(buf, stdout);
    }
  }
}

static void
do_slice(FILE *f, regex_t *reg)
{
  char buf[4096];
  int i, j;
  regmatch_t patternMatch[100];
  int size = sizeof(patternMatch) / sizeof(regmatch_t);
  while(fgets(buf, sizeof(buf), f) != NULL) {
    if (regexec(reg, buf, size, patternMatch, 0) == 0) {
      for (i = 0; i < size; i++) {
        if ((int)patternMatch[i].rm_eo >= 0 && (int)patternMatch[i].rm_so >= 0) {
          printf("%d:%d\n", (int)patternMatch[i].rm_so, (int)patternMatch[i].rm_eo);
          for (j = patternMatch[i].rm_so; j < patternMatch[i].rm_eo; j++) {
            putchar(buf[j]);
          }
          putchar('\n');
        }
      }
    }
  }
}
