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

Process createProcess(int process_id, int arrival_time, int burst_time) {
    Process p;
    p.process_id = process_id;
    p.arrival_time = arrival_time;
    p.burst_time = burst_time;
    initializeProcess(&p);
    return p;
}

Process* createProcessArray(int input[][3], int size) {
    Process *processes = (Process*)malloc(size * sizeof(Process));

    for (int i = 0; i < size; i++) {
        processes[i] = createProcess(input[i][0], input[i][1], input[i][2]);
    }
    return processes;
}

void printProcesses(Process proc[], int num_processes) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < num_processes; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time, proc[i].completion_time);
    }
}
