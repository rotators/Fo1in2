@REM
@REM For quick compilation without VS (%WINDIR%\Microsoft.Net\Framework\v*\csc.exe won't work [for average user], as it supports C#5 only)
@REM
@REM https://dist.nuget.org/win-x86-commandline/latest/nuget.exe
@REM nuget.exe install Microsoft.Net.Compilers -ExcludeVersion
@REM
Microsoft.Net.Compilers\tools\csc.exe src\Program.cs src\dat.cs src\script.cs
