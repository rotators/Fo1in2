/*

   Junktown Casino

*/

#pragma once

/************************************************
    Generic Defines
************************************************/

//MAP_GLOBAL_VARS:

//GLOBAL                                        NUMBER
// timed event params

//==================================================================

// All Map Vars need to start w/ MVAR_
#define MVAR_Sinthia_dead                     (0)  // Tells if Sinthia was killed.
#define MVAR_raider_status                    (1)  // Tells if the crazed raider was killed.
#define MVAR_helped_Killian                   (2)  // Tells if the dude helped fight Kenji.
#define MVAR_save_da_ho                       (3)  // Tracks progress of Sinthia/raider adventure.
#define MVAR_Sinthia_award                    (4)  // Tells if dude has been given exp. for saving Sinthia.
#define MVAR_assassin_seed                    (5)  // Tracks status of Kenji's hit on Killian for Gizmo.
#define MVAR_got_Gizmo                        (6)  // Tells if dude got a confession from Gimzo to Killian.
#define MVAR_hodiction                        (7)  // TRUE if the dude is addicted to Sinthia.
#define MVAR_dude_messing_with_Killians_door  (8)  // TRUE if dude picks Killian's door. // Replaced with timer event
#define MVAR_dude_messing_with_Killians_home  (9)  // TRUE if dude picks Killian's home door. // Used in KILLSAFE.ssl
#define MVAR_Invasion                         (10) // Has the town been invaded?

