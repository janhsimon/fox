#include <stdio.h>

char *read_source_file(const char *filename);
char *source_to_output_filename(const char *filename);
FILE *open_output_file(const char *filename);