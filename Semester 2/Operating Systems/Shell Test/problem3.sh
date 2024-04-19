#!/bin/bash
#Write a bash script that counts all the lines of code in the C files from the directory given as command-line argument and all its subdirectories, excluding lines that are empty or contain only spaces.
if test $# -ne 1; then
        echo More or not enough arguments!
        exit 1
fi
if ! test -d $1; then
        echo File is not a directory!
        exit 2
fi
total=0
for file in $(find $1 -type f | grep -E "\.c$");do
	current_lines=$(grep -E -c -v "^[ ]*$" $file)
	echo File:$file has this number of lines - $current_lines
	total=$(($total+$current_lines))
done     
echo Total number of lines: $total
