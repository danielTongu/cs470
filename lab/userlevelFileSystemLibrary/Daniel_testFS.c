#include "Daniel_libFS.h"
#include <ctype.h>  // For tolower()
#include <stdio.h>  // For standard I/O functions

// Function to display the menu
void displayMenu() {
    printf("\n--- Menu ---\n");
    printf("1. Create a file\n");
    printf("2. Open a file\n");
    printf("3. Write to a file\n");
    printf("4. Read from a file\n");
    printf("5. Close a file\n");
    printf("6. Delete a file\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

// Function to wait for user input to continue
void waitForUser() {
    printf("\nPress Enter to continue...");
    getchar();  // Wait for Enter key
}

// Main function to test file operations
int main() {
    char filename[MAX_FILENAME];
    char data[MAX_FILE_SIZE];
    int file_index = -1;  // Track the currently open file
    int choice;
    char buffer[MAX_FILE_SIZE];
    int bytes_read;

    while (1) {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');  // Clear invalid input
            continue;
        }
        getchar();  // Clear the newline character from the buffer

        switch (choice) {
            case 1:  // Create a file
                printf("Enter the filename to create: ");
                if (fgets(filename, MAX_FILENAME, stdin) == NULL) {
                    printf("Error reading filename.\n");
                    waitForUser();
                    break;
                }
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                if (fileCreate(filename) != 0) {
                    printf("Error creating file.\n");
                }
                waitForUser();
                break;

            case 2:  // Open a file
                printf("Enter the filename to open: ");
                if (fgets(filename, MAX_FILENAME, stdin) == NULL) {
                    printf("Error reading filename.\n");
                    waitForUser();
                    break;
                }
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                file_index = fileOpen(filename);
                if (file_index == -1) {
                    printf("Error opening file.\n");
                }
                waitForUser();
                break;

            case 3:  // Write to a file
                if (file_index == -1) {
                    printf("Error: No file is open. Please open a file first.\n");
                } else {
                    printf("Enter data to write to the file (end with a single '.'): \n");
                    data[0] = '\0';  // Initialize data buffer
                    char line[MAX_FILE_SIZE];
                    while (fgets(line, sizeof(line), stdin)) {
                        if (strcmp(line, ".\n") == 0) {
                            break;  // End input on single '.'
                        }
                        strcat(data, line);
                    }
                    if (fileWrite(file_index, data) != 0) {
                        printf("Error writing to file.\n");
                    }
                }
                waitForUser();
                break;

            case 4:  // Read from a file
                if (file_index == -1) {
                    printf("Error: No file is open. Please open a file first.\n");
                } else {
                    printf("Reading from file '%s'...\n", file_table[file_index].filename);
                    bytes_read = fileRead(file_index, buffer, sizeof(buffer) - 1);
                    if (bytes_read == -1) {
                        printf("Error reading from file.\n");
                    } else {
                        buffer[bytes_read] = '\0';  // Null-terminate the buffer
                        printf("Data read from file:\n%s\n", buffer);
                    }
                }
                waitForUser();
                break;

            case 5:  // Close a file
                if (file_index == -1) {
                    printf("Error: No file is open.\n");
                } else {
                    if (fileClose(file_index) == 0) {
                        file_index = -1;  // Reset file index after closing
                    } else {
                        printf("Error closing file.\n");
                    }
                }
                waitForUser();
                break;

            case 6:  // Delete a file
                printf("Enter the filename to delete: ");
                if (fgets(filename, MAX_FILENAME, stdin) == NULL) {
                    printf("Error reading filename.\n");
                    waitForUser();
                    break;
                }
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                if (fileDelete(filename) != 0) {
                    printf("Error deleting file.\n");
                }
                waitForUser();
                break;

            case 7:  // Exit
                printf("Exiting the program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                waitForUser();
                break;
        }
    }

    return 0;
}