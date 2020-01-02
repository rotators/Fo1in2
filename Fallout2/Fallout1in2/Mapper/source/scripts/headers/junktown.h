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
#define quest_join_skullz_inactive       (global_var(GVAR_JOIN_SKULLZ) == 0)
#define quest_join_skullz_active         (global_var(GVAR_JOIN_SKULLZ) == 1)
#define quest_join_skullz_completed      (global_var(GVAR_JOIN_SKULLZ) == 2)

#define set_quest_join_skullz_active     set_global_var(GVAR_JOIN_SKULLZ, 1)
#define set_quest_join_skullz_completed  if quest_join_skullz_active then set_global_var(GVAR_JOIN_SKULLZ, 2)

#endif // JUNKTOWN_H




