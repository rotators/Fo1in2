/*

   Vault 13 header

*/

#ifndef MAPVAULT13_H
#define MAPVAULT13_H

/************************************************
    Generic Defines
************************************************/

//MAP_GLOBAL_VARS:

//GLOBAL                                        NUMBER
// timed event params

//==================================================================

// All Map Vars need to start w/ MVAR_
#define MVAR_SecDoor_open         (0) // NOT USED
#define MVAR_armory_access        (1) // convinced Security Officer to open door
#define MVAR_revolting            (2) // Rebels still around and/or pissed
#define MVAR_traitor              (3) // Water Thief
#define MVAR_MAP_INIT             (4) // has map init run
#define MVAR_rebels_leave_date    (5) // ignored
#define MVAR_INVADED              (6) // Has map been invaded by mutant invasion

#endif // MAPVAULT13_H
