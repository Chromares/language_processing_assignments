#!/bin/bash

echo -n "Enter name of the file to be marked : "
read -e file_name
new_file="${file_name}_temp"
touch $new_file
counter=1
(while read f
do
  echo "$counter $f"
  #var="$counter $f"
  #echo $var
  counter=$((counter + 1))
  #$var > $new_file
done < $file_name) > $new_file
rm $file_name
mv $new_file $file_name
