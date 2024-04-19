#!/bin/bash
#Write a bash script that receives any number of command line arguments and prints on the screen, for each argument, if it is a file, a directory, a number or something else.

while ! test $# -eq 0; do
      	if test -f $1; then
		echo Argument is a file
	elif test -d $1; then
		echo Argument is a directory
	elif echo $1 | grep -E -q "^[0-9]+$"; then
		echo Argument is an integerer
	else
		echo Argument is something else
	fi
	shift
done	
