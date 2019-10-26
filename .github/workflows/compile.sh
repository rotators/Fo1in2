#!/bin/bash

compile_exe="$(pwd)/Tools/sFall_ScriptEditor/resources/compile.exe"
scripts_dir="$(pwd)/Fallout2/Fallout1in2/Mapper/source/scripts"

exit_val=0

echo Compiling...

for ssl_full in $scripts_dir/**/*.[Ss][Ss][Ll]; do
    local ssl_file=$(basename $ssl_full)
    local ssl_dir=$(dirname $ssl_full)
    local ssl_show=$(echo "$ssl_full" | sed -e "s!^$scripts_dir/!!")
    local int_file=$(echo "$ssl_file" | sed -e 's!\.[Ss][Ss][Ll]$!\.int!')
    local log_file=$ssl_file.log
    local ssl_prefix=

    # ssl compiler is too dumb to understand paths and always checks current directory
    cd $ssl_dir
    $compile_exe -q -n -l -p -s -O2 $ssl_file -o $int_file > $log_file

    # clean unwanted lines from log
    sed -i '/^$/d' $log_file
    sed -i '/^Compiling /d' $log_file
    sed -i '/THERE WERE ERRORS/g' $log_file

    if [ -f "$int_file" ]; then
       ssl_prefix=WARNING
       rm $int_file
    else
       ssl_prefix=ERROR
       exit_val=1
    fi

    # if log exists and not empty
    if [ -s "$log_file" ]; then
       echo ::group::[$ssl_prefix] $ssl_show
       cat $log_file
       echo ::endgroup::
    fi
    rm $log_file
done

echo exit $exit_val
exit $exit_val
