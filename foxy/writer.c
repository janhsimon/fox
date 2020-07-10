#include <stdio.h>
#include <stdlib.h> // for malloc

#include "error.h"
#include "tokenizer.h"
#include "var.h"

FILE* file;

const char* source_to_output_filename(const char* filename)
{
  const char* i = filename;
  while (*i != 0 && *i != '.') {
    ++i;
  }

  int len = i - filename;
  char* output_filename = malloc(len + 2);

  for (int j = 0; j < len; ++j)
  {
    output_filename[j] = filename[j];
  }

  output_filename[len + 0] = '.';
  output_filename[len + 1] = 's';
  output_filename[len + 2] = 0;

  return output_filename;
}

void open_output_file(const char* filename)
{
  file = fopen(filename, "w");

  if (file == 0)
  {
    error(ERROR_INVALID_OUTPUT_FILE, filename);
    fclose(file);
    return;
  }
}

void write_linux_gcc_7_5(struct token *t)
{
  while (t != 0) {
    switch (t->type) {
    case TOKEN_TYPE_HEAD:
      fputs(".globl main\nmain:\n", file);
      break;
    case TOKEN_TYPE_TAIL:
      break;
    case TOKEN_TYPE_RETURN:
      fprintf(file, "  movq %%r%d, %%rax\n  ret\n", read_var((char)t->value));
      break;
    case TOKEN_TYPE_VAR:
      write_var((char)t->value, 11);
      break;
    case TOKEN_TYPE_CALL:
      fprintf(file, "  movq $%d, %%r%d\n", t->value2, read_var((char)t->value));
    default:
      break;
    }
    t = t->next;
  }

  fclose(file);
}

void write_win_vs_2019(struct token *t)
{
  while (t != 0) {
    switch (t->type) {
    case TOKEN_TYPE_HEAD:
      fputs(".code\nmain proc\n", file);
      break;
    case TOKEN_TYPE_TAIL:
      fputs("main endp\nend", file);
      break;
    case TOKEN_TYPE_RETURN:
      fprintf(file, "  mov rax, r%d\n  ret\n", read_var((char)t->value));
      break;
    case TOKEN_TYPE_VAR:
      write_var((char)t->value, 11);
      break;
    case TOKEN_TYPE_CALL:
      fprintf(file, "  mov r%d, %d\n", read_var((char)t->value), t->value2);
    default:
      break;
    }
    t = t->next;
  }
}

