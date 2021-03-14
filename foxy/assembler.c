#include "error.h"
#include "tokenizer.h"
#include "var.h"

#include <stdio.h>
#include <stdlib.h> // for malloc

FILE *file;
unsigned char config = 0;

void token_head()
{
  if ((config & 2) == 0)
  // assembly output
  {
    if ((config & 1) == 0)
    // linux gcc platform
    {
      fputs(".globl main\nmain:\n", file);
    }
    else
    // windows vs platform
    {
      fputs(".code\nmain proc\n", file);
    }
  }
}

void token_tail()
{
  if ((config & 2) == 0)
  // assembly output
  {
    if ((config & 1) == 1)
    // windows vs platform
    {
      fputs("main endp\nend", file);
    }
  }
}

void token_return(struct token *t)
{
  if ((config & 2) == 0)
  // assembly output
  {
    if ((config & 1) == 0)
    // linux gcc platform
    {
      fprintf(file, "  movq %%r%d, %%rax\n  ret\n", read_var((char)t->value));
    }
    else
    // windows vs platform
    {
      fprintf(file, "  mov rax, r%d\n  ret\n", read_var((char)t->value));
    }
  }
  else
  // machine code output
  {
    fputc(0x4c, file);
    fputc(0x89, file);
    fputc(0xc0 + (read_var((char)t->value) - 8) * 8, file);
    fputc(0xc3, file);
  }
}

void token_var(struct token *t)
{
  write_var((char)t->value, 11);
}

void token_call(struct token *t)
{
  if ((config & 2) == 0)
  // assembly output
  {
    if ((config & 1) == 0)
    // linux gcc platform
    {
      fprintf(file, "  movq $%d, %%r%d\n", t->value2, read_var((char)t->value));
    }
    else
    // windows vs platform
    {
      fprintf(file, "  mov r%d, %d\n", read_var((char)t->value), t->value2);
    }
  }
  else
  // machine code output
  {
    fputc(0x49, file);
    fputc(0xc7, file);
    fputc(0xc0 + read_var((char)t->value) - 8, file);
    fputc(t->value2, file);
    fputc(0x00, file);
    fputc(0x00, file);
    fputc(0x00, file);
  }
}

void configure_assembler(unsigned char config_)
{
  config = config_;
}

const char *source_to_output_filename(const char *filename)
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
  output_filename[len + 1] = (config & 2) == 0 ? 's' : 'o';
  output_filename[len + 2] = 0;

  return output_filename;
}

void open_output_file(const char *filename)
{
  file = fopen(filename, "w");

  if (file == 0)
  {
    error(ERROR_INVALID_OUTPUT_FILE, filename);
    fclose(file);
    return;
  }
}

void assemble(struct token *t)
{
  while (t != 0)
  {
    switch (t->type)
    {
    case TOKEN_TYPE_HEAD:
      token_head();
      break;
    case TOKEN_TYPE_TAIL:
      token_tail();
      break;
    case TOKEN_TYPE_RETURN:
      token_return(t);
      break;
    case TOKEN_TYPE_VAR:
      token_var(t);
      break;
    case TOKEN_TYPE_CALL:
      token_call(t);
    default:
      break;
    }
    t = t->next;
  }

  fclose(file);
}