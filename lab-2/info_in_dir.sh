# Write a bash script to show the filename, size and line of code of all C/C++ files in a given directory.
#!/bin/bash

dir_name="/home/iit/Documents/zahid db"
for i in "$dir_name"/*.cpp "$dir_name"/*.c; do
    if [ -f "$i" ]; then
        filename=$(basename "$i")
        size=$(wc -c < "$i")
        lines=$(wc -l < "$i")
        echo "File Name: $filename, Size: $size, Lines of code: $lines"
    fi
done