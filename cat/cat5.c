#include <stdio.h>
#include <stdlib.h>

static void do_cat(FILE *file);

int
main(int argc, char const *argv[]) {
  if (argc == 1) {
    perror(argv[1]);
    exit(1);
  }

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
  return 0;
}


#define BUFFER_SIZE 2048

static void
do_cat(FILE *file)
{
  char buf[BUFFER_SIZE];

  for (;;) {
    size_t n_read = fread(buf, 1, sizeof(buf), file);
    if (ferror(file) > 0) exit(1);
    size_t n_written = fwrite(buf, 1, n_read, stdout);
    if (n_written < n_read) exit(1);
    if (n_read < sizeof(buf)) break;
  }

  return;
}
