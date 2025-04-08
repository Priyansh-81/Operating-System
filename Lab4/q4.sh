#!/bin/bash
# Usage: ./wordcount.sh option filename

case $1 in
  -linecount)
    wc -l < "$2"
    ;;
  -wordcount)
    wc -w < "$2"
    ;;
  -charcount)
    wc -m < "$2"
    ;;
  *)
    echo "Usage: $0 {-linecount|-wordcount|-charcount} filename"
    ;;
esac