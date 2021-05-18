#!/bin/bash

# set -e ... don't! it will stop this script on first .ssl error;
#            we want a full list of all errors to fix everything at once,
#            instead of 'commit -> report -> fix -> commit...' loop

for option in $@; do
    [[ "$option" =~ ^--debug$ ]] && set -x
done

# default options
option_bytecode=0
option_bytecode_dir="Fallout2/Fallout1in2/mods/fo1_base/scripts"
option_compiler="Tools/SFallScriptEditor/resources/compile.exe"
option_dry=0
option_include_dir=
option_optimization=2
option_scripts_dir="Fallout2/Fallout1in2/Mapper/source/scripts"
option_headers_dir="Fallout2/Fallout1in2/Mapper/source/scripts/headers"

# user options
for option in "$@"; do
    # --bytecode
    # enable updating .int files
    [[ "$option" == "--bytecode" ]] && option_bytecode=1

    # --bytecode-dir=some/directory
    # path to .int files directory
    [[ "$option" =~ ^--bytecode-dir=([A-Za-z0-9_\.\/]+)$ ]] && option_bytecode_dir=${BASH_REMATCH[1]}

    # --bytecode-dir=?
    # path to .int files directory set to .ssl files directory
    [[ "$option" == "--bytecode-dir=?" ]] && option_bytecode_dir="?"

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

    # --headers-dir=some/directory
    # path to .h files directory
    [[ "$option" =~ ^--headers-dir=([A-Za-z0-9_\.\/]+)$ ]] && option_headers_dir=${BASH_REMATCH[1]}

    # --include-dir=some/directory
    # additional include directory used by compiler (-I switch)
    [[ "$option" =~ ^--include-dir=([A-Za-z0-9_\.\/]+)$ ]] && option_include_dir=-I$(pwd)/${BASH_REMATCH[1]}
done

# constants
readonly windows_pwd="$(pwd | sed -re 's!^/([A-Za-z])/!\U\1:/!g')/"
readonly compile_exe="$(pwd)/$option_compiler"
readonly scripts_dir="$(pwd)/$option_scripts_dir"
readonly headers_dir="$(pwd)/$option_headers_dir"
readonly random_char='ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefhijklmnopqrstuvwxyz0123456789'

if [ "$option_bytecode_dir" != "?" ]; then
   readonly bytecode_dir="$(pwd)/$option_bytecode_dir"
else
   readonly bytecode_dir="."
fi

if [ $option_dry -eq 0 ]; then
   readonly dry=
else
   readonly dry=echo
fi

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
last_dir=

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
    # (random).int
    int_temp=
    for c in {1..16}; do
        int_temp="${int_temp}${random_char:RANDOM % ${#random_char}:1}"
    done
    int_temp=${int_temp}.int
    # script.int
    int_file=$(echo "$ssl_file" | sed -e 's!\.[Ss][Ss][Ll]$!\.int!')
    # (random).log
    log_file=$(echo "$int_temp" | sed -e 's!\.int$!\.log!')

    ssl_result=

    # ssl compiler is too dumb to understand paths and always checks current directory
    if [ "$last_dir" != "$ssl_dir" ]; then
       last_dir="$ssl_dir"
       $dry cd "$ssl_dir"
    fi

    $dry $compile_exe -q -l -p -s -I${headers_dir} ${option_include_dir} -O${option_optimization} "$ssl_file" -o "$int_temp" > $log_file

    if [ $option_dry -eq 1 ]; then
       cat $log_file
       rm -f $log_file
       continue
    fi

    # remove unwanted lines from log
    sed -i '/^$/d' $log_file
    sed -i '/^Compiling /d' $log_file
    sed -i '/^Set include directory: /d' $log_file
    sed -i '/THERE WERE ERRORS/d' $log_file

    # convert absolute paths to relative
    sed -i "s!$windows_pwd!!g" $log_file

    # pass #1
    # guess result -- does bytecode exists?

    if [ ! -f "$int_temp" ]; then
       ssl_result=ERROR
       num_errors=$((num_errors+1))
    else
       if [ $option_bytecode -eq 1 ]; then
          mv $int_temp $bytecode_dir/$int_file
       else
         rm $int_temp
       fi
       ssl_result=WARNING
    fi

    # pass #2
    # confirm result -- does log exists and is not empty?
    if [ -s $log_file ]; then
       log_msg="$ssl_result $ssl_show" # log_msg="[$ssl_result]" ... DON'T! grouping colorized lines is broken

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

    rm $log_file
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
