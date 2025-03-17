# Makefile to compile and run CPU scheduling algorithms

CC = gcc
CFLAGS = -Wall -Wextra -O2

# Executable names
RR_EXEC = schedule_rr_exec
SJF_EXEC = schedule_sjf_exec
FCFS_EXEC = schedule_fcfs_exec
PRIORITY_EXEC = schedule_priority_exec

# Source files
RR_SRC = schedule_rr.c process.c
SJF_SRC = schedule_sjf.c process.c
FCFS_SRC = schedule_fcfs.c process.c
PRIORITY_SRC = schedule_priority.c process.c

# Build rules
all: $(RR_EXEC) $(SJF_EXEC) $(FCFS_EXEC) $(PRIORITY_EXEC)

$(RR_EXEC): $(RR_SRC)
	$(CC) $(CFLAGS) -o $(RR_EXEC) $(RR_SRC)

$(SJF_EXEC): $(SJF_SRC)
	$(CC) $(CFLAGS) -o $(SJF_EXEC) $(SJF_SRC)

$(FCFS_EXEC): $(FCFS_SRC)
	$(CC) $(CFLAGS) -o $(FCFS_EXEC) $(FCFS_SRC)

$(PRIORITY_EXEC): $(PRIORITY_SRC)
	$(CC) $(CFLAGS) -o $(PRIORITY_EXEC) $(PRIORITY_SRC)

# Run options
run:
	@echo "Select an option:"
	@echo "1) Run Round Robin Algorithm"
	@echo "2) Run SJF Algorithm"
	@echo "3) Run FCFS Algorithm"
	@echo "4) Run Priority Scheduling Algorithm"
	@echo "5) Run All Algorithms"
	@read -p "Enter choice: " choice; \
	if [ $$choice -eq 1 ]; then ./$(RR_EXEC); \
	elif [ $$choice -eq 2 ]; then ./$(SJF_EXEC); \
	elif [ $$choice -eq 3 ]; then ./$(FCFS_EXEC); \
	elif [ $$choice -eq 4 ]; then ./$(PRIORITY_EXEC); \
	elif [ $$choice -eq 5 ]; then ./$(RR_EXEC) && ./$(SJF_EXEC) && ./$(FCFS_EXEC) && ./$(PRIORITY_EXEC); \
	else echo "Invalid choice"; fi

# Clean up compiled files
clean:
	rm -f $(RR_EXEC) $(SJF_EXEC) $(FCFS_EXEC) $(PRIORITY_EXEC)
	@echo "Cleanup completed!"