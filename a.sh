#!/bin/bash

# Script to create 100 files

# Directory where files will be created (change as needed)
DIR="./files"

# Create directory if it doesn't exist
mkdir -p "$DIR"

# Create 100 files
for i in {1..100}; do
    # Format the number with leading zeros (001, 002, ..., 100)
    filename=$(printf "file%03d.txt" "$i")
    touch "$DIR/$filename"
done

echo "Created 100 files in $DIR/"
