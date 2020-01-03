This is a tool to extract needed files from the MASTER.DAT resource file shipped with Fallout 1.

# Changelog

## 1.07
2020-01-03
* Use exe path instead of GetCurrentDirectory.
* Enable buttons for choosing directory again if the extraction fails.

## 1.06
2019-12-29
* Autodetect destination mod folder if the program is launched from a directory where fallout2.exe exist.
* Run a GC.Collect() after extraction of a compressed file to clear disposed resources.

## 1.05
2019-12-14
* Removed a few versions of the icon that were unnecessary, to reduce size of exe.
* Icon for application.
* Launching UI via commandline.
* Better commandline parsing.

## 1.04
2019-12-13
* Added the ability to extract files via CLI with progress indicator.
* Removed reference to System.Net.Http.

## 1.03
2019-11-22
* Changed URL.

## 1.02
2019-10-26
* Fixed a bug where the validation of MASTER.DAT failed in such a way that if you selected CRITTER.DAT instead, the application accepted it as a valid MASTER.DAT.
* Minor UI tweaks.
* Better error handling.
* Proper versioning.
* Links to GitHub and [fodev.net](https://fodev.net).

## 1.01
2019-10-25
* .NET 4.0 as a runtime target for maximum compatibility with ancient Windows versions.
* Added a nicer icon than the default one provided by .NET.
* File containing list of files to extract is now named [undat_files.txt](../undat_files.txt)

## 1.0
* Initial release.
