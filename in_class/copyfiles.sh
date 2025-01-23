#!/bin/bash

# File Name: copyfiles.sh
# Description: Script to copy files from a directory to another
# Author: Daniel Tongu
# Date: Jan 21, 2025




# Define constants
NUM_FILES=100
SOURCE_DIR="source470"
DEST_DIR="dest470"



# Step 1: Create the two folders
echo "Creating the $SOURCE_DIR and $DEST_DIR folders..."
mkdir -p "$SOURCE_DIR" "$DEST_DIR"



# Step 2: Create 100 sample files in the source folder
echo "Creating sample files in the $SOURCE_DIR folder..."
EXTENSIONS=("txt" "csv" "log" "json" "xml")
for i in $(seq 1 $NUM_FILES); do
	#Generate a random file extension
	EXTENSION=${EXTENSIONS[$RANDOM % ${#EXTENSIONS[@]}]}
	FILENAME="file_$i.$EXTENSION"

	#Create  a texte-based file
	echo "Created sample file $i." > "$SOURCE_DIR/$FILENAME"
done

#Verify if the files were created successfully.
FILE_COUNT=$(ls "$SOURCE_DIR" | wc -l)
if [[ $FILE_COUNT -ne $NUM_FILES ]]; then
	echo "Error: Expected $NUM_FILES files, but found $FILE_COUNT in $SOURCE_DIR." >&2
	exit 1
fi



# Step 3: Copy files from the source folder to the destination folder
echo "Copying files from $SOURCE_DIR to $DEST_DIR..."
cp "$SOURCE_DIR"/* "$DEST_DIR"

# Verify if the files were copied successfully
COPIED_COUNT=$(ls "$DEST_DIR" | wc -l)
if [[ $COPIED_COUNT -ne $NUM_FILES ]]; then
	echo "Error: Expected $NUM_FILES files to be copied, but found $COPIED_COUNT in $DEST_DIR." >&2
	exit 1
fi



# Step 4: Display the contents of both folders
echo "Contents of $SOURCE_DIR:"
ls  "$SOURCE_DIR"

echo "Contents of $DEST_DIR:"
ls "$DEST_DIR"



echo  "Copied $NUM_FILES files from $SOURCE_DIR to $DEST_DIR successfully."
