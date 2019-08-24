/*
	Copyright 1998-2003 Interplay Entertainment Corp.  All rights reserved.
*/

#ifndef ARCAVES_H
#define ARCAVES_H


#define teleport_back      play_sfx("uranium");                   \
                           gfade_out(600);                        \
                           load_map(MAP_GUARDIAN,10);             \
                           anim( dude_obj, ANIMATE_ROTATION, 5 ); \
                           gfade_in(600)
 

 // Comments

//MAP_GLOBAL_VARS:

//GLOBAL                                        NUMBER

// All Map Vars need to start w/ MVAR_

#define MVAR_Arroyo_Trial_Spear00               (0)
#define MVAR_Arroyo_Trial_Spear01               (1)
#define MVAR_Arroyo_Trial_Spear02               (2)
#define MVAR_Arroyo_Trial_Spear03               (3)
#define MVAR_Arroyo_Trial_Spear04               (4)
#define MVAR_Arroyo_Trial_Spear05               (5)
#define MVAR_Arroyo_Trial_Spear06               (6)
#define MVAR_Arroyo_Trial_Spear07               (7)
#define MVAR_Arroyo_Trial_Spear08               (8)
#define MVAR_Arroyo_Trial_Spear09               (9)
#define MVAR_Arroyo_Trial_Spear10               (10)
#define MVAR_Arroyo_Trial_Spear11               (11)
#define MVAR_Arroyo_Trial_Spear12               (12)
#define MVAR_Arroyo_Trial_Spear13               (13)
#define MVAR_Arroyo_Trial_Spear14               (14)
#define MVAR_Arroyo_Trial_Spear15               (15)
#define MVAR_Arroyo_Trial_Spear16               (16)
#define MVAR_Arroyo_Trial_Spear17               (17)
#define MVAR_Arroyo_Trial_Spear18               (18)
#define MVAR_Arroyo_Trial_Spear19               (19)
#define MVAR_Passed_Fighting                    (20)


#endif // ARCAVES_H
