#!/bin/bash

#Write a script that receives a directory as a command line argument. The script will delete all the C source files from the directory and will display all other text files sorted alphabetically.

if test $# -ne 1;then
	echo More or no directory provided!
	exit 1
fi

if ! test -d $1; then
	echo Not a directory!
	exit 2
fi

for file in $(find $1 -type f);do
	file_c=""
	file_c=$(echo $file | grep '.c$')
	if test -n "$file_c";then
		rm $file_c
		echo File: $file_c was removed
	fi
done

find $1 -type f | sort | cat
