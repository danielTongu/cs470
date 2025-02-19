#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
} Process;



/**
 * @brief Function to calculate waiting times and execution order for all processes
 * @param proc Array of processes
 * @param n Number of processes
 * @param quantum Time quantum for Round Robin
 */
void calculateWaitingTimeAndExecutionOrder(Process proc[], int n, int quantum) {
    int time = 0; // Current time
    int done = 0; // Counter for completed processes
    int execution_order[1000]; // Store execution order
    int exec_index = 0; // Index for execution order storage

    // Initialize remaining burst times
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
    }

    while (done < n) {
        for (int i = 0; i < n; i++) {
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
 * @param n Number of processes
 */
void calculateTurnaroundTime(Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
    }
}



/**
 * @brief Executes the Round Robin scheduling algorithm
 * @param proc Array of processes
 * @param n Number of processes
 * @param quantum Time quantum
 */
void roundRobin(Process proc[], int n, int quantum) {
    calculateWaitingTimeAndExecutionOrder(proc, n, quantum);
    calculateTurnaroundTime(proc, n);
}



/**
 * @brief Prints process information
 * @param proc Array of processes
 * @param n Number of processes
 */
void printProcesses(Process proc[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}



int main() {
    // Initialize processes
    Process proc[] = {
        {1, 0, 24, 0, 0, 0, 0},
        {2, 0, 3, 0, 0, 0, 0},
        {3, 0, 3, 0, 0, 0, 0}
    };

    int n = sizeof(proc) / sizeof(proc[0]); // Number of processes
    int quantum = 4; // Time quantum for Round Robin scheduling

    roundRobin(proc, n, quantum);
    printProcesses(proc, n);

    return 0;
}