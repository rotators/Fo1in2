#!/bin/bash

set -e -o pipefail

master_dat="$1"
if [[ ! -f "$master_dat" ]]; then
  echo "Please pass path to Fallout 1's master.dat to the script."
  exit 1
fi
set -u

if ! which wine > /dev/null 2>&1; then
  echo "Please install wine and make sure it's in PATH!"
  exit 1
fi

root_dir="$(dirname $0)"
data_dir="$root_dir/data"
dat3="$root_dir/dat3"
undat_list="$root_dir/undat_files.txt"

if ! $dat3 l "${master_dat}" > /dev/null 2>&1; then
  echo "Error: can't read Fallout 1's master.dat."
  exit 1
fi

$dat3 x -o "$data_dir" "$master_dat" "@$undat_list"

echo "Extracted successfully."
