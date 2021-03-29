#include "args.h"
#include "compiler.h"
#include "error.h"
#include "fileio.h"
#include "linker.h"
#include "assembler.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  // Always get rid of the first argument containing the path to foxy
  --argc;
  argv = &argv[1];

  // Scan arguments for options, store their values and mark them as null
  if (parse_options(argc, argv) == 0)
  {
    return 1;
  }

  for (int i = 0; i < argc; ++i)
  // Iterate all source files
  {
    const char *source_filename = argv[i];

    if (source_filename == 0)
    // Skip this argument if it was already parsed as an option
    {
      continue;
    }

    char *source = read_source_file(source_filename);
    if (source == 0)
    // Skip this source file if there was an error reading it
    {
      continue;
    }

    char *output_filename = source_to_output_filename(source_filename);
    FILE *output_file = open_output_file(output_filename);
    if (output_file == 0)
    // Skip this source file if there was an error opening an output file for it
    {
      free(output_filename);
      continue;
    }

    // Compile the source into a linked-list of tokens
    printf("%s\n", source_filename);
    set_error_filename(source_filename);
    struct token *t = compile(source);
    free(source); // Free the source buffer
    if (t == 0)
    // Skip this source file if there was a compiler error
    {
      free(output_filename);
      fclose(output_file);
      continue;
    }

    // Assemble the source file into the output file
    assemble(t, output_file);
    // TODO: Free t
    fclose(output_file);
    printf("%s -> %s\n", source_filename, output_filename);

    if (get_output() == OUTPUT_EXECUTABLE)
    // Link the output file into an executable if desired
    {
      printf("%s -> %s\n", output_filename, "life");
      if (link("life", output_filename) == 0)
      // Skip this executable if there was a linker error
      {
        free(output_filename);
        continue;
      }
    }

    free(output_filename);
  }

  return 0;
}