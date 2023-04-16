#include <stddef.h>

#include "../psed.h"

typedef enum {
  FUNC,
  PATTERN,
  REPLACEMENT,
} ParserPhase;

OptionalProgram parse_program(char *program_string) {
  Program program = {
      .func = SUBSTITUTE,
      .pattern = NULL,
      .replacement = NULL,
  };
  ParserPhase phase = FUNC;
  while (*program_string != '\0') {
    char current = *program_string;
    switch (phase) {
    case FUNC:
      switch (current) {
        case 's':
          program.func = SUBSTITUTE;
          break;
        default:
          return (OptionalProgram) {
            .val = {.error = "Whoops"},
            .has_program = false,
          };
      }
      break;
    case PATTERN:
      break;
    case REPLACEMENT:
      break;
    }
    // do interesting things
    program_string++;
  }
  return (OptionalProgram) {
    .val = {program},
    .has_program = true,
  };
}
