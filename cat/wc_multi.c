#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define BUFFER_SIZE 2048

static void do_count(int fd, const char *path);

int
main(int argc, char *argv[])
{
  int i;

  if (argc < 2) {
    fprintf(stderr, "%s: file name not given\n", argv[0]);
    exit(1);
  }
  for (i = 1; i < argc; i++) {
    char *path = argv[i];
    int fd = open(path, O_RDONLY);
    do_count(fd, path);
    if (close(fd) < 0) exit(1);
  }
}

static void
do_count(int fd, const char *path)
{
  long count = 0;

  for (;;) {
    char buf[BUFFER_SIZE];
    int n = read(fd, buf, sizeof(buf));
    if (n < 0) exit(1);
    if (n == 0) break;

    long i;
    for (i = 0; i < BUFFER_SIZE; i++) {
      if (buf[i] == '\n') {
        count++;
      }
    }
  }
  printf("count = %ld\n", count);
}
