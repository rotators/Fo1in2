#!/bin/bash

set -euo pipefail

root_dir="$(cd "$(dirname "$0")" && pwd)"
master_dat="${1:-}"
destination="${2:-}"

if [[ $# -lt 1 || $# -gt 2 || ! -f "$master_dat" ]]; then
  echo "Usage: bash undat_macos.sh /path/to/Fallout1/MASTER.DAT [Fallout1in2-folder]" >&2
  exit 1
fi

# In the repository the script lives in Tools/UndatCLI; releases put it beside data/.
if [[ -z "$destination" ]]; then
  if [[ -f "$root_dir/../../Fallout2/Fallout1in2/fallout2.cfg" ]]; then
    destination="$root_dir/../../Fallout2/Fallout1in2"
  else
    destination="$root_dir"
  fi
fi

if [[ ! -d "$destination" || ! -f "$destination/fallout2.cfg" ]]; then
  echo "Error: select the Fallout1in2 folder containing fallout2.cfg." >&2
  exit 1
fi

dat_tool="$root_dir/ce-dat-tool"
undat_list="$root_dir/undat_files.txt"
if [[ ! -f "$undat_list" ]]; then
  undat_list="$root_dir/../UndatUI/undat_files.txt"
fi

if [[ ! -f "$dat_tool" ]]; then
  echo "Error: the macOS ce-dat-tool executable is missing from $root_dir." >&2
  exit 1
fi
if [[ ! -x "$dat_tool" ]]; then
  # ZIPs packaged on Windows can lose the executable permission.
  chmod +x "$dat_tool"
fi
if [[ ! -f "$undat_list" ]]; then
  echo "Error: undat_files.txt is missing." >&2
  exit 1
fi

"$dat_tool" "$master_dat" extract --lower --file-list "$undat_list" "$destination/data"
echo "Extracted successfully."
