#!/bin/bash

#.Write a shell script that receives any number of words as command line arguments, and continuously reads from the keyboard one file name at a time. The program ends when all words received as parameters have been found at least once across the given files.

if test $# -eq 0;then
	echo Provide at least one word!
	exit 1
fi

declare -A words
for word in $@;do
	words[$word]=0
done

found_all=false
while ! ${found_all};do
	to_find=""
	for word in ${!words[@]};do
		if test ${words[$word]} -eq 0;then
			to_find="$to_find $word"
		fi
	done
	echo "Left to find:$to_find"
	read -p "Please input a filename: " file
	if test -z "$file"; then
		echo "Please input a non empty string"
	elif ! test -f "$file"; then
		echo "$file is not a file"
	else
		found_all=true
		for word in $@; do
			if grep -E -q "\<$word\>" "$file";then
				echo "Found $word in $file"
				words[$word]=1
			fi
			if test ${words[$word]} -eq 0;then
				found_all=false
			fi
		done
	fi
done
echo "All done"
