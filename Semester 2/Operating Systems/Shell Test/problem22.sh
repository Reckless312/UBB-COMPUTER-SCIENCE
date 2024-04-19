#!/bin/bash

users="-e"
if test $# -gt 0;then
	users=""
	for user in $@;do
		users="$users -u $user"
	done
fi

while true; do
	clear
	ps -f $users | awk 'NR > 1 {print $1}' | sort | uniq -c | sort -n -r
	sleep 1
done
