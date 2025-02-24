//process.h

#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


/**
 * @struct Process
 * @brief Structure to represent a process for various scheduling algorithms
 */
typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    int is_completed;
    int priority; // For priority scheduling
    int start_time; // First time the process gets the CPU
    int response_time; // Response time for response ratio algorithms
    int queue_level; // For multilevel queue scheduling
    int time_quantum; // For round robin scheduling
} Process;


/**
 * @brief Initializes a Process with default values.
 * @param p Pointer to the Process to be initialized.
 */
void initializeProcess(Process *p);


/**
 * @brief Prints the process information.
 * @param proc Array of processes
 * @param num_processes Number of processes
 */
void printProcesses(Process proc[], int num_processes);



#endif // PROCESS_H
