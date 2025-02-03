# Makefile to build and manage the process creation program

# Compiler to use
CC = gcc

# Compiler flags:
# -Wall : Enable all warnings
# -Wextra : Enable additional warnings
# -g    : Include debugging information
CFLAGS = -Wall -Wextra -g

# The target executable file
TARGET = process_manager

# The source code file
SRC = process_manager.c

# Default target: Build the executable
# This is the first target executed when running 'make' without arguments
all: $(TARGET)

# Rule to compile the program
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean rule: Deletes the compiled executable to free up space or for recompilation
# Run this using 'make clean'
clean:
	rm -f $(TARGET)
