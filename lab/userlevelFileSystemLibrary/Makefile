# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -Wextra -Werror -std=c11

# Source files
SRCS = Daniel_libFS.c Daniel_testFS.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = Daniel_testApp

# Default target (compile and link everything)
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Rule to compile .c files into .o object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the compiled program
run: $(TARGET)
	./$(TARGET)

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets (these do not represent actual files)
.PHONY: all clean run
