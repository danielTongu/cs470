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
 *
 * @param p Pointer to the Process to be initialized.
 */
void initializeProcess(Process *p);

/**
 * @brief Creates a Process with process ID, arrival time, and burst time.
 *
 * @param process_id The ID of the process
 * @param arrival_time The arrival time of the process
 * @param burst_time The burst time of the process
 * @return Process The initialized process
 */
Process createProcess(int process_id, int arrival_time, int burst_time);



/**
 * @brief Creates an array of processes from a 2D input array.
 *
 * @param input 2D array containing process information
 * @param size Number of processes in the input array
 * @return Process* Pointer to dynamically allocated array of processes
 */
Process* createProcessArray(int input[][3], int size);



/**
 * @brief Prints the process information. This will be defined by the scheduling algorithm.
 *
 * @param proc Array of processes
 * @param num_processes Number of processes
 */
void printProcesses(Process proc[], int num_processes);

#endif // PROCESS_H
