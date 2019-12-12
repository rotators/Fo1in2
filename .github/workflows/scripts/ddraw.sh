#!/bin/bash

set -e

for option in $@; do
    [[ "$option" =~ ^--debug$ ]] && set -x
done

command=$1

function Usage()
{
    error=$1

    echo ""
    echo "USAGE:  $(basename $0) [command] [options...]"
    echo ""
    echo "COMMANDS"
    echo ""
    echo "  get-dll-appveyor  downloads ddraw.dll"
    echo "    --dll=[path]    output filename"
    echo ""
    echo "  get-dll-version   prints .dll FileVersion"
    echo "    --dll=[path]    path to .dll file"
    echo ""
    echo "  set-dll-version   updates comment with sfall version"
    echo "    --ini=[path]    path to ddraw.ini"
    echo "    --dll=[path]    path to ddraw.dll"
    echo ""
    echo "  set-mod-version   updates setting 'VersionString'"
    echo "    --ini=[path]    path to ddraw.ini"
    echo "    --mod=[0-9]     major mod version"
    echo "    --bump          (optional) increase minor mod version by 1"
    echo ""

    if [ -n "$error" ]; then
       echo "ERROR: $error"
       echo ""
    fi

    exit 1
}

function GetDllAppVeyor()
{
    local dll=$1

    [ -z "$dll" ] && Usage ".dll filename not set"
    [ ! -w $dll ] && Usage "cannot write '$dll'"

    curl -L 'https://ci.appveyor.com/api/projects/rotators/sfall/artifacts/ddraw.dll?job=Configuration:%20ReleaseXP&branch=develop&pr=false' -o $dll
}

function GetDllVersion()
{
    local dll=$1

    [ -z "$dll" ] && Usage ".dll filename not set"
    [ ! -r $dll ] && Usage "cannot read '$dll'"

    # old method, left for reference
    # local version=$(powershell -command "(Get-Item $dll).VersionInfo.ProductVersion")

    # 7zip v19.00 uses slightly different format than v16.00 when reporting version info (two lines match on v19.00, one on v16.00)
    # use last match found -- without trailing ".0"
    local version=$(7z l $dll | grep '^FileVersion:' | awk '{print $2}' | tail -1)

    echo "$version"
}

function SetDllVersion()
{
    local ini=$1
    local dll=$2

    [ -z "$ini" ] && Usage ".ini filename not set"
    [ -z "$dll" ] && Usage ".dll filename not set"
    [ ! -r $ini ] && Usage "cannot read '$ini'"
    [ ! -w $ini ] && Usage "cannot write '$ini'"
    [ ! -r $dll ] && Usage "cannot read '$dll'"

    local version=$(GetDllVersion $dll)

    dos2unix -q $ini
    sed -ri "s!^;v[0-9\.]+.*!;v$version!" $ini
    unix2dos -q $ini
}

function SetModVersion()
{
    # hardcoded due to mess with spaces :(
    local readonly string="FALLOUT ET TU v@MOD@.@COMMITS@"

    local ini=$1
    local mod=$2
    local bump=$3

    [ -z "$ini" ] && Usage ".ini filename not set"
    [ -z "$mod" ] && Usage "mod version not set"
    [ ! -r $ini ] && Usage "cannot read '$ini'"
    [ ! -w $ini ] && Usage "cannot write '$ini'"

    local commits=$(git rev-list HEAD --count)

    if [ $bump -eq 1 ]; then
       local commits=$((commits+1))
    fi

    local version="$string"
    local version=$(echo "$version" | sed -e "s!@MOD@!$mod!g")
    local version=$(echo "$version" | sed -e "s!@COMMITS@!$commits!g")

    dos2unix -q $ini
    sed -ri "s!^[\t\ ]*VersionString[\t\ ]*=[\t\ ]*.+!VersionString=${version}!" $ini
    unix2dos -q $ini
}


option_dll=
option_ini=
option_mod=
option_bump=0

if   [ -z "$command" ]; then
     Usage "missing command"
elif [ "$command" == "get-dll-appveyor" ]; then
     for option in ${@:2}; do
         [[ "$option" =~ ^--dll=(.+)$ ]] && option_dll=${BASH_REMATCH[1]}
     done
     GetDllAppVeyor "$option_dll"
elif [ "$command" == "get-dll-version" ]; then
     for option in ${@:2}; do
         [[ "$option" =~ ^--dll=(.+)$ ]] && option_dll=${BASH_REMATCH[1]}
     done
     GetDllVersion "$option_dll"
elif [ "$command" == "set-dll-version" ]; then
     for option in ${@:2}; do
         [[ "$option" =~ ^--ini=(.+)$ ]] && option_ini=${BASH_REMATCH[1]}
         [[ "$option" =~ ^--dll=(.+)$ ]] && option_dll=${BASH_REMATCH[1]}
     done
     SetDllVersion "$option_ini" "$option_dll"
elif [ "$command" == "set-mod-version" ]; then
     for option in ${@:2}; do
         [[ "$option" =~ ^--ini=(.+)$ ]] && option_ini=${BASH_REMATCH[1]}
         [[ "$option" =~ ^--mod=([0-9]+)$ ]] && option_mod=${BASH_REMATCH[1]}
         [[ "$option" =~ ^--bump$ ]] && option_bump=1
     done
     SetModVersion "$option_ini" "$option_mod" "$option_bump"
else
     Usage "unknown command '$command'"
fi
