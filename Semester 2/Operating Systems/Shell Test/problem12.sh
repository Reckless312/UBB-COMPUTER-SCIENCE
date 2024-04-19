#!/bin/bash

if test $# -ne 1; then
	echo More or no arguments provided!
	exit 1
fi

if ! test -f $1; then
	echo Argument not a file!
	exit 2
fi

while test -N $1; do
	echo Waiting...
	sleep 1
done
echo File has changed!
