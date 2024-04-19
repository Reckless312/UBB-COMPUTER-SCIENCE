#!/bin/bash

for file_name in $@; do
	if test -d $file_name; then
		find $file_name -type f | grep -q -E '\.txt$'
	elif test -f $file_name;then
		string=""
		string=$(echo $file_name | grep -E '\.sh$')
		if test -n "$string";then
			cat $file_name | grep -E -v '^[ \t]*$'
		fi
	fi
done
