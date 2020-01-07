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
    echo "  get                prints setting in .ini file"
    echo "    --ini=[path]     path to .ini file"
    echo "    --cfg=[name]     section name"
    echo "    --key=[name]     key name"
    echo "    --fmt=[format]   (optional) use specific format for output"
    echo ""
    echo "  set                changes setting in .ini file"
    echo "    --ini=[path]     path to .ini file"
    echo "    --cfg=[name]     section name"
    echo "    --key=[name]     key name"
    echo "    --val=[string]   key value"
    echo "    --with-space     (optional) adds spaces around '='"
    echo ""
    echo "  list               prints section settings in .ini file"
    echo "    --ini=[path]     path to .ini file"
    echo "    --cfg=[name]     section name"
    echo "    --section-name   (optional) adds section name before output"
    echo ""
    echo "  get-dll-appveyor   downloads ddraw.dll"
    echo "    --dll=[path]     output filename"
    echo "    --branch=[name]  branch name"
    echo ""
    echo "  get-dll-version    prints .dll FileVersion"
    echo "    --dll=[path]     path to .dll file"
    echo ""
    echo "  set-dll-version    updates comment with sfall version"
    echo "    --ini=[path]     path to ddraw.ini"
    echo "    --dll=[path]     path to ddraw.dll"
    echo ""
    echo "  set-mod-version    updates setting 'VersionString'"
    echo "    --ini=[path]     path to ddraw.ini"
    echo "    --mod=[string]   mod version string; replacements: @COMMITS@"
    echo "    --bump           (optional) increases @COMMITS@ value by 1"
    echo ""

    if [ -n "$error" ]; then
       echo "ERROR: $error"
       echo ""
    fi

    exit 1
}

# here be dragon
# based on https://stackoverflow.com/a/54597545/11998612
function IniParse()
{
    local ini='\
# find and save current section                         \
match( $0, /^[\t\ ]*\[(.+)\]/, re )                     \
{                                                       \
    in_section=re[1];                                   \
    next;                                               \
}                                                       \
                                                        \
# find and print current setting                        \
match( $0, /^[\t\ ]*(.+)[\t\ ]*=[\t\ ]*(.+)/, in_key )  \
{                                                       \
    # skip comments                                     \
    if( match( in_key[1], /^[#;]/ ))                    \
        next;                                           \
                                                        \
    # normalize line ending                             \
    gsub( "\r", "" );                                   \
                                                        \
    # normalize setting name/value                      \
    sub( /[\t ]+$/, "", in_key[1] );                    \
    sub( /^[\t ]+/, "", in_key[2] );                    \
                                                        \
    # skip unwanted entries                             \
    if( ___IF___ )                                      \
        next;                                           \
                                                        \
    # strip trailing comment                            \
    sub( /[\t ]*[;#].*$/, "", in_key[2] );              \
                                                        \
    # print results                                     \
    #   in_section  current section name                \
    #   in_key[1]   current setting name                \
    #   in_key[2]   current setting value               \
    print ___PRINT___                                   \
}'

    # allow changing which parts should be printed
    if [ -n "$1" ]; then
       local _print=$1
    else
       local _print='"["in_section"]", in_key[1], "=", in_key[2]'
    fi

    # allow changing which lines should be skipped
    if [ -n "$2" ]; then
       local _if=$2
    else
       local _if='in_section != section || in_key[1] != key'
    fi

    local ini=$(echo "$ini" | sed -e "s@___PRINT___@${_print}@g" -e "s@___IF___@${_if}@g")

    echo "$ini"
}

function Get()
{
    local ini=$1
    local cfg=$2
    local key=$3
    local fmt=$4

    [ -z "$ini" ] && Usage ".ini filename not set"
    [ -z "$cfg" ] && Usage ".ini section not set"
    [ -z "$key" ] && Usage ".ini key not set"
    [ ! -r $ini ] && Usage "cannot read '$ini'"

    if [ -z "$fmt" ]; then
       local fmt='in_key[2]'
    fi

    awk -v section="$cfg" -v key="$key" "$(IniParse "$fmt")" $ini
}

function Set()
{
    local ini=$1
    local cfg=$2
    local key=$3
    local val=$4
    local int=$5

    [ -z "$ini" ] && Usage ".ini filename not set"
    [ -z "$cfg" ] && Usage ".ini section not set"
    [ -z "$key" ] && Usage ".ini key not set"
    [ -z "$val" ] && Usage ".ini value not set"
    [ ! -r $ini ] && Usage "cannot read '$ini'"
    [ ! -w $ini ] && Usage "cannot write '$ini'"

    if [ -n "$int" ] && [ $int -eq 1 ]; then
       local space=" "
    else
       local space=""
    fi

    # get line number with [section]->key setting
    local line=$(awk -v section="$cfg" -v key="$key" "$(IniParse 'NR')" $ini) #"

    if [ -z "$line" ]; then
       echo "ERROR: setting [$cfg]->$key not found";
       exit 1
    fi

    dos2unix -q $ini

    # rewrite line with new setting
    sed -ri "${line}s!^.+!${key}${space}=${space}$val!" $ini

    unix2dos -q $ini
}

function List()
{
    local ini=$1
    local cfg=$2
    local int=$3

    [ -z "$ini" ] && Usage ".ini filename not set"
    [ -z "$cfg" ] && Usage ".ini section not set"
    [ ! -r $ini ] && Usage "cannot read '$ini'"

    if [ -n "$int" ] && [ $int -eq 1 ]; then
       echo "[$cfg]"
    fi

    awk -v section="$cfg" "$(IniParse 'in_key[1]" = "in_key[2]' 'in_section != section')" $ini
}

# download ddraw.dll compiled from specific branch (ReleaseXP configuration)
# branches 'master' and 'develop' = no changes compared to original sfall repository
function GetDllAppVeyor()
{
    local dll=$1
    local branch=$2

    [ -z "$dll" ] && Usage ".dll filename not set"
    [ -z "$branch" ] && Usage "branch not set"

    [ ! -w $dll ] && Usage "cannot write '$dll'"

    curl -L "https://ci.appveyor.com/api/projects/rotators/sfall/artifacts/ddraw.dll?job=Configuration:%20ReleaseXP&branch=${branch}&pr=false" -o $dll
}

# extract version info from .dll file
# using 7zip which is probably most portable way to do that
# for reference:
#   powershell -command "(Get-Item ddraw.dll).VersionInfo.ProductVersion"
#   exiftool ddraw.dll | egrep '^File Version[\t ]+:' | awk '{print $4}'
function GetDllVersion()
{
    local dll=$1

    [ -z "$dll" ] && Usage ".dll filename not set"
    [ ! -r $dll ] && Usage "cannot read '$dll'"

    # 7zip v19.x uses slightly different format than v16.x when reporting version info (two lines match on v19.x, one on v16.x)
    # use last match found -- without trailing ".0"
    local version=$(7z l $dll | egrep '^(FileVersion|Comment = FileVersion):' | sed -e 's!^Comment = !!' | awk '{print $2}' | tail -1) #'

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
    local int=$3

    [ -z "$ini" ] && Usage ".ini filename not set"
    [ -z "$mod" ] && Usage "mod version not set"

    local commits=$(git rev-list HEAD --count)

    if [ -n "$int" ] && [ $int -eq 1 ]; then
       local commits=$((commits+1))
    fi

    local mod=$(echo "$mod" | sed -e "s!@COMMITS@!$commits!g")

    Set "$ini" "Misc" "VersionString" "$mod"
}

option_cfg=
option_dll=
option_fmt=
option_ini=
option_key=
option_mod=
option_val=

option_int=0

if   [ -z "$command" ]; then
     Usage
elif [ "$command" == "get" ]; then
     for option in "${@:2}"; do
         [[ "$option" =~ ^--ini=(.+)$ ]] && option_ini=${BASH_REMATCH[1]}
         [[ "$option" =~ ^--cfg=(.+)$ ]] && option_cfg=${BASH_REMATCH[1]}
         [[ "$option" =~ ^--key=(.+)$ ]] && option_key=${BASH_REMATCH[1]}
         [[ "$option" =~ ^--fmt=(.+)$ ]] && option_fmt=${BASH_REMATCH[1]}
     done
     Get "$option_ini" "$option_cfg" "$option_key" "$option_fmt"
elif [ "$command" == "set" ]; then
     for option in "${@:2}"; do
         [[ "$option" =~ ^--ini=(.+)$ ]] && option_ini=${BASH_REMATCH[1]}
         [[ "$option" =~ ^--cfg=(.+)$ ]] && option_cfg=${BASH_REMATCH[1]}
         [[ "$option" =~ ^--key=(.+)$ ]] && option_key=${BASH_REMATCH[1]}
         [[ "$option" =~ ^--val=(.+)$ ]] && option_val=${BASH_REMATCH[1]}
         [[ "$option" =~ ^--with-space$ ]] && option_int=1
     done
     Set "$option_ini" "$option_cfg" "$option_key" "$option_val" "$option_int"
elif [ "$command" == "list" ]; then
     for option in "${@:2}"; do
         [[ "$option" =~ ^--ini=(.+)$ ]] && option_ini=${BASH_REMATCH[1]}
         [[ "$option" =~ ^--cfg=(.+)$ ]] && option_cfg=${BASH_REMATCH[1]}
         [[ "$option" =~ ^--section-name ]] && option_int=1
     done
     List "$option_ini" "$option_cfg" "$option_int"
elif [ "$command" == "get-dll-appveyor" ]; then
     for option in "${@:2}"; do
         [[ "$option" =~ ^--dll=(.+)$ ]] && option_dll=${BASH_REMATCH[1]}
         [[ "$option" =~ ^--branch=(.+)$ ]] && option_key=${BASH_REMATCH[1]}
     done
     GetDllAppVeyor "$option_dll" "${option_key}"
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
         [[ "$option" =~ ^--bump$ ]] && option_int=1
     done
     SetModVersion "$option_ini" "$option_mod" "$option_int"
else
     Usage "unknown command '$command'"
fi
