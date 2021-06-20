#!/bin/bash

set -eu

# NOTE: poify uses

mods=Fallout2/Fallout1in2/mods
msg2po=Tools/msg2po

git submodule update --init
pip3 install -r $msg2po/requirements.txt
pip3 install shyaml

po="$(cat .bgforge.yml | shyaml get-value translation.po_dir || echo po)"
src="$(cat .bgforge.yml | shyaml get-value translation.src_lang)"
tra="$(cat .bgforge.yml | shyaml get-value translation.tra_dir)"

rm -fr $tra $mods
mkdir -p $tra

# get current state from master branch
git checkout master $mods/fo1_base/text/$src/
git checkout master $mods/fo1_lang_*
git rm -r --cached Fallout2/

# generate <base>.pot
mv $mods/fo1_base/text/$src $tra/$src
rm -fr $mods/fo1_base/
$msg2po/poify
rm -fr $tra/$src/

# generate <lang>.po
find $mods -type d -name 'fo1_lang_*' | sort | while read dir; do
   # dir=Fallout2/Fallout1in2/mods/fo1_lang_name
     dir_base="$(basename $dir)" # fo1_lang_name
     lang="${dir_base:9}"        # name

     mv $dir/text/$lang/ $tra/$lang/
     rm -fr $dir/

     cp $tra/$po/$src.pot $tra/$po/$lang.po
     $msg2po/dir2msgstr -s $tra/$lang -o $tra/po/$lang.po --ext msg
     $msg2po/dir2msgstr -s $tra/$lang -o $tra/po/$lang.po --ext sve
     $msg2po/dir2msgstr -s $tra/$lang -o $tra/po/$lang.po --ext txt
     # anything else?

     rm -fr $tra/$lang
done

rm -fr Fallout2/
