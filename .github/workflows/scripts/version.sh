#!/bin/bash


MOD_VERSION="1.3"


MOD_COMMITS=$(git rev-list HEAD --count)

if [ "$2" == "--bump" ]; then
   MOD_COMMITS=$((MOD_COMMITS+1))
fi

MOD_VERSION_LONG="${MOD_VERSION}.${MOD_COMMITS}"

[ "$1" == "game"  ]   && echo "FALLOUT ET TU v${MOD_VERSION_LONG}" && exit
[ "$1" == "release" ] && echo "Fallout1in2 v${MOD_VERSION_LONG}"   && exit
[ "$1" == "tag" ]     && echo "v${MOD_VERSION_LONG}"               && exit

[ "$1" == "raw" ]     && echo "${MOD_VERSION}"                     && exit

echo ""
echo "USAGE:  $(basename $0) <game|release|tag> [--bump]"
echo ""
exit 1
