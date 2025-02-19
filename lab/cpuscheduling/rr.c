#include <stdio.h>
#include <stdlib.h>
#include "process.h"

/**
 * @brief Function to calculate waiting times and execution order for all processes
 * @param proc Array of processes
 * @param num_processes Number of processes
 * @param quantum Time quantum for Round Robin
 */
void calculateWaitingTimeAndExecutionOrder(Process proc[], int num_processes, int quantum) {
    int time = 0; // Current time
    int done = 0; // Counter for completed processes
    int execution_order[1000]; // Store execution order
    int exec_index = 0; // Index for execution order storage

    while (done < num_processes) {
        for (int i = 0; i < num_processes; i++) {
            if (proc[i].remaining_time > 0) {
                // Store execution order
                execution_order[exec_index++] = proc[i].process_id;

                if (proc[i].remaining_time > quantum) {
                    time += quantum;
                    proc[i].remaining_time -= quantum;
                } else {
                    time += proc[i].remaining_time;
                    proc[i].waiting_time = time - proc[i].burst_time - proc[i].arrival_time;
                    proc[i].remaining_time = 0;
                    proc[i].completion_time = time;
                    done++;
                }
            }
        }
    }

    // Print execution order
    printf("Execution Order: ");
    for (int i = 0; i < exec_index; i++) {
        printf("P%d ", execution_order[i]);
    }
    printf("\n");
}

/**
 * @brief Function to calculate turnaround times for all processes
 * @param proc Array of processes
 * @param num_processes Number of processes
 */
void calculateTurnaroundTime(Process proc[], int num_processes) {
    for (int i = 0; i < num_processes; i++) {
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
    }
}

/**
 * @brief Executes the Round Robin scheduling algorithm
 * @param proc Array of processes
 * @param num_processes Number of processes
 * @param quantum Time quantum
 */
void roundRobin(Process proc[], int num_processes, int quantum) {
    calculateWaitingTimeAndExecutionOrder(proc, num_processes, quantum);
    calculateTurnaroundTime(proc, num_processes);
}

int main() {
    int input[][3] = {
        {1, 0, 24},
        {2, 0, 3},
        {3, 0, 3}
    };

    int num_processes = sizeof(input) / sizeof(input[0]);
    Process* proc = createProcessArray(input, num_processes);
    int quantum = 4; // Time quantum for Round Robin scheduling

    roundRobin(proc, num_processes, quantum);
    printProcesses(proc, num_processes);

    free(proc);
    return 0;
}
