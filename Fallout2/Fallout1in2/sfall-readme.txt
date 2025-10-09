sfall, a Fallout 2 engine tweak mod by Timeslip and many other contributors
version 4.4.8, built for Fallout 2 v1.02 US

Project Page on SourceForge: https://sourceforge.net/projects/sfall/
Code Repository on GitHub:   https://github.com/sfall-team/sfall
Additional materials at:     http://timeslip.users.sourceforge.net/

This was a quick Fallout mod which I originally stuck together to try and fix a few minor annoyances that I had with the games, but which then turned into a slightly bigger mod which fixed some other peoples annoyances and some of the bugs in the original Fallout engine too, and has since turned into a bloody huge mod with code contributions from a double figured number of people and with which modders could practically write a whole new game. The features are too numerous to list these days, so you'll have to read through the changelog instead.

This mod only works with a specific version of the Fallout 2 exe; the US copy of 1.02. Attempting to use this mod with an incompatible version of Fallout will result in an error when you try to run it. If your version of Fallout doesn't have kids, then you have the UK version instead of the US version, so you'll need to patch it into the US version before using this mod.

Using a D3D9 graphics mode obviously requires you to have DX9 installed and a DX9 compatible graphics card. sfall requires a recent DX9.0c update. (Specifically, the one that includes d3dx9_43.dll.) If you set the graphics mode to 4, 5, or 6 but don't have DX9.0c installed at all, Fallout will crash on startup. If you have a version of DX9.0c installed, but one which is older than the required one, Fallout will crash at the main menu. Please note that there have been several years worth of releases all labelled '9.0c', with little way of telling them apart aside from the release date. The versions of DirectX 10 and 11 included with Windows Vista and 7, as well as the versions of DirectX installed by games, do not always contain the most up to date DirectX 9 components, so even if you think you have DX9.0c already, run the web installer to check if you crash at the main menu.

The current version of sfall only works on Windows XP Service Pack 3 or later, and requires a processor with SSE support (Pentium III or Athlon XP or later). Versions up to 3.8.x are available for Windows 2000, and Windows 9x is no longer supported.

******************
** Installation **
******************

Extract 'ddraw.dll', 'ddraw.ini', 'sfall.dat', and the 'mods' folder to Fallout's base directory (i.e. the one that contains fallout2.exe). Also, remove gl_highlighting.int and gl_partycontrol.int from Fallout's data\scripts\ directory if you are updating from an older version.

IMPORTANT NOTE:
If you are using a mod that already included sfall (e.g. killap's Unofficial Patch or Restoration Project), then that mod has probably included a custom modified ddraw.ini. In that case, overwriting it with sfall's vanilla ddraw.ini will be likely break your game. Instead, only overwrite ddraw.dll, and keep the mod's existing copy of ddraw.ini. (Or, if you know what you're doing, you can merge them together by hand.)

The folder 'translations' contains translations of some of the strings that sfall displays in the game. To use a translation, copy this folder to Fallout's base directory too, and then in ddraw.ini change the 'TranslationsINI' setting to '.\translations\<your language>.ini'.

********************
** Uninstallation **
********************

Delete ddraw.dll, ddraw.ini, and sfall.dat from your Fallout directory, and delete sfall-mods.ini from the mods folder.

***********
** Usage **
***********

This mod is configured via the 'ddraw.ini' and 'sfall-mods.ini' files, which can be opened with any text editor. Details of every configurable option are included in those files. Where a comment refers to a DX scancode, the complete list of codes can be found at the link below:
https://kippykip.com/b3ddocs/commands/scancodes.htm

In a default installation using an unmodified copy of ddraw.ini, the middle mouse button will be set to switch between weapons and the mouse wheel will be set to scroll through any menus that respond to the up/down arrow keys. Holding Ctrl and hitting numpad keys 0 to 6 (with Num Lock off) will adjust the game speed. Holding left Ctrl will let you move items between inventory lists by simply clicking on them. Pressing left Shift will highlight items on the ground, and holding the key will let you move an entire stack of items at once. The script extender and any engine fixes are also enabled. Most of the options that change gameplay in some way not originally intended by the developers are disabled.

For Wine users:
You need to set DLL overrides for ddraw.dll to 'native, builtin' in winecfg or use WINEDLLOVERRIDES="ddraw=n,b" to run Fallout from the command line. If you want to play alternative sound files, you'll also need to install GStreamer Good 32-bit plugins.

******************
** Known issues **
******************

It is not possible to completely remove the Fallout 2 13 year time limit, because Fallout 2 stores the time passed since the start of the game in a 32-bit variable, and on the 8th of March 2255 this variable overflows, causing Fallout to crash. (Normally, the game will end on the 25th of July 2254) This mod does give you several options for removing the limit, but each option has its own set of side effects. If you are planning on powergaming, as well as setting the TimeLimit line to -3, I suggest setting the WorldMapTimeMod value to somewhere around 10, which will increase the amount of gameplay time you have between tickcount rollovers by an order of magnitude.

Starting from 4.2.2, sfall is not compatible with the experimental version of the hi-res patch v4.1.8 with zoom feature.

***************
** Changelog **
***************

v4.4.8
>HRP: Fixed a crash and a visual glitch in the interface bar at ultrawide resolutions
>HRP: Fixed splash screen display when the file is packed in an uncompressed .dat file
>Fixed incorrect mnemonic names in script dumps generated by the script decompiler (int2ssl.exe in the modders pack)
>Added a fix for a crash when an encounter between two groups fighting each other fails to spawn one group
>Added a fix to use the art\splash\ directory as the fallback for loading splash screens for non-English languages
>Added a fix for the game not applying the mouse sensitivity setting correctly in certain cases
>Added a fix for file seeking in uncompressed .dat files
>Added an option to disable the engine's processing of Arroyo-related events
>Added support for switching to alternate keyboard character codes (from Crafty)

v4.4.7
>Fixed potential undefined behavior in FullItemDescInBarter
>Fixed the behavior of 'break' statement in script compiler and decompiler (compile.exe and int2ssl.exe in the modders pack)
>Improved the fix for removing floating text messages on the map when moving to another map or elevation
>Improved the error handling for missing main .dat files
>Removed glass glare from the 'Use Inventory Item On' window to match other game interfaces
>Added a fix for a crash when a critter with a powered melee/unarmed weapon runs out of ammo and there is ammo nearby
>Added a fix to prevent a potential crash when using skills on non-critter objects
>Added a fix for the duplicate click sound for the 'Done' button in the 'Move Items' and 'Set Timer' windows
>Added a few fixes for slightly misaligned buttons in the pipboy, character screen, and barter screen
>Added missing sounds to the 'Done' and 'Cancel' buttons in the 'Custom' disposition of the combat control panel
>Added lowercase 'a' as a hotkey for the 'Take All' button (previously only uppercase 'A')

v4.4.6.1
>The compatibility mode check now targets only unsupported Windows versions
>Changed the way ProcessorIdle works to prevent conflicts with CPU_USAGE_FIX option in f2_res.ini
>Added a fix to prevent out-of-bounds selection in the file list when loading a character file
>Added a fix to remove visible newline control characters '\n' when examining items in the barter screen

v4.4.6
>Fixed a bug introduced in 4.3.1 that broke the debug message about a missing critter art file
>Fixed an issue where an item with a unique ID in the inventory had its ID reset by a non-unique item
>Restored the position of the ammo bar when ALTERNATE_AMMO_METRE=0 in f2_res.ini
>Improved the fix for the display issue in the pipboy when the automap list is too long
>Improved the compatibility mode check for newer Windows
>Changed PipBoyAvailableAtGameStart option and set_pipboy_available script function to no longer modify the vault suit movie state
>Added a fix for the main menu music not stopping when replaying the intro
>Added a fix for display issues when highlighting a multiline dialogue option
>Added a fix for the incorrect message being displayed when attempting to repair a dead robot
>Added a fix for the duplicate click sound when selecting a location in the Status section of the pipboy
>Added a fix for extra hidden buttons below the location list in the Status section of the pipboy
>Added a fix for map lighting from Night Vision perk not updating when loading a saved game
>Added a fix for an animation glitch when death animations and combat start simultaneously
>Added a fix to prevent the game from hanging when reloading a weapon overloaded with ammo via the interface bar
>Added a few fixes for issues related to weapons with negative ammo
>Added a tweak to replace death animations on critters with single-frame variants on map load
>Added more options for tweaking some engine perks to the perks ini file
>Reduced the green tone of the message window on the interface bar for text clarity

v4.4.5.1
>HRP: Fixed the behavior of IFACE_BAR_WIDTH for a modified fallout2.exe with Chinese/Japanese support
>Fixed a bug in XPTable that caused leveling issues with Here and Now perk
>Disabled unnecessary selfrun file creation in the recording mode (autoplay has been disabled in 4.3)

v4.4.5
>Fixed a bug introduced in 4.2.9 that caused game_loaded script function to always return 1 when called from normal scripts
>Fixed a bug introduced in 4.4.4 that caused the information card for the hero appearance mod not to refresh properly
>Fixed a crash bug in AutoSearchSFX when an ACM file has a name longer than 12 characters
>Fixed an issue where sfall did not reset data properly after attempting to load a corrupted saved game
>Fixed the inconsistent behavior of the escaped percent sign '%' in sprintf and string_format script functions
>Fixed show/hide_iface_tag script functions to prevent unnecessary toggling of tags
>Fixed using_skill script function returning garbage values when the arguments are not the player and Sneak skill
>Added a fix for the engine not checking 'misc' type items when correcting data for items on maps
>Added a fix to prevent the windows of Tag! and Mutate! perks from reappearing when there are still unused perks
>Added a tweak to restore the player's sneak state when switching between maps
>Added options to item highlighting mod to separately set the color of outlines for highlighted containers and corpses
>New hook script: hs_buildsfxweapon

v4.4.4
>Fixed a bug in NPCsTryToSpendExtraAP that caused NPCs to still be able to move in their combat turn after they killed themselves
>Fixed a bug in PlayIdleAnimOnReload that could cause critters to lose highlights after reloading weapons in combat
>Fixed a crash bug in interface_art_draw script function when drawing beyond window bounds
>Fixed the missing hotkeys for additional elevators derived from the original elevator types
>Fixed and improved the syntax parsing in script compiler (compile.exe in the modders pack)
>Improved the fix for using 'English' as the fallback language directory for msg files to work on a per-line basis
>Improved the fix for saving/loading party member protos to include the car trunk
>Improved the performance of draw_image, draw_image_scaled, and interface_art_draw script functions
>Expanded show/hide_iface_tag script functions to work with the tag value 0 (sneak)
>Changed the expanded world map interface to be compatible with older versions of the hi-res patch
>Changed the expanded action points bar to require fewer resources and be compatible with older versions of the hi-res patch
>Changed AIDrugUsePerfFix to be enabled by default
>Tweaked the behavior of NPCAutoLevel option and renamed it to PartyMemberNonRandomLevelUp to better match its behavior
>Removed the unnecessary error message about sndlist.lst when AutoSearchSFX is enabled
>Added a fix for the time interval for healing during world map travel being tied to the system timer instead of game time
>Added a fix for the interface bar obscuring the barter/trade interface when using the hi-res patch
>Added a tweak to prevent the 'forever' type of animation on objects from stopping when entering combat
>Added an option to use the expanded barter/trade interface (4 item slots per table instead of 3)
>Added an option to use the expanded inventory/loot screens (8 vertical slots instead of 6)
>Added an option to pre-fill the 'Move Items' window with the correct balancing amount when moving money/caps in the barter screen
>Added an option to set up a key to let you move items between inventory lists by simply clicking on them
>Added debug options to adjust the size and text font for the internal debug window
>Added an option for tweaking Cautious Nature perk to the perks ini file
>Added a new attribute type value to get_window_attribute script function
>Added PAUSEWIN flag to the game mode functions (when pausing the game using Ctrl+P)
>Added 2 new arguments to HOOK_ENCOUNTER hook script
>Added a healing skills example script to the example mods in the modders pack
>New script function: signal_close_game, art_frame_data, set_worldmap_heal_time

v4.4.3.1
>Fixed a possible hang or crash introduced in 4.4.1 when running certain script sequences

v4.4.3
>Fixed a bug introduced in 4.2.9 that caused critters with crippled arms to be unable to attack in certain cases
>Fixed the critical hit messages of the right arm and left leg for super mutants
>Fixed add_extra_msg_file script function to prevent it from loading the same msg file more than once
>Removed DisplaySwiftLearnerExp from ddraw.ini because there is little reason to turn it off
>Removed SpeedInterfaceCounterAnims=3. Now the AC counter is always instantly updated when switching to other controlled critters in combat
>Added a fix for the game disappearing from the taskbar after using Alt+Tab
>Added a fix for the clickability issue of the 'Use Inventory Item On' action when the selected item overlaps an object
>Added a fix for the xp exploit from canceling Here and Now perk when the player has Swift Learner perk
>Added support for loading an external DirectDraw wrapper (ddraw.dll) from the <GameRoot>\wrapper\ directory for rendering
>Added a static books mod and a molotov fire damage mod to the example mods in the modders pack

v4.4.2
>Fixed a bug in XPTable that could cause a hang when leveling up in some cases
>Fixed the critical hit messages of the right arm for some critter types
>Changed add_mult_objs_to_inven script function to allow adding more than 99999 instances of an object in one go
>Added a fix to use 'English' as the fallback language directory for loading credits.txt/quotes.txt
>Added a fix for gaining two levels at once when leveling up from level 97
>Added a fix for the modulo operator treating negative integers as unsigned
>Added a fix to prevent integer overflow for the number of items in a stack in the inventory
>Added a fix to COMBATDAMAGE hook to prevent instadeath critical hits for no damage
>New script function: reg_anim_animate_and_move

v4.4.1
>HRP: Fixed the clickability issue of the file list for save/load and 'print to file' options in the character screen
>Fixed a bug introduced in 4.4 that broke the interoperability of saved arrays with older versions
>Fixed a crash when calling start_gdialog outside the talk_p_proc procedure for talking heads
>Fixed create_object_sid script function to allow creating an object with no script correctly when passing 0 as the script index number
>Changed the calculation of the 'best armor' score to exclude the EMP stats (gameplay mod friendly)
>Tweaked the position of the ammo bar on the interface bar
>Removed AdditionalWeaponAnims from ddraw.ini. Now additional weapon animation codes are always available
>Updated NPC combat control mod to make the player's Jinxed trait/perk affect all controlled critters

v4.4.0.1
>Fixed a crash on startup on Windows XP/2003

v4.4
>Implemented a mods_order.txt to improve and simplify mod ordering and add support for mod managers. This replaces previous .dat file autoloading. Please refer to ddraw.ini for details
>Implemented a custom config file parser, which greatly improves the performance of sfall initialization and reading files from scripts
>Item highlighting and NPC combat control mods are now packed into sfall.dat resource file, and sfall-mods.ini is moved to <GameRoot>\mods\
>Fixed a bug when updating the maximum HP stat of critters on the map when loaded for the first time
>Fixed set_pc_base/extra_stat and set_critter_base/extra_stat script functions not updating derived stats when setting SPECIAL stats
>Fixed wield_obj_critter script function, which can now put non-weapon/armor items in the critter's hand
>Fixed get_tile_fid script function to work on elevations 1 and 2 instead of always elevation 0
>Fixed create_spatial script function not setting the script index number upon object creation
>Fixed incorrect behavior of the subtraction operator involving floats and negative integers
>Fixed the backward compatibility of get_npc_level script function
>Fixed a crash bug in display_msg and debug_msg script functions when printing a string longer than 260 characters
>Fixed a crash bug in AMMOCOST hook when returning ammo cost of 0 for burst attacks
>Fixed various issues in script compiler and decompiler (compile.exe and int2ssl.exe in the modders pack)
>Improved item highlighting mod to handle the line-of-sight check properly when the player is moving while holding down the key
>Improved and tweaked the behavior of ComputeSpray_* options
>Expanded atoi script function to support parsing binary strings
>Expanded string_format script function to support more arguments and conversion types
>Changed CheckWeaponAmmoCost to be enabled by default and affect only hook type 1 of HOOK_AMMOCOST hook script
>Changed how HOOK_DESCRIPTIONOBJ hook script handles its return value. Now you can return normal strings directly in the hook
>Re-added the check for valid objects to get/set_object_data script functions (only disabled in combat for accessing the combat data)
>Removed the debug message about a missing critter art file from displaying in the game (added in 4.2.2)
>Added options to override the names of sound files used by the engine
>Added an option to item highlighting mod to highlight critters with the same rules as in combat, and changed CheckLOS to be enabled by default
>Added a debug option to duplicate logs to a dedicated console window alongside the game window
>Added a lower limit of -99% and an upper limit of 999% to the hit chance value to prevent a display issue
>Added more options for tweaking some engine perks to the perks ini file
>Added a new argument and a new return value to HOOK_STEAL hook script
>Added a burst control example script and a resting encounters mod to the example mods in the modders pack
>Updated the compute damage example script in the modders pack. Now it should be easier to write one's own damage formula
>Increased the setting range of the combat speed slider in the preferences screen
>New script functions: set_spray_settings, get/set_combat_free_move, get_ini_config, string_find

v4.3.8
>Fixed a bug introduced in 4.2.8 that broke the arguments of HOOK_RESTTIMER hook script
>Fixed a bug introduced in 4.3.1 that caused the game to display incorrect names for corpses in some cases
>Fixed a crash bug in FullItemDescInBarter when a weapon/ammo has no item description
>Fixed create_object_sid script function not setting the script index number upon object creation
>Fixed the broken read_string script function
>Fixed the order of autoloaded .dat files on the FAT file system
>Changed the way disabled unsafe script functions work. Now they don't cause scripts to end abruptly
>Removed StackEmptyWeapons from ddraw.ini. Now unloaded weapons will always stack, no matter what type of ammo was loaded previously
>Removed CreditsAtBottom from ddraw.ini. Now sfall built-in credits are shown at the beginning when from the main menu and at the end during the ending
>Added a fix for the player's traits not being displayed on the character screen in certain cases
>Added a fix for incorrect death endings being shown under certain conditions
>Added a tweak to the ammo information in the inventory for Glovz's damage formula and Haenlomal's YAAM
>Added a tweak to allow premade characters to have less than two traits
>Added a tweak to INVENTORYMOVE hook for getting the amount of dropped money/caps
>Added support for closing the game by pressing Alt+F4

v4.3.7
>Dropped support for older pre-SSE processors in favor of more optimized code. Now sfall requires a processor with SSE support
>Fixed a bug that could prevent loading files from the art\<language>\ directory
>Fixed REMOVEINVENOBJ hook to match the values of RMOBJ_* constants correctly
>Fixed NPC combat control mod not setting the lighting of controlled critters correctly in some cases
>Expanded set_pipboy_available script function to match PipBoyAvailableAtGameStart option
>Expanded message_str_game script function to support editor.msg file
>Increased the default number of sound buffers available for sound effects from 4 to 8
>Changed the way AllowDShowSound works. Now mode 2 is combined with mode 1
>Removed MoreTiles from ddraw.ini. Now the maximum number of tile FRMs is always 16383

v4.3.6
>Minor code fixes and improvements to sfall and engine functions
>Fixed UseWalkDistance having no effect when trying to use a ladder
>Fixed float_msg script function not setting the purple or black text color correctly
>Changed mode 1 of NPC combat control mod to require sfall debugging mode to control all critters in combat
>Added a fix for NPC stuck in a loop of reloading the solar scorcher when out of ammo
>Added an option to NPC combat control mod to allow the player to gain a positive reputation while controlling other critters
>Added a boundary check to set_terrain_name script function
>New script function: get_terrain_name

v4.3.5
>HRP: Fixed movie subtitles not showing up when MOVIE_SIZE=1 with certain combinations of screen and movie aspect ratios
>HRP: Disabled IFACE_BAR_WIDTH and SCALE_BUTTONS_AND_TEXT_MENU for a modified fallout2.exe with Chinese/Japanese support to prevent garbled text
>HRP: Added support for SPLASH_SCRN_TIME option in f2_res.ini
>Fixed the handling of obsolete script functions that are still recognized by script compiler and decompiler
>Fixed NPC combat control mod not redrawing the interface bar properly when it's the player's turn again
>Improved the fix for updating the maximum HP stat of critters on the map when loaded for the first time
>Removed DivisionOperatorFix from ddraw.ini because there is little reason to turn it off
>Removed ComputeSprayMod from ddraw.ini. Now ComputeSpray_* options no longer require a master switch
>Added a fix for a crash when the player equips a weapon overloaded with ammo
>Added a fix for being able to use the 'Push' action on members of the player's team in combat when they are knocked down
>Added missing sounds to the markers on the world map interface (similar to Fallout 1, from Ghosthack)

v4.3.4
>HRP: Fixed a few issues with the main menu
>HRP: Added support for LocalMapXLimit/LocalMapYLimit options in ddraw.ini
>Removed FadeBackgroundMusic option because the fix in 4.3.3 doesn't work reliably in all cases
>Added a fix for being unable to plant items on non-biped critters with the 'Barter' flag set (e.g. Skynet and Goris)
>Updated the ammo ini loader mod in the modders pack

v4.3.3.1
>HRP: Fixed a possible crash in combat when enabling EXTRA_WIN_MSG_CHECKS
>HRP: Fixed broke console messages when enabling ConsoleOutputPath
>HRP: Fixed the main menu still being stretched when MAIN_MENU_SIZE=0
>Fixed a bug introduced in 4.3.1 that caused the game to print an incorrect item name in some cases
>Fixed screenshots for DX9 graphics modes. Now the screenshots are saved in PNG format when in DX9 mode
>Improved the functionality of AllowDShowMovies. Now you can take screenshots and press any key to skip AVI movies
>Added a tweak to prevent 'Failure initializing input devices' error for built-in HRP/DX9 windowed mode

v4.3.3
>Implemented an integrated High Resolution Patch mode, which has almost the same functionality as the original hi-res patch and has better integration with sfall's graphics features/improvements
>Fixed a bug introduced in 4.3.1 that broke the fix for party members with drug addictions
>Fixed a bug introduced in 4.3.1 that caused AI to be unable to use some weapons
>Fixed a bug introduced in 4.3.1 that caused the music not to be played after loading a saved game on the same map
>Fixed critical bugs in FadeBackgroundMusic that caused crashes in various situations
>Fixed incorrect display of name and damage values for unarmed attacks in the inventory in some cases
>Fixed the black screen issue in DX9 mode when returning to the game after using Alt+Tab
>Fixed the mouse cursor lag in the save/load game screens
>Fixed broken object descriptions for a modified fallout2.exe with Chinese/Japanese support
>Fixed and expanded the mouse drop area for the PC's and NPC's inventory on the barter screen
>Changed the 'Radiated' on the character screen to be highlighted in gray when the player still has an impending radiation effect
>Changed SkipCompatModeCheck to not require sfall debugging mode
>Removed UseCommandLine from ddraw.ini. Now sfall will always check command line arguments for another ini file
>Removed ArraysBehavior and RemoveWindowRounding from ddraw.ini because there is little reason to turn them off
>Removed SkipSizeCheck from ddraw.ini and the executable file size check from sfall
>Removed the dependency on d3dcompiler_43.dll for DX9 graphics modes
>Added a fix for incorrect value of the limit number of floating text messages
>Added a tweak to allow printing new floating text messages when their limit is exceeded
>Added a debug option to set up a key to toggle the display of the hex grid on the map on or off (like in the mapper)

v4.3.2
>Changed the fix for grave type containers in 4.3.1 to an option, to fix compatibility with existing grave scripts
>Changed OverrideArtCacheSize to set the art cache size to 261 instead of 256
>Changed Enable option in the [Speed] section to no longer affect SpeedMultiInitial
>Tweaked the window title bar for DX9 windowed mode
>Optimized the calculation process in Glovz's damage formula and Haenlomal's YAAM for burst attacks

v4.3.1
>Fixed the Jet addiction not being removed when using the antidote in some cases
>Fixed the key repeat delay and rate when enabling the game speed tweak
>Fixed a possible crash at the end of the playback of alternative sound files
>Fixed a rounding error in Glovz's damage formula
>Fixed and improved NPC combat control mod and the behavior of SpeedInterfaceCounterAnims=3
>Improved the rendering performance of DX9 graphics modes
>Improved and tweaked the page control in ExtraSaveSlots
>Changed the way AutoQuickSave works. Now it sets the number of pages used for quick saving
>Changed SingleCore to set processor affinity to the second processor core if available
>Changed HOOK_CANUSEWEAPON hook script to run for both the player and NPCs
>Excluded the walking animation from the debug message about a missing critter art file for stationary critters
>Excluded the animated colors from TravelMarkerColor (same as in 3.8.x)
>Removed unnecessary check on action points when AI reloads a weapon (added in 4.3)
>Removed AffectPlayback option because it's not practical
>Added a fix for a crash when opening a file with name containing a '%' character
>Added a fix to prevent the main menu music from stopping when entering the load game screen
>Added a fix to display the palette color with index 255 correctly in DX9 mode when using the hi-res patch
>Added a fix for grave type containers in the open state not executing the use_p_proc procedure
>Added a tweak to update unarmed attacks after leveling up
>Added a tweak to keep the selected attack mode for unarmed attacks when closing the inventory or when the combat ends
>Added a tweak to display the actual damage values of unarmed attacks in the inventory
>Added an option to enable fade effects for background music when stopping and starting the playback
>Added an option to automatically search for new SFX sound files at game startup
>Added a config file to change the requirements and effects of unarmed attacks
>Added a config file to change some engine parameters for the game mechanics
>Added the ability to continuously play the music when moving to another map that uses the same music
>Added the ability to set custom names for unarmed attacks in the inventory to TranslationsINI
>Added support for using the newline control character '\n' in the object description in pro_*.msg files
>Added support for the new 'Healing Item' flag to item protos. Now AI will also use items with this flag for healing in combat
>Added support for the new 'Cannot Use' flag to the misc flags of item objects. This flag makes a weapon object unusable in combat
>Added missing sounds to the buttons on the world map interface (similar to Fallout 1 behavior)
>Added 5 metarule3 macros for controlling the save slot with scripts to sfall.h in the modders pack
>New script functions: set_scr_name, obj_is_openable
>Updated NPC armor appearance mod in the modders pack to prevent NPCs from equipping 'unusable' weapons
>Included Brazilian Portuguese and Polish translation (from Felipefpl and Jaiden)

v4.3.0.2
>Fixed a bug introduced in 4.3 that caused a hang when opening the pipboy if the value of a quest location in quests.txt is less than 1500
>Fixed a bug introduced in 4.3 that caused a black screen after starting a new game without the hi-res patch
>Fixed a bug in INVENTORYMOVE hook that caused duplicate items when canceling moving an item into bag/backpack
>Updated French translation (from HawK-EyE)

v4.3.0.1
>Fixed a crash bug introduced in 4.3 with the fix for animation registration
>Fixed a bug in AIDrugUsePerfFix that could cause a hang in combat
>Fixed the extra check for friendly fire not working if the 'area_attack_mode' parameter in the AI packet is not set or set to no_pref
>Added a fix for chem_primary_desire values in party member AI packets not being saved and reset correctly

v4.3
>Fixed the original engine issues with being unable to register animations in certain situations in the game
>Fixed a crash bug introduced in 4.2.9 with the fix for the 'Leave' event procedure in AddRegionProc function
>Fixed a bug in ObjCanSeeObj_ShootThru_Fix that could cause a hang in some cases
>Fixed the check of the ammo cost for a shot in CheckWeaponAmmoCost
>Fixed set_critter_burst_disable script function, which now applies only to weapons with the burst attack as the secondary mode
>Fixed the error handling in create_object_sid script function to prevent a crash when the proto is missing
>Fixed METARULE_CURRENT_TOWN metarule function not returning the correct index of the current town at the start of a new game
>Fixed the auto-close containers mod for gravesites and not closing containers in some cases (in the modders pack)
>Fixed and improved the functionality of AllowLargeTiles
>Restored the functionality of obj_under_cursor script function for the movement cursor (changed in 4.2.9)
>Improved the hero appearance mod to be able to load the interface text from text\<language>\game\AppIface.msg
>Improved the functionality of TranslationsINI to also search for the ini file relative to the text\<language>\ directory
>Improved the 'order to attack' mode in NPC combat control mod. Now the target can only be assigned if the party member sees it
>Improved the fix for a duplicate obj_dude script being created when loading a saved game
>Rewrote the priority score calculation in AIBestWeaponFix, and changed the option to be enabled by default
>Changed FastShotFix to be disabled by default
>Removed DataLoadOrderPatch from ddraw.ini because there is little reason to turn it off
>Added a fix for the script attached to an object not being initialized properly upon object creation
>Added a fix to prevent the player name from being displayed at the bottom of the dialog review window when the text is longer than one screen
>Added a fix for the in-game quest list not being in the same order as in quests.txt
>Added a fix for multihex critters hitting themselves when they miss an attack with ranged weapons
>Added a fix for the placement of multihex critters in the player's party when entering a map or elevation
>Added a fix to the starting position of the player's marker on the world map when starting a new game
>Added a fix for AI not checking the safety of weapons based on the selected attack mode
>Added a fix for the incorrect check and AP cost when AI reloads a weapon
>Added a fix to AI behavior to prevent the use of healing drugs when not necessary
>Added a fix for the incorrect object type search when loading a game saved in combat mode
>Added a few fixes for issues with knocked out/down critters. Now the combat doesn't automatically end if the target is only knocked out
>Added a tweak to prevent NPC aggression when non-hostile NPCs accidentally hit the player or members of the player's team
>Added a tweak to play the 'magic hands' animation when using an item on an object. This also prevents a few issues with scripted animations not playing
>Added a tweak to remove the unspent skill points limit
>Added an option to disable the engine's special handling of city areas 45 and 46 when visiting Area 45
>Added a new value to AIDrugUsePerfFix to allow NPCs to use only the drugs listed in chem_primary_desire and healing drugs
>Added support for loading premade character GCD/BIO files from the premade\<language>\ directory for non-English languages
>Added support for loading fonts from the fonts\<language>\ directory for non-English languages
>Added a debug option to control messages relating to engine fixes in the debug log
>Added a debug message about a missing combat object
>Added a new argument to HOOK_CALCAPCOST hook script
>New script function: set_quest_failure_value
>New hook scripts: hs_bestweapon, hs_canuseweapon
>Updated NPC armor appearance mod to prevent NPCs from picking up and trying to equip disallowed weapons in combat
>sfall can now load a localized sfall_xx.dat resource file instead of the default sfall.dat

v4.2.9
>Fixed the critical hits from unaimed shots not matching the ones from aimed torso shots for some critter types
>Fixed the display issue in DX9 mode when returning to the game after using Alt+Tab in dialogue
>Fixed obj_under_cursor script function, which now returns 0 if the cursor is in movement mode
>Improved compatibility with some older DX9 graphics cards
>Changed intface_redraw script function with one argument to be able to redraw the specified interface window
>Changed HOOK_DESCRIPTIONOBJ hook script to run for all types of objects, not just the items
>Changed the filename of the debug editor to FalloutDebug.exe (in the modders pack)
>Excluded SFX sounds from the search for alternative formats
>Removed the tweak that adds the city name in the description for empty save slots (added in 4.2.7)
>Added a fix to update the maximum HP stat of critters on the map when loaded for the first time
>Added a fix to the poison/radiation-related engine functions when taking control of an NPC
>Added a fix to AI weapon switching when not having enough AP to make an attack. Now AI will try to change attack mode before deciding to switch weapon
>Added a fix for the carry weight penalty of the Small Frame trait not being applied to bonus Strength points
>Added a fix for the flags of non-door objects being set/unset when using obj_close/open script functions
>Added a fix for the 'Leave' event procedure in AddRegionProc function not being triggered when the cursor moves to a non-scripted window
>Added support for ACM files at 44.1 kHz sample rate
>Added stereo support for SFX and speech ACM files at 44.1 kHz sample rate
>Added support for panning SFX sounds and reduced the volume for objects located on a different elevation of the map
>Added more options for tweaking some engine perks to the perks ini file
>Added options for tweaking tag skills to the skills ini file
>Added an option about the behavior of maximum HP calculation to the stats ini file
>Added 3 new attribute type values to get_window_attribute script function
>Added additional universal opcodes sfall_func7 and sfall_func8 (compile.exe and int2ssl.exe in the modders pack are also updated)
>Added a new mode to NPC combat control mod that lets you use the command cursor to specify targets for party members to attack in combat
>Added an auto-close containers mod to the example mods in the modders pack
>Added snd2acm_fix.exe (snd2acm with a fix wrapper) to the modders pack for writing the correct sample rate and channel info from WAV files to ACM format
>New script functions: interface_overlay
>New hook scripts: hs_adjustpoison, hs_adjustrads, hs_rollcheck

v4.2.8.1
>Fixed a few minor bugs introduced in 4.2.8
>Added support for drawing PCX images to draw_image, draw_image_scaled, and interface_art_draw script functions
>New script function: win_fill_color
>Cleaned up define_lite.h and command_lite.h in the modders pack

v4.2.8
>Fixed a bug in ObjCanSeeObj_ShootThru_Fix that caused the source to be unable to see the target if it has the 'ShootTrhu' flag set
>Fixed the encounter messages still being limited to 50 entries per table when EncounterTableSize is set to greater than 50
>Fixed temporary arrays in scripts being cleared when flushing the keyboard buffer
>Fixed the broken Print() script function
>Improved the field of view check in ObjCanSeeObj_ShootThru_Fix
>Improved the functionality of GlobalShaderFile to be able to load multiple shader files
>Improved the performance of DX9 graphics modes
>Extended the upper limit of set_pickpocket_max and set_hit_chance_max script functions to 999
>Expanded get_window_attribute script function to support the automap interface window
>Removed the check for valid objects from get/set_object_data script functions to make them work with other structured data
>Removed KeepWeaponSelectMode and InterfaceDontMoveOnTop from ddraw.ini because there is little reason to turn them off
>Added a fix for the engine building the path to the central hex of a multihex object
>Added a fix for the flags of critters in the line of fire not being taken into account when calculating the hit chance penalty of ranged attacks
>Added a fix to the check for ranged weapons in the Fast Shot trait and FastShotFix
>Added a fix for the background image of the character portrait on the player's inventory screen
>Added the original Fallout 1 behavior of the Fast Shot trait to FastShotFix
>Added an option to enable linear texture filtering for DX9 graphics modes
>Added support for ACM audio file playback and volume control to soundplay script function
>Added support for transparent interface/script windows
>Added the ability to change the poison level for NPCs to poison and set_critter_stat script functions
>Added the ability for controlled critters to use Sneak skill in combat
>Added a volume control to reduce the volume for play_sfall_sound script function
>Added an argument to intface_redraw script function to redraw all interface windows
>Added a new argument to HOOK_TOHIT hook script
>Added a new argument to HOOK_COMBATDAMAGE hook script
>Added a new hook type to HOOK_WITHINPERCEPTION hook script (when AI determines whether it sees a potential target)
>Added two sharpen filter files as global shader examples to the modders pack
>New script functions: interface_art_draw, interface_print, combat_data
>Updated the ammo ini loader mod in the modders pack

v4.2.7
>Fixed the default values for Movie1 - Movie17 options
>Fixed the playback of additional movies defined in Movie18 - Movie32 options
>Fixed OverrideMusicDir=2 not overriding the music path properly
>Fixed incorrect Melee Damage stat value being displayed when BonusHtHDamageFix=1 and DisplayBonusDamage=0
>Fixed attack_complex script function not setting result flags correctly for the attacker and the target
>Fixed and improved SFX and speech playback for alternative sound files
>Fixed and improved the behavior of nested timer events in global scripts
>Improved the functionality of AllowDShowMovies: added volume control support and a new value to force AVI videos to fit the screen width, and fixed movie subtitles not showing up
>Changed AttackComplexFix to make attacker_results and target_results arguments work independently of each other
>Changed ObjCanSeeObj_ShootThru_Fix to allow critters to see through other critters and added a check for the direction the source is facing
>Changed the behavior of replacing FRM aliases for critters. Now FRM files from their aliases are taken only if the critter doesn't have its own files
>Added a fix for ANIM_charred_body/ANIM_charred_body_sf animations not being available to most appearances
>Added a fix to remove floating text messages on the map when moving to another map or elevation
>Added a fix for a visual glitch on the black edges of the map when the map borders for the hi-res patch are set smaller than the screen size
>Added a fix to prevent the execution of critter_p_proc and game events when playing movies
>Added a fix to prevent crashes and loading maps when the death animation causes the player to cross an exit grid
>Added a fix to limit the maximum distance for the knockback animation to 20 hexes
>Added a tweak to allow setting custom colors from the game palette for object outlines
>Added a tweak to add the city name in the description for empty save slots
>Added an option to use Fallout's normal text font for death screen subtitles
>Added a debug message about a corrupted proto file
>Added a function extension for vanilla metarule3 function and added set_horrigan_days and clear_keyboard_buffer macros to sfall.h in the modders pack
>Added DAM_PRESERVE_FLAGS flag to attack_complex script function to keep the existing result flags when setting new flags
>Updated the example global shader file in the modders pack
>Updated German and Russian translations

v4.2.6
>Fixed a hero appearance mod issue that caused the player's gender not to be reset properly when creating a new character
>Fixed a hero appearance mod issue that caused the player to lose some fire/electrical death animations
>Fixed a bug introduced in 4.2.3 that broke the PlayIdleAnimOnReload option
>Improved the pathfinding in the engine function when a multihex object is in the line of fire
>Improved the functionality of display_stats script function to also update player's stats on the character screen
>Improved the fix for incorrect positioning after exiting small/medium locations
>Removed AutoSearchPath from ddraw.ini. Now the directory for autoloading custom files is the fixed <GameRoot>\mods\
>Added a fix to prevent critters from overlapping other object tiles when moving to the retargeted tile
>Added a fix to prevent showing an empty perk selection window (crash when clicking on the empty perk list)
>Added a fix for NPC stuck in an animation loop in combat when trying to move close to a multihex critter
>Increased the maximum text width of the player name on the character screen
>New script functions: get_stat_max/min

v4.2.5.1
>Fixed the extra check for friendly fire treating non-critter objects as friendly critters
>Changed the debug message about a missing critter art file to be displayed in the game only when in sfall debugging mode

v4.2.5
>Fixed a bug introduced in 4.1.9 that could cause the combat to end automatically in some cases
>Fixed a bug introduced in 4.2 that caused AI to miscalculate the hit chance in determining whether to use secondary attacks if BodyHit_Torso and BodyHit_Torso_Uncalled modifiers were not equal
>Fixed a bug introduced in 4.2.3 that caused CorpseDeleteTime not to set the timer correctly
>Fixed a bug introduced in 4.2.4 that caused AllowDShowSound=2 not to work
>Fixed loot_obj script function not returning the correct object when switching to another corpse in the loot screen
>Fixed and improved the functionality of ReloadWeaponKey for using any non-weapon item
>Fixed and changed the behavior of GvarID option in the drugs ini file
>Improved the fix for items on the ground being obscured by a pool of blood after the corpse is removed
>Changed the priority of files in the AutoSearchPath folder to be higher than the PatchFileXX options
>Added a fix for AI skipping a target simply because its weapon is currently empty
>Added a fix for AI not always considering the safe distance when using grenades or rockets
>Added a fix to AI behavior for 'Snipe' distance preference (distance=snipe in AI.txt). Now the attacker will try to shoot the target instead of always running away from it at the beginning of the turn
>Added a fix to reduce friendly fire in burst attacks. Now there is an extra roll for AI to not use burst attacks if a friendly critter is in the line of fire
>Added a check for the weapon range and the AP cost when AI is choosing weapon attack modes
>Added a tweak to allow party members to keep their current target as one of the potential targets when choosing new targets at the beginning of their turn
>Added a tweak to the displayed message if the main target of a missed attack has the 'Flat' flag set

v4.2.4
>Fixed stuttering when playing AVI movies
>Fixed a crash when playing MVE movies in DX9 mode with the CPU doing the palette conversion and without the hi-res patch
>Fixed a crash when using older versions of the hi-res patch
>Fixed a possible crash or player's turn being skipped when returning to the game after using Alt+Tab in combat
>Fixed a bug introduced in 4.1.9 that could cause a hang when loading a saved game
>Fixed COMBATTURN hook not being triggered when loading a saved game in combat
>Fixed and improved the playback of alternative sound files
>Re-added TownMapHotkeysFix option to ddraw.ini for mod testing
>Changed play/stop_sfall_sound script functions to return/accept the ID number of the played sound instead of a raw pointer
>Changed the 'Radiated' on the character screen to be highlighted in red when player's stats are affected by radiation exposure
>Added a new 'fullscreen windowed' mode to DX9 graphics modes
>Added saving the position of the game window to ddraw.ini
>Added a fix for the player's money not being displayed in the dialog window after leaving the barter/combat control interface
>Added a fix for a crash or animation glitch of the critter in combat when an explosion from explosives and the AI attack animation are performed simultaneously
>Added a fix for the 'Fill_W' flag in worldmap.txt not uncovering all tiles to the left edge of the world map
>Added a fix for leaving the map after reloading a saved game if the player died on the world map from radiation
>Added a fix to prevent the player from dying if a stat is less than 1 when removing radiation effects
>Added a fix for the same effect message being displayed when removing radiation effects
>Added a fix for NPCs not fully reloading a weapon if it has an ammo capacity larger than one box of ammo
>Added an option to display messages about radiation for the active geiger counter
>Added an option to change the displayed message when you recover from the negative effects of radiation exposure
>Added a new value to AllowUnsafeScripting to disable the memory address check in unsafe script functions
>Added a new value of 3 to the 'mark_state' argument of mark_area_known script function to uncover locations without radius (Fallout 1 behavior)
>Added a new mode to play_sfall_sound script function

v4.2.3
>Fixed the timing of setting WORLDMAP, DIALOG, PIPBOY, INVENTORY, INTFACEUSE, and INTFACELOOT game mode flags
>Fixed the execution of the timer event in global scripts
>Fixed the palette and the movie playback in DX9 mode
>Improved the functionality of create_message_window script function to support the newline control character '\n'
>Removed TownMapHotkeysFix and DisplaySecondWeaponRange from ddraw.ini because there is little reason to turn them off
>Added a fix for duplicate critters being added to the list of potential targets for AI
>Added a fix for the playback of the speech sound file for the death screen being ended abruptly in some cases
>Added a fix for the barter button on the dialog window not animating until after leaving the barter screen
>Added a fix for the division operator treating negative integers as unsigned
>Added a fix for trying to loot corpses with the 'NoSteal' flag set
>Added an option to allow using the caret character '^' in dialog msg files to specify alternative text in dialogue based on the player's gender
>Added options to draw a dotted line while traveling on the world map (similar to Fallout 1, from Ghosthack)
>Added an option to display terrain types when hovering the cursor over the player's marker on the world map (from Ghosthack)
>Added a flashing icon to the Horrigan encounter and scripted force encounters by default
>Added new flags to force_encounter_with_flags script function
>Added a procedure and macros for comparing unsigned integers to lib.math.h in the modders pack
>Increased the maximum text width of the total weight display in the inventory
>New script functions: string_to_case, set_terrain_name, get_window_attribute, set_town_title, message_box, 'div' operator (unsigned integer division)
>New hook script: hs_encounter

v4.2.2
>Fixed GAMEMODECHANGE hook being triggered in dialog even when the game mode is not changed
>Fixed the return value of charcode script function for characters in the extended ASCII character set
>Fixed the return value of get_script script function
>Fixed and improved the functionality of substr script function
>Restored and fixed RemoveWindowRounding option that was removed in 4.1.2
>Improved the functionality of inventory_redraw script function
>Changed the way IniConfigFolder works. Now the game will search for ini files relative to the specified directory
>Changed the debug message about a missing critter art file to also be displayed in the game
>Code refactoring for various script functions
>Added a fix to prevent the player from moving when clicking on a script-created window and prevent the mouse cursor from being toggled when hovering over a hidden window
>Added a fix to prevent crashes when DebugMode is enabled and there is a '%' character in the printed message
>Added an option to load a global shader file at game startup and added an example global shader file to the modders pack
>Added support for executing the timed_event_p_proc procedure in global scripts
>Added SPECIAL flag to the game mode functions (when switching from dialog mode to barter mode, or a party member joins/leaves in the dialog screen)
>Added a new argument to HOOK_GAMEMODECHANGE hook script
>New game hook: HOOK_STDPROCEDURE_END, as an extension to HOOK_STDPROCEDURE hook script
>New script functions: add_g_timer_event, remove_timer_event, reg_anim_callback, get_sfall_arg_at, hide/show_window, set_window_flag, get_text_width, string_compare, string_format, objects_in_radius, tile_by_position
>New hook script: hs_targetobject

v4.2.1.1
>Fixed a crash bug introduced in 4.2.1 with the fix for corpses blocking line of fire

v4.2.1
>Fixed a bug in save_array script function that could corrupt sfallgv.sav when saving a new array under the same key
>Fixed a crash bug in PremadePaths when a name exceeds 11 characters
>Fixed move_obj_inven_to_obj/drop_obj script functions not removing the equipped armor properly for the player and party members
>Fixed inven_unwield script function not updating the active item button on the interface bar for the player
>Fixed art_change_fid_num script function not setting player's FID correctly when the hero appearance mod is enabled
>Fixed critter_add/rm_trait script functions ignoring the 'amount' argument. Note: pass negative amount values to critter_rm_trait to remove all ranks of the perk (vanilla behavior)
>Fixed the xp bonus set by set_swiftlearner_mod script function not being reset on game load
>Fixed the player name while controlling other critters
>Fixed NPC combat control mod not removing the inherited perks from controlled critters properly
>Improved the display of the car fuel gauge on the world map interface
>Improved the hero appearance mod to search for files in .dat files and folders simultaneously
>Improved HOOK_INVENWIELD hook script to run for the player and NPCs when removing equipped items, and added a new argument to it
>Expanded set_critter_stat script function to allow changing the base stats of STAT_unused and STAT_dmg_* for the player, and STAT_unused for other critters
>Changed AllowUnsafeScripting to not require sfall debugging mode
>Removed NPCStage6Fix and CorpseLineOfFireFix from ddraw.ini because there is little reason to turn them off
>Added a fix to prevent the player from equipping a weapon when the current appearance has no animation for it
>Added a fix to use 'English' as the fallback language directory for loading msg files
>Added a fix for party member's equipped weapon being placed in the incorrect item slot after leveling up
>Added a new value to AIBestWeaponFix to change the priority multiplier for having weapon perk to 3x (the original is 5x)
>Added a new flag to MainMenuFontColour to only change the font color of the Fallout/sfall version text
>Added optional options to enable modification sections for perks and traits to the perks ini file
>Added support for displaying AP cost up to 19 on the active item button on the interface bar
>Added a check for valid objects to get/set_object_data script functions
>Added a debug message about a missing critter art file to DebugMode
>New script functions: unwield_slot, add_trait, get_inven_ap_cost
>Updated NPC armor appearance mod and added an alternative npcarmor.ini for vanilla Fallout 2 (in the modders pack)

v4.2
>Fixed a bug in XPTable that prevented the player from reaching the highest specified level
>Fixed create_message_window script function to prevent it from creating multiple message windows
>Fixed obj_art_fid script function returning incorrect player's FID when the hero appearance mod is enabled
>Fixed a crash bug in message_str_game script function when passing a negative fileId value
>Fixed MainMenuFontColour not changing the font color of the copyright text on the main menu
>Fixed a hero appearance mod issue that caused the incorrect FRM to be displayed when opening bag/backpack in the inventory
>Fixed some arguments in BARTERPRICE hook when trading with a party member
>Fixed a crash bug introduced in 4.1.8 when calling game_time_advance in the map_exit_p_proc procedure with active explosives on the map
>Fixed some of sfall features that depend on the hi-res patch not working properly in some cases
>Fixed a bug introduced in 4.1.8 that broke the AllowLargeTiles option
>Fixed the AP cost display issue in NPC combat control mod
>Improved the functionality of add_extra_msg_file script function to use 'English' as the fallback language directory for loading msg files
>Changed the DAM_BACKWASH flag to be set for the attacker before calculating combat damage when taking self-damage from explosions
>Changed CorpseLineOfFireFix to be enabled by default
>Removed the dependency of Body_Torso from Body_Uncalled hit modifier, and re-added BodyHit_Torso to ddraw.ini. Now you can use set_bodypart_hit_modifier script function to set them individually
>Replaced the 'Take All' hotkey mod with an extended UI hotkeys mod in the modders pack
>Added a fix to prevent the car from being lost when entering a location via the Town/World button and then leaving on foot
>Added a fix for items on the ground being obscured by a pool of blood after the corpse is removed
>Added a fix for player's position if the entrance tile is blocked when entering a map
>Added a fix for the player stuck at 'climbing' frame after ladder climbing animation
>Added an option to change the path and filename of the critical table file
>Added an option to change the font color of the button text on the main menu
>Added an option to override the path location of all ini files used by scripts
>Added an option to change some of Fallout 2 engine functions to Fallout 1 behavior
>Added support for the new 'Energy Weapon' flag to weapon protos. This flag forces the weapon to use Energy Weapons skill regardless of its damage type
>Added options for tweaking some engine perks to the perks ini file
>Added a new flag to force_encounter_with_flags script function
>Added COUNTERWIN flag to the game mode functions (when moving multiple items or setting a timer)
>Added a new argument to HOOK_ADJUSTFID hook script
>Added a new argument to HOOK_BARTERPRICE hook script
>Added a compute damage example script to the modders pack
>Slightly increased the width of the car fuel gauge on the world map interface
>New script function: register_hook_proc_spec
>New hook script: hs_stdprocedure

v4.1.9.1
>Fixed the error handling for loading sfallgv.sav to improve backward compatibility with older saved games
>Fixed key_pressed script function not working in HOOK_KEYPRESS hook script
>Fixed a bug in NPC combat control that caused perks picked in combat to disappear after switching control to other critters
>Fixed a bug in NPC combat control that caused player's selected attack mode not to be saved
>Fixed the map elevation check in get/set_can_rest_on_map script functions
>Improved the functionality of add_extra_msg_file script function to allow automatically assigning numbers to msg files
>Changed DebugMode and HideObjIsNullMsg to not require sfall debugging mode
>Added an option to NPC combat control mod to let you set a list of perks to be inherited from the player

v4.1.9
>Fixed some scrolling bugs in WorldMapSlots option
>Fixed fade in/out of the screen in DX9 mode (partially)
>Fixed get/set_critter_base/extra_stat script functions not accepting a pointer to the player
>Fixed set_dude_obj script function not accepting a null argument
>Fixed a crash bug in COMBATTURN hook when loading a game saved in combat mode while controlling other critters
>Fixed a bug in NPC combat control mod that caused the last controlled critter to get player's combat xp
>Fixed the last procedure in a script being unable to be called through a variable containing its name as a string
>Fixed a bug introduced in 4.1.8 that caused the DAM_KNOCKED_DOWN flag not to be reset for knocked out party members when leaving a map
>Improved NPC combat control to keep the selected attack mode of the controlled critter
>Improved the functionality of the debug editor (in the modders pack)
>Improved the fix for 'NPC turns into a container' bug
>Changed DataLoadOrderPatch to be enabled by default
>Changed ItemCounterDefaultMax to not set the counter to maximum when in the barter screen
>Added a fix for the broken 'reserve movement' function
>Added a fix for the up/down button images on the world map interface
>Added a fix for the position of the destination marker for small/medium location circles when using the location list
>Added a fix for player's movement in combat being interrupted when trying to use objects with Bonus Move APs available
>Added a fix for the incorrect coordinates for small/medium location circles that the engine uses to highlight their sub-tiles
>Added a fix for visited tiles on the world map being darkened again when a location is added next to them
>Added a fix for Scout perk being taken into account when setting the visibility of locations with mark_area_known script function
>Added a fix for combat not ending automatically when there are no hostile critters
>Added a fix for critters/items on a map having duplicate object IDs
>Added a fix for knocked down critters not playing stand up animation when the combat ends
>Added a fix for dead NPCs reloading their weapons when the combat ends
>Added an option to use the expanded world map interface (requires the hi-res patch v4.1.8)
>Added an option to allow setting a directory for the game to automatically search and load custom .dat files
>Added an option to expand the number of action points displayed on the interface bar (requires the hi-res patch v4.1.8)
>Added an option to change the base value of the duration of the knockout effect
>Added a check for the DAM_KNOCKED_OUT flag to wield_obj_critter/inven_unwield script functions
>Added a new value to SkipOpeningMovies to also skip the splash screen
>Added a new 'combat ends normally' event to HOOK_COMBATTURN hook script
>Added a sfall.dat resource file, which contains the required files for various features
>New script functions: metarule_exist, add_extra_msg_file

v4.1.8.1
>Fixed a bug introduced in 4.1.4 that could crash the game when calling knockback modifier functions
>Improved compatibility with older processors (pre-SSE2)

v4.1.8
>Fixed broken get/mod_kill_counter script functions when ExtraKillTypes is enabled
>Fixed the argument value of dialogue_reaction script function
>Fixed getting perks and traits from the real dude_obj while controlling other critters
>Fixed the position of the items in active item slots after ending control of the critter
>Improved the fix for the removal of party member's corpse to prevent save file corruption. Now party member's corpse is removed in the same way as all other critter corpses
>Changed the engine functions for saving party member protos and removing the drug effects for NPC to be called after executing the map_exit_p_proc procedure
>Changed create_message_window script function to be available when other game interfaces are opened
>Removed DialogOptions9Lines from ddraw.ini because there is little reason to turn it off
>Removed LoadProtoMaxLimit from ddraw.ini. Now the proto limit is automatically increased when needed
>Added a fix for party member's stats being reset to the base level when their base protos with the read-only attribute set are placed in the proto\critters\ directory
>Added a fix for NPC stuck in a loop of picking up items in combat and the incorrect message being displayed when the NPC cannot pick up an item due to not enough space in the inventory
>Added a fix to allow fleeing NPC to use drugs
>Added a fix for AI not checking minimum HP properly for using stimpaks
>Added a fix for NPC stuck in fleeing mode when the hit chance of a target was too low
>Added a fix to prevent fake perks from being added to all controlled critters
>Added a missing option for testing AllowSoundForFloats to the [Debugging] section of ddraw.ini
>Added a new 'dropping item on the character portrait' event to HOOK_INVENTORYMOVE hook script
>Added an ammo ini loader mod to the example mods in the modders pack
>Slightly increased the maximum text width of the information card on the character screen
>New script functions: draw_image, draw_image_scaled, set_fake_perk/trait_npc, set_selectable_perk_npc, has_fake_perk/trait_npc

v4.1.7
>Implemented a critter individualization system. Each critter has its own independent base/bonus stats, separated from other critters sharing the same PID. Now set_critter_base/extra_stat script functions only set stats for a specific critter
>Fixed the argument numbering in error messages when validating arguments
>Fixed the weapon duplication bug in NPC combat control mod
>Fixed a bug in CheckWeaponAmmoCost that caused NPCs not to switch to other weapons when there is not enough ammo to shoot
>Fixed fake perks not stacking properly
>Fixed the position of the 32-bit talking heads when the game resolution is higher than 640x480
>Fixed a bug in item highlighting that caused items to be kept highlighted when picking them up while holding the highlight key
>Changed hero_select_win function to require an AppHeroWin.frm file (included in the modders pack) in the art\intrface\ directory
>Added a fix for unexplored areas being revealed on the automap when entering a map
>Added a fix for the overflow of the automap tables when the number of maps in maps.txt is more than 160
>Added a fix for a duplicate obj_dude script being created when loading a saved game
>Added a fix to prevent the reserved object IDs of the player and party members from being generated for other objects
>Added a fix for the display issue in the pipboy when the automap list is too long
>Added a fix for the start procedure not being called correctly if the required standard script procedure is missing (from Crafty)
>Added an option to disable the engine's special handling of map IDs 19 and 37 when entering those maps
>Added support for the new 'automap=yes/no' parameter to maps.txt. This parameter overrides the hardcoded values for displaying the map in the pipboy automaps for the first 160 maps
>Added a new 'picking up item' event to HOOK_INVENTORYMOVE hook script
>Added files for using 32-bit images for talking heads to the modders pack
>Improved the functionality of the debug editor (in the modders pack)
>Improved the functionality of Use32BitHeadGraphics to allow using 32-bit images without having to patch talking head FRM files
>The number of simultaneously displayed notification boxes now depends on the game resolution
>New script function: set_unique_id
>New hook script: hs_sneak

v4.1.6
>Fixed a crash bug introduced in 4.1.5 when using various inventory items while a books ini file is loaded
>Fixed the return value of has_skill script function for incorrect skill numbers
>Fixed the negative skill points of a skill not being taken into account when calculating the skill level
>Fixed incorrect skill point cost for negative skill levels when using a skills ini file
>Fixed the screen not returning to the player when moving a controlled critter to another map elevation
>Fixed some functionality issues of fake perks
>Fixed the broken get_perk_available script function
>Fixed the lighting of controlled critters in NPC combat control mod
>Fixed the return FID in NPC armor appearance mod (in the modders pack)
>Expanded get/inc_npc_level script functions to accept party member PIDs
>Removed MultiPatches from ddraw.ini. Now Fallout always loads multiple patch files at once
>Added a fix for the reserved item FRM being displayed in the top-left corner when in the loot/barter screens
>Added a fix for the active effects of drugs not being saved properly
>Added a fix for NPC stuck in a loop of reloading melee/unarmed weapons when out of ammo
>Added a fix for critters not being healed over time when entering a map with 'dead_bodies_age=No' set in maps.txt
>Added a fix for corpses being removed early after returning to the map
>Added a fix for the removal of party member's corpse. Now items in party member's inventory are not removed along with the corpse
>Added an option to change the timer for deleting corpses on a map after you leave
>Added an option to override the global variable number used to show the special death message of the Modoc toilet explosion
>Added a new [ExtraPatches] section to allow setting multiple custom paths for loading game data
>Added a config file to change some parameters for drugs and their addictions
>Added displaying the NPC's addictions on the character screen when controlled by the player
>Added the ability to add extra non-scripted perks to the perks ini file
>Added support for extra perks to has_fake_perk/get_perk_available script functions
>Added a new argument to HOOK_REMOVEINVENOBJ hook script
>New script functions: add_iface_tag, npc_engine_level_up, set_drugs_data
>Updated NPC combat control mod to be able to automatically set the number for the notification box

v4.1.5
Various bug fixes and features based on the work by Mr.Stalin:
>Fixed a hang on startup if there is an invalid character for SPECIAL stats in the skills ini file
>Fixed set_self function for use_obj_on_obj, attack, and attack_complex vanilla functions
>Fixed attack_complex script function still causing minimum damage to the target when the attacker misses
>Fixed critter_mod_skill script function taking a negative amount value as a positive
>Fixed a crash when calling use_obj/use_obj_on_obj without using set_self in global scripts
>Fixed pickup_obj, drop_obj, and use_obj script functions not working properly in some cases
>Fixed TimeLimit=-3 not returning the correct year, and removed the setting value of -2 (Now it works the same as -3)
>Fixed the mouse cursor lag on the world map when WorldMapFPSPatch is enabled
>Fixed issues with the game speed tweak. Now the game speed will be temporarily set to normal speed when in the inventory or dialogue, and it doesn't affect the endgame slideshow
>Fixed and improved the functionality of UseFileSystemOverride and fs_* script functions
>Improved the functionality of get/set_sfall_global script functions to print error messages to debug output if the name of sfall global variable is not 8 characters long
>Improved the error handling for saving/loading sfall data files in savegames
>Expanded abs math script function to support returning integers
>Added a fix for critters not attacking the player in combat when loading a game saved in combat mode
>Added a fix for player's turn being skipped when loading a game saved in combat mode
>Added an option to fix and repurpose the unused called_shot/num_attacks arguments of attack_complex script function
>Added an option to make the game speed tweak also affect the playback speed of MVE video files without an audio track
>Added a debug option to hide error messages in debug output when a null value is passed to the function as an object
>Increased the maximum number of books in BooksFile to 50
>New script function: art_cache_clear

v4.1.4.1
>Fixed a bug introduced in 4.1.4 that broke the calculation of the skill point cost for increasing skill levels (from Mr.Stalin)

v4.1.4
>Fixed a bug in NPC armor appearance mod (in the modders pack) that caused other critters to be unable to attack with weapons

Various bug fixes and features based on the work by Mr.Stalin:
>Fixed a crash bug when using sorting functions on an associative array
>Improved the functionality of ElevatorsFile to allow changing the FRM images of the elevator panel and creating new elevator types
>Expanded resize_array function to support sorting associative arrays by keys or values
>Expanded create/temp_array functions to allow creating a new 'lookup' type of associative array
>Changed INVENTORYMOVE hook to be called before displaying the 'Move Items' window for dragging and dropping ammo on weapons
>Added a fix to prevent sfall from trying to load global scripts with an extension that exceeds three characters (e.g. gl_test.int123)
>Added a fix to the following script functions to ensure they set the correct object: set_critter_burst_disable, set_critter_pickpocket_mod, set_critter_skill_mod, set_critter_hit_chance_mod, set_*_knockback
>Added a debug option to force sfall to search for global scripts every time the game loads rather than only the first time
>Added an option to change the distance at which the player will switch to walking when trying to use objects or pick up items
>New hook script: hs_setlighting

v4.1.3
>Changed PartyMemberExtraInfo to not show 'Addict' text (in dark green) on the combat control panel if the party member is not addicted to drugs
>Changed read_byte, read_short, read_int, and read_string script functions to not require AllowUnsafeScripting
>Changed AutoQuickSave to use the current selected page if AutoQuickSavePage is disabled

Various bug fixes and features based on the work by Mr.Stalin:
>Fixed a bug introduced in 4.1 that broke the return values of HOOK_FINDTARGET hook script
>Fixed the missing return value of -1 for HOOK_USEOBJON hook script
>Fixed the order of loading global scripts from multiple paths
>Fixed the return values of a hook getting corrupted if another hook was called during the execution of the current hook
>Fixed a bug in the hero appearance mod that caused the player to disappear after saving the game when player's base FID is greater than 255
>Changed how HOOK_FINDTARGET hook script handles its return values. Now you don't have to specify all 4 targets to override normal sorting
>Added a fix for being unable to sell/give items in the barter screen when the player/party member is overloaded
>Added a fix for AI still taking distance into account when calculating hit chance using the 'no_range' flag
>Added a fix for AI not taking chem_primary_desire in AI.txt as a preference list when using drugs in the inventory
>Added a fix to display a pop-up message box about death from radiation
>Added a fix to prevent hook scripts from being executed when the depth limit is exceeded, or the hook is called recursively
>Added a new value to SpeedInterfaceCounterAnims to update the AC counter instantly when switching to other controlled critters in combat
>New script functions: obj_under_cursor, loot_obj, get/set_object_data, get_object_ai_data
>New hook script: hs_subcombatdmg

v4.1.2
>Updated NPC combat control mod to work with BoxBarCount and prevent Marcus and non-biped critters from equipping armor when controlled by the player
>Updated item highlighting mod to be disabled while in the loot screen
>Changed the debug editor to require sfall debugging mode
>Removed RemoveWindowRounding option because it doesn't affect anything

Original engine bug fixes and various features based on the work by Crafty:
>Added a fix for Heave Ho! perk increasing Strength stat above 10 when determining the maximum range of thrown weapons
>Added an option to display party member's current level/AC/addict flag on the combat control panel
>Added a new value to DebugMode to send debug output to both the screen and debug.log
>Added a new return value to HOOK_KEYPRESS hook script to override the pressed key

Various bug fixes and features based on the work by Mr.Stalin:
>Fixed DX9 mode not showing movie subtitles properly when not using the hi-res patch
>Fixed DisplayBonusDamage not being applied to Melee Damage stat on the character screen when BonusHtHDamageFix is enabled
>Improved the functionality of ExtraSaveSlots: added sound effect when clicking on the navigation buttons
>Improved the functionality of StartGDialogFix to fix a crash when calling start_gdialog outside the talk_p_proc procedure for talking heads
>Added a fix for the exploit that allows you to gain excessive skill points from Tag! perk before leaving the character screen
>Added an option to change the limit of how many protos per type can be loaded into memory at once, and improved the functionality of set_proto_data script function to be able to automatically increase the limit when needed
>Added an option to skip the 'Move Items' window when taking items from containers or corpses and not holding down ItemFastMoveKey
>Added an option to skip loading game settings from saved games
>Added an option to fix the bug of using First Aid/Doctor skills when using them on the player
>Added 4 new modes to metarule2_explosions function
>New script functions: item_make_explosive, dialog_obj
>New hook scripts: hs_useskillon, hs_onexplosion

v4.1.1
Original engine bug fixes based on the work by Crafty:
>Added a fix for the encounter description being displayed in two lines instead of one
>Added a fix for the maximum text width of the player name in the inventory
>Added a fix for the 'mood' argument of start_gdialog script function being ignored for talking heads

Various bug fixes and features based on the work by Mr.Stalin:
>Fixed broken get/reset_critical_table script functions
>Improved the functionality of CritterInvSizeLimitMode and added party member's current/max inventory size info to the combat control panel
>Improved the functionality of AllowDShowSound: added volume control support and the ability to play alternative music files even if original ACM files are not present in the music folder, and fixed initialization crash bug when DX9 mode is disabled
>Added a fix for the underline position in the inventory display window when the item name is longer than one line
>Added a fix for AI being unable to use the picked up object immediately when there is a different object with the same ID
>Added an option to prevent the inventory/loot/automap interfaces from being placed on top of other script-created windows
>New script functions: get_current_inven_size, create_win, get/set_can_rest_on_map

v4.1
>Added an option to display experience points with the bonus from Swift Learner perk when gained from non-scripted situations (from Crafty)

Original engine bug fixes and various features based on the work by Mr.Stalin:
>Implemented a code injection system for game hooks. In previous versions, the code of game hooks was always executed even if there was no corresponding hook script. Now the code of a game hook is only injected into the game when the corresponding hook script exists
>Code refactoring for some hook scripts
>Fixed an issue where the file IDs of additional game msg files were shifted when a file in ExtraGameMsgFileList was missing
>Fixed obj_can_see_obj script function not checking if source and target objects are on the same elevation before calling HOOK_WITHINPERCEPTION hook script
>Improved the functionality of ExtraGameMsgFileList to allow manually assigning numbers to specific msg files
>Improved the functionality of HOOK_AMMOCOST hook script when CheckWeaponAmmoCost is enabled
>Improved and expanded the functionality of UseScrollingQuestsList to display page numbers and add another set of scroll buttons
>Expanded is_iface_tag_active script function to check tag values of 0/1/2 (sneak/poisoned/radiated)
>Added a fix for missing AC/DR mod stats when examining ammo in the barter screen
>Added a fix for the display issue in the pipboy when a quest list is too long with UseScrollingQuestsList disabled
>Added a fix for the clickability issue of the holodisk list in the pipboy
>Added a fix for the broken obj_can_hear_obj script function
>Added a fix for multihex critters moving too close and overlapping their targets in combat
>Added a fix for AI not checking weapon perks properly when choosing the best weapon
>Added an option to keep the selected attack mode when moving the weapon between active item slots
>Added an option to set the number of additional notification boxes to the interface
>Added an option to load alternative dialog msg and subtitle files for female PC (translation friendly)
>Added an option to display full item description for weapon/ammo in the barter screen
>Added options to change the location of quest list scroll buttons
>Added options to use more than one save slot for quick saving
>Added DIALOGVIEW flag to the game mode functions (when reviewing the current conversation)
>Added a new argument to HOOK_WITHINPERCEPTION hook script
>Added a new return value to HOOK_BARTERPRICE hook script to modify the value of player's goods
>New script functions: get_string_pointer, dialog_message
>New hook scripts: hs_useanimobj, hs_explosivetimer, hs_descriptionobj

v4.0.7
>Fixed the game thinking you dropped an active explosive when the dropping is prevented by HOOK_INVENTORYMOVE hook script (from Mr.Stalin)
>New script function: inventory_redraw (from Mr.Stalin)
>NPC combat control mod now centers the screen on the controlled critter and has new options to display critter's name

v4.0.6
>Fixed a crash bug introduced in 4.0.5 when calling various hooks

v4.0.5
>Added an option to use Fallout's normal text font instead of DOS-like font on the world map
>Added an option to increase the maximum number of tile FRMs (from Crafty)
>Added the ability to define allowed weapon animations for NPCs to NPC armor appearance mod (in the modders pack)

Original engine bug fixes and various features based on the work by Mr.Stalin:
>Added a fix for a crash when the critter goes through a door with animation triggers
>Added a fix for critters killed in combat by scripting still being able to move in their combat turn if the 'distance' parameter in their AI packets is set to stay_close/charge, or NPCsTryToSpendExtraAP is enabled
>Added support for adding custom background FRM to the character screen of the hero appearance mod
>Added an option to display the range of the secondary attack mode in the inventory when you switch weapon modes in active item slots
>Added an option to set up a key to let you move/drop a whole stack of items at once without the 'Move Items' window
>Added an option to change the counter in the 'Move Items' window to start with maximum number
>Added a new mode to metarule2_explosions function
>New script function: set_iface_tag_text
>New hook script: hs_gamemodechange
>Expanded get_mouse_buttons function to return a value for the middle mouse button
>Improved the functionality of hs_inventorymove and hs_invenwield

v4.0.4
>Fixed a broken functionality of ExtraSaveSlots option. Now sfall will remember the last selected save game slot. The position data is saved to/loaded from an auto-generated slotdat.ini in your savegame folder
>Fixed the last additional notification boxes to the interface being missing
>Fixed a bug in NPC combat control mod that caused Gecko Skinning to appear in the perk selection window
>Fixed a bug in item highlighting mod that caused items to be kept highlighted when entering combat while holding the highlight key
>Fixed the broken get_attack_type script function (from Mr.Stalin and Crafty)
>Added a fix for being at incorrect hex after map change when the exit hex in source map is at the same position as some exit hex in destination map (from Crafty)
>Added a math script function: floor2
>New script functions: set_ini_setting, lock_is_jammed, unjam_lock, set_unjam_locks_time, get/set_map_enter_position, set_rest_heal_time, set_rest_mode, attack_is_aimed (from Mr.Stalin)
>New hook scripts: hs_setglobalvar, hs_resttimer (from Mr.Stalin)

v4.0.3
>Fixed the broken ExtraGameMsgFileList option
>Fixed a bug in NPC combat control mod that increases the rank of Gecko Skinning perk when the combat ends
>Fixed add_mult_objs_to_inven script function adding only 500 instances of an object when the 'count' argument is over 99999
>Improved the fix for player's base EMP DR to make sure the value is set correctly
>Item highlighting mod now only highlights lootable corpses

v4.0.2
>Fixed sneak_success script function not checking if the player is currently sneaking
>Added a fix for player's base EMP DR not being properly initialized when creating a new character and then starting the game
>New script function: display_stats
>Improved the functionality of UseScrollWheel. Now you can scroll through items in the loot/barter screens, and text in the message window (from Crafty)

v4.0.1
>Fixed a crash bug in NPC combat control when trying to control a temporary party member that has no data in party.txt

v4.0
>The build environment is now Visual Studio 2015, and Win XP SP2 and Win 2000 are no longer supported
>Extensive code reorganizing/rewrite was made in the effort to tidy up sfall code base accumulated over the years and make it easier to read, understand, and extend. Main code was split into separate 'modules'. Code for interacting with Fallout 2 engine was moved and expanded to allow for engine manipulations without using too much Assembly code
>Fixed an issue where the game was rendered before the hero appearance mod was loaded
>Item highlighting mod is moved from sfall into a separate script (gl_highlighting.int) and extended with new options
>NPC combat control mod is moved from sfall into a separate script (gl_partycontrol.int)
>Related options of item highlighting and NPC combat control mods were moved from ddraw.ini into a separate sfall-mods.ini
>A new version of NPC armor appearance mod was implemented as a separate script (gl_npcarmor.int in the modders pack). It can be configured and made compatible with any Fallout 2 mod
>Improved compatibility between hero appearance, NPC combat control, and NPC armor appearance mods
>A bunch of hooks and script functions were added to allow implementing multiple vehicles in the game
>New script functions: item_weight, get/set_outline, get/set_flags, tile_refresh_display, outlined_object, set_dude_obj, real_dude_obj, get_ini_sections, get_ini_section, car_gas_amount, set_car_intface_art, get/set_cursor_mode
>New hook scripts: hs_adjustfid, hs_combatturn, hs_cartravel
>Added the ability to load global scripts from different paths
>Included Chinese and Russian translations

Original engine bug fixes and various features based on the work by Crafty:
>Added a fix for the exploit that Bonus Move APs are replenished when you save and load the game in combat
>Added a fix for the displayed message when the attack randomly hits a target that is not a critter and has a script attached
>Added a fix for damage_p_proc being called for misses if the target is not a critter
>Added a fix for the double damage effect of Silent Death perk not being applied to critical hits
>Implemented standard script procedures: combat_is_starting_p_proc (called when a combat starts, but doesn't mean that the critter is in combat) and combat_is_over_p_proc (called when the combat ends)
>Added INTFACEUSE, INTFACELOOT, BARTER, and HEROWIN flags to the game mode functions
>Added a new argument to HOOK_COMBATDAMAGE hook script
>Added an option to prevent the player from running while sneaking without Silent Running perk

v3.8.4
>Fixed a crash introduced in 3.8.3 when calling destroy_object or destroy_mult_objs
>Fixed a hero appearance mod issue that caused the race and style not to be loaded properly from savegames
>Added an option to set the color of outlines for highlighted items and containers

v3.8.3
>Fixed a crash when pressing reload weapon key while in the main menu
>Fixed metarule2_explosions not being reset properly
>Fixed global scripts not running on the world map when disabling the world map speed patch
>Fixed inconsistent behavior of motion sensor flag 2
>Added 3 new arguments to HOOK_TOHIT hook script
>Added a fix for the bag/backpack exploit that lets you keep items that are supposed to be removed from the inventory
>Added a fix for the original engine issue that caused Sequence stat value not to be printed correctly when using 'print to file' option
>Improved the functionality of ScrollMod
>Improved the functionality of ExplosionsEmitLight. Now it will check if an item was lit prior to being thrown/shot
>Changed SkipSizeCheck and ExtraCRC to not require sfall debugging mode
>Removed the obsolete WorldMapFPS, ForceLowResolutionTimer, and WorldMapDelay options

Original engine bug fixes and various features based on the work by Crafty:
>Added a fix for a crash when clicking on empty space in the inventory list opened by 'Use Inventory Item On' (backpack) action icon
>Added a fix for negative SPECIAL values in the character creation
>Added a fix for the game hanging in an endless loop in combat mode when calling anim script functions inside damage_p_proc
>Added 3 new arguments to HOOK_BARTERPRICE hook script

v3.8.2
>Fixed broken call_offset_* script functions
>Fixed OverrideMusicDir not using the correct path string
>Fixed a bug in metarule2_explosions function that caused damage type change not to work
>Fixed a crash when calling reg_anim_obj_run_to_tile after reg_anim_combat_check
>Changed sfallgv.sav to be loaded before other savegame files to make saved arrays available in the start procedure
>Changed BodyHit_Torso to BodyHit_Torso_Uncalled because it sets both body_torso and body_uncalled hit modifiers

Original engine bug fixes and various features based on the work by Crafty:
>Added a fix for display issues when calling gdialog_mod_barter with critters with no 'Barter' flag set
>Added a fix for the original engine issue that caused items to disappear from the inventory when you try to drag them to bag/backpack in the inventory list and are overloaded
>Added a fix for the original engine issue that caused the game not to check player's inventory properly when putting items into the bag/backpack in the hands
>Added a fix for the original engine issue that caused the current carry weight and the range of equipped weapons being lowered temporarily when opening bag/backpack
>Added a fix for a crash when trying to open bag/backpack on the table in the bartering interface
>Added the ability to move items from bag/backpack to the main inventory list by dragging them on the character portrait (similar to Fallout 1 behavior)
>Changed WorldMapEncounterFix/Rate to work independently of WorldMapFPSPatch

v3.8.1
>Fixed pressing F6 not displaying the Quick Save screen

v3.8
>Improved NPC combat control and fixed various issues with it
>Fixed bugs in set*_stat_min script functions that set max values instead of min
>Unified the style of global/hook script log entries
>Added new universal opcodes sfall_funcX that allow adding new script functions without changing script compiler and decompiler
>Added new script functions: spatial_radius, critter_inven_obj2, intface_redraw, intface_hide, intface_show, intface_is_hidden, exec_map_update_scripts

Original engine bug fixes and various features based on the work by Crafty:
>sfall can now load global/hook scripts from .dat files
>Improved the 'print to file' fix and added the ability to use long filenames in .dat files
>Improved the functionality of ProcessorIdle

v3.7.4
>Improved the functionality of DisableHorrigan to work on old saved games
>Replaced NumberPatchLoop with a simpler MultiPatches toggle
>Added a new value to PipBoyAvailableAtGameStart to make the pipboy available by only skipping the vault suit movie check
>Changed BodypartHitModX to BodyHit_(body parts) in ddraw.ini to make them easier to understand
>Removed BodyHit_Uncalled from ddraw.ini. Now body_torso and body_uncalled hit modifiers share the same value, and set_bodypart_hit_modifier script function is also tweaked to match the change
>Removed CarryWeightLimit option because it can be scripted with set_stat_max script function
>Removed GainStatPerkFix from ddraw.ini because there is little reason to turn it off

Original engine bug fixes and various features based on the work by Crafty:
>sfall now loads global/hook scripts, shaders, 32-bit talking head images, and AVI movies from master_patches path in fallout2.cfg instead of the fixed 'data\' directory
>Added a fix for the original engine issue that caused incorrect positioning after exiting small locations (e.g. Ghost Farm)
>Added an option to use a modified data load order for the engine to find game data

v3.7.3
>Changed the displayed version number to the same as the internal version number
>Added the ability to read additional game msg files, as opposed to dialog msg files (from Vennor)
>Added an option to display sfall built-in credits at the bottom of credits.txt contents instead of at the top

Original engine bug fixes and various features based on the work by Crafty:
>Fixed get_screen_width/height script functions not returning correct values when using the hi-res patch
>Fixed incorrect savegame path detection when reading/writing sfallgv.sav and sfallfs.sav under certain circumstances
>Improved the unlimited ammo exploit fix to prevent crashes with some faulty scripting
>Added a fix for the original engine issue that caused action points to be initialized incorrectly at the beginning of each turn, thus giving a hidden bonus to your opponent's armor class and reducing your hit chance
>Added a fix for destroy_p_proc not being called if the critter is killed by explosives when you leave the map
>Added a fix for incorrect death animations being used when killing critters with kill_critter_type script function
>Added a fix for the original engine issue that caused Fallout to check the horizontal position on the y-axis instead of x when setting coordinates on the world map
>Changed the way SpeedInterfaceCounterAnims=2 works. Now it updates the HP/AC counters instantly in all cases
>Added an option to display numbered dialogue options

v3.7b
>Fixed broken sfall_ver_* script functions
>Fixed potential undefined behavior and crashes in sfall arrays (from Vennor)
>Optimized some code to make the compiled DLLs about 10 KB smaller in size
>Switched to using the precomputed CRC table instead of creating the CRC table at runtime. This could potentially improve startup time in emulated or partially emulated environments (from Oppen)
>Added rounding calculation to ComputeSprayMod for a more balanced bullet distribution in burst attacks
>Re-added CarChargingFix option to ddraw.ini for mods that have custom vehicles
>Removed MultiHexPathingFix from ddraw.ini because there is little reason to turn it off

Original engine bug fixes and various features based on the work by Crafty:
>Fixed a crash bug introduced with the inventory drag and drop fix
>Added a new value to SpeedInterfaceCounterAnims to update the HP/AC counters instantly when the number is not negative
>Added an option to skip weapon equip/unequip animations when performing various actions
>Added an option to control the speed of pipboy alarm clock animations
>Added an option to change the carry weight limit

v3.7a
>Partially refactored all the source code to use proper engine function/variable names
>Removed a few options from ddraw.ini that should never be turned off

Original engine bug fixes and various features based on the work by Crafty:
>Added a fix for being unable to sell used geiger counters or stealth boys
>Added a fix for not counting in the weight of equipped items on NPC when stealing or bartering
>Added a fix for only using one box of ammo when reloading a weapon above the ammo in the inventory list by drag and drop
>Added an option to remove the ability to enter unvisited areas on a town map by hitting number keys
>Added an option to leave the music playing in dialogue with talking heads
>Added an option to skip the 'Move Items' window when using drap and drop to reload weapons in the inventory

v3.7
>Fixed incorrect bonuses on AC and Melee Damage from the Heavy Handed trait when using perks.ini
>New hook script: hs_invenwield (when causing a critter to wield/unwield an armor or a weapon)
>Expanded message_str_game script function to support all pro_*.msg files as well
>ExtraCRC can now accept multiple CRC values
>Merged sfall debugging features into the normal version, thus removing the need of a separate debugging version for modders
>Removed the obsolete Jim's damage formula
>Removed a few options from ddraw.ini that should never be turned off

Original engine bug fixes and various features based on the work by Crafty:
>Fixed SpeedInterfaceCounterAnims not displaying the correct negative value when HP drops below zero
>Rewrote the Sharpshooter perk fix to match its description correctly
>Rewrote the dodgy door fix to apply to both melee and ranged attacks
>Added a fix for a crash when leaving the map while waiting for someone to die of a super stimpak overdose
>Added a fix for the original engine issue that caused party members to have incorrect stats when they level up while on drugs
>Added a fix for the unlimited ammo exploit
>Added a fix for negative values in Skilldex window
>Added a fix for the clickability issue in the pipboy and an exploit that allows resting in restricted areas
>Added a fix to prevent 'Too Many Items' bug from corrupting save files
>Added a fix for the exploit that you can gain stats from more than two doses of a specific chem after save/load
>Added a fix for the original engine issues with reverse order of items in memory relative to visual order in the inventory list
>Added a fix for the original engine issue that caused party members to be able to unequip multiple of the same armor and reduce their stats to below the proper values
>Added a fix for the original engine issues that caused the game not to check NPC's addictions properly and the Jet Antidote not to work on NPCs
>Added a fix for the maximum text width of the item weight (Wt.) in party member trading window
>Added a fix for the original engine issue that caused NPCs to become unresponsive and act like walking containers if you move to another map while they are under 'lost next turn' critical miss effect
>Added a fix for the original engine issues with being able to charge the car by using cells on other scenery/critters, and cells getting consumed even when the car is already fully charged
>Added an option to stack empty identical weapons, no matter what type of ammo was loaded previously
>Added an option to highlight containers as well as items
>Added an option to allow 9 options (lines of text) to be displayed correctly in the dialog window
>Added an option to display additional points of damage from Bonus HtH/Ranged Damage perks in the inventory

v3.6
>Fixed a bug in books.ini handling that caused not all books to be loaded
>Fixed several different minor bugs that may theoretically cause unstable crashes
>Changed the way get_script function works: now returns a proper scriptID (line number in scripts.lst)
>Fixed set_script function to make it accept a proper scriptID, execute map_enter_p_proc by default, and create proper script types for the given object
>Fixed set_self function again (hopefully)
>Fixed AllowUnsafeScripting not being in the [Debugging] section of ddraw.ini

>Unified and changed how all sfall scripts are initialized. Exported procedures, scripted UI event handlers, named events (and maybe some other stuff) will finally work properly in all hs_ and gl_ scripts
>Slight change to when sfall resets state for all its components. Previously it happened after the game was loaded from a save, now it will happen before actually loading. This prevents a few nasty bugs
>Added safechecks to some script functions so the game won't crash if object argument is 0
>Expanded set_self function so you can access object script's local variables from another script
>HOOK_WITHINPERCEPTION hook script can now override the blocking check in obj_can_see_obj script function
>New script functions: obj_blocking_line, obj_blocking_tile, tile_get_objs, party_member_list, path_find_to, create_spatial, art_exists, obj_is_carrying_obj
>list_* functions can now return spatial scripts as well, so you can delete them if you want
>New hook script: hs_inventorymove (when moving objects around in the inventory screen)
>Added more arguments and return values to HOOK_COMBATDAMAGE hook script, so you can now implement your own damage formula entirely in a script

>Rewrote NPC combat control from scratch, with many bug fixes and improvements
>Rewrote CorpseLineOfFireFix to fix the conflict with TOHIT hook and the bug that corpse in the same hex as target still absorbs bullets
>Added an option to set up a key to reload your currently equipped weapon
>Added an option to skip the executable file size check
>Moved FalloutClient.exe to the modders pack

v3.5
>The build environment is reverted to Visual Studio 2010. The project itself still can be compiled with Visual Studio 2012/2013
>Added options to control the speed of combat/dialogue panel animations (from Tehnokrat)
>Added an error message (with sfx) when sfall cannot create sfallgv.sav file during saving the game
>sfall globals are now removed from savegame when setting them to zero (0) for a cleaner save file
>Array-related code refactoring and bug fixing
>Changed how save/load_array functions work when key is 0
>Added special cases for array_resize operator to perform efficient array sorting, reversing and shuffling (lists only)
>Added the ability to resize or clear maps (arrays)
>Zero values are now saved when using associative array expressions (assigning zero to existing array still removes corresponding element from array)
>Fixed the offset for the exported procedure patch
>You can now export variables from global/hook scripts and import them into any other scripts, no longer have to use set_sfall_global or arrays passing values between global/hook and other scripts
>Code refactoring for hook scripts. Now there is no limitation as to where you put the start procedure in global/hook scripts
>Added a new and better way to use hook scripts - register_hook_proc function will tie a sfall hook to a given procedure in the current script
>New script functions: charcode, message_str_game, sneak_success, tile_light
>Added some math script functions: ^ operator, log, exponent, ceil, round
>New hook scripts: hs_keypress, hs_mouseclick, hs_useskill, hs_steal, hs_withinperception
>Added the ability to use virtual key codes in the keypress hook script and key_pressed script function
>HOOK_CALCAPCOST hook script is now called for all misc items in hands as well as weapons
>HOOK_USEOBJON hook script is now also called when the player or AI uses any drug
>Fixed bugs in pickpocket script functions that max and mod values were not initialized and not reset on game load
>AP counter on the interface bar is now redrawn when using set_critter_current_ap on dude_obj
>Fixed a minor bug in the sprintf script function
>Rewrote code related to set_self script function, and fixed many vanilla opcodes not working from sfall scripts (roll_vs_skill, do_check, etc.)

v3.4
>Added a fix for the obj_can_see_obj script function (from Mash)
>Re-added Windows 2000 support
>Code refactoring, and all rest of the changes are from phobos2077
>Added options to modify the bullet distribution in burst attacks
>Added an option to make explosions and projectiles emit light
>Added options to change explosives damage
>Fixed unstable problems in the string_split script function
>Added options to change Hakunin movie timers
>New script functions: substr, strlen, sprintf, typeof
>atoi can now parse hex and octal strings properly into integers
>Rewrote sfall arrays to provide more flexible, safe and powerful tools
>Added 7 new reg_anim_* script functions to manipulate animations further
>New hook scripts: hs_ammocost, hs_useobj
>Added an option to add proper checks for weapons that use multiple ammo per shot
>More control over the critter_dmg script function
>Added a new 'metarule2_explosions' function to change various aspects of explosions in combat
>Added a config file to reassign or add books
>Fixed incorrect key_pressed statuses for most keys
>The map_*_p_proc procedures are now executed for global scripts in mode 0 and 3
>Fixed incorrect behavior of op_negate, op_mult, and op_div involving floats and negative integers
>Fixed the imported procedure patch, which was applied at the wrong offsets

v3.3
>A new ammo patch (from JimTheDinosaur)
>Added new script functions: gdialog_get_barter_mod, tile_under_cursor, set_inven_ap_cost
>Added an option to restrict inventory weight limit to active items only
>Added an option to modify inventory AP cost
>Fixes to Glovz's ammo patch (from Glovz)
>Fixed melee/unarmed losing their str dependence when using a skills ini file
>Fixed the set_perk_freq function, which I seem to have broken at some point
>Fixed the broken third return value for the afterhitroll script

v3.2
>The build environment is now Visual Studio 2012. The required D3DX9 version is increased, and Win XP SP2 and Win 2000 are no longer supported
>Fixed potential corruption of PC's age, gender, or current HP/poison/rads when using perks.ini
>Re-added NPC combat control
>Changed the way mode 1 global scripts work, to fix compatibility with the latest hi-res patch
>Fixes to Glovz's ammo patch

v3.1
>Fixed folding of constant float expressions in sfall script editors optimizer
>Fixed the active_hand and set_pickpocket_max script functions
>Added a fix for a crash when killing critters with explosives

v3.0
>Added get/set_critter_skill_points, get/set_available_skill_points, mod_skill_points_per_level, set_perk_freq, get_last_attacker, get_last_target and block_combat script functions
>Added a fix for the super stimpak exploit
>Added config options to control skill costs
>Fixed in_world_map script function potentially returning an incorrect value
>Fixed force_aimed_shots and disable_aimed_shots corrupting behaviour of other weapons
>Fixed potential problem with the modified_ini script function
>Fixed the missing last argument of the AP cost hook script
>Fixed appearance of version info in Windows (from NovaRain)
>When using DX9 graphics, GPUBlt is enabled automatically if supported
>When using DX9 graphics, resolution is changed automatically when using the hi-res patch
>Removed upscaling filter support
>Removed ddraw.ini defined global shader
>Removed multiplayer
>Removed the update check

v2.20a
>Fixes for sfall bugs in critical hits against Horrigan and the player
>Update check is now disabled by default

v2.19a
>Added options to move the main menu buttons and credit text
>Fixed a bug in the default heal rate formula when modifying stat relationships

v2.18a
>Added an option to disable the pipboy alarm
>Hero appearance mod bug fixes (from Mash)

v2.17b
>Fixed a crash bug introduced with motion scanners

v2.17a
>Added an option to adjust the behaviour of the motion scanner
>Added an option to increase the maximum number of slots in encounter tables
>Added new script function: get_npc_level
>Fixed removal of hardcoded effects for the skilled trait

v2.16a
>Added new script functions: force_aimed_shots, disable_aimed_shots, mark_movie_played
>Added a config file to change the SPECIAL/derived stat relationships
>Added an option to limit inventory by space as well as weight
>Improved the compatibility mode check

v2.15a
>Added the ability to adjust skill/stat relationship
>Added an option to add stat/skill effects to traits via config files
>Fixed an issue with doors being able to dodge bullets (from Mash)
>Added an option to increase the maximum number of named scripts

v2.14a
>Added a method of creating critical tables for new critter types
>Added a new option to block all saving in combat (off by default)

v2.13b
>A fix for hero appearance mod breakage in 2.13a (from Mash)

v2.13a
>Fixed a virtual file system bug
>Hero appearance mod fixes and improvements (from Mash)
>Two alternate fixes to the interaction between HtH attacks and the Fast Shot trait (one from Haenlomal)

v2.12a
>New script function: set_sfall_arg
>Added a fix for the original engine issue that could cause Fallout to look for the music in the wrong folder
>Added a fix for the original engine issue that prevented melee NPCs from attacking multihex critters (from Haenlomal)
>Added an option to allow party members to reach level 6 (from Haenlomal)
>Added an option to change the font colour on the main menu
>More bug fixes for Glovz's mod
>More flexibility for the 32-bit talking heads
>key_pressed now accepts values from 256 to 263 to report on the status of up to 8 mouse buttons (from NVShacker)
>Fix the rcpres variable in shaders containing two copies of 1/screen width
>Fixed an sfall bug that broke critical hits when starting a new game, up until a game was first reloaded
>Limited the scrollable quest window to prevent crashes from multiline quests (from Haenlomal)

v2.11a
>Added an option to remove the critical hit/miss limits in the first few days of game time
>Added an option to use 32-bit images for talking heads
>Fixed the original engine issue that resulted in the Jet Antidote not being consumed (from Haenlomal)
>Fixed the original engine issues with the wield_obj_critter script function (from Haenlomal)
>Fixed the original engine issue that caused the critical hit bonuses from special unarmed attacks not to be applied correctly (from Haenlomal)
>Fixed the sfall bug that made the Jinxed trait rather more potent than it should have been
>Fixed an issue with the karma image override that caused it to leak out to other panels
>Fixed a hero appearance mod issue that caused the wrong FRM to be displayed when opening a bag in the inventory (from Mash)
>Fixed a bug in Glovz's damage mod

v2.10b
>Fix a crash bug in Haenlomal's HtH damage fix

v2.10a
>A fix for the original engine bug that caused Bonus HtH Damage not to be applied correctly (from Haenlomal)
>New script function: get_sfall_args
>A new hook script hs_itemdamage
>A fix for one possible cause of the cannot create input device error (Thanks to mjurgilas for the hint)
>An option to increase the cap on maximum number of map animations to 127 (from Mash)
>Moved DontDeleteProtos to the [Debugging] section of ddraw.ini

v2.9c
>A hero appearance mod fix (from Mash)
>A new version of Glovz's ammo patch (from, umm, Glovz...)

v2.9b
>Fix a mixup with the hs_hex[type]blocking which resulted in using the shoot blocking rule for a sight test
>Last of the ddraw.ini cleanup

v2.9a
>New script functions: scan_array, get_tile_fid, modified_ini
>New hook scripts: hs_movecost, hs_hex[type]blocking
>Fixed a crash bug in get_game_mode
>Some more ddraw.ini cleanup

v2.8c
>Added the ability to add additional notification boxes to the interface
>Some more ddraw.ini cleanup
>Fixed critical hits against the player being broken when overriding the critical hit table

v2.8b
>new script functions: atoi, atof
>Moved SkipCompatModeCheck to the [Debugging] section of ddraw.ini
>Removed a few options from ddraw.ini that should never be turned off
>Added an option to apply bug fixes to the critical table without having to supply an ini (Values from killap)
>Fixed the broken return value from hs_barterprice

v2.8a
>New script functions: len_array, resize_array, temp_array, fix_array, string_split, list_as_array
>New hook scripts: hs_removeinvenobj, hs_barterprice
>Added an option to adjust the rotation rate of the critter FRM in the inventory/new char screens (from Mash)
>the list_xxx functions can now list over scenery, walls and misc objects
>A new ammo mod (from Haenlomal)
>Fixed a crash bug in get_uptime
>Moved ExtraCRC and AllowUnsafeScripting into the [Debugging] section of ddraw.ini

v2.7a
>Added an option to make the karma image on the character screen dependent on your current karma
>Added support for using wma, mp3 or wav files for sound, and new looping script functions
>Added array support in scripts
>Added an option to allow the use of the science/repair skills on critters
>Some debug editor improvements (array and critter editing support)
>updater improvements to prevent the crashes that happened during SourceForge's maintenance downtime from reoccurring

v2.6c
>More appearance mod bugfixes (from Mash)
>Fixed a crash when restoring the Fallout window while using graphics mode 4

v2.6b
>Fixed a bug in the hero appearance mod that broke player sfx (from Mash)

v2.6a
>New script function: set_map_time_multi
>Added option to speed up the spinning interface counter animations
>Debug editor now has access to sfall globals, and can show the names of globals and critters
>Fixed a nasty memory corruption bug in hook scripts
>Added an option to increase the number of save slots (from Mash)
>Added improved logging capabilities

v2.5b
>Fixed a crash bug in the hero appearance mod (from Mash)

v2.5a
>Appearance mod improvements (from Mash)
>Added a debug editor that lets you make changes to various values while in game
>The combatdamage hook script can now get the targeted bodypart

v2.4a
>New script function: force_encounter_with_flags
>Added an option to save the console contents to a file
>get/set_sfall_global can now optionally take an int instead of a string
>The limit of 1024 sfall globals has been removed
>sfall globals are now far faster if many are in use at once

v2.3a
>Added the ability to attach voice clips to floating text displayed in combat
>Added an option to override the hardcoded city reputations list
>New script function: get_attack_type
>Added a fix for the original engine issue that could prevent NPC levelling with some party combinations
>Fixed reentrency problems in hook scripts
>Fixed the delay loading of D3DX, which became broken when I switched to the newer DirectX SDK
>Removed the trait_adjust_* hook scripts, which were causing unfixable script corruption

v2.2b
>New script function: refresh_pc_art (from Mash)
>Appearance mod fixes and tweaks (from Mash)
>create_message_window tweaks (from Helios)
>Fixed CRC check checking the size of the wrong file when launching Fallout from a shortcut

v2.2a
>Added the ability to control premade characters, and add additional ones
>Switched to using a CRC check to make sure that sfall is being used with the correct Fallout exe
>The multiplayer server is now functional, and the client is included
>New script function: get_light_level
>Two new hook scripts: hs_adjustskill and hs_adjuststat
>Included German and French translations (from Mr.Wolna and Ardent)

v2.1a
>Some elements of sfall can now be translated
>Added a check-for-updates option
>Added an option to allow scrolling of quest lists in the pipboy (from Ray)
>Removed EAX support
>Removed Win9x support
>Removed the block on Steam, and the timeout code

v2.0d
>Modified the trait override code to not run if the perks.ini is not present
>Another attempt at fixing the explorer hang

v2.0c
>You can now edit traits via perks.ini as well as perks
>New script function: remove_trait
>Fixed sfall title display when using the hi-res patch
>Updated hero appearance mod (from Mash)

v2.0b
>The control party members option now behaves slightly better
>The mouse position functions now return the hotspot rather than the upper left corner of the cursor
>Fixed something I broke while adding in Helios's code

v2.0a
>Added new hook scripts hs_findtarget and hs_useobjon
>Added an option to skip the opening movies
>Made a fix to the line of fire fix
>Added an option to give NPCs a second chance to spend left over AP at the end of their combat turn
>Added new script functions to manipulate weapon ammo
>Added an option to allow the use of tiles larger than 80x36
>Added an option to directly control party members in combat (buggy)
>Multiplayer support (buggier)
>New script function: write_string
>Added an option to replace the mouse cursor used when using skills (from Helios)
>Added new window related script functions (from Helios)

v1.49d
>Fixed issue with global scripts not running on the world map when using the new world map speed patch
>Fixed issue with item highlighting only working on the first elevation of each map

v1.49c
>Hero appearance mod behaviour changes to fix some conflicts with patch dats and sfall saving (from Mash)

v1.49b
>Fixed some parts of the hero appearance mod still running even if disabled in the ini

v1.49a
>Added Hero appearance mod code from Mash
>Extra argument to hook script hs_combatdamage to get the weapon used in the attack
>Fixed set_script bug when used with critters
>New script function: set_critter_burst_disable

v1.48a
>Altered numbering scheme to avoid bug in unicode version of Windows
>sfall now displays its version number on the title menu
>Display an appropriate message and quit when used with Steam
>Fixed very nasty bug when saving with a patch file loaded
>Added new script functions to get the current sfall version

v1.47b
>New script functions: list_begin, list_next and list_end
>Fixed an issue if a global script tried to register_hook a hook that already had a hs_* script attached
>Fixed an issue with using register_hook across reloads

v1.47
>New script functions: set_proto_data, set_self, register_hook
>Further file system script functions
>Hook script changes to aid in mod compatibility; multiple scripts can now attach to one hook point

v1.46b
>New script function: get_proto_data

v1.46
>13 new script functions related to a virtual filesystem
>Added a new hook script hs_ondeath
>Added a new option 'GPUBlt' to speed up rendering in DX9 graphics modes by 3-4x
>Using graphics mode 4 or 5 with an out of date version of DirectX now displays a useful error message instead of crashing

v1.45b
>Added an option to prevent Fallout from hogging the processor
>Fixed get_script still returning a script after calling remove_script
>set_script can now be used on objects that are already scripted

v1.45
>Added a new hook script, hs_combatdamage
>Added 3 new script functions: remove_script, set_script and get_script
>Fixed the vanilla Fallout bug where an instadeath critical hit for no damage wouldn't run the critter death function
>Fixed issue with the initialization function of most hook scripts not being rerun on player reload
>Added an extra check to try and fix WorldMapFPSPatch crashes

v1.44c
>Added an option to reverse the left and right mouse buttons for left handed players

v1.44b
>Added an option to set up a key to toggle highlighting of items on the ground
>Fixed issue with death anim hook scripts crashing on some NPCs
>Fixed fake traits/perks not being removed if picked and then canceled

v1.44
>Added two new hook scripts to allow scripting of death animations

v1.43b
>Added an option to play the player's idle animation on weapon reload
>Added a fix for corpses absorbing weapons fire

v1.43
>Added an option to display karma changes
>Added new world map speed patch (from Ray)
>Added shiv item code fix (from Kanhef)
>Added fix for imported procedures with arguments (from KLIMaka)
>Added an option to always reload msg files (from Ray)

v1.42
>Added some math script functions: sqrt, abs, sin, cos, tan, arctan
>New script function: set_palette
>New hook script: hs_calcapcost

v1.41c
>Added an option to load multiple patch files at once (from Ray)

v1.41b
>New script function: get_ini_string
>New hook script: hs_afterhitroll

v1.41
>Added new script functions for modifying the critical hit table, AP/AC bonus and to support hook scripts
>Added an option to override the default critical hit table
>Added hook scripts. (Only one atm, to override the hit percentage chance modifier)

v1.40
>Added 2 new script functions: get_bodypart_hit_modifier and set_bodypart_hit_modifier
>New options in the ini file to set the initial bodypart hit modifiers

v1.39
>Added 3 new script functions: show_iface_tag, hide_iface_tag and is_iface_tag_active
>Added an option to fix the crash caused by withdrawal effects without an associated description

v1.38
>Added an ini option to skip the compatibility mode check
>Added 11 new script functions for performing generic memory writes and function calls
>Added new script function: set_hp_per_level_mod

v1.37
>Added support for adding additional movies (max of 32)
>In DX9 mode, AVI movies will be used in preference to .mve's if they exist
>Weapon animation codes 11 and 15 now correspond to file paths of 's' and 't' respectively
>Weapon animation codes greater than 15 are no longer allowed
>Fixed another possible hang on startup problem on Win9x

v1.36
>Added an option to increase the number of sound buffers available for sound effects
>Added an option to stop Fallout from deleting non read-only protos
>Fixed compatibility with v1.7 of the resolution patch when using graphics mode 5 or 6

v1.35d
>Fixed a crash bug with thrown weapons introduced in 1.33

v1.35c
>Fixed issues with negative hit chances
>Increased the number of new animation slots
>Trying to set a custom xp table caused a hang on startup with the Win9x version

v1.35b
>Fixed player not being able to increase skills

v1.35
>Added an option to set a custom xp table and level cap
>Added the ability to add new weapon animation types
>Fixed a possible issue with fake perks on Win9x

v1.34c
>Fixed a bug introduced in 1.33 that caused skills with negative percentages to wrap around
>Fixed elevators again

v1.34b
>Fixed an issue with adding additional elevators

v1.34
>Added an option to define a key to allow you to move the window in graphics mode 5
>Added experimental support for adding additional elevators and modifying old ones

v1.33c
>Fixed a compilation error in the Win XP version that broke compatibility with older processors

v1.33b
>Added some extra script functions to modify some of the vanilla perks

v1.33
>8 new script functions related to adding new perks
>6 new script functions to allow critter specific modifications to skill caps, stealing and combat hit chances

v1.32
>New script functions: set_fake_trait and set_fake_perk

v1.31b
>Fixed some get_game_mode issues
>A further slight speed increase in DX9 mode

v1.31
>Improved fps in DX9 mode
>Add a 'combat save' fix that prevents saving in combat if you have spent any ap
>Removed the Bonus Move fix, which was unfixably buggy, in favour of the combat save fix

v1.30
>Fixed movies in DX9 mode
>The compatibility mode check will now ignore the disable themes, turn off advanced text services and run as administrator settings
>Added new script functions: set_pc_stat_min, set_pc_stat_max, set_npc_stat_min, set_npc_stat_max

v1.29d
>Added a fix for the print to file crash caused by Fallout's inability to handle long filenames

v1.29c
>Expanded set_stat_max to work on most of the derived stats
>Added new script functions: set_stat_min, set_car_current_town

v1.29b
>A fix to the ammo damage tweak (from Glovz)
>Added new script function: set_stat_max

v1.29
>Added SKILLDEX, INVENTORY and AUTOMAP flags to the game mode functions
>set_shader_mode now lets you set a list of excluded and required loops simultaneously
>Added new script function: get_uptime

v1.28c
>Glovz fixed a bug in his AP ammo mod

v1.28b
>World map speed timer will revert to the normal timer if the high performance timer is low resolution
>Reduced the art cache size override setting

v1.28
>Added a fix for the Skilldex button vanishing if you have many active quests and holodisks
>Added a fix for the gain xxx perks not giving all the bonuses that they should (Will only affect new games)
>Updated the AP ammo mod (from Glovz)
>Hopefully fixed the issues with quickload
>sfall will display an error if you try running the Win XP version in Win 9x compatibility mode
>Added an option to override the art cache size, to fix F2RP EPA crashes without modifying fallout2.cfg
>Added new script functions: get_shader_texture, set_shader_texture

v1.27
>Added an override console option to fit more text into the console at high resolutions (Not finished!)
>Added a fix for saving/loading in combat with the Bonus Move perk
>Added an option to automatically set processor affinity to a single core
>sfall functions which expect a string as a parameter now accept variables as well as constants
>Global scripts set to run only on the local map no longer stop running in combat
>Improved the behaviour of set_shader_mode
>Added new script functions: get_game_mode, force_graphics_refresh

v1.26
>Global script modes 2 or 3 no longer require the world map speed patch to be active to work
>Added new script functions: get_ini_setting, set_shader_mode, get_shader_version
>Graphics mode 0 was broken in the Win XP version of 1.25

v1.25
>Added the city limits patch
>You can now use hardware shaders in DX9 mode when using Mash's resolution patch. Software scalers will not be supported
>Added new script functions: set_xp_mod, set_perk_level_mod
>Graphics modes 1, 2 and 3 are no longer supported

v1.24b
>Tweaked DX9 mode to be compatible with Mash's resolution patch (Warning: Using very high resolutions in DX9 mode will be _slow_)

v1.24
>Added options for setting starting world map position and world map viewport
>Added new script functions: get_viewport_x, get_viewport_y, set_viewport_x, set_viewport_y

v1.23
>Added an option to remove the random element from NPC levelling
>Added a new script function inc_npc_level

v1.22b
>EAX environment can be set on a per map basis via an eax.ini file
>Tweaked the way the disable Horrigan encounter option works (Now only affects new games)

v1.22
>Added EAX support
>2 new script functions: eax_available, set_eax_environment
>Bug fixes to save/load/new game hooks (Most visible result is that global scripts no longer run on the main menu)

v1.21
>Added six new script functions: set_sfall_global, get_sfall_global_int, get_sfall_global_float, set_pickpocket_max, set_hit_chance_max and set_skill_max

v1.20c
>Fixed a crash if you set the height greater than the width using scale filter 6
>Fixed a crash bug in the combat_p_proc fix when critter_dmg was called (from Ray)

v1.20b
>The global shader can declare a variable called rcpres which will receive the reciprocal screen resolution
>All shaders can load up to 128 textures (e.g. add the lines 'string texname1="filename.bmp";' and 'texture tex1;' to load a texture from data\art\stex\filename.bmp)
>Two new ScaleFilter modes

v1.20
>Added an option to disable the Horrigan encounter
>Added two new script functions set_global_script_type and available_global_script_types
>Added two additional execution modes for global scripts
>combat_p_proc fix (from Ray)
>Added an alternative damage calculation formula. (from Glovz)

v1.19b
>Fixed a crash introduced in 1.19a when gaining two levels at once

v1.19
>Tweaks to the way perks work when the script extender is being used: If you go more than 3 levels without visiting the character screen, you no longer loose your perk
>set_perk_owed now accepts values up to 250, so you can give the player multiple perks in one go
>Updated the ammo patch (from Glovz)

v1.18f
>get_perk_owed will now return 1 as soon as the player levels up, rather than only after they have visted the character screen

v1.18e
>Added an option to modify the encounter rate
>Make use of a higher resolution counter for world map fps counting if one is available
>More bugfixes

v1.18b
>Added an option to make world map encounters independent of world map travel speed (from Ray, from www.teamx.ru)
>Some bug fixes

v1.18
>Added an option to remove the ability to escape dialogue by hitting 0 (from Ray, from www.teamx.ru)
>Added new script functions: get_active_hand, toggle_active_hand, set_weapon_knockback, set_target_knockback, set_attacker_knockback, remove_weapon_knockback, remove_target_knockback, remove_attacker_knockback

v1.17c
>Made the world map speed patch independent of processor speed

v1.17b
>Fixed some of the filter stuff that I managed to screw up...

v1.17
>Added an option to use Glovz's AP ammo patch
>Added some upscaling filters (from Dream, from www.fallout.ru)
>Fixed ForceEncounter preventing the encounter with Horrigan if it was used to soon

v1.16d
>Added new script functions: get/set_critter_current_ap
>Modified world map speed setting to work on copies of the Fallout exe's without the speed patch already applied

v1.16c
>Added new script functions: get_perk_owed, set_perk_owed, get_perk_available
>Fixed a bug in get_kill_counter function
>Fixed a few bugs introduced in 1.16b

v1.16b
>Added an option to double the number of available kill types
>Some performance tweaks

v1.16
>Added new script functions: get_kill_counter, mod_kill_counter

v1.15
>Global scripts are now also loaded when the player starts a new game, instead of only when an existing game is loaded
>Added an option to enable the pipboy on game start
>Added a set_pipboy_available script function

v1.14
>Added the ability to modify perks
>19 new set_perk_xxx functions to modify perks in-game

v1.13c
>You can now change the limit on how far away from the player local maps can be scrolled

v1.13b
>Added the option to change the starting day/month/year
>Fixed a 1.13 bug which broke female players

v1.13
>You can now change the start and default player models
>You can now change the hardcoded in-game movies
>Added new script functions: set_dm_model, set_df_model, set_movie_path
>If you use the fallout2.exe included with killaps patch, sfall will no longer complain about an unsupported exe if you use the Sharpshooter fix

v1.12b
>Added new script functions: get_world_map_x_pos, get_world_map_y_pos, set_world_map_pos

v1.12
>You can change the number of locations displayed in the locations list of the world map
>A fix for the bug that could cause the world map locations list to become unresponsive
>You can tell Fallout to use a patch file other than patch000.dat
>You can change the version string that appears in the bottom right of the main menu
>You can use command line arguments to tell sfall to use an ini file other than ddraw.ini

v1.11b
>Fixed a possible crash related to trying to load global scripts that don't actually exist

v1.11
>Added the ability to tell Fallout 2 to use a config file other than fallout2.cfg
>Shaders now have access to the system tick count. (Create a non-static variable called 'tickcount')
>If using a DX9 mode, you can set up a key to toggle the global shader, and control when the shader gets used
>Added new script functions: in_world_map, force_encounter, set_shader_int, set_shader_float, set_shader_vector

v1.10b
>Fixed a couple of issues with the DX9 graphics modes
>sfall no longer tries to load global scripts if you have the script extender turned off

v1.10
>Added an option to display debug messages in Fallout, or to print them to a debug.log file
>Added the ability to create global scripts. (Scripts that run independently of the loaded map, and are not attached to any object)
>Added new script functions: set_global_script_repeat, input_funcs_available, key_pressed
>When using a DX9 graphics mode with a non 640x480 resolution and with multiple shaders running, the screen is no longer distorted

v1.9c
>Fixed a mistake in ddraw.ini's default settings

v1.9b
>Fixed possible lock-up bug when using graphics mode 4 or 5

v1.9
>If you use sfall with a version of fallout2.exe that it wasn't built for, you get a useful error instead of the generic 'requires DirectX 3a' message
>If using a 16-bit colour mode, you can alter the speed of fades
>Added some extra graphics modes that use D3D9 for rendering instead of ddraw
>Can change the initial map to load when starting a new game
>Added some extra script functions. (game_loaded, graphics_funcs_available, load_shader, free_shader, activate_shader, deactivate_shader)

v1.8
>If using the Pathfinder fix, you can modify how fast game time moves when travelling across the world map
>If using an exe with the world map speed tweak applied, you can change how fast you physically move across the map
>Added a new script function (get_year)
>Fixed a bug when setting TimeLimit=-3 that could cause crashes before reaching the 13 year limit

v1.7
>Added a fix for the Pathfinder perk
>Added a new and improved fix for the 13 year time limit, that no longer results in the date wrapping around
>Added a new script function (tap_key)
>You can now set a key to toggle the speed tweak on or off

v1.6d
>Added some extra script functions. (get_critter_base_stat, get_critter_extra_stat, set_critter_base_stat and set_critter_extra_stat)
>Fixed parameter checking bug with set_pc_base_stat and set_pc_extra_stat
>get_pc_base_stat and get_pc_extra_stat now return 0 if an invalid stat ID is given

v1.6c
>Fixed bug with get_pc_base_stat and get_pc_extra_stat returning incorrect values

v1.6b
>Added some extra script functions. (get_pc_base_stat, get_pc_extra_stat, set_pc_base_stat and set_pc_extra_stat)

v1.6
>Added an option to reduce mouse sensitivity below Fallout's normal minimum
>Added the option to use a 16-bit colour mode in Fallout 2. (Windowed 16-bit is a lot faster than windowed 8-bit)
>Added the Sharpshoot perk perception fix for Fallout 2
>Made a few extra functions available to scripts. (read_byte, read_short, read_int and read_string)

v1.5c
>More bugfixes to the time limit adjuster

v1.5b
>Slight bugfix to the time limit adjuster

v1.5
>Added an option to adjust the 13 year time limit in Fallout 2
>Added an option to set the initial speed at game startup

v1.4
>Restructured source code so that it's easier to add support for different exe versions
>Created a new dll for the v1.2 US version of Fallout 1

v1.3
>Added an option to bind the middle mouse button to a keyboard key. ('c' by default)
>Added a frameskip option when running in windowed mode
>Fallout's DirectInput device is now used to control speed changes and any other keyboard input this mod requires, because GetAsyncKeyState is unreliable when DInput is in use
>Added an option to force DirectInput into background mode
>The mouse wheel scroll modifier can now be set to 0 to always scroll one click regardless of mouse and windows settings (This is the new default.)

v1.2
>The whole gameplay speed section of the mod can now be disabled, while still allowing windowed mode
>Added an option to let you use the mouse scroll wheel to scroll through your inventory and save menu

v1.1
>You no longer need to hex-edit fallout2.exe in order to get this mod working
>You can now edit the controls in ddraw.ini
>Added an additional option to run Fallout in windowed mode

*************
** Credits **
*************

ravachol    For the old Sharpshooter perk fix
Noid        For the debug patch
Glovz       For the AP ammo patch
Dream       For the upscaling filter code
Ray/Alray   For the active hand and dialogue fix memory addresses, the encounter rate patch,
              the combat_p_proc fix and the load multiple patch files option, and more
Kanhef      For the shiv item code address
KLIMaka     For the imported procedure fix
Mash        For the hero appearance mod and the extra save game slots
Helios      For the Skilldex mouse cursor patch and a bunch of script functions
Haenlomal   For another ammo patch, and lots of other stuff (See the changelog)
phobos2077  For the code refactoring, array improvements, and many other changes since 3.4
Tehnokrat   For the combat/dialogue panel animations memory addresses
Crafty      For lots of engine bug fixes and new features since 3.7
Slider2k    For the new Sharpshooter perk fix proposal
Vennor      For the array bug fixes and the additional game msg files
Oppen       For the precomputed CRC table
Mr.Stalin   For various bug fixes and new features since 4.0.4
Ghosthack   For the base code of Fallout 1 style world map features
