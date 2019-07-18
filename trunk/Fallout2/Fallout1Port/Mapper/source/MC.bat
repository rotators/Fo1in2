@ECHO OFF
prompt $g
mcpp.exe -P -Iinclude scripts\%1.ssl %1.i
IF ERRORLEVEL 1 PAUSE
compile.exe -n %1.i
IF ERRORLEVEL 1 PAUSE
MOVE /Y %1.INT C:\Users\Sduibek\Documents\Dropbox\GitHub\fo1tofo2\from_download\DATA\SCRIPTS
IF ERRORLEVEL 1 PAUSE
