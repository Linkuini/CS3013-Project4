CC=gcc
CFLAGS= -std=gnu99
DEPS = UserAPI.h hierarchy.h
OBJ = UserAPI.o VirtualMemory.o 

all: VirtualMemory

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

VirtualMemory: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean: 
	rm VirtualMemory *.o
