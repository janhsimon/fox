#include "error.h"
#include "parser.h"
#include "tokenizer.h"
#include "writer.h"

#include <stdio.h>  // for printf
#include <stdlib.h> // for malloc
#include <string.h> // for strcmp

enum
{
  PLATFORM_NONE,
  PLATFORM_LINUX_GCC_7_5,
  PLATFORM_WIN_VS_2019
} platform = PLATFORM_NONE;

int main(int argc, char* argv[])
{
  const char* filename;

  char* arg_ignore = malloc((argc - 1) * sizeof(int));

  if (argc < 2) {
    printf("wrong usage: specify at least one source file\n");
    return 1;
  }

  for (int i = 1; i < argc; ++i)
  {
    arg_ignore[i - 1] = 0;
    if (strcmp(argv[i], "-platform") == 0)
    {
      arg_ignore[i - 1] = 1;
      if (i + 1 >= argc)
      {
        break;
      }

      if (strcmp(argv[i + 1], "linux-gcc") == 0)
      {
        platform = PLATFORM_LINUX_GCC_7_5;
        arg_ignore[i] = 1;
        break;
      }
      else if (strcmp(argv[i + 1], "win-vs") == 0)
      {
        platform = PLATFORM_WIN_VS_2019;
        arg_ignore[i] = 1;
        break;
      }
      else
      {
        printf("invalid platform specified: expected linux-gcc or win-vs, got \"%s\"\n", argv[i + 1]);
        return 3;
      }
    }
  }

  if (platform == PLATFORM_NONE)
  {
    printf("no platform specified: set -platform to linux-gcc or win-vs\n");
    return 4;
  }

  for (int i = 1; i < argc; ++i)
  {
    if (arg_ignore[i - 1] == 1)
    {
      continue;
    }

    filename = argv[i];
    set_error_filename(filename);

    printf("%s\n", filename);

    const char* source = parse_source_file(filename);
    if (source == 0) {
      continue;
    }

    struct token* t = tokenize(filename, source);
    if (t == 0) {
      continue;
    }

    const char* output_filename = source_to_output_filename(filename);
    open_output_file(output_filename);

    if (platform == PLATFORM_LINUX_GCC_7_5)
    {
      write_linux_gcc_7_5(t);
    }
    else if (platform == PLATFORM_WIN_VS_2019)
    {
      write_win_vs_2019(t);
    }

    printf("%s -> %s\n", filename, output_filename);
  }

  return 0;
}
