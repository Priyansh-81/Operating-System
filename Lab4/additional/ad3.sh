#!/bin/bash
# Usage: ./lines.sh filename start_line end_line

if [ $# -ne 3 ]; then
  echo "Usage: $0 filename start_line end_line"
  exit 1
fi

filename=$1
start=$2
end=$3

sed -n "${start},${end}p" "$filename"