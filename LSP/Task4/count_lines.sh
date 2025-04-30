#!/bin/bash

# Function to count and print the number of lines in a file
count_lines() {
    local file="$1"
    if [[ -f "$file" ]]; then
        local lines
        lines=$(wc -l < "$file")
        echo "File: $file - Lines: $lines"
    else
        echo "File: $file does not exist."
    fi
}

# List of files (you can modify this list)
files=("file1.txt" "file2.txt" "file3.txt")

# Loop through the list and call the function
for file in "${files[@]}"; do
    count_lines "$file"
done
