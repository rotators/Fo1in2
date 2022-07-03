#!/bin/bash

repo=$1

if [[ -z "$repo" ]]; then
	echo ""
	echo "USAGE: $(basename $0) [owner]/[repository]"
	echo ""

	exit 1
fi

curl -s https://api.github.com/repos/$repo/releases | jq -r '[.[] | select(.assets[0] != null) | [.tag_name,.created_at,.assets[0].download_count,.prerelease] | @sh]' | grep '"' | tr -d \''"',\' | sed -re 's!T.+Z!!g' | sed -re 's!true$!(prerelease)!g' | sed -re 's! false$!!g' | sed '1s!^!Tag Created Downloads\n!' | column -t | awk -v repo="$repo" '{print} END { if(!NR) printf "No assets found in %s releases\n", repo }'
