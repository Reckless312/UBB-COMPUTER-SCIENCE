#!/bin/bash
#Write a script that receives as command line arguments pairs consisting of a filename and a word. For each pair, check if the given word appears at least 3 times in the file and print a corresponding message.

odd_or_even=$(($# % 2))
if test $# -eq 0; then
	echo No arguments provided!
	exit 1
fi
if test $odd_or_even -ne 0;then
	echo Arguments not in pair!
	exit 2
fi
while ! test $# -eq 0; do
	if test -f $1; then
		appearances=$(grep -E -o "\<$2\>" $1 | wc -l)
		if test $appearances -ge 3; then
			echo For file: $1, the numbers of the word: $2 that appeared is: $appearances
		fi
	fi
	shift
	shift
done
