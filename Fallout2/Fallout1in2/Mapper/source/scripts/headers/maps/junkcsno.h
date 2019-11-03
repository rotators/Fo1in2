/*

   Junktown Casino

*/

#ifndef MAPJUNKCAS_H
#define MAPJUNKCAS_H

/************************************************
    Generic Defines
************************************************/

//MAP_GLOBAL_VARS:

//GLOBAL                                        NUMBER
// timed event params

//==================================================================

// All Map Vars need to start w/ MVAR_
#define MVAR_Skulz_left             (0)  // Skulz left in battle at the Skum Pitt.
#define MVAR_guards_left            (1)  // Guards left in battle at the Skum Pitt.
#define MVAR_bar_fight              (2)  // Tells if everyone is set up for killing Neal.
#define MVAR_exp_for_killing_Gizmo  (3)  // Set to TRUE once the dude gets exp for killing Gizmo.
#define MVAR_caught_stealing_urn    (4)  // Set to TRUE if the dude is caught stealing Neal's urn.
#define MVAR_dog_is_angry           (5)  // TRUE if Dogmeat is still angry at Phil.
#define MVAR_smartass_1             (6)  // Flag for Lenore's smartass remarks.
#define MVAR_smartass_2             (7)  // Flag for Lenore's smartass remarks.
#define MVAR_Phil_approaches        (8)  // TRUE if Phil approaches his house.
#define MVAR_growling               (9)  // TRUE if Dogmeat is growling at Phil.
#define MVAR_initialized_bar_fight  (10) // TRUE if bar fight is set up.
#define MVAR_Invasion               (11) // Has this map been invaded by Super Mutants?
#define MVAR_SkumPitt_Noisy         (12) // Has the player been caught breaking into the Skum Pitt?

#endif // MAPJUNKCAS_H
