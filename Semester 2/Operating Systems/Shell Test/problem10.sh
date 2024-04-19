#!/bin/bash
#Write a bash script that sorts all files given as command line arguments descending by size. (first check if an argument is a file)

if test $# -eq 0; then
	echo No arguments provided!
	exit 1
fi

for file in $@; do
	if test -f $file;then
		if find $file | grep -q '.c'; then
			du -b $file
		fi
	fi	
done | sort -r -n
