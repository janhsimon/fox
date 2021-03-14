// bitmask:
// least significant bit: 0 = linux-gcc, 1 = win/vs
// 2nd least significant bit: 0 = output assembly, 1 = output machine code
void configure_assembler(char config);

const char *source_to_output_filename(const char *filename);
void open_output_file(const char *filename);
void assemble(struct token *t);