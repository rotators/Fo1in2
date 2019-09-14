#!/bin/bash

curl -L "https://ci.appveyor.com/api/projects/rotators/sfall/artifacts/ddraw.dll?job=Configuration:%20ReleaseXP&branch=develop&pr=false" -o ddraw.dev.dll
