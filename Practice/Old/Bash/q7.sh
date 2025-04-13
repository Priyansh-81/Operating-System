#Write a shell script which deletes all the even numbered lines in a text file.

#!/bin/bash

echo "Enter the name of input file"

read input_file
touch output_file

sed 'n;d' "$input_file" > output_file
echo "Output written to output_file"

cat output_file
