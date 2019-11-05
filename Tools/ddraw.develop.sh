#!/bin/bash

set -e

MOD_DIR="$(git rev-parse --show-toplevel)/Fallout2/Fallout1in2"

curl -L "https://ci.appveyor.com/api/projects/rotators/sfall/artifacts/ddraw.dll?job=Configuration:%20ReleaseXP&branch=develop&pr=false" -o "$MOD_DIR/ddraw.develop.dll"
