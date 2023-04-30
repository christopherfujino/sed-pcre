#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../psed.h"

typedef enum {
  FUNC,
  PATTERN,
  REPLACEMENT,
} ParserPhase;

EitherProgram parse_program(char *program_string) {
  Program program = {
      .func = SUBSTITUTE,
      .pattern = NULL,
      .replacement = NULL,
  };
  size_t pattern_buffer_len = 20;
  char *pattern_buffer = malloc(pattern_buffer_len);
  int pattern_buffer_idx = 0;

  ParserPhase phase = FUNC;
  while (*program_string != '\0') {
    char current = *program_string;
    switch (phase) {
    case FUNC:
      switch (current) {
        case 's':
          program.func = SUBSTITUTE;
          program_string++;
          if (*program_string != '/') {
            return (EitherProgram) {
              .val = {.error = "Expected a '/' char"},
              .has_error = true,
            };
          }
          program_string++;
          phase = PATTERN;
          break;
        default:
          return (EitherProgram) {
            .val = {.error = "Unknown function"},
            .has_error = true,
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
  return (EitherProgram) {
    .val = {program},
    .has_error = false,
  };
}
