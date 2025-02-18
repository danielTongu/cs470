# Makefile to build and manage the process creation program

# Compiler to use
CC = gcc

# Compiler flags:
# -Wall : Enable all warnings
# -Wextra : Enable additional warnings
# -g    : Include debugging information
CFLAGS = -Wall -Wextra -g

# The target executable file
SRC_EXEC = process_manager

# The source code file
SRC = process_manager.c

# Default target: Build the executable
# This is the first target executed when running 'make' without arguments
all: $(SRC_EXEC)

# Rule to compile the program
$(SRC_EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(SRC_EXEC) $(SRC)

# Rule to run the compiled program
run: $(SRC_EXEC)
	./$(SRC_EXEC)

# Clean rule: Deletes the compiled executable to free up space or for recompilation
# Run this using 'make clean'
clean:
	rm -f $(SRC_EXEC)
	@echo "Cleanup completed!"
