#!/bin/bash

dir=${1:-"."}
echo $dir

if test -d "$dir";then
	for f in $(find "$dir" -type f);do
		if file $f | grep -E -q "text";then
			size=$(du -b $f | cut -f1)
			perm=$(ls -l $f | cut -d' ' -f1)
			lines=$(sort $f | uniq | wc -l)
			echo "Filename: $f - size: $size - permissions: $perm lines: $lines"
		fi
	done
fi
