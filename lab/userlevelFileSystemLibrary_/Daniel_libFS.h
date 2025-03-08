#ifndef DANIEL_LIBFS_H
#define DANIEL_LIBFS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For unlink() function (used in file deletion)


// ----- Constants -----
#define MAX_FILES 100
#define MAX_FILENAME 50
#define MAX_FILE_SIZE 1024


// ----- File system structures -----


/**
 * Structure representing a file entry in the file system.
 */
typedef struct {
    char filename[MAX_FILENAME]; /**< Name of the file */
    int size;                    /**< Size of the file in bytes */
    int is_open;                 /**< Flag indicating if the file is open (1) or closed (0) */
} FileEntry;



// ----- Global Variables -----
/**
 * Global file table tracking all files in the system.
 * Defined in Daniel_libFS.c, but referenced in other files using `extern`.
 */
extern FileEntry file_table[MAX_FILES];



/**
 * Global variable to track the number of files.
 */
extern int file_count;



// ----- Function prototypes -----


/**
 * Creates a new file in the file system.
 *
 * @param filename The name of the file to create.
 * @return 0 if successful, or -1 if an error occurs.
 */
int fileCreate(const char *filename);



/**
 * Opens an existing file in the file system.
 *
 * @param filename The name of the file to open.
 * @return The index of the file in the file table if successful, or -1 if an error occurs.
 */
int fileOpen(const char *filename);



/**
 * Writes data to an open file.
 *
 * @param file_index The index of the file in the file table.
 * @param data The data to write to the file.
 * @return 0 if successful, or -1 if an error occurs.
 */
int fileWrite(int file_index, const char *data);



/**
 * Reads data from an open file.
 *
 * @param file_index The index of the file in the file table.
 * @param buffer The buffer where the read data will be stored.
 * @param buffer_size The size of the buffer.
 * @return The number of bytes read, or -1 if an error occurs.
 */
int fileRead(int file_index, char *buffer, int buffer_size);



/**
 * Closes an open file.
 *
 * @param file_index The index of the file in the file table.
 * @return 0 if successful, or -1 if an error occurs.
 */
int fileClose(int file_index);



/**
 * Deletes a file from the file system.
 *
 * @param filename The name of the file to delete.
 * @return 0 if successful, or -1 if an error occurs.
 */
int fileDelete(const char *filename);

#endif // DANIEL_LIBFS_H