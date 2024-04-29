#!/bin/bash

set -e

for option in $@; do
    [[ "$option" =~ ^--debug$ ]] && set -x
done

# default options
option_scripts_dir="Fallout2/Fallout1in2/Mapper/source/scripts"

# user options
for option in "$@"; do
    # --scripts-dir=some/directory
    # path to .ssl files directory
    [[ "$option" =~ ^--scripts-dir=([A-Za-z0-9_\.\/]+)$ ]] && option_scripts_dir=${BASH_REMATCH[1]}
done

readonly scripts_dir="$(pwd)/$option_scripts_dir"

if [ ! -d "$scripts_dir" ]; then
   echo "[ERROR] Cannot find scripts directory : $scripts_dir"
   exit 1
fi

    # /c/repo/path/to/scripts/sub/dir/script.ssl
for ssl_full in $(find $scripts_dir -type f -name '*.[Ss][Ss][Ll]' | sort); do
    # /c/repo/path/to/scripts/sub/dir
    ssl_dir=$(dirname "$ssl_full")
    # script.ssl
    ssl_file=$(basename "$ssl_full")
    # .ssl
    ssl_ext=${ssl_file##*.}
    # script
    ssl_file=${ssl_file%.*}
    # /c/repo/path/to/scripts/sub/dir/script.ssl (lowercase extension)
    ssl_full_new="${ssl_dir}/${ssl_file}.${ssl_ext,,}"

    sed -ri 's!#include "..[\\/]headers[\\/]!#include "!' "$ssl_full"
    sed -ri 's!#include "maps\\!#include "maps/!' "$ssl_full"
    sed -ri 's!#include "sfall\\!#include "sfall/!' "$ssl_full"

    sed -ri 's!#include "..\\generic\\!#include "../GENERIC/!' "$ssl_full"
    sed -ri 's!#include "../generic/!#include "../GENERIC/!' "$ssl_full"

    if [ "$ssl_full" != "$ssl_full_new" ]; then
       git mv "$ssl_full" "$ssl_full_new"
    fi

    dos2unix -q "$ssl_full_new"
done
