#!/bin/bash

in_dir="$1"
out_dir="$2"
diff="$3"

in_dir=${in_dir%/}
out_dir=${out_dir%/}

git diff --name-only "$diff" -- $in_dir | while read name
do
	shortname="${name#${in_dir}/}"
	dirname="$(dirname $shortname)"
	mkdir -p "$out_dir/$dirname"
	git diff "$diff" -- "$name" > "$out_dir/$shortname.diff"
done
