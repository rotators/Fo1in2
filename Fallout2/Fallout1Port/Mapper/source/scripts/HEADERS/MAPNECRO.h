/*

	Necropolis header
	
*/

#ifndef MAPNECRO_H
#define MAPNECRO_H

/************************************************
    Generic Defines
************************************************/

#define check_manhole					if (tile_contains_obj_pid(self_tile,self_elevation,PID_SEWER_COVER)) then begin \
											cover_state := (obj_is_open(Cover_Ptr)); \
											if cover_state == 0 then begin \
												script_overrides; \
												display_msg(message_str(SCRIPT_NHUP2DN1,100)); \
											end \
											else begin \
												call move_elevation; \
											end \
										end \
										else begin \
											call move_elevation; \
										end \
										
										
#define check_watershed_sm_killed 		if (global_var(SUPER_MUTANTS_KILLED) >= global_var(MAX_MUTANTS)) then begin \
											set_global_var(PLAYER_REPUTATION_GENERAL, global_var(PLAYER_REPUTATION_GENERAL) + 3); \
											set_global_var(NECROP_MUTANTS_KILLED, 2); \
											if (global_var(GVAR_NECROPOLIS_INVADED_DATE) == 110) and get_necropolis_days_left > 30 then begin \
												set_global_var(GVAR_NECROPOLIS_INVADED_DATE, ((game_time / ONE_GAME_DAY) + 30)); \
											end \
										end

//MAP_GLOBAL_VARS:

//GLOBAL                                        NUMBER
// timed event params

//==================================================================

// All Map Vars need to start w/ MVAR_


#endif // MAPNECRO_H