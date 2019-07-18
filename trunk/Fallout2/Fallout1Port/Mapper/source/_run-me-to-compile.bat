@echo off
prompt $g
del *.int
del *.i
del compile.log
@for %%f in (scripts\*.ssl) do MC %%~nf
