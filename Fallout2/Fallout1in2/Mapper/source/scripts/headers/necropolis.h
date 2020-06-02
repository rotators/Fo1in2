/*

    Necropolis header

*/

#ifndef MAPNECRO_H
#define MAPNECRO_H

/************************************************
    Generic Defines
************************************************/
#define check_manhole   if (tile_contains_obj_pid(self_tile,self_elevation,PID_SEWER_COVER)) then begin \
                            cover_state := (obj_is_open(Cover_Ptr));                                    \
                            if (cover_state == 0) then begin                                            \
                                script_overrides;                                                       \
                                /*display_msg(message_str(SCRIPT_NHUP2DN1,100));*/                      \
                                obj_open(Cover_Ptr);                                                    \
                            end                                                                         \
                            else begin                                                                  \
                                call move_elevation;                                                    \
                            end                                                                         \
                        end                                                                             \
                        else begin                                                                      \
                            call move_elevation;                                                        \
                        end

// Quests
#define set_waterpump_fixed            set_global_var(GVAR_NECROP_WATER_PUMP_FIXED, 2)

// Player has killed Harry & friends
#define check_watershed_sm_killed       if (global_var(GVAR_SUPER_MUTANTS_KILLED) >= global_var(GVAR_MAX_MUTANTS)) then begin     \
                                            set_global_var(GVAR_PLAYER_REPUTATION, global_var(GVAR_PLAYER_REPUTATION) + 3);       \
                                            set_global_var(GVAR_NECROP_MUTANTS_KILLED, 2);                                        \
                                            inc_necropolis_rep(REP_BONUS_WATERSHED_MUTANTS_DEAD);                                 \
                                            if (get_necropolis_days_left > 30 and get_necropolis_days_left < 10000) then begin    \
                                                set_global_var(GVAR_NECROPOLIS_INVASION_DAYS, ((game_time / ONE_GAME_DAY) + 30)); \
                                            end                                                                                   \
                                        end

// Car related defines
#define set_car_used_first_time         if (global_var(GVAR_QUEST_MOTORCYCLE) < 20) then \
                                        set_global_var(GVAR_QUEST_MOTORCYCLE,20)
#define get_car_used                    (global_var(GVAR_QUEST_MOTORCYCLE) >= 20)
#define Place_Trunk(Hex,Elevation)      if get_car_used then begin                                          \
                                            if (global_var(GVAR_PLAYER_GOT_CAR) == 1) then begin            \
                                                tile:=tile_num_in_direction(Hex,1,1);                       \
                                            end else if (global_var(GVAR_PLAYER_GOT_CAR) == 2) then begin   \
                                                tile:=Hex+2;                                                \
                                            end                                                             \
                                            move_to(Trunk_Ptr,tile,Elevation);                              \
                                        end
#define set_trunk_visible               if get_car_used then set_obj_visibility(Trunk_Ptr,0)
#define set_trunk_invisible             if get_car_used then set_obj_visibility(Trunk_Ptr,1)

// Find the fuel cell controler without Griffith:
#define STATE_HIDDEN             0
#define STATE_SPOTTED            1
#define STATE_TAKEN_DUDE         2
#define STATE_TAKEN_GRIFFITH     3

/************************************************
    "Tell Me About"-Defines
************************************************/
#define set_tma_necropolis    if CUR_MAP_HALLDED then begin             \
                                 set_tma_data_generic(TMA_MSG_HALLDED); \
                              end                                       \
                              else if CUR_MAP_WATRSHD then begin        \
                                 set_tma_data_generic(TMA_MSG_WATRSHD); \
                              end                                       \
                              else if CUR_MAP_HOTEL then begin          \
                                 set_tma_data_generic(TMA_MSG_HOTEL);   \
                              end

#endif // MAPNECRO_H
