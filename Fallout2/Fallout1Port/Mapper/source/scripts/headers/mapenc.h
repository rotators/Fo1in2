/*

	Generic Encounters

*/

#ifndef MAPENC_H
#define MAPENC_H

/************************************************
    Generic Defines
************************************************/

// All Map Vars need to start w/ MVAR_
#define MVAR_Hostile_Total             	(0)   // Number of monsters created
#define MVAR_CARVN_LEAD 				(1)

//==================================================================
#define spawn_dead_critter(x,y,z)		Critter_type := x; 					\
										Critter_script := y;				\
										Critter_direction := random(0, 5); 	\
										call Place_critter; 				\
										anim(Critter, 1000, random(0, 5)); 	\
										kill_critter(Critter, z)
										
#define enc_group_angle(x) 			if (group_angle == 0) then begin 		\
										x := 3;								\
									end										\
									else if (group_angle == 1) then begin	\
										x := 4;								\
									end										\
									else if (group_angle == 2) then begin	\
										x := 5;								\
									end										\
									else if (group_angle == 3) then begin	\
										x := 0;								\
									end										\
									else if (group_angle == 4) then begin	\
										x := 1;								\
									end										\
									else if (group_angle == 5) then begin	\
										x := 2;								\
									end



#endif // MAPENC_H
