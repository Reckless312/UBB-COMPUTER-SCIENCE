#!/bin/bash

#Write a shell script that, for all the users in /etc/passwd, creates a file with the same name as the username and writes in it all the ip addresses from which that user has logged in. (hint: use the last command to find the ip addresses)

directory="./results"

if ! test -d $directory;then
	if ! test -e $directory;then
		mkdir $directory
	else
		echo The file exists and its not a directory
		exit 1
	fi
fi

for user in $(awk -F: '{print $1}' ../NotSortedStuff/passwd.fake);do
	ip=$(last $user | head -n -2 | awk '{print $3}' | sort | uniq)
	if test -n "$ip";then
		echo "$ip" > $directory/$user
	fi
done	
