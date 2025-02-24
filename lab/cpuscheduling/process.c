//process.c

#include "process.h"


void initializeProcess(Process *p) {
    p->remaining_time = p->burst_time;
    p->waiting_time = 0;
    p->turnaround_time = 0;
    p->completion_time = 0;
    p->is_completed = 0;
    p->priority = 0; // Default priority
    p->start_time = -1; // Indicates process has not started yet
    p->response_time = -1; // Not yet calculated
    p->queue_level = 0; // Default queue level
    p->time_quantum = 0; // Default time quantum
}


void printProcesses(Process proc[], int num_processes) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < num_processes; i++) {
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
