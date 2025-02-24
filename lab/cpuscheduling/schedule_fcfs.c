//schedule_fcfs.c

#include <stdio.h>
#include <stdlib.h>
#include "process.h"


/**
 * @brief Swaps two process elements in an array.
 */
void swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}


/**
 * @brief Partitions the array for QuickSort.
 */
int partition(Process proc[], int low, int high) {
    int pivot = proc[high].arrival_time;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (proc[j].arrival_time < pivot) {
            i++;
            swap(&proc[i], &proc[j]);
        }
    }
    swap(&proc[i + 1], &proc[high]);
    return i + 1;
}


/**
 * @brief QuickSort function to sort processes by arrival time.
 */
void quickSort(Process proc[], int low, int high) {
    if (low < high) {
        int pi = partition(proc, low, high);
        quickSort(proc, low, pi - 1);
        quickSort(proc, pi + 1, high);
    }
}


/**
 * @brief Executes the First-Come, First-Served (FCFS) scheduling algorithm.
 *
 * @param proc Array of processes
 * @param num_processes Number of processes
 */
void fcfs(Process proc[], int num_processes) {
    quickSort(proc, 0, num_processes - 1); // Sort processes by arrival time
    int current_time = 0;

    for (int i = 0; i < num_processes; i++) {
        if (current_time < proc[i].arrival_time) {
            current_time = proc[i].arrival_time; // CPU remains idle if no process has arrived
        }
        printf("Time %d: Process %d starts\n", current_time, proc[i].process_id);
        proc[i].completion_time = current_time + proc[i].burst_time;
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
        proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
        current_time = proc[i].completion_time;
        printf("Time %d: Process %d completes\n", current_time, proc[i].process_id);
    }
}


int main() {
    int input[][3] = {
        {3, 2, 8},  /* {process_id,  arrival_time,  burst_time} */
        {1, 0, 5},
        {4, 3, 6},
        {2, 1, 3}
    };

    int num_processes = sizeof(input) / sizeof(input[0]);
    Process* proc = (Process*)malloc(num_processes * sizeof(Process));

    for (int i = 0; i < num_processes; i++) {
        proc[i].process_id = input[i][0];
        proc[i].arrival_time = input[i][1];
        proc[i].burst_time = input[i][2];
        initializeProcess(&proc[i]);
    }

    fcfs(proc, num_processes);
    printProcesses(proc, num_processes);

    free(proc);
    return 0;
}
