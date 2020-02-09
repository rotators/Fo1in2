/*
   Copyright 1998-2003 Interplay Entertainment Corp.  All rights reserved.
*/

#ifndef CARAVAN_H
#define CARAVAN_H

/**********************************************************
   All thing great and important to know about Caravans
   for travel on the world map and beyond
**********************************************************/

variable Finding_New_Tile;

#define set_caravan_pos(x,y)                    wm_area_set_pos(AREA_CARAVAN_ENCOUNTER,x+random(-25,25),y+random(-25,25))

#define Create_Enemy(who,weapon,script)         Critter_Counter+=1;                                                             \
                                                Critter:=create_object_sid(who,0,0,script);                                     \
                                                Critter_Tile:=tile_num_in_direction(Critter_Tile,random(0,5),random(2,5));      \
                                                Finding_New_Tile:=0;                                                            \
                                                while ((not(tile_in_tile_rect(8709,15638,24963,31892,Critter_Tile))) and (Finding_New_Tile < 5)) do begin           \
                                                    Finding_New_Tile+=1;                                                        \
                                                    Critter_Tile:=tile_num_in_direction(tile_num(dude_obj),Encounter_Rotation,dude_perception*2);  \
                                                end                                                                             \
                                                critter_attempt_placement(Critter,Critter_Tile,elevation(dude_obj));            \
                                                if (weapon > 0) then begin                                                      \
                                                    item:=create_object(weapon,0,0);                                            \
                                                    add_obj_to_inven(Critter,item);                                             \
                                                    wield_obj_critter(Critter,item);                                            \
                                                end                                                                             \
                                                anim(Critter,ANIMATE_ROTATION,rotation_to_tile(tile_num(Critter),tile_num(dude_obj)))

// TODO: Make new defines!
#define WM_In_EPA(x,y)                          ((x >= 400) and (x <= 750) and (y >= 800) and (y <= 1150))

#define WM_In_New_Reno(x,y)                     (((x >= 750) and (x <= 1050) and (y >= 800) and (y <= 1100)) or      \
                                                 ((x >= 850) and (x <= 1000) and (y >= 700) and (y <= 800)))

#define WM_In_SRNRRN(x,y)                       ((x >= 550) and (x <= 800) and (y >= 700) and (y <= 800))

#define WM_In_Brok(x,y)                         (((x >= 1050) and (x <= 1100) and (y >= 750) and (y <= 800)) or      \
                                                 ((x >= 1100) and (x <= 1400) and (y >= 750) and (y <= 1050)))

#define WM_In_NCR(x,y)                          ((x >= 1000) and (x <= 1200) and (y >= 1350) and (y <= 1500))

#define WM_In_Band(x,y)                         (((x >= 650) and (x <= 800) and (y >= 0) and (y <= 100)) or          \
                                                 ((x >= 650) and (x <= 800) and (y >= 150) and (y <= 400)))

#define WM_In_Redding(x,y)                      (((x >= 500) and (x <= 850) and (y >= 400) and (y <= 700)) and       \
                                                 (not((x >= 500) and (x <= 550) and (y >= 500) and (y <= 600))) and  \
                                                 (not((x >= 800) and (x <= 850) and (y >= 650) and (y <= 700))))

#define WM_In_VPat(x,y)                         (((x >= 1050) and (x <= 1400) and (y >= 250) and (y <= 450)) and        \
                                                 (not((x >= 1150) and (x <= 1400) and (y >= 250) and (y <= 300))) and   \
                                                 (not((x >= 1050) and (x <= 1100) and (y >= 400) and (y <= 450))))

#define WM_In_NRNR(x,y)                         (((x >= 700) and (x <= 800) and (y >= 1150) and (y <= 1300)) or     \
                                                 ((x >= 750) and (x <= 950) and (y >= 1300) and (y <= 1350)) or     \
                                                 ((x >= 850) and (x <= 1000) and (y >= 1350) and (y <= 1400)))

#define WM_In_DNRV(x,y)                         (((x >= 400) and (x <= 450) and (y >= 400) and (y <= 500)) or       \
                                                 ((x >= 450) and (x <= 500) and (y >= 300) and (y <= 550)) or       \
                                                 ((x >= 500) and (x <= 550) and (y >= 500) and (y <= 600)))

#define WM_In_DVMV(x,y)                         (((x >= 950) and (x <= 1200) and (y >= 200) and (y <= 250)) or      \
                                                 ((x >= 1150) and (x <= 1300) and (y >= 250) and (y <= 300)))

#define WM_In_VNNB(x,y)                         (((x >= 1100) and (x <= 1200) and (y >= 1000) and (y <= 1400)) or   \
                                                 ((x >= 1050) and (x <= 1100) and (y >= 1200) and (y <= 1250)) or   \
                                                 ((x >= 1100) and (x <= 1150) and (y >= 1400) and (y <= 1450)))

#define WM_In_RDRC(x,y)                         (((x >= 1200) and (x <= 1450) and (y >= 450) and (y <= 650)) or     \
                                                 ((x >= 1150) and (x <= 1300) and (y >= 650) and (y <= 750)))

#define WM_In_DMRV(x,y)                         (((x >= 500) and (x <= 600) and (y >= 150) and (y <= 250)) or       \
                                                 ((x >= 550) and (x <= 950) and (y >= 100) and (y <= 150)) or       \
                                                 ((x >= 900) and (x <= 1050) and (y >= 200) and (y <= 250)))

// Caravan Encounter World Coordinates.
// Start City, Destination City, Number of Encounters, Encounter Subclass, x/y position
// Hub <--> Junktown, 1 Encounter only
#define HUB_JNK_1_1_x                              (883)
#define HUB_JNK_1_1_y                              (625)

// Hub <--> Junktown, 2 Encounter only
#define HUB_JNK_2_1_x                              (874)
#define HUB_JNK_2_1_y                              (661)
#define HUB_JNK_2_2_x                              (877)
#define HUB_JNK_2_2_y                              (573)

// Hub <--> Junktown, 3 Encounter only
#define HUB_JNK_3_1_x                              (875)
#define HUB_JNK_3_1_y                              (673)
#define HUB_JNK_3_2_x                              (876)
#define HUB_JNK_3_2_y                              (626)
#define HUB_JNK_3_3_x                              (876)
#define HUB_JNK_3_3_y                              (574)

// Hub <--> Junktown, 4 Encounter only
#define HUB_JNK_4_1_x                              (876)
#define HUB_JNK_4_1_y                              (683)
#define HUB_JNK_4_2_x                              (876)
#define HUB_JNK_4_2_y                              (646)
#define HUB_JNK_4_3_x                              (876)
#define HUB_JNK_4_3_y                              (602)
#define HUB_JNK_4_4_x                              (876)
#define HUB_JNK_4_4_y                              (566)

// Hub <--> Necropolis, 1 Encounter only
#define HUB_NEC_1_1_x                              (997)
#define HUB_NEC_1_1_y                              (708)

// Hub <--> Necropolis, 2 Encounter only
#define HUB_NEC_2_1_x                              (947)
#define HUB_NEC_2_1_y                              (713)
#define HUB_NEC_2_2_x                              (1038)
#define HUB_NEC_2_2_y                              (694)

// Hub <--> Necropolis, 3 Encounter only
#define HUB_NEC_3_1_x                              (953)
#define HUB_NEC_3_1_y                              (711)
#define HUB_NEC_3_2_x                              (1008)
#define HUB_NEC_3_2_y                              (700)
#define HUB_NEC_3_3_x                              (1074)
#define HUB_NEC_3_3_y                              (674)

// Hub <--> Necropolis, 4 Encounter only
#define HUB_NEC_4_1_x                              (928)
#define HUB_NEC_4_1_y                              (728)
#define HUB_NEC_4_2_x                              (1004)
#define HUB_NEC_4_2_y                              (714)
#define HUB_NEC_4_3_x                              (1085)
#define HUB_NEC_4_3_y                              (721)
#define HUB_NEC_4_4_x                              (1140)
#define HUB_NEC_4_4_y                              (720)

// Hub <--> Brotherhood, 1 Encounter only
#define HUB_BOS_1_1_x                              (727)
#define HUB_BOS_1_1_y                              (614)

// Hub <--> Brotherhood, 2 Encounter only
#define HUB_BOS_2_1_x                              (785)
#define HUB_BOS_2_1_y                              (652)
#define HUB_BOS_2_2_x                              (691)
#define HUB_BOS_2_2_y                              (546)

// Hub <--> Brotherhood, 3 Encounter only
#define HUB_BOS_3_1_x                              (781)
#define HUB_BOS_3_1_y                              (694)
#define HUB_BOS_3_2_x                              (698)
#define HUB_BOS_3_2_y                              (595)
#define HUB_BOS_3_3_x                              (675)
#define HUB_BOS_3_3_y                              (493)

// Hub <--> Brotherhood, 4 Encounter only
#define HUB_BOS_4_1_x                              (813)
#define HUB_BOS_4_1_y                              (693)
#define HUB_BOS_4_2_x                              (728)
#define HUB_BOS_4_2_y                              (645)
#define HUB_BOS_4_3_x                              (691)
#define HUB_BOS_4_3_y                              (510)
#define HUB_BOS_4_4_x                              (667)
#define HUB_BOS_4_4_y                              (475)

// Hub <--> Boneyard, 1 Encounter only
#define HUB_ADY_1_1_x                              (820)
#define HUB_ADY_1_1_y                              (817)

// Hub <--> Boneyard, 2 Encounter only
#define HUB_ADY_2_1_x                              (843)
#define HUB_ADY_2_1_y                              (779)
#define HUB_ADY_2_2_x                              (807)
#define HUB_ADY_2_2_y                              (855)

// Hub <--> Boneyard, 3 Encounter only
#define HUB_ADY_3_1_x                              (827)
#define HUB_ADY_3_1_y                              (761)
#define HUB_ADY_3_2_x                              (786)
#define HUB_ADY_3_2_y                              (804)
#define HUB_ADY_3_3_x                              (775)
#define HUB_ADY_3_3_y                              (877)

// Hub <--> Boneyard, 4 Encounter only
#define HUB_ADY_4_1_x                              (834)
#define HUB_ADY_4_1_y                              (723)
#define HUB_ADY_4_2_x                              (815)
#define HUB_ADY_4_2_y                              (771)
#define HUB_ADY_4_3_x                              (824)
#define HUB_ADY_4_3_y                              (818)
#define HUB_ADY_4_4_x                              (822)
#define HUB_ADY_4_4_y                              (877)

// Travel time in days
#define TRAVEL_TIME_HUB_ADY               (2*ONE_GAME_DAY)
#define TRAVEL_TIME_HUB_NEC               (9*ONE_GAME_DAY)
#define TRAVEL_TIME_HUB_BOS               (15*ONE_GAME_DAY)
#define TRAVEL_TIME_HUB_JNK               (7*ONE_GAME_DAY)

// Style of the caravan critters
#define STYLE_NONE         (0)
#define STYLE_CRIMSON      (1)
#define STYLE_FARGO        (2)
#define STYLE_WATER        (3)

#define set_caravan_style_crimson         set_global_var(GVAR_CARAVAN_LOOK,STYLE_CRIMSON)
#define set_caravan_style_fargo           set_global_var(GVAR_CARAVAN_LOOK,STYLE_FARGO)
#define set_caravan_style_water           set_global_var(GVAR_CARAVAN_LOOK,STYLE_WATER)

#define caravan_style_crimson             global_var(GVAR_CARAVAN_LOOK) == STYLE_CRIMSON
#define caravan_style_fargo               global_var(GVAR_CARAVAN_LOOK) == STYLE_FARGO
#define caravan_style_water               global_var(GVAR_CARAVAN_LOOK) == STYLE_WATER

// Caravan States
// GVAR_CARAVAN_STATUS
#define CARAVAN_STATUS_NONE                  (0)
#define CARAVAN_STATUS_WAITING               (1)
#define CARAVAN_STATUS_ON_JOB                (2)
#define CARAVAN_STATUS_SUCCESS               (3)
#define CARAVAN_STATUS_PARTIAL_SUCCESS       (4)
#define CARAVAN_STATUS_FAILED                (5)
#define CARAVAN_STATUS_TOTAL_FAILED          (6)
#define CARAVAN_STATUS_THEFT                 (7)
#define CARAVAN_STATUS_ABANDONED             (8)

// GVAR_CARAVAN_START
// GVAR_CARAVAN_END
#define CARAVAN_NONE                         (0)
#define CARAVAN_HUB                          (1)
#define CARAVAN_JUNKTOWN                     (2)
#define CARAVAN_NECROPOLIS                   (3)
#define CARAVAN_BOS                          (4)
#define CARAVAN_BONEYARD                     (5)

// Hub Caravans
#define HUB_CARAVAN_NONE                     (0)
#define HUB_CARAVAN_AGREED                   (1)
#define HUB_CARAVAN_NOT_READY_YET            (2)
#define HUB_CARAVAN_ABANDONED                (3)
#define HUB_CARAVAN_ON_CARAVAN               (4)
#define HUB_CARAVAN_TOTAL_FAILURE            (5)
#define HUB_CARAVAN_FAILURE                  (6)
#define HUB_CARAVAN_AVERAGE_SUCCESS          (7)
#define HUB_CARAVAN_COMPLETE_SUCCESS         (8)
#define HUB_CARAVAN_THEFT                    (9)

// Set States for the Caravan
#define set_caravan_status(x)                set_global_var(GVAR_CARAVAN_STATUS,x)
#define set_caravan_start(x)                 set_global_var(GVAR_CARAVAN_START,x)
#define set_caravan_end(x)                   set_global_var(GVAR_CARAVAN_END,x)

#define set_caravan_masters(x)               set_global_var(GVAR_CARAVAN_MASTERS_TOTAL,x);      \
                                             set_global_var(GVAR_CARAVAN_MASTERS,x)
#define set_caravan_drivers(x)               set_global_var(GVAR_CARAVAN_DRIVERS_TOTAL,x);      \
                                             set_global_var(GVAR_CARAVAN_DRIVERS,x)
#define set_caravan_guards(x)                set_global_var(GVAR_CARAVAN_GUARDS_TOTAL,x);       \
                                             set_global_var(GVAR_CARAVAN_GUARDS,x)
#define set_caravan_brahmin(x)               set_global_var(GVAR_CARAVAN_BRAHMIN_TOTAL,x);      \
                                             set_global_var(GVAR_CARAVAN_BRAHMIN,x)
#define set_caravan_carts(x)                 set_global_var(GVAR_CARAVAN_CARTS_TOTAL,x);        \
                                             set_global_var(GVAR_CARAVAN_CARTS,x)
#define set_caravan_encounters(x)            set_global_var(GVAR_CARAVAN_ENCOUNTERS_TOTAL,x);   \
                                             set_global_var(GVAR_CARAVAN_ENCOUNTERS,x)

#define CARAVAN_FALSE                        0    // default value of mvar_caravan
#define CARAVAN_HOME                         1    // value of mvar_caravan if at home
#define CARAVAN_GOING_HOME                   2    // value of mvar_caravan if going home
#define CARAVAN_DEST_REACHED                 3    // value of mvar_caravan if dest reached

// Current Counts for the Caravan
#define caravan_masters_left                 global_var(GVAR_CARAVAN_MASTERS)
#define caravan_drivers_left                 global_var(GVAR_CARAVAN_DRIVERS)
#define caravan_guards_left                  global_var(GVAR_CARAVAN_GUARDS)
#define caravan_brahmin_left                 global_var(GVAR_CARAVAN_BRAHMIN)
#define caravan_carts_left                   global_var(GVAR_CARAVAN_CARTS)
#define encounters_left                      global_var(GVAR_CARAVAN_ENCOUNTERS)
#define caravan_status                       global_var(GVAR_CARAVAN_STATUS)

#define caravan_total_masters                global_var(GVAR_CARAVAN_MASTERS_TOTAL)
#define caravan_total_drivers                global_var(GVAR_CARAVAN_DRIVERS_TOTAL)
#define caravan_total_guards                 global_var(GVAR_CARAVAN_GUARDS_TOTAL)
#define caravan_total_brahmin                global_var(GVAR_CARAVAN_BRAHMIN_TOTAL)
#define caravan_total_carts                  global_var(GVAR_CARAVAN_CARTS_TOTAL)

// Set Lost/Destroyed States for Caravan
#define rm_caravan_masters(x)                set_global_var(GVAR_CARAVAN_MASTERS,global_var(GVAR_CARAVAN_MASTERS) - x)
#define rm_caravan_drivers(x)                set_global_var(GVAR_CARAVAN_DRIVERS,global_var(GVAR_CARAVAN_DRIVERS) - x)
#define rm_caravan_guards(x)                 set_global_var(GVAR_CARAVAN_GUARDS,global_var(GVAR_CARAVAN_GUARDS) - x)
#define rm_caravan_brahmin(x)                set_global_var(GVAR_CARAVAN_BRAHMIN,global_var(GVAR_CARAVAN_BRAHMIN) - x)
#define rm_caravan_carts(x)                  set_global_var(GVAR_CARAVAN_CARTS,global_var(GVAR_CARAVAN_CARTS) - x)

// Check Killed/Lost States
#define caravan_masters_killed               (global_var(GVAR_CARAVAN_MASTERS_TOTAL) - global_var(GVAR_CARAVAN_MASTERS))
#define caravan_drivers_killed               (global_var(GVAR_CARAVAN_DRIVERS_TOTAL) - global_var(GVAR_CARAVAN_DRIVERS))
#define caravan_guards_killed                (global_var(GVAR_CARAVAN_GUARDS_TOTAL) - global_var(GVAR_CARAVAN_GUARDS))
#define caravan_brahmin_killed               (global_var(GVAR_CARAVAN_BRAHMIN_TOTAL) - global_var(GVAR_CARAVAN_BRAHMIN))
#define caravan_carts_lost                   (global_var(GVAR_CARAVAN_CARTS_TOTAL) - global_var(GVAR_CARAVAN_CARTS))

// Encounter Information
#define made_encounter                       set_global_var(GVAR_CARAVAN_ENCOUNTERS,global_var(GVAR_CARAVAN_ENCOUNTERS) - 1)
#define total_encounters                     global_var(GVAR_CARAVAN_ENCOUNTERS_TOTAL)
#define caravan_start                        global_var(GVAR_CARAVAN_START)
#define caravan_end                          global_var(GVAR_CARAVAN_END)

// Fo1 doesn't use 2 brahmins per cart
//#define too_many_carts                      ((caravan_carts_left > ((caravan_brahmin_left/2) + (caravan_brahmin_left % 2))) and (caravan_brahmin_left != 0))
#define too_many_carts                       (caravan_carts_left > caravan_brahmin_left)

#define give_money(who,amount)               if (dude_perk(PERK_fortune_finder)) then \
                                                item_caps_adjust(who,2*(amount));     \
                                             else                                     \
                                                item_caps_adjust(who,(amount))

/*********************************************************
    Defines for critter scripts
*********************************************************/
// Used to delete the critter after x time has passed
// IMPORTANT:
//    Can't just delete critters right away, because this can cause nullpointer crashes
//    if the caravan is still in the map while combat starts.
//    Example: https://github.com/rotators/Fo1in2/issues/31
#define check_map_enter_timer                if not(map_is_caravan_escort) then begin                                \
                                                if not(self_visible) then destroy_object(self_obj);                  \
                                                if (local_var(LVAR_CaravanTimer) == 0) then                          \
                                                   set_local_var(LVAR_CaravanTimer, GAME_TIME_IN_HOURS);             \
                                                if (((GAME_TIME_IN_HOURS) - local_var(LVAR_CaravanTimer)) >= 2) then \
                                                   /*destroy_object(self_obj);*/                                         \
                                                   set_self_invisible; \
                                             end

#define check_critter_timer                  if not(map_is_caravan_escort) then begin                                                                          \
                                                if ((((GAME_TIME_IN_HOURS) - local_var(LVAR_CaravanTimer)) >= 2) and (local_var(LVAR_CaravanTimer) != 0)) then \
                                                   /*destroy_object(self_obj);*/ \
                                                   set_self_invisible; \
                                             end

#endif // CARAVAN_H
