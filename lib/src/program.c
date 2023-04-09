#include "../sed-pcre.h"

Program parse_program(char *program_string) {
  Program program_val;
  while (*program_string != '\0') {
    // do interesting things
    program_string++;
  }
  program_val.func = SUBSTITUTE;
  return program_val;
}
