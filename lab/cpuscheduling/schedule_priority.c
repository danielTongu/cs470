#include "process.h"




/**
 * @brief Finds the highest-priority available process.
 * - For Non-Preemptive Priority Scheduling: Selects process with the **highest priority** (lowest priority number).
 * - For Preemptive Priority Scheduling: Dynamically selects the process with the **highest priority at any given time**.
 *
 * @param proc Array of processes.
 * @param num_processes Number of processes.
 * @param time Current system time.
 * @param preemptive Boolean flag (1 = preemptive, 0 = non-preemptive). [Now used properly]
 * @return Index of the selected process, or -1 if no process is available.
 */
int findHighestPriorityProcess(Process proc[], int num_processes, int time, int preemptive) {
    int min_index = -1;

    for (int i = 0; i < num_processes; i++) {
        if (proc[i].arrival_time <= time && proc[i].remaining_time > 0) {
            // Non-preemptive: Selects the first available highest priority process
            if (!preemptive && (min_index == -1 || proc[i].priority < proc[min_index].priority)) {
                min_index = i;
            }

            // Preemptive: Continuously selects the highest priority process available
            if (preemptive && (min_index == -1 || proc[i].priority < proc[min_index].priority)) {
                min_index = i;
            }
        }
    }
    return min_index;
}




/**
 * @brief Executes the selected process.
 * - Updates execution log and Gantt Chart.
 * - Handles both **preemptive** and **non-preemptive** priority scheduling.
 *
 * @param proc Array of processes.
 * @param index Index of the selected process.
 * @param time Pointer to current time.
 * @param gantt_chart Array storing execution order.
 * @param gc_index Pointer to Gantt chart index.
 * @param preemptive Boolean flag (1 = preemptive, 0 = non-preemptive).
 */
void executeProcessPriority(Process proc[], int index, int *time, int gantt_chart[], int *gc_index, int preemptive) {
    if (index == -1) {
        (*time)++;  // Move time forward if no process is available
        return;
    }

    printf("Time %d: Process %d starts (Priority %d)\n", *time, proc[index].process_id, proc[index].priority);
    gantt_chart[(*gc_index)++] = proc[index].process_id;

    // Execution time: 1 unit (preemptive) or entire burst time (non-preemptive)
    int execution_time = (preemptive) ? 1 : proc[index].burst_time;
    proc[index].remaining_time -= execution_time;
    *time += execution_time;

    // If process completes execution
    if (proc[index].remaining_time == 0) {
        proc[index].completion_time = *time;
        proc[index].turnaround_time = proc[index].completion_time - proc[index].arrival_time;
        proc[index].waiting_time = proc[index].turnaround_time - proc[index].burst_time;
        printf("Time %d: Process %d completes\n", *time, proc[index].process_id);
    }
}




/**
 * @brief Implements Priority Scheduling (Non-Preemptive)
 * - The process with the **highest priority** executes first.
 */
void priorityScheduling(Process proc[], int num_processes) {
    int time = 0, completed = 0;
    int gantt_chart[100], gc_index = 0;

    printf("\n=== Priority Scheduling (Non-Preemptive) ===\n");

    while (completed < num_processes) {
        int index = findHighestPriorityProcess(proc, num_processes, time, 0);

        if (index != -1) {
            executeProcessPriority(proc, index, &time, gantt_chart, &gc_index, 0);
            completed++; // Process finishes in one execution
        } else {
            time++; // Move time forward if no process is available
        }
    }

    // Print Gantt Chart Execution Order
    printf("\nGantt Chart Execution Order (Priority Non-Preemptive):\n");
    for (int i = 0; i < gc_index; i++) {
        printf("P%d ", gantt_chart[i]);
    }
    printf("\n");
}




/**
 * @brief Implements Preemptive Priority Scheduling.
 * - If a new process arrives with a higher priority, it **preempts the current process**.
 */
void priorityPreemptiveScheduling(Process proc[], int num_processes) {
    int time = 0, completed = 0;
    int gantt_chart[100], gc_index = 0;

    printf("\n=== Priority Scheduling (Preemptive) ===\n");

    while (completed < num_processes) {
        int index = findHighestPriorityProcess(proc, num_processes, time, 1);

        if (index != -1) {
            executeProcessPriority(proc, index, &time, gantt_chart, &gc_index, 1);
            if (proc[index].remaining_time == 0) {
                completed++;
            }
        } else {
            time++; // Move time forward if no process is available
        }
    }

    // Print Gantt Chart Execution Order
    printf("\nGantt Chart Execution Order (Priority Preemptive):\n");
    for (int i = 0; i < gc_index; i++) {
        printf("P%d ", gantt_chart[i]);
    }
    printf("\n");
}




/**
 * @brief Main function for Priority Scheduling
 */
int main() {
    int input[][4] = {
        {1, 0, 8, 3},  /* {process_id,  arrival_time,  burst_time, priority} */
        {2, 1, 4, 1},
        {3, 2, 9, 4},
        {4, 3, 5, 2}
    };

    int num_processes = sizeof(input) / sizeof(input[0]);
    Process* proc = (Process*)malloc(num_processes * sizeof(Process));

    // Non-preemptive Priority Scheduling
    for (int i = 0; i < num_processes; i++) {
        initializeProcess(&proc[i]);
        proc[i].process_id = input[i][0];
        proc[i].arrival_time = input[i][1];
        proc[i].burst_time = input[i][2];
        proc[i].priority = input[i][3];
        proc[i].remaining_time = proc[i].burst_time;// Ensure remaining_time is set
    }

    priorityScheduling(proc, num_processes);
    printProcesses(proc, num_processes);

    // Reset processes for Preemptive Priority Scheduling
    for (int i = 0; i < num_processes; i++) {
        initializeProcess(&proc[i]);
        proc[i].process_id = input[i][0];
        proc[i].arrival_time = input[i][1];
        proc[i].burst_time = input[i][2];
        proc[i].priority = input[i][3];
        proc[i].remaining_time = proc[i].burst_time;// Ensure remaining_time is set
    }

    // Preemptive Priority Scheduling
    priorityPreemptiveScheduling(proc, num_processes);
    printProcesses(proc, num_processes);

    free(proc);
    return 0;
}