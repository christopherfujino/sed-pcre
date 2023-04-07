#include <stdio.h>

const int ERR_CODE = 42;

int main(int argc, char *argv[]) {
  fprintf(stderr, "Yikes!\n");
  return ERR_CODE;
}
