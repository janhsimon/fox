#include "fileio.h"
#include "args.h"

#include <stdlib.h>

char *read_source_file(const char *filename)
{
  // Open the source file and check for errors
  FILE *file = fopen(filename, "r");
  if (file == 0)
  {
    printf("%s: no such file or directory\n", filename);
    return 0;
  }

  // Determine the number of bytes in the source file
  fseek(file, 0, SEEK_END);
  const size_t size = ftell(file);
  rewind(file);

  // Copy the entire contents of the source file into a buffer
  char *source = malloc(size + 2);
  fread(source, size, 1, file);
  fclose(file);

  // Append line break and null-termination
  source[size] = '\n';
  source[size + 1] = 0;

  return source;
}

char *source_to_output_filename(const char *filename)
{
  const char *i = filename;
  while (*i != 0 && *i != '.')
  {
    ++i;
  }

  int len = i - filename;
  char *output_filename = malloc(len + 2);

  for (int j = 0; j < len; ++j)
  {
    output_filename[j] = filename[j];
  }

  output_filename[len + 0] = '.';
  output_filename[len + 1] = (get_output() == OUTPUT_EXECUTABLE ? 'o' : 's');
  output_filename[len + 2] = 0;

  return output_filename;
}

FILE *open_output_file(const char *filename)
{
  // Open the output file and check for errors
  FILE *file = fopen(filename, "w");
  if (file == 0)
  {
    printf("%s: failed to open file for output\n", filename);
    return 0;
  }

  return file;
}