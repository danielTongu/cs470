//schedule_srtf.c

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "process.h"

/**
 * @brief Shortest Remaining Time First (SRTF) Scheduling Algorithm (Preemptive)
 *
 * **Difference from SJF:**
 * - SJF (Non-Preemptive) selects the shortest job at the time of scheduling and does not interrupt.
 * - SRTF (Preemptive) continuously selects the job with the shortest remaining time, allowing preemption if a shorter process arrives.
 *
 * **Key Features:**
 * - **Preemptive:** A new process with a shorter burst time can interrupt the running process.
 * - **Continuous Selection:** The CPU always executes the process with the shortest remaining time at every time unit.
 * - **Better Response Time:** Ensures shorter processes execute sooner, benefiting interactive systems.
 * - **Possible Starvation:** Longer processes may suffer delays if shorter jobs keep arriving.
 */

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
 * @brief Executes the Shortest Remaining Time First (SRTF) scheduling algorithm.
 *
 * @param proc Array of processes
 * @param num_processes Number of processes
 */
void srtf(Process proc[], int num_processes) {
    int current_time = 0;
    int completed = 0;

    while (completed != num_processes) {
        int index = findNextProcess(proc, num_processes, current_time);

        if (index != -1) {
            printf("Time %d: Process %d executing\n", current_time, proc[index].process_id);
            proc[index].remaining_time--;
            current_time++;

            if (proc[index].remaining_time == 0) {
                completed++;
                proc[index].completion_time = current_time;
                proc[index].turnaround_time = proc[index].completion_time - proc[index].arrival_time;
                proc[index].waiting_time = proc[index].turnaround_time - proc[index].burst_time;
                printf("Time %d: Process %d completes\n", current_time, proc[index].process_id);
            }
        } else {
            current_time++;
        }
    }
}

int main() {
    int input[][3] = {
        {1, 0, 8},
        {2, 1, 4},
        {3, 2, 9},
        {4, 3, 5}
    };

    int num_processes = sizeof(input) / sizeof(input[0]);
    Process* proc = createProcessArray(input, num_processes);

    srtf(proc, num_processes);
    printProcesses(proc, num_processes);

    free(proc);
    return 0;
}
