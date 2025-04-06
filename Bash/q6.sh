#Write a shell script to modify all occurrences of “ex:” with “Example:” in all the files
#present in current folder only if “ex:” occurs at the start of the line or after a period
#(.). Example: if a file contains a line: “ex: this is first occurrence so should be re-
#placed” and “second ex: should not be replaced as it occurs in the middle of the sen-
#-tence.”

#!/bin/bash


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
