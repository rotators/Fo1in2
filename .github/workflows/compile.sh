#!/bin/bash

compile_exe="$(pwd)/Tools/sFall_ScriptEditor/resources/compile.exe"
compile_log="$(pwd)/compile.log"
scripts_dir="$(pwd)/Fallout2/Fallout1in2/Mapper/source/scripts"

# local testing
if [ -f $compile_log ]; then
   rm $compile_log
fi

# ssl files with errors
ssl_errors=()

for ssl_full in $scripts_dir/**/*.[Ss][Ss][Ll]; do
    ssl_file=$(basename $ssl_full)
    ssl_dir=$(dirname $ssl_full)
    ssl_show=$(echo "$ssl_full" | sed -e "s!^$scripts_dir/!!")
    int_file=$(echo "$ssl_file" | sed -e 's!\.[Ss][Ss][Ll]$!\.int!')

    echo ::group::Compiling $ssl_show

    # ssl compiler is too dumb to understand paths and always checks current directory
    cd $ssl_dir
    $compile_exe -q -n -l -p -s -O2 $ssl_file -o $int_file | tee -a $compile_log

    # log cleanup
    sed -i '/^$/d' $compile_log
    sed -i '/^Compiling /d' $compile_log
    sed -i '/THERE WERE ERRORS/g' $compile_log

    if [ -f "$int_file" ]; then
       rm $int_file
    else
       ssl_errors+=("$ssl_show")
    fi

    echo ::endgroup::
done

exit_val=0

# !ssl_errors.empty()
if [ "${#ssl_errors[@]}" -gt 0 ]; then
   exit_val=1
   echo "ERRORS"
   for error in ${ssl_errors[@]}; do
       echo "  $error"
   done
   echo ""
fi

# exist and not empty
if [ -s "$compile_log" ]; then
   cat $compile_log
fi

echo exit $exit_val
exit $exit_val
