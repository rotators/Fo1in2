/*

   Vault 13 Cavern

*/

#ifndef MAPV13ENT_H
#define MAPV13ENT_H

/************************************************
    Generic Defines
************************************************/

//MAP_GLOBAL_VARS:

//GLOBAL                                        NUMBER
// timed event params

//==================================================================

// All Map Vars need to start w/ MVAR_
#define MVAR_Overseer_ptr           (0)  // Referenced pointer to the Overseer, endgame
#define MVAR_Door_Blown             (1)  // Has door computer been destroyed (makes door stay open)
#define MVAR_INVADED                (2)  // Has map been invaded

#endif // MAPV13ENT_H
