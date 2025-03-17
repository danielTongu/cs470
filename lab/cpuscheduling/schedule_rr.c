#include "process.h"

/**
 * @brief Executes one quantum slice of the selected process for Round Robin scheduling.
 * - Uses a **fixed time quantum** for execution.
 * - Updates the execution log and Gantt Chart.
 * - Prints the "Process starts" message only when switching to a new process.
 * - Does not print the "completes quantum" message.
 *
 * @param proc Array of processes.
 * @param index Index of the selected process.
 * @param time Pointer to the current time.
 * @param quantum Time quantum for Round Robin.
 * @param gantt_chart Array storing the execution order.
 * @param gc_index Pointer to the current Gantt Chart index.
 * @param last_index Pointer to the variable storing the index of the last process that executed.
 */
void executeRoundRobin(Process proc[], int index, int *time, int quantum, int gantt_chart[], int *gc_index, int *last_index) {
    // Print "Process starts" message only if switching to a new process.
    if (*last_index != index) {
        printf("Time %d: Process %d starts, (Burst time: %d)\n", *time, proc[index].process_id, proc[index].remaining_time);
        *last_index = index;  // Update last_index to the current process index.

        // Log the execution in the Gantt chart.
        gantt_chart[(*gc_index)++] = proc[index].process_id;
    }

    // Execute for the time quantum or until the process completes.
    int execution_time = (proc[index].remaining_time > quantum) ? quantum : proc[index].remaining_time;
    proc[index].remaining_time -= execution_time;
    *time += execution_time;

    // If the process finishes execution, print the completion message.
    if (proc[index].remaining_time == 0) {
        proc[index].completion_time = *time;
        printf("Time %d: Process %d completes\n", *time, proc[index].process_id);
    }
}

/**
 * @brief Implements Round Robin (RR) Scheduling without using a queue.
 * - Each process is given a fixed time quantum.
 * - Processes are scanned in the array order on each cycle.
 * - Before switching to a different process, if the previous process has not finished,
 *   prints "completes quantum" for that process.
 *
 * @param proc Array of processes.
 * @param num_processes Number of processes.
 * @param quantum Time quantum for Round Robin.
 */
void roundRobinScheduling(Process proc[], int num_processes, int quantum) {
    int time = 0, completed = 0;
    int gantt_chart[100], gc_index = 0;
    int last_index = -1;  // Holds the index of the last process that was executed; initialized to -1 (invalid index).

    printf("\n=== Round Robin Scheduling, Quantum: %d ===\n", quantum);

    // Continue scheduling until all processes have completed.
    while (completed < num_processes) {
        int executed = 0;  // Flag to check if any process was executed in this cycle.

        // Loop through all processes.
        for (int i = 0; i < num_processes; i++) {
            // Check if process has arrived and is not finished.
            if (proc[i].arrival_time <= time && proc[i].remaining_time > 0) {
                // If switching from a previous process to a new one,
                // and the previous process has not yet completed, print "completes quantum".
                if (last_index != -1 && last_index != i && proc[last_index].remaining_time > 0) {
                    printf("Time %d: Process %d completes quantum\n", time, proc[last_index].process_id);
                }
                // Execute one quantum slice for process at index i.
                executeRoundRobin(proc, i, &time, quantum, gantt_chart, &gc_index, &last_index);
                executed = 1;  // Mark that at least one process was executed in this cycle.

                // If the process completed during this quantum, count it.
                if (proc[i].remaining_time == 0) { completed++; }
            }
        }
        // If no process was executed in this full cycle, simply advance time.
        if (!executed) { time++; }
    }

    // Print the final Gantt Chart Execution Order.
    printf("\nGantt Chart Execution Order (Round Robin):\n");
    for (int i = 0; i < gc_index; i++) {
        printf("P%d ", gantt_chart[i]);
    }
    printf("\n");
}

/**
 * @brief Main function for Round Robin Scheduling.
 */
int main() {
    int input[][3] = {
        {1, 0, 24}, /* {process_id, arrival_time, burst_time} */
        {2, 0, 3},
        {3, 0, 3}
    };

    int num_processes = sizeof(input) / sizeof(input[0]);
    Process* proc = (Process*)malloc(num_processes * sizeof(Process));

    // Initialize each process.
    for (int i = 0; i < num_processes; i++) {
        initializeProcess(&proc[i]);
        proc[i].process_id = input[i][0];
        proc[i].arrival_time = input[i][1];
        proc[i].burst_time = input[i][2];
        proc[i].remaining_time = proc[i].burst_time; // Ensure remaining_time is set.
    }

    roundRobinScheduling(proc, num_processes, 4);
    printProcesses(proc, num_processes);

    free(proc);
    return 0;
}