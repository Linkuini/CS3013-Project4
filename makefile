CC=gcc
CFLAGS= -std=gnu99
DEPS = UserAPI.h hierarchy.h pageTable.h
OBJ = UserAPI.o VirtualMemory.o pageTable.o

all: VirtualMemory

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

VirtualMemory: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean: 
	rm VirtualMemory *.o
