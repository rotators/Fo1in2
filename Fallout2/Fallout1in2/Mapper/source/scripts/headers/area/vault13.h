/*

    General Vault 13 header
    Used to track quest states and stuff.

*/

#pragma once

/************************************************
    Generic Defines
************************************************/

#define waterthief_not_started              (not(global_var(GVAR_QUEST_VAULT13_5_WTR_THIEF)))
#define waterthief_started                  (global_var(GVAR_QUEST_VAULT13_5_WTR_THIEF) == 1)
#define set_waterthief_started              set_global_var(GVAR_QUEST_VAULT13_5_WTR_THIEF, 1)
#define waterthief_captured                 (global_var(GVAR_QUEST_VAULT13_5_WTR_THIEF) == 2)
#define set_waterthief_captured             set_global_var(GVAR_QUEST_VAULT13_5_WTR_THIEF, 2)

// Water rations scene
#define EVENT_WaterRation  (4)

// Changed condition from GVAR_QUEST_VAULT13_4_WATERCHIP == 0 to days-check, because it would be false if the player has send water from the water merchants once.
#define water_rations \
   if (not(waterchip_returned) and (get_water_days_left < 90))  then begin          \
      if (local_var(LVAR_WaterRations) == 0) then begin                             \
         if ((self_elevation == elevation(WtrGrd_ptr)) and (self_elevation == dude_elevation)) then begin \
            if ((game_time_hour > 700) and (game_time_hour < 900)) then begin       \
               call get_rations;                                                    \
            end                                                                     \
         end                                                                        \
      end                                                                           \
      flush_add_timer_event(self_obj, game_ticks(random(1,5)), EVENT_WaterRation);  \
   end                                                                              \
   noop

// Use Vault door
#define toggle_v13_door    if obj_is_open(vault_door_ptr) then begin \
                              obj_close(vault_door_ptr);             \
                              obj_lock(vault_door_ptr);              \
                           end                                       \
                           else begin                                \
                              obj_unlock(vault_door_ptr);            \
                              obj_open(vault_door_ptr);              \
                           end

// Fixt uses different code in V13. Maybe it can / should be consolidated with fo1.h define.
#define invasion_kill_critter_V13   variable DeathType;                             \
                                    variable id := random(0, 18);                   \
                                    if id <= 2 then begin                           \
                                        DeathType := ANIM_exploded_to_nothing_sf;   \
                                    end                                             \
                                    else if id <= 10 then begin                     \
                                        DeathType := ANIM_burned_to_nothing_sf;     \
                                    end                                             \
                                    else if id <= 15 then begin                     \
                                        DeathType := ANIM_melted_to_nothing_sf;     \
                                    end                                             \
                                    else begin                                      \
                                        DeathType := ANIM_fall_front_blood_sf;      \
                                    end                                             \
                                    kill_critter(self_obj, DeathType)
