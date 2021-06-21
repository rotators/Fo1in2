#!/bin/bash

set -eu

mods=Fallout2/Fallout1in2/mods
msg2po=Tools/msg2po

git fetch origin master:master
git submodule update --init
pip3 install -r $msg2po/requirements.txt
pip3 install shyaml

# NOTE: msg2po scripts uses .bgforge.yml way too often, it's better to roll with that...

po="$(cat .bgforge.yml | shyaml get-value translation.po_dir || echo po)"
src="$(cat .bgforge.yml | shyaml get-value translation.src_lang)"
tra="$(cat .bgforge.yml | shyaml get-value translation.tra_dir)"

rm -fr $mods

$msg2po/unpoify

find $tra -mindepth 1 -maxdepth 1 -type d | sort | while read dir; do
     if [[ $dir == "$tra/$po" ]]; then
        continue
     fi

     lang="$(basename $dir)"
     mkdir -p $mods
     mv $tra/$lang $mods/fo1_lang_$lang
done
