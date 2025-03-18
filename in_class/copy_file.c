#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



#define SOURCE_DIR "source_dir"   /**< Name of the source directory */
#define DEST_DIR "des_dir"        /**< Name of the destination directory */
#define FILE_EXT ".txt"           /**< File extension for the created files */
#define CMD_BUFFER_SIZE 512       /**< Buffer size for storing shell commands */



/**
 * @brief Main function to create directories and copy files using execvp.
 *
 * This program performs the following steps:
 * 1. Creates `SOURCE_DIR` and `DEST_DIR` using the `mkdir -p` command.
 * 2. Creates three `.txt` files inside `SOURCE_DIR` using `touch`.
 * 3. Uses `execvp()` to copy the entire `SOURCE_DIR` into `DEST_DIR`.
 *
 * @return int Returns 0 on success, exits with failure status otherwise.
 */
int main() {
    char command[CMD_BUFFER_SIZE];  /**< Buffer to store system commands dynamically */



    /**
     * Step 1: Create source and destination directories.
     * - `snprintf()` safely constructs a command string to create both directories.
     * - `mkdir -p` ensures that directories are created only if they don’t already exist.
     */
    snprintf(command, sizeof(command), "mkdir -p %s %s", SOURCE_DIR, DEST_DIR);
    if (system(command) == -1) {
        perror("Failed to create directories");
        exit(EXIT_FAILURE);
    }



    /**
     * Step 2: Create three text files inside the source directory.
     * - `snprintf()` formats the `touch` command to create multiple files.
     * - This avoids hardcoded file names, making modifications easier.
     */
    snprintf(command, sizeof(command), "touch %s/file1%s %s/file2%s %s/file3%s",
             SOURCE_DIR, FILE_EXT, SOURCE_DIR, FILE_EXT, SOURCE_DIR, FILE_EXT);
    if (system(command) == -1) {
        perror("Failed to create files");
        exit(EXIT_FAILURE);
    }



    /**
     * Step 3: Prepare the arguments for `execvp()`
     * - The `cp` command is used to copy files recursively from SOURCE_DIR to DEST_DIR.
     * - `execvp()` replaces the current process with the new process.
     * - The last argument must be `NULL` to mark the end of the argument list.
     */
    char *args[] = {
        "cp",     /**< Command name for copying files */
        "-r",     /**< Recursive flag to copy directories */
        SOURCE_DIR,
        DEST_DIR,
        NULL      /**< Null-terminator for execvp */
    };



    printf("Copying files from %s to %s...\n", SOURCE_DIR, DEST_DIR);



    /**
     * Step 4: Execute the copy command using `execvp()`
     * - If `execvp()` succeeds, it replaces the current process, so code after this call won’t execute.
     * - If it fails, an error message is printed, and the program exits with failure status.
     */
    execvp("cp", args);



    // If execvp fails, print an error message and exit
    perror("execvp failed");
    exit(EXIT_FAILURE);
}