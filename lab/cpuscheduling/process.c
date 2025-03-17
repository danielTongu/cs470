//process.c

#include "process.h"

void initializeProcess(Process *p) {
    p->remaining_time = p->burst_time;  // Used for Preemptive Scheduling
    p->completion_time = 0;
    p->is_completed = 0; // Mark as not completed
    p->priority = 0; // Default priority (used in Priority Scheduling)
    p->start_time = -1; // Indicates the process has not started execution
    p->response_time = -1; // Response time not yet calculated
    p->queue_level = 0; // Default queue level (for Multilevel Queue Scheduling)
    p->time_quantum = 0; // Default time quantum (only used in RR if needed per process)
}

int calculateTurnarroundTime(Process *p) {
    return p->completion_time - p->arrival_time;
}

int calculateWaitingTime(Process *p) {
    return p->completion_time - p->arrival_time - p->burst_time;
}

void printProcesses(Process proc[], int num_processes) {
    printf("\nProcess ID\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n");

    float avg_tat = 0, avg_wt = 0;

    for (int i = 0; i < num_processes; i++) {
        int turnarround_time =  calculateWaitingTime(&proc[i]);
        int waiting_time = calculateTurnarroundTime(&proc[i]);

        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id,
               proc[i].arrival_time,
               proc[i].burst_time,
               turnarround_time,
               waiting_time
        );

        // Calculate and display average turnaround time and waiting time
        avg_tat += turnarround_time;
        avg_wt += waiting_time;
    }

    avg_tat /= num_processes;
    avg_wt /= num_processes;

    printf("\nAverage Turnaround Time: %.2f ms\n", avg_tat);
    printf("Average Waiting Time: %.2f ms\n", avg_wt);
}