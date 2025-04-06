#!/bin/bash

echo "enter the name of the file/folder to be checked : "
read smp_file

if [ -f "$smp_file" ]; then
    echo "Its a file"
elif [ -d "$smp_file" ]; then
    echo "Its a directory"
else
    echo "$smp_file not found"
fi
