#Write a program to copy all the files (having file extension input by the user) in the
#current folder to the new folder input by the user. ex: user enter .text TEXT then all
#files with .text should be moved to TEXT folder. This should be done only at single
#level. i.e if the current folder contains a folder name ABC which has .txt files then
#these files should not be copied to TEXT.

#!/bin/bash

echo "Enter the extension "
read ext
echo "Enter the folder in which the files has to be copied to "
read folder

if [ ! -d "$folder" ]; then
    mkdir "$folder"
fi

find . -maxdepth 1 -type f -name "*.$ext" -print | while read filename
do
    cp -v "$filename" "./$folder"
    echo "file $filename copied to $folder"
done
