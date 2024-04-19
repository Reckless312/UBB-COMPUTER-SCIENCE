#!/bin/bash

#Write a bash script that receives a folder name as an argument. Find recursively in the folder the number of times each file name is repeated.

if test $# -ne 1; then
	echo More or no argument has been found!
	exit 1
fi

if ! test -d $1; then
	echo Not a folder!
	exit 2
fi

find $1 -type d | awk -F '/' '{print $NF}' | sed -E 's/[.\/]//g' | sort | uniq -c
