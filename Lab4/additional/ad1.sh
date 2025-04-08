#!/bin/bash
# Usage: ./permissions.sh filename

if [ ! -f "$1" ]; then
  echo "File not found!"
  exit 1
fi

perm=$(ls -l "$1" | awk '{print $1}')

echo "Permissions: $perm"
echo "Owner  : ${perm:1:3}"
echo "Group  : ${perm:4:3}"
echo "Others : ${perm:7:3}"