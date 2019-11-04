/*

    General Vault 13 header
    Used to track quest states and stuff.

*/

#ifndef VAULT13_H
#define VAULT13_H

/************************************************
    Generic Defines
************************************************/

#define fixt_PickDeadBodyType 	   variable id := 11; 									\
								   id := random(0, 6) + random(0, 6) + random(0, 6); 	\
								   if id <= 2 then begin 								\
									  DeathType := ANIM_exploded_to_nothing_sf;			\
								   end 													\
								   else if id <= 10 then begin 							\
									  DeathType := ANIM_burned_to_nothing_sf;			\
								   end 													\
								   else if id <= 15 then begin 							\
									  DeathType := ANIM_melted_to_nothing_sf;			\
								   end 													\
								   else 												\
									  DeathType := ANIM_fall_front_blood_sf				\

#endif // VAULT13_H




