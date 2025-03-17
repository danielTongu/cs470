//process.h

#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


/**
 * @struct Process
 * @brief Structure to represent a process for CPU scheduling.
 * Lower effective priority means a higher scheduling priority.
 */
typedef struct {
  int process_id;      /**< Unique identifier for the process. */
  int arrival_time;    /**< Time at which the process arrives. */
  int burst_time;      /**< Total CPU time required. */
  int remaining_time;  /**< Remaining CPU time (used in preemptive scheduling). */
  int completion_time; /**< Time at which the process completes execution. */
  int is_completed;    /**< Flag to indicate if the process has completed. */
  int priority;        /**< Original priority (lower number means higher priority). */
  int time_quantum;    /**< Time quantum for Round Robin scheduling (if needed). */
} Process;


/**
 * @brief Initializes a Process with default values.
 * @param p Pointer to the Process to be initialized.
 */
void initializeProcess(Process *p);


/**
 * @brief Calculates the turnaround time of a process.
 * @param p Pointer to the Process.
 * @return Turnaround time.
 */
int calculateTurnarroundTime(Process *p);


/**
 * @brief Calculates the waiting time of a process.
 * @param p Pointer to the Process.
 * @return Waiting time.
 */
int calculateWaitingTime(Process *p);


/**
 * @brief Prints the process information.
 * @param proc Array of processes.
 * @param num_processes Number of processes.
 */
void printProcesses(Process proc[], int num_processes);

#endif // PROCESS_H
