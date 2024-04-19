#!/bin/bash

#9.Consider a file containing a username on each line. Generate a comma-separated string with email addresses of the users that exist. The email address will be obtained by appending "@scs.ubbcluj.ro" at the end of each username. Make sure the generated string does NOT end in a comma.

if test $# -ne 1;then
	echo More or no files provided!
	exit 1
fi

if ! test -f $1;then
	echo Not a file!
	exit 2
fi

for username in $(cat $1);do
	echo $username | sed -E "s/$username/$username@scs.ubbcluj.ro/"
done

