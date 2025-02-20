#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "process.h"


/**
 * @brief Finds the index of the process with the shortest remaining time.
 *
 * @param proc Array of processes
 * @param num_processes Number of processes
 * @param current_time The current execution time
 * @return int The index of the next process to be executed
 */
int findNextProcess(Process proc[], int num_processes, int current_time) {
    int min_time = INT_MAX;
    int index = -1;

    for (int i = 0; i < num_processes; i++) {
        if (proc[i].arrival_time <= current_time && proc[i].remaining_time > 0 && proc[i].remaining_time < min_time) {
            min_time = proc[i].remaining_time;
            index = i;
        }
    }
    return index;
}


/**
 * @brief Executes the Shortest Job First (SJF) scheduling algorithm (Non-Preemptive).
 *
 * @param proc Array of processes
 * @param num_processes Number of processes
 */
void sjf(Process proc[], int num_processes) {
    int current_time = 0;
    int completed = 0;
    int prev_index = -1;

    while (completed != num_processes) {
        int index = findNextProcess(proc, num_processes, current_time);

        if (index != -1) {
            if (index != prev_index) {
                printf("Time %d: Process %d starts\n", current_time, proc[index].process_id);
                prev_index = index;
            }
            proc[index].remaining_time--;
            current_time++;

            if (proc[index].remaining_time == 0) {
                completed++;
                proc[index].is_completed = 1;
                proc[index].completion_time = current_time;
                proc[index].turnaround_time = proc[index].completion_time - proc[index].arrival_time;
                proc[index].waiting_time = proc[index].turnaround_time - proc[index].burst_time;
                printf("Time %d: Process %d completes\n", current_time, proc[index].process_id);
                prev_index = -1;
            }
        } else {
            current_time++;
        }
    }
}


int main() {
    int input[][3] = {
        {1, 0, 8},  /* {process_id,  arrival_time,  burst_time} */
        {2, 1, 4},
        {3, 2, 9},
        {4, 3, 5}
    };
    int num_processes = sizeof(input) / sizeof(input[0]);
    Process* proc = (Process*)malloc(num_processes * sizeof(Process));

    for (int i = 0; i < num_processes; i++) {
        proc[i].process_id = input[i][0];
        proc[i].arrival_time = input[i][1];
        proc[i].burst_time = input[i][2];
        initializeProcess(&proc[i]);
    }

    sjf(proc, num_processes);
    printProcesses(proc, num_processes);

    free(proc);
    return 0;
}
