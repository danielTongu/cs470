# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -std=c11

# Source files
SRCS = Daniel_libFS.c Daniel_testFS.c

# Object files (derived from source files)
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = Daniel_testFS

# Default target
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean