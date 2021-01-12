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
                                        end                                                                                       \
                                        noop

// Super Mutants are leaving after the Vats are destroyed
#define sm_wp_1         (13128)
#define sm_wp_2         (10162)

#define sm_leave_watershed \
   if ((global_var(GVAR_WATERSHED_MUTANTS_LEAVE) == 1) and (self_tile != sm_wp_1)) then               \
      self_walk_to_tile(sm_wp_1);                                                                     \
   else if ((global_var(GVAR_WATERSHED_MUTANTS_LEAVE) == 1) and (self_tile == sm_wp_1)) then          \
      set_global_var(GVAR_WATERSHED_MUTANTS_LEAVE, 2);                                                \
   else if ((global_var(GVAR_WATERSHED_MUTANTS_LEAVE) == 2) and (self_tile != sm_wp_2)) then          \
      self_walk_to_tile(sm_wp_2);                                                                     \
   else if ((self_tile == sm_wp_2) and (global_var(GVAR_WATERSHED_MUTANTS_LEAVE) == 2)) then begin    \
      if not(is_loading_game) then set_self_invisible;                                                \
   end                                                                                                \
   noop


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

/************************************************
    Sewer King / Motorcycle quest
************************************************/
#define SEWER_POS_WATRSHED    (20321)
#define SEWER_POS_HOTEL       (19943)
#define SEWER_POS_HALLDED     (18666)

procedure spawn_sewer_king begin
variable Critter,
         Critter_spawn_hex := global_var(GVAR_SEWER_KING_POS),
         Critter_tile,
         rats := 4,
         Item;

   Critter := create_object_sid(PID_ZOMBIE_GUARD, 0, 0, SCRIPT_GRIFFITH);
   critter_attempt_placement(Critter, Critter_spawn_hex, 0);
   anim(Critter, ANIMATE_ROTATION, random(0, 5));
   Item := create_object(PID_WAKIZASHI_BLADE, 0, 0);
   add_obj_to_inven(Critter, Item);
   Item := create_object(PID_MOTO_KEY, 0, 0);
   add_obj_to_inven(Critter, Item);
   Item := create_object(PID_SMALL_ENERGY_CELL, 0, 0);
   add_obj_to_inven(Critter, Item);
   item_caps_adjust(Critter, random(10, 40));
   kill_critter(Critter, ANIM_chunks_of_flesh_sf);

   Critter := create_object_sid(PID_SEWER_KING, 0, 0, SCRIPT_NKINGRAT);
   critter_attempt_placement(Critter, Critter_spawn_hex, 0);
   anim(Critter, ANIMATE_ROTATION, random(0, 5));

   while(rats) do begin
      Critter_tile := tile_num_in_direction(Critter_spawn_hex, random(0, 5), random(2,5));
      Critter := create_object_sid(PID_TOUGH_RADIATED_RAT, 0, 0, SCRIPT_NKINGRAT);
      critter_attempt_placement(Critter, Critter_spawn_hex, 0);
      anim(Critter, ANIMATE_ROTATION, random(0, 5));
      rats := rats - 1;
   end

   set_global_var(GVAR_SEWER_KING_POS, -1);
end

#endif // MAPNECRO_H
