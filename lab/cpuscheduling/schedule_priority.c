#include "process.h"

/**
 * @brief Finds the highest-priority available process.
 * - For both non-preemptive and preemptive priority scheduling, selects the process
 *   with the highest priority (lowest priority number) among those that have arrived.
 *
 * @param proc Array of processes.
 * @param num_processes Number of processes.
 * @param time Current system time.
 * @return Index of the selected process, or -1 if no process is available.
 */
int findHighestPriorityProcess(Process proc[], int num_processes, int time) {
    int min_index = -1;

    for (int i = 0; i < num_processes; i++) {
        if (proc[i].arrival_time <= time && proc[i].remaining_time > 0) {
            // For both non-preemptive and preemptive, select the process with the lowest priority number.
            if (min_index == -1 || proc[i].priority < proc[min_index].priority) {
                min_index = i;
            }
        }
    }
    return min_index;
}

/**
 * @brief Executes the selected process for Priority Scheduling.
 * - Updates execution log and Gantt Chart.
 * - For preemptive scheduling, the process runs for 1 time unit;
 *   for non-preemptive scheduling, the process runs to completion.
 * - In preemptive mode, the "Process starts" message is printed only when switching to a new process.
 *
 * @param proc Array of processes.
 * @param index Index of the selected process.
 * @param time Pointer to current time.
 * @param gantt_chart Array storing execution order.
 * @param gc_index Pointer to Gantt chart index.
 * @param preemptive Boolean flag (1 = preemptive, 0 = non-preemptive).
 * @param last_index Pointer to variable tracking the index of the last executed process.
 */
void executeProcessPriority(Process proc[], int index, int *time, int gantt_chart[], int *gc_index, int preemptive, int *last_index) {
    if (preemptive) {
        // In preemptive scheduling, print "Process starts" only if switching to a new process.
        if (*last_index != index) {
            printf("Time %d: Process %d starts (Burst time: %d) (Priority: %d)\n",
                   *time, proc[index].process_id, proc[index].remaining_time, proc[index].priority);
            *last_index = index;  // Update the last executed process index.

            // Log the process in the Gantt chart.
            gantt_chart[(*gc_index)++] = proc[index].process_id;
        }

    } else {
        // In non-preemptive scheduling, the process runs to completion so we always print the start message.
        printf("Time %d: Process %d starts (Burst time: %d) (Priority: %d)\n",
               *time, proc[index].process_id, proc[index].remaining_time, proc[index].priority);

        // Log the process in the Gantt chart.
        gantt_chart[(*gc_index)++] = proc[index].process_id;
    }



    // Determine execution time: 1 unit if preemptive, full burst time otherwise.
    int execution_time = (preemptive) ? 1 : proc[index].burst_time;
    proc[index].remaining_time -= execution_time;
    *time += execution_time;

    // If process completes execution, print the completion message.
    if (proc[index].remaining_time == 0) {
        proc[index].completion_time = *time;
        printf("Time %d: Process %d completes\n", *time, proc[index].process_id);
    }
}

/**
 * @brief Implements Priority Scheduling (Non-Preemptive).
 * - The process with the highest priority executes first.
 *
 * @param proc Array of processes.
 * @param num_processes Number of processes.
 */
void priorityScheduling(Process proc[], int num_processes) {
    int time = 0, completed = 0;
    int gantt_chart[100], gc_index = 0;
    int last_index = -1;  // Not used in non-preemptive mode, but passed for uniformity.

    printf("\n=== Priority Scheduling (Non-Preemptive) ===\n");

    while (completed < num_processes) {
        int index = findHighestPriorityProcess(proc, num_processes, time);
        if (index != -1) {
            executeProcessPriority(proc, index, &time, gantt_chart, &gc_index, 0, &last_index);
            completed++; // Process runs to completion.
        } else {
            time++; // Advance time if no process is available.
        }
    }

    // Print Gantt Chart Execution Order.
    printf("\nGantt Chart Execution Order (Priority Non-Preemptive):\n");
    for (int i = 0; i < gc_index; i++) {
        printf("P%d ", gantt_chart[i]);
    }
    printf("\n");
}

/**
 * @brief Implements Preemptive Priority Scheduling.
 * - If a new process arrives with a higher priority, it preempts the current process.
 * - Additionally, if switching from one process to another, and the previous process is not yet finished,
 *   prints a "completes quantum" message for the previous process.
 *
 * @param proc Array of processes.
 * @param num_processes Number of processes.
 */
void priorityPreemptiveScheduling(Process proc[], int num_processes) {
    int time = 0, completed = 0;
    int gantt_chart[100], gc_index = 0;
    int last_index = -1;  // Track the index of the last process that was executed.

    printf("\n=== Priority Scheduling (Preemptive) ===\n");

    while (completed < num_processes) {
        int index = findHighestPriorityProcess(proc, num_processes, time);
        if (index != -1) {
            // If switching from a previous process (that hasn't finished) to a new one,
            // print "completes quantum" for the previous process.
            if (last_index != -1 && last_index != index && proc[last_index].remaining_time > 0) {
                printf("Time %d: Process %d completes quantum\n", time, proc[last_index].process_id);
            }
            executeProcessPriority(proc, index, &time, gantt_chart, &gc_index, 1, &last_index);
            if (proc[index].remaining_time == 0) {
                completed++;
            }
        } else {
            time++; // Advance time if no process is available.
        }
    }

    // Print Gantt Chart Execution Order.
    printf("\nGantt Chart Execution Order (Priority Preemptive):\n");
    for (int i = 0; i < gc_index; i++) {
        printf("P%d ", gantt_chart[i]);
    }
    printf("\n");
}

/**
 * @brief Main function for Priority Scheduling.
 */
int main() {
    int input[][4] = {
        {1, 0, 8, 3},  /* {process_id, arrival_time, burst_time, priority} */
        {2, 1, 4, 1},
        {3, 2, 9, 4},
        {4, 3, 5, 2}
    };

    int num_processes = sizeof(input) / sizeof(input[0]);
    Process* proc = (Process*)malloc(num_processes * sizeof(Process));

    // Non-preemptive Priority Scheduling: Initialize processes.
    for (int i = 0; i < num_processes; i++) {
        initializeProcess(&proc[i]);
        proc[i].process_id = input[i][0];
        proc[i].arrival_time = input[i][1];
        proc[i].burst_time = input[i][2];
        proc[i].priority = input[i][3];
        proc[i].remaining_time = proc[i].burst_time; // Ensure remaining_time is set.
    }

    priorityScheduling(proc, num_processes);
    printProcesses(proc, num_processes);

    // Reset processes for Preemptive Priority Scheduling.
    for (int i = 0; i < num_processes; i++) {
        initializeProcess(&proc[i]);
        proc[i].process_id = input[i][0];
        proc[i].arrival_time = input[i][1];
        proc[i].burst_time = input[i][2];
        proc[i].priority = input[i][3];
        proc[i].remaining_time = proc[i].burst_time; // Ensure remaining_time is set.
    }

    // Preemptive Priority Scheduling.
    priorityPreemptiveScheduling(proc, num_processes);
    printProcesses(proc, num_processes);

    free(proc);
    return 0;
}