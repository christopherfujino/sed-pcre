#ifndef PSED_H
#define PSED_H

#include <stdbool.h>

static const int ERR_CODE = 42;

/// The function this program should operate with.
///
/// Only substitute is implemented.
typedef enum {
  /// Substitute pattern matches for a replacement string.
  SUBSTITUTE
} ProgramFunction;

/// A sed-like program.
typedef struct {
  ProgramFunction func;
  char *pattern;
  char *replacement;
} Program;

typedef union {
  Program program;
  char* error;
} ProgramOrError;

/// Tagged Union
typedef struct {
  ProgramOrError val;
  bool has_program;
} OptionalProgram;

OptionalProgram parse_program(char *contents);

void usage(void);

#endif
