//schedule_priority.c

#include <stdio.h>
#include <stdlib.h>
#include "process.h"


/**
 * @brief Finds the index of the process with the highest priority.
 *
 * @param proc Array of processes
 * @param num_processes Number of processes
 * @param current_time The current execution time
 * @return int The index of the highest priority process to be executed
 */
int findHighestPriorityProcess(Process proc[], int num_processes, int current_time) {
    int highest_priority = INT_MAX;
    int index = -1;

    for (int i = 0; i < num_processes; i++) {
        if (proc[i].arrival_time <= current_time && proc[i].remaining_time > 0 && proc[i].priority < highest_priority) {
            highest_priority = proc[i].priority;
            index = i;
        }
    }
    return index;
}


/**
 * @brief Executes the Priority Scheduling algorithm (Non-Preemptive).
 *
 * @param proc Array of processes
 * @param num_processes Number of processes
 */
void priorityScheduling(Process proc[], int num_processes) {
    int current_time = 0;
    int completed = 0;

    while (completed != num_processes) {
        int index = findHighestPriorityProcess(proc, num_processes, current_time);

        if (index != -1) {
            printf("Time %d: Process %d starts\n", current_time, proc[index].process_id);
            current_time += proc[index].burst_time;
            proc[index].completion_time = current_time;
            proc[index].turnaround_time = proc[index].completion_time - proc[index].arrival_time;
            proc[index].waiting_time = proc[index].turnaround_time - proc[index].burst_time;
            proc[index].remaining_time = 0;
            proc[index].is_completed = 1;
            completed++;
            printf("Time %d: Process %d completes\n", current_time, proc[index].process_id);
        } else {
            current_time++;
        }
    }
}


int main() {
    int input[][4] = {
        {1, 10, 3},  /* {process_id,  burst_time, priority} */
        {2, 1, 1},
        {3, 2, 4},
        {4, 1, 5},
        {4, 5, 2}
    };

    int num_processes = sizeof(input) / sizeof(input[0]);
    Process* proc = (Process*)malloc(num_processes * sizeof(Process));


    for (int i = 0; i < num_processes; i++) {
        proc[i].arrival_time = i;
        proc[i].process_id = input[i][0];
        proc[i].burst_time = input[i][1];
        proc[i].priority = input[i][2];
        initializeProcess(&proc[i]);
    }

    priorityScheduling(proc, num_processes);
    printProcesses(proc, num_processes);

    free(proc);
    return 0;
}
