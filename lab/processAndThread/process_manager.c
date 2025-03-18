#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#define NUM_CHILDREN 10  /**< Ensures exactly 10 child processes are created */
#define MAX_ARGS 3       /**< Maximum arguments per command (command + argument + NULL for execvp) */


/**
 * @brief Main function to create child processes and execute predefined commands.
 *
 * This program:
 * 1. Defines a set of shell commands.
 * 2. Creates child processes to execute the commands using `execvp()`.
 * 3. The parent process waits for all children to finish.
 *
 * @return int Returns 0 on success, exits with failure status otherwise.
 */
int main() {
    pid_t pid;      /**< Process ID for child processes */
    int status;     /**< Variable to store child exit status */


    /**
     * @brief List of commands to be executed by child processes.
     *
     * Each command is represented as a NULL-terminated array of strings.
     * - `MAX_ARGS` ensures a fixed structure for memory safety.
     * - Each row contains a command and its optional argument.
     */
    char *commands[][MAX_ARGS] = {
        {"echo", "Hello Daniel, this is the first listed command", NULL},  // Print a message
        {"ls", "-l", NULL},              // List directory contents in long format
        {"pwd", NULL, NULL},             // Print current working directory
        {"date", NULL, NULL},            // Display system date and time
        {"ps", NULL, NULL},              // Display active processes
        {"uptime", NULL, NULL},          // Show system uptime
        {"df", "-h", NULL}              // Display disk space usage
    };


    // Dynamically determine the number of available commands
    size_t num_commands = sizeof(commands) / sizeof(commands[0]);
    printf("[Parent PID: %d] Creating %d child processes...\n", getpid(), NUM_CHILDREN);


    /**
     * @brief Loop to create child processes and assign commands.
     * - Each child executes a command from the predefined list.
     * - If more children than commands, it cycles through commands.
     */
    for (int i = 0; i < NUM_CHILDREN; i++) {
        printf("[Parent PID: %d] Creating child process %d...\n", getpid(), i + 1);
        pid = fork();  // Fork a new process

        if (pid < 0) { /* If fork fails, print error and exit */
            fprintf(stderr, "[Parent PID: %d] Failed to create child process [%d]: ", getpid(), i + 1);
            perror("Fork failed");
            exit(EXIT_FAILURE);

        } else if (pid == 0) { /* Child process */
            // Determine which command to execute (cycle through commands if needed)
            int cmd_index = i % num_commands;
            printf("[Child %d | PID: %d] Executing command: %s\n", i + 1, getpid(), commands[cmd_index][0]);

            // Execute the command in the child process
            execvp(commands[cmd_index][0], commands[cmd_index]);

            // If execvp() fails, print an error and terminate the child
            fprintf(stderr, "[Child %d | PID: %d] Failed to execute command '%s': ", i + 1, getpid(), commands[cmd_index][0]);
            perror("execvp failed");
            exit(EXIT_FAILURE);
        }
        // Parent process continues to loop and create more children
    }


    // Parent process waits for all child processes to complete
    while ((pid = wait(&status)) > 0) {
        // Check if the child process exited normally
        if (WIFEXITED(status)) {
            printf("[Parent PID: %d] Child process (PID: %d) finished with exit status %d\n", getpid(), pid, WEXITSTATUS(status));
        }
        // Check if the child process was terminated by a signal
        else if (WIFSIGNALED(status)) {
            printf("[Parent PID: %d] Child process (PID: %d) terminated by signal %d\n", getpid(), pid, WTERMSIG(status));
        }
        // Handle other abnormal termination cases
        else {
            printf("[Parent PID: %d] Child process (PID: %d) ended abnormally\n", getpid(), pid);
        }
    }


    // Final message indicating all child processes have completed
    printf("[Parent PID: %d] All %d child processes have completed. Parent process exiting.\n", getpid(), NUM_CHILDREN);


    return EXIT_SUCCESS;
}