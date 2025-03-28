GLOBAL SCRIPTS
--------------

As well as the new functions, sfall also adds global scripts. These run independent of any loaded maps, but do not have an attached object (i.e. using `self_obj` without using `set_self` first will crash the script).

To use a global script, the script must have a name which begins with `gl` and contains a procedure called `start`, `map_enter_p_proc`, `map_exit_p_proc`, or `map_update_p_proc`. The `start` procedure will be executed once when the player loads a saved game or starts a new game. The `map_*_p_proc` procedures will be executed once when a map is being entered/left/updated. If you wish the script to be executed repeatedly, call `set_global_script_repeat` on the first run of the `start` procedure using the number of frames between each run as the argument (0 disables the script, 1 runs it every frame, 2 runs it every other frame, etc.).

Global scripts have multiple modes, which can be set using the `set_global_script_type` function. In the default mode (i.e. mode 0) their execution is linked to the local map game loop, so the script will not run in dialogs or on the world map. In mode 1 their execution is linked to the player input, and so they will run whenever the mouse cursor is visible on screen, including the world map, character dialogs, etc. In mode 2, execution is linked to the world map loop, so the script will only be executed on the world map and not on the local map or in any dialog windows. Mode 3 is a combination of modes 0 and 2, so scripts will be executed on both local maps and the world map, but not in dialog windows.


----------------------
NOTES ON NEW FUNCTIONS
----------------------

Both `set_global_script_repeat` and `set_global_script_type` only have an effect on the script they were called from. Every global script needs its own `game_loaded` block to correctly set up the script type and repeat rate. `set_global_script_repeat` will have no effect if called on a non-global script.

The `read_xxx` functions take a memory address as the parameter and can read arbitrary pieces of Fallout's address space. The `write_xxx` functions are equivalent except that they write to arbitrary memory addresses.

The `call_offset_xx` functions can be used to call arbitrary functions inside Fallout. Different versions are used to call functions with different numbers of arguments.
None of `write_xxx` and `call_offset_xx` functions will work unless **AllowUnsafeScripting** is enabled in **ddraw.ini**.

The `get_pc_base_stat`, `set_pc_base_stat`, `get_pc_extra_stat` and `set_pc_extra_stat` functions are equivalent to calling `get_critter_base_stat`, `set_critter_base_stat`, `get_critter_extra_stat` and `set_critter_extra_stat` with `dude_obj` as the critter pointer. None of these stat functions take perks into account, and neither do they do range clamping to make sure the stats are valid. Use the normal `get_critter_stat` function to get a correctly perk adjusted and range clamped value for a stat.

The `set_stat_min` and `set_stat_max` functions can be used to set the valid ranges on stats. Values returned by `get_current_stat` will be clamped to this range. The `set_pc_stat_*` functions only affect the player, the `set_npc_stat_*` functions only affect other critters, and the `set_stat_*` functions affect both.

The graphics functions are only available if the user is using graphics mode 4 or 5. Use `graphics_funcs_available` to check; it returns 1 if you can use them or 0 if you can't. Calling graphics functions when `graphics_funcs_available` returns 0 will do nothing.

The `load_shader` takes a path relative to the `<GameRoot>\<master_patches>\shaders\` directory as an argument and returns a shader ID. That ID should be passed as the first argument to all other shader functions, and is valid until `free_shader` is called on the ID, the player loads a saved game or the player quits to the main menu.

The `get_shader_version` gives you the highest shader version supported by the player's graphics cards. Possible return values are 11, 12, 13, 14, 20, 21 and 30.

The `set_shader_mode` tells sfall when to use a shader. The parameter is a set of 32 flags which specify the screens on which the shader will be disabled, unless bit 32 is set, in which case the shader will only be active on those screens. Remember that screens are displayed on top of each other; if the player opens the character menu which in combat, the game still considers the player to be in combat. See **sfall.h** for a list of defines.

The `force_graphics_refresh` forces the screen to redraw at times when it normally wouldn't. If you're using animated shader, turning this option on is recommended.

The mapper manual lists the functions `world_map_x_pos` and `world_map_y_pos`, which supposedly return the player's x and y positions on the world map. The `get_world_map_x_pos` and `get_world_map_y_pos` are included here anyway, because I was unable to get those original functions to work, or even to find any evidence that they existed in game.

The `get_critter_current_ap` and `set_critter_current_ap` functions should only be used during the target critters turn while in combat. Calling them outside of combat typically returns the critters max AP, but don't rely on that behaviour. (Specifically, if the critter has never before entered combat, it will probably return the critters base AP ignoring any extra bonuses from perks etc.)

The **type** value in the weapon knockback functions can be 0 or 1. If 0, the value becomes an absolute distance that targets will be knocked back. If 1, the value is multiplied by the distance they would normally have been knocked back. Weapon knockback modifiers are applied in the order `weapon -> attacker -> target`, so a x2 weapon wielded by an abs 6 attacker hitting a /2 target will knock the target back 3 squares. The knockback functions will not override the stonewall perk or knockdowns resulting from criticals. knockback values set on weapons or critters are not saved, and must be reset each time the player reloads.

The `get_sfall_global` and `set_sfall_global` functions require an 8 characters long case sensitive string for the variable name. The variables behave the same as normal Fallout globals, except that they don't have to be declared beforehand in **vault13.gam**. Trying to get a variable which hasn't been set will always return 0. These functions are intended for use when a patch to a mod requires the addition of a new global variable, a case which would otherwise require the player to start a new game.

The `set_pickpocket_max` and `set_hit_chance_max` affect all critters rather than just the player and can set the maximum in range from 0 to 999.

The `set_skill_max` can't be used to increase the skill cap above 300. The `set_perk_level_mod` sets a modifier between +25 and -25 that is added/subtracted from the player's level for the purposes of deciding which perks can be chosen.

The `set_fake_trait` and `set_fake_perk` can be used to add additional traits and perks to the character screen. They will be saved correctly when the player saves and reloads games, but by themselves they will have no further effect on the character. For perks, the allowed range for levels is between 0 and 100; setting the level to 0 removes that perk. For traits, the level must be 0 or 1. The image is a numeric ID that corresponds to an entry in **skilldex.lst**. The name is limited to 63 characters and the description to 255 characters by sfall, but internal Fallout limits may be lower.

The `has_fake_trait` and `has_fake_perk` return the number of levels the player has of the perks/traits with the given name or ID of extra perk.

The `perk_add_mode`, `set_selectable_perk`, `set_perkbox_title`, `hide_real_perks`, `show_real_perks` and `clear_selectable_perks` control the behaviour of the select a perk box. The `set_selectable_perk` can be used to add additional items by setting the **active** parameter to 1, and to remove them again by setting it to 0. The `set_perkbox_title` can be used to change the title of the box, or by using `""` it will be set back to the default. The `hide_real_perks` and `show_real_perks` can be used to prevent the dialog from displaying any of the original 119 perks. The `perk_add_mode` modifies what happens when a fake perk is selected from the perks dialog. It is treated as a set of flags - if bit 1 is set then it is added to the player's traits, if bit 2 is set it is added to the player's perks, and if bit 3 is set it is removed from the list of selectable perks. The default is 0x2. The `clear_selectable_perks` restores the dialog to its default state.

The `show_iface_tag`, `hide_iface_tag` and `is_iface_tag_active` relate to the boxes that appear above the interface such as SNEAK and LEVEL. You can use 0 for **SNEAK** (starting from sfall 4.4.4/3.8.44), 3 for **LEVEL**, 4 for **ADDICT**, and 5 to (4 + the value of BoxBarCount in **ddraw.ini**) for custom boxes. Remember to add your messages to **intrface.msg** and set up the font colours in **ddraw.ini** if you're going to use custom boxes. Starting from sfall 4.1/3.8.12, `is_iface_tag_active` can also be used to check 0 for **SNEAK**, 1 for **POISONED**, and 2 for **RADIATED**.

The `get_bodypart_hit_modifier` and `set_bodypart_hit_modifier` alter the hit percentage modifiers for aiming at specific bodyparts. Valid bodypart id's are from 0 to 8. Changes are not saved, and will reset to the defaults (or to the values specified in **ddraw.ini** if they exist) at each reload.

The `get_critical_table`, `set_critical_table` and `reset_critical_table` are used for modifying the critical table (for details, see http://falloutmods.wikia.com/wiki/Critical_hit_tables). Changes are not saved, and will reset to the defaults (or to the contents of **CriticalOverrides.ini**, if it exists) at each game reload. These function also require **OverrideCriticalTable** to be enabled in **ddraw.ini**.

The `get_unspent_ap_bonus` and `set_unspent_ap_bonus` alter the AC bonus you receive per unused action point at the end of your turn in combat. To allow for fractional values, the value given if divided by 4. (Hence the default value is 4 and not 1.) The `get_unspent_ap_perk_bonus` and `set_unspent_ap_perk_bonus` are similar, but affect the extra AC granted by the HtH Evade perk. (The default value of this is also 4, equivalent to doubling the original bonus.)

The `fs_*` functions are used to manipulate a virtual file system. Files saved here should have paths relative to the data folder, and use backslashes as the directory separator. They will take precedence over files stored in the normal data folder. They will also be saved into save games if you set a flag for them using `fs_resize(fileId, -1)`, so be avoid creating large files. Using `fs_copy` followed by `fs_read_xxx`, you can read the contents of existing files.

The `get_proto_data` and `set_proto_data` are used to manipulate the in memory copies of the **.pro** files Fallout makes when they are loaded. The offset refers to the offset in memory from the start of the proto to the element you are reading. Changes are not stored on disc, and are not permanent. If you modify the protos, and then Fallout subsequently reloads the file your changes will be lost.

The `list_xxx` functions can be used to loop over all items on a map. `list_begin` takes an argument telling sfall what you want to list (defined in **sfall.h**). It returns a list pointer, which you iterate through with `list_next`. Finally, when you've finished with the list use `list_end` on it. Not calling `list_end` will result in a memory leak. Alternatively, use `list_as_array` to get the whole list at once as a temp array variable, which can be looped over using `len_array` and which you don't need to remember to free afterwards.

The `play_sfall_sound` and `stop_sfall_sound` are used to play **mp3/wav/wma** files. The path given is relative to the Fallout folder. Specify mode as 1 to loop the file continuously, 2 to replace the current background game music with playing the specified file in loop mode, or 0 to play the file once. If you don't wish to loop, `play_sfall_sound` returns 0. If you do loop, it returns an ID which can be passed back to `stop_sfall_sound` when you want to stop the effect. All sounds effects will be stopped on game reload, looping or not. These functions do not require **AllowDShowSound** to be set to 1 in **ddraw.ini**.
Starting from sfall 4.2.8/3.8.28, you can pass a value in the **mode** argument for a reduced sound volume. To set the volume, you need to convert the number to hexadecimal and use the argument format `0xZZZZ000Y`, where `ZZZZ` is the volume reduction value in range from 0 to 32767 (the value 32767 is muted), and `Y` is the playback mode.

Arrays are created and manipulated with the `xxx_array` functions. An array must first be created with `create_array` or `temp_array`, specifying how many data elements the array can hold. You can store any of ints, floats and strings in an array, and can mix all 3 in a single array. The ID returned by `create_array` or `temp_array` can then be used with the other array functions. Arrays are shared between all scripts. (i.e. you can call `create_array` from one script, and then use the returned ID from another script.) They are also saved across savegames. Arrays created with `temp_array` will be automatically freed at the end of the frame. These functions are safe, in that supplying a bad ID or trying to access out of range elements will not crash the script. `create_array` is the only function that returns a permanent array, all other functions which return arrays (`string_split`, `list_as_array`, etc,) all return temp arrays. You can use `fix_array` to make a temp array permanent.\
__NOTE:__ refer to **arrays.md** for detailed description of the array behavior and function usage.

The `force_aimed_shots` and `disable_aimed_shots` allow overriding the normal rules regarding which weapons are allowed to make aimed attacks. (e.g. weapons that cause explosive damage normally cannot normally make aimed shots.) `force_aimed_shots` will allow a weapon to make aimed shots even if it normally couldn't, and `disable_aimed_shots` stops a weapon from making aimed shots even if it normally could. Both of these functions affect player and NPCs alike. `force_aimed_shots` does not override the effects of the fast shot trait. The list of edited weapons is not saved over game loads, so you need to call the functions once at each reload. Use a pid of 0 to represent unarmed.

The `get_critter_skill_points` and `set_critter_skill_points` will get or set the number of additional points a critter has in a skill, on top of whatever they have from their stats and other bonuses. Note that skill points are part of the proto, so calling `set_skill_points` on a critter will affect all critters that share the same proto.


--------------------
DEPRECATED FUNCTIONS
--------------------

Using global scripts in mode 1 requires the input wrapper to be enabled. Use `available_global_script_types` to check what is available.

The input functions are only available if the user has the input hook turned on in **ddraw.ini**. Use `input_funcs_available` to check.

The `nb_create_char` function is reserved for the brotherhood tactical training mod, and should be avoided.


---------------
TYPES REFERENCE
---------------

Data types mentioned in this document:

* `void`   - means opcode does not return any value
* `any`    - any type
* `int`    - integer number
* `float`  - floating point number
* `string` - string (text) value
* `object` - pointer to game object (actually an integer)
* `array`  - array ID to be used with array-related functions (actually an integer)
* `bool`   - boolean values: `True` or `False` (actually an integer 1 or 0)


------------------
FUNCTION REFERENCE
------------------

#### `int game_loaded()`
- Returns 1 the first time it is called after a new game or game load, and 0 any time after. It works on an individual basis for each script, so one script wont interfere with others. Its primary use is for global scripts, so that they know when to call `set_global_script_repeat`, but it can be called from normal scripts too.

-----
#### `void set_pipboy_available(int available)`
- Sets the availability of the pipboy in the game. Use 0 to disable the pipboy, and 1 or 2 to enable it (value 2 does not change the player's default appearance).
- The availability state will be reset each time the player reloads the game.
- __NOTE:__ Starting from sfall 4.4.6/3.8.46, value 1 no longer marks the `VSUIT_MOVIE` movie as "played". Use `mark_movie_played(VSUIT_MOVIE)` instead if you want the old behavior.

-----
#### `void inc_npc_level(int pid/string name)`
- Takes a party member PID or an NPC name (deprecated, for compatibility with sfall 4.1.5/3.8.15 or earlier) as an argument. The NPC must be in your party.
- This function ignores player level requirements and the minimum 3 player level delay between NPC level gains. It also ignores the random element, regardless of sfall's **NPCAutoLevel** or **PartyMemberNonRandomLevelUp** setting.

-----
#### `int get_npc_level(int pid/string name)`
- Also takes the party member PID or NPC name (deprecated, for compatibility with sfall 4.1.5/3.8.15 or earlier) as an argument, and returns the NPC's current level. Again, the NPC needs to be in your party.

-----
#### `void set_car_current_town(int town)`
- Changes the current town index for the player's car.

-----
#### `int get_ini_setting(string setting)`
- Reads an integer value from an ini file in the Fallout directory.
- It only takes a single argument; seperate the file name, section and key with a `|` character, e.g. `myvar := get_ini_setting("myini.ini|mysec|var1")`.
- If the file or key cannot be found or the setting argument is in an invalid format, it returns -1.
- The file name is limited to 63 chars, including the extension.
- The section name is limited to 32 characters.
- It can also be used to get sfall settings by using **ddraw.ini** as the file name.

-----
#### `string get_ini_string(string setting)`
- Reads a string value from an ini file in the Fallout directory.
- If the file or key cannot be found, it returns an empty string.
- If the setting argument is in an invalid format, it returns -1 (integer).

-----
#### `int get_game_mode()`
- Is a more flexible version of `in_world_map`. It will return a set of flags indicating which mode the game is currently in.
- These flags are the same as those used in the `set_shader_mode` function.

-----
#### `int get_uptime()`
- Is just a wrapper around the windows `GetTickCount()` function. It's useful for making time fade effects in shaders, since they already have access to the current tick count.

-----
#### `bool in_world_map()`
- Returns 1 if the player is looking at the world map, or 0 at any other time.
- Obviously this is only useful in global scripts, since normal scripts will never get the chance to run on the world map.

-----
#### `void force_encounter(int map)`
- Can be called either from a global script while traveling on the world map, or from a normal script while on a local map.
- In either case the encounter occurs shortly after the next time the player moves on the world map.
- The player will not get an outdoorsman skill check.

-----
#### `void force_encounter_with_flags(int map, int flags)`
- Does the same thing as `force_encounter`, but allows the specification of some extra options (see **sfall.h** for available flags).
- Forcing a random encounter on a map that is not normally used for random encounters may cause the player to lose the car, if they have it.
- In this case use `force_encounter_with_flags` with the `ENCOUNTER_FLAG_NO_CAR` flag set.

-----
#### `int get_light_level()`
- Ambient light level in range 0..65536
- The value returned by `get_light_level` may not exactly match that set by `set_light_level`, as `set_light_level` applies modifiers from the night vision perk.

-----
#### `void set_map_time_multi(float multi)`
- Adjusts how fast time passes while you're on the world map. It takes a single float as an argument, where 1 is the normal speed.
- This function works in addition to the **WorldMapTimeMod** setting in **ddraw.ini** and the Pathfinder perk, rather than overriding it, so calling `set_map_time_multi(0.5)` when the player has 2 levels of pathfinder would result in time passing at 25% the normal speed on the world map.

-----
#### `void remove_script(object obj)`
- Accepts a pointer to an object and will remove the script from that object.

-----
#### `void set_script(object obj, int scriptID)`
- Accepts a pointer to an object and **scriptID**, and applies the given script to an object (scriptID accepts the same values as `create_object_sid`)
- If used on an object that is already scripted, it will remove the existing script first; you cannot have multiple scripts attached to a single object. Calling `set_script` on `self_obj` will have all sorts of wacky side effects, and should be avoided.
- If you add `0x80000000` to the SID when calling `set_script`, `map_enter_p_proc` will be SKIPPED. The `start` proc will always be run.

-----
#### `int get_script(object obj)`
- Accepts a pointer to an object and returns its scriptID (line number in **scripts.lst**), or 0 if the object is unscripted.
- Returns -1 on argument error.

-----
#### `void set_self(object setObj)`
- Overrides the script's `self_obj` for the next function call.
- It is primarily used to allow the calling of functions which take an implicit `self_obj` parameter (e.g. `drop_obj`) from global scripts, but it can also be used from normal scripts.
- `self_obj` will be reverted to its original value after the next function call.
- Calling `set_self(0)` will also revert `self_obj` to its original value. It is recommended to call this after each use of `set_self` in normal scripts in order to avoid unforeseen side effects.
- `source_obj`, `target_obj`, and similar functions will not work if preceded by `set_self`.
- __NOTE:__ for `use_obj` and `use_obj_on_obj` vanilla functions to work correctly, it is required to call `set_self` twice. You can also access the local variables in the script of an object after calling `set_self` twice.

-----
#### `void mod_skill_points_per_level(int x)`
- Accepts a value of between -100 and 100, and modifies the number of skill points the player receives when they level up.
- This is a modification of what would otherwise happen, rather than a replacement.
- The value is not saved into the save game, so should be reset in the `game_loaded` section of a script.

-----
#### `void set_perk_freq(int x)`
- Sets the number of levels between each perk.
- Setting 0 will reset it back to the default.
- This overrides the effects of the skilled trait.
- It is not saved into the save game, so needs to be called once per reload.
- Be careful not to let the player obtain a perk when no perks are available to pick, or the game may crash.

-----
#### `object get_last_target(object critter)`
- Will return the last critter to be deliberately attacked.

-----
#### `object get_last_attacker(object critter)`
- Will return the last critter to deliberately launch an attack against the argument critter.
- If a critter has not launched/received an attack, it will return 0. This is only stored for the duration of combat, and outside of combat both functions will always return 0.

-----
#### `void set_base_pickpocket_mod(int max, int mod)`
- Changes maximum chance of success and chance mod for each steal attempt.
- `max` will replace 95% success chance cap (so you can set 100% maximum chance, for instance).
- `mod` will add this much percent to each success chance. For example, if your chance is 50% and `mod` is 20, you will get 70% actual success rate.

-----
#### `void set_critter_pickpocket_mod(object critter, int max, int mod)`
- The same as above, but applies only to specific critter.

-----
#### `int get_tile_fid(int tileData)`
- Returns FID information about the square under the given tile at elevation 0.
- Pass elevation as 4-bit number in bits 25-28 to access other elevations.
- Pass result mode in bits 29-32: 0 - ground FID, 1 - roof FID, 2 - raw data. Following macros are available in **sfall.h**:

-----
#### `int get_tile_ground_fid(int tileNum, int elevation)`
- Returns FID of a ground tile at given tile number and elevation.

-----
#### `int get_tile_roof_fid(int tileNum, int elevation)`
- Returns FID of a roof tile at given tile number and elevation. Note that FID of 1 is used when there is no actual roof.

-----
#### `void reg_anim_combat_check(int enable)`
- Allows enabling all `reg_anim_*` functions in combat (including vanilla functions) if set to 0. It is automatically reset at the end of each frame, so you need to call it before `reg_anim_begin() ... reg_anim_end()` code block.

**Some additional `reg_anim_*` functions were introduced. They all work in the same convention as vanilla functions and use the same underlying code.**

#### `void reg_anim_destroy(object obj)`
- Given object is destroyed at the end of current animation set.

-----
#### `void reg_anim_animate_and_hide(object obj, int animID, int delay)`
- Works exactly like `reg_anim_animate` but the object will automatically disappear after the last animation frame (but not destroyed).
- `delay`: delay from the previous animation. A value of -1 will execute the specified animation immediately after the previous one in the sequence ends.

-----
#### `void reg_anim_light(object obj, int light, int delay)`
- Change light of any object. light argument is a light radius (0-8), but you can use highest 2 bytes to pass light intensity as well (example: `0xFFFF0008` - intensity 65535 and radius 8). If highest 2 bytes are 0, intensity will not be changed. Intensity range is from 0 to 65535 (0xFFFF).

-----
#### `void reg_anim_change_fid(object obj, int fid, int delay)`
- Should work like `art_change_fid_num` but in `reg_anim` sequence.

-----
#### `void reg_anim_take_out(object obj, holdFrameID, int delay)`
- Plays "take out weapon" animation for given **holdFrameID**. It is not required to have such weapon in critter's inventory.

-----
#### `void reg_anim_turn_towards(object obj, int/object tile/target, int delay)`
- Makes object change its direction to face given tile number or target object.

-----
#### `void reg_anim_callback(procedure proc)`
- Adds the given procedure to an animation sequence-list and executes it in the registered sequence.

-----
#### `int/array metarule2_explosions(int arg1, int arg2, int arg3)`
- Was made as a quick-and-dirty hack to enable dynamic changes to some explosion parameters for ranged attacks. All changed parameters are automatically reset to vanilla state after each attack action. Following macros are available in **sfall.h**:

-----
#### `void set_attack_explosion_pattern(int x, int y)`
- Currently `y` is not used and `x` means: 1 - reduced explosion pattern (3 effects are spawned instead of 7), 0 - full pattern.

-----
#### `void set_attack_explosion_art(int x, int y)`
- `y` is not used and `x` is a misc frame ID (last 3 bytes, without object type) to use for the next explosion.

-----
#### `void set_attack_explosion_radius(int x)`
- Changes radius at which explosion will hit secondary targets for the next attack (from the experiments it is limited to something around 8 by the engine)

-----
#### `void set_attack_is_explosion_fire`
- If you call this right before using a weapon with fire damage type (e.g. in `HOOK_AFTERHITROLL`), it will produce explosion effects (and radius damage) just like "explosion" type, but all targets will still receive fire damage.

-----
#### `void set_explosion_radius(int grenade, int rocket)`
- Sets a permanent radius of the explosion for grenades and/or rockets. Passing 0 means not changing the corresponding radius.
- Changed radius will be reset each time the player reloads the game.

-----
#### `array get_explosion_damage(int itemPid)`
- Returns an array of the minimum and maximum damage of the explosive item.

-----
#### `void set_dynamite_damage(int minDmg, int maxDmg)`
- Sets the minimum and maximum damage for Dynamite.
- Changed damage will be reset each time the player reloads the game.

-----
#### `void set_plastic_damage(int minDmg, int maxDmg)`
- Sets the minimum and maximum damage for Plastic Explosives.
- Changed damage will be reset each time the player reloads the game.

-----
#### `void set_explosion_max_targets(int x)`
- Sets the maximum number of additional targets for an explosion, valid range: 1..6 (default is 6)

---
### Some utility/math functions are available:

#### `array string_split(string text, string split)`
- Takes a string and a separator, searches the string for all instances of the separator, and returns a temp array filled with the pieces of the string split at each instance. If you give an empty string as the separator, the string is split into individual characters.
- You can use this to search for a substring in a string like this: `strlen(get_array(string_split(haystack, needle), 0))`

-----
#### `string substr(string text, int start, int length)`
- Cuts a substring from a string starting at `start` up to `length` characters. The first character position is 0 (zero).
- If `start` is negative - it indicates a position starting from the end of the string (for example, `substr("test", -2, 2)` will return last 2 charactes: "st").
- If `length` is negative - it means so many characters will be omitted from the end of string (example: `substr("test", 0, -2)` will return string without last 2 characters: "te").
- If `length` is zero - it will return a string from the starting position to the end of the string (**new behavior** since sfall 4.2.2/3.8.22).

-----
#### `int strlen(string text)`
- Returns string length.

-----
#### `string sprintf(string format, any value)`
- Formats given value using standard syntax of C `printf` function (google "printf" for format details). However, it is limited to formatting only 1 value.
- Can be used to get character by ASCII code (`%c`).

-----
#### `int typeof(any value)`
- Returns type of the given value: `VALTYPE_INT`, `VALTYPE_FLOAT` or `VALTYPE_STR`.

-----
#### `int charcode(string text)`
- Returns ASCII code for the first character in given string.

-----
#### `div` operator (unsigned integer division)
- Use as a division operator, like `3 + (20 div 5)`
- If both dividend and divisor are integers, they will be treated as unsigned integers.
- If one of them is a float, div will perform the signed division just like vanilla division operator.

-----
#### `^` operator (exponentiation)
- Use as any other arithmetic operator, like `5 ^ (1 / 3)`
- If exponent is an integer, you can use a negative base, otherwise you will get `NaN` with a negative base.
- If both arguments are integers, the result will be an integer.

-----
#### `float log(float x)`
- Natural logarithm of `x`.

-----
#### `float exponent(float x)`
- `e ^ x`

-----
#### `int ceil(float x)`
- Round `x` to the nearest integer that is not less than `x`.

-----
#### `int round(float x)`
- Round `x` to the nearest integer.

-----
#### `float sqrt(float x)`
- Square root of `x`.

-----
#### `int/float abs(int/float x)`
- Absolute (positive) value of `x`.

-----
#### `float sin(float x)`
- Sine of `x`.

-----
#### `float cos(float x)`
- Cosine of `x`.

-----
#### `float tan(float x)`
- Tangent of `x`.

-----
#### `float arctan(float x, float y)`
- Arctangent of `x`.
- Just pass 1 as `y` (don't ask...)

-----
#### `void register_hook_proc(int hookID, procedure proc)`
- Works just like `register_hook`, but allows to specify which procedure to use for given hook script (instead of `start`).
- Use zero (0) as second argument to unregister hook script from current global script.
- Only use in global scripts.
- Second argument should be passed just like you pass procedures to functions like `gsay_option`, `giq_option`, etc. (name without quotes).
- See **hookscripts.md** for more details.

-----
#### `void register_hook_proc_spec(int hookID, procedure proc)`
- Works just like `register_hook_proc`, but allows to register a script at the end of the hook script execution chain (i.e. the script will be executed after all previously registered scripts for the same hook, including the `hs_*.int` script).
- To unregister hook script from current global script, use the `register_hook_proc` function.

-----
#### `string message_str_game(int fileId, int messageId)`
- Works exactly the same as `message_str`, except you get messages from files in the `text\<language>\game\` directory.
- Use `GAME_MSG_*` defines or `mstr_*` macros from **sfall.h** to use specific msg file.
- Additional game msg files added by **ExtraGameMsgFileList** setting will have consecutive fileIds assigned beginning from `0x2000` to `0x2FFF`. (e.g. if you set `ExtraGameMsgFileList=foo,bar` in **ddraw.ini**, foo.msg will be associated with 0x2000 and bar.msg with 0x2001.)
- If a file has a specific number assigned in **ExtraGameMsgFileList**, its fileId will be (`0x2000` + assigned number). (e.g. with `ExtraGameMsgFileList=foo,bar:2,foobar` in **ddraw.ini**, bar.msg will be associated with 0x2002 and foobar.msg with 0x2003.)

-----
#### `int sneak_success()`
- Returns 1 if the player is currently sneaking, and last sneak attempt (roll against skill) was successful; 0 otherwise.
- This calls an internal engine function which is used to determine the perception range of critters (which you can override using `HOOK_WITHINPERCEPTION`).

-----
#### `int tile_light(int elevation, int tileNum)`
- Returns light intensity at the given tile in range from 0 to 65536.

-----
#### `object obj_blocking_line(object objFrom, int tileTo, int blockingType)`
- Returns first object which blocks direct linear path from objFrom to tileTo using selected blocking function (see `BLOCKING_TYPE_*` constants in **sfall.h**).
- If path is clear (no blocker was encountered by selected function) - returns 0.
- `objFrom` is always excluded from calculations, but is required to be a valid object.

-----
#### `object obj_blocking_tile(int tileNum, int elevation, int blockingType)`
- Returns first object blocking given tile using given blocking function or 0 if tile is clear.

-----
#### `array tile_get_objs(int tileNum, int elevation)`
- Returns an array of all objects at given tile.
- It will include any hidden, dead or system objects (like cursor), so make sure to check properly when iterating.

-----
#### `array party_member_list(int includeHidden)`
- Returns an array of all current party members (0 - only critters that are alive and visible will be returned, 1 - all objects, including the car trunk, etc.)

-----
#### `array path_find_to(object objFrom, int tileTo, int blockingType)`
- Returns the shortest path to a given tile using given blocking function as an array of tile directions (0..5) to move on each step.
- Array length equals to a number of steps.
- Empty array means that specified target cannot be reached.

-----
#### `object create_spatial(int scriptID, int tile, int elevation, int radius)`
- Creates new spatial script with given SID, at given tile, and radius.

-----
#### `int art_exists(int artFID)`
- Checks if given **artFID** exists in the game.
- Useful when you want to check if critter can use specific weapon: `art_exists((artFid bwand 0xFFFF0FFF) bwor (weaponAnim * 0x1000))`

-----
#### `int obj_is_carrying_obj(object invenObj, object itemObj)`
- Returns number of itemObj inside invenObj's inventory, note that both arguments are object pointers.
- Useful when dealing with different stacks of same item (`obj_is_carrying_obj_pid` just returns total for all stacks of the same PID).

-----
#### `any sfall_funcX(string funcName, ...)`
- These opcodes allows to use additional script functions, that do not require new opcode.
- First argument is always function name (string).
- There are 9 versions of this opcode for different number of additional arguments (for convenience).
- Opcodes have return value, but it is not necessary to use it.


------------------------------
sfall_funcX metarule functions
------------------------------

#### get_metarule_table
`array sfall_func0("get_metarule_table")`
- Returns names of all currently available script functions (via `sfall_funcX`)

----
#### metarule_exist
`bool sfall_func1("metarule_exist", string metaruleName)`
- Returns True if the specified name of `sfall_funcX` metarule function exists in the current version of sfall

----
#### spatial_radius
`int sfall_func1("spatial_radius", object obj)`
- Returns radius of spatial script, associated with given dummy-object (returned by `create_spatial`)

----
#### critter_inven_obj2
`object sfall_func2("critter_inven_obj2", object invenObj, int type)`
- Works just like vanilla `critter_inven_obj`, but correctly reports item in player's inactive hand slot

----
#### intface_redraw
`void sfall_func0("intface_redraw")`\
`void sfall_func1("intface_redraw", int winType)`
- Redraws main game interface, useful to reflect changes after directly changing current player weapons or stats
- `winType`: the type number of the interface window (see `WINTYPE_*` constants in **sfall.h**). Pass -1 to redraw all interface windows

----
#### intface_hide
`void sfall_func0("intface_hide")`
- Hides main interface

----
#### intface_show
`void sfall_func0("intface_show")`
- Shows main interface

----
#### intface_is_hidden
`int sfall_func0("intface_is_hidden")`
- Returns 1 if interface is currently hidden, 0 otherwise

----
#### exec_map_update_scripts
`void sfall_func0("exec_map_update_scripts")`
- Executes `map_update_p_proc` for all objects on map and global/hook scripts as well

----
#### set_ini_setting
`void sfall_func2("set_ini_setting", string setting, int/string value)`
- Writes an integer or a string value to an ini file in the Fallout directory. If the ini file does not exist, it will be created
- The `setting` argument works in the same way as in get_ini_setting; seperate the file name, section and key with a `|` character, e.g. `set_ini_setting("myini.ini|mysec|var1", 42)`
- The file name is limited to 63 chars, including the extension
- The section name is limited to 32 characters

----
#### floor2
`int sfall_func1("floor2", int/float value)`
- Works just like vanilla `floor` function, but returns correct integers for negative floats
- __NOTE:__ vanilla `floor` function works exactly the same as `ceil` for negative floats (i.e. basically `trunc` in C/C++)

----
#### item_weight
`int sfall_func1("item_weight", object obj)`
- Gets the current weight of an object

----
#### get_outline
`int sfall_func1("get_outline", object obj)`
- Gets the current outline color for an object

----
#### set_outline
`void sfall_func2("set_outline", object obj, int color)`
- Sets the outline color of an object (see `OUTLINE_*` constants in **sfall.h**)
- Can also set a custom color from the game palette by shifting the color index value left by 8 bits: `0xCC00` where `CC` is the palette index (**available since sfall 4.2.7/3.8.27**)
- Passing 0 will disable the outline
- call `tile_refresh_display` after changing outline of objects to properly redraw the scene

----
#### get_flags
`int sfall_func1("get_flags", object obj)`
- Gets the current value of object flags (see **define_extra.h** for available flags)

-----
#### set_flags
`void sfall_func2("set_flags", object obj, int flags)`
- Sets the current flags of an object
- All flags are rewritten with given integer, so first get current flags with `get_flags` and use `bwor`/`bwand` to set/remove specific flag

----
#### tile_refresh_display
`void sfall_func0("tile_refresh_display")`
- Redraws the game scene (tiles, walls, objects, etc.)

----
#### outlined_object
`object sfall_func0("outlined_object")`
- Returns an object that is currently highlighted by hovering the mouse above it

----
#### set_dude_obj
`object sfall_func1("set_dude_obj", int critter)`
- Take control of a given critter
- Passing 0 will reset control back to "real" dude

----
#### real_dude_obj
`void sfall_func0("real_dude_obj")`
- Returns the initial `dude_obj` after `set_dude_obj` was used

----
#### get_ini_sections
`array sfall_func1("get_ini_sections", string file)`
- Returns an array of names of all sections in a given INI file
- If the INI file is not found, it returns an empty array

----
#### get_ini_section
`array sfall_func2("get_ini_section", string file, string section)`
- Returns an associative array of keys and values for a given INI file and section
- If the INI file is not found, it returns an empty array
- __NOTE:__ all keys and their values will be of String type

----
#### car_gas_amount
`int sfall_func0("car_gas_amount")`
- Returns the current amount of fuel in player's car (between 0 and 80000)
- To change fuel amount, use vanilla function: `metarule(METARULE_GIVE_CAR_GAS, amount)` - amount can be positive or negative

----
#### set_car_intface_art
`void sfall_func1("set_car_intface_art", int artIndex)`
- Changes the interface art (index in **intrface.lst**) for the car image on the world map interface
- Should be called before going to the world map
- Vanilla art index is 433

----
#### get_cursor_mode
`int sfall_func0("get_cursor_mode")`
- Returns the current cursor mode: 0 - movement cursor, 1 - command cursor, 2 - targeting cursor
- Mode 4 to 10 are **Skilldex** skills (yellow targeting cursor)

----
#### set_cursor_mode
`void sfall_func1("set_cursor_mode", int mode)`
- Sets the current cursor mode

----
#### display_stats
`void sfall_func0("display_stats")`
- Updates player stats in the inventory display window or on the character screen
- __NOTE:__ works only when the interface window is opened

----
#### lock_is_jammed
`int sfall_func1("lock_is_jammed", object obj)`
- Returns 1 if the lock (container or scenery) is currently jammed, 0 otherwise

----
#### unjam_lock
`void sfall_func1("unjam_lock", object obj)`
- Unjams a lock immediately without having to wait until the next day, or leave the map and then return after 24 hours
- __NOTE:__ does not work in `use_skill_on_p_proc` procedure

----
#### set_unjam_locks_time
`void sfall_func1("set_unjam_locks_time", int time)`
- Sets after how many hours (up to 127 hours) jammed locks will be unjammed if the player leaves the map
- Also disables the auto unjam that occurs at midnight when the player is on the map
- Passing 0 will disable the auto unjam mechanism completely
- The auto unjam mechanism will be reset each time the player reloads the game

----
#### get_map_enter_position
`array sfall_func0("get_map_enter_position")`
- Returns an array of the player's position data (index 0 - tile, 1 - elevation, 2 - rotation) when entering the map through exit grids
- If entering from the world map, the tile value will be -1
- Should be called in `map_enter_p_proc` procedure to get the correct position data

----
#### set_map_enter_position
`void sfall_func3("set_map_enter_position", int tile, int elevation, int rotation)`
- Overrides the player's entry position when entering the map through exit grids
- Setting the `tile` to 0 will put the player on the start hex (default tile and elevation) of the map
- __NOTE:__ works only in `map_enter_p_proc` procedure

----
#### set_rest_heal_time
`void sfall_func1("set_rest_heal_time", int minutes)`
- Sets the time interval in minutes for healing during resting. The default is 180
- The time interval will be reset each time the player reloads the game

----
#### set_rest_mode
`void sfall_func1("set_rest_mode", int mode)`
- Sets the bit flags for the rest mode (see `RESTMODE_*` constants in **sfall.h**)
- Passing 0 will reset the rest mode. It will also be reset each time the player reloads the game

----
#### attack_is_aimed
`int sfall_func0("attack_is_aimed")`
- Returns 1 if the aimed attack mode is selected, 0 otherwise

----
#### set_iface_tag_text
`void sfall_func3("set_iface_tag_text", int tag, string text, int color)`
- Sets the text messages and colors for custom notification boxes to the interface without the need to add messages to intrface.msg and set up the font colors in **ddraw.ini**
- `tag` value is the same as used in `show_iface_tag`, `hide_iface_tag`, and `is_iface_tag_active`. The valid range is from 5 to (4 + the value of **BoxBarCount** in **ddraw.ini**) or the number of the last custom box added using the `add_ifaca_tag` function
- The text is limited to 19 characters
- Available colors: 0 - green, 1 - red, 2 - white, 3 - yellow, 4 - dark yellow, 5 - blue, 6 - purple, 7 - dull pink

----
#### add_iface_tag
`int sfall_func0("add_iface_tag")`
- Adds one custom box to the current boxes, and returns the number of the added tag (-1 if the tags limit is exceeded)
- The maximum number of boxes is limited to 126 tags

----
#### inventory_redraw
`void sfall_func0("inventory_redraw")`\
`void sfall_func1("inventory_redraw", int invSide)`
- Redraws inventory list in the inventory/use inventory item on/loot/barter screens
- `invSide` specifies which side needs to be redrawn: 0 - the player, 1 - target (container/NPC in loot/barter screens), -1 - both sides (same as without argument)

----
#### item_make_explosive
`void sfall_func3("item_make_explosive", int pid, int activePid, int damage)`\
`void sfall_func4("item_make_explosive", int pid, int activePid, int min, int max)`
- Makes the specified item (pid) an explosive item like Dynamite or Plastic Explosives
- `activePid` is for an item with an active timer, can be the same as the `pid` argument
- The item proto must be the **Misc Item** type and have the **Use** action flag
- `min` and `max` are the minimum and maximum explosion damage
- Using the function on an item that is already set as an explosive will override its previous settings
- __NOTE:__ this function does not work for pid's of Dynamite and Plastic Explosives

----
#### get_string_pointer
`int sfall_func1("get_string_pointer", string text)`
- (DEPRECATED) Returns a pointer to a string variable or to a text
- __NOTE:__ this function is intended for use only in `HOOK_DESCRIPTIONOBJ`. Starting from sfall 4.4/3.8.40, you can return normal strings directly in the hook without calling the function

----
#### dialog_message
`void sfall_func1("dialog_message", string text)`
- Displays a message in the NPC response window in dialog or barter screen

----
#### get_current_inven_size
`int sfall_func1("get_current_inven_size", object obj)`
- Returns the current inventory size of the container or the critter

----
#### create_win
`void sfall_func5("create_win", string winName, int x, int y, int width, int height)`\
`void sfall_func6("create_win", string winName, int x, int y, int width, int height, int flags)`
- Works just like vanilla `CreateWin` function, but creates a window with `MoveOnTop` flag if the flags argument is not specified, and allows to set additional flags for the created window
- `MoveOnTop` flag allows the created window to be placed on top of the game interface

----
#### set_can_rest_on_map
`void sfall_func3("set_can_rest_on_map", int mapNum, int elev, bool value)`
- Allows/disallows to rest on the map for the specified level, overrides the `can_rest_here` values in **maps.txt**
- `mapNum` is the map index from **maps.txt**
- Passing -1 to the `elev` argument will set the rest value for all map elevations
- The set rest value will be stored in **sfalldb.sav** file (in savegame)

----
#### get_can_rest_on_map
`int sfall_func2("get_can_rest_on_map", int mapNum, int elev)`
- Returns the set rest value of the map after using the `set_can_rest_on_map` function
- Returns -1 if the rest value of the map was not previously set (i.e. no data for the map in **sfalldb.sav**)
- The `can_rest_here` values from **maps.txt** are ignored

----
#### dialog_obj
`object sfall_func0("dialog_obj")`
- Returns a pointer to the object (critter) the player is having a conversation or bartering with

----
#### obj_under_cursor
`object sfall_func2("obj_under_cursor", bool onlyCritter, bool includeDude)`
- Returns the object under the cursor on the main game screen
- `onlyCritter`:\
    True - only checks critters and ignores their cover (roof tiles, walls, scenery, etc.)\
    False - checks all objects (can't check critters under objects)
- Passing False to the `includeDude` argument will ignore `dude_obj`
- __NOTE:__ to get an object located on a tile when the cursor is in movement mode (hexagon cursor), use the `tile_under_cursor` function

----
#### loot_obj
`object sfall_func0("loot_obj")`
- Returns a pointer to the target object (container or critter) of the loot screen

----
#### get_object_data
`int sfall_func2("get_object_data", object obj, int offset)`
- Returns the data at the specified offset of an object (see `OBJ_DATA_*` constants in **define_extra.h** for offsets)

----
#### set_object_data
`void sfall_func3("set_object_data", object obj, int offset, int data)`
- Sets the data at the specified offset of an object

----
#### get_object_ai_data
`int sfall_func2("get_object_ai_data", object obj, int aiParam)`
- Returns the setting value from the AI packet of an object (critter)
- Use `AI_CAP_*` constants from **define_extra.h** for the aiParam argument to get AI value

-----
#### art_cache_clear
`void sfall_func0("art_cache_clear")`
- Clears the cache of FRM image files loaded into memory

----
#### npc_engine_level_up
`void sfall_func1("npc_engine_level_up", bool toggle)`
- Enables/disables the engine function that increases the level of party members in the player leveling process
- If the engine function is disabled, the process of leveling up party members should be performed by script functions

----
#### set_drugs_data
`void sfall_func3("set_drugs_data", int type, int pid, int value)`
- Overrides the parameters of drugs set in the configuration file (**DrugsFile** setting in **ddraw.ini**)
- `type`:\
    0 - changes the value of **NumEffects** for the drug (see **Drugs.ini** for the description of NumEffects)\
    1 - changes the duration of the addiction effect for the drug (a value of 1 = one game minute)

----
#### set_unique_id
`int sfall_func1("set_unique_id", object obj)`\
`int sfall_func2("set_unique_id", object obj, int flag)`
- Assigns a unique ID number to the object and returns it. If a unique ID number has already been assigned to an object, then ID number is returned without reassignment
- Items with unique IDs will not stack with other items of the same type in the inventory
- To just get the current ID number of an object, use `sfall_func2("get_object_data", object, OBJ_DATA_ID)`
- Unique ID numbers are saved in your savegame, and have a range from `0x10000000` to `0x7FFFFFFF`
- There is also a unique ID number range for the player and party members from 18000 to 83535
- To assign a new ID number generated by the engine to the object (i.e. unassign a unique ID), call the function with two arguments and pass -1 for the flag argument

----
#### draw_image | draw_image_scaled
`void sfall_func5("draw_image", string/int artFile/artId, int frame, int x, int y, bool noTransparent)`\
`void sfall_func6("draw_image_scaled", string/int pathFile/artId, int frame, int x, int y, int width, int height)`
- Displays the specified PCX or FRM image in the active window created by vanilla `CreateWin` or sfall's `create_win` script function
- `artFile/artId`: path to the PCX/FRM file (e.g. `art\\inven\\5mmap.frm`), or its FRM ID number (e.g. `0x7000026`, see specification of the FID format)

**Optional arguments:**
- `frame`: frame number, the first frame starts from zero
- `x/y`: offset relative to the top-left corner of the window
- `width/height`: the new width/height to scale the image to. Pass -1 to either width or height to keep the aspect ratio when scaling
- `noTransparent`: pass True to display an image without transparent background
- __NOTE:__ to omit optional arguments starting from the right, call the functions with different sfall_funcX (e.g. `sfall_func4("draw_image", pathFile, frame, x, y)`)
- If `draw_image_scaled` is called without x/y/width/height arguments, the image will be scaled to fit the window without transparent background

----
#### set_fake_perk_npc | set_fake_trait_npc | set_selectable_perk_npc | has_fake_perk_npc | has_fake_trait_npc
`void sfall_func5("set_fake_perk_npc", object npc, string namePerk, int level, int image, string desc)`\
`void sfall_func5("set_fake_trait_npc", object npc, string nameTrait, int active, int image, string desc)`\
`void sfall_func5("set_selectable_perk_npc", object npc, string namePerk, int active, int image, string desc)`\
`int  sfall_func2("has_fake_perk_npc", object npc, string namePerk)`\
`int  sfall_func2("has_fake_trait_npc", object npc, string nameTrait)`
- These functions are similar to `has_fake_perk`, `has_fake_trait`, `set_fake_perk`, `set_fake_trait`, `set_selectable_perk`, and `set_selectable_trait` functions, but apply to the specified party member NPC (including `dude_obj`)

----
#### add_extra_msg_file
`int sfall_func1("add_extra_msg_file", string fileName)`\
`int sfall_func2("add_extra_msg_file", string fileName, int fileNumber)`
- Loads the custom message file, and returns the file ID number assigned to it in range from `0x3000` to `0x3FFF` for the `message_str_game` function to get messages from the file
- `fileName`: the name of the custom message file (including the **.msg** extension) in the `text\<language>\game\` directory
- __NOTE:__ if the msg file does not exist in the current language directory, the function will try to load it from the `text\English\game\` directory

**Optional argument:**
- `fileNumber`: the file ID number for the `message_str_game` function. The available range is from `0x2000` to `0x2FFF` (see **ExtraGameMsgFileList** setting in **ddraw.ini**). Use **fileNumber** only if you want to add a message file without editing **ddraw.ini** or existing scripts to support the old way

----
#### unwield_slot
`void sfall_func2("unwield_slot", object critter, int slot)`
- Unequips an item from the specified slot for a critter or the player
- Can take off player's equipped item when the inventory is opened, or the player is in the barter screen
- `slot`: 0 - armor slot, 1 - right slot, 2 - left slot (see `INVEN_TYPE_*` in **define.h**)

----
#### add_trait
`void sfall_func1("add_trait", int traitID)`
- Adds the specified trait to the player

----
#### get_inven_ap_cost
`int sfall_func0("get_inven_ap_cost")`
- Returns the current AP cost to access the inventory in combat

----
#### add_g_timer_event
`void sfall_func2("add_g_timer_event", int time, int fixedParam)`
- Adds a timer event that calls the `timed_event_p_proc` procedure in the current global script
- `time`: the number of ticks after which the event timer is triggered
- `fixedParam`: the value that is passed to the `timed_event_p_proc` procedure for the `fixed_param` function

----
#### remove_timer_event
`void sfall_func0("remove_timer_event")`\
`void sfall_func1("remove_timer_event", int fixedParam)`
- Clears all set timer events for the current global script
- `fixedParam`: removes all timer events with the specified value for the current global script

----
#### get_sfall_arg_at
`mixed sfall_func1("get_sfall_arg_at", int argNum)`
- Gets the value of hook argument with the specified argument number (*first argument of hook starts from 0*)

----
#### hide_window
`void sfall_func0("hide_window")`\
`void sfall_func1("hide_window", string winName)`
- Hides the specified or currently active (selected) script window
- `winName`: the window name, assigned to the window by the `CreateWin` or `create_win` function

----
#### show_window
`void sfall_func0("show_window")`\
`void sfall_func1("show_window", string winName)`
- Displays the specified hidden script window or the one previously hidden with the `sfall_func0("hide_window")` function
- `winName`: the window name, assigned to the window by the `CreateWin` or `create_win` function

----
#### set_window_flag
`void sfall_func3("set_window_flag", string/int winName/winID, int flag, bool value)`
- Changes the specified flag for the created script or game interface window
- `winName`: the window name, assigned to the window by the `CreateWin` or `create_win` function
- `winID`: the ID number of the interface or script window obtained with the `get_window_under_mouse` function, or 0 for the current game interface
- `flag`: the flag to change (see `WIN_FLAG_*` constants in **define_extra.h**)
- `value`: True - set the flag, False - unset the flag

----
#### get_text_width
`int sfall_func1("get_text_width", string text)`
- Returns the text width in pixels for the currently set font

----
#### string_compare
`bool sfall_func2("string_compare", string str1, string str2)`\
`bool sfall_func3("string_compare", string str1, string str2, int codePage)`
- Compares two strings case-insensitive, and returns True if the two strings are matched
- `codePage`: code page number to properly compare national characters in the range 128-255 of the ASCII code table. Available encodings: 1250-1252, 866

----
#### string_format
`string sfall_func2("string_format", string format, any val1)`\
`string sfall_funcX("string_format", string format, any val1, any val2, ...)`
- Formats given values using standard syntax of C `printf` function (google "printf" for format details). However, it is limited to formatting up to 7 values
- The format string is limited to 1024 characters

----
#### objects_in_radius
`array sfall_func3("objects_in_radius", int tile, int radius, int elevation)`\
`array sfall_func4("objects_in_radius", int tile, int radius, int elevation, int type)`
- Returns an array of objects of a type (see `OBJ_TYPE_*` constants in **define_extra.h**) within the specified radius from the given tile
- Passing -1 to the `type` argument or not specifying it will return all objects within the radius
- The radius is limited to 50 hexes

----
#### tile_by_position
`int sfall_func2("tile_by_position", int x, int y)`
- Returns the tile number at the x, y position relative to the top-left corner of the game screen
- If the position is outside of the range of tiles, it will return -1

----
#### string_to_case
`string sfall_func2("string_to_case", string text, int toCase)`
- Converts all letters in the given string to the specified case
- `toCase`: 0 - lowercase, 1 - uppercase
- __NOTE:__ this function works only for English letters of A-Z and a-z

----
#### set_terrain_name
`void sfall_func3("set_terrain_name", int x, int y, string name)`
- Overrides the terrain type name for the sub-tile on the world map by the specified coordinates

----
#### get_terrain_name
`string sfall_func0("get_terrain_name")`\
`string sfall_func2("get_terrain_name", int x, int y)`
- Returns the terrain type name for the sub-tile on the world map by the specified coordinates, or by the player's current position if called without arguments

----
#### get_window_attribute
`int sfall_func1("get_window_attribute", int winType)`\
`int sfall_func2("get_window_attribute", int winType, int attrType)`
- Returns the attribute of the specified interface window by the `attrType` argument
- `winType`: the type number of the interface window (see `WINTYPE_*` constants in **sfall.h**)
- `attrType:`\
    0 - checks and returns a value of 1 if the specified interface window is created by the game (same as without the argument)\
    1 - X position, 2 - Y position (relative to the top-left corner of the game screen)\
    3 - interface width size, 4 - interface height size\
    5 - window ID (to compare with the `get_window_under_mouse` function)\
    -1 - returns an associative array of keys (left, top, right, bottom) and values that define the position of the window rectangle (use standard syntax to access array values, e.g. `win.top`, `win.bottom`)
- Returns -1 if the specified attribute cannot be obtained

----
#### set_town_title
`void sfall_func2("set_town_title", int areaID, string title)`
- Sets a floating text for a town on the world map when hovering the cursor over the player's marker
- `areaID`: the ID number of the town from **city.txt**

----
#### message_box
`int sfall_func4("message_box", string message, int flags, int color1, int color2)`
- Creates a dialog box with text and returns the result of pressing the button: 0 - No (Escape), 1 - Yes/Done (Enter)
- Returns -1 if for some reason the dialog box cannot be created
- `message`: the text in the dialog box. Use the `\n` control character to move text to a new line (example: "Hello\nWorld!")

**Optional arguments:**
- `flags`: mode flags (see `MSGBOX_*` constants in **define_extra.h**). Pass -1 to skip setting the flags (default flags are `NORMAL` and `YESNO`)
- `color1/color2`: the color index in the game palette. `color1` sets the text color for the first line, and `color2` for all subsequent lines of text (default color is 145)

----
#### get_stat_min | get_stat_max
`int sfall_func1("get_stat_min", int stat)`\
`int sfall_func1("get_stat_max", int stat)`\
`int sfall_func2("get_stat_min", int stat, bool who)`\
`int sfall_func2("get_stat_max", int stat, bool who)`
- Returns the maximum or minimum set value of the specified stat (see `set_stat_min` and `set_stat_max` functions)
- `who`: 0 (False) or omitting the argument - returns the value of the player, 1 (True) - returns the value set for other critters

----
#### interface_art_draw
`int sfall_func4("interface_art_draw", int winType, string/int artFile/artId, int x, int y)`\
`int sfall_func5("interface_art_draw", int winType, string/int artFile/artId, int x, int y, int frame)`\
`int sfall_func6("interface_art_draw", int winType, string/int artFile/artId, int x, int y, int frame, array param)`
- Draws the specified PCX or FRM image in the game interface window, returns -1 on any error
- `winType`: the type number of the interface window (see `WINTYPE_*` constants in **sfall.h**). This also takes the value of the flag `0x1000000` to prevent immediate redrawing of the interface window
- `artFile/artId`: path to the PCX/FRM file (e.g. `art\\inven\\5mmap.frm`), or its FRM ID number (e.g. `0x7000026`, see specification of the FID format)
- `x/y`: offset relative to the top-left corner of the window

**Optional arguments:**
- `frame`: frame number, the first frame starts from zero
- `param`: an array which specifies additional parameters, where:\
    index 0 - sprite direction for multi-directional FRM\
    index 1/index 2 - the new width/height to scale the image to. Pass -1 to use the original width/height

----
#### interface_print
`int sfall_func5("interface_print", string text, int winType, int x, int y, int color)`\
`int sfall_func6("interface_print", string text, int winType, int x, int y, int color, int width)`
- Displays the text in the specified interface window with the current font. Use vanilla `SetFont` function to set the font
- Returns the count of lines printed, or -1 on any error
- `text`: the text to be printed. Use the `\n` control character to move text to a new line (example: "Hello\nWorld!")
- `winType`: the type number of the interface window (see `WINTYPE_*` constants in **sfall.h**)
- `x/y`: offset relative to the top-left corner of the window
- `color`: the color index in the game palette. Pass 0 if the text color was previously set by vanilla `SetTextColor` function. It can also take additional flags (via `bwor`) for displaying text:\
    `0x0010000` - adds a shadow to the text, the `textshadow` compiler constant\
    `0x1000000` - prevents immediate redrawing of the interface window, the `textdirect` compiler constant (works the other way around)\
    `0x2000000` - fills the background of the text with black color, the `textnofill` compiler constant (works the other way around)

**Optional argument:**
- `width`: the maximum width of the text. The text will be wrapped to fit within the specified width

----
#### combat_data
`mixed sfall_func0("combat_data")`
- Returns a pointer to the `C_ATTACK_*` data for the current combat attack turn (see defined constants in **define_extra.h**)
- Can be used in conjunction with the `get_object_data` and `set_object_data` functions\
  Example: `sfall_func3("set_object_data", sfall_func0("combat_data"), C_ATTACK_UNUSED, 255);`

----
#### win_fill_color
`int sfall_func0("win_fill_color")`\
`int sfall_func5("win_fill_color", int x, int y, int width, int height, int color)`
- Fills the rectangle area of the currently selected script window with the specified color, or clears the window with transparent color (use index 0 or call the function without arguments)
- `color`: the color index in the game palette (from 0 to 255)

----
#### interface_overlay
`int sfall_func2("interface_overlay", int winType, int mode)`\
`int sfall_func6("interface_overlay", int winType, 2, int x, int y, int width, int height)`
- Creates an additional drawing surface above the graphic layer of the specified interface window. All subsequent calls of `interface_art_draw` and `interface_print` functions will draw on it
- `winType`: the type number of the interface window (see `WINTYPE_*` constants in **sfall.h**)
- `mode`:\
    1 - creates a new overlay surface\
    2 - clears the overlay area or the specified rectangle defined by the x, y, width, height arguments\
    0 - destroys the created overlay surface (frees up the memory allocated to the surface)

----
#### set_quest_failure_value
`void sfall_func2("set_quest_failure_value", int gvarNumber, int thresholdValue)`
- Sets the threshold value (failure_threshold) for the quest at which the quest will be considered failed (its description in the pipboy will be crossed out and colored red)
- `gvarNumber`: the number of the global variable controlling the quest
- `thresholdValue`: the value of the global variable at which the quest is counted as a failure

----
#### set_scr_name
`void sfall_func1("set_scr_name", string name)`
- Overrides the name of the script object that was set from **scrname.msg**
- The changed name will be reset each time the player leaves the map or reloads the game
- Passing an empty string ("") to the `name` argument or omitting it will allow the game to get the name for the object from pro_*.msg files
- __NOTE:__ this function is intended for use in normal game scripts and overrides the name only once for the same object until reset

----
#### obj_is_openable
`bool sfall_func1("obj_is_openable", object obj)`
- Returns True if the object is openable (i.e. has an opening/closing animation), False otherwise

----
#### set_spray_settings
`void sfall_func4("set_spray_settings", int centerMult, int centerDiv, int targetMult, int targetDiv)`

- Allows changing the multipliers and divisors for the bullet distribution of burst attacks dynamically. All settings are automatically reset to default values (i.e. **ComputeSpray_\*** settings in **ddraw.ini**) after each attack action
- Should be called before the calculation of the bullet distribution (e.g. in `HOOK_TOHIT` or `HOOK_AMMOCOST`)
- `centerDiv/targetDiv`: the minimum value of divisor is 1
- `centerMult/targetMult`: multiplier values are capped at divisor values
- __NOTE:__ refer to the description of **ComputeSpray_\*** settings in **ddraw.ini** for details of the bullet distribution of burst attacks

----
#### get_combat_free_move
`int sfall_func0("get_combat_free_move")`

- Returns available "bonus move" points of the current critter's turn. For NPCs, this is always 0 unless changed by `set_combat_free_move`

----
#### set_combat_free_move
`void sfall_func1("set_combat_free_move", int value)`

- Allows changing "bonus move" points (yellow lights on the interface bar) that can only be used for movement, not attacking
- Can be called from `HOOK_COMBATTURN` at the start of the turn (will not work on `dude_obj`)
- Can be called from `HOOK_STDPROCEDURE` with `combat_proc` event (will work on both NPCs and `dude_obj`)

----
#### get_ini_config
`array sfall_func2("get_ini_config", string file, bool searchDB)`
- Loads a given INI file and returns a permanent array (map) where keys are section names and values are permanent sub-arrays (maps) where keys and values are strings
- `searchDB`:\
    False - searches the file in the regular file system, like with all other ini-related functions\
    True - searches the file in database (DAT) files. If not found, then it will try the regular file system
- Subsequent calls for the same file will return the same array, unless it was disposed using `free_array`

----
#### string_find
`int sfall_func2("string_find", string haystack, string needle)`\
`int sfall_func3("string_find", string haystack, string needle, int pos)`

- Returns the position of the first occurrence of a `needle` string in a `haystack` string, or -1 if not found. The first character position is 0 (zero)

**Optional argument:**
- `pos`: the position at which to start the search. If negative, it indicates a position starting from the end of the string

----
#### reg_anim_animate_and_move
`void sfall_func4("reg_anim_animate_and_move", object obj, int tile, int animID, int delay)`
- Plays the specified animation while simultaneously moving the object to the given tile
- `delay`: delay from the previous animation. A value of -1 will execute the specified animation immediately after the previous one in the sequence ends

----
#### signal_close_game
`void sfall_func0("signal_close_game")`
- Works in a similar way to vanilla function: `metarule(METARULE_SIGNAL_END_GAME, 0)`, but it will then close the game instead of only returning the player to the main menu

----
#### art_frame_data
`array sfall_func3("art_frame_data", string/int artFile/artId, int frame, int rotation)`
- Returns the dimensions of a given PCX or FRM frame as a temp array in the form **[width, height]**
- `artFile/artId`: path to the PCX/FRM file (e.g. `art\\inven\\5mmap.frm`), or its FRM ID number (e.g. `0x7000026`, see specification of the FID format)

**Optional arguments:**
- `frame`: frame number, the first frame starts from zero
- `rotation`: rotation to get the frame for, useful when reading FRM files by path

----
#### set_worldmap_heal_time
`void sfall_func1("set_worldmap_heal_time", int minutes)`
- Sets the time interval in minutes for healing during world map travel. The default is 180
- Passing 0 will revert to 1 second of real time (vanilla engine behavior)
- Passing -1 will disable healing during travel
- The time interval will be reset each time the player reloads the game


****
_See other documentation files (arrays.md, hookscripts.md) for related functions reference._
