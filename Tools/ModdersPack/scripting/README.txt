This folder contains documentation about sfall scripting extensions.

    headers\ - folder contains sfall headers that you should #include in your scripts
        sfall.h - main sfall header, always include it
        define_extra.h - some additional preprocessor constants for vanilla engine stuff (proto offsets, etc.)
        define_lite.h - a lite version of official define.h
        command_lite.h - a lite version of official command.h
        dik.h - DX scancodes constants for use with key_pressed function and HOOK_KEYPRESS
        lib.arrays.h - procedures that will help you use arrays in their full:
            - use them as stacks, sets
            - easily compare, copy, slice, cut, add arrays
            - display array contents (for debugging)
            - save/load two-dimensional arrays to savegame in one command (e.g. arrays of objects)
        lib.inven.h - fallout items manipulation functions
        lib.math.h - a few simple functions for calculations
        lib.strings.h - search in strings, join, repeat, etc.
        lib.misc.h - misc stuff

    sfall function notes.html - incomplete reference for new opcodes
    sfall opcode list.txt - list of all sfall opcodes (w/o descriptions)
    hookscripts.html - detailed manual for using hook scripts to modify engine behavior
    arrays.html - manual for sfall arrays

If you are/will be using sfall Script Editor, don't forget to check out new compiler documentation in .\compiler\sslc_readme.html.
There are numerious new syntax features and extensions to SSL (Star-Trek Scripting Language).
