#!/bin/bash
#Write a bash script that calculates the sum of the sizes (in bytes) of all regular files in a folder given as a parameter.(use test to check if the folder exists and if a given file is a regular file)

if test $# -ne 1; then
	echo More or no arguments provided!
	exit 1
fi

if ! test -d $1; then
	echo Argument is not a file!
	exit 2
fi

total=0
for file in $(ls $1); do
	if test -f $file; then
		current_size=$(du -b $file | awk '{print $1}')
		total=$(($current_size + $total))
	fi
done

echo Total size of regular files: $total
