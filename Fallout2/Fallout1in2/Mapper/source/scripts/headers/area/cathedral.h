/*

    General Cathedral / Master's Lair header
    Used to track quest states and stuff.

*/

#pragma once

/************************************************
    Generic Defines
************************************************/

// Cathedral invaders
#define FOLINVAD_FLOAT_Entrance     bit_1
#define FOLINVAD_FLOAT_Vault        bit_2
#define FOLINVAD_FLOAT_Master       bit_3
#define FOLINVAD_FLOAT_Exit         bit_4
#define BROINVAD_FLOAT_Room         bit_5
#define BROINVAD_FLOAT_Master       bit_6

#define set_invad_status(x)         set_gvar_bit_on(GVAR_CATHEDRAL_INVADER_STATES, x)
#define invad_status(x)             (gvar_bit(GVAR_CATHEDRAL_INVADER_STATES, x))

// For Master's Lair hidden door
// We use this because the autodoor script would still try to make the player run through the door (but fail)
// Creating / deleting the blockers hides the fact there is a door in the wall.
#define create_blocker     if is_visible(J_Door_Ptr) and not(tile_contains_pid_obj(tile_num(J_Door_Ptr), 0, PID_BLOCKING_HEX)) then begin \
                              Scenery_Creation := create_object(PID_BLOCKING_HEX, self_tile, self_elevation); \
                           end \
                           noop

#define delete_blocker     Scenery_Creation_Ptr := tile_contains_pid_obj(tile_num(J_Door_Ptr), 0, PID_BLOCKING_HEX); \
                           destroy_object(Scenery_Creation_Ptr)

#define set_blocker_state \
   if ((obj_is_open(J_Door_Ptr) == false) and (map_var(MVAR_SECRET_DOOR) == 0)) then begin  \
      create_blocker;                                 \
   end                                                \
   else begin                                         \
      delete_blocker;                                 \
   end                                                \
   noop
