#include "assembler.h"
#include "args.h"
#include "compiler.h"
#include "var.h"

void token_head(FILE *file)
{
  if (get_output() == OUTPUT_INTEL_X64_ASM)
  {
    if (get_target_platform() == TARGET_PLATFORM_LINUX)
    {
      fputs(".globl main\nmain:\n", file);
    }
    else if (get_target_platform() == TARGET_PLATFORM_WIN)
    {
      fputs(".code\nmain proc\n", file);
    }
  }
}

void token_tail(FILE *file)
{
  if (get_output() == OUTPUT_INTEL_X64_ASM)
  {
    if (get_target_platform() == TARGET_PLATFORM_WIN)
    {
      fputs("main endp\nend", file);
    }
  }
}

void token_return(struct token *t, FILE *file)
{
  if (get_output() == OUTPUT_INTEL_X64_ASM)
  {
    if (get_target_platform() == TARGET_PLATFORM_LINUX)
    {
      fprintf(file, "  movq %%r%d, %%rax\n  ret\n", read_var((char)t->value));
    }
    else if (get_target_platform() == TARGET_PLATFORM_WIN)
    {
      fprintf(file, "  mov rax, r%d\n  ret\n", read_var((char)t->value));
    }
  }
  else if (get_output() == OUTPUT_EXECUTABLE)
  {
    if (get_target_platform() == TARGET_PLATFORM_LINUX)
    {
      // mov eax, 1 (sys_exit)
      fputc(0xB8, file);
      fputc(0x01, file);
      fputc(0x00, file);
      fputc(0x00, file);
      fputc(0x00, file);

      // mov ebx, value (return code)
      fputc(0xBB, file);
      fputc(/*read_var((char)t->value)*/0x05, file);
      fputc(0x00, file);
      fputc(0x00, file);
      fputc(0x00, file);

      // Interrupt 0x80
      fputc(0xCD, file);
      fputc(0x80, file);
    }
    // TODO: Implement for Windows
  }
}

void token_var(/*struct token *t*/)
{
  //write_var((char)t->value, 11);
}

void token_call(struct token *t, FILE *file)
{
  if (get_output() == OUTPUT_INTEL_X64_ASM)
  {
    if (get_target_platform() == TARGET_PLATFORM_LINUX)
    {
      fprintf(file, "  movq $%d, %%r%d\n", t->value2, read_var((char)t->value));
    }
    else if (get_target_platform() == TARGET_PLATFORM_WIN)
    {
      fprintf(file, "  mov r%d, %d\n", read_var((char)t->value), t->value2);
    }
  }
  else if (get_output() == OUTPUT_EXECUTABLE)
  {
    write_var((char)t->value, t->value2);
  }
}

void assemble(struct token *t, FILE *file)
{
  while (t)
  {
    switch (t->type)
    {
    case TOKEN_TYPE_HEAD:
      token_head(file);
      break;
    case TOKEN_TYPE_TAIL:
      token_tail(file);
      break;
    case TOKEN_TYPE_RETURN:
      token_return(t, file);
      break;
    case TOKEN_TYPE_VAR:
      token_var(/*t*/);
      break;
    case TOKEN_TYPE_CALL:
      token_call(t, file);
    default:
      break;
    }

    t = t->next;
  }
}