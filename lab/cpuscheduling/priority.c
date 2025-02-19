#include <stdio.h>
#include <stdlib.h>

/**
 * @struct Process
 * @brief Structure to represent a process in Priority Scheduling
 */
typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int completion_time;
} Process;

/**
 * @brief QuickSort partition function (Sorting by Priority)
 * @param proc Array of processes
 * @param low Starting index
 * @param high Ending index
 * @return int Partition index
 */
int partition(Process proc[], int low, int high) {
    int pivot = proc[high].priority; // Lower priority number = higher priority
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (proc[j].priority < pivot) { // Higher priority first
            i++;
            Process temp = proc[i];
            proc[i] = proc[j];
            proc[j] = temp;
        }
    }

    Process temp = proc[i + 1];
    proc[i + 1] = proc[high];
    proc[high] = temp;
    return i + 1;
}

/**
 * @brief QuickSort algorithm to sort processes by priority
 * @param proc Array of processes
 * @param low Starting index
 * @param high Ending index
 */
void quickSort(Process proc[], int low, int high) {
    if (low < high) {
        int pi = partition(proc, low, high);
        quickSort(proc, low, pi - 1);
        quickSort(proc, pi + 1, high);
    }
}

/**
 * @brief Function to perform Priority Scheduling (Non-Preemptive)
 * @param proc Array of processes
 * @param n Number of processes
 */
void priorityScheduling(Process proc[], int n) {
    // Sort processes based on priority (lower number = higher priority)
    quickSort(proc, 0, n - 1);

    // Compute completion, waiting, and turnaround times
    proc[0].waiting_time = 0; // First process has no waiting time
    proc[0].completion_time = proc[0].arrival_time + proc[0].burst_time;
    proc[0].turnaround_time = proc[0].completion_time - proc[0].arrival_time;

    for (int i = 1; i < n; i++) {
        // Calculate waiting time as completion time of the previous process - arrival time
        proc[i].waiting_time = proc[i - 1].completion_time - proc[i].arrival_time;

        // Ensure waiting time is not negative (for idle CPU times)
        if (proc[i].waiting_time < 0) {
            proc[i].waiting_time = 0;
        }

        // Compute completion time
        proc[i].completion_time = proc[i].arrival_time + proc[i].waiting_time + proc[i].burst_time;

        // Compute turnaround time
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
    }
}

/**
 * @brief Function to print process details
 * @param proc Array of processes
 * @param n Number of processes
 */
void printProcesses(Process proc[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\tCompletion Time\n");

    for (int i = 0; i < n; i++) {
        printf(
            "%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            proc[i].process_id,
            proc[i].arrival_time,
            proc[i].burst_time,
            proc[i].priority,
            proc[i].waiting_time,
            proc[i].turnaround_time,
            proc[i].completion_time
        );
    }
}

int main() {
    // Define processes (process_id, arrival_time, burst_time, priority)
    Process proc[] = {
        {1, 0, 10, 2},
        {2, 1, 5, 1},
        {3, 2, 8, 3},
        {4, 3, 6, 1},
        {5, 4, 2, 4}
    };

    int n = sizeof(proc) / sizeof(proc[0]); // Number of processes

    priorityScheduling(proc, n);  // Perform Priority Scheduling
    printProcesses(proc, n); // Print process details

    return 0;
}