/*

    General Boneyard header
    Used to track quest states.

*/

#ifndef BONEYARD_H
#define BONEYARD_H

/************************************************
    Generic Defines
************************************************/

//******************** Quest: Blades vs. Regulators conflict
//--- Gun Runners:
// PipBoy quest tracker:
#define momclaw_quest_inactive          (global_var(GVAR_QUEST_KILL_MOMCLAW) == 0)
#define momclaw_quest_active            (global_var(GVAR_QUEST_KILL_MOMCLAW) == 1)
#define momclaw_quest_completed         (global_var(GVAR_QUEST_KILL_MOMCLAW) == 2)
#define set_momclaw_quest_active        set_global_var(GVAR_QUEST_KILL_MOMCLAW, 1)
#define set_momclaw_quest_completed     set_global_var(GVAR_QUEST_KILL_MOMCLAW, 2)

// Deathclaws:
#define set_quest_kill_deathclaws       set_global_var(GVAR_GUN_RUNNERS_STATUS, 9201)
#define get_quest_kill_deathclaws       (global_var(GVAR_GUN_RUNNERS_STATUS) == 9201)

#define set_all_deathclaws_killed       set_global_var(GVAR_WATER_CHIP_8, 9250)
#define get_all_deathclaws_killed       (global_var(GVAR_WATER_CHIP_8) == 9250)

#define set_gunrunners_armed_blades     set_global_var(GVAR_GUN_RUNNERS_STATUS, 9202)
#define get_gunrunners_armed_blades     (global_var(GVAR_GUN_RUNNERS_STATUS) == 9202)

#define set_gunrunners_armed_dude       set_global_var(GVAR_WATER_CHIP_8, 2)
#define get_gunrunners_armed_dude       (global_var(GVAR_WATER_CHIP_8) == 2)

//--- Blades:
#define set_arming_blades               set_global_var(GVAR_BLADES_STATUS, 9101)
#define get_arming_blades               global_var( GVAR_BLADES_STATUS ) == 9101

// Player wants to talk to Zimmermann before the attack:
#define set_blades_attacking_wait       set_global_var(GVAR_BLADES_STATUS, 9102)
#define get_blades_attacking_wait       (global_var(GVAR_BLADES_STATUS) == 9102)

// Blades are attacking:
#define set_blades_attacking            set_global_var(GVAR_BLADES_STATUS, 9103)
#define get_blades_attacking            (global_var(GVAR_BLADES_STATUS) == 9103)

// Player declines to attack with Blades:
#define set_blades_attacking_alone      set_global_var(GVAR_BLADES_STATUS, 9104)
#define get_blades_attacking_alone      (global_var(GVAR_BLADES_STATUS) == 9104)

//--- Regulators:
#define get_gangwar_inactive            (global_var(GVAR_QUEST_BONEYARD_7_GANG_WAR) == 0) // this stuff is old and unfinished. Replaced with quest var down below.
#define get_gangwar_active              (global_var(GVAR_QUEST_BONEYARD_7_GANG_WAR) == 1) // this stuff is old and unfinished. Replaced with quest var down below.

#define quest_kill_razor_inactive       (global_var(GVAR_QUEST_KILL_RAZOR) == 0)
#define quest_kill_razor_active         (global_var(GVAR_QUEST_KILL_RAZOR) == 1)
#define quest_kill_razor_completed      (global_var(GVAR_QUEST_KILL_RAZOR) == 2)
#define set_quest_kill_razor_active     set_global_var(GVAR_QUEST_KILL_RAZOR, 1)
#define set_quest_kill_razor_completed  set_global_var(GVAR_QUEST_KILL_RAZOR, 2)


//--- Zimmermann:
#define set_task_kill_razor             set_global_var(GVAR_ZIMMERMAN_STATUS, 9001); \
                                        if quest_kill_razor_inactive then set_quest_kill_razor_active
#define get_task_kill_razor             (global_var(GVAR_ZIMMERMAN_STATUS) == 9001)

#define set_razor_killed                set_global_var(GVAR_ZIMMERMAN_STATUS, 9002); \
                                        if quest_kill_razor_active then set_quest_kill_razor_completed
#define get_razor_killed                (global_var(GVAR_ZIMMERMAN_STATUS) == 9002)

#define set_zimmermann_turned           set_global_var(GVAR_ZIMMERMAN_STATUS, 9003)
#define get_zimmermann_turned           (global_var(GVAR_ZIMMERMAN_STATUS) == 9003)


//******************** Quest: Fix the farm
//--- Smitty and Miles:
#define get_quest_farm_inactive         (global_var(GVAR_QUEST_BONEYARD_5_FIX_FARM) == 0)
#define set_quest_farm_active           set_global_var(GVAR_QUEST_BONEYARD_5_FIX_FARM, 1)
#define get_quest_farm_active           (global_var(GVAR_QUEST_BONEYARD_5_FIX_FARM) == 1)

#define set_give_parts_to_smitty        set_global_var(GVAR_QUEST_BONEYARD_5_FIX_FARM, 9302)
#define get_given_parts_to_smitty_yet   (global_var(GVAR_QUEST_BONEYARD_5_FIX_FARM) == 9302)

#define set_smitty_fixing_parts         set_global_var(GVAR_QUEST_BONEYARD_5_FIX_FARM, 9303)
#define get_smitty_fixing_parts         (global_var(GVAR_QUEST_BONEYARD_5_FIX_FARM) < 9303)
#define get_parts_fixed                 (global_var(GVAR_QUEST_BONEYARD_5_FIX_FARM) == 9303)

#define set_offer_upgrading_item        set_global_var(GVAR_QUEST_BONEYARD_5_FIX_FARM, 9304)
#define get_offer_upgrading_item        (global_var(GVAR_QUEST_BONEYARD_5_FIX_FARM) == 9304)

// Generic dialog stuff:
#define set_zimmermann_insulted         set_global_var(GVAR_ZIMMERMAN_STATUS, 1)
#define get_zimmermann_insulted         (global_var(GVAR_ZIMMERMAN_STATUS) == 1)

#define set_zimmermann_at_peace         set_global_var(GVAR_ZIMMERMAN_STATUS, 2)
#define get_zimmermann_at_peace         (global_var(GVAR_ZIMMERMAN_STATUS) == 2)

#endif // BONEYARD_H




