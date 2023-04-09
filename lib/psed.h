#ifndef PSED_H
#define PSED_H

static const int ERR_CODE = 42;

typedef enum {
  SUBSTITUTE
} ProgramFunction;

typedef struct {
  ProgramFunction func;
} Program;

Program parse_program(char *contents);

void usage(void);

#endif
