/*

   Military Base Entrance

*/

#ifndef MAPMBENT_H
#define MAPMBENT_H

/************************************************
    Generic Defines
************************************************/

//MAP_GLOBAL_VARS:

//GLOBAL                                        NUMBER
// timed event params

//==================================================================

// All Map Vars need to start w/ MVAR_
#define MVAR_radio_trick          (0) // Tells if the gate guards have been tricked with the radio.
#define MVAR_know_door_code       (1) // TRUE if dude knows the electronic code to the Military Base door.
#define MVAR_radio_used_at_entry  (2) // TRUE if radio used on entrance map.
#define MVAR_MBDoor_ptr           (3) // Pointer to Military Base door.
#define MVAR_ignoring_dude        (4) // Mutants ignoring Dude
#define MVAR_UNKNOWN_VAR_0        (5) // According to F12se this is actually used???
#define MVAR_UNKNOWN_VAR_1        (6) // According to F12se this is actually used???
#define MVAR_BOS_FLOAT          (7) // Only one soldier will float welcome

#endif // MAPMBENT_H
