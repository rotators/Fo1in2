/*
   Copyright 1998-2003 Interplay Entertainment Corp.  All rights reserved.
*/

#ifndef COMMAND_H
#define COMMAND_H

//Did the above so I could include it in define.h without inheritance problems

/*********************************************************
 define file for commands dealing with the dude.

 Contents of the File:
        I.      Flee from Player
        II.     Player Information
        III.    Dialogue Information
*********************************************************/

// include files that are needed after other declarations are made.
//#include "..\headers\reppoint.h"
#include "reppoint.h"

/*********************************************************
   General stats stuff. Moved here because of Wipe.
*********************************************************/

/*********************************************************
 General interaction dealing with the dude
 should he attack people in a community
*********************************************************/
variable global_temp;

#define Get_Rotation_Away_From_Dude(x)      rotation_to_tile(tile_num(dude_obj),tile_num(x))

#define Run_Away_From_Dude_Dir              Get_Rotation_Away_From_Dude(self_obj)
#define run_away_from_dist                  random(3, 10)
#define push_away_from_dist                 random(2, 5)

#define run_away_tile_dir(x)                tile_num_in_direction(tile_num(self_obj), x, run_away_from_dist)
#define Run_Away_From_Dude_Tile             run_away_tile_dir(Run_Away_From_Dude_Dir)

#define Current_Distance_From_Obj(the_obj)  tile_distance_objs(self_obj,the_obj)
#define Current_Distance_From_Dude          Current_Distance_From_Obj(dude_obj)

#define Future_Distance_From_Obj(x, y)      tile_num_in_direction(tile_num(x), ((has_trait(TRAIT_OBJECT,x,OBJECT_CUR_ROT) + 3)%6), y)
#define Future_Distance_From_Dude(x)        Future_Distance_From_Obj(dude_obj, x)

#define away_from_tile_type(x, type, dist)  if (anim_busy(self_obj) == false) then begin                                                             \
                                               global_temp := rotation_to_tile(x, self_tile);                                                        \
                                               self_##type##_to_tile(tile_num_in_direction(self_tile, global_temp, dist));                        \
                                               global_temp := (global_temp + 1) % 6;                                                                 \
                                               while ((anim_busy(self_obj) == false) and (global_temp != rotation_to_tile(x, self_tile))) do begin   \
                                                  debug_msg("flee loop: rot == "+global_temp);                                                       \
                                                  self_##type##_to_tile(tile_num_in_direction(self_tile, global_temp, dist));                     \
                                                  global_temp := (global_temp + 1) % 6;                                                              \
                                               end                                                                                                   \
                                            end

#define simulate_push(x)                    away_from_tile_type(tile_num_in_direction(self_tile, rotation_to_tile(x, self_tile), 1), walk, push_away_from_dist)
#define flee_from_tile(x)                   away_from_tile_type(x, run, run_away_from_dist)
#define Flee_From_Dude                      if ((Current_Distance_From_Dude < 8) or (self_can_see_dude)) then begin  \
                                               flee_from_tile(dude_tile)                                             \
                                            end

#define Flee_From_Dude_Force                if ((Current_Distance_From_Dude < 8) or (self_can_see_dude)) then begin  \
                                                self_run_to_tile_force(Run_Away_From_Dude_Tile);                  \
                                            end

#define Follow_Dude(X,Y)                    if (Current_Distance_From_Dude > X) then begin                  \
                                               if (Current_Distance_From_Dude > X*2) then begin             \
                                                  self_run_to_tile(Future_Distance_From_Dude(Y));        \
                                               end else begin                                               \
                                                  self_walk_to_tile(Future_Distance_From_Dude(Y));       \
                                               end                                                          \
                                            end

#define get_follow_point_dist(the_obj)      ((tile_distance_objs(the_obj, self_obj) / 5) + 1)
#define follow_obj_point(the_range, the_dist, the_obj)                                                            \
                                            if (Current_Distance_From_Dude > the_range) then begin                \
                                                if (Current_Distance_From_Dude > (the_range * 2)) then begin    \
                                                   anim_run_to_point_rate(tile_num_in_direction(tile_num(the_obj), rotation_to_tile(tile_num(the_obj), self_tile), the_dist), get_follow_point_dist(the_obj))   \
                                                end else begin                                                  \
                                                   anim_move_to_point_rate(tile_num_in_direction(tile_num(the_obj), rotation_to_tile(tile_num(the_obj), self_tile), the_dist), get_follow_point_dist(the_obj))  \
                                                end                                                             \
                                            end
#define party_follow_dude_point(the_range, the_dist)                                                              \
                                            if (Current_Distance_From_Dude > the_range) then begin                \
                                                if (anim_busy(self_obj) == false) then begin                      \
                                                   dest_tile := tile_num_in_direction(tile_num_in_direction(dude_tile, Run_Away_From_Dude_Dir, the_dist), random(0, 5), random(0, 2)); \
                                                   if (Current_Distance_From_Dude > (the_range * 2)) then begin   \
                                                      self_run_to_tile(dest_tile);                             \
                                                   end else begin                                                 \
                                                      self_walk_to_tile(dest_tile);                            \
                                                   end                                                            \
                                                end else if (self_distance_from_dude < tile_distance(self_tile, dest_tile)) then begin  \
                                                   reg_anim_clear(self_obj);                                      \
                                                end                                                               \
                                            end
#define follow_dude_point(the_range, the_dist)     follow_obj_point(the_range, the_dist, dude_obj)

#define Follow_Dude_Run_Only(X,Y)           if (Current_Distance_From_Dude > X) then begin                  \
                                               self_run_to_tile(Future_Distance_From_Dude(Y));           \
                                            end

#define Follow_Obj_Run_Only(O,X,Y)          if (tile_distance_objs(self_obj,O) > X) then begin              \
                                               self_run_to_tile(Future_Distance_From_Obj(O, Y));         \
                                            end
#define Get_In_Obj_Face(the_obj)            if (tile_distance_objs(self_obj, the_obj) > 1) then begin                                                              \
                                               self_walk_to_tile(tile_num_in_direction(tile_num(the_obj), has_trait(TRAIT_OBJECT,the_obj,OBJECT_CUR_ROT), 1));  \
                                            end else if (rotation_to_tile(tile_num(self_obj),tile_num(the_obj)) != self_cur_rot) then begin                        \
                                               if (anim_busy(self_obj) == false) then begin                                                                        \
                                                  Face_Critter(the_obj, self_obj);                                                                                 \
                                               end                                                                                                                 \
                                            end
#define Get_In_Face_Run_Dist(the_obj,dist)  if (tile_distance_objs(self_obj, the_obj) > 1) then begin                                                              \
                                               self_run_to_tile(tile_num_in_direction(tile_num(the_obj), has_trait(TRAIT_OBJECT,the_obj,OBJECT_CUR_ROT), dist));\
                                            end else if (rotation_to_tile(tile_num(self_obj),tile_num(the_obj)) != self_cur_rot) then begin                        \
                                               if (anim_busy(self_obj) == false) then begin                                                                        \
                                                  Face_Critter(the_obj, self_obj);                                                                                 \
                                               end                                                                                                                 \
                                            end

#define next_and_face_obj(the_obj, the_type, the_rate)                                                                                                                       \
                                             if (tile_distance_objs(self_obj, the_obj) > 1) then begin                                                             \
                                                the_type(tile_num_in_direction(tile_num(the_obj), rotation_to_tile(tile_num(the_obj),tile_num(self_obj)), 1), the_rate);     \
                                             end else if (rotation_to_tile(tile_num(self_obj),tile_num(the_obj)) != self_cur_rot) then begin                       \
                                                if (anim_busy(self_obj) == false) then begin                                                                       \
                                                   Face_Critter(the_obj, self_obj);                                                                                \
                                                end                                                                                                                \
                                             end

#define point_next_and_face_obj(the_obj, the_type, the_rate)                                                                                                                 \
                                             if (tile_distance_objs(self_obj, the_obj) > 1) then begin                                                             \
                                                the_type(tile_num_in_direction(tile_num(the_obj), rotation_to_tile(tile_num(the_obj),tile_num(self_obj)), 1), the_rate) \
                                             end else if (rotation_to_tile(tile_num(self_obj),tile_num(the_obj)) != self_cur_rot) then begin                       \
                                                if (anim_busy(self_obj) == false) then begin                                                                       \
                                                   Face_Critter(the_obj, self_obj);                                                                                \
                                                end                                                                                                                \
                                             end

#define Get_Next_To_Obj_And_Face_Rate(the_obj, x)     next_and_face_obj(the_obj, self_walk_to_tile, x)
#define Get_Next_To_Obj_And_Face(the_obj)             next_and_face_obj(the_obj, self_walk_to_tile, 1)
#define Run_Next_To_Obj_And_Face_Rate(the_obj, x)     next_and_face_obj(the_obj, self_run_to_tile, x)
#define Run_Next_To_Obj_And_Face(the_obj)             next_and_face_obj(the_obj, self_run_to_tile, 1)
#define point_move_next_and_face_Rate(the_obj, x)     point_next_and_face_obj(the_obj, anim_move_to_point, x)
#define point_move_next_and_face(the_obj)             point_next_and_face_obj(the_obj, anim_move_to_point, 1)
#define point_run_next_and_face_Rate(the_obj, x)      point_next_and_face_obj(the_obj, anim_run_to_point, x)
#define point_run_next_and_face(the_obj)              point_next_and_face_obj(the_obj, anim_run_to_point, 1)

// the Z is a variable LOCAL variable that stores the tile where the dude was last time it was told to follow
//    this will keep the animation for the follow clean

#define closest_clear_tile(obj, the_tile, x)       x := the_tile;                                                                   \
                                                   while ((x != tile_num(obj)) and (tile_is_blocked(x, elevation(obj)))) do begin   \
                                                      x := tile_num_in_direction(x, rotation_to_tile(x, tile_num(obj)), 1);         \
                                                   end
// this is like the above but uses to regular variables instead of local vars
// this steps like the old step macro, but it's faster and better
//
variable dest_tile;
variable step_tile;
#define FAIL_STEP_ACTION                           if (tile_get_next_critter(tile_num_in_direction(self_tile, self_cur_rot, 1), self_elevation, 0) != 0) then begin \
                                                      simulate_push(tile_num_in_direction(self_tile, self_cur_rot, 1))                                                                                                 \
                                                   end else step_tile := -10;
//#define FAIL_STEP_ACTION                           step_tile := -5;
#define move_to_point(the_tile, move_type, x)                                                                                                                                    \
                                                   if ((self_tile != the_tile) and (the_tile != 0)) then begin                                                                                  \
                                                      if ((dest_tile == the_tile) and (step_tile < 0)) then begin                                                                               \
                                                         step_tile += 1;                                                                                                                        \
                                                      end else if (anim_busy(self_obj) == false) then begin                                                                                     \
                                                         dest_tile := the_tile;                                                                                                                 \
                                                         step_tile := the_tile;                                                                                                                 \
                                                         self_##move_type##_to_tile(step_tile);                                                                                              \
                                                         while ((anim_busy(self_obj) == false) and (((tile_distance(self_tile, the_tile)) >= (tile_distance(step_tile, the_tile))))) do begin   \
                                                            step_tile := tile_num_in_direction(step_tile, rotation_to_tile(step_tile, self_tile), (x % tile_distance(step_tile, self_tile)) + 1);   \
                                                            self_##move_type##_to_tile(step_tile);                                                                                           \
                                                         end                                                                                                                                    \
                                                         if (anim_busy(self_obj) == false) then begin                                                                                           \
                                                            FAIL_STEP_ACTION                                                                                                                    \
                                                         end                                                                                                                                    \
                                                      end else if ((tile_distance(self_tile, the_tile)) < (tile_distance(dest_tile, the_tile))) then begin                                        \
                                                         reg_anim_clear(self_obj);                                                                                                              \
                                                      end                                                                                                                                       \
                                                   end

#define anim_move_to_point_rate(the_tile, x)       move_to_point(the_tile, walk, x)
#define anim_move_to_point(the_tile)               anim_move_to_point_rate(the_tile, 1)
#define anim_run_to_point_rate(the_tile, x)        move_to_point(the_tile, run, x)
#define anim_run_to_point(the_tile)                anim_run_to_point_rate(the_tile, 1)

// BIG REORDER, for bored people, starts HERE //
//
// misc singletons
//

#define self_pid                          obj_pid(self_obj)

//
// misc tuples
//
#define dude_walk_to_tile(tile)           animate_move_obj_to_tile(dude_obj,tile,ANIMATE_WALK)
#define self_walk_to_tile(tile)           animate_move_obj_to_tile(self_obj,tile,ANIMATE_WALK)

#define dude_walk_to_tile_force(tile)     animate_move_obj_to_tile(dude_obj,tile,ANIMATE_WALK_FORCE)
#define self_walk_to_tile_force(tile)     animate_move_obj_to_tile(self_obj,tile,ANIMATE_WALK_FORCE)

#define dude_run_to_tile(tile)            animate_move_obj_to_tile(dude_obj,tile,ANIMATE_RUN)
#define self_run_to_tile(tile)            animate_move_obj_to_tile(self_obj,tile,ANIMATE_RUN)

#define dude_run_to_tile_force(tile)      animate_move_obj_to_tile(self_obj,tile,ANIMATE_RUN_FORCE)
#define self_run_to_tile_force(tile)      animate_move_obj_to_tile(self_obj,tile,ANIMATE_RUN_FORCE)

#define dude_stand                        animate_stand_obj(dude_obj)
#define self_stand                        animate_stand_obj(self_obj)

#define dude_stand_reverse                animate_stand_reverse_obj(dude_obj)
#define self_stand_reverse                animate_stand_reverse_obj(self_obj)

#define dude_set_frame(frame)             anim(dude_obj,ANIMATE_SET_FRAME,frame)
#define self_set_frame(frame)             anim(self_obj,ANIMATE_SET_FRAME,frame)

#undef  dude_elevation
#undef  self_elevation
#define dude_elevation                    elevation(dude_obj)
#define self_elevation                    elevation(self_obj)
#define source_elevation                  elevation(source_obj)

#define dude_fid                          obj_art_fid(dude_obj)
#define self_fid                          obj_art_fid(self_obj)

#define dude_can_see_self                 obj_can_see_obj(dude_obj,self_obj)
#define self_can_see_dude                 obj_can_see_obj(self_obj,dude_obj)

#define dude_can_hear_self                obj_can_hear_obj(dude_obj,self_obj)
#define self_can_hear_dude                obj_can_hear_obj(self_obj,dude_obj)

#define dude_name                         obj_name(dude_obj)
#define self_name                         obj_name(self_obj)

#define dude_caps                         item_caps_total(dude_obj)
#define self_caps                         item_caps_total(self_obj)

#define dude_caps_adjust(caps)            item_caps_adjust(dude_obj,caps)
#define self_caps_adjust(caps)            item_caps_adjust(self_obj,caps)
#define fortune_finder(caps)              (caps * (dude_perk(PERK_fortune_finder) + 1))

#undef  dude_tile
#undef  self_tile
#define dude_tile                         tile_num(dude_obj)
#define self_tile                         tile_num(self_obj)
#define source_tile                       tile_num(source_obj)

#define dude_rotation_to_self             rotation_to_tile(dude_tile,self_tile)
#define self_rotation_to_dude             rotation_to_tile(self_tile,dude_tile)

#define dude_look_at_self                 anim(dude_obj,ANIMATE_ROTATION,dude_rotation_to_self)
#define self_look_at_dude                 anim(self_obj,ANIMATE_ROTATION,self_rotation_to_dude)

#define dude_is_sneaking                  using_skill(dude_obj,SKILL_SNEAK)
#define self_is_sneaking                  using_skill(self_obj,SKILL_SNEAK)
//
// gear
//

#define get_left_hand(cr)                 critter_inven_obj(cr,INVEN_TYPE_LEFT_HAND)
#define dude_left_hand                    get_left_hand(dude_obj)
#define self_left_hand                    get_left_hand(self_obj)

#define get_right_hand(cr)                critter_inven_obj(cr,INVEN_TYPE_RIGHT_HAND)
#define dude_right_hand                   get_right_hand(dude_obj)
#define self_right_hand                   get_right_hand(self_obj)

#define get_armor(cr)                     critter_inven_obj(cr,INVEN_TYPE_WORN)
#define dude_armor                        get_armor(dude_obj)
#define self_armor                        get_armor(self_obj)

//
// SPECIAL
//

#define get_strength(cr)                  get_critter_stat(cr,STAT_st)
#define dude_strength                     get_strength(dude_obj)
#define self_strength                     get_strength(self_obj)

#define get_perception(cr)                get_critter_stat(cr,STAT_pe)
#define dude_perception                   get_perception(dude_obj)
#define self_perception                   get_perception(self_obj)

#define get_endurance(cr)                 get_critter_stat(cr,STAT_en)
#define dude_endurance                    get_endurance(dude_obj)
#define self_endurance                    get_endurance(self_obj)

#define get_charisma(cr)                  get_critter_stat(cr,STAT_ch)
#define dude_charisma                     get_charisma(dude_obj)
#define self_charisma                     get_charisma(self_obj)

#define get_iq(cr)                        get_critter_stat(cr,STAT_iq)
#define dude_iq                           get_iq(dude_obj)
#define self_iq                           get_iq(self_obj)

#define get_agility(cr)                   get_critter_stat(cr,STAT_ag)
#define dude_agility                      get_agility(dude_obj)
#define self_agility                      get_agility(self_obj)

#define get_luck(cr)                      get_critter_stat(cr,STAT_lu)
#define dude_luck                         get_luck(dude_obj)
#define self_luck                         get_luck(self_obj)

//
// SPECIAL extras
//
#define dude_is_stupid                    (dude_iq <= 3)

//
// hit points
//

#define get_cur_hp(cr)                    get_critter_stat(cr,STAT_current_hp)
#define dude_cur_hp                       get_cur_hp(dude_obj)
#define self_cur_hp                       get_cur_hp(self_obj)

#define get_max_hp(cr)                    get_critter_stat(cr,STAT_max_hp)
#define dude_max_hp                       get_max_hp(dude_obj)
#define self_max_hp                       get_max_hp(self_obj)

//
// rads
//

#define get_rads(cr)                      get_critter_stat(cr,STAT_current_rad)
#define dude_rads                         get_rads(dude_obj)
#define self_rads                         get_rads(self_obj)

//
// poison
//

// possibly broken or something
//#define dude_poison                     get_poison(dude_obj)
//#define self_poison                     get_poison(self_obj)

#define  get_poison_stat(cr)              get_critter_stat(cr,STAT_current_poison)
#define dude_poison_stat                  get_poison_stat(dude_obj)
#define self_poison_stat                  get_poison_stat(self_obj)

//
// gender
//

#define  get_gender(cr)                   get_critter_stat(cr,STAT_gender)
#define dude_gender                       get_gender(dude_obj)
#define self_gender                       get_gender(self_obj)

#define  get_is_male(cr)                  (get_gender(cr) == GENDER_MALE)
#define dude_is_male                      get_is_male(dude_obj)
#define self_is_male                      get_is_male(self_obj)

#define  get_is_female(cr)                (get_gender(cr) == GENDER_FEMALE)
#define dude_is_female                    get_is_female(dude_obj)
#define self_is_female                    get_is_female(self_obj)

//
// perks
//

#define  get_perk(cr,perk)                has_trait(TRAIT_PERK,cr,perk)
#define dude_perk(perk)                   get_perk(dude_obj,perk)
#define self_perk(perk)                   get_perk(self_obj,perk)

//
// traits
//

#define  get_trait(cr,trait)              has_trait(TRAIT_TRAIT,cr,trait)
#define dude_trait(trait)                 get_trait(dude_obj,trait)
#define self_trait(trait)                 get_trait(self_obj,trait)

//
// AI
//

#define get_ai(cr)                        has_trait(TRAIT_OBJECT,cr,OBJECT_AI_PACKET)
#define self_ai                           get_ai(self_obj)

#define set_ai(cr,ai)                     critter_add_trait(cr,TRAIT_OBJECT,OBJECT_AI_PACKET,ai)
#define set_self_ai(ai)                   set_ai(self_obj,ai)

//
// team
//

#define get_team(cr)                      has_trait(TRAIT_OBJECT,cr,OBJECT_TEAM_NUM)
#define self_team                         get_team(self_obj)

#define set_team(cr,team)                 critter_add_trait(cr,TRAIT_OBJECT,OBJECT_TEAM_NUM,team)
#define set_self_team(team)               set_team(self_obj,team)

//
// Rotators, rotate!
//

#define obj_rotate(obj,dir)               anim(obj,ANIMATE_ROTATION,dir)
#define dude_rotate(dir)                  obj_rotate(dude_obj,dir)
#define self_rotate(dir)                  obj_rotate(self_obj,dir)


//
// items
//
#define get_item(cr,pid)                  obj_carrying_pid_obj(cr,pid) // due to shitty && confusing naming
#define dude_item(pid)                    get_item(dude_obj,pid)
#define self_item(pid)                    get_item(self_obj,pid)

#define get_item_count(cr,pid)            obj_is_carrying_obj_pid(cr,pid) // due to shitty && confusing naming
#define dude_item_count(pid)              get_item_count(dude_obj,pid)
#define self_item_count(pid)              get_item_count(self_obj,pid)

//
// misc triplets
//

#define get_cur_rot(cr)                   has_trait(TRAIT_OBJECT,cr,OBJECT_CUR_ROT)
#define dude_cur_rot                      get_cur_rot(dude_obj)
#define self_cur_rot                      get_cur_rot(self_obj)

// BIG REORDER, for bored people, ends HERE //

// map variables that share the same number throught the maps are listed here

#define critter_is_armed(x)                 (((obj_item_subtype(critter_inven_obj(x,INVEN_TYPE_RIGHT_HAND))) == item_type_weapon) or \
                                             ((obj_item_subtype(critter_inven_obj(x,INVEN_TYPE_LEFT_HAND))) == item_type_weapon))
#define critter_weight(x)                   (100 + ((get_critter_stat(x,STAT_gender) == GENDER_MALE) * 50) + (get_critter_stat(x,STAT_st) * 5) - ((get_critter_stat(x,STAT_ag) + get_critter_stat(x,STAT_en))/3))
#define critter_wearing_armor(x)            (obj_item_subtype(critter_inven_obj(x,INVEN_TYPE_WORN)) == item_type_armor)

#ifndef dude_level
#define dude_level                          (get_pc_stat(PCSTAT_level))
#endif
#define dude_age                            (get_critter_stat(dude_obj,STAT_age))
#define dude_weight                         critter_weight(dude_obj)

#define dude_is_armed                       critter_is_armed(dude_obj)
#define dude_wearing_armor                  critter_wearing_armor(dude_obj)

#define dude_has_power_armor                (((obj_is_carrying_obj_pid(dude_obj, PID_POWERED_ARMOR)) +            \
                                              (obj_is_carrying_obj_pid(dude_obj, PID_ADVANCED_POWER_ARMOR)) +     \
                                              (obj_is_carrying_obj_pid(dude_obj, PID_ADVANCED_POWER_ARMOR_MK2)) + \
                                              (obj_is_carrying_obj_pid(dude_obj, PID_HARDENED_POWER_ARMOR))) > 0)

#define dude_wielding_knife                 ((obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_RIGHT_HAND)) == PID_KNIFE) or                \
                                             (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_RIGHT_HAND)) == PID_THROWING_KNIFE) or       \
                                             (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_RIGHT_HAND)) == PID_RIPPER) or               \
                                             (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_RIGHT_HAND)) == PID_COMBAT_KNIFE) or         \
                                             (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_LEFT_HAND)) == PID_KNIFE) or                 \
                                             (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_LEFT_HAND)) == PID_THROWING_KNIFE) or        \
                                             (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_LEFT_HAND)) == PID_RIPPER) or                \
                                             (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_LEFT_HAND)) == PID_COMBAT_KNIFE))

#define dude_wearing_power_armor            ((dude_armor == PID_POWERED_ARMOR) or \
                                             (dude_armor == PID_ADVANCED_POWER_ARMOR) or \
                                             (dude_armor == PID_ADVANCED_POWER_ARMOR_MK2) or \
                                             (dude_armor == PID_HARDENED_POWER_ARMOR))

#define dude_wearing_bos_power_armor        ((dude_armor == PID_POWERED_ARMOR) or \
                                             (dude_armor == PID_HARDENED_POWER_ARMOR))

#define critter_wearing_power_armor(x)      ((obj_pid(critter_inven_obj(x,INVEN_TYPE_WORN)) == PID_POWERED_ARMOR) or \
                                             (obj_pid(critter_inven_obj(x,INVEN_TYPE_WORN)) == PID_ADVANCED_POWER_ARMOR) or \
                                             (obj_pid(critter_inven_obj(x,INVEN_TYPE_WORN)) == PID_ADVANCED_POWER_ARMOR_MK2) or \
                                             (obj_pid(critter_inven_obj(x,INVEN_TYPE_WORN)) == PID_HARDENED_POWER_ARMOR))

#define dude_wearing_leather_armor          ((dude_armor == PID_LEATHER_ARMOR) or \
                                             (dude_armor == PID_LEATHER_JACKET) or \
                                             (dude_armor == PID_LEATHER_ARMOR_MK_II) or \
                                             (dude_armor == PID_CURED_LEATHER_ARMOR))

#define dude_wearing_combat_armor           ((dude_armor == PID_COMBAT_ARMOR) or \
                                             (dude_armor == PID_BROTHERHOOD_COMBAT_ARMOR) or \
                                             (dude_armor == PID_COMBAT_ARMOR_MK_II))

#define dude_wearing_metal_armor            ((dude_armor == PID_METAL_ARMOR) or \
                                             (dude_armor == PID_METAL_ARMOR_MK_II))

#define dude_wearing_vault_suit             (dude_armor == 0 or dude_armor == PID_V13_VSUIT)

#define dude_has_gambling_skills            ((dude_iq > 3) and (has_skill(dude_obj, SKILL_GAMBLING) >= 25))

#define dude_is_walking                     (art_anim(dude_fid) == ANIM_walk)
#define dude_is_running                     (art_anim(dude_fid) == ANIM_running)
#define dude_is_crippled                    ((critter_state(dude_obj) bwand DAM_CRIP_LEG_LEFT)  or \
                                             (critter_state(dude_obj) bwand DAM_CRIP_LEG_RIGHT) or \
                                             (critter_state(dude_obj) bwand DAM_CRIP_ARM_LEFT)  or \
                                             (critter_state(dude_obj) bwand DAM_CRIP_ARM_RIGHT))

#define dude_inv_rot                        ((dude_cur_rot + 3)%6)

#define tile_behind_obj(who)                (tile_num_in_direction(tile_num(who),((has_trait(TRAIT_OBJECT,who,OBJECT_CUR_ROT) + 3) % 6), 1))
#define tile_behind_obj_rng(who, rng)       (tile_num_in_direction(tile_num(who),((has_trait(TRAIT_OBJECT,who,OBJECT_CUR_ROT) + 3) % 6), rng))



#define dude_has_car                        global_var(GVAR_PLAYER_GOT_CAR) != 0
#define dude_is_pornstar                    dude_has_porn_star_rep
#define dude_is_high                        drug_influence(dude_obj)


#define dude_stat_win(X,Y)                  ((do_check(dude_obj,X,Y)) > (do_check(self_obj,X,0)))
#define dude_stat_lose(X,Y)                 ((do_check(dude_obj,X,Y)) < (do_check(self_obj,X,0)))
#define dude_stat_tie(X,Y)                  ((do_check(dude_obj,X,Y)) == (do_check(self_obj,X,0)))

#define dude_is_addict                      (has_trait(TRAIT_TRAIT, dude_obj, TRAIT_drug_addict))

// spouse related
#define spouse_none                       (0)
#define spouse_female                     (1)
#define spouse_male                       (2)
#define dude_spouse_is_male               (global_var(GVAR_PLAYER_MARRIED) == spouse_male)
#define dude_spouse_is_female             (global_var(GVAR_PLAYER_MARRIED) == spouse_female)
#define dude_is_married                   (global_var(GVAR_PLAYER_MARRIED) != spouse_none)
#define set_dude_married                  if ((dude_is_married == false) and (dude_was_married == false)) then begin    \
                                             if (NAME == SCRIPT_MCDAVIN) then begin                                     \
                                                set_global_var(GVAR_PLAYER_MARRIED, spouse_male);                       \
                                             end else if (NAME == SCRIPT_MCMIRIA) then begin                                                             \
                                                set_global_var(GVAR_PLAYER_MARRIED, spouse_female);                     \
                                             end                                                                        \
                                          end                                                                           \
                                          debug_msg("set_dude_married")
#define dude_spouse_was_male              (global_var(GVAR_PLAYER_WAS_MARRIED) == spouse_male)
#define dude_spouse_was_female            (global_var(GVAR_PLAYER_WAS_MARRIED) == spouse_female)
#define dude_was_married                  (global_var(GVAR_PLAYER_WAS_MARRIED) != 0)
#define set_dude_was_married              debug_msg("start: set_dude_was_married");                                     \
                                          if ((dude_is_married) and (dude_was_married == false)) then begin             \
                                             debug_msg("   GVAR_PLAYER_WAS_MARRIED before == " + global_var(GVAR_PLAYER_WAS_MARRIED)); \
                                             set_global_var(GVAR_PLAYER_WAS_MARRIED, global_var(GVAR_PLAYER_MARRIED));  \
                                             debug_msg("   GVAR_PLAYER_WAS_MARRIED after == " + global_var(GVAR_PLAYER_WAS_MARRIED));  \
                                             set_global_var(GVAR_PLAYER_MARRIED, spouse_none);                          \
                                          end                                                                           \
                                          debug_msg("finished: set_dude_was_married")

/*********************************************************
 General information dealing with a critter script
*********************************************************/
#define self_attack_dude                    if (critter_is_fleeing(self_obj)) then begin        \
                                               if (anim_busy(self_obj) == false) then begin     \
                                                  Flee_From_Dude                                \
                                               end                                              \
                                            end else attack(dude_obj)


#define self_is_armed                       critter_is_armed(self_obj)
#define self_wearing_armor                  critter_wearing_armor(self_obj)

#define self_carrying_laser_pistol          ((obj_pid(critter_inven_obj(self_obj,INVEN_TYPE_LEFT_HAND)) == PID_LASER_PISTOL) or \
                                             (obj_pid(critter_inven_obj(self_obj,INVEN_TYPE_RIGHT_HAND)) == PID_LASER_PISTOL))

#define self_is_walking                     (art_anim(self_fid) == ANIM_walk)
#define self_is_running                     (art_anim(self_fid) == ANIM_running)

#define self_inv_rot                        ((self_cur_rot + 3)%6)

#define skill_success(x,y,z)                (is_success(roll_vs_skill(x,y,z)))
#define stat_success(x,y,z)                 (is_success(do_check(x,y,z)))

#define self_distance_from_dude             tile_distance(self_tile, dude_tile)
#define self_is_high                        drug_influence(self_obj)

// some timer event macros
#define check_set_obj_visiblility(the_obj, x)       if (obj_is_visible_flag(the_obj) == x) then set_obj_visibility(the_obj, x)

#define flush_add_timer_event(obj, time, param)    rm_fixed_timer_event(obj, param);               \
                                                   add_timer_event(obj, time, param)
#define flush_add_timer_event_sec(obj, sec, param) flush_add_timer_event(obj, game_ticks(sec), param)

/******************************************************************
 General commands getting information about time
******************************************************************/

#define morning                             ((game_time_hour >= 600) and  (game_time_hour < 700))
#ifndef day
#define day                                 ((game_time_hour >= 700) and  (game_time_hour < 1800))
#endif
#define evening                             ((game_time_hour >= 1800) and (game_time_hour < 1900))
#ifndef night
#define night                               ((game_time_hour >= 1900) or  (game_time_hour < 600))
#endif

#define GAME_TIME_SUBSECOND_RESOLUTION  (10)
#define SECONDS_PER_MINUTE              (60)
#define MINUTES_PER_HOUR                (60)
#define HOURS_PER_DAY                   (24)
#define DAYS_PER_YEAR                   (365)
                                // Seconds Minutes Hours Days Months ==> Year
#define GAME_TIME_IN_YEARS   (game_time / (GAME_TIME_SUBSECOND_RESOLUTION * SECONDS_PER_MINUTE * MINUTES_PER_HOUR * HOURS_PER_DAY * DAYS_PER_YEAR))
#define GAME_TIME_IN_DAYS    (game_time / (GAME_TIME_SUBSECOND_RESOLUTION * SECONDS_PER_MINUTE * MINUTES_PER_HOUR * HOURS_PER_DAY))
#define GAME_TIME_IN_HOURS   (game_time / (GAME_TIME_SUBSECOND_RESOLUTION * SECONDS_PER_MINUTE * MINUTES_PER_HOUR))
#define GAME_TIME_IN_MINUTES (game_time / (GAME_TIME_SUBSECOND_RESOLUTION * SECONDS_PER_MINUTE))
#define GAME_TIME_IN_SECONDS (game_time / GAME_TIME_SUBSECOND_RESOLUTION)


#define ticks_til_hour(x)                 ((ONE_GAME_DAY * (game_time_hour > (x))) + ((((x)/100) - (game_time_hour/100)) * ONE_GAME_HOUR) + ((((x)%100) - (game_time_hour%100)) * ONE_GAME_MINUTE))
#define game_time_advance_hour(x)         game_time_advance(ticks_til_hour(x))

// use times in define.h for passed_time(example: ONE_GAME_DAY)
#define time_has_passed(old_time, passed_time)      ((passed_time + old_time) <= game_time)
// get the actual amout of time that has passed
#define amt_time_has_passed(old_time, time_unit)  ((game_time - old_time) / time_unit)

#define one_second_passed(old_time)       time_has_passed(old_time,ONE_GAME_SECOND)
#define one_minute_passed(old_time)       time_has_passed(old_time,ONE_GAME_MINUTE)
#define one_hour_passed(old_time)         time_has_passed(old_time,ONE_GAME_HOUR)
#define one_day_passed(old_time)          time_has_passed(old_time,ONE_GAME_DAY)
#define one_week_passed(old_time)         time_has_passed(old_time,ONE_GAME_WEEK)
#define one_month_passed(old_time)        time_has_passed(old_time,ONE_GAME_MONTH)

/***************************************************************
****************  Dialogue Information   ***********************
***************************************************************/
#ifndef floater
   #define floater(x)           float_msg(self_obj, message_str(NAME,x), FLOAT_COLOR_NORMAL)
#endif
#define floater_rand(x,y)       floater(random(x,y))

#define dude_floater(x)         float_msg(dude_obj, message_str(NAME,x), FLOAT_COLOR_NORMAL)
#define dude_floater_rand(x,y)  dude_floater(random(x,y))
#define dude_floater_bad(x)     float_msg(dude_obj, message_str(NAME,x), FLOAT_COLOR_BAD)
#define dude_floater_sick(x)    float_msg(dude_obj, message_str(NAME,x), FLOAT_COLOR_SICK)

variable in_dialog;
variable forced_node;

#define start_dialog(X,Y)                       start_gdialog(-1,X,Y,-1,-1)

#define start_dialog_at_node(x)                       if (in_dialog == false) then begin           \
                                                         in_dialog := true;                        \
                                                         start_gdialog(NAME,self_obj,4,-1,-1);     \
                                                         gSay_Start;                               \
                                                            call x;                                \
                                                         gSay_End;                                 \
                                                         end_dialogue;                             \
                                                         in_dialog := false;                       \
                                                      end else call x

#define force_dialog_start(the_node)            debug_msg("force_dialog_start("+forced_node+"): "+self_name);  \
                                                      forced_node := the_node;                                    \
                                                      dialogue_system_enter

#define check_forced_dialog                           if (forced_node != 0) then begin          \
                                                         debug_msg("calling forced dialog: "+forced_node);\
                                                         start_dialog_at_node(forced_node);     \
                                                         forced_node := 0;                      \
                                                      end

variable tmp_rotation;
#define face_start_dialog_at_node(x)         tmp_rotation:=self_cur_rot;         \
                                    Face_Critter(dude_obj,self_obj);    \
                                    Face_Critter(self_obj,dude_obj);    \
                                    start_dialog_at_node(x);         \
                                    self_rotate(tmp_rotation)

/*
FLOAT_MSG_BLACK
FLOAT_MSG_PURPLE
FLOAT_MSG_NEAR_WHITE
FLOAT_MSG_BLUE
*/
#define FLOAT_COLOR_NORMAL          FLOAT_MSG_YELLOW
#define FLOAT_COLOR_SICK            FLOAT_MSG_GREEN
#define FLOAT_COLOR_BAD             FLOAT_MSG_RED
#define FLOAT_COLOR_GOOD            FLOAT_MSG_WHITE
#define FLOAT_COLOR_SFX             FLOAT_MSG_LIGHT_GREY
#define FLOAT_COLOR_SAD             FLOAT_MSG_GREY
#define FLOAT_COLOR_AFRAID          FLOAT_MSG_LIGHT_RED
#define FLOAT_COLOR_PAIN            FLOAT_MSG_LIGHT_GREY
#define FLOAT_COLOR_HIGH            FLOAT_MSG_PURPLE
#define FLOAT_COLOR_WHISPER         FLOAT_MSG_GREY

#define obj_floater_type(z,x,type)  float_msg(z, x, FLOAT_COLOR_NORMAL + ((type - FLOAT_COLOR_NORMAL) * has_trait(TRAIT_PERK, dude_obj, PERK_empathy)))
#define floater_type_msg(x, type)   obj_floater_type(self_obj, x, type)
#define floater_type(x, type)       floater_type_msg(mstr(x), type)
#define floater_bad(x)              floater_type(x, FLOAT_COLOR_BAD)
#define floater_bad_rand(x,y)       floater_bad(random(x,y))
#define floater_sick(x)             floater_type(x, FLOAT_COLOR_SICK)
#define floater_sick_rand(x,y)      floater_sick(random(x,y))
#define floater_afraid(x)           floater_type(x, FLOAT_COLOR_AFRAID)
#define floater_afraid_rand(x,y)    floater_afraid(random(x,y))
#define floater_high(x)             floater_type(x, FLOAT_COLOR_HIGH)
#define floater_high_rand(x,y)      floater_high(random(x,y))
#define floater_good(x)             floater_type(x, FLOAT_COLOR_GOOD)
#define floater_good_rand(x,y)      floater_good(random(x,y))

#define mstr(x)                     message_str(NAME,x)
#define display_mstr(x)             display_msg(mstr(x))
#define gen_mstr(x)                 message_str(SCRIPT_GENCHAT,x) // Fallout 1
#define g_mstr(x)                   message_str(SCRIPT_GENERIC,x) // Fallout 2
#define g_grunt                     g_mstr(random(300,303))
#define g_bye                       g_mstr(random(375,376))
#define g_more                      message_str(SCRIPT_MODREACT,106)
#define g_done                      message_str(SCRIPT_MODREACT,108)

#define LOW_IQ                      (-3)

#define Reply(x)                    gSay_Reply(NAME,x)
#define Reply_Rand(x,y)             Reply(random(x,y))
#define GMessage(x)                 gSay_Message(NAME,x,GOOD_REACTION)
#define NMessage(x)                 gSay_Message(NAME,x,NEUTRAL_REACTION)
#define BMessage(x)                 gSay_Message(NAME,x,BAD_REACTION)
#define RMessage(x)                 gSay_Message(NAME,x,RND_REACTION)

// this converts a number from 0-100 to the text representing the number, ie: 1 -> "one", 40 -> "forty-one"
#define num_to_num_text(x)          g_mstr(2000+x)

// Option(Message Number, Node Number, IQ)         ==>     giQ_Option(IQ, Message Number, Node Number)      -rwh2 (11/12/97)
#define GOption(x,y,z)              giQ_Option(z,NAME,x,y,GOOD_REACTION)
#define NOption(x,y,z)              giQ_Option(z,NAME,x,y,NEUTRAL_REACTION)
#define BOption(x,y,z)              giQ_Option(z,NAME,x,y,BAD_REACTION)
#define ROption(x,y,z)              giQ_Option(z,NAME,x,y,RND_REACTION)
#define GLowOption(x,y)             giQ_Option(LOW_IQ,NAME,x,y,GOOD_REACTION)
#define NLowOption(x,y)             giQ_Option(LOW_IQ,NAME,x,y,NEUTRAL_REACTION)
#define BLowOption(x,y)             giQ_Option(LOW_IQ,NAME,x,y,BAD_REACTION)
#define RLowOption(x,y)             giQ_Option(LOW_IQ,NAME,x,y,RND_REACTION)

#define display_mstr_rand(x,y)      display_msg(mstr(random(x,y)))

/***************************************************************
****************  Global Variable commands *********************
***************************************************************/
#define inc_global_var_amt(x,y)     set_global_var(x,global_var(x)+y)
#define inc_global_var(x)           inc_global_var_amt(x,1)
#define dec_global_var_amt(x,y)     set_global_var(x,global_var(x)-y)
#define dec_global_var(x)           dec_global_var_amt(x,1)

/***************************************************************
****************  map Variable commands ************************
***************************************************************/
#define inc_map_var_amt(x,y)        set_map_var(x,map_var(x)+y)
#define inc_map_var(x)              inc_map_var_amt(x,1)
#define dec_map_var_amt(x,y)        set_map_var(x,map_var(x)-y)
#define dec_map_var(x)              dec_map_var_amt(x,1)

/***************************************************************
****************  Local Variable commands **********************
***************************************************************/
#define inc_local_var_amt(x,y)      set_local_var(x,local_var(x)+y)
#define inc_local_var(x)            inc_local_var_amt(x,1)
#define dec_local_var_amt(x,y)      set_local_var(x,local_var(x)-y)
#define dec_local_var(x)            dec_local_var_amt(x,1)

/***************************************************************
**************** Bit Manipulation Macros ***********************
***************************************************************/
#define MAXINT 4294967295                 //Max int
#define INV(x) (MAXINT - x)               //An inverse function

// get bit state
#define gvar_bit(x, the_bit)                          ((global_var(x) bwand the_bit) != 0)
#define mvar_bit(x, the_bit)                          ((map_var(x) bwand the_bit) != 0)
#define lvar_bit(x, the_bit)                          ((local_var(x) bwand the_bit) != 0)

// switch bit on
#define set_gvar_bit_on(x, the_bit)                   set_global_var(x, global_var(x) bwor the_bit)
#define set_mvar_bit_on(x, the_bit)                   set_map_var(x, map_var(x) bwor the_bit)
#define set_lvar_bit_on(x, the_bit)                   set_local_var(x, local_var(x) bwor the_bit)

// switch bit off
#define set_gvar_bit_off(x, the_bit)                  set_global_var(x, global_var(x) bwand INV(the_bit))
#define set_mvar_bit_off(x, the_bit)                  set_map_var(x, map_var(x) bwand INV(the_bit))
#define set_lvar_bit_off(x, the_bit)                  set_local_var(x, local_var(x) bwand INV(the_bit))

// truncates a number
#define trunc(x)                (x * -(x<1))

/******************************************************************
 General commands getting information about a critter
******************************************************************/
/*#define critter_is_armed        (((obj_item_subtype(critter_inven_obj(self_obj,INVEN_TYPE_RIGHT_HAND))) == item_type_weapon)  \
                                or ((obj_item_subtype(critter_inven_obj(self_obj,INVEN_TYPE_LEFT_HAND))) == item_type_weapon))
*/
/******************************************************************
 General commands setting and getting the map exit
******************************************************************/
// note set either exit or next to 0 for invalid
#define set_map_exit_tiles(the_exit,the_next)     set_global_var(GVAR_MAP_EXIT_TILE,the_exit);  set_global_var(GVAR_MAP_NEXT_TILE,the_next)
#define map_exit_tile                             (global_var(GVAR_MAP_EXIT_TILE))
#define map_next_tile                             (global_var(GVAR_MAP_NEXT_TILE))

/******************************************************************
 General commands for checking and changing status variables
         note: variable needs to be global for the functions to work
         note: the defines for the status's are in GLOBAL.H
******************************************************************/
#define change_status_on(status_var, which_status)    set_gvar_bit_on(status_var, which_status);
#define change_status_off(status_var, which_status)   set_gvar_bit_off(status_var, which_status);

#define set_status_known(status_var)                  change_status_on(status_var, PERSON_KNOWN)
#define set_status_attacked(status_var)               change_status_on(status_var, PERSON_ATTACKED)
#define set_status_killed(status_var)                 change_status_on(status_var, PERSON_KILLED)
#define set_status_assassinated(status_var)           change_status_on(status_var, PERSON_ASSASSINATED)
#define set_status_dead(status_var)                   change_status_on(status_var, PERSON_DEAD)
#define set_status_spoken_to(status_var)              change_status_on(status_var, PERSON_SPOKEN_TO)
#define set_status_spoken_to_special(status_var)      change_status_on(status_var, PERSON_SPOKEN_TO_SPECIAL)
#define set_status_special(status_var)                change_status_on(status_var, PERSON_SPECIAL)
#define set_status_special_2(status_var)              change_status_on(status_var, PERSON_SPECIAL_2)
#define set_status_in_party(status_var)               change_status_on(status_var, PERSON_IN_PARTY)
#define set_status_not_in_party(status_var)           change_status_off(status_var, PERSON_IN_PARTY)
#define set_status_warned(status_var)                 change_status_on(status_var, PERSON_WARNED)
#define set_status_sex(status_var)                    change_status_on(status_var, PERSON_SEX)

#define status_is(status_var, check_status)           (gvar_bit(status_var, check_status))

#define status_is_known(status_var)                   (status_is(status_var, PERSON_KNOWN))
#define status_is_unknown(status_var)                 (status_is_known(status_var) == false)
#define status_is_attacked(status_var)                (status_is(status_var, PERSON_ATTACKED))
#define status_is_killed(status_var)                  (status_is(status_var, PERSON_KILLED))
#define status_is_assassinated(status_var)            (status_is(status_var, PERSON_ASSASSINATED))
#define status_is_dead(status_var)                    (status_is(status_var, PERSON_DEAD))
#define status_is_spoken_to(status_var)               (status_is(status_var, PERSON_SPOKEN_TO))
#define status_is_spoken_to_special(status_var)       (status_is(status_var, PERSON_SPOKEN_TO_SPECIAL))
#define status_is_special(status_var)                 (status_is(status_var, PERSON_SPECIAL))
#define status_is_special_2(status_var)               (status_is(status_var, PERSON_SPECIAL_2))
#define status_is_in_party(status_var)                (status_is(status_var, PERSON_IN_PARTY))
#define status_is_not_in_party(status_var)            (status_is(status_var, PERSON_IN_PARTY) == false)
#define status_is_warned(status_var)                  (status_is(status_var, PERSON_WARNED))
#define status_is_sex(status_var)                     (status_is(status_var, PERSON_SEX))

#define status_is_alive(status_var)                   (not (status_is_killed(status_var) or status_is_assassinated(status_var) or status_is_dead(status_var)))

/******************************************************************
 General commands restocking inventory
 note: this is generally placed in the "box" of a merchant to refil it every so once in a while
       only call this when it's time to restock the "box"... see "diTubBox.ssl" for a hint
       but most of all, have fun, remember, fun
******************************************************************/
variable restock_amt;
variable restock_obj;
variable restock_trash;
variable removed_qty;
#define transfer_pid_between_objs(source, target, the_pid, qty)                           \
         restock_amt := qty;                                                              \
         if (obj_is_carrying_obj_pid(source, the_pid) < qty) then begin                   \
            restock_amt := obj_is_carrying_obj_pid(source, the_pid);                      \
         end                                                                              \
         if (restock_amt > 0) then begin                                                  \
            restock_obj := obj_carrying_pid_obj(source, the_pid);                         \
            restock_trash := rm_mult_objs_from_inven(source, restock_obj, restock_amt);   \
            add_mult_objs_to_inven(target, restock_obj, restock_amt);                     \
         end

#define transfer_all_pid_between_objs(source, target, the_pid)                            \
         restock_amt := obj_is_carrying_obj_pid(source, the_pid);                         \
         if (restock_amt > 0) then begin                                                  \
            restock_obj := obj_carrying_pid_obj(source, the_pid);                         \
            restock_trash := rm_mult_objs_from_inven(source, restock_obj, restock_amt);   \
            add_mult_objs_to_inven(target, restock_obj, restock_amt);                     \
         end

#define give_pid_qty(who_obj, the_pid, pid_qty)                                           \
           restock_obj := create_object(the_pid,0,0);                                     \
           add_mult_objs_to_inven(who_obj, restock_obj, (pid_qty));

#define remove_armor(who_obj)                                                                            \
            if (critter_wearing_armor(who_obj)) then begin                                               \
               restock_obj := critter_inven_obj(who_obj,INVEN_TYPE_WORN);                                \
               debug_msg("armour pid == "+obj_pid(restock_obj));                                         \
               rm_obj_from_inven(who_obj, restock_obj);                                                  \
               add_obj_to_inven(who_obj, restock_obj);                                                   \
            end

#define remove_pid_qty(who_obj, the_pid, pid_qty)                                            \
           removed_qty := obj_is_carrying_obj_pid(who_obj,the_pid);                          \
           if ((pid_qty) < removed_qty) then begin                                           \
              removed_qty := pid_qty;                                                        \
           end                                                                               \
           if (removed_qty > 0) then begin                                                   \
              restock_obj := obj_carrying_pid_obj(who_obj, the_pid);                         \
              if (obj_type(self_obj) == 1) then begin                                        \
                 restock_obj := obj_carrying_pid_obj(who_obj, the_pid);                      \
                 if (critter_inven_obj(self_obj,INVEN_TYPE_WORN) == restock_obj) then begin  \
                    remove_armor(who_obj)                                                    \
                 end else if ((critter_inven_obj(who_obj, INVEN_TYPE_LEFT_HAND) == restock_obj) or (critter_inven_obj(who_obj, INVEN_TYPE_RIGHT_HAND) == restock_obj)) then begin     \
                    inven_unwield(who_obj);                                                  \
                 end                                                                         \
              end                                                                            \
              restock_amt := rm_mult_objs_from_inven(who_obj, restock_obj, removed_qty);     \
              destroy_object(restock_obj);                                                   \
           end                                                                               \
           restock_obj := 0;                                                                 \
           restock_amt := 0;

#define stock_pid_qty(who_obj, the_pid, pid_qty)                                                   \
        if (obj_is_carrying_obj_pid(who_obj,the_pid) < pid_qty) then begin                         \
           give_pid_qty(self_obj, the_pid, pid_qty - obj_is_carrying_obj_pid(who_obj,the_pid))     \
        end else if (obj_is_carrying_obj_pid(who_obj,the_pid) > pid_qty) then begin                \
           remove_pid_qty(who_obj, the_pid, (obj_is_carrying_obj_pid(who_obj,the_pid) - pid_qty))  \
        end else begin                                                                             \
           restock_obj := 0;                                                                       \
        end

#define check_restock_item(the_item, min_amt, max_amt, res_perc)                    \
        restock_amt := random(min_amt, max_amt);                                    \
        if (obj_is_carrying_obj_pid(self_obj, the_item) < restock_amt) then begin   \
            if (res_perc >= random(1,100)) then begin                               \
               stock_pid_qty(self_obj, the_item, restock_amt)                       \
            end                                                                     \
        end else begin                                                              \
           stock_pid_qty(self_obj, the_item, restock_amt)                           \
        end
#define check_restock_item_min_limit(the_item, min_amt, max_amt, res_perc)          \
        if (obj_is_carrying_obj_pid(self_obj, the_item) < min_amt) then begin       \
           check_restock_item(the_item, min_amt, max_amt, res_perc)                 \
        end

/******************************************************************
 general macros for arming an object
 note: passing 0 through to the special_ammo_pid will give ammo of the lowest possible damage type
******************************************************************/
#define give_obj_weapon(who_obj, weapon_pid, weapon_qty, ammo_pid, ammo_qty, wield_me)       \
        stock_pid_qty(who_obj, weapon_pid, weapon_qty)                                       \
        if (wield_me) then begin                                                             \
           if (obj_is_carrying_obj_pid(who_obj, weapon_pid)) then begin                      \
              wield_obj_critter(who_obj, obj_carrying_pid_obj(who_obj, weapon_pid));         \
           end else begin                                                                    \
              debug_msg("NOT ARMING THE WEAPON!!!");                                         \
           end                                                                               \
        end                                                                                  \
        if (ammo_pid != 0) then begin                                                        \
           stock_pid_qty(who_obj, ammo_pid, ammo_qty)                                        \
        end else begin                                                                       \
           if ((weapon_pid == PID_10MM_PISTOL) or                                            \
               (weapon_pid == PID_ZIP_GUN) or                                                \
               (weapon_pid == PID_10MM_SMG)) then begin                                      \
              stock_pid_qty(who_obj, PID_10MM_JHP, ammo_qty)                                 \
           end else if ((weapon_pid == PID_HUNTING_RIFLE) or                                 \
                        (weapon_pid == PID_BOZAR) or                                         \
                        (weapon_pid == PID_LIGHT_SUPPORT_WEAPON) or                          \
                        (weapon_pid == PID_SNIPER_RIFLE) or                                  \
                        (weapon_pid == PID_223_PISTOL) or                                    \
                        (weapon_pid == PID_SCOPED_HUNTING_RIFLE)) then begin                 \
              stock_pid_qty(who_obj, PID_223_FMJ, ammo_qty)                                  \
           end else if ((weapon_pid == PID_FLAMER) or                                        \
                        (weapon_pid == PID_IMPROVED_FLAMETHROWER)) then begin                \
              stock_pid_qty(who_obj, PID_FLAMETHROWER_FUEL, ammo_qty)                        \
           end else if ((weapon_pid == PID_MINIGUN) or                                       \
                        (weapon_pid == PID_INDEPENDENT) or                                   \
                        (weapon_pid == PID_AVENGER_MINIGUN) or                               \
                        (weapon_pid == PID_ASSAULT_RIFLE_EXT_MAG) or                         \
                        (weapon_pid == PID_ASSAULT_RIFLE)) then begin                        \
              stock_pid_qty(who_obj, PID_5MM_JHP, ammo_qty)                                  \
           end else if (weapon_pid == PID_ROCKET_LAUNCHER) then begin                        \
              stock_pid_qty(who_obj, PID_EXPLOSIVE_ROCKET, ammo_qty)                         \
           end else if ((weapon_pid == PID_PLASMA_RIFLE) or                                  \
                        (weapon_pid == PID_YK42B_PULSE_RIFLE) or                             \
                        (weapon_pid == PID_GATLING_LASER) or                                 \
                        (weapon_pid == PID_LASER_RIFLE) or                                   \
                        (weapon_pid == PID_LASER_RIFLE_EXT_CAP) or                           \
                        (weapon_pid == PID_TURBO_PLASMA_RIFLE)) then begin                   \
              stock_pid_qty(who_obj, PID_MICRO_FUSION_CELL, ammo_qty)                        \
           end else if ((weapon_pid == PID_LASER_PISTOL) or                                  \
                        (weapon_pid == PID_POWER_FIST) or                                    \
                        (weapon_pid == PID_MEGA_POWER_FIST) or                               \
                        (weapon_pid == PID_RIPPER) or                                        \
                        (weapon_pid == PID_CATTLE_PROD) or                                   \
                        (weapon_pid == PID_SUPER_CATTLE_PROD) or                             \
                        (weapon_pid == PID_PLASMA_PISTOL) or                                 \
                        (weapon_pid == PID_PLASMA_PISTOL_EXT_CART) or                        \
                        (weapon_pid == PID_PHAZER) or                                        \
                        (weapon_pid == PID_YK32_PULSE_PISTOL) or                             \
                        (weapon_pid == PID_ALIEN_LASER_PISTOL) or                            \
                        (weapon_pid == PID_MAGNETO_LASER_PISTOL)) then begin                 \
              stock_pid_qty(who_obj, PID_SMALL_ENERGY_CELL, ammo_qty)                        \
           end else if ((weapon_pid == PID_DESERT_EAGLE) or                                  \
                        (weapon_pid == PID_44_MAGNUM_SPEEDLOADER) or                         \
                        (weapon_pid == PID_DESERT_EAGLE_EXT_MAG) or                          \
                        (weapon_pid == PID_44_MAGNUM_REVOLVER)) then begin                   \
              stock_pid_qty(who_obj, PID_44_MAGNUM_JHP, ammo_qty)                            \
           end else if (weapon_pid == PID_14MM_PISTOL) then begin                            \
              stock_pid_qty(who_obj, PID_14MM_AP, ammo_qty)                                  \
           end else if ((weapon_pid == PID_SHOTGUN) or                                       \
                        (weapon_pid == PID_PANCOR_JACKHAMMER) or                             \
                        (weapon_pid == PID_SAWED_OFF_SHOTGUN) or                             \
                        (weapon_pid == PID_COMBAT_SHOTGUN) or                                \
                        (weapon_pid == PID_HK_CAWS)) then begin                              \
              stock_pid_qty(who_obj, PID_SHOTGUN_SHELLS, ammo_qty)                           \
           end else if (weapon_pid == PID_9MM_MAUSER) then begin                             \
              stock_pid_qty(who_obj, PID_9MM_BALL, ammo_qty)                                 \
           end else if (weapon_pid == PID_HK_P90C) then begin                                \
              stock_pid_qty(who_obj, PID_9MM_AMMO, ammo_qty)                                 \
           end else if (weapon_pid == PID_ROBO_ROCKET_LAUNCHER) then begin                   \
              stock_pid_qty(who_obj, PID_ROBO_ROCKET_AMMO, ammo_qty)                         \
           end else if (weapon_pid == PID_SPRINGER_RIFLE) then begin                         \
              stock_pid_qty(who_obj, PID_ROCK, ammo_qty)                                     \
           end else if ((weapon_pid == PID_RED_RYDER_BB_GUN) or                              \
                        (weapon_pid == PID_RED_RYDER_LE_BB_GUN) or                           \
                        (weapon_pid == PID_JONNY_BB_GUN)) then begin                         \
              stock_pid_qty(who_obj, PID_BBS, ammo_qty)                                      \
           end else if ((weapon_pid == PID_TOMMY_GUN) or                                     \
                        (weapon_pid == PID_GREASE_GUN)) then begin                           \
              stock_pid_qty(who_obj, PID_45_CALIBER_AMMO, ammo_qty)                          \
           end else if ((weapon_pid == PID_FN_FAL) or                                        \
                        (weapon_pid == PID_FN_FAL_NIGHT_SCOPE) or                            \
                        (weapon_pid == PID_M60)) then begin                                  \
              stock_pid_qty(who_obj, PID_7_62MM_AMMO, ammo_qty)                              \
           end else if ((weapon_pid == PID_M72_GAUSS_RIFLE) or                               \
                        (weapon_pid == PID_PK12_GAUSS_PISTOL)) then begin                    \
              stock_pid_qty(who_obj, PID_2MM_EC_AMMO, ammo_qty)                              \
           end else if ((weapon_pid == PID_HK_G11) or                                        \
                        (weapon_pid == PID_HK_G11E) or                                       \
                        (weapon_pid == PID_VINDICATOR_MINIGUN)) then begin                   \
              stock_pid_qty(who_obj, PID_4_7MM_CASELESS, ammo_qty)                           \
           end else if (weapon_pid == PID_NEEDLER_PISTOL) then begin                         \
              stock_pid_qty(who_obj, PID_HN_NEEDLER_CARTRIDGE, ammo_qty)                     \
           end                                                                               \
        end

#define arm_obj(who_obj, weapon_pid, weapon_qty, ammo_pid, ammo_qty)                give_obj_weapon(who_obj, weapon_pid, weapon_qty, ammo_pid, ammo_qty, true)
#define stock_weapon_obj(who_obj, weapon_pid, weapon_qty, ammo_pid, ammo_qty)       give_obj_weapon(who_obj, weapon_pid, weapon_qty, ammo_pid, ammo_qty, false)

/******************************************************************
 general macros/defines related to having sex
******************************************************************/
// is_sex_god is temporary for when the player gets the sex perk ***
#define is_sex_god               ((global_var(GVAR_PLAYER_SEX_LEVEL)>=100) /*or (dude_has_porn_star_rep)*/)
#define have_sex_time_obj(x)     (((get_critter_stat(x,STAT_en)) * random(4,8)) * ONE_GAME_MINUTE)
#define have_sex_time            have_sex_time_obj(dude_obj)
#define advance_sex_time         game_time_advance(have_sex_time)
// these are to be compared to sex_rating
#define sex_rating_great         (9)
#define sex_rating_good          (7)
#define sex_rating_normal        (5)
#define sex_rating_bad           (3)
#define sex_rating_horrible      (2)
// returns a value between 1 and 10 on how good the sex was
#define obj_sex_rating(x)        ((((get_critter_stat(x,STAT_ch)*50) +                    \
                                    (get_critter_stat(x,STAT_en)*25) +                    \
                                    (get_critter_stat(x,STAT_ag)*13) +                    \
                                    (get_critter_stat(x,STAT_st)*12))/100) +              \
                                    (has_trait(TRAIT_PERK,x,PERK_kama_sutra_perk) * 2) +  \
                                    /*(has_trait(TRAIT_TRAIT,x,TRAIT_sex_appeal)) +*/     \
                                    (is_sex_god * 2 * (x == dude_obj)))
#define dude_sex_rating          obj_sex_rating(dude_obj)
#define self_sex_rating          obj_sex_rating(self_obj)
#define up_sex_status_amt(x)     inc_global_var_amt(GVAR_PLAYER_SEX_LEVEL, dude_sex_rating * x);   \
                                 if (global_var(GVAR_SEX_COUNTER) >= 9) then begin                 \
                                    set_global_var(GVAR_SEXPERT, 1);                               \
                                 end                                                               \
                                 if (dude_sex_rating >= sex_rating_great) then begin               \
                                    set_global_var(GVAR_GIGALO, 1);                                \
                                 end                                                               \
                                 inc_global_var_amt(GVAR_SEX_COUNTER, x)
#define up_sex_status            up_sex_status_amt(1)
#define do_default_sex           advance_sex_time;    \
                                 up_sex_status

#define destroy_obj_inven(obj)                      \
   global_temp := create_object(PID_FOOTLOCKER_CLEAN_LEFT,0,0); \
   move_obj_inven_to_obj(obj, global_temp);                     \
   destroy_object(global_temp)

// Info relating to carry weight, how much something costs, and weights
#define pid_weight(x)                                   proto_data(x,it_weight)
#define obj_weight(x)                                   pid_weight(obj_pid(x))
#define pid_cost(x)                                     proto_data(x, it_cost)
#define obj_cost(x)                                     pid_cost(obj_pid(x))

#define amt_cost_barter(who1, who2, x)                  floor(2 * x * ((160.0 + has_skill(who2,SKILL_BARTER)) / (160.0 + has_skill(who1,SKILL_BARTER))))
#define pid_cost_barter(who1, who2, x)                  amt_cost_barter(who1, who2, pid_cost(x))
#define obj_cost_barter(who1, who2, x)                  pid_cost_barter(who1, who2, obj_pid(x))
#define who_max_carry(x)                               get_critter_stat(x,STAT_carry_amt)
#define who_carry_amount(x)                             has_trait(TRAIT_OBJECT, x, OBJECT_CUR_WEIGHT)
#define who_inven_free_amt(x)                           (who_max_carry(x) - who_carry_amount(x))


/********************************************************************
************   These are for cutting down on the lvars   ************
********************************************************************/
// for examples of use, see new reno and raiders
// default bits for character flag
#define herebefore_bit                                bit_1
#define hostile_bit                                   bit_2
#define examined_bit                                  bit_3
#define personal_enemy_bit                            bit_4
#define initialized_bit                               bit_5
#define is_float_bit                                  bit_7
#define destroy_me_bit                                bit_8
#define heard_call_bit                                bit_9

// here before
#define herebefore                                    lvar_bit(LVAR_Flags, herebefore_bit)
#define set_herebefore                                set_lvar_bit_on(LVAR_Flags, herebefore_bit)
#define off_herebefore                                set_lvar_bit_off(LVAR_Flags, herebefore_bit)
// hostile
#define hostile                                       lvar_bit(LVAR_Flags, hostile_bit)
#define set_hostile                                   set_lvar_bit_on(LVAR_Flags, hostile_bit)
#define off_hostile                                   set_lvar_bit_off(LVAR_Flags, hostile_bit)
// examined
#define examined                                      lvar_bit(LVAR_Flags, examined_bit)
#define set_examined                                  set_lvar_bit_on(LVAR_Flags, examined_bit)
// personal enemy
#define personal_enemy                                lvar_bit(LVAR_Flags, personal_enemy_bit)
#define set_personal_enemy                            set_lvar_bit_on(LVAR_Flags, personal_enemy_bit); set_hostile
// initialized
#define destroy_me                                    lvar_bit(LVAR_Flags, destroy_me_bit)
#define set_destroy_me                                set_lvar_bit_on(LVAR_Flags, destroy_me_bit)
// initialized
#define initialized                                   lvar_bit(LVAR_Flags, initialized_bit)
#define set_initialized                               set_lvar_bit_on(LVAR_Flags, initialized_bit)
// heard_call
#define heard_call                                    lvar_bit(LVAR_Flags, heard_call_bit)
#define set_heard_call                                set_lvar_bit_on(LVAR_Flags, heard_call_bit)
// set message type
#define is_float                                      lvar_bit(LVAR_Flags, is_float_bit)
#define is_click                                      (is_float == false)
#define set_is_float                                  set_lvar_bit_on(LVAR_Flags, is_float_bit)
#define set_is_click                                  set_lvar_bit_off(LVAR_Flags, is_float_bit)
#define create_out_of_business(tile, elev, pid)                                                                                                                       \
         if ((tile_contains_pid_obj(tile, elev, PID_OUT_OF_BUSINESS_NORTH) == 0) and (tile_contains_pid_obj(tile, elev, PID_OUT_OF_BUSINESS_EAST) == 0)) then begin   \
            global_temp := create_object_sid(pid, 0, 0, SCRIPT_ZICLOSED);                                                                                                \
            set_obj_visibility(global_temp,true);                                                                                                                        \
            move_to(global_temp, tile, elev);                                                                                                                            \
         end                                                                                                                                                          \
         debug_msg("created out of business @ tile == " + tile + " / elevation == " + elev)
#define create_north_out_of_business(x, e)            create_out_of_business(x, e, PID_OUT_OF_BUSINESS_NORTH)
#define create_east_out_of_business(x, e)             create_out_of_business(x, e, PID_OUT_OF_BUSINESS_EAST)

#endif // COMMAND_H
