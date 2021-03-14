PROGRAM = foxy
OBJS = foxy.o assembler.o error.o parser.o tokenizer.o var.o
CFLAGS = -x c -std=c11 -Wall -Werror -Wextra -Wpedantic

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	cc -o $@ $(OBJS)

%.o: %.c
	cc $(CFLAGS) -o $@ -c $<

clean:
	rm $(OBJS) $(PROGRAM)