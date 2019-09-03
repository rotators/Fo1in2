#!/bin/bash

int2ssl="../tools/int2ssl-repo"

errors="errors"
errors_txt="$errors/$errors.txt"

rm -fR $errors

chmod -f u+w *.ssl
rm -f *.ssl

find . -maxdepth 1 -regex '.+\.[Ii][Nn][Tt]$' -printf '%P\n' | sort | while read int; do
	echo "$int"
	ssl="${int%%.*}.ssl"
	err="${int%%.*}.error.txt"
	dmp="${int%%.*}.dump.txt"

	$int2ssl -s4 -1 -a $int $ssl > $err

	if [ -s $ssl ]; then
		rm $err
	else
		$int2ssl -1 -d -a $int $dmp >/dev/null

		tldr=$(egrep "Error:.+" $err | sed -e 's/.*Error/Error/')
		mkdir -p $errors
		cp -v "$int" "$errors/"
		mv -v $err $dmp "$errors/"

		if [ ! -s $errors_txt ]; then
			echo "| Script | Error message |" > $errors_txt
			echo "| --- | --- |" >> $errors_txt
		fi

		printf "| %s | \`%s\` |\n" "$int" "$tldr" >> $errors_txt
	fi
done

chmod -f 0444 *.ssl

if [ -s $errors_txt ]; then
    (cd $errors && 7za a -tzip $errors.zip *)
fi
