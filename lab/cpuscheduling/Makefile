# Makefile to compile and run multiple CPU scheduling algorithms

CC = gcc
CFLAGS = -Wall -Wextra -O2

# Executable names
FCFS_EXEC = fcfs_scheduling
SJF_EXEC = sjf_scheduling
SRTF_EXEC = srtf_scheduling
PRIORITY_EXEC = priority_scheduling
RR_EXEC = rr_scheduling

# Source files
FCFS_SRC = fcfs.c
SJF_SRC = sjf.c
SRTF_SRC = srtf.c
PRIORITY_SRC = priority.c
RR_SRC = rr.c

# Build rules
all: $(FCFS_EXEC) $(SJF_EXEC) $(SRTF_EXEC) $(PRIORITY_EXEC) $(RR_EXEC)

$(FCFS_EXEC): $(FCFS_SRC)
	$(CC) $(CFLAGS) -o $(FCFS_EXEC) $(FCFS_SRC)

$(SJF_EXEC): $(SJF_SRC)
	$(CC) $(CFLAGS) -o $(SJF_EXEC) $(SJF_SRC)

$(SRTF_EXEC): $(SRTF_SRC)
	$(CC) $(CFLAGS) -o $(SRTF_EXEC) $(SRTF_SRC)

$(PRIORITY_EXEC): $(PRIORITY_SRC)
	$(CC) $(CFLAGS) -o $(PRIORITY_EXEC) $(PRIORITY_SRC)

$(RR_EXEC): $(RR_SRC)
	$(CC) $(CFLAGS) -o $(RR_EXEC) $(RR_SRC)

# Run options
run:
	@echo "Select the scheduling algorithm(s) to run:"
	@echo "1) Run FCFS Algorithm"
	@echo "2) Run SJF Algorithm"
	@echo "3) Run SRTF Algorithm"
	@echo "4) Run Priority Algorithm"
	@echo "5) Run Round Robin Algorithm"
	@echo "6) Run All Algorithms"
	@read -p "Enter choice (separate multiple choices with spaces, e.g., '1 3 5' or '6' for all): " choices; \

	for choice in $$choices; do \
		if [ $$choice -eq 1 ]; then ./$(FCFS_EXEC); fi; \
		if [ $$choice -eq 2 ]; then ./$(SJF_EXEC); fi; \
		if [ $$choice -eq 3 ]; then ./$(SRTF_EXEC); fi; \
		if [ $$choice -eq 4 ]; then ./$(PRIORITY_EXEC); fi; \
		if [ $$choice -eq 5 ]; then ./$(RR_EXEC); fi; \
		if [ $$choice -eq 6 ]; then ./$(FCFS_EXEC) && ./$(SJF_EXEC) && ./$(SRTF_EXEC) && ./$(PRIORITY_EXEC) && ./$(RR_EXEC); fi; \
	done

# Clean up compiled files
clean:
	rm -f $(FCFS_EXEC) $(SJF_EXEC) $(SRTF_EXEC) $(PRIORITY_EXEC) $(RR_EXEC)
	@echo "Cleanup completed!"