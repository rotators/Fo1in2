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
#define EXP_RETURN_WATERCHIP 					(7500)

// Vault 15

// Shady Sands
#define EXP_HIRED_IAN							(100)

// Raiders

// Junktown

// Hub

// Boneyard

// Necropolis

// Glow
#define EXP_REPAIR_GENERATOR 					(1000)

// BOS

// Mariposa

/***************************************************
     Giving Experience Points
***************************************************/

/***************************************
 Give the experience points and display
 a message informing the player how many
 points he received.
***************************************/
#define give_xp(x)                              give_exp_points(x);             \
                                                display_msg(message_str(SCRIPT_GENERIC,100)+x+message_str(SCRIPT_GENERIC,101))

#endif // EXPPOINT_H
