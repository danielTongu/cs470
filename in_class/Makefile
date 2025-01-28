# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -Wextra -pedantic -std=c11

# Executable Name
TARGET = copy_file

# Source Files
SRC = copy_file.c

# Build the executable
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean compiled files
clean:
	rm -f $(TARGET)