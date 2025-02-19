#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    int is_completed;
} Process;



int n; // Number of processes



/**
 * @brief Finds the index of the process with the shortest remaining time.
 *
 * @param proc Array of processes
 * @param current_time The current execution time
 * @return int The index of the next process to be executed
 */
int findNextProcess(Process proc[], int current_time) {
    int min_time = INT_MAX;
    int index = -1;

    for (int i = 0; i < n; i++) {
        // Check if process has arrived and is not completed
        if (proc[i].arrival_time <= current_time &&
            proc[i].remaining_time > 0 &&
            proc[i].remaining_time < min_time) {
            min_time = proc[i].remaining_time;
            index = i;
        }
    }

    return index;
}



/**
 * @brief Executes the Shortest Remaining Time First (SRTF) scheduling algorithm.
 * @param proc Array of processes
 */
void srtf(Process proc[]) {
    int current_time = 0;
    int completed = 0;
    int prev_index = -1;

    // Initialize remaining time and other parameters
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].is_completed = 0;
        proc[i].waiting_time = 0;
        proc[i].turnaround_time = 0;
        proc[i].completion_time = 0;
    }

    // Execute processes
    while (completed != n) {
        int index = findNextProcess(proc, current_time);

        if (index != -1) {
            // Execute process for 1 time unit
            proc[index].remaining_time--;
            current_time++;

            // If process is completed
            if (proc[index].remaining_time == 0) {
                completed++;
                proc[index].is_completed = 1;
                proc[index].completion_time = current_time;
                proc[index].turnaround_time = proc[index].completion_time - proc[index].arrival_time;

                // Waiting time using recurrence relation
                if (prev_index == -1) {
                    proc[index].waiting_time = 0;  // First process has 0 waiting time
                } else {
                    proc[index].waiting_time = proc[prev_index].waiting_time + proc[prev_index].burst_time;
                }

                prev_index = index;
            }
        } else {
            // If no process is ready, move time forward
            current_time++;
        }
    }
}



/**
 * @brief Prints the process details including waiting time and turnaround time.
 *
 * @param proc Array of processes
 */
void printProcesses(Process proc[]) {
    printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf(
            "%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            proc[i].process_id,
            proc[i].arrival_time,
            proc[i].burst_time,
            proc[i].completion_time,
            proc[i].waiting_time,
            proc[i].turnaround_time
        );
    }
}



int main() {
    // Initialize processes with their IDs, arrival times, and burst times
    Process proc[] = {
        {1, 0, 8, 0, 0, 0, 0, 0},
        {2, 1, 4, 0, 0, 0, 0, 0},
        {3, 2, 9, 0, 0, 0, 0, 0},
        {4, 3, 5, 0, 0, 0, 0, 0}
    };

    n = sizeof(proc) / sizeof(proc[0]);

    srtf(proc);
    printProcesses(proc);

    return 0;
}