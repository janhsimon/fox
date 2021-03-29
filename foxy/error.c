#include "error.h"

#include <stdio.h>

struct error_state
{
  const char *filename;
  unsigned int line;
} state;

void set_error_filename(const char *filename)
{
  state.filename = filename;
}

void set_error_line(unsigned int line)
{
  state.line = line;
}

const char *error_code_to_string(enum error_code code)
{
  switch (code)
  {
  case ERROR_COMPILER_UNKNOWN_IDENTIFIER:
    return "unknown identifier";
  case ERROR_COMPILER_EXPECTED_NUMBER:
    return "expected number after";
  case ERROR_COMPILER_EXPECTED_IDENTIFIER:
    return "expected identifier after";
  case ERROR_LINKER_INVALID_INPUT_FILE:
    return "invalid input file for linking";
  case ERROR_LINKER_INVALID_OUTPUT_FILE:
    return "invalid output file for linking";
  default:
    return "";
  }
}

void error(enum error_code code, const char *detail)
{
  if (detail == 0)
  {
    printf("%s(%d) -> error F%04d: %s\n", state.filename, state.line, code, error_code_to_string(code));
  }
  else
  {
    printf("%s(%d) -> error F%04d: %s '%s'\n", state.filename, state.line, code, error_code_to_string(code), detail);
  }
}