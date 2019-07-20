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

//MAP_GLOBAL_VARS:

//GLOBAL                                        NUMBER
// timed event params

//==================================================================

// All Map Vars need to start w/ MVAR_


#endif // MAPNECRO_H