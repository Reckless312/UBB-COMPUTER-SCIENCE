#!/bin/bash
#Write a bash script that counts all the lines of code in the C files from the directory given as command-line argument, excluding lines that are empty or contain only spaces.

if test $# -ne 1; then
	echo More or not enough arguments!
	exit 1
fi
if ! test -d $1; then
	echo Not a folder!
	exit 2
fi
total=0
for file in $(ls $1 | grep -E "\.c$");do
	if test -f $1/$file; then
		nr_lines=$(grep -E -c -v "^[ \t]*$" $1/$file)
		echo $file: $nr_lines
		total=$((total+nr_lines))
	fi
done
echo "Total lines: $total"
