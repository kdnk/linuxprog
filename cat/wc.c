#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define BUFFER_SIZE 2048

void count_new_line(const char *path, int *line);

int
main(int argc, char *argv[])
{
  if (argc != 2) {
    exit(1);
  }
  int line_number = 0;
  count_new_line(argv[1], &line_number);
  printf("line_number = %d\n", line_number);
  return 0;
}

void
count_new_line(const char *path, int *line_number)
{
  int fd;
  char buf[BUFFER_SIZE];
  int n;
  long i;

  fd = open(path, O_RDONLY);
  if (fd < 0) exit(1);
  for (;;) {
    n = read(fd, buf, sizeof(buf));
    if (n == 0) break;
    if (n < 0) exit(1);
    for (i = 0; i < BUFFER_SIZE; i++) {
      if (buf[i] == '\n') {
        *line_number = *line_number + 1;
      }
    }
    // if (write(STDOUT_FILENO, buf, sizeof(buf)) < 0) exit(1);
  }
}
