#!/bin/bash

for link in $(find $1 -type l); do
	if ! test -e $link; then
		echo Link doesnt exit anymore
	fi
done
