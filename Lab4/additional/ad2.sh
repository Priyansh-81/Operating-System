#!/bin/bash
# Usage: ./created_between.sh 2014 2015

start_year=$1
end_year=$2

echo "Files created between $start_year and $end_year:"
for file in *; do
  if [ -f "$file" ]; then
    file_year=$(stat -c %y "$file" | cut -d '-' -f 1)
    if [ "$file_year" -ge "$start_year" ] && [ "$file_year" -le "$end_year" ]; then
      echo "$file"
    fi
  fi
done