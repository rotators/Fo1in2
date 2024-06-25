FALLOUT ET TU
-------------
Fallout to Fallout 2 engine conversion


Fallout et tu (also called Fallout 1@2, 1at2, 1in2, ...) is bringing the first Fallout game into the engine of the second one while utilizing features available in Fallout 2 wherever we can (within reason).

---

Discussion
- https://nma-fallout.com/threads/218045/ (release, beta)
- https://nma-fallout.com/threads/217892/ (alpha)
- https://nma-fallout.com/threads/179809/ (legacy)

Repository
- https://github.com/rotators/Fo1in2/


MOD INSTALLATION
----------------

- Install FALLOUT 1 anywhere.
  - The game is **REQUIRED** to play the Fallout 1 in 2 engine conversion!

- Install FALLOUT 2 anywhere.
  - The game is **REQUIRED** to play the Fallout 1 in 2 engine conversion!

- Unpack FALLOUT ET TU into your Fallout 2 folder.
  - The folder structure must look like this:
    ```
    \Fallout2\Fallout1in2\Fallout2.exe
    ```

- Start the `UNDAT.EXE` and select the `MASTER.DAT` file from your FALLOUT 1 installation directory.
  - If you are using a (pre)release package, `UNDAT.EXE` can be found in the `Fallout1in2` folder.
  - If you are using the repository, `UNDAT.EXE` can be found in the `Tools\UndatUI` folder.
  - If you are using Linux, `UNDAT.SH` can be used instead (requires `WINE` installed).
  - If you are using a (pre)release package, `UNDAT.SH` can be found in the `Fallout1in2` folder.
  - If you are using the repository, `UNDAT.SH` can be found in the `Tools/UndatCLI` folder.

- Select the `Fallout1in2` folder as extraction target.

- Extract the files.

That's it. The game can now be played!

When using Linux with Wine, if there are issues running the game correctly, set the *.dll override priorities in Wine: `WINEDLLOVERRIDES="ddraw.dll=n,b" wine Fallout2.exe`


CONFIGURATION
-------------

Main mod configuration can be found in [config/fo1_settings.ini](config/fo1_settings.ini). It is recommended to check and/or tweak settings in this file _before_ starting a new game. Changing settings mid-game have a chance to corrupt savegames or introduce undefined behavior.

Other interesting files:
- [ddraw.ini](ddraw.ini) (sfall configuration)
- [f2_res.ini](f2_res.ini) (high resolution patch configuration)
- [mods/sfall-mods.ini](mods/sfall-mods.ini) (item highlighting and NPC combat control configuration)
- [config/](config/) directory (misc modifications configuration)


STEAM
-----------------

The mod can be started easily with the Steam client, replacing vanilla FALLOUT 1. We released a small, dedicated tool, which helps keeping manual configuration at minimum.
See https://nma-fallout.com/threads/220425/ for details.

ADDITIONAL CONTENT
------------------

While most optional content is a part of the mod core, and can be toggled on and off by editing the [config/fo1_settings.ini](config/fo1_settings.ini), there are a few mini-mods - separated from main codebase - included as well.

### Classic worldmap ###
[mods/fo1_classic_worldmap](mods/fo1_classic_worldmap)

Enabled by default.
Replaces Fallout 2's green circles, as well as the worldmap tiles with city locations to bring the game's look more in line with the original Fallout 1.

### Carry Weight Indicator  ###
[mods/ShowLootWeight](mods/ShowLootWeight)

Adds a lightweight current/max carry weight indicator to the looting and stealing interface.

### Fallout 1 Interface ###
[mods/fo1_interface](mods/fo1_interface)

Enabled by default.
This mod replaces the FALLOUT 2 interface with the graphics from FALLOUT 1.

### Fallout 1 Maps - Mountains ###
[mods/fo1_maps_mountains](mods/fo1_maps_mountains)

Enabled by default.
Increases the visible area of the mountain encounter maps to support a resolution of 1280x720px without showing black bars at the top and bottom of the screen.

### Improved Death Animations ###
[mods/Anim_ImprovedSMutantDeath](mods/Anim_ImprovedSMutantDeath)

Enabled by default.
Replaces Super Mutant and Power Armor fire and electrocuted death animations with resized versions, to match their regular animations.

### Interface Upscaled ###
[mods/InterfaceUpscaled](mods/InterfaceUpscaled)

Various static images (splash/death screens, endgame slides, town/world, ...) use a higher resolution.

### Inventory AP cost ###
[mods/InventoryAPcosts](mods/InventoryAPcosts)

Tweaks the costs of specific actions while using inventory.

### Language Pack - German ###
[mods/fo1_lang_german](mods/fo1_lang_german)

The german translation of FALLOUT ET TU. It's highly recommended to check the README in language pack directory.

### Language Pack - French ###
[mods/fo1_lang_french](mods/fo1_lang_french)

The french translation of FALLOUT ET TU. It's highly recommended to check the README in language pack directory.

### Robodog ###
[mods/fo1_robodog](mods/fo1_robodog)

Turns Dogmeat into a Robodog, slightly changing available combat options.


ADDITIONAL MODS
--------------
For various other QoL features that aren't included in FALLOUT ET TU already, check out these mods:
- [High quality music](https://github.com/BGforgeNet/Fallout2-HQ-music)
- [Party Orders](https://github.com/BGforgeNet/Fallout2_Party_Orders)
- [FO2tweaks](https://github.com/BGforgeNet/FO2tweaks)
- [Banjo's Fallout 2 Mods](https://www.nma-fallout.com/threads/banjos-fallout-2-mods.220413/)
- [Upscaled videos](https://www.nma-fallout.com/threads/fallout-ettu-hd-videos-playable-ingame.221565/)

SPECIAL THANKS
--------------

We would like to thank NovaRain and Mr.Stalin for their never-ending amounts of patience, scripting advices, sfall tweaks, testing sessions and general support while we was working on the project.
We love you guys!
