#ifndef PSED_H
#define PSED_H

static const int ERR_CODE = 42;

/// The function this program should operate with.
///
/// Only substitute is implemented.
typedef enum {
  /// Substitute pattern matches for a replacement string.
  ///
  SUBSTITUTE
} ProgramFunction;

typedef struct {
  ProgramFunction func;
  char *pattern;
  char *replacement;
} Program;

//typedef struct {
//  Program program;
//}

Program parse_program(char *contents);

void usage(void);

#endif
