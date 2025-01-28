#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Main function to copy a file using the `cp` command.
 * 
 * This program takes two command-line arguments: the source file
 * and the destination file. It then executes the `cp` command using
 * `system()` to copy the file.
 * 
 * @param argc Argument count
 * @param argv Argument vector (array of arguments)
 * @return int Returns 0 on success, 1 on failure
 */
int main(int argc, char *argv[]) {
    // Ensure correct number of arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    // Construct the command string
    char command[512];
    snprintf(command, sizeof(command), "cp %s %s", argv[1], argv[2]);

    // Execute the command
    int status = system(command);

    // Check if the command executed successfully
    if (status == -1) {
        perror("system");
        return 1;
    }

    printf("File copied successfully from %s to %s\n", argv[1], argv[2]);
    return 0;
}