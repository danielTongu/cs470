# Compiler to be used for compiling the C program
CC = gcc

# Compiler flags:
# -Wall    : Enable all warnings
# -Wextra  : Enable extra warnings
# -pedantic: Enforce strict compliance with the C standard
# -std=c11 : Use the C11 standard
CFLAGS = -Wall -Wextra -pedantic -std=c11

# Name of the output executable file
TARGET = copy_file

# Source file that needs to be compiled
SRC = copy_file.c

# Default target: This compiles the C program and produces an executable
all:$(TARGET)

# Rule to compile the C program
# This tells Make to compile 'copy_files.c' into an executable named 'copy_files'
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean rule: Deletes the compiled executable to free up space or for recompilation
clean:
	rm -f $(TARGET)