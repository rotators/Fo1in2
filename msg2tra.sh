#!/bin/bash

set -eux

function SetHeader()
{
    local pot="$1"
    local key="$2"
    local val="$3"

    sed -ri "s!^\"($key):.+\"\$!\"\1: $val\\\\n\"!" $pot
}

function Format()
{
    local po="$1"

    local args=--no-wrap

    msguniq   $args --output-file=$po.tmp $po
    msgattrib $args --output-file=$po $po.tmp
    rm -f $po.tmp
}

msg2po="$(cat .bgforge.yml | grep msg2po_dir: | awk '{print $2}')"
pip3 install -r $msg2po/requirements.txt

po="po"
#po="$($msg2po/bgforge-config.py po_dir)"
src="$($msg2po/bgforge-config.py src_lang)"
tra="$($msg2po/bgforge-config.py tra_dir)"

gha="$($msg2po/bgforge-config.py ettu_gha)"
mods="$($msg2po/bgforge-config.py ettu_mods)"

git fetch origin master:master
git submodule update --init
pip3 install $($msg2po/bgforge-config.py ettu_pip)

rm -fr $tra $mods
mkdir -p $tra/$po

# get current state from master branch
git checkout master $gha/version.sh
git checkout master $mods/fo1_base/text/$src/
git checkout master $mods/fo1_lang_*
git rm -r --cached $gha/version.sh $mods

# generate <base>.pot
mv $mods/fo1_base/text/$src $tra/$src
rm -fr $mods/fo1_base/
$msg2po/poify | tee $tra/$po/$src.log
rm -fr $tra/$src/

SetHeader $tra/$po/$src.pot "Project-Id-Version" "Fallout1in2 v$($gha/version.sh raw)"
SetHeader $tra/$po/$src.pot "Report-Msgid-Bugs-To" "https://github.com/rotators/Fo1in2/issues/"
SetHeader $tra/$po/$src.pot "Language" "$src"
Format $tra/$po/$src.pot
msgcheck $tra/$po/$src.pot > $tra/$po/$src.msgcheck || true

# generate <lang>.po
find $mods -type d -name 'fo1_lang_*' | sort | while read dir; do
   # dir=Fallout2/Fallout1in2/mods/fo1_lang_name
     dir_base="$(basename $dir)" # fo1_lang_name
     lang="${dir_base:9}"        # name

     mv $dir/text/$lang/ $tra/$lang/
     rm -fr $dir/

     cp $tra/$po/$src.pot $tra/$po/$lang.po
     $msg2po/dir2msgstr -s $tra/$lang -o $tra/$po/$lang.po --ext msg | tee --append $tra/$po/$lang.log
     $msg2po/dir2msgstr -s $tra/$lang -o $tra/$po/$lang.po --ext sve | tee --append $tra/$po/$lang.log
     $msg2po/dir2msgstr -s $tra/$lang -o $tra/$po/$lang.po --ext txt | tee --append $tra/$po/$lang.log
     # anything else?

     rm -fr $tra/$lang

     SetHeader $tra/$po/$lang.po "Language" "$lang"

     Format $tra/$po/$lang.po
     msgcheck $tra/$po/$lang.po > $tra/$po/$lang.msgcheck || true
done

rm -fr $gha $mods
find . -type d -empty -delete

find $tra/$po -type f -iname '*.msgcheck' | while read file; do
     sed -ri "s!$(pwd)/$tra/$po/!!g" $file
done
