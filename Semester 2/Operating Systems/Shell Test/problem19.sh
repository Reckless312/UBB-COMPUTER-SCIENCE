#!/bin/bash

#.Write a script that finds recursively in the current folder and displays all the regular files that have write permissions for everybody (owner, group, other). Then the script removes the write permissions from everybody. Hint: use chmod's symbolic permissions mode (see the manual).

for file in $(find . -type f);do
	if test -f $file;then
		file_cut=$(echo $file | sed -E 's/.\///')
		file_and_acces=$(ls -l | awk 'NR > 1 {print $9, $1}' | grep -E "\<$file_cut ")
                string="" 
		string=$(echo $file_and_acces | awk '$2 ~ /-.w..w..w./ {print $0}')
		if test -n "$string";then
			echo $string
			chmod 555 $file
		fi
	fi
done

