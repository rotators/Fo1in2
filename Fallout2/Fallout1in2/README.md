FALLOUT ET TU
-------------
Fallout to Fallout 2 engine conversion


Fallout et tu (also called Fallout 1@2, 1at2, 1in2, ...) is bringing the first Fallout game into the engine of the second one while utilizing features available in Fallout 2 wherever we can (within reason).

---

Discussion: https://nma-fallout.com/threads/218045/ (beta),
            https://nma-fallout.com/threads/217892/ (alpha),
            https://nma-fallout.com/threads/179809/ (legacy)

Repository: https://github.com/rotators/Fo1in2/


MOD INSTALLATION
----------------

- Install FALLOUT 1 anywhere.
  - The game is **REQUIRED** to play the Fallout 1 in 2 engine conversion!

- Install FALLOUT 2 anywhere.
  - The game is **REQUIRED** to play the Fallout 1 in 2 engine conversion!

- Install FALLOUT ET TU into your Fallout 2 folder.
  - The folder structure must look like this:
    ```
    \Fallout2\Fallout1in2\fallout2.exe
    ```

- Start the `UNDAT.EXE` and select the `MASTER.DAT` file from your FALLOUT 1 installation directory.
  - If you are using (pre)release package, `UNDAT.EXE` can be found in `Fallout1in2` folder.
  - If you are using development version (repository), `UNDAT.EXE` can be found in `Tools\UndatUI` folder.

- Select the `Fallout1in2` folder as extraction target.

- Extract the files.

That's it. The game can now be played!


CONFIGURATION
-------------

Main mod configuration can be found in [config/fo1_settings.ini](config/fo1_settings.ini). It is recommended to tweak settings in this file _before_ starting a new game. Changing settings mid-game have a chance to corrupt savegames or introduce undefined behavior.

Other interesting files:
- [ddraw.ini](ddraw.ini), (sfall configuration)
- [sfall-mods.ini](sfall-mods.ini), [config/](config/) directory (sfall modifications configuration)
- [mods/InventoryFilter/InvenFilter.ini](mods/InventoryFilter/InvenFilter.ini) (InventoryFilter mini-mod configuration)


ADDITIONAL CONTENT
------------------

While most of optional content is a part of a mod core, and can be turned on and off by editing [config/fo1_settings.ini](config/fo1_settings.ini), there is a few mini-mods - separated from main codebase - included as well.

### Classic worldmap ###
[mods/fo1_classic_worldmap](mods/fo1_classic_worldmap)

Replaces Fallout 2's green circles, as well as the worldmap tiles with city locations to bring the game's look more in line with the original Fallout 1.

### Inventory AP cost ###
[mods/InventoryAPcosts](mods/InventoryAPcosts)

Tweaks a cost of specific actions while using inventory.

### Inventory Filter ###
[mods/InventoryFilter](mods/InventoryFilter)

Created by Mr.Stalin, see https://www.nma-fallout.com/threads/214445/

### Robodog ###
[mods/fo1_robodog](mods/fo1_robodog)

Turns Dogmeat into a Robodog, slightly changing available combat options.


SPECIAL THANKS
--------------

We would like to thank NovaRain and Mr.Stalin for their never-ending amounts of patience, scripting advices, sfall tweaks, testing sessions and general support while we was working on the project. We love you guys!
