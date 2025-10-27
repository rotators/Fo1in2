/*

    General Junktown header
    Used to track quest states.

*/

#pragma once

/************************************************
    Generic Defines
************************************************/
// Killian
#define shop_open_time                    (650)
#define shop_closed_time                  (1900)
#define darkwaters_shop_open              (game_time_hour > shop_open_time and game_time_hour < shop_closed_time)

#define quest_capture_gizmo_inactiv       (global_var(GVAR_CAPTURE_GIZMO) == 0)
#define quest_capture_gizmo_active        (global_var(GVAR_CAPTURE_GIZMO) == 1)
#define quest_capture_gizmo_completed     (global_var(GVAR_CAPTURE_GIZMO) == 2)

#define set_quest_capture_gizmo_active    set_global_var(GVAR_CAPTURE_GIZMO, 1)
#define set_quest_capture_gizmo_completed set_global_var(GVAR_CAPTURE_GIZMO, 2)


// Gizmo
#define gizmo_hex                         (16523)

#define set_gizmo_remains_timer           if (global_var(GVAR_GIZMO_REMAINS_TIMER) == 0) then set_global_var(GVAR_GIZMO_REMAINS_TIMER, game_time)

#define gizmo_remains_rotting             (game_time > (global_var(GVAR_GIZMO_REMAINS_TIMER) + (ONE_GAME_DAY * corpse_timer)))
#define gizmo_remains_empty_desk          (game_time > (global_var(GVAR_GIZMO_REMAINS_TIMER) + (ONE_GAME_DAY * (corpse_timer * 2))))

#define set_quest_kill_killian_active      set_global_var(GVAR_KILL_KILLIAN, 1)
#define set_quest_kill_killian_completed   set_global_var(GVAR_KILL_KILLIAN, 2)
#define set_quest_kill_killian_canceled    set_global_var(GVAR_KILL_KILLIAN, 3)

#define quest_kill_killian_inactiv        (global_var(GVAR_KILL_KILLIAN) == 0)
#define quest_kill_killian_active         (global_var(GVAR_KILL_KILLIAN) == 1)
#define quest_kill_killian_completed      (global_var(GVAR_KILL_KILLIAN) == 2)
#define quest_kill_killian_canceled       (global_var(GVAR_KILL_KILLIAN) == 3)

// Skum Pitt:
#define check_noise_hex    (19274)



// Skullz:
#define quest_join_skullz_inactive        (global_var(GVAR_JOIN_SKULLZ) == 0)
#define quest_join_skullz_active          (global_var(GVAR_JOIN_SKULLZ) == 1)
#define quest_join_skullz_completed       (global_var(GVAR_JOIN_SKULLZ) == 2)

#define set_quest_join_skullz_active      set_global_var(GVAR_JOIN_SKULLZ, 1)
#define set_quest_join_skullz_completed   if quest_join_skullz_active then set_global_var(GVAR_JOIN_SKULLZ, 2)

// Trish and Saul quest:
#define DUDE_KNOWS_TRISH                  bit_1
#define TRISH_SCREAMED_SAUL               bit_2
#define TRISH_TALKED_ABOUT_SAUL           bit_3
#define DUDE_TALKED_WITH_TRISH            bit_4
#define SAUL_CARES                        bit_5
#define TRISH_CONCERNED                   bit_6
#define TRISH_UNDERSTANDS_SAUL            bit_8
#define SAUL_UNDERSTANDS_TRISH            bit_16
#define TRISH_IS_DEAD                     bit_31 // was 64 in Fo1
#define RELATIONSHIP_SAVED                bit_32

#define set_trish_state(x)                set_gvar_bit_on(GVAR_TRISH_STATUS, x)
#define get_trish_state(x)                (gvar_bit(GVAR_TRISH_STATUS, x))

#define saul_is_dead                      (global_var(GVAR_SAUL_STATUS) == 3)
#define set_saul_is_dead                  set_global_var(GVAR_SAUL_STATUS, 3)

#define saul_mentioned_trish              (global_var(GVAR_SAUL_STATUS) == 2)
#define set_saul_mentioned_trish          set_global_var(GVAR_SAUL_STATUS, 2)

#define check_relationship_saved \
   if (not(get_trish_state(RELATIONSHIP_SAVED)) and get_trish_state(TRISH_UNDERSTANDS_SAUL) and get_trish_state(SAUL_UNDERSTANDS_TRISH)) then begin \
      set_trish_state(RELATIONSHIP_SAVED);                                       \
      inc_general_rep(2);                                                        \
      inc_junktown_rep(REP_BONUS_HELPED_TRISH_AND_SAUL);                         \
      give_xp_msg(EXP_TRISH_SAUL_RELATIONSHIP, message_str(SCRIPT_TRISH, 204));  \
   end                                                                           \
   noop

#define dog_is_angry                      (map_var(MVAR_dog_is_angry) != 0)
#define dog_is_killed                     (global_var(GVAR_DOGMEAT_KILLED))
