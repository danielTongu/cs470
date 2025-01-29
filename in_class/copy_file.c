#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief Main function to create directories and copy files using execvp.
 *
 * This program:
 * 1. Creates `source_dir` and `des_dir` using the `mkdir -p` command.
 * 2. Creates three `.txt` files inside `source_dir` using `touch`.
 * 3. Uses `execvp()` to copy the entire `source_dir` into `des_dir`.
 *
 * @return int Returns 0 on success, exits with failure status otherwise.
 */
int main() {
    // Create source and destination directories
    if (system("mkdir -p source_dir des_dir") == -1) {
        perror("Failed to create directories");
        exit(EXIT_FAILURE);
    }

    // Create three text files inside the source directory
    if (system("touch source_dir/file1.txt source_dir/file2.txt source_dir/file3.txt") == -1) {
        perror("Failed to create files");
        exit(EXIT_FAILURE);
    }

    // Prepare the arguments for execvp
    char *args[] = {
        "cp",     // Command label
        "-r",     // Recursive copy flag (to copy directories)
        "source_dir",
        "des_dir",
        NULL      // Null-terminator for execvp
    };

    printf("Copying files from source_dir to des_dir...\n");

    // Execute the copy command
    execvp("cp", args);

    // If execvp fails, print an error message and exit
    perror("execvp failed");
    exit(EXIT_FAILURE);
}