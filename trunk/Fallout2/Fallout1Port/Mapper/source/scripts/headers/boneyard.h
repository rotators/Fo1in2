/*

	General Boneyard header
	Used to track quest states.

*/

#ifndef BONEYARD_H
#define BONEYARD_H

/************************************************
    Generic Defines
************************************************/

#define set_quest_kill_deathclaws 		set_global_var(GVAR_GUN_RUNNERS_STATUS, 9201)
#define get_quest_kill_deathclaws		(global_var(GVAR_GUN_RUNNERS_STATUS) == 9201)

#define get_arming_blades 	 			global_var( GVAR_BLADES_STATUS ) == 9101

#define set_all_deathclaws_killed		set_global_var(GVAR_WATER_CHIP_8, 9250)
#define get_all_deathclaws_killed 		(global_var(GVAR_WATER_CHIP_8) == 9250)

#define set_gunrunners_armed_blades 	set_global_var(GVAR_GUN_RUNNERS_STATUS, 9202)
#define get_gunrunners_armed_blades		(global_var(GVAR_GUN_RUNNERS_STATUS) == 9202)

#define set_gunrunners_armed_dude	 	set_global_var(GVAR_WATER_CHIP_8, 2)
#define get_gunrunners_armed_dude	 	(global_var(GVAR_WATER_CHIP_8) == 2)

#define set_blades_attacking_wait		set_global_var(GVAR_BLADES_STATUS, 9102)
#define get_blades_attacking_wait		(global_var(GVAR_BLADES_STATUS) == 9102)

#define set_blades_attacking			set_global_var(GVAR_BLADES_STATUS, 9103)
#define get_blades_attacking			(global_var(GVAR_BLADES_STATUS) == 9103)

#define set_blades_attacking_alone		set_global_var(GVAR_BLADES_STATUS, 9104)
#define get_blades_attacking_alone		(global_var(GVAR_BLADES_STATUS) == 9104)

#define get_zimmermann_turned 			(global_var(GVAR_ZIMMERMAN_STATUS) == 9003)
#define set_zimmermann_turned			set_global_var(GVAR_ZIMMERMAN_STATUS, 9003)

#define set_zimmermann_insulted 		set_global_var(GVAR_ZIMMERMAN_STATUS, 1)
#define get_zimmermann_insulted 		(global_var(GVAR_ZIMMERMAN_STATUS) == 1)

// Blades attacking
#define start_blades_invasion 			if (map_var(MVAR_AddedBlades) == 0) then begin			\
											set_map_var(MVAR_AddedBlades, 1); 					\
											critter_attempt_placement(InBladePtr1, 9702, 0); 	\
											critter_attempt_placement(InBladePtr2, 9700, 0); 	\
											critter_attempt_placement(InBladePtr3, 9698, 0); 	\
											critter_attempt_placement(InBladePtr4, 9895, 0); 	\
											critter_attempt_placement(InBladePtr5, 9696, 0); 	\
											critter_attempt_placement(InBladePtr6, 26717, 0); 	\
											critter_attempt_placement(InBladePtr7, 26711, 0);	\
											critter_attempt_placement(InBladePtr8, 24492, 0);	\
											gfade_in(1);										\
										end

#endif // MAPLABLADES_H




