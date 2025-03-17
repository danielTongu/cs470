#include "process.h"

void initializeProcess(Process *p) {
    p->process_id = 0;
    p->arrival_time = 0;
    p->burst_time = 0;
    p->remaining_time = 0;
    p->completion_time = 0;
    p->is_completed = 0;
    p->priority = 0;
    p->time_quantum = 0;
}

int calculateTurnarroundTime(Process *p) {
    return p->completion_time - p->arrival_time;
}

int calculateWaitingTime(Process *p) {
    return calculateTurnarroundTime(p) - p->burst_time;
}

void printProcesses(Process proc[], int num_processes) {
    int i;
    printf("\nProcess Details:\n");
    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (i = 0; i < num_processes; i++) {
        int tat = calculateTurnarroundTime(&proc[i]);
        int wt = calculateWaitingTime(&proc[i]);
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n", proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].completion_time, tat, wt);
    }
}