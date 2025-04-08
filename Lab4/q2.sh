#!/bin/bash
# Usage: ./remove.sh file1 file2 ...

for file in "$@"; do
  echo -n "Do you want to delete $file? (y/n): "
  read ans
  if [ "$ans" = "y" ]; then
    rm "$file"
    echo "$file deleted."
  else
    echo "$file skipped."
  fi
done