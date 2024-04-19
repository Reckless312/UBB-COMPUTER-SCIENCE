#!/bin/bash
# Write a script that reads filenames until the word "stop" is entered. For each filename, check if it is a text file and if it is, print the number of words on the first line.(Hint: test command to check if regular file; file command to check if text file)

read filename
while ! test $filename = stop; do
	if test -f $filename; then
		if file $filename | grep -E -q "text"; then
			words=$(awk 'NR == 1 {print $0}' $filename | wc -w | awk '{print $1}') 
			echo Number of words on the first line: $words
		fi
	fi
	read filename
done
