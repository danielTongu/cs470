#!/bin/bash



# ===============================
# Description: Script to create sample files, verify them, and copy them
# File Name: copyfiles.sh
# Author: Daniel Tongu
# Date: Jan 21, 2025
# ===============================



# Define constants
NUM_FILES=100              # Number of sample files to create
SOURCE_DIR="source470"     # Name of the source directory
DEST_DIR="dest470"         # Name of the destination directory

# List of possible file extensions for generated files
EXTENSIONS=("txt" "csv" "log" "json" "xml")



# ===============================
# Step 1: Create the source and destination folders
# ===============================
echo "Creating the '$SOURCE_DIR' and '$DEST_DIR' folders..."
# -p ensures directories are created only if they don't already exist
mkdir -p "$SOURCE_DIR" "$DEST_DIR"



# ===============================
# Step 2: Generate sample files in the source directory
# ===============================
echo "Creating $NUM_FILES sample files in '$SOURCE_DIR'..."
for i in $(seq 1 $NUM_FILES); do
    # Generate a random file extension from the EXTENSIONS array
    EXTENSION=${EXTENSIONS[$RANDOM % ${#EXTENSIONS[@]}]}

    # Construct the filename using an indexed format
    FILENAME="file_$i.$EXTENSION"

    # Create a sample text-based file with some initial content
    echo "Created sample file $i." > "$SOURCE_DIR/$FILENAME"
done

# Verify if the correct number of files was created
FILE_COUNT=$(ls "$SOURCE_DIR" | wc -l)
if [[ $FILE_COUNT -ne $NUM_FILES ]]; then
    echo "Error: Expected $NUM_FILES files, but found $FILE_COUNT in '$SOURCE_DIR'." >&2
    exit 1
fi



# ===============================
# Step 3: Copy files from source to destination
# ===============================
echo "Copying files from '$SOURCE_DIR' to '$DEST_DIR'..."
cp "$SOURCE_DIR"/* "$DEST_DIR"

# Verify if all files were copied successfully
COPIED_COUNT=$(ls "$DEST_DIR" | wc -l)
if [[ $COPIED_COUNT -ne $NUM_FILES ]]; then
    echo "Error: Expected $NUM_FILES files to be copied, but found $COPIED_COUNT in '$DEST_DIR'." >&2
    exit 1
fi



# ===============================
# Step 4: Display folder contents
# ===============================
echo "Displaying contents of both directories..."

echo "Contents of '$SOURCE_DIR':"
ls "$SOURCE_DIR"

echo "Contents of '$DEST_DIR':"
ls "$DEST_DIR"

# Final success message
echo "Successfully copied $NUM_FILES files from '$SOURCE_DIR' to '$DEST_DIR'."