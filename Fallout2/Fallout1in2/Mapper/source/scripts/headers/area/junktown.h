/*

    General Junktown header
    Used to track quest states.

*/

#ifndef JUNKTOWN_H
#define JUNKTOWN_H

/************************************************
    Generic Defines
************************************************/
#define gizmo_hex                   (16523)

#define set_gizmo_remains_timer     if (global_var(GVAR_GIZMO_REMAINS_TIMER) == 0) then set_global_var(GVAR_GIZMO_REMAINS_TIMER, game_time)

#define gizmo_remains_rotting       (game_time > (global_var(GVAR_GIZMO_REMAINS_TIMER) + (ONE_GAME_DAY * corpse_timer)))
#define gizmo_remains_empty_desk    (game_time > (global_var(GVAR_GIZMO_REMAINS_TIMER) + (ONE_GAME_DAY * (corpse_timer * 2))))

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

#endif // JUNKTOWN_H




