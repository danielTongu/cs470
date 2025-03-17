#include "process.h"

/**
 * @brief Finds the shortest available process at the current time.
 * - For Non-Preemptive SJF: Selects process with the **shortest burst time**.
 * - For Preemptive SJF (SRTF): Selects process with the **shortest remaining time**.
 *
 * @param proc Array of processes.
 * @param num_processes Number of processes.
 * @param time Current system time.
 * @param preemptive Boolean flag (1 = preemptive, 0 = non-preemptive).
 * @return Index of the selected process, or -1 if no process is available.
 */
int findShortestAvailableProcess(Process proc[], int num_processes, int time, int preemptive) {
    int min_index = -1;

    for (int i = 0; i < num_processes; i++) {
        if (proc[i].arrival_time <= time && proc[i].remaining_time > 0) {
            if (min_index == -1 ||
                (preemptive ? proc[i].remaining_time < proc[min_index].remaining_time
                            : proc[i].burst_time < proc[min_index].burst_time)) {
                min_index = i;
            }
        }
    }
    return min_index;
}

/**
 * @brief Executes the selected process.
 * - Updates execution log and Gantt Chart.
 * - Handles both **preemptive (SRTF)** and **non-preemptive (SJF)** cases.
 * - Prints the "Process starts" message only if switching to a new process.
 *
 * @param proc Array of processes.
 * @param index Index of the selected process.
 * @param time Pointer to current time.
 * @param gantt_chart Array storing execution order.
 * @param gc_index Pointer to Gantt chart index.
 * @param preemptive Boolean flag (1 = preemptive, 0 = non-preemptive).
 * @param last_process Pointer to the variable storing the last process ID that started.
 */
void executeProcess(Process proc[], int index, int *time, int gantt_chart[], int *gc_index, int preemptive, int *last_process) {
    // Only print the start message if switching to a new process.
    if (*last_process != proc[index].process_id) {
        printf("Time %d: Process %d starts, (Burst time: %d)\n", *time, proc[index].process_id, proc[index].remaining_time);
        *last_process = proc[index].process_id;  // Update last_process to current process ID

        // Log process execution in the Gantt chart.
        gantt_chart[(*gc_index)++] = proc[index].process_id;
    }

    // Calculate execution time: for preemptive scheduling, execute one time unit; otherwise, the entire burst time.
    int execution_time = (preemptive) ? 1 : proc[index].burst_time;
    proc[index].remaining_time -= execution_time;
    *time += execution_time;

    // If process completes execution, print completion message.
    if (proc[index].remaining_time == 0) {
        proc[index].completion_time = *time;
        printf("Time %d: Process %d completes\n", *time, proc[index].process_id);
    }
}

/**
 * @brief Implements Shortest Job First (Non-Preemptive)
 * - The process with the **shortest burst time** executes first.
 */
void sjfScheduling(Process proc[], int num_processes) {
    int time = 0, completed = 0;
    int gantt_chart[100], gc_index = 0;
    int last_process = -1;  // Initialize to an invalid process ID

    printf("\n=== Shortest Job First (Non-Preemptive) ===\n");

    while (completed < num_processes) {
        int index = findShortestAvailableProcess(proc, num_processes, time, 0);

        if (index != -1) {
            // Execute the process and update the last process if needed.
            executeProcess(proc, index, &time, gantt_chart, &gc_index, 0, &last_process);
            completed++; // In non-preemptive scheduling, process finishes in one go.
        } else {
            time++; // No process is available; increment time.
        }
    }

    // Print Gantt Chart Execution Order.
    printf("\nGantt Chart Execution Order (SJF Non-Preemptive):\n");
    for (int i = 0; i < gc_index; i++) {
        printf("P%d ", gantt_chart[i]);
    }
    printf("\n");
}

/**
 * @brief Implements Shortest Remaining Time First (SJF Preemptive)
 * - If a new process arrives with a shorter remaining time, it preempts the current process.
 */
void sjfPreemptiveScheduling(Process proc[], int num_processes) {
    int time = 0, completed = 0;
    int gantt_chart[100], gc_index = 0;
    int last_process = -1;  // Initialize to an invalid process ID

    printf("\n=== Shortest Job First (Preemptive - Shortest Remaining Time First) ===\n");

    while (completed < num_processes) {
        int index = findShortestAvailableProcess(proc, num_processes, time, 1);

        if (index != -1) {
            // Execute the process; if it is the same as the last one, the start message won't print.
            executeProcess(proc, index, &time, gantt_chart, &gc_index, 1, &last_process);
            if (proc[index].remaining_time == 0) {
                completed++;
            }
        } else {
            time++; // No process available; move time forward.
        }
    }

    // Print Gantt Chart Execution Order.
    printf("\nGantt Chart Execution Order (SJF Preemptive):\n");
    for (int i = 0; i < gc_index; i++) {
        printf("P%d ", gantt_chart[i]);
    }
    printf("\n");
}

/**
 * @brief Main function for SJF Scheduling.
 */
int main() {
    int input[][3] = {
        {1, 0, 8},  /* {process_id, arrival_time, burst_time} */
        {2, 1, 4},
        {3, 2, 9},
        {4, 3, 5}
    };

    int num_processes = sizeof(input) / sizeof(input[0]);
    Process* proc = (Process*)malloc(num_processes * sizeof(Process));

    // Initialize processes for Non-preemptive SJF.
    for (int i = 0; i < num_processes; i++) {
        initializeProcess(&proc[i]);
        proc[i].process_id = input[i][0];
        proc[i].arrival_time = input[i][1];
        proc[i].burst_time = input[i][2];
        proc[i].remaining_time = proc[i].burst_time; // Ensure remaining_time is set
    }

    sjfScheduling(proc, num_processes);
    printProcesses(proc, num_processes);

    // Reset processes for Preemptive SJF.
    for (int i = 0; i < num_processes; i++) {
        initializeProcess(&proc[i]);
        proc[i].process_id = input[i][0];
        proc[i].arrival_time = input[i][1];
        proc[i].burst_time = input[i][2];
        proc[i].remaining_time = proc[i].burst_time; // Ensure remaining_time is set
    }

    // Execute Preemptive - Shortest Remaining Time First scheduling.
    sjfPreemptiveScheduling(proc, num_processes);
    printProcesses(proc, num_processes);

    free(proc);
    return 0;
}