#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent a process
typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int is_completed;
} Process;




int n; // Number of processes




/**
 * Function to find the index of the process with the shortest remaining time
 * @param proc Array of processes
 * @param current_time Current time in the scheduling process
 * @return Index of the process with the shortest remaining time, or -1 if none are available
 */
int findNextProcess(Process proc[], int current_time) {
    int min_time = INT_MAX;
    int index = -1;
    for (int i = 0; i < n; i++) {
        // Check if process has arrived and is not completed
        if (proc[i].arrival_time <= current_time && proc[i].remaining_time > 0 && proc[i].remaining_time < min_time) {
            min_time = proc[i].remaining_time;
            index = i;
        }
    }
    return index;
}




/**
 * Function to perform Shortest Remaining Time First (SRTF) scheduling
 * @param proc Array of processes
 */
void srtf(Process proc[]) {
    int current_time = 0;
    int completed = 0;

    // Initialize remaining times and process completion status
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].is_completed = 0;
    }

    // Execute processes in a loop until all are completed
    while (completed != n) {
        int index = findNextProcess(proc, current_time);

        if (index != -1) {
            proc[index].remaining_time--;
            current_time++;

            // If process is completed
            if (proc[index].remaining_time == 0) {
                proc[index].is_completed = 1;
                completed++;

                // Calculate turnaround time and waiting time
                proc[index].turnaround_time = current_time - proc[index].arrival_time;
                proc[index].waiting_time = proc[index].turnaround_time - proc[index].burst_time;
            }
        } else {
            current_time++; // No process available, advance time
        }
    }
}




/**
 * Function to print the processes and their details
 * @param proc Array of processes
 */
void printProcesses(Process proc[]) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf(
            "%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            proc[i].process_id,
            proc[i].arrival_time,
            proc[i].burst_time,
            proc[i].waiting_time,
            proc[i].turnaround_time
        );
    }
}




int main() {
    // Initialize processes with their IDs, arrival times, and burst times
    Process proc[] = {
        {1, 0, 8, 0, 0, 0, 0},
        {2, 1, 4, 0, 0, 0, 0},
        {3, 2, 9, 0, 0, 0, 0},
        {4, 3, 5, 0, 0, 0, 0}
    };

    n = sizeof(proc) / sizeof(proc[0]);

    // Execute Shortest Remaining Time First scheduling
    srtf(proc);

    // Print the final process details
    printProcesses(proc);

    return 0;
}
