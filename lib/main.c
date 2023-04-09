#include <stdio.h>

#include "psed.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    usage();
    return ERR_CODE;
  }
  printf("Success: %s\n", argv[1]);
  return 0;
}
