#include "process.h"

/**
 * @brief Finds the next available process based on FCFS.
 * - Selects the process that arrived first and has not completed.
 *
 * @param proc Array of processes.
 * @param num_processes Number of processes.
 * @param time Current system time.
 * @return Index of the selected process, or -1 if no process is available.
 */
int findNextFCFSProcess(Process proc[], int num_processes, int time) {
    int min_index = -1;
    int earliest_arrival = __INT_MAX__; // Large initial value

    for (int i = 0; i < num_processes; i++) {
        if (proc[i].arrival_time <= time && proc[i].remaining_time > 0) {
            if (proc[i].arrival_time < earliest_arrival) {
                earliest_arrival = proc[i].arrival_time;
                min_index = i;
            }
        }
    }
    return min_index;
}

/**
 * @brief Executes the selected process.
 * - Updates execution log and Gantt Chart.
 *
 * @param proc Array of processes.
 * @param index Index of the selected process.
 * @param time Pointer to current time.
 * @param gantt_chart Array storing execution order.
 * @param gc_index Pointer to Gantt chart index.
 */
void executeProcessFCFS(Process proc[], int index, int *time, int gantt_chart[], int *gc_index) {
    if (index == -1) {
        (*time)++;  // Move time forward if no process is available
        return;
    }

    printf("Time %d: Process %d starts\n", *time, proc[index].process_id);
    gantt_chart[(*gc_index)++] = proc[index].process_id;

    // Execute for full burst time
    *time += proc[index].burst_time;
    proc[index].remaining_time = 0;
    proc[index].completion_time = *time;
    proc[index].turnaround_time = proc[index].completion_time - proc[index].arrival_time;
    proc[index].waiting_time = proc[index].turnaround_time - proc[index].burst_time;

    printf("Time %d: Process %d completes\n", *time, proc[index].process_id);
}

/**
 * @brief Implements First-Come, First-Served (FCFS) Scheduling.
 * - The process that arrives first gets executed first.
 */
void fcfsScheduling(Process proc[], int num_processes) {
    int time = 0, completed = 0;
    int gantt_chart[100], gc_index = 0;

    printf("\n=== First-Come, First-Served (FCFS) Scheduling ===\n");

    while (completed < num_processes) {
        int index = findNextFCFSProcess(proc, num_processes, time);

        if (index != -1) {
            executeProcessFCFS(proc, index, &time, gantt_chart, &gc_index);
            completed++; // Process finishes in one execution
        } else {
            time++; // Move time forward if no process is available
        }
    }

    // Print Gantt Chart Execution Order
    printf("\nGantt Chart Execution Order (FCFS):\n");
    for (int i = 0; i < gc_index; i++) {
        printf("P%d ", gantt_chart[i]);
    }
    printf("\n");
}

/**
 * @brief Main function for FCFS Scheduling
 */
int main() {
    int input[][3] = {
        {1, 0, 8},  /* {process_id,  arrival_time,  burst_time} */
        {2, 1, 4},
        {3, 2, 9},
        {4, 3, 5}
    };

    int num_processes = sizeof(input) / sizeof(input[0]);
    Process* proc = (Process*)malloc(num_processes * sizeof(Process));

    // Initialize processes
    for (int i = 0; i < num_processes; i++) {
        proc[i].process_id = input[i][0];
        proc[i].arrival_time = input[i][1];
        proc[i].burst_time = input[i][2];
        initializeProcess(&proc[i]);  // Ensure remaining_time is set
    }

    fcfsScheduling(proc, num_processes);
    printProcesses(proc, num_processes);

    free(proc);
    return 0;
}