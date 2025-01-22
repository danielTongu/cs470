#!/bin/bash

# File Name: create_files_with_subdirs.sh
#
# Description:
#   Creates a main directory with the current date and time as its name.
#   It generates 10 subdirectories, each containing 10 .txt files,
#   each populated with a unique programming language.
#
# Author: Daniel Tongu
# Date: Jan 21, 2025


# Get the current date and time for the directory name
CURRENT_DATE_TIME=$(date +"%Y-%m-%d_%H-%M-%S")
MAIN_DIR=$CURRENT_DATE_TIME


# List of programming languages to populate in files
LANGUAGES=("Python" "Java" "C++" "JavaScript" "Ruby" "Go" "Swift" "PHP" "Kotlin" "Rust")


# Step 1: Create the main directory
echo "Creating the main directory: $MAIN_DIR..."
mkdir "$MAIN_DIR"


# Check if the main directory was created successfully
if [[ ! -d "$MAIN_DIR" ]]; then
    echo "Error: Failed to create the main directory $MAIN_DIR." >&2
    exit 1
fi



# Step 2: Create subdirectories and populate files
echo "Creating 10 subdirectories and files within them..."


for i in {101..110}; do
    # Create subdirectory
    SUB_DIR="$MAIN_DIR/subdir_$i"
    mkdir "$SUB_DIR"
  
  
    # Check if the subdirectory was created successfully
    if [[ ! -d "$SUB_DIR" ]]; then
        echo "Error: Failed to create subdirectory $SUB_DIR." >&2
        exit 1
    fi


    # Create 10 files in the subdirectory
    for j in {501..510}; do
        FILE_PATH="$SUB_DIR/file_$j.txt"

        # Write a unique programming language into each file
        LANGUAGE_INDEX=$(( (j - 501) % ${#LANGUAGES[@]} ))
        echo "${LANGUAGES[$LANGUAGE_INDEX]}" > "$FILE_PATH"

        # Check if the file was created successfully
        if [[ ! -f "$FILE_PATH" ]]; then
            echo "Error: Failed to create file $FILE_PATH." >&2
            exit 1
        fi
    done
    
    # Print the contents of the subdirectory after adding files
    echo "Subdirectory $SUB_DIR with files created successfully."
    echo "Contents of $SUB_DIR:"
    ls -l "$SUB_DIR"
    
done




# Final message indicating script completion
echo "Script execution completed successfully."
echo "Directory structure created under $MAIN_DIR."
