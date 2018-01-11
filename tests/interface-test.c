#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void loadTest (char *const fpath) {
  int fd = open(fpath, O_RDONLY);
  if (fd < 0)
    exit(-1);

  char test[2048];
  size_t test_size = read(fd, test, sizeof(test));
  printf("foobar");
  printf("%s", test);
}

int main(int argc, char **argv) {
  loadTest("example.yaml"); 
}
