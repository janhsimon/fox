#include "args.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum output o = OUTPUT_EXECUTABLE;
enum target_platform tp = TARGET_PLATFORM_LINUX;

enum output get_output()
{
  return o;
}

enum target_platform get_target_platform()
{
  return tp;
}

void print_usage()
{
  printf("foxy - Fox cross-compiler and linker\n");
  printf("usage: fox [options] source files\n");
  printf("example: fox -output=intel-x64-asm main.fox math.fox\n");
  printf("options:\n");
  printf("-output=executable (default) or intel-x64-asm\n");
  printf("-target-platform=linux (default) or win\n");
}

char parse_options(int argc, char *argv[])
{
  if (argc <= 0)
  {
    print_usage();
    return 0;
  }

  unsigned long num_source_files = 0;
  for (int i = 0; i < argc; ++i)
  {
    if (strncmp(argv[i], "-output=", 8) == 0)
    {
      const char *value = argv[i] + 8;
      if (strcmp(value, "executable") == 0)
      {
        o = OUTPUT_EXECUTABLE;
      }
      else if (strcmp(value, "intel-x64-asm") == 0)
      {
        o = OUTPUT_INTEL_X64_ASM;
      }
      else
      {
        printf("invalid -output specified: expected \"executable\" or \"intel-x64-asm\", got \"%s\"\n", value);
        return 0;
      }
      argv[i] = 0;
    }
    else if (strncmp(argv[i], "-target-platform=", 17) == 0)
    {
      const char *value = argv[i] + 17;
      if (strcmp(value, "linux") == 0)
      {
        tp = TARGET_PLATFORM_LINUX;
      }
      else if (strcmp(value, "win") == 0)
      {
        tp = TARGET_PLATFORM_WIN;
      }
      else
      {
        printf("invalid -target-platform specified: expected \"linux\" or \"win\", got \"%s\"\n", value);
        return 0;
      }
      argv[i] = 0;
    }
    else
    {
      ++num_source_files;
    }
  }

  if (num_source_files == 0)
  {
    printf("no source files\n");
    return 0;
  }

  return 1;
}