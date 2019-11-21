#!/bin/bash

set -e

readonly repo="rotators/Fo1in2"

event="$1"
if [ -z "$event" ]; then
   echo "Usage: dispatch.sh [event]"
   exit 1
fi

known=(schedule schedule-push)

echo "Sending dispatch"
echo "  event_type: $event"
echo

if [[ ! " ${known[@]} " =~ " ${event} " ]]; then
	echo "WARNING: unknown event '$event'"
	echo
fi

winpty=

if [ -n "$WINDIR" ]; then
	winpty=$winpty
fi

read -p "Enter host username: " username

if [ -z "$username" ]; then
	echo "Username is required, you doofus!"
	exit 1
fi

$winpty curl -i -u "$username" -H "Accept: application/vnd.github.everest-preview+json" -H "Content-Type: application/json" https://api.github.com/repos/$repo/dispatches --data "{\"event_type\": \"$event\"}"
