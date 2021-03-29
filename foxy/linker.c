#include "linker.h"
#include "error.h"

#include <stdio.h>

void byte(int byte0, FILE *file)
{
  fputc(byte0, file);
}

void half_word(int byte0, int byte1, FILE *file)
{
  fputc(byte0, file);
  fputc(byte1, file);
}

void word(int byte0, int byte1, int byte2, int byte3, FILE *file)
{
  fputc(byte0, file);
  fputc(byte1, file);
  fputc(byte2, file);
  fputc(byte3, file);
}

void double_word(int byte0, int byte1, int byte2, int byte3, int byte4, int byte5, int byte6, int byte7, FILE *file)
{
  fputc(byte0, file);
  fputc(byte1, file);
  fputc(byte2, file);
  fputc(byte3, file);
  fputc(byte4, file);
  fputc(byte5, file);
  fputc(byte6, file);
  fputc(byte7, file);
}

char link(const char *outfilename, const char *infilename)
{
  FILE *of = fopen(outfilename, "w");
  if (of == 0)
  {
    error(ERROR_LINKER_INVALID_OUTPUT_FILE, outfilename);
    fclose(of);
    return 0;
  }

  FILE *inf = fopen(infilename, "r");
  if (inf == 0)
  {
    error(ERROR_LINKER_INVALID_INPUT_FILE, infilename);
    fclose(of);
    fclose(inf);
    return 0;
  }

  // Determine the number of bytes in the object file
  fseek(inf, 0, SEEK_END);
  int sz = ftell(inf);
  printf("Size of program %s: %d\n", infilename, sz);
  rewind(inf);

  // ELF header (64 bytes)
  word(0x7f, 0x45, 0x4c, 0x46, of);                                 // Magic number
  byte(0x02, of);                                                   // 64-bit
  byte(0x01, of);                                                   // Little-endian
  byte(0x01, of);                                                   // ELF version (1)
  byte(0x00, of);                                                   // Target operating system (generic)
  double_word(0x00, 0x00, 0x000, 0x00, 0x00, 0x00, 0x00, 0x00, of); // ABI detail (unused)
  half_word(0x02, 0x00, of);                                        // Type executable (ET_EXEC)
  half_word(0x3e, 0x00, of);                                        // Target architecture amd64 (x86-64)
  word(0x01, 0x00, 0x00, 0x00, of);                                 // ELF version (1)
  double_word(0x78, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, of);  // Entry point address in VRAM (0x400078)
  double_word(0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, of);  // Program headers file offset (64 bytes)
  double_word(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, of);  // Section headers file offset (0 bytes)
  word(0x00, 0x00, 0x00, 0x00, of);                                 // Flags (unused)
  half_word(0x40, 0x00, of);                                        // ELF header size (64 bytes)
  half_word(0x38, 0x00, of);                                        // Size of program header (56 bytes)
  half_word(0x01, 0x00, of);                                        // Number of program headers (1)
  half_word(0x00, 0x00, of);                                        // Size of section headers (0 bytes)
  half_word(0x00, 0x00, of);                                        // Number of section headers (0)
  half_word(0x00, 0x00, of);                                        // Index of section header table entry

  // Program header (56 bytes)
  word(0x01, 0x00, 0x00, 0x00, of);                                // Segment type (loadable)
  word(0x05, 0x00, 0x00, 0x00, of);                                // Segment flags (readable, executable)
  double_word(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, of); // Offset of segment in file (offset 120 bytes)
  double_word(0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, of); // Address of segment in VRAM (0x400000)
  double_word(0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, of); // Address of segment in RAM (0x400000)
  double_word(sz, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, of);   // Size of program as file
  double_word(sz, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, of);   // Size of program in memory
  double_word(0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, of); // Alignment

  // Program segment
  // Append the entire object file to the executable file
  unsigned char data[sz];
  fread(data, sz, 1, inf);
  fwrite(data, sz, 1, of);

  return 1;
}