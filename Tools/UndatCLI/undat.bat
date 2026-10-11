@echo off

set "master_dat=%~1"
if "%master_dat%" == "" goto NOFILE
if not exist "%master_dat%" goto NOFILE

set "root_dir=%~dp0"
set "data_dir=%root_dir%data"
set "dat2=%root_dir%dat2.exe"
set "undat_list=%root_dir%undat_files.txt"

"%dat2%" l "%master_dat%" >nul 2>&1
if errorlevel 1 (
    echo Error: can't read Fallout 1's master.dat.
    exit /b 1
)

"%dat2%" x -d "%data_dir%" "%master_dat%" "@%undat_list%"
if errorlevel 1 exit /b 1

echo Extracted successfully.
exit /b 0

:NOFILE
echo Please pass path to Fallout 1's master.dat to the script.
exit /b 1
