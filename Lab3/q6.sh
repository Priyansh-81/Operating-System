#!/bin/sh

# Loop through all files in the current directory
for file in *; do
    # Check if it's a regular file
    if [ -f "$file" ]; then
        # Use sed to perform the replacement
        sed -i.bak -E 's/(^|\. )ex:/\1Example:/g' "$file"
        echo "Modified $file"
    fi
done

echo "Replacement complete. Backup of original files created with .bak extension."
