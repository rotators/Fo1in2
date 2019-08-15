/*

	General Boneyard header
	Used to track quest states.

*/

#ifndef BONEYARD_H
#define BONEYARD_H

/************************************************
    Generic Defines
************************************************/

//--- Gun Runners:
#define set_quest_kill_deathclaws 		set_global_var(GVAR_GUN_RUNNERS_STATUS, 9201)
#define get_quest_kill_deathclaws		(global_var(GVAR_GUN_RUNNERS_STATUS) == 9201)

#define set_all_deathclaws_killed		set_global_var(GVAR_WATER_CHIP_8, 9250)
#define get_all_deathclaws_killed 		(global_var(GVAR_WATER_CHIP_8) == 9250)

#define set_gunrunners_armed_blades 	set_global_var(GVAR_GUN_RUNNERS_STATUS, 9202)
#define get_gunrunners_armed_blades		(global_var(GVAR_GUN_RUNNERS_STATUS) == 9202)

#define set_gunrunners_armed_dude	 	set_global_var(GVAR_WATER_CHIP_8, 2)
#define get_gunrunners_armed_dude	 	(global_var(GVAR_WATER_CHIP_8) == 2)

//--- Blades:
#define set_arming_blades				set_global_var(GVAR_BLADES_STATUS, 9101)
#define get_arming_blades 	 			global_var( GVAR_BLADES_STATUS ) == 9101

// Player talks to Zimmermann first:
#define set_blades_attacking_wait		set_global_var(GVAR_BLADES_STATUS, 9102)
#define get_blades_attacking_wait		(global_var(GVAR_BLADES_STATUS) == 9102)

#define set_blades_attacking			set_global_var(GVAR_BLADES_STATUS, 9103)
#define get_blades_attacking			(global_var(GVAR_BLADES_STATUS) == 9103)

// Player declines to attack with them:
#define set_blades_attacking_alone		set_global_var(GVAR_BLADES_STATUS, 9104)
#define get_blades_attacking_alone		(global_var(GVAR_BLADES_STATUS) == 9104)

//--- Zimmermann:
#define set_task_kill_razor				set_global_var(GVAR_ZIMMERMAN_STATUS, 9001)
#define get_task_kill_razor 			(global_var(GVAR_ZIMMERMAN_STATUS) == 9001)

#define set_razor_killed				set_global_var(GVAR_ZIMMERMAN_STATUS, 9002)
#define get_razor_killed 				(global_var(GVAR_ZIMMERMAN_STATUS) == 9002)

#define set_zimmermann_turned			set_global_var(GVAR_ZIMMERMAN_STATUS, 9003)
#define get_zimmermann_turned 			(global_var(GVAR_ZIMMERMAN_STATUS) == 9003)

// Generic dialog stuff:
#define set_zimmermann_insulted 		set_global_var(GVAR_ZIMMERMAN_STATUS, 1)
#define get_zimmermann_insulted 		(global_var(GVAR_ZIMMERMAN_STATUS) == 1)

#endif // MAPLABLADES_H




