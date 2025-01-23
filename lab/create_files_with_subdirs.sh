#!/bin/bash



# File Name: create_files with_subdirs.sh
# Description:
# - Creates a main directory with the current date and time as its name.
# - Generates 10 subdirectories; each containing 10 .txt file,
#   each populated with a unique programming language.
# Author: Daniel Tongu
# Date Jan 21, 2025



#Array of programming languages
LANGUAGES=("Python" "Java" "C++" "JavaScript" "Ruby" "Go" "Swift" "PHP" "Kotlin" "Rust")

#Current date and time, formatted
CURRENT_DATE_TIME=$(date +"%Y%m%d_%H%M%S")
echo "Current date time $CURRENT_DATE_TIME"




# Main directory name
MAIN_DIR=$CURRENT_DATE_TIME

# Remove the main directory if it already exists to avoid duplicates
if [ -d "$MAIN_DIR" ]; then
    echo "Main directory $MAIN_DIR already exists. Removing it to avoid duplicates..."
    rm -rf "$MAIN_DIR"
fi

# Create the main directory
echo "Creating the main directory ..."
mkdir "$MAIN_DIR"

#Check if the main directory was created successfully
if [ ! -d "$MAIN_DIR" ]; then
    echo "Error: Failed to create the main directory $MAIN_DIR." >&2
    exit 1
fi



#prefix for each subdirectory
DIR_NAME_PREFIX="file"



#Create subdirectories and populate files
echo "Creating 10 subdirectories and files within them..."
for i in {101..110}; do
    #create a subdirectory
    SUB_DIR="$MAIN_DIR/$DIR_NAME_PREFIX$i"
    echo "Creating $DIR_NAME_PREFIX$i ..."
    mkdir "$SUB_DIR"

    #check if the subdirectory was created successfully
    if [ ! -d "$SUB_DIR" ]; then
        echo "Error: Failed to create subdirectory $SUBDIR." >&2
        exit 1
    fi


    # create 10 unique files in the subdirectory
    for j in {501..510}; do
        #Create the file path
        FILE_PATH="$SUB_DIR/$DIR_NAME_PREFIX$j.txt"

        #Calculate the index of the programming language
        LANGUAGES_LENGTH=${#LANGUAGES[@]}
        LANGUAGE_INDEX=$(( (j - 501) % LANGUAGES_LENGTH ))

        #write the programming language to the file
        echo "${LANGUAGES[LANGUAGE_INDEX]}" > "$FILE_PATH"

        #check if the file was created successfully
        if [ ! -f "$FILE_PATH" ]; then
            echo "Error: Failed to create file $FILE_PATH." >&2
            exit 1
        fi
    done

    #print the files in the subdirectory
    echo "contents of $SUB_DIR: "
    ls $SUB_DIR
done




# Final message indicating script completion
echo
echo "Script execution completed successfully."
echo "Directory structure created under $MAIN_DIR."
