#!/bin/bash

set -e

readonly repo="rotators/Fo1in2"

event="$1"
if [ -z "$event" ]; then
   echo "Usage:    dispatch.sh [event] (payload1:value1) (payloadN:valueN)"
   echo
   echo "Example:  dispatch.sh my-event"
   echo "Example:  dispatch.sh my-event my-key:my-value"
   echo
   exit 1
fi

payload=
for tmpayload in ${@:2}; do
	if [[ "$tmpayload" =~ : ]]; then
		key="$(echo "$tmpayload" | awk -F : '{print $1}')"
		val="$(echo "$tmpayload" | awk -F : '{print $2}')"

		if   [ "$key" == "" ]; then
			echo "Invalid payload key, you doofus!"
			exit 1
		elif [ "$val" == "" ]; then
			echo "Invalid payload value, you doofus!"
			exit 1
		fi

		payload="$payload,\"$key\":\"$val\""
		payload=${payload#,}
	else
		echo "Invalid payload, you doofus!"
		exit 1
	fi
done

if [ -n "$payload" ]; then
	data=$(jq -n --arg event "$event" --argjson payload "{$payload}" '{"event_type": $event, "client_payload": $payload}')
else
	data=$(jq -n --arg event "$event" '{"event_type": $event}')
fi

echo "dispatch"
echo "$data"
echo

known=(schedule schedule-push)

if [[ ! " ${known[@]} " =~ " ${event} " ]]; then
	echo "WARNING: unknown event '$event'"
	echo
fi

winpty=

if [ -n "$WINDIR" ]; then
	winpty=winpty
fi

read -p "Enter host username: " username

if [ -z "$username" ]; then
	echo "Username is required, you doofus!"
	exit 1
fi

$winpty curl -i -u "$username" -H "Accept: application/vnd.github.everest-preview+json" -H "Content-Type: application/json" https://api.github.com/repos/$repo/dispatches --data "$data"
