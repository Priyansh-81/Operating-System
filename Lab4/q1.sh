#!/bin/bash
# Usage: ./duplicate.sh filename

if [ $# -eq 0 ]; then
  echo "Usage: $0 filename"
  exit 1
fi

cp "$1" "$1.copy"
echo "Copied $1 to $1.copy"