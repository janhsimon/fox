PROGRAM = life
SRC = life.fox
FC = ../../foxy/foxy
CFLAGS = 

all: clean $(PROGRAM) promote

$(PROGRAM): $(SRC)
	$(FC) $(CFLAGS) $(SRC)

clean:
	- rm $(PROGRAM) $(PROGRAM).o

promote:
	chmod +x $(PROGRAM)