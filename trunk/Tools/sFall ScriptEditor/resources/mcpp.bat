@echo off
set fscript=%1
set pfile=%2
set warn=%3
set scrpath=%4
set path=%5
set def=%6
set param=%7
set add=%8

echo Include path: %path%
echo Script preprocessing path: %fscript%

mcpp.exe -v -k -Q -W%warn% %fscript% -o%pfile% -I%path% -I%scrpath% %def% %param% %add%

if not exist %pfile% goto FAILED
goto DONE

:FAILED
Exit 1
:DONE