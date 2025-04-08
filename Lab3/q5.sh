echo "enter a file extension"
read ex
echo "enter the folder name"
read folder
if [ ! -d "$folder" ]
then 
mkdir "$folder"
fi

find . -maxdepth 1 -type f -name "*$ex" | while read -r file 
do
cp -v "$file" "$folder/"
echo "copied $file to $folder"
done

