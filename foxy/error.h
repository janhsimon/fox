enum error_code
{
  ERROR_COMPILER_UNKNOWN_IDENTIFIER,
  ERROR_COMPILER_EXPECTED_NUMBER,
  ERROR_COMPILER_EXPECTED_IDENTIFIER,
  ERROR_LINKER_INVALID_INPUT_FILE,
  ERROR_LINKER_INVALID_OUTPUT_FILE
};

void set_error_filename(const char *filename);
void set_error_line(unsigned int line);

void error(enum error_code code, const char *detail);