

# Makefile to compile and run CPU scheduling algorithms

CC = gcc
CFLAGS = -Wall -Wextra -O2

# Executable names
RR_EXEC = rr_scheduling
SJF_EXEC = sjf_scheduling

# Source files
RR_SRC = rr.c process.c
SJF_SRC = sjf.c process.c

# Build rules
all: $(RR_EXEC) $(SJF_EXEC)

$(RR_EXEC): $(RR_SRC)
	$(CC) $(CFLAGS) -o $(RR_EXEC) $(RR_SRC)

$(SJF_EXEC): $(SJF_SRC)
	$(CC) $(CFLAGS) -o $(SJF_EXEC) $(SJF_SRC)

# Run options
run:
	@echo "Select an option:"
	@echo "1) Run Round Robin Algorithm"
	@echo "2) Run SJF Algorithm"
	@echo "3) Run Both"
	@read -p "Enter choice: " choice; \
	if [ $$choice -eq 1 ]; then ./$(RR_EXEC); \
	elif [ $$choice -eq 2 ]; then ./$(SJF_EXEC); \
	elif [ $$choice -eq 3 ]; then ./$(RR_EXEC) && ./$(SJF_EXEC); \
	else echo "Invalid choice"; fi

# Clean up compiled files
clean:
	rm -f $(RR_EXEC) $(SJF_EXEC)
	@echo "Cleanup completed!"