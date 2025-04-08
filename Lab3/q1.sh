#!/bin/sh

echo "Enter the name of file/folder"
read sample
if [ -f "$sample" ]; then
    echo "It's a file"
elif [ -d "$sample" ]; then
    echo "It's a folder"
else
    echo "$sample not found"
fi
