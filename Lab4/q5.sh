#!/bin/bash
# Usage: ./patternmenu.sh pattern1 pattern2 ...

read -p "Enter input file name: " file

PS3="Choose an operation: "
select opt in "Search Patterns" "Delete Patterns" "Exit"; do
  case $opt in
    "Search Patterns")
      for pattern in "$@"; do
        echo "Matching lines for pattern '$pattern':"
        grep "$pattern" "$file"
        echo "-------------------------"
      done
      ;;
    "Delete Patterns")
      for pattern in "$@"; do
        sed -i "/$pattern/d" "$file"
        echo "Deleted pattern '$pattern' from $file"
      done
      ;;
    "Exit")
      break
      ;;
    *)
      echo "Invalid option."
      ;;
  esac
done