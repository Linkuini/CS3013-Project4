CC=gcc
CFLAGS= -std=gnu99
DEPS = hierarchy.h pageTable.h UserAPI.h Error.h
OBJ = hierarchy.o pageTable.o UserAPI.o Error.o VirtualMemory.o

all: VirtualMemory

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

VirtualMemory: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean: 
	rm VirtualMemory *.o
