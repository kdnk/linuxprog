#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(stderr, "%s: file name not given\n", argv[0]);
  }
  int i;
  for (i = 1; i < argc; i++) {
    FILE *file;
    int c;
    char *path = argv[i];
    file = fopen(path, "r");
    if (file == NULL) exit(1);
    while ((c = fgetc(file)) != EOF) {
      if (putchar(c) == EOF) exit(1);
    }
    fclose(file);
  }
  exit(0);
}
