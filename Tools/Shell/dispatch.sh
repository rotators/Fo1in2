#!/bin/bash

set -e

readonly repo="rotators/Fo1in2"

event="$1"
known=(schedule schedule-push package-prerelease package-release)
payload=
winpty=

if [ -z "$event" ]; then
   echo "Usage:    dispatch.sh [event] (payload1:value1) (payloadN:valueN)"
   echo
   echo "Example:  dispatch.sh my-event"
   echo "Example:  dispatch.sh my-event my-key:my-value"
   echo
   exit 1
fi

for tmpayload in ${@:2}; do
	if [[ "$tmpayload" =~ ^(.+):(.+)$ ]]; then
		key="${BASH_REMATCH[1]}"
		val="${BASH_REMATCH[2]}"

		payload="$payload, \"$key\": \"$val\" "
	else
		echo "Invalid payload, you doofus!"
		exit 1
	fi
done

if [ -n "$payload" ]; then
	payload=${payload#,}
	payload=", \"client_payload\": {$payload}"
fi

data="{ \"event_type\": \"$event\"$payload }"

echo "dispatch"
echo "$data"
echo

if [[ ! " ${known[@]} " =~ " ${event} " ]]; then
	echo "[WARNING] unknown event '$event'"
	echo
fi

if [ -n "$WINDIR" ]; then
	winpty=winpty
fi

read -p "Enter host username: " username

if [ -z "$username" ]; then
	echo "Username is required, you doofus!"
	exit 1
fi

$winpty curl -i -u "$username" -H "Accept: application/vnd.github.everest-preview+json" -H "Content-Type: application/json" https://api.github.com/repos/$repo/dispatches --data "$data"
