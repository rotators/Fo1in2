/*
    Copyright 1998-2003 Interplay Entertainment Corp.  All rights reserved.
*/

#ifndef EXPPOINT_H
#define EXPPOINT_H

/************************************************************
   defines for the Experience Point awards in the game
   all defines for experience points need to be in the
   form of:
      EXP_seed
   If there are any modifies (such as using a skill), please
   add that to the name so that rewards and be adjusted
   accordingly by the designers
************************************************************/


/*-----------------9/16/97 7:45:M-------------------
 General Format for this file is:

 I. Experience for Skill Usage
    A. Lockpick
    B. Stealing
    C. Traps
    D. Gambling
    E. Speech
    F. Science
    G. Repair

 II. Experience Points for solving seeds

 III. Giving Experience Points
    A. Display Message string


 10/27/98 Added Karma awards -NBK

--------------------------------------------------*/


/*-----------------9/16/97 7:47:M-------------------
 Experience Points for Skill Usage
--------------------------------------------------*/

/****************************************
 Lockpick Experience Points
****************************************/
#define EXP_LOCKPICK_NORMAL                     (25)
#define EXP_LOCKPICK_NEG_10                     (35)
#define EXP_LOCKPICK_NEG_20                     (45)
#define EXP_LOCKPICK_NEG_30                     (55)
#define EXP_LOCKPICK_NEG_40                     (65)
#define EXP_LOCKPICK_NEG_50                     (75)
#define EXP_LOCKPICK_NEG_60                     (85)
#define EXP_LOCKPICK_NEG_70                     (95)
#define EXP_LOCKPICK_NEG_80                     (105)
#define EXP_LOCKPICK_NEG_90                     (115)

/****************************************
 Stealing Experience Points
****************************************/
#define EXP_STEALING_NORMAL                     (25)
#define EXP_STEALING_NEG_10                     (35)
#define EXP_STEALING_NEG_20                     (45)
#define EXP_STEALING_NEG_30                     (55)
#define EXP_STEALING_NEG_40                     (65)
#define EXP_STEALING_NEG_50                     (75)
#define EXP_STEALING_NEG_60                     (85)
#define EXP_STEALING_NEG_70                     (95)
#define EXP_STEALING_NEG_80                     (105)
#define EXP_STEALING_NEG_90                     (115)

/****************************************
 Traps Experience Points
****************************************/
#define EXP_TRAPS_NORMAL                        (25)
#define EXP_TRAPS_NEG_10                        (35)
#define EXP_TRAPS_NEG_20                        (45)
#define EXP_TRAPS_NEG_30                        (55)
#define EXP_TRAPS_NEG_40                        (65)
#define EXP_TRAPS_NEG_50                        (75)
#define EXP_TRAPS_NEG_60                        (85)
#define EXP_TRAPS_NEG_70                        (95)
#define EXP_TRAPS_NEG_80                        (105)
#define EXP_TRAPS_NEG_90                        (115)

/****************************************
 Gambling Experience Points
****************************************/
#define EXP_GAMBLING_NORMAL                     (25)
#define EXP_GAMBLING_NEG_10                     (35)
#define EXP_GAMBLING_NEG_20                     (45)
#define EXP_GAMBLING_NEG_30                     (55)
#define EXP_GAMBLING_NEG_40                     (65)
#define EXP_GAMBLING_NEG_50                     (75)
#define EXP_GAMBLING_NEG_60                     (85)
#define EXP_GAMBLING_NEG_70                     (95)
#define EXP_GAMBLING_NEG_80                     (105)
#define EXP_GAMBLING_NEG_90                     (115)

/****************************************
 Speach Experience Points
****************************************/
#define EXP_SPEECH_NORMAL                       (25)
#define EXP_SPEECH_NEG_10                       (35)
#define EXP_SPEECH_NEG_20                       (45)
#define EXP_SPEECH_NEG_30                       (55)
#define EXP_SPEECH_NEG_40                       (65)
#define EXP_SPEECH_NEG_50                       (75)
#define EXP_SPEECH_NEG_60                       (85)
#define EXP_SPEECH_NEG_70                       (95)
#define EXP_SPEECH_NEG_80                       (105)
#define EXP_SPEECH_NEG_90                       (115)

/****************************************
 Science Experience Points
****************************************/
#define EXP_SCIENCE_NORMAL                      (35)
#define EXP_SCIENCE_NEG_10                      (45)
#define EXP_SCIENCE_NEG_20                      (55)
#define EXP_SCIENCE_NEG_30                      (65)
#define EXP_SCIENCE_NEG_40                      (75)
#define EXP_SCIENCE_NEG_50                      (85)
#define EXP_SCIENCE_NEG_60                      (95)
#define EXP_SCIENCE_NEG_70                      (105)
#define EXP_SCIENCE_NEG_80                      (115)
#define EXP_SCIENCE_NEG_90                      (125)

/****************************************
 Repair Experience Points
****************************************/
#define EXP_REPAIR_NORMAL                       (35)
#define EXP_REPAIR_NEG_10                       (45)
#define EXP_REPAIR_NEG_20                       (55)
#define EXP_REPAIR_NEG_30                       (65)
#define EXP_REPAIR_NEG_40                       (75)
#define EXP_REPAIR_NEG_50                       (85)
#define EXP_REPAIR_NEG_60                       (95)
#define EXP_REPAIR_NEG_70                       (105)
#define EXP_REPAIR_NEG_80                       (115)
#define EXP_REPAIR_NEG_90                       (125)


/*-----------------9/16/97 7:47:M-------------------
     Experience Points for Solving Seeds
--------------------------------------------------*/

// Vault 13
#define EXP_RETURN_WATERCHIP                    (7500)
#define EXP_DESTROYED_DOOR_TERMINAL             (50)

// Vault 15
#define EXP_RATS_TUNNEL_DESTROYED               (100)
#define EXP_V15_EXPLORED                        (500)

// Shady Sands
#define EXP_HIRED_IAN                           (100)
#define EXP_TANDI_RETURNED                      (400)
#define EXP_EXPLAINED_CROP_ROTATION             (500)
#define EXP_KILLED_SS_RADSCORPION               (500)
#define EXP_JARVIS_ANTIDOTE                     (500)

// Raiders
#define EXP_BEFRIEND_KHANS                      (500)
#define EXP_RESCUE_SLAVE                        (200)

// Junktown
#define EXP_TRISH_SAUL_RELATIONSHIP             (250)
#define EXP_KILLED_KENJI                        (400)
#define EXP_GET_RID_OF_DOGMEAT                  (35)
#define EXP_DOGMEAT_JOINS_PARTY                 (100)
#define EXP_HIRED_TYCHO                         (300)
#define EXP_SAUL_TRISH_RELATIONSHIP             (250)
#define EXP_BUSTING_OUT_OF_JAIL                 (250)

// Hub
#define EXP_BOUGHT_WATER_CARAVAN                (1000)
#define EXP_FIND_DEATHCLAW                      (800)
#define EXP_BLACKMAILING_BOB                    (500)
#define EXP_NECKLACE_STOLEN                     (500)
#define EXP_IRWINE_FARM_CLEARED                 (500)

// Boneyard
#define EXP_QUEST_KILLED_DCLAWS                 (1000)
#define EXP_UPGRADE_MOTORCYCLE                  (500)
#define EXP_HIRED_KATJA                         (200)

// Necropolis
#define EXP_WATER_CHIP_TAKEN                    (2500)
#define EXP_WATER_PUMP_FIXED                    (1000)
#define EXP_PRISONER_FREED                      (500)
#define EXP_GIVEN_ENERGY_CELLS                  (1000)
#define EXP_STOLEN_CONTROLLER                   (250)
#define EXP_BOUGHT_BIKE                         (500)

// Glow
#define EXP_DISABLED_TRAPS                      (0)
#define EXP_MAINFRAME_ACCESS                    (100)
#define EXP_REPAIR_GENERATOR                    (1000)

// Brotherhood of Steel
#define EXP_REPAIR_PA                           (500)
#define EXP_BECOME_INITITAT                     (2000)

// Mariposa
#define EXP_BONUS_HACKING                       (800)
#define EXP_HANDYC_CLEANUP                      (1000)
#define EXP_OVERHEARD_CONVERSATION              (1000)
#define EXP_TRICKING_MUTANTS                    (1500)
#define EXP_SNEAK_SUCCESS                       (2000)
#define EXP_VATS_DESTROYED                      (10000)

// Cathedral
#define EXP_KILLED_MORPHEUS                     (1000)
#define EXP_FOUND_MILITARY_BASE                 (1250)
#define EXP_KNEW_ABOUT_MILITARY_BASE            (500)
#define EXP_WENT_TO_MILITARY_BASE               (50)
#define EXP_MASTER_DESTROYED                    (10000)

/***************************************************
     Giving Experience Points
***************************************************/

#define EXP_SHOVELED_ALL_CRAP                   (150)
#define EXP_TEMPLE_OF_TRIALS                    (500)

/***************************************
 Give the experience points and display
 a message informing the player how many
 points he received.
***************************************/
#define give_xp(x)                              give_exp_points(x);             \
                                                display_msg(message_str(SCRIPT_GENERIC,10)+x+message_str(SCRIPT_GENERIC,11))

#endif // EXPPOINT_H
