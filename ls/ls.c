#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <dirent.h>

int
main(int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(stderr, "%s: no arguments", argv[0]);
    exit(1);
  }
  int i;
  for (i = 1; i < argc; i++) {
    DIR *d = opendir(argv[i]);
    if (!d) {
      perror(argv[i]);
      exit(1);
    }
    struct dirent *ent;
    while ((ent = readdir(d)) != NULL) {
      printf("%s\n", (*ent).d_name);
    }
    closedir(d);
  }
  exit(0);
}
