@echo off
rem *** Example user config for compiling script file ***

if not exist %1 goto NOFILE
set namescript=%~n1

set ipath=%2

rem Preprocessor definition for conditional compilation option
set def=%3

rem Compiling with Short-Circuit Evaluation option
set shortCircuit=%4

rem Set path to compile scripts
set pathcompile=..\

rem Set name and path for preprocessing file
set prefile=..\scrTemp\%namescript%_[pre].ssl
if exist %prefile% del %prefile%

echo -------------------------------------------------------------------------------
echo   Compilation script: 
echo   %1
echo -------------------------------------------------------------------------------
wcc386.exe %1 -p -fo=%namescript%.i -w -i=%ipath% %def%
if not exist %namescript%.i goto ERROR
echo   Preprocessing script: OK.

ren %namescript%.i %namescript%.ssl
if exist %namescript%.int del %namescript%.int

rem compiling script with original fallout Bis compiler
dos32a.exe bcompile.exe %namescript%.ssl
if exist %namescript%.int goto COMPILE
echo   [Warning] BIS Compilation script error.

echo   Sfall - Compilation script.
echo -------------------------------------------------------------------------------
compile.exe -O1 %shortCircuit% %namescript%.ssl
echo -------------------------------------------------------------------------------
:COMPILE
if not exist %namescript%.int goto ERROR 
move %namescript%.int %pathcompile%%namescript%.int
del %namescript%.ssl
echo Script compilation is completed.
echo Script file is compiled into: %pathcompile%%namescript%.int
goto DONE

:NOFILE
echo File script %1 is not found.
Exit 1
goto DONE

:ERROR
echo Compilation of script %namescript%.ssl error.
echo Look for an error in preprocessing file: %prefile%
move %namescript%.ssl %prefile%
Exit 1

:DONE