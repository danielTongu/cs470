#!/bin/bash


# ===============================
# File Name: create_files with_subdirs.sh
# Description:
# - Creates a main directory with the current date and time as its name.
# - Generates 10 subdirectories; each containing 10 .txt file,
#   each populated with a unique programming language.
# Author: Daniel Tongu
# Date Jan 21, 2025
# ===============================


echo "Initiating process..."


# ===============================
# Step 1: Define Constants and Variables
# ===============================

# Array of programming languages to be written into files
LANGUAGES=("Python" "Java" "C++" "JavaScript" "Ruby" "Go" "Swift" "PHP" "Kotlin" "Rust")

# Get the current date and time in YYYYMMDD_HHMMSS format
CURRENT_DATE_TIME=$(date +"%Y%m%d_%H%M%S")

# Main directory name (uses timestamp to ensure uniqueness)
MAIN_DIR=$CURRENT_DATE_TIME
echo "Main directory name: $MAIN_DIR"

# Prefix for naming each subdirectory and file
DIR_NAME_PREFIX="file"

# Counter for successful subdirectory creation
SUCCESSFUL_SUBDIR_COUNT=0



# ===============================
# Step 2: Remove Existing Directory (if exists)
# ===============================

# Check if the main directory exists; if so, remove it to avoid duplicates
if [ -d "$MAIN_DIR" ]; then
    echo "Main directory '$MAIN_DIR' already exists. Removing it to avoid duplicates..."
    rm -rf "$MAIN_DIR"
fi



# ===============================
# Step 3: Create the Main Directory
# ===============================

echo "Creating the main directory and its subdirectories containing files..."

mkdir "$MAIN_DIR"
# Verify if the main directory was created successfully
if [ ! -d "$MAIN_DIR" ]; then
    echo "Error: Failed to create the main directory '$MAIN_DIR'." >&2
    exit 1
fi



# ===============================
# Step 4: Create Subdirectories and Populate Them with Files
# ===============================

for i in {101..110}; do
    # Define subdirectory path
    SUB_DIR="$MAIN_DIR/$DIR_NAME_PREFIX$i"

    echo
    echo "Creating subdirectory: $SUB_DIR ..."
    mkdir "$SUB_DIR"

    # Verify if the subdirectory was created successfully
    if [ ! -d "$SUB_DIR" ]; then
        echo "Error: Failed to create subdirectory '$SUB_DIR'." >&2
        exit 1
    else
        SUCCESSFUL_SUBDIR_COUNT=$((SUCCESSFUL_SUBDIR_COUNT + 1))
    fi

    # Create 10 unique files in the subdirectory
    for j in {501..510}; do
        # Define the file path
        FILE_PATH="$SUB_DIR/$DIR_NAME_PREFIX$j.txt"

        # Determine the programming language to write into the file
        LANGUAGES_LENGTH=${#LANGUAGES[@]}  # Get total languages
        LANGUAGE_INDEX=$(( (j - 501) % LANGUAGES_LENGTH ))  # Cycle through the list

        # Write the programming language name into the file
        echo "${LANGUAGES[LANGUAGE_INDEX]}" > "$FILE_PATH"

        # Verify if the file was created successfully
        if [ ! -f "$FILE_PATH" ]; then
            echo "Error: Failed to create file '$FILE_PATH'." >&2
            exit 1
        fi
    done

    # Display the files inside the created subdirectory
    echo "Contents of '$SUB_DIR':"
    ls "$SUB_DIR"
done



# ===============================
# Step 5: Final Verification and Summary
# ===============================

echo
if [ "$SUCCESSFUL_SUBDIR_COUNT" -eq 10 ]; then
    echo "All 10 subdirectories were successfully created under '$MAIN_DIR'."
else
    echo "Error: Only $SUCCESSFUL_SUBDIR_COUNT out of 10 subdirectories were created." >&2
    exit 1
fi

# Final message indicating script completion
echo "Process terminated successfully."