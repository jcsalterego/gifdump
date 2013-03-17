
EXE=gifdump
CFLAGS=-Wall -g -O3

OBJS=gifdump.o gif.o stream.o

all: gifdump
gifdump: gifdump.o gif.o stream.o
	$(CC) $(CFLAGS) $(OBJS) -o $(EXE)
%.o: %.cc
	$(CC) -c $(CFLAGS) $< -o $@
clean:
	rm -rf *.o *~ \#*\# *.dSYM/ $(EXE)
