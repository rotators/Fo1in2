/*

    The Hub generic defines

*/

#pragma once

/************************************************
    Generic Defines
************************************************/

// Timer for the conversation between Guido and Leon at the FLC
#define TIMER_CONVERSATION     (6) // orig. 3


// Quests
#define set_quest_kill_merchant        set_global_var(GVAR_KILL_MERCHANT, 1)
#define get_quest_kill_merchant        (global_var(GVAR_KILL_MERCHANT) == 1)

#define set_quest_merchant_killed      set_global_var(GVAR_KILL_MERCHANT, 2)
#define get_quest_merchant_killed      (global_var(GVAR_KILL_MERCHANT) == 2)

#define set_quest_merchant_attacked    set_global_var(GVAR_KILL_MERCHANT, 5)
#define get_quest_merchant_attacked    (global_var(GVAR_KILL_MERCHANT) == 5)

#define set_quest_kill_jain      set_global_var(GVAR_KILL_JAIN, 1)
#define get_quest_kill_jain      (global_var(GVAR_KILL_JAIN) == 1)

#define set_quest_jain_killed    set_global_var(GVAR_KILL_JAIN, 2)
#define get_quest_jain_killed    (global_var(GVAR_KILL_JAIN) == 2)


// New varibales for easier handling of the PipBoy quest entries
#define set_quest_kill_merchant_inactive  if (global_var(GVAR_QUEST_PIPBOY_HIGHTOWER) == 1) then \
                                             set_global_var(GVAR_QUEST_PIPBOY_HIGHTOWER, 0)

#define set_quest_kill_merchant_active    if (global_var(GVAR_QUEST_PIPBOY_HIGHTOWER) == 0) then \
                                             set_global_var(GVAR_QUEST_PIPBOY_HIGHTOWER, 1)

#define set_quest_kill_merchant_completed if (global_var(GVAR_QUEST_PIPBOY_HIGHTOWER) == 1) then \
                                             set_global_var(GVAR_QUEST_PIPBOY_HIGHTOWER, 2)

#define set_quest_kill_jain_inactive      if (global_var(GVAR_QUEST_PIPBOY_JAIN) == 1) then \
                                             set_global_var(GVAR_QUEST_PIPBOY_JAIN, 0)

#define set_quest_kill_jain_active        if (global_var(GVAR_QUEST_PIPBOY_JAIN) == 0) then \
                                             set_global_var(GVAR_QUEST_PIPBOY_JAIN, 1)

#define set_quest_kill_jain_completed     if (global_var(GVAR_QUEST_PIPBOY_JAIN) == 1) then \
                                             set_global_var(GVAR_QUEST_PIPBOY_JAIN, 2)
