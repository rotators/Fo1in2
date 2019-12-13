#!/bin/bash

set -e

for option in "$@"; do
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
    echo "  get               prints setting in .ini file"
    echo "    --ini=[path]    path to ddraw.ini"
    echo "    --cfg=[name]    section name"
    echo "    --key=[name]    key name"
    echo ""
    echo "  set               changes setting in .ini file"
    echo "    --ini=[path]    path to ddraw.ini"
    echo "    --cfg=[name]    section name"
    echo "    --key=[name]    key name"
    echo "    --val=[string]  key value"
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
    echo "    --mod=[string]  mod version string; replacements: @COMMITS@"
    echo "    --bump          (optional) increase minor mod version by 1"
    echo ""

    if [ -n "$error" ]; then
       echo "ERROR: $error"
       echo ""
    fi

    exit 1
}

# here be dragon
# awk -v section="SectionName" -v key="SettingName" 'match($0,/^[\t\ ]*\[(.+)\]/,re) {curr=re[1]; next} match($0,/^[\t\ ]*(.+)[\t\ ]*=[\t\ ]*(.+)/,line) {gsub("\r",""); if(curr!=section || line[1]!=key) next; print NR"|"curr"|"line[1]"|"line[2]}' FileName.ini

function Get()
{
    local ini=$1
    local cfg=$2
    local key=$3

    [ -z "$ini" ] && Usage ".ini filename not set"
    [ -z "$cfg" ] && Usage ".ini section not set"
    [ -z "$key" ] && Usage ".ini key not set"
    [ ! -r $ini ] && Usage "cannot read '$ini'"

    awk -v section="$cfg" -v key="$key" 'match($0,/^[\t\ ]*\[(.+)\]/,re) {curr=re[1]; next} match($0,/^[\t\ ]*(.+)[\t\ ]*=[\t\ ]*(.+)/,line) {gsub("\r",""); if(curr!=section || line[1]!=key) next; print line[2]}' $ini
}

function Set()
{
    local ini=$1
    local cfg=$2
    local key=$3
    local val=$4

    [ -z "$ini" ] && Usage ".ini filename not set"
    [ -z "$cfg" ] && Usage ".ini section not set"
    [ -z "$key" ] && Usage ".ini key not set"
    [ -z "$val" ] && Usage ".ini value not set"
    [ ! -r $ini ] && Usage "cannot read '$ini'"
    [ ! -w $ini ] && Usage "cannot write '$ini'"

    # get line number with [section]->key setting
    local line=$(awk -v section="$cfg" -v key="$key" 'match($0,/^[\t\ ]*\[(.+)\]/,re) {curr=re[1]; next} match($0,/^[\t\ ]*(.+)[\t\ ]*=[\t\ ]*(.+)/,line) {gsub("\r",""); if(curr!=section || line[1]!=key) next; print NR}' $ini) #'

    if [ -z "$line" ]; then
       echo "ERROR: [$cfg]->$key not found";
       exit 1
    fi

    dos2unix -q $ini

    # rewrite line with new setting
    sed -ri "${line}s!^.+!$key=$val!" $ini

    unix2dos -q $ini
}

# download ddraw.dll compiled from 'develop' branch (no changes compared to original sfall repository)
function GetDllAppVeyor()
{
    local dll=$1

    [ -z "$dll" ] && Usage ".dll filename not set"
    [ ! -w $dll ] && Usage "cannot write '$dll'"

    curl -L 'https://ci.appveyor.com/api/projects/rotators/sfall/artifacts/ddraw.dll?job=Configuration:%20ReleaseXP&branch=develop&pr=false' -o $dll
}

# extract version info from .dll file
# using 7zip which is probably most portable way to do that
# for reference:
#   powershell -command "(Get-Item ddraw.dll).VersionInfo.ProductVersion"
#   exiftool ddraw.dll | egrep '^File Version[\t\ ]+:' | awk '{print $4}'
function GetDllVersion()
{
    local dll=$1

    [ -z "$dll" ] && Usage ".dll filename not set"
    [ ! -r $dll ] && Usage "cannot read '$dll'"

    # 7zip v19.00 uses slightly different format than v16.00 when reporting version info (two lines match on v19.00, one on v16.00)
    # use last match found -- without trailing ".0"
    local version=$(7z l $dll | grep '^FileVersion:' | awk '{print $2}' | tail -1)

    echo "$version"
}

# update comment with currently used sfall version, extracted from .dll
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

# update setting with mod version string
function SetModVersion()
{
    local ini=$1
    local mod=$2
    local bump=$3

    [ -z "$ini" ] && Usage ".ini filename not set"
    [ -z "$mod" ] && Usage "mod version not set"

    local commits=$(git rev-list HEAD --count)

    if [ $bump -eq 1 ]; then
       local commits=$((commits+1))
    fi

    local mod=$(echo "$mod" | sed -e "s!@COMMITS@!$commits!g")

    Set "$ini" "Misc" "VersionString" "$mod"
}

option_cfg=
option_dll=
option_ini=
option_key=
option_mod=
option_val=
option_bump=0

if   [ -z "$command" ]; then
     Usage
elif [ "$command" == "get" ]; then
     for option in "${@:2}"; do
         [[ "$option" =~ ^--ini=(.+)$ ]] && option_ini=${BASH_REMATCH[1]}
         [[ "$option" =~ ^--cfg=(.+)$ ]] && option_cfg=${BASH_REMATCH[1]}
         [[ "$option" =~ ^--key=(.+)$ ]] && option_key=${BASH_REMATCH[1]}
     done
     Get "$option_ini" "$option_cfg" "$option_key"
elif [ "$command" == "set" ]; then
     for option in "${@:2}"; do
         [[ "$option" =~ ^--ini=(.+)$ ]] && option_ini=${BASH_REMATCH[1]}
         [[ "$option" =~ ^--cfg=(.+)$ ]] && option_cfg=${BASH_REMATCH[1]}
         [[ "$option" =~ ^--key=(.+)$ ]] && option_key=${BASH_REMATCH[1]}
         [[ "$option" =~ ^--val=(.+)$ ]] && option_val=${BASH_REMATCH[1]}
     done
     Set "$option_ini" "$option_cfg" "$option_key" "$option_val"
elif [ "$command" == "get-dll-appveyor" ]; then
     for option in "${@:2}"; do
         [[ "$option" =~ ^--dll=(.+)$ ]] && option_dll=${BASH_REMATCH[1]}
     done
     GetDllAppVeyor "$option_dll"
elif [ "$command" == "get-dll-version" ]; then
     for option in "${@:2}"; do
         [[ "$option" =~ ^--dll=(.+)$ ]] && option_dll=${BASH_REMATCH[1]}
     done
     GetDllVersion "$option_dll"
elif [ "$command" == "set-dll-version" ]; then
     for option in "${@:2}"; do
         [[ "$option" =~ ^--ini=(.+)$ ]] && option_ini=${BASH_REMATCH[1]}
         [[ "$option" =~ ^--dll=(.+)$ ]] && option_dll=${BASH_REMATCH[1]}
     done
     SetDllVersion "$option_ini" "$option_dll"
elif [ "$command" == "set-mod-version" ]; then
     for option in "${@:2}"; do
         [[ "$option" =~ ^--ini=(.+)$ ]] && option_ini=${BASH_REMATCH[1]}
         [[ "$option" =~ ^--mod=(.+)$ ]] && option_mod=${BASH_REMATCH[1]}
         [[ "$option" =~ ^--bump$ ]] && option_bump=1
     done
     SetModVersion "$option_ini" "$option_mod" "$option_bump"
else
     Usage "unknown command '$command'"
fi
