enum error_code
{
  // input
  ERROR_INVALID_SOURCE_FILE,

  // output
  ERROR_INVALID_OUTPUT_FILE,

  // tokenizer
  ERROR_UNKNOWN_IDENTIFIER,

  ERROR_EXPECTED_NUMBER,
  ERROR_EXPECTED_IDENTIFIER
};

void set_error_filename(const char* filename);
void set_error_line(unsigned int line);

void error(enum error_code code, const char* detail);