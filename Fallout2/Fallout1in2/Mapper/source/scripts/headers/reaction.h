/*
   Copyright 1998-2003 Interplay Entertainment Corp.  All rights reserved.
*/

#pragma once

/***************************************************
 This file as all the generic actions people will
 take based on the following actions:
    1) Pickpocketing
    2) Theft from container
    3) Lockpicking Door
    4) Sneaking
    5) Starting Combat

 Created: May 18, 1998  (rwh2)

 Updated:
***************************************************/

#define gen_floater(Who,x)          float_msg(Who, message_str(SCRIPT_GENERIC,x),FLOAT_MSG_YELLOW)

#define TIMED_EVENT_SNEAK           (1422)      // arbitrary number for Fixed_Param for timed_event
#define WAIT_TIME_SNEAK             (5)         // in seconds

// Message Lines for Taunts/Comments from the NPC
#define MSG_PICKPOCKET_TG_START     (3000)
#define MSG_PICKPOCKET_TG_END       (3024)
#define MSG_PICKPOCKET_NG_START     (3025)
#define MSG_PICKPOCKET_NG_END       (3049)
#define MSG_PICKPOCKET_TC_START     (3050)
#define MSG_PICKPOCKET_TC_END       (3074)
#define MSG_PICKPOCKET_NC_START     (3075)
#define MSG_PICKPOCKET_NC_END       (3099)

#define MSG_THEFT_TG_START          (3300)
#define MSG_THEFT_TG_END            (3324)
#define MSG_THEFT_NG_START          (3325)
#define MSG_THEFT_NG_END            (3349)
#define MSG_THEFT_TC_START          (3350)
#define MSG_THEFT_TC_END            (3374)
#define MSG_THEFT_NC_START          (3375)
#define MSG_THEFT_NC_END            (3399)

#define MSG_LOCKPICK_TG_START       (3600)
#define MSG_LOCKPICK_TG_END         (3624)
#define MSG_LOCKPICK_NG_START       (3625)
#define MSG_LOCKPICK_NG_END         (3649)
#define MSG_LOCKPICK_TC_START       (3650)
#define MSG_LOCKPICK_TC_END         (3674)
#define MSG_LOCKPICK_NC_START       (3675)
#define MSG_LOCKPICK_NC_END         (3699)

#define MSG_SNEAK_TG_START          (3900)
#define MSG_SNEAK_TG_END            (3924)
#define MSG_SNEAK_NG_START          (3925)
#define MSG_SNEAK_NG_END            (3949)
#define MSG_SNEAK_TC_START          (3950)
#define MSG_SNEAK_TC_END            (3974)
#define MSG_SNEAK_NC_START          (3975)
#define MSG_SNEAK_NC_END            (3999)

#define MSG_ATTACKED_TG_START       (4200)
#define MSG_ATTACKED_TG_END         (4224)
#define MSG_ATTACKED_NG_START       (4225)
#define MSG_ATTACKED_NG_END         (4249)
#define MSG_ATTACKED_TC_START       (4250)
#define MSG_ATTACKED_TC_END         (4274)
#define MSG_ATTACKED_NC_START       (4275)
#define MSG_ATTACKED_NC_END         (4299)

#define MSG_CALL_GUARD_TG_START     (4500)
#define MSG_CALL_GUARD_TG_END       (4524)
#define MSG_CALL_GUARD_NG_START     (4525)
#define MSG_CALL_GUARD_NG_END       (4549)
#define MSG_CALL_GUARD_TC_START     (4550)
#define MSG_CALL_GUARD_TC_END       (4574)
#define MSG_CALL_GUARD_NC_START     (4575)
#define MSG_CALL_GUARD_NC_END       (4599)

#define MSG_CALL_OTHER_TG_START     (4800)
#define MSG_CALL_OTHER_TG_END       (4824)
#define MSG_CALL_OTHER_NG_START     (4825)
#define MSG_CALL_OTHER_NG_END       (4849)
#define MSG_CALL_OTHER_TC_START     (4850)
#define MSG_CALL_OTHER_TC_END       (4874)
#define MSG_CALL_OTHER_NC_START     (4875)
#define MSG_CALL_OTHER_NC_END       (4899)

#define MSG_WARCRY_TG_START         (5100)
#define MSG_WARCRY_TG_END           (5124)
#define MSG_WARCRY_NG_START         (5125)
#define MSG_WARCRY_NG_END           (5149)
#define MSG_WARCRY_TC_START         (5150)
#define MSG_WARCRY_TC_END           (5174)
#define MSG_WARCRY_NC_START         (5175)
#define MSG_WARCRY_NC_END           (5199)

// Variable Type
#define TVAR_COMMON                 (0)
#define TVAR_LOCAL                  (1)
#define TVAR_MAP                    (2)
#define TVAR_GLOBAL                 (3)

// Generic NPC personality types
#define TYPE_CUSTOM                 (0)
#define TYPE_TOUGH_GUARD            (1)
#define TYPE_GUARD                  (2)
#define TYPE_TOUGH_CITIZEN          (3)
#define TYPE_CITIZEN                (4)

// Number of Warnings for Types
#define WARNING_CUSTOM              (0)
#define WARNING_TOUGH_GUARD         (0)
#define WARNING_GUARD               (1)
#define WARNING_TOUGH_CITIZEN       (1)
#define WARNING_CITIZEN             (1)

// Illegal Actions the player does
#define ACTION_NONE                 (0)
#define ACTION_PICKPOCKET           (1)
#define ACTION_THEFT                (2)
#define ACTION_LOCKPICK             (3)
#define ACTION_SNEAK                (4)
#define ACTION_ATTACK               (5)

// Fleeing from Danger Source
#define Get_Rot_Away_From_Who(Source,Dest)      rotation_to_tile(tile_num(Source),tile_num(Dest))

#define Run_Away_From_Who_Dir(Source,Dest)      Get_Rotation_Away_From_Who(Source,Dest)
#define Run_Away_From_Who_Dist                  random(6,10)

#define Run_Away_From_Who_Tile(Source,Dest)     tile_num_in_direction(tile_num(Dest),Run_Away_From_Who_Dir(Source,Dest),Run_Away_From_Who_Dist)

#define Current_Distance_From_Who(Source,Dest)  tile_distance_objs(Source,Dest)

#define Flee_From_Who(Source,Dest)              if (Current_Distance_From_Who(Source,Dest) < 8) then begin                \
                                                    self_run_to_tile(Run_Away_From_Who_Tile(Source,Dest));             \
                                                end


// Call for Help
#define Call_For_Guards(Who,Type,Guard)         if (Type == TYPE_TOUGH_GUARD) then                                                                          \
                                                    gen_floater(Who, random(MSG_CALL_GUARD_TG_START,MSG_CALL_GUARD_TG_END));                              \
                                                else if (Type == TYPE_GUARD) then                                                                           \
                                                    gen_floater(Who, random(MSG_CALL_GUARD_NG_START,MSG_CALL_GUARD_NG_END));                              \
                                                else if (Type == TYPE_TOUGH_CITIZEN) then                                                                   \
                                                    gen_floater(Who, random(MSG_CALL_GUARD_TC_START,MSG_CALL_GUARD_TC_END));                              \
                                                else if (Type == TYPE_CITIZEN) then                                                                         \
                                                    gen_floater(Who, random(MSG_CALL_GUARD_NC_START,MSG_CALL_GUARD_NC_END));                              \
                                                animate_move_obj_to_tile(Guard, tile_num_in_direction(tile_num(self_obj),random(0,5),random(2,4)), ANIMATE_RUN)

#define Call_For_Others(Who,Type)               if (Type == TYPE_TOUGH_GUARD) then                                             \
                                                    gen_floater(Who,random(MSG_CALL_OTHER_TG_START,MSG_CALL_OTHER_TG_END));    \
                                                else if (Type == TYPE_GUARD) then                                              \
                                                    gen_floater(Who,random(MSG_CALL_OTHER_NG_START,MSG_CALL_OTHER_NG_END));    \
                                                else if (Type == TYPE_TOUGH_CITIZEN) then                                      \
                                                    gen_floater(Who,random(MSG_CALL_OTHER_TC_START,MSG_CALL_OTHER_TC_END));    \
                                                else if (Type == TYPE_CITIZEN) then                                            \
                                                    gen_floater(Who,random(MSG_CALL_OTHER_NC_START,MSG_CALL_OTHER_NC_END))

#define Warn_Player(Who,Type,Action)            if (Type == TYPE_TOUGH_GUARD) then begin                                                \
                                                    if (Action == ACTION_PICKPOCKET) then                                               \
                                                        gen_floater(Who,random(MSG_PICKPOCKET_TG_START,MSG_PICKPOCKET_TG_END));         \
                                                    else if (Action == ACTION_THEFT) then                                               \
                                                        gen_floater(Who,random(MSG_THEFT_TG_START,MSG_THEFT_TG_END));                   \
                                                    else if (Action == ACTION_LOCKPICK) then                                            \
                                                        gen_floater(Who,random(MSG_LOCKPICK_TG_START,MSG_LOCKPICK_TG_END));             \
                                                    else if (Action == ACTION_SNEAK) then                                               \
                                                        gen_floater(Who,random(MSG_SNEAK_TG_START,MSG_SNEAK_TG_END));                   \
                                                    else if (Action == ACTION_ATTACK) then                                              \
                                                        gen_floater(Who,random(MSG_ATTACKED_TG_START,MSG_ATTACKED_TG_END));             \
                                                end                                                                                     \
                                                else if (Type == TYPE_GUARD) then begin                                                 \
                                                    if (Action == ACTION_PICKPOCKET) then                                               \
                                                        gen_floater(Who,random(MSG_PICKPOCKET_NG_START,MSG_PICKPOCKET_NG_END));         \
                                                    else if (Action == ACTION_THEFT) then                                               \
                                                        gen_floater(Who,random(MSG_THEFT_NG_START,MSG_THEFT_NG_END));                   \
                                                    else if (Action == ACTION_LOCKPICK) then                                            \
                                                        gen_floater(Who,random(MSG_LOCKPICK_NG_START,MSG_LOCKPICK_NG_END));             \
                                                    else if (Action == ACTION_SNEAK) then                                               \
                                                        gen_floater(Who,random(MSG_SNEAK_NG_START,MSG_SNEAK_NG_END));                   \
                                                    else if (Action == ACTION_ATTACK) then                                              \
                                                        gen_floater(Who,random(MSG_ATTACKED_NG_START,MSG_ATTACKED_NG_END));             \
                                                end                                                                                     \
                                                else if (Type == TYPE_TOUGH_CITIZEN) then begin                                         \
                                                    if (Action == ACTION_PICKPOCKET) then                                               \
                                                        gen_floater(Who,random(MSG_PICKPOCKET_TC_START,MSG_PICKPOCKET_TC_END));         \
                                                    else if (Action == ACTION_THEFT) then                                               \
                                                        gen_floater(Who,random(MSG_THEFT_TC_START,MSG_THEFT_TC_END));                   \
                                                    else if (Action == ACTION_LOCKPICK) then                                            \
                                                        gen_floater(Who,random(MSG_LOCKPICK_TC_START,MSG_LOCKPICK_TC_END));             \
                                                    else if (Action == ACTION_SNEAK) then                                               \
                                                        gen_floater(Who,random(MSG_SNEAK_TC_START,MSG_SNEAK_TC_END));                   \
                                                    else if (Action == ACTION_ATTACK) then                                              \
                                                        gen_floater(Who,random(MSG_ATTACKED_TC_START,MSG_ATTACKED_TC_END));             \
                                                end                                                                                     \
                                                else if (Type == TYPE_CITIZEN) then begin                                               \
                                                    if (Action == ACTION_PICKPOCKET) then                                               \
                                                        gen_floater(Who,random(MSG_PICKPOCKET_NC_START,MSG_PICKPOCKET_NC_END));         \
                                                    else if (Action == ACTION_THEFT) then                                               \
                                                        gen_floater(Who,random(MSG_THEFT_NC_START,MSG_THEFT_NC_END));                   \
                                                    else if (Action == ACTION_LOCKPICK) then                                            \
                                                        gen_floater(Who,random(MSG_LOCKPICK_NC_START,MSG_LOCKPICK_NC_END));             \
                                                    else if (Action == ACTION_SNEAK) then                                               \
                                                        gen_floater(Who,random(MSG_SNEAK_NC_START,MSG_SNEAK_NC_END));                   \
                                                    else if (Action == ACTION_ATTACK) then                                              \
                                                        gen_floater(Who,random(MSG_ATTACKED_NC_START,MSG_ATTACKED_NC_END));             \
                                                end                                                                                     \


#define War_Cry(Who,Type)                       if (Type == TYPE_TOUGH_GUARD) then                                          \
                                                    gen_floater(Who,random(MSG_WARCRY_TG_START,MSG_WARCRY_TG_END));         \
                                                else if (Type == TYPE_GUARD) then                                           \
                                                    gen_floater(Who,random(MSG_WARCRY_NG_START,MSG_WARCRY_NG_END));         \
                                                else if (Type == TYPE_TOUGH_CITIZEN) then                                   \
                                                    gen_floater(Who,random(MSG_WARCRY_TC_START,MSG_WARCRY_TC_END));         \
                                                else if (Type == TYPE_CITIZEN) then                                         \
                                                    gen_floater(Who,random(MSG_WARCRY_NC_START,MSG_WARCRY_NC_END))


// Someone is Caught doing something wrong
#define Caught_Who(Who,Type,Action,Source,Warning,Count,TVar)    if (Action == ACTION_PICKPOCKET) then begin                 \
                                                                     if (Count < Warning) begin                              \
                                                                         if (TVar == TVAR_COMMON) then                       \
                                                                            Count+=1;                                        \
                                                                         else if (TVar == TVAR_LOCAL) then                   \
                                                                            set_local_var(Count,local_var(Count)+1);         \
                                                                         else if (TVar == TVAR_MAP) then                     \
                                                                            set_map_var(Count,map_var(Count)+1);             \
                                                                         else if (TVar == TVAR_GLOBAL) then                  \
                                                                            set_global_var(Count,global_var(Count)+1);       \
                                                                         Warn_Player(Who,Type,Action)                        \
                                                                     end                                                     \
                                                                     else if (Count == Warning) begin                        \
                                                                         if (Type == TYPE_TOUGH_GUARD) begin                 \
                                                                             War_Cry(Who,Type);                              \
                                                                             attack(Source);                                 \
                                                                         end                                                 \
                                                                         else begin                                          \
                                                                             Call_For_Others(Who,Type);                      \
                                                                             if (Type == TYPE_CITIZEN) then                  \
                                                                                 Flee_From_Who(Source,Who)                   \
                                                                             else                                            \
                                                                                 attack(Source);                             \
                                                                         end                                                 \
                                                                     end                                                     \
                                                                 end                                                         \
                                                                 else if (Action == ACTION_THEFT) then begin                 \
                                                                     if (Count < Warning) begin                              \
                                                                         if (TVar == TVAR_COMMON) then                       \
                                                                            Count+=1;                                        \
                                                                         else if (TVar == TVAR_LOCAL) then                   \
                                                                            set_local_var(Count,local_var(Count)+1);         \
                                                                         else if (TVar == TVAR_MAP) then                     \
                                                                            set_map_var(Count,map_var(Count)+1);             \
                                                                         else if (TVar == TVAR_GLOBAL) then                  \
                                                                            set_global_var(Count,global_var(Count)+1);       \
                                                                         Warn_Player(Who,Type,Action)                        \
                                                                     end                                                     \
                                                                     else if (Count == Warning) begin                        \
                                                                         if (Type == TYPE_TOUGH_GUARD) begin                 \
                                                                             War_Cry(Who,Type);                              \
                                                                                 attack(Source);                             \
                                                                         end                                                 \
                                                                         else begin                                          \
                                                                             Call_For_Others(Who,Type);                      \
                                                                             if (Type == TYPE_CITIZEN) then                  \
                                                                                 Flee_From_Who(Source,Who)                   \
                                                                             else                                            \
                                                                                 attack(Source);                             \
                                                                         end                                                 \
                                                                     end                                                     \
                                                                 end                                                         \
                                                                 else if (Action == ACTION_LOCKPICK) then begin              \
                                                                     if (Count < Warning) begin                              \
                                                                         if (TVar == TVAR_COMMON) then                       \
                                                                            Count+=1;                                        \
                                                                         else if (TVar == TVAR_LOCAL) then                   \
                                                                            set_local_var(Count,local_var(Count)+1);         \
                                                                         else if (TVar == TVAR_MAP) then                     \
                                                                            set_map_var(Count,map_var(Count)+1);             \
                                                                         else if (TVar == TVAR_GLOBAL) then                  \
                                                                            set_global_var(Count,global_var(Count)+1);       \
                                                                         Warn_Player(Who,Type,Action)                        \
                                                                     end                                                     \
                                                                     else if (Count == Warning) begin                        \
                                                                         if (Type == TYPE_TOUGH_GUARD) begin                 \
                                                                             War_Cry(Who,Type);                              \
                                                                                 attack(Source);                             \
                                                                         end                                                 \
                                                                         else begin                                          \
                                                                             Call_For_Others(Who,Type);                      \
                                                                             if (Type == TYPE_CITIZEN) then                  \
                                                                                 Flee_From_Who(Source,Who)                   \
                                                                             else                                            \
                                                                                 attack(Source);                             \
                                                                         end                                                 \
                                                                     end                                                     \
                                                                 end                                                         \
                                                                 else if (Action == ACTION_SNEAK) then begin                 \
                                                                     if (Count < Warning) begin                              \
                                                                         if (TVar == TVAR_COMMON) then                       \
                                                                            Count+=1;                                        \
                                                                         else if (TVar == TVAR_LOCAL) then                   \
                                                                            set_local_var(Count,local_var(Count)+1);         \
                                                                         else if (TVar == TVAR_MAP) then                     \
                                                                            set_map_var(Count,map_var(Count)+1);             \
                                                                         else if (TVar == TVAR_GLOBAL) then                  \
                                                                            set_global_var(Count,global_var(Count)+1);       \
                                                                         Warn_Player(Who,Type,Action)                        \
                                                                         add_timer_event(Who,game_ticks(TIMED_EVENT_SNEAK),WAIT_TIME_SNEAK)   \
                                                                     end                                                     \
                                                                     else if (Count == Warning) begin                        \
                                                                         if (Type == TYPE_TOUGH_GUARD) begin                 \
                                                                             War_Cry(Who,Type);                              \
                                                                                 attack(Source);                             \
                                                                         end                                                 \
                                                                         else begin                                          \
                                                                             Call_For_Others(Who,Type);                      \
                                                                             if (Type == TYPE_CITIZEN) then                  \
                                                                                 Flee_From_Who(Source,Who)                   \
                                                                             else                                            \
                                                                                 attack(Source);                             \
                                                                         end                                                 \
                                                                     end                                                     \
                                                                 end                                                         \
                                                                 else if (Action == ACTION_ATTACK) then begin                \
                                                                     if (Count < Warning) begin                              \
                                                                         if (TVar == TVAR_COMMON) then                       \
                                                                            Count+=1;                                        \
                                                                         else if (TVar == TVAR_LOCAL) then                   \
                                                                            set_local_var(Count,local_var(Count)+1);         \
                                                                         else if (TVar == TVAR_MAP) then                     \
                                                                            set_map_var(Count,map_var(Count)+1);             \
                                                                         else if (TVar == TVAR_GLOBAL) then                  \
                                                                            set_global_var(Count,global_var(Count)+1);       \
                                                                         Warn_Player(Who,Type,Action)                        \
                                                                     end                                                     \
                                                                     else if (Count == Warning) begin                        \
                                                                         if (Type == TYPE_TOUGH_GUARD) begin                 \
                                                                             War_Cry(Who,Type);                              \
                                                                             attack(Source);                                 \
                                                                         end                                                 \
                                                                         else begin                                          \
                                                                             Call_For_Others(Who,Type);                      \
                                                                             if (Type == TYPE_CITIZEN) then                  \
                                                                                 Flee_From_Who(Source,Who)                   \
                                                                             else                                            \
                                                                                 attack(Source);                             \
                                                                         end                                                 \
                                                                     end                                                     \
                                                                 end


#define Caught_Pickpocket(Who,Type,Source,Warning,Count,TVar)   Caught_Who(Who,Type,Source,ACTION_PICKPOCKET,Warning,Count,TVar)
#define Caught_Theft(Who,Type,Source,Warning,Count,TVar)        Caught_Who(Who,Type,Source,ACTION_THEFT,Warning,Count,TVar)
#define Caught_Lockpick(Who,Type,Source,Warning,Count,TVar)     Caught_Who(Who,Type,Source,ACTION_LOCKPICK,Warning,Count,TVar)
#define Caught_Sneak(Who,Type,Source,Warning,Count,TVar)        Caught_Who(Who,Type,Source,ACTION_SNEAK,Warning,Count,TVar)
#define Caught_Attack(Who,Type,Source,Warning,Count,TVar)       Caught_Who(Who,Type,Source,ACTION_ATTACK,Warning,Count,TVar)

//////////////////////////////////////////////
// Catching Someone doing something illegal //
//////////////////////////////////////////////
// This line is to be used in Pickup_p_proc. This is when the someone is caught pick_pocketing someone
#define Catch_Pickpocket(Type,Source,Warning,Count,TVar)        Caught_Pickpocket(self_obj,Type,Source,Warning,Count,TVar)

// This is used in the container script that is locked
#define Catch_Theft(Who,Type,Source,Warning,Count,TVar)         if (obj_can_see_obj(Who,Source)) then                  \
                                                                    Caught_Theft(Who,Type,Source,Warning,Count,TVar)

// Adds Timed event to Who
#define Catch_Sneak(Who,Type,Source,Warning,Count,TVar)         if (obj_can_see_obj(Who,Source) then                   \
                                                                    if (using_skill(Source,SKILL_SNEAK)) then          \
                                                                        Caught_Sneak(Who,Type,Source,Warning,Count,TVar)

// This is used on a Locked Door.
#define Catch_Lockpick(Who,Type,Source,Warning,Count,TVar)      if (obj_can_see_obj(Who,Source)) then                  \
                                                                    Caught_Lockpick(Who,Type,Source,Warning,Count,TVar)

// Used on guarded item
#define Catch_User(Who,Type,Source,Warning,Count,TVar)          Catch_Theft(Who,Type,Source,Warning,Count,TVar)

///////////////////////////////////////////////////
// Variable based Getting Caught doing something //
///////////////////////////////////////////////////

// Common Variable being Caught
#define CV_Catch_Pickpocket(Type,Source,Warning,Count)          Catch_Pickpocket(Type,Source,Warning,Count,TVAR_COMMON)
#define CV_Catch_Theft(Who,Type,Source,Warning,Count)           Catch_Theft(Who,Type,Source,Warning,Count,TVAR_COMMON)
#define CV_Catch_Sneak(Who,Type,Source,Warning,Count)           Catch_Sneak(Who,Type,Source,Warning,Count,TVAR_COMMON)
#define CV_Catch_Lockpick(Who,Type,Source,Warning,Count)        Catch_Lockpick(Who,Type,Source,Warning,Count,TVAR_COMMON)
#define CV_Catch_User(Who,Type,Source,Warning,Count)            Catch_User(Who,Type,Source,Warning,Count,TVAR_COMMON)

// Local Variable being Caught
#define LV_Catch_Pickpocket(Type,Source,Warning,Count)          Catch_Pickpocket(Type,Source,Warning,Count,TVAR_LOCAL)
#define LV_Catch_Theft(Who,Type,Source,Warning,Count)           Catch_Theft(Who,Type,Source,Warning,Count,TVAR_LOCAL)
#define LV_Catch_Sneak(Who,Type,Source,Warning,Count)           Catch_Sneak(Who,Type,Source,Warning,Count,TVAR_LOCAL)
#define LV_Catch_Lockpick(Who,Type,Source,Warning,Count)        Catch_Lockpick(Who,Type,Source,Warning,Count,TVAR_LOCAL)
#define LV_Catch_User(Who,Type,Source,Warning,Count)            Catch_User(Who,Type,Source,Warning,Count,TVAR_LOCAL)

// Map Variable being Caught
#define MV_Catch_Pickpocket(Type,Source,Warning,Count)          Catch_Pickpocket(Type,Source,Warning,Count,TVAR_MAP)
#define MV_Catch_Theft(Who,Type,Source,Warning,Count)           Catch_Theft(Who,Type,Source,Warning,Count,TVAR_MAP)
#define MV_Catch_Sneak(Who,Type,Source,Warning,Count)           Catch_Sneak(Who,Type,Source,Warning,Count,TVAR_MAP)
#define MV_Catch_Lockpick(Who,Type,Source,Warning,Count)        Catch_Lockpick(Who,Type,Source,Warning,Count,TVAR_MAP)
#define MV_Catch_User(Who,Type,Source,Warning,Count)            Catch_User(Who,Type,Source,Warning,Count,TVAR_MAP)

// Global Variable being Caught
#define GV_Catch_Pickpocket(Type,Source,Warning,Count)          Catch_Pickpocket(Type,Source,Warning,Count,TVAR_GLOBAL)
#define GV_Catch_Theft(Who,Type,Source,Warning,Count)           Catch_Theft(Who,Type,Source,Warning,Count,TVAR_GLOBAL)
#define GV_Catch_Sneak(Who,Type,Source,Warning,Count)           Catch_Sneak(Who,Type,Source,Warning,Count,TVAR_GLOBAL)
#define GV_Catch_Lockpick(Who,Type,Source,Warning,Count)        Catch_Lockpick(Who,Type,Source,Warning,Count,TVAR_GLOBAL)
#define GV_Catch_User(Who,Type,Source,Warning,Count)            Catch_User(Who,Type,Source,Warning,Count,TVAR_GLOBAL)


/**************************************************************************************************************
****************************************  Reaction Profiles ***************************************************
**************************************************************************************************************/

/////////////////
// Tough Guard //
/////////////////

// Common Variable being Caught
#define TG_CV_Catch_Pickpocket(Source,Count)              Catch_Pickpocket(TYPE_TOUGH_GUARD,Source,WARNING_TOUGH_GUARD,Count,TVAR_COMMON)
#define TG_CV_Catch_Theft(Who,Source,Count)               Catch_Theft(Who,TYPE_TOUGH_GUARD,Source,WARNING_TOUGH_GUARD,Count,TVAR_COMMON)
#define TG_CV_Catch_Sneak(Source,Count)                   Catch_Sneak(Who,TYPE_TOUGH_GUARD,Source,WARNING_TOUGH_GUARD,Count,TVAR_COMMON)
#define TG_CV_Catch_Lockpick(Who,Source,Count)            Catch_Lockpick(Who,TYPE_TOUGH_GUARD,WARNING_TOUGH_GUARD,Count,Count,TVAR_COMMON)
#define TG_CV_Catch_User(Who,Source,Count)                Catch_User(Who,TYPE_TOUGH_GUARD,Source,WARNING_TOUGH_GUARD,Count,TVAR_COMMON)

// Local Variable being Caught
#define TG_LV_Catch_Pickpocket(Source,Count)              Catch_Pickpocket(TYPE_TOUGH_GUARD,Source,WARNING_TOUGH_GUARD,Count,TVAR_LOCAL)
#define TG_LV_Catch_Theft(Who,Source,Count)               Catch_Theft(Who,TYPE_TOUGH_GUARD,Source,WARNING_TOUGH_GUARD,Count,TVAR_LOCAL)
#define TG_LV_Catch_Sneak(Source,Count)                   Catch_Sneak(Who,TYPE_TOUGH_GUARD,Source,WARNING_TOUGH_GUARD,Count,TVAR_LOCAL)
#define TG_LV_Catch_Lockpick(Who,Source,Count)            Catch_Lockpick(Who,TYPE_TOUGH_GUARD,Source,WARNING_TOUGH_GUARD,Count,TVAR_LOCAL)
#define TG_LV_Catch_User(Who,Source,Count)                Catch_User(Who,TYPE_TOUGH_GUARD,Source,WARNING_TOUGH_GUARD,Count,TVAR_LOCAL)

// Map Variable being Caught
#define TG_MV_Catch_Pickpocket(Source,Count)              Catch_Pickpocket(TYPE_TOUGH_GUARD,Source,WARNING_TOUGH_GUARD,Count,TVAR_MAP)
#define TG_MV_Catch_Theft(Who,Source,Count)               Catch_Theft(Who,TYPE_TOUGH_GUARD,Source,WARNING_TOUGH_GUARD,Count,TVAR_MAP)
#define TG_MV_Catch_Sneak(Source,Count)                   Catch_Sneak(Who,TYPE_TOUGH_GUARD,Source,WARNING_TOUGH_GUARD,Count,TVAR_MAP)
#define TG_MV_Catch_Lockpick(Who,Source,Count)            Catch_Lockpick(Who,TYPE_TOUGH_GUARD,Source,WARNING_TOUGH_GUARD,Count,TVAR_MAP)
#define TG_MV_Catch_User(Who,Source,Count)                Catch_User(Who,TYPE_TOUGH_GUARD,Source,WARNING_TOUGH_GUARD,Count,TVAR_MAP)

// Global Variable being Caught
#define TG_GV_Catch_Pickpocket(Source,Count)              Catch_Pickpocket(TYPE_TOUGH_GUARD,Source,WARNING_TOUGH_GUARD,Count,TVAR_GLOBAL)
#define TG_GV_Catch_Theft(Who,Source,Count)               Catch_Theft(Who,TYPE_TOUGH_GUARD,Source,WARNING_TOUGH_GUARD,Count,TVAR_GLOBAL)
#define TG_GV_Catch_Sneak(Source,Count)                   Catch_Sneak(self_obj,TYPE_TOUGH_GUARD,Source,WARNING_TOUGH_GUARD,Count,TVAR_GLOBAL)
#define TG_GV_Catch_Lockpick(Who,Source,Count)            Catch_Lockpick(Who,TYPE_TOUGH_GUARD,Source,WARNING_TOUGH_GUARD,Count,TVAR_GLOBAL)
#define TG_GV_Catch_User(Who,Source,Count)                Catch_User(Who,TYPE_TOUGH_GUARD,Source,WARNING_TOUGH_GUARD,Count,TVAR_GLOBAL)

//////////////////
// Normal Guard //
//////////////////

// Common Variable being Caught
#define NG_CV_Catch_Pickpocket(Source,Count)              Catch_Pickpocket(TYPE_GUARD,Source,WARNING_GUARD,Count,TVAR_COMMON)
#define NG_CV_Catch_Theft(Who,Source,Count)               Catch_Theft(Who,TYPE_GUARD,Source,WARNING_GUARD,Count,TVAR_COMMON)
#define NG_CV_Catch_Sneak(Source,Count)                   Catch_Sneak(Who,TYPE_GUARD,Source,WARNING_GUARD,Count,TVAR_COMMON)
#define NG_CV_Catch_Lockpick(Who,Source,Count)            Catch_Lockpick(Who,TYPE_GUARD,WARNING_GUARD,Count,Count,TVAR_COMMON)
#define NG_CV_Catch_User(Who,Source,Count)                Catch_User(Who,TYPE_GUARD,Source,WARNING_GUARD,Count,TVAR_COMMON)

// Local Variable being Caught
#define NG_LV_Catch_Pickpocket(Source,Count)              Catch_Pickpocket(TYPE_GUARD,Source,WARNING_GUARD,Count,TVAR_LOCAL)
#define NG_LV_Catch_Theft(Who,Source,Count)               Catch_Theft(Who,TYPE_GUARD,Source,WARNING_GUARD,Count,TVAR_LOCAL)
#define NG_LV_Catch_Sneak(Source,Count)                   Catch_Sneak(Who,TYPE_GUARD,Source,WARNING_GUARD,Count,TVAR_LOCAL)
#define NG_LV_Catch_Lockpick(Who,Source,Count)            Catch_Lockpick(Who,TYPE_GUARD,Source,WARNING_GUARD,Count,TVAR_LOCAL)
#define NG_LV_Catch_User(Who,Source,Count)                Catch_User(Who,TYPE_GUARD,Source,WARNING_GUARD,Count,TVAR_LOCAL)

// Map Variable being Caught
#define NG_MV_Catch_Pickpocket(Source,Count)              Catch_Pickpocket(TYPE_GUARD,Source,WARNING_GUARD,Count,TVAR_MAP)
#define NG_MV_Catch_Theft(Who,Source,Count)               Catch_Theft(Who,TYPE_GUARD,Source,WARNING_GUARD,Count,TVAR_MAP)
#define NG_MV_Catch_Sneak(Source,Count)                   Catch_Sneak(Who,TYPE_GUARD,Source,WARNING_GUARD,Count,TVAR_MAP)
#define NG_MV_Catch_Lockpick(Who,Source,Count)            Catch_Lockpick(Who,TYPE_GUARD,Source,WARNING_GUARD,Count,TVAR_MAP)
#define NG_MV_Catch_User(Who,Source,Count)                Catch_User(Who,TYPE_GUARD,Source,WARNING_GUARD,Count,TVAR_MAP)

// Global Variable being Caught
#define NG_GV_Catch_Pickpocket(Source,Count)              Catch_Pickpocket(TYPE_GUARD,Source,WARNING_GUARD,Count,TVAR_GLOBAL)
#define NG_GV_Catch_Theft(Who,Source,Count)               Catch_Theft(Who,TYPE_GUARD,Source,WARNING_GUARD,Count,TVAR_GLOBAL)
#define NG_GV_Catch_Sneak(Source,Count)                   Catch_Sneak(self_obj,TYPE_GUARD,Source,WARNING_GUARD,Count,TVAR_GLOBAL)
#define NG_GV_Catch_Lockpick(Who,Source,Count)            Catch_Lockpick(Who,TYPE_GUARD,Source,WARNING_GUARD,Count,TVAR_GLOBAL)
#define NG_GV_Catch_User(Who,Source,Count)                Catch_User(Who,TYPE_GUARD,Source,WARNING_GUARD,Count,TVAR_GLOBAL)

///////////////////
// Tough Citizen //
///////////////////

// Common Variable being Caught
#define TC_CV_Catch_Pickpocket(Source,Count)              Catch_Pickpocket(TYPE_TOUGH_CITIZEN,Source,WARNING_TOUGH_CITIZEN,Count,TVAR_COMMON)
#define TC_CV_Catch_Theft(Who,Source,Count)               Catch_Theft(Who,TYPE_TOUGH_CITIZEN,Source,WARNING_TOUGH_CITIZEN,Count,TVAR_COMMON)
#define TC_CV_Catch_Sneak(Source,Count)                   Catch_Sneak(Who,TYPE_TOUGH_CITIZEN,Source,WARNING_TOUGH_CITIZEN,Count,TVAR_COMMON)
#define TC_CV_Catch_Lockpick(Who,Source,Count)            Catch_Lockpick(Who,TYPE_TOUGH_CITIZEN,WARNING_TOUGH_CITIZEN,Count,Count,TVAR_COMMON)
#define TC_CV_Catch_User(Who,Source,Count)                Catch_User(Who,TYPE_TOUGH_CITIZEN,Source,WARNING_TOUGH_CITIZEN,Count,TVAR_COMMON)

// Local Variable being Caught
#define TC_LV_Catch_Pickpocket(Source,Count)              Catch_Pickpocket(TYPE_TOUGH_CITIZEN,Source,WARNING_TOUGH_CITIZEN,Count,TVAR_LOCAL)
#define TC_LV_Catch_Theft(Who,Source,Count)               Catch_Theft(Who,TYPE_TOUGH_CITIZEN,Source,WARNING_TOUGH_CITIZEN,Count,TVAR_LOCAL)
#define TC_LV_Catch_Sneak(Source,Count)                   Catch_Sneak(Who,TYPE_TOUGH_CITIZEN,Source,WARNING_TOUGH_CITIZEN,Count,TVAR_LOCAL)
#define TC_LV_Catch_Lockpick(Who,Source,Count)            Catch_Lockpick(Who,TYPE_TOUGH_CITIZEN,Source,WARNING_TOUGH_CITIZEN,Count,TVAR_LOCAL)
#define TC_LV_Catch_User(Who,Source,Count)                Catch_User(Who,TYPE_TOUGH_CITIZEN,Source,WARNING_TOUGH_CITIZEN,Count,TVAR_LOCAL)

// Map Variable being Caught
#define TC_MV_Catch_Pickpocket(Source,Count)              Catch_Pickpocket(TYPE_TOUGH_CITIZEN,Source,WARNING_TOUGH_CITIZEN,Count,TVAR_MAP)
#define TC_MV_Catch_Theft(Who,Source,Count)               Catch_Theft(Who,TYPE_TOUGH_CITIZEN,Source,WARNING_TOUGH_CITIZEN,Count,TVAR_MAP)
#define TC_MV_Catch_Sneak(Source,Count)                   Catch_Sneak(Who,TYPE_TOUGH_CITIZEN,Source,WARNING_TOUGH_CITIZEN,Count,TVAR_MAP)
#define TC_MV_Catch_Lockpick(Who,Source,Count)            Catch_Lockpick(Who,TYPE_TOUGH_CITIZEN,Source,WARNING_TOUGH_CITIZEN,Count,TVAR_MAP)
#define TC_MV_Catch_User(Who,Source,Count)                Catch_User(Who,TYPE_TOUGH_CITIZEN,Source,WARNING_TOUGH_CITIZEN,Count,TVAR_MAP)

// Global Variable being Caught
#define TC_GV_Catch_Pickpocket(Source,Count)              Catch_Pickpocket(TYPE_TOUGH_CITIZEN,Source,WARNING_TOUGH_CITIZEN,Count,TVAR_GLOBAL)
#define TC_GV_Catch_Theft(Who,Source,Count)               Catch_Theft(Who,TYPE_TOUGH_CITIZEN,Source,WARNING_TOUGH_CITIZEN,Count,TVAR_GLOBAL)
#define TC_GV_Catch_Sneak(Source,Count)                   Catch_Sneak(self_obj,TYPE_TOUGH_CITIZEN,Source,WARNING_TOUGH_CITIZEN,Count,TVAR_GLOBAL)
#define TC_GV_Catch_Lockpick(Who,Source,Count)            Catch_Lockpick(Who,TYPE_TOUGH_CITIZEN,Source,WARNING_TOUGH_CITIZEN,Count,TVAR_GLOBAL)
#define TC_GV_Catch_User(Who,Source,Count)                Catch_User(Who,TYPE_TOUGH_CITIZEN,Source,WARNING_TOUGH_CITIZEN,Count,TVAR_GLOBAL)

////////////////////
// Normal Citizen //
////////////////////

// Common Variable being Caught
#define NC_CV_Catch_Pickpocket(Source,Count)              Catch_Pickpocket(TYPE_CITIZEN,Source,WARNING_CITIZEN,Count,TVAR_COMMON)
#define NC_CV_Catch_Theft(Who,Source,Count)               Catch_Theft(Who,TYPE_CITIZEN,Source,WARNING_CITIZEN,Count,TVAR_COMMON)
#define NC_CV_Catch_Sneak(Source,Count)                   Catch_Sneak(Who,TYPE_CITIZEN,Source,WARNING_CITIZEN,Count,TVAR_COMMON)
#define NC_CV_Catch_Lockpick(Who,Source,Count)            Catch_Lockpick(Who,TYPE_CITIZEN,WARNING_CITIZEN,Count,Count,TVAR_COMMON)
#define NC_CV_Catch_User(Who,Source,Count)                Catch_User(Who,TYPE_CITIZEN,Source,WARNING_CITIZEN,Count,TVAR_COMMON)

// Local Variable being Caught
#define NC_LV_Catch_Pickpocket(Source,Count)              Catch_Pickpocket(TYPE_CITIZEN,Source,WARNING_CITIZEN,Count,TVAR_LOCAL)
#define NC_LV_Catch_Theft(Who,Source,Count)               Catch_Theft(Who,TYPE_CITIZEN,Source,WARNING_CITIZEN,Count,TVAR_LOCAL)
#define NC_LV_Catch_Sneak(Source,Count)                   Catch_Sneak(Who,TYPE_CITIZEN,Source,WARNING_CITIZEN,Count,TVAR_LOCAL)
#define NC_LV_Catch_Lockpick(Who,Source,Count)            Catch_Lockpick(Who,TYPE_CITIZEN,Source,WARNING_CITIZEN,Count,TVAR_LOCAL)
#define NC_LV_Catch_User(Who,Source,Count)                Catch_User(Who,TYPE_CITIZEN,Source,WARNING_CITIZEN,Count,TVAR_LOCAL)

// Map Variable being Caught
#define NC_MV_Catch_Pickpocket(Source,Count)              Catch_Pickpocket(TYPE_CITIZEN,Source,WARNING_CITIZEN,Count,TVAR_MAP)
#define NC_MV_Catch_Theft(Who,Source,Count)               Catch_Theft(Who,TYPE_CITIZEN,Source,WARNING_CITIZEN,Count,TVAR_MAP)
#define NC_MV_Catch_Sneak(Source,Count)                   Catch_Sneak(Who,TYPE_CITIZEN,Source,WARNING_CITIZEN,Count,TVAR_MAP)
#define NC_MV_Catch_Lockpick(Who,Source,Count)            Catch_Lockpick(Who,TYPE_CITIZEN,Source,WARNING_CITIZEN,Count,TVAR_MAP)
#define NC_MV_Catch_User(Who,Source,Count)                Catch_User(Who,TYPE_CITIZEN,Source,WARNING_CITIZEN,Count,TVAR_MAP)

// Global Variable being Caught
#define NC_GV_Catch_Pickpocket(Source,Count)              Catch_Pickpocket(TYPE_CITIZEN,Source,WARNING_CITIZEN,Count,TVAR_GLOBAL)
#define NC_GV_Catch_Theft(Who,Source,Count)               Catch_Theft(Who,TYPE_CITIZEN,Source,WARNING_CITIZEN,Count,TVAR_GLOBAL)
#define NC_GV_Catch_Sneak(Source,Count)                   Catch_Sneak(self_obj,TYPE_CITIZEN,Source,WARNING_CITIZEN,Count,TVAR_GLOBAL)
#define NC_GV_Catch_Lockpick(Who,Source,Count)            Catch_Lockpick(Who,TYPE_CITIZEN,Source,WARNING_CITIZEN,Count,TVAR_GLOBAL)
#define NC_GV_Catch_User(Who,Source,Count)                Catch_User(Who,TYPE_CITIZEN,Source,WARNING_CITIZEN,Count,TVAR_GLOBAL)
