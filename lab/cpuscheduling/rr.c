


/*
#include <stdio.h>
#include <stdlib.h>



#define MAX_EXECUTIONS 1000 // Assuming a maximum of 1000 executions for simplicity



// Structure to represent a process
typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;




/**
 * Function to calculate waiting times and execution order for all processes using Round Robin scheduling.
 * @param proc Array of processes.
 * @param n Number of processes.
 * @param quantum Time quantum for the Round Robin scheduling.
 *
void calculateWaitingTimeAndExecutionOrder(Process proc[], int n, int quantum) {
    int remaining[MAX_EXECUTIONS]; // Array to store remaining burst times
    for (int i = 0; i < n; i++) {
        remaining[i] = proc[i].burst_time; // Initialize remaining burst times
    }

    int time = 0; // Current time
    int done;

    printf("Execution Order: ");

    // Keep traversing processes in round-robin manner until all are completed
    while (1) {
        done = 1;
        for (int i = 0; i < n; i++) {
            // If burst time of a process is greater than 0, it still needs processing
            if (remaining[i] > 0) {
                done = 0; // There is at least one pending process

                printf("P%d ", proc[i].process_id);

                if (remaining[i] > quantum) {
                    // Process executes for a full quantum
                    time += quantum;
                    remaining[i] -= quantum;
                } else {
                    // Process executes for remaining time
                    time += remaining[i];
                    proc[i].waiting_time = time - proc[i].burst_time;
                    remaining[i] = 0; // Process is finished
                }
            }
        }

        // If all processes are done, exit loop
        if (done == 1) break;
    }
    printf("\n");
}




/**
 * Function to calculate turnaround times for all processes.
 * @param proc Array of processes.
 * @param n Number of processes.
 *
void calculateTurnaroundTime(Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
    }
}




/**
 * Function to execute Round Robin scheduling.
 * @param proc Array of processes.
 * @param n Number of processes.
 * @param quantum Time quantum for the Round Robin scheduling.
 *
void roundRobin(Process proc[], int n, int quantum) {
    calculateWaitingTimeAndExecutionOrder(proc, n, quantum);
    calculateTurnaroundTime(proc, n);
}




/**
 * Function to print process details.
 * @param proc Array of processes.
 * @param n Number of processes.
 *
void printProcesses(Process proc[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf(
            "%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            proc[i].process_id,
            proc[i].arrival_time,
            proc[i].burst_time,
            proc[i].waiting_time,
            proc[i].turnaround_time
        );
    }
}




int main() {
    // Initializing process list
    Process proc[] = {
        {1, 0, 24, 0, 0, 0},
        {2, 0, 3, 0, 0, 0},
        {3, 0, 3, 0, 0, 0}
    };

    int n = sizeof(proc) / sizeof(proc[0]); // Number of processes
    int quantum = 4; // Time quantum for Round Robin scheduling

    // Execute Round Robin scheduling
    roundRobin(proc, n, quantum);

    // Print the final process details
    printProcesses(proc, n);

    return 0;
}
*/