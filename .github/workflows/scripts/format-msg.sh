#!/bin/bash

set -e

for option in $@; do
    [[ "$option" =~ ^--debug$ ]] && set -x
done

# default options
option_text_dir="Fallout2/Fallout1in2/mods"

# user options
for option in "$@"; do
    # --text-dir=some/directory
    # path to .msg files directory
    [[ "$option" =~ ^--text-dir=([A-Za-z0-9_\.\/]+)$ ]] && option_text_dir=${BASH_REMATCH[1]}
done

readonly text_dir="$(pwd)/$option_text_dir"

if [[ ! -d "$text_dir" ]]; then
   echo "[ERROR] Cannot find text directory : $text_dir"
   exit 1
fi

    # /c/repo/path/to/text/sub/dir/filename.msg
find $text_dir -type f -iname '*.msg' | sort | while read msg_full; do
    # /c/repo/path/to/text/sub/dir
    msg_dir=$(dirname "$msg_full")
    # filename.msg
    msg_file=$(basename "$msg_full")
    # .msg
    msg_ext=${msg_file##*.}
    # filename
    msg_file=${msg_file%.*}
    # /c/repo/path/to/text/sub/dir/FILENAME.msg (uppercase name, lowercase extension)
    msg_full_new="${msg_dir}/${msg_file^^}.${msg_ext,,}"

    echo >> $msg_full
    sed -ri 's/(^|})[[:blank:]]+$/\1/' $msg_full
    perl -i -0777 -pe 's{\s+\z}{\n}m' $msg_full

    if [[ "$msg_full" != "$msg_full_new" ]]; then
       git mv "$msg_full" "$msg_full_new"
    fi

    dos2unix -q "$msg_full_new"
done
