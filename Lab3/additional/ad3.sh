#!/bin/bash
# Usage: ./split_even_odd.sh filename

file="$1"
awk 'NR % 2 == 0 { print > "evenfile" } NR % 2 == 1 { print > "oddfile" }' "$file"