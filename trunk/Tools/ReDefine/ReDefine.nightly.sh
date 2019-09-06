#!/bin/bash

set -e

zip="/tmp/ReDefine.zip"
exe="ReDefine.exe"

curl -L "https://ci.appveyor.com/api/projects/rotators/ReDefine/artifacts/ReDefine.zip?job=Image:%20Visual%20Studio%202017;%20Platform:%20x32&branch=master&pr=false" -o $zip
7z x -aoa $zip
chmod a+x $exe
rm -f $zip
file $exe
