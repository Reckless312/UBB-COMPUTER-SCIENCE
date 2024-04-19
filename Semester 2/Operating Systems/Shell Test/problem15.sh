#!/bin/bash

#Calculate the average of all process ids in the system p

current_user=""
average=0
count=1
position=0
for pid in $(ps -ef | awk 'NR > 1 {print $1, $2}' | sort); do
	if test $position -eq 0;then
		if test "$current_user" != "$pid";then
			average=$(($average/$count))
			echo User: $current_user has an average of PID: $average
			current_user=$pid
			average=0
			count=1	
		fi
		position=1
	else
		if test $average -eq 0;then
			average=$(($average+$pid))
		else
			average=$(($average+$pid))
			count=$(($count+1))
		fi
		position=0
	fi	
done | awk 'NR > 1 {print $0}'
