CC=gcc
CFLAGS=-I.
#DEPS = hellomake.h
OBJ = error.o foxy.o parser.o tokenizer.o var.o writer.o 

%.o: %.c %.h
	$(CC) -c -o $@ $< $(CFLAGS)

foxy: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
