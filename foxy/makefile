PROGRAM = foxy
OBJS = foxy.o args.o assembler.o compiler.o error.o fileio.o linker.o var.o
CFLAGS = -x c -std=c11 -Wall -Werror -Wextra -Wpedantic

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	cc -o $@ $(OBJS)

%.o: %.c
	cc $(CFLAGS) -o $@ -c $<

clean:
	rm $(OBJS) $(PROGRAM)