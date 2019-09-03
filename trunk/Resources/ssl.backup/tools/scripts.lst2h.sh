#!/bin/bash

set -e
if [ "x$1" == "x" ]; then
	echo "Usage: lst2h.sh file.lst"
	exit
fi

lst="$1"

id=0

while IFS="" read -r line || [ -n "$line" ]
do
	id=$(expr $id + 1)
	comment=$(echo "$line" | sed -e 's/^.*\;[\t\ ]*//' | sed -e 's/[\t\ ]*\#.*//' | sed -e 's/\"/```/g' )
	echo $line | awk "{printf \"#define SCRIPT_%s (%d) // $comment\n\", toupper(\$1), $id}" | sed -e 's/\.INT//' | sed -e 's/```/\"/g'
done < $lst
