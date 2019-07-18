sfall offers a couple of features for inspecting mods in game.

Firstly, set Enable=1 in the [Debugging] section in ddraw.ini to enable logging, and extract FalloutClient.exe to your Fallout directory. Exactly which types of messages are printed to the log can also be set in the [Debugging] section in ddraw.ini.

Secondly, when using the debug editor to inspect game variables, it searches for the files 'globals.txt' and 'critters.txt' in the Fallout base directory in order to get human readable names. The files included in this directory are for vanilla Fallout 2; you will have to create your own following the same syntax if you want human readable names in mods.

* The debug editor will also try to find the unpacked 'vault13.gam' file from the game to get the actual names instead of the names from the globals.txt file.
