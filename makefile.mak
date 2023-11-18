# Makefile for your project

# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall -g

# Target executable name
TARGET = main

# Object files
OBJ = main.o pagetable.o phypages.o

# Default target
all: $(TARGET)

# Rule for linking the final executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Rule for compiling source files to object files
main.o: main.c pagetable.h phypages.h
	$(CC) $(CFLAGS) -c main.c

pagetable.o: pagetable.c pagetable.h
	$(CC) $(CFLAGS) -c pagetable.c

phypages.o: phypages.c phypages.h
	$(CC) $(CFLAGS) -c phypages.c

# Clean target for removing compiled files
clean:
	rm -f $(TARGET) $(OBJ)