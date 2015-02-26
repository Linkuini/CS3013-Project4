CC=gcc
CFLAGS= -std=gnu99
DEPS = Error.h hierarchy.h pageTable.h UserAPI.h
OBJ = Error.c hierarchy.o pageTable.o UserAPI.o VirtualMemory.o

all: VirtualMemory

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

VirtualMemory: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean: 
	rm VirtualMemory *.o
