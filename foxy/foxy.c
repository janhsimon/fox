#include "error.h"
#include "parser.h"
#include "tokenizer.h"

#include "assembler.h"

#include <stdio.h>  // for printf
#include <string.h> // for strcmp

enum
{
  PLATFORM_NONE,
  PLATFORM_LINUX_GCC_7_5,
  PLATFORM_WIN_VS_2019
} platform = PLATFORM_NONE;

enum
{
  MODE_COMPILE_ONLY,
  MODE_COMPILE_AND_ASSEMBLE
} mode = MODE_COMPILE_AND_ASSEMBLE;

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("wrong usage: specify at least one source file\n");
    return 1;
  }

  char arg_ignore[argc];
  for (int i = 1; i < argc; ++i)
  {
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
    else if (strcmp(argv[i], "-c") == 0)
    {
      arg_ignore[i - 1] = 1;
      mode = MODE_COMPILE_ONLY;
    }
    else
    {
      arg_ignore[i - 1] = 0;
    }
  }

  if (platform == PLATFORM_NONE)
  {
    printf("no platform specified: set -platform to linux-gcc or win-vs\n");
    return 4;
  }

  unsigned char config = (mode == MODE_COMPILE_ONLY ? 0 : 1) << 1 | (platform == PLATFORM_LINUX_GCC_7_5 ? 0 : 1);
  configure_assembler(config);

  for (int i = 1; i < argc; ++i)
  {
    if (arg_ignore[i - 1] == 1)
    {
      continue;
    }

    const char *filename = argv[i];
    set_error_filename(filename);

    printf("%s\n", filename);

    const char *source = parse_source_file(filename);
    if (source == 0)
    {
      continue;
    }

    struct token *t = tokenize(source);
    if (t == 0)
    {
      continue;
    }

    const char *output_filename = source_to_output_filename(filename);
    open_output_file(output_filename);
    assemble(t);
    printf("%s -> %s\n", filename, output_filename);
  }

  return 0;
}