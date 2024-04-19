#!/bin/bash
#Write a bash script that counts all the C files from a given directory and all of its subdirectories.
if test $# -ne 1; then
	echo Main file not provide or more arguments are present!
	exit 1
fi
find $1 -type f | grep -E ".*.c$"

