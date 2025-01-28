#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#define NUM_CHILDREN 10  // Define the number of child processes



/**
 * Function to execute a command in a child process.
 * This function replaces the child process with a new program using execvp().
 * @param command The command to execute (array of strings).
 */
void execute_command(char *command[]) {
    execvp(command[0], command);

    // If execvp() fails, print an error and exit the child process
    perror("execvp failed");
    exit(EXIT_FAILURE);
}





int main() {
    pid_t pids[NUM_CHILDREN];  // Array to store child process PIDs
    int status;                // Variable to store child process exit status



    // List of commands that each child process will execute
    char *commands[NUM_CHILDREN][3] = {
        {"echo", "Hello Daniel", NULL},  // Print custom message
        {"ls", "-l", NULL},                   // List directory contents in long format
        {"pwd", NULL, NULL},                   // Print current working directory
        {"date", NULL, NULL},                  // Display system date and time
        {"whoami", NULL, NULL},                // Show current user
        {"ps", NULL, NULL},                    // Display active processes
        {"uptime", NULL, NULL},                // Show system uptime
        {"hostname", NULL, NULL},              // Show system hostname
        {"df", "-h", NULL},                    // Display disk space usage
        {"id", NULL, NULL}                     // Show user ID and group ID
    };



    printf("Parent process (PID: %d) is creating %d child processes...\n", getpid(), NUM_CHILDREN);



    // Loop to create child processes
    for (int i = 0; i < NUM_CHILDREN; i++) {
        pids[i] = fork();  // Create a new child process

        if (pids[i] < 0) {  // If fork fails
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pids[i] == 0) { // Child process executes here
            printf("Child process %d (PID: %d) executing: %s\n", i + 1, getpid(), commands[i][0]);
            execute_command(commands[i]);  // Execute command
        }
    }



    // Parent process waits for all child processes to complete
    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid_t pid = waitpid(pids[i], &status, 0);  // Wait for specific child

        if (pid > 0) {  // If waitpid was successful
            if (WIFEXITED(status)) {  // If the child exited normally
                printf("Child PID %d exited normally with status %d\n", pid, WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {  // If child was terminated by a signal
                printf("Child PID %d was terminated by signal %d\n", pid, WTERMSIG(status));
            }
        }
    }



    printf("All %d child processes have completed. Parent process exiting.\n", NUM_CHILDREN);



    return 0;  // Successful execution
}