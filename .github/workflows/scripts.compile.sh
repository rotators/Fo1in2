#!/bin/bash

# set -e ... don't! it will stop this script on first .ssl error;
#            we want a full list of all errors to fix everything at once,
#            instead of 'commit -> report -> fix -> commit...' loop

# default options
option_bytecode=0
option_bytecode_dir="Fallout2/Fallout1in2/mods/fo1_base/scripts"
option_compiler="Tools/SFallScriptEditor/resources/compile.exe"
option_dry=0
option_optimization=2
option_scripts_dir="Fallout2/Fallout1in2/Mapper/source/scripts"

# user options
for option in "$@"; do
    # --bytecode
    # enable updating .int files
    [[ "$option" == "--bytecode" ]] && option_bytecode=1

    # --bytecode-dir=some/directory
    # path to .int files directory
    [[ "$option" =~ ^--bytecode-dir=([A-Za-z0-9_\.\/]+)$ ]] && option_bytecode_dir=${BASH_REMATCH[1]}

    # --compiler=some/filename.exe
    # path to compiler executable
    [[ "$option" =~ ^--compiler=([A-Za-z0-9_\.\/]+)$ ]] && option_compiler=${BASH_REMATCH[1]}

    # --dry
    # enable logging arguments passed to compiler without running it
    [[ "$option" == "--dry" ]] && option_dry=1

    # --optimization=0 (none)
    # --optimization=1 (standard)
    # --optimization=2 (full)
    # optimization level used by compiler; values higher than 2 are not recommended/supported
    [[ "$option" =~ ^--optimization=([0-9]+)$ ]] && option_optimization=${BASH_REMATCH[1]}

    # --scripts-dir=some/directory
    # path to .ssl files directory
    [[ "$option" =~ ^--scripts-dir=([A-Za-z0-9_\.\/]+)$ ]] && option_scripts_dir=${BASH_REMATCH[1]}
done

# constants
readonly windows_pwd="$(pwd | sed -re 's!^/([A-Za-z])/!\U\1:/!g')/"
readonly compile_exe="$(pwd)/$option_compiler"
readonly scripts_dir="$(pwd)/$option_scripts_dir"
readonly bytecode_dir="$(pwd)/$option_bytecode_dir"

# output grouping, for GitHub Actions
# regular echo when running on local
function group_start()
{
    if [ -n "$GITHUB_ACTIONS" ]; then
       echo "::group::$@"
    else
       echo "$@"
    fi
}

# output grouping, for GitHub Actions
# no-op when running on local
function group_end()
{
    if [ -n "$GITHUB_ACTIONS" ]; then
       echo "::endgroup::"
    fi
}

# sanity checks
if   [ ! -f "$compile_exe" ]; then
     echo "[ERROR] Cannot find compiler : $compile_exe"
     exit 1
elif [ ! -x "$compile_exe" ]; then
     echo "[ERROR] Cannot run compiler : $compile_exe"
     exit 1
elif [ ! -d "$scripts_dir" ]; then
     echo "[ERROR] Cannot find scripts directory : $scripts_dir"
     exit 1
elif [ ! -d "$bytecode_dir" ]; then
     echo "[ERROR] Cannot find bytecode directory : $bytecode_dir"
     exit 1
fi

num_errors=0
num_warnings=0

echo Compiling...

    # /c/repo/path/to/scripts/sub/dir/script.ssl
for ssl_full in $(find $scripts_dir -type f -name '*.[Ss][Ss][Ll]' | sort); do
    # /c/repo/path/to/scripts/sub/dir
    ssl_dir=$(dirname "$ssl_full")
    # sub/dir/script.ssl
    ssl_show=${ssl_full#$scripts_dir}
    ssl_show=${ssl_show#/}
    # script.ssl
    ssl_file=$(basename "$ssl_full")
    # script.int
    int_file=$(echo "$ssl_file" | sed -e 's!\.[Ss][Ss][Ll]$!\.int!')
    # script.ssl.log
    log_file="$ssl_file.log"

    ssl_result=

    # ssl compiler is too dumb to understand paths and always checks current directory
    cd "$ssl_dir"

    if [ $option_dry -eq 0 ]; then
       $compile_exe -q -l -p -s -O${option_optimization} "$ssl_file" -o "$int_file" > "$log_file"
    else
       echo "[$(dirname $ssl_show)] $compile_exe -q -l -p -s -O${option_optimization} $ssl_file -o $int_file > $log_file"
       continue
    fi

    # remove unwanted lines from log
    sed -i '/^$/d' $log_file
    sed -i '/^Compiling /d' $log_file
    sed -i '/THERE WERE ERRORS/d' $log_file

    # convert absolute paths to relative
    sed -i "s!$windows_pwd!!g" $log_file

    # pass #1
    # guess result -- does bytecode exists?
    if [ ! -f "$int_file" ]; then
       ssl_result=ERROR
       num_errors=$((num_errors+1))
    else
       if [ $option_bytecode -eq 1 ]; then
          mv $int_file $bytecode_dir/$int_file
       else
         rm $int_file
       fi
       ssl_result=WARNING
    fi

    # pass #2
    # confirm result -- does log exists and is not empty?
    if [ -s "$log_file" ]; then
       log_msg="$ssl_result $ssl_show"

       if [ "$ssl_result" == "ERROR" ]; then
          echo $log_msg
          cat $log_file
       else
          num_warnings=$((num_warnings+1))

          # group scripts with warnings only
          group_start $log_msg
          cat $log_file
          group_end
       fi
    fi

    rm "$log_file"
done

str_ok=" OK"
str_errors=
str_warnings=

if [ $num_errors -ge 1 ]; then
   str_ok=
   str_errors=" ERRORS:$num_errors"
fi
if [ $num_warnings -ge 1 ]; then
   str_ok=
   str_warnings=" WARNINGS:$num_warnings"
fi

echo Compiling...${str_ok}${str_errors}${str_warnings}

exit $num_errors
