/*

    The Glow defines

*/

#pragma once

/************************************************
    Generic Defines
************************************************/
#define glow_power_offline          (global_var(GVAR_GLOW_POWER) == 0)
#define glow_power_emergency        (global_var(GVAR_GLOW_POWER) == 1)
#define glow_power_online           (global_var(GVAR_GLOW_POWER) == 2)

#define set_glow_power_offline      set_global_var(GVAR_GLOW_POWER, 0)
#define set_glow_power_emergency    set_global_var(GVAR_GLOW_POWER, 1)
#define set_glow_power_online       set_global_var(GVAR_GLOW_POWER, 2)

#define glow_quest_power_restored      (global_var(GVAR_QUEST_GLOW_2_START_POWER) == 2)
#define set_glow_quest_power_restored  set_global_var(GVAR_QUEST_GLOW_2_START_POWER, 2)

#define glow_traps_active           (global_var(GVAR_QUEST_GLOW_1_TRAPS_OFF) == 0)
#define glow_traps_inactive         (global_var(GVAR_QUEST_GLOW_1_TRAPS_OFF) == 1)

#define set_glow_taps_active        set_global_var(GVAR_QUEST_GLOW_1_TRAPS_OFF, 0)
#define set_glow_taps_inactive      set_global_var(GVAR_QUEST_GLOW_1_TRAPS_OFF, 1)

#define glow_weapons_locked         (global_var(GVAR_WEAPON_LOCKER) == 1)
#define glow_weapons_unlocked       (global_var(GVAR_WEAPON_LOCKER) == 2)

#define set_glow_weapons_locked     set_global_var(GVAR_WEAPON_LOCKER, 1)
#define set_glow_weapons_unlocked   set_global_var(GVAR_WEAPON_LOCKER, 2)

// Using Keycards on doors and lockers:
#define play_sfx_doorcard   if (random(0,1) == 1) then    \
                                play_sfx("SLDOORSA");     \
                            else                          \
                                play_sfx("SLDOORSB")

#define play_sfx_doorfail   if (random(0,1) == 1) then    \
                                play_sfx("SNDOORSA");     \
                            else                          \
                                play_sfx("SNDOORSB")
