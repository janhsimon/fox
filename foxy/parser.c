#include <stdio.h>
#include <stdlib.h> // for malloc

#include "error.h"

FILE* file;

char* parse_source_file(const char* filename)
{
  file = fopen(filename, "r");

  if (file == NULL)
  {
    error(ERROR_INVALID_SOURCE_FILE, filename);
    return 0;
  }

  char* src = malloc(256 * 256 + 2);
  size_t size = fread(src, 1, 256 * 256, file);
  fclose(file);
  
  src[size] = '\n';
  src[size + 1] = 0;

  return src;
}