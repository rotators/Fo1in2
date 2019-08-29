@echo off

setlocal EnableDelayedExpansion

pushd "..\..\..\..\..\Tools\sFall ScriptEditor\resources\"
set compile="%CD%\compile.exe"
popd

set /a e=0
for /f "usebackq" %%S in (`dir /s /b *.ssl`) do (
	pushd %%~dpS

	%compile% -q -n -l -p -O2 %%~nxS -o drycompile.int

	if exist "drycompile.int" (
		del drycompile.int
	) else (
		set /a e+=1
		set ferror[!e!]=%%S
	)
	popd
)

if %e% gtr 0 (
	echo --- ERRORS --
	for /l %%E in (1,1,%e%) do (
		echo !ferror[%%E]!
	)
)
