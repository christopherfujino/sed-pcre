#include <stdio.h>

#include "sed-pcre.h"

const int ERR_CODE = 42;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    usage();
    return ERR_CODE;
  }
  printf("Success: %s\n", argv[1]);
  return 0;
}

void usage() {
  fprintf(stderr, "Usage: sed-pcre <PROGRAM>\n");
}
