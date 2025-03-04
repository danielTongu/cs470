//process.h

#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


/**
 * @struct Process
 * @brief Structure to represent a process for CPU scheduling
 */
typedef struct {
     int process_id;
     int arrival_time;
     int burst_time;
     int remaining_time;  // Used in Preemptive Scheduling & Round Robin
     int waiting_time;
     int turnaround_time;
     int completion_time;
     int is_completed;    // Used in Non-Preemptive Scheduling (FCFS, SJF, Priority)
     int priority;        // Needed for Priority Scheduling
     int start_time;      // First time the process gets CPU (for Response Ratio Scheduling)
     int response_time;   // Response time for Response Ratio algorithms
     int queue_level;     // For Multilevel Queue Scheduling
     int time_quantum;    // For Round Robin scheduling (if specific to a process)
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
