#!/bin/bash
#Write a bash script that keeps reading strings from the keyboard until the name of a readable regular file is given

while true;do
	read file_name
	if test -f $file_name; then
		echo This is a regular file! Closing...
		exit 0
	fi
	echo Nope! Not a regular file!
done
