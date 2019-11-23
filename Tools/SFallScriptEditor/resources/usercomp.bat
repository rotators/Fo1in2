@echo off
rem *** Example user config for compiling script file ***

if not exist %1 goto NOFILE
set namescript=%~n1

rem Include files path
set ipath=%2

rem Path to compile scripts
set pathcompile=%3

rem Preprocessor definition for conditional compilation option
set def=
if not %4 == 0 (
	echo Build type: %4
	set def=-d%4%
) else (echo Build type: None)

rem Compiling with optimization level option
set optimize=%5

rem Compiling with Short-Circuit Evaluation option (last)
set shortCircuit=%7

rem Set name and path for preprocessing file
set prefile=..\scrTemp\%namescript%_[pre].ssl
if exist %prefile% del %prefile%
if exist %namescript%.ssl del /q %namescript%.ssl

echo -------------------------------------------------------------------------------
echo   Compilation script:
echo   %~6\%namescript%.ssl
echo -------------------------------------------------------------------------------
wcc386.exe %1 -p -fo=%namescript%.i -w -i=%ipath% %def%
if not exist %namescript%.i goto ERROR
echo   Preprocessing script: OK.

ren %namescript%.i %namescript%.ssl
if exist %namescript%.int del %namescript%.int

rem compiling script sfall compiler with BIS compatible mode
compile.exe -b -O%optimize% %namescript%.ssl

if exist %namescript%.int (
	echo   [BIS] Script compilation is completed.
	goto COMPILE
)
echo   [BIS] Compilation script error.
echo   Try sfall compiler.
echo -------------------------------------------------------------------------------
compile.exe -O%optimize% %shortCircuit% %namescript%.ssl
echo -------------------------------------------------------------------------------
if not exist %namescript%.int goto ERROR
echo   [SFALL] Script compilation is completed.

:COMPILE
move %namescript%.int %pathcompile%\%namescript%.int
del %namescript%.ssl
echo Script file is compiled into: %pathcompile:~1,-1%\%namescript%.int
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