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

for ssl_full in $(/usr/bin/find $scripts_dir -type f -name '*.[Ss][Ss][Ll]' | /usr/bin/sort); do
    sed -ri 's!#include "..[\\/]headers[\\/]!#include "!' $ssl_full
    sed -ri 's!#include "maps\\!#include "maps/!' $ssl_full
    sed -ri 's!#include "sfall\\!#include "sfall/!' $ssl_full
done
