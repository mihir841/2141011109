#!/bin/bash

# Define the word to search and the file to search in
search_word="example"
file_name="sample.txt"

# Check if file exists
if [[ ! -f "$file_name" ]]; then
    echo "File '$file_name' not found."
    exit 1
fi

# Search and sort results
grep "$search_word" "$file_name" | sort
