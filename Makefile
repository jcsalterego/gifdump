
EXE=gifdump
CFLAGS=-Wall -g -O3

OBJS=gifdump.o gif.o

all: gifdump
gifdump: gifdump.o gif.o
	$(CC) $(CFLAGS) $(OBJS) -o $(EXE)
%.o: %.cc
	$(CC) -c $(CFLAGS) $< -o $@
clean:
	rm -rf *.o *~ \#*\# *.dSYM/ $(EXE)
