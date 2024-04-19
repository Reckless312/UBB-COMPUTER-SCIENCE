#!/bin/bash

#Write a script that receives program/process names as command line arguments. The script will monitor all the processes in the system, and whenever a program with one of those names is run, the script will kill it and display a message. (see commands ps, kill, killall).

if test $# -eq 0;then
	echo Provide at least one argument
	exit 1
fi

while true;do
	for process in $@;do
		PID=""
		PID=$(ps -ef | awk '{print $9, $2}' | grep -E "\<$process " | awk '{print $2}')
		if test -n "$PID";then
			kill -9 $PID
			echo KILLED!
		fi
	done
	sleep 3
done

