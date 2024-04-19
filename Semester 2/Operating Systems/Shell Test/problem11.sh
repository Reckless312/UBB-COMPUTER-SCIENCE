#!/bin/bash

if test $# -eq 0; then
	echo No arguments given!
	exit 1
fi

for file in $@; do
	if test -f $file; then
		if file $file | grep -q '.c'; then
			grep -E '^#include[ ]*<.*>$' $file >> problem11.txt
		fi
	else
		echo Argument: $file is not a file!
	fi
done
