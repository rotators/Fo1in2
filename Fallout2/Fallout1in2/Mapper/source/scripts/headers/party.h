/*
    Copyright 1998-2003 Interplay Entertainment Corp.  All rights reserved.
*/

#pragma once

#include "sfall/sfall.h"

/***************************************************************
    The following contain all of the Party information and
    commands for Fallout 2
***************************************************************/

variable How_Many_Party_Members_Are_Injured;
variable How_Many_Party_Members_Armed;

#define FOLLOW_DISTANCE_CLOSE               (2) // Fo2: 3
#define FOLLOW_DISTANCE_MEDIUM              (4) // Fo2: 6
#define FOLLOW_DISTANCE_FAR                 (6) // Fo2: 9

#define obj_in_party(x)                     (party_member_obj(obj_pid(x)) != 0)
// Pointers to the Party Members
//#define Trunk_Ptr                         party_member_obj(PID_CAR_TRUNK)
#define Trunk_Ptr                           party_member_obj(PID_MOTO1_TRUNK)
#define Ian_ptr                             party_member_obj(PID_IAN)
#define Dog_ptr                             party_member_obj(PID_DOGMEAT)
#define Tycho_ptr                           party_member_obj(PID_TYCHO)
#define Katja_ptr                           party_member_obj(PID_KATJA)
#define Tandi_ptr                           party_member_obj(PID_TANDI)
#define Handy_ptr                           party_member_obj(PID_MRHANDYC)
#define Eyebot_ptr                          party_member_obj(PID_EYEBOT)
#define Rae_ptr                             party_member_obj(PID_RAE)
#define Vasquez_ptr                         party_member_obj(PID_VASQUEZ)

// Is this person in my party
#define Ian_In_Party                        (Ian_ptr != 0)
#define Dog_In_Party                        (Dog_ptr != 0)
#define Tycho_In_Party                      (Tycho_ptr != 0)
#define Katja_In_Party                      (Katja_ptr != 0)
#define Tandi_In_Party                      (Tandi_ptr != 0)
#define MrHandyC_In_Party                   (Handy_ptr != 0)
#define Eyebot_In_Party                     (Eyebot_ptr != 0)
#define Rae_In_Party                        (Rae_ptr != 0)
#define Vasquez_In_Party                    (Vasquez_ptr != 0)

// Party Size Information
#define party_size                          (party_member_count(DONT_LIST_HIDDEN_MEMBERS))
#define true_party_size                     (party_size - 1)
#define party_max_formula                   (floor(dude_charisma/2) + (has_trait(TRAIT_PERK,dude_obj,PERK_magnetic_personality_perk)))
#define dude_at_max_party_size              ((true_party_size >= (party_max_formula)) or (true_party_size >= 5))
#define party_size_humans                   (Ian_In_Party+Tycho_In_Party+Katja_In_Party+Tandi_In_Party+Vasquez_In_Party)
#define party_size_male                     (Ian_In_Party+Tycho_In_Party+Vasquez_In_Party)
#define party_size_female                   (Katja_In_Party+Tandi_In_Party)
#define party_size_strange                  (MrHandyC_In_Party+Dog_In_Party+Eyebot_In_Party+Rae_In_Party)
#define party_size_biped                    (party_size_male + party_size_female)

// Health of Party Members
#define Is_Injured(Who)                     (get_critter_stat(Who, STAT_current_hp) < get_critter_stat(Who, STAT_max_hit_points))
#define Injured_How_Much(Who)               (get_critter_stat(Who, STAT_max_hit_points) - get_critter_stat(Who, STAT_current_hp))
#define Is_Crippled(Who)                    (critter_state(Who) BWAND (DAM_CRIP_LEG_LEFT BWOR DAM_CRIP_LEG_RIGHT BWOR DAM_CRIP_ARM_LEFT BWOR DAM_CRIP_ARM_RIGHT))
#define Is_Blind(Who)                       (critter_state(Who) BWAND DAM_BLIND)
#define Is_Armed(Who)                       (((obj_item_subtype(critter_inven_obj(Who,INVEN_TYPE_RIGHT_HAND))) == item_type_weapon))


#define If_Party_Has_Injured                How_Many_Party_Members_Are_Injured := 0;            \
                                            if (Ian_In_Party) then                              \
                                                if (Is_Injured(Ian_ptr)) then                   \
                                                    How_Many_Party_Members_Are_Injured+=1;      \
                                            if (Dog_In_Party) then                              \
                                                if (Is_Injured(Dog_ptr)) then                   \
                                                    How_Many_Party_Members_Are_Injured+=1;      \
                                            if (Tycho_In_Party) then                            \
                                                if (Is_Injured(Tycho_ptr)) then                 \
                                                    How_Many_Party_Members_Are_Injured+=1;      \
                                            if (Katja_In_Party) then                            \
                                                if (Is_Injured(Katja_ptr)) then                 \
                                                    How_Many_Party_Members_Are_Injured+=1;      \
                                            if (Tandi_In_Party) then                            \
                                                if (Is_Injured(Tandi_ptr)) then                 \
                                                    How_Many_Party_Members_Are_Injured+=1;      \
                                            /*if (MrHandyC_In_Party) then                       \
                                                if (Is_Injured(Handy_ptr)) then                 \
                                                    How_Many_Party_Members_Are_Injured+=1;      \
                                            if (Eyebot_In_Party) then                           \
                                                if (Is_Injured(Eyebot_ptr)) then                \
                                                    How_Many_Party_Members_Are_Injured+=1;*/    \
                                            if (Rae_In_Party) then                              \
                                                if (Is_Injured(Rae_ptr)) then                   \
                                                    How_Many_Party_Members_Are_Injured+=1;      \
                                            if (Vasquez_In_Party) then                          \
                                                if (Is_Injured(Vasquez_ptr)) then               \
                                                    How_Many_Party_Members_Are_Injured+=1;      \
                                            if (How_Many_Party_Members_Are_Injured > 0)


#define If_Party_Is_Armed                   How_Many_Party_Members_Armed := 0;                  \
                                            if (dude_is_armed) then                             \
                                               How_Many_Party_Members_Armed+=1;                 \
                                            if (Ian_In_Party) then                              \
                                                if (Is_Injured(Ian_ptr)) then                   \
                                                    How_Many_Party_Members_Armed+=1;            \
                                            if (Dog_In_Party) then                              \
                                                if (Is_Injured(Dog_ptr)) then                   \
                                                    How_Many_Party_Members_Armed+=1;            \
                                            if (Tycho_In_Party) then                            \
                                                if (Is_Injured(Tycho_ptr)) then                 \
                                                    How_Many_Party_Members_Armed+=1;            \
                                            if (Katja_In_Party) then                            \
                                                if (Is_Injured(Katja_ptr)) then                 \
                                                    How_Many_Party_Members_Armed+=1;            \
                                            if (Tandi_In_Party) then                            \
                                                if (Is_Injured(Tandi_ptr)) then                 \
                                                    How_Many_Party_Members_Armed+=1;            \
                                            if (MrHandyC_In_Party) then                         \
                                                if (Is_Injured(Handy_ptr)) then                 \
                                                    How_Many_Party_Members_Armed+=1;            \
                                            if (Eyebot_In_Party) then                           \
                                                if (Is_Injured(Eyebot_ptr)) then                \
                                                    How_Many_Party_Members_Armed+=1;            \
                                            if (Rae_In_Party) then                              \
                                                if (Is_Injured(Rae_ptr)) then                   \
                                                    How_Many_Party_Members_Armed+=1;            \
                                            if (Vasquez_In_Party) then                          \
                                                if (Is_Injured(Vasquez_ptr)) then               \
                                                    How_Many_Party_Members_Armed+=1;            \
                                            if (How_Many_Party_Members_Armed > 0)

#define Party_Childkiller_Mask              (bit_2 BWOR bit_4 BWOR bit_6 BWOR bit_8 BWOR bit_10 BWOR bit_12 BWOR bit_14 BWOR    \
                                             bit_16 BWOR bit_18 BWOR bit_20 BWOR bit_22 BWOR bit_24 BWOR bit_26 BWOR bit_28     \
                                             BWOR bit_30 BWOR bit_32)

#define attempt_place_party_member(the_obj, the_tile, the_elev)            \
         if (the_obj != 0) then begin                                      \
            if (obj_is_visible_flag(the_obj)) then begin                   \
               critter_attempt_placement(the_obj, the_tile, the_elev);     \
            end                                                            \
         end
#define attempt_place_party(the_tile, the_elev)                           \
        attempt_place_party_member(Trunk_Ptr, the_tile, the_elev)         \
        attempt_place_party_member(Ian_ptr, the_tile, the_elev)           \
        attempt_place_party_member(Dog_ptr, the_tile, the_elev)           \
        attempt_place_party_member(Tycho_ptr, the_tile, the_elev)         \
        attempt_place_party_member(Katja_ptr, the_tile, the_elev)         \
        attempt_place_party_member(Tandi_ptr, the_tile, the_elev)         \
        attempt_place_party_member(Handy_ptr, the_tile, the_elev)         \
        attempt_place_party_member(Eyebot_ptr, the_tile, the_elev)        \
        attempt_place_party_member(Rae_ptr, the_tile, the_elev)           \
        attempt_place_party_member(Vasquez_ptr, the_tile, the_elev)


//#define Party_Childkiller                   (global_var(GVAR_PARTY_CHILDKILLER) BWAND Party_Childkiller_Mask)
#define Childkiller_Ian                     ((global_var(GVAR_PARTY_CHILDKILLER) BWAND bit_2) and (Ian_ptr != 0))
#define Childkiller_Dog                     ((global_var(GVAR_PARTY_CHILDKILLER) BWAND bit_4) and (Dog_ptr != 0))
#define Childkiller_Tycho                   ((global_var(GVAR_PARTY_CHILDKILLER) BWAND bit_6) and (Tycho_ptr != 0))
#define Childkiller_Katja                   ((global_var(GVAR_PARTY_CHILDKILLER) BWAND bit_8) and (Katja_ptr != 0))
#define Childkiller_Tandi                   ((global_var(GVAR_PARTY_CHILDKILLER) BWAND bit_10) and (Tandi_ptr != 0))
#define Childkiller_MrHandyC                ((global_var(GVAR_PARTY_CHILDKILLER) BWAND bit_12) and (Handy_ptr != 0))
#define Childkiller_Eyebot                  ((global_var(GVAR_PARTY_CHILDKILLER) BWAND bit_14) and (Eyebot_ptr != 0))
#define Childkiller_Rae                     ((global_var(GVAR_PARTY_CHILDKILLER) BWAND bit_16) and (Rae_ptr != 0))
#define Childkiller_Vasquez                 ((global_var(GVAR_PARTY_CHILDKILLER) BWAND bit_18) and (Vasquez_ptr != 0))

#define Party_Childkiller                   (Childkiller_Ian or Childkiller_Dog or Childkiller_Tycho or Childkiller_Katja or Childkiller_Tandi or Childkiller_MrhandyC or Childkiller_Eyebot or Childkiller_Rae or Childkiller_Vasquez)

//#define inc_party_childkiller(who)          if () then

variable PartyHealingItem;

#define obj_heal_time(x)                     if (x > 0) then begin        \
                                                game_time_advance(x);     \
                                             end

#define obj_heal(who)                        if (obj_is_carrying_obj_pid(who,PID_SUPER_STIMPAK)) then begin                     \
                                                if ((global_temp == 0) and (combat_is_initialized == false)) then begin         \
                                                   gfade_out(600);                                                              \
                                                   obj_heal_time(0)                                                             \
                                                   gfade_in(600);                                                               \
                                                end                                                                             \
                                                PartyHealingItem:=obj_carrying_pid_obj(who,PID_SUPER_STIMPAK);                  \
                                                use_obj_on_obj(PartyHealingItem,who);                                           \
                                                debug_msg(obj_name(who)+" used super stimpak.");                                \
                                             end                                                                                \
                                             else if (obj_is_carrying_obj_pid(who,PID_STIMPAK)) then begin                      \
                                                if ((global_temp == 0) and (combat_is_initialized == false)) then begin         \
                                                   gfade_out(600);                                                              \
                                                   obj_heal_time(0)                                                             \
                                                   gfade_in(600);                                                               \
                                                end                                                                             \
                                                use_obj_on_obj(obj_carrying_pid_obj(who,PID_STIMPAK),who);                      \
                                                debug_msg(obj_name(who)+" used stimpak.");                                      \
                                             end                                                                                \
                                             else if (obj_is_carrying_obj_pid(who,PID_HEALING_POWDER)) then begin               \
                                                if ((global_temp == 0) and (combat_is_initialized == false)) then begin         \
                                                   gfade_out(600);                                                              \
                                                   obj_heal_time(0)                                                             \
                                                   gfade_in(600);                                                               \
                                                end                                                                             \
                                                use_obj_on_obj(obj_carrying_pid_obj(who,PID_HEALING_POWDER),who);               \
                                                debug_msg(obj_name(who)+" used healing powder.");                               \
                                             end                                                                                \
                                             else if (obj_is_carrying_obj_pid(who,PID_DOCTORS_BAG)) then begin                  \
                                                if ((global_temp == 0) and (combat_is_initialized == false)) then begin         \
                                                   gfade_out(600);                                                              \
                                                   obj_heal_time(0)                                                             \
                                                   gfade_in(600);                                                               \
                                                end                                                                             \
                                                use_obj_on_obj(obj_carrying_pid_obj(who,PID_DOCTORS_BAG),who);                  \
                                                debug_msg(obj_name(who)+" used doctor's bag kit.");                             \
                                             end                                                                                \
                                             else if (obj_is_carrying_obj_pid(who,PID_FIRST_AID_KIT)) then begin                \
                                                if ((global_temp == 0) and (combat_is_initialized == false)) then begin         \
                                                   gfade_out(600);                                                              \
                                                   obj_heal_time(0)                                                             \
                                                   gfade_in(600);                                                               \
                                                end                                                                             \
                                                use_obj_on_obj(obj_carrying_pid_obj(who,PID_FIRST_AID_KIT),who);                \
                                                debug_msg(obj_name(who)+" used First Aid kit.");                                \
                                             end                                                                                \
                                             else if (has_skill(who,SKILL_DOCTOR) > has_skill(who,SKILL_FIRST_AID)) then begin  \
                                                if ((global_temp == 0) and (combat_is_initialized == false)) then begin         \
                                                   gfade_out(600);                                                              \
                                                   obj_heal_time(ONE_GAME_HOUR)                                                 \
                                                   gfade_in(600);                                                               \
                                                end                                                                             \
                                                if (is_success(roll_vs_skill(who,SKILL_DOCTOR,0))) then begin                   \
                                                    critter_heal(who,random(10,25));                                            \
                                                    debug_msg(obj_name(who)+" healed some using doctor skill.");                \
                                                end                                                                             \
                                             end                                                                                \
                                             else begin                                                                         \
                                                if ((global_temp == 0) and (combat_is_initialized == false)) then begin         \
                                                   gfade_out(600);                                                              \
                                                   obj_heal_time(15*ONE_GAME_MINUTE)                                            \
                                                   gfade_in(600);                                                               \
                                                end                                                                             \
                                                if (is_success(roll_vs_skill(who,SKILL_FIRST_AID,0))) then begin                \
                                                    critter_heal(who,random(5,15));                                             \
                                                    debug_msg(obj_name(who)+" healed some using first aid skill.");             \
                                                end                                                                             \
                                             end

#define obj_heal_no_skill(who)               if (obj_is_carrying_obj_pid(who,PID_SUPER_STIMPAK)) then begin                     \
                                                if ((global_temp == 0) and (combat_is_initialized == false)) then begin         \
                                                   gfade_out(600);                                                              \
                                                   obj_heal_time(0)                                                             \
                                                   gfade_in(600);                                                               \
                                                end                                                                             \
                                                PartyHealingItem:=obj_carrying_pid_obj(who,PID_SUPER_STIMPAK);                  \
                                                use_obj_on_obj(PartyHealingItem,who);                                           \
                                                debug_msg(obj_name(who)+" used super stimpak.");                                \
                                             end                                                                                \
                                             else if (obj_is_carrying_obj_pid(who,PID_STIMPAK)) then begin                      \
                                                if ((global_temp == 0) and (combat_is_initialized == false)) then begin         \
                                                   gfade_out(600);                                                              \
                                                   obj_heal_time(0)                                                             \
                                                   gfade_in(600);                                                               \
                                                end                                                                             \
                                                use_obj_on_obj(obj_carrying_pid_obj(who,PID_STIMPAK),who);                      \
                                                debug_msg(obj_name(who)+" used stimpak.");                                      \
                                             end                                                                                \
                                             else if (obj_is_carrying_obj_pid(who,PID_HEALING_POWDER)) then begin               \
                                                if ((global_temp == 0) and (combat_is_initialized == false)) then begin         \
                                                   gfade_out(600);                                                              \
                                                   obj_heal_time(0)                                                             \
                                                   gfade_in(600);                                                               \
                                                end                                                                             \
                                                use_obj_on_obj(obj_carrying_pid_obj(who,PID_HEALING_POWDER),who);               \
                                                debug_msg(obj_name(who)+" used healing powder.");                               \
                                             end                                                                                \
                                             else if (obj_is_carrying_obj_pid(who,PID_DOCTORS_BAG)) then begin                  \
                                                if ((global_temp == 0) and (combat_is_initialized == false)) then begin         \
                                                   gfade_out(600);                                                              \
                                                   obj_heal_time(0)                                                             \
                                                   gfade_in(600);                                                               \
                                                end                                                                             \
                                                use_obj_on_obj(obj_carrying_pid_obj(who,PID_DOCTORS_BAG),who);                  \
                                                debug_msg(obj_name(who)+" used doctor's bag kit.");                             \
                                             end                                                                                \
                                             else if (obj_is_carrying_obj_pid(who,PID_FIRST_AID_KIT)) then begin                \
                                                if ((global_temp == 0) and (combat_is_initialized == false)) then begin         \
                                                   gfade_out(600);                                                              \
                                                   obj_heal_time(0)                                                             \
                                                   gfade_in(600);                                                               \
                                                end                                                                             \
                                                use_obj_on_obj(obj_carrying_pid_obj(who,PID_FIRST_AID_KIT),who);                \
                                                debug_msg(obj_name(who)+" used First Aid kit.");                                \
                                             end



//Hiding party members
#define get_p_hidden_flag_obj(x, the_ptr, the_bit, the_var)             \
         if (x == the_ptr) then begin                                   \
            the_var := gvar_bit(GVAR_PARTY_MEMBERS_HIDDEN, the_bit);    \
         end
#define     get_p_hidden_flag(x, hidden)                                            \
            get_p_hidden_flag_obj(x, Ian_ptr, hidden_ian_bit, hidden)               \
            else get_p_hidden_flag_obj(x, Dog_ptr, hidden_dog_bit, hidden)          \
            else get_p_hidden_flag_obj(x, Tycho_ptr, hidden_tycho_bit, hidden)      \
            else get_p_hidden_flag_obj(x, Katja_ptr, hidden_katja_bit, hidden)      \
            else get_p_hidden_flag_obj(x, Tandi_ptr, hidden_tandi_bit, hidden)      \
            else get_p_hidden_flag_obj(x, Handy_ptr, hidden_mrhandyc_bit, hidden)   \
            else get_p_hidden_flag_obj(x, Eyebot_ptr, hidden_eyebot_bit, hidden)    \
            else get_p_hidden_flag_obj(x, Rae_ptr, hidden_rae_bit, hidden)          \
            else get_p_hidden_flag_obj(x, Vasquez_ptr, hidden_vasquez_bit, hidden)

#define party_member_hidden(x, result)                                           \
   if (x) then begin                                                             \
      if (obj_is_visible_flag(x) == 0) then begin                                \
         get_p_hidden_flag(x, result)                                            \
         if (result) then begin                                                  \
            result := 1;                                                         \
         end else begin                                                          \
            result := 0;                                                         \
            debug_msg("PARTY.H:::: party member hidden but not my my macro.. "); \
         end                                                                     \
      end                                                                        \
   end

#define hidden_ian_bit                      bit_1
#define hidden_dog_bit                      bit_2
#define hidden_tycho_bit                    bit_3
#define hidden_katja_bit                    bit_4
#define hidden_tandi_bit                    bit_5
#define hidden_mrhandyc_bit                 bit_6
#define hidden_eyebot_bit                   bit_7
#define hidden_rae_bit                      bit_8
#define hidden_vasquez_bit                  bit_9
#define all_hidden_bit                      bit_19



#define party_bit_hidden(x)                  (gvar_bit(GVAR_PARTY_MEMBERS_HIDDEN, x))

#define all_party_hidden                     party_bit_hidden(all_hidden_bit)
#define set_party_bit_hidden(x, member)      set_gvar_bit_on(GVAR_PARTY_MEMBERS_HIDDEN, x); set_obj_visibility(member, 1)
#define party_member_hide(the_obj, the_bit)                                                        \
         if (the_obj) then begin                                                                   \
            if (obj_is_visible_flag(the_obj)) then begin                                           \
               debug_msg("set party member hidden: " + obj_name(the_obj));                         \
               set_party_bit_hidden(the_bit, the_obj);                                             \
            end else begin                                                                         \
               debug_msg("PARTY.H:::: no party member hidden because they already are invisible"); \
            end                                                                                    \
         end
#define party_member_hide_all                                                       \
         set_gvar_bit_on(GVAR_PARTY_MEMBERS_HIDDEN, all_hidden_bit);                \
         party_member_hide(Ian_ptr, hidden_ian_bit)                                 \
         party_member_hide(Dog_ptr, hidden_dog_bit)                                 \
         party_member_hide(Tycho_ptr, hidden_tycho_bit)                             \
         party_member_hide(Katja_ptr, hidden_katja_bit)                             \
         party_member_hide(Tandi_ptr, hidden_tandi_bit)                             \
         party_member_hide(Handy_ptr, hidden_mrhandyc_bit)                          \
         party_member_hide(Eyebot_ptr, hidden_eyebot_bit)                           \
         party_member_hide(Rae_ptr, hidden_rae_bit)                                 \
         party_member_hide(Vasquez_ptr, hidden_vasquez_bit)


#define all_party_unhidden                   (all_party_hidden == false)
#define set_party_bit_unhidden(x, member)    debug_msg("unhiding party member "+obj_name(member)); set_gvar_bit_off(GVAR_PARTY_MEMBERS_HIDDEN, x); set_obj_visibility(member, 0)
#define party_member_unhide(the_obj, the_bit)                                                   \
         if (the_obj) then begin                                                                \
            if (obj_is_visible_flag(the_obj) == 0) then begin                                   \
               if (party_bit_hidden(the_bit)) then begin                                        \
                  set_party_bit_unhidden(the_bit, the_obj);                                     \
               end else begin                                                                   \
                  debug_msg("PARTY.H:::: party member wasn't hidden by my macro");              \
               end                                                                              \
            end else begin                                                                      \
               set_party_bit_unhidden(the_bit, the_obj);                                        \
               debug_msg("PARTY.H:::: party member wasn't hidden.. clearing my state");         \
            end                                                                                 \
         end
#define party_member_unhide_all                                      \
        set_gvar_bit_off(GVAR_PARTY_MEMBERS_HIDDEN, all_hidden_bit); \
        party_member_unhide(Ian_ptr, hidden_ian_bit)                 \
        party_member_unhide(Dog_ptr, hidden_dog_bit)                 \
        party_member_unhide(Tycho_ptr, hidden_tycho_bit)             \
        party_member_unhide(Katja_ptr, hidden_katja_bit)             \
        party_member_unhide(Tandi_ptr, hidden_tandi_bit)             \
        party_member_unhide(Handy_ptr, hidden_mrhandyc_bit)          \
        party_member_unhide(Eyebot_ptr, hidden_eyebot_bit)           \
        party_member_unhide(Rae_ptr, hidden_rae_bit)                 \
        party_member_unhide(Vasquez_ptr, hidden_vasquez_bit)

//End hiding party members


// Default
// party member health states
#define party_healed_max                     (self_cur_hp == self_max_hp)
#define party_healed_good                    (((self_cur_hp * 100)/self_max_hp) >= 90)
#define party_healed_hurt                    (((self_cur_hp * 100)/self_max_hp) >= 70)
#define party_healed_bad                     (((self_cur_hp * 100)/self_max_hp) < 70)

// Generic Options for party members
#define def_heal_msg                         g_mstr(10001)
#define def_wait_msg                         g_mstr(10002)
#define def_unarm_msg                        g_mstr(10003)
#define def_close_msg                        g_mstr(10004)
#ifndef def_med_msg
  #define def_med_msg                        g_mstr(10005)
#endif
#ifndef def_far_msg
  #define def_far_msg                        g_mstr(10006)
#endif
#define def_end_msg                          g_mstr(10007)
#ifndef def_follow_msg
  #define def_follow_msg                     g_mstr(10008)
#endif
#define def_gear_msg                         g_mstr(10009)
#define def_ignore_follow_msg                g_mstr(10010)
#define def_ignore_gear_msg                  g_mstr(10011)
#define def_armor_msg                        g_mstr(10012)
#define def_weapon_use_msg                   g_mstr(10013)
#define def_nowait_msg                       g_mstr(10100)
#define def_stupid_msg                       g_mstr(random(300, 303))

#define DEF_PARTY_HEAL_NODE                  Node1001
#define DEF_PARTY_WAIT_NODE                  Node1002
#define DEF_UNARM_NODE                       Node1003
#define DEF_FOLLOW_CLOSE_NODE                Node1004
#define DEF_FOLLOW_MEDIUM_NODE               Node1005
#define DEF_FOLLOW_FAR_NODE                  Node1006
#define DEF_PARTY_FOLLOW_NODE                Node1007
#define DEF_PARTY_GEAR_NODE                  Node1008
#define DEF_REMOVE_ARMOR_NODE                Node1009
#define DEF_WEAPON_USE_NODE                  Node1010
#define DEF_PARTY_NOWAIT_NODE                Node1100
#define DEF_PARTY_END_NODE                   Node999
#define DEF_PARTY_STUPID_NODE                Node999
#define party_member_options(heal_msg, follow_msg, gear_msg, wait_msg, nowait_msg, end_msg, stupid_msg)  \
                                             if (party_is_waiting == false) then begin                   \
                                                if (local_var(LVAR_FOLLOW_DISTANCE) == 0) then begin     \
                                                   set_follow_medium;                                    \
                                                end                                                      \
                                                if (heal_msg != 0) then begin                            \
                                                   if (self_cur_hp < self_max_hp) then begin             \
                                                      NOption(heal_msg, DEF_PARTY_HEAL_NODE, 004);       \
                                                   end                                                   \
                                                end                                                      \
                                                if (follow_msg != 0) then begin                          \
                                                   NOption(follow_msg, DEF_PARTY_FOLLOW_NODE, 004);      \
                                                end                                                      \
                                                if (gear_msg != 0) then begin                            \
                                                   NOption(gear_msg, DEF_PARTY_GEAR_NODE, 004);          \
                                                end                                                      \
                                                if (wait_msg != 0) then begin                            \
                                                   NOption(wait_msg, DEF_PARTY_WAIT_NODE, 004);          \
                                                end                                                      \
                                             end else if (nowait_msg != 0) then begin                    \
                                                NOption(nowait_msg, DEF_PARTY_NOWAIT_NODE, 004);         \
                                             end                                                         \
                                             if (end_msg != 0) then begin                                \
                                                NOption(end_msg, DEF_PARTY_END_NODE, 004);               \
                                             end                                                         \
                                             if (stupid_msg != 0) then begin                             \
                                                NOption(stupid_msg, DEF_PARTY_STUPID_NODE, -003);        \
                                             end                                                         \
                                             debug_msg("USED PARTY MEMBER OPTIONS")
// this goes into node 1007
#define party_follow_options(close_msg, med_msg, far_msg, follow_ignore_msg)                                                  \
                                             if (close_msg != 0) then begin                                                   \
                                                if (local_var(LVAR_FOLLOW_DISTANCE) != FOLLOW_DISTANCE_CLOSE) then begin      \
                                                   NOption(close_msg, DEF_FOLLOW_CLOSE_NODE, 004);                            \
                                                end                                                                           \
                                             end                                                                              \
                                             if (med_msg != 0) then begin                                                     \
                                                if (local_var(LVAR_FOLLOW_DISTANCE) != FOLLOW_DISTANCE_MEDIUM) then begin     \
                                                   NOption(med_msg, DEF_FOLLOW_MEDIUM_NODE, 004);                             \
                                                end                                                                           \
                                             end                                                                              \
                                             if (far_msg != 0) then begin                                                     \
                                                if (local_var(LVAR_FOLLOW_DISTANCE) != FOLLOW_DISTANCE_FAR) then begin        \
                                                   NOption(far_msg, DEF_FOLLOW_FAR_NODE, 004);                                \
                                                end                                                                           \
                                             end                                                                              \
                                             if (follow_ignore_msg != 0) then begin                                           \
                                                NOption(follow_ignore_msg, PARTY_NODE_X, 004);                                \
                                             end                                                                              \
                                             debug_msg("USED PARTY FOLLOW OPTIONS")

// this goes into node 1008
#define party_gear_options(weapon_use_msg, unarm_msg, armor_msg, gear_ignore_msg)                     \
                                             if (weapon_use_msg != 0) then begin                      \
                                                NOption(weapon_use_msg, DEF_WEAPON_USE_NODE, 004);    \
                                             end                                                      \
                                             if (unarm_msg != 0) then begin                           \
                                                if (self_is_armed) then begin                         \
                                                   NOption(unarm_msg, DEF_UNARM_NODE, 004);           \
                                                end                                                   \
                                             end                                                      \
                                             if (armor_msg != 0) then begin                           \
                                                if (self_wearing_armor) then begin                    \
                                                   NOption(armor_msg, DEF_REMOVE_ARMOR_NODE, 004);    \
                                                end                                                   \
                                             end                                                      \
                                             if (gear_ignore_msg != 0) then begin                     \
                                                NOption(gear_ignore_msg, PARTY_NODE_X, 004);          \
                                             end                                                      \
                                             debug_msg("USED PARTY GEAR OPTIONS")

#define party_member_default_options         party_member_options(def_heal_msg, def_follow_msg, def_gear_msg, def_wait_msg, def_nowait_msg, def_end_msg, def_stupid_msg)
#define party_member_def_follow_options      party_follow_options(def_close_msg, def_med_msg, def_far_msg, def_ignore_follow_msg)
#define party_member_def_gear_options        party_gear_options(def_weapon_use_msg, def_unarm_msg, def_armor_msg, def_ignore_gear_msg)

// party member follow macros
#define party_no_follow_on                   set_global_var(GVAR_PARTY_NO_FOLLOW, 1)
#define party_no_follow_off                  set_global_var(GVAR_PARTY_NO_FOLLOW, 0)
#define party_no_follow                      (global_var(GVAR_PARTY_NO_FOLLOW) != 0)

#define set_follow_close                     set_local_var(LVAR_FOLLOW_DISTANCE, FOLLOW_DISTANCE_CLOSE)
#define set_follow_medium                    set_local_var(LVAR_FOLLOW_DISTANCE, FOLLOW_DISTANCE_MEDIUM)
#define set_follow_far                       set_local_var(LVAR_FOLLOW_DISTANCE, FOLLOW_DISTANCE_FAR)
#define party_member_follow_dude             if ((party_is_waiting == false) and (party_no_follow == false)) then begin                \
                                                if (local_var(LVAR_FOLLOW_DISTANCE) == 0) then begin                                   \
                                                   set_follow_medium;                                                                  \
                                                end                                                                                    \
                                                party_follow_dude_point(((3*local_var(LVAR_FOLLOW_DISTANCE))/2), local_var(LVAR_FOLLOW_DISTANCE))  \
                                             end

// party member team macros
#ifndef set_default_party_follow
  #define set_default_party_follow           set_follow_medium
#endif
#define store_party_team                     if (self_team != TEAM_PLAYER) then begin                 \
                                                set_local_var(LVAR_TEAM, self_team);                  \
                                             end
#define party_add_self                       if (is_critter_dead(self_obj) == false) then begin                            \
                                                if (local_var(LVAR_FOLLOW_DISTANCE) == 0) then begin                       \
                                                   set_default_party_follow;                                               \
                                                end                                                                        \
                                                set_local_var(LVAR_WAITING, 0);                                            \
                                                store_party_team                                                           \
                                                critter_add_trait(self_obj, TRAIT_OBJECT, OBJECT_TEAM_NUM, TEAM_PLAYER);   \
                                                party_add(self_obj);                                                       \
                                             end                                                                           \
                                             debug_msg("join party: " + self_name)
#define party_remove_self                    party_remove(self_obj)

// party member abandons party macros
#define abandoned_party                      (local_var(LVAR_TEAM) == -1)
#define set_self_abandon_party               if (obj_in_party(self_obj)) then begin                                                \
                                                debug_msg("abandon party: " + self_name);                                          \
                                                party_remove_self;                                                                 \
                                             end                                                                                   \
                                             if ((local_var(LVAR_TEAM) != -1) and (self_team == false)) then begin                 \
                                                 critter_add_trait(self_obj, TRAIT_OBJECT, OBJECT_TEAM_NUM, local_var(LVAR_TEAM)); \
                                                 set_local_var(LVAR_TEAM, -1);                                                     \
                                             end                                                                                   \
                                             debug_msg("" + obj_name(self_obj) + " has abandoned the party")

// party member waiting macros
#define party_is_waiting                     (local_var(LVAR_WAITING) != 0)
#define set_party_waiting                    set_local_var(LVAR_WAITING, game_time);      \
                                             party_remove_self
#define end_party_waiting                    set_local_var(LVAR_WAITING, 0);              \
                                             party_add_self

// If a party member was waiting in any invasion location, he will be killed
#define check_invasion_party_waiting        if not(Ian_In_Party) then begin             \
                                                kill_critter_type(PID_IAN, 1);          \
                                            end                                         \
                                            if not(Tycho_In_Party) then begin           \
                                                kill_critter_type(PID_TYCHO, 1);        \
                                            end                                         \
                                            if not(Katja_In_Party) then begin           \
                                                kill_critter_type(PID_KATJA, 1);        \
                                            end                                         \
                                            if not(Tandi_In_Party) then begin           \
                                                kill_critter_type(PID_TANDI, 1);        \
                                            end                                         \
                                            if not(Vasquez_In_Party) then begin         \
                                                kill_critter_type(PID_VASQUEZ, 1);      \
                                            end                                         \
                                            if not(MrHandyC_In_Party) then              \
                                                kill_critter_type(PID_MRHANDYC, 1)


/***************************************************************************************
   Mariposa prisoner state
****************************************************************************************/
#define prisoner_ian_bit                     bit_1
#define prisoner_dog_bit                     bit_2
#define prisoner_tycho_bit                   bit_3
#define prisoner_katja_bit                   bit_4
#define prisoner_tandi_bit                   bit_5
#define prisoner_mrhandy_bit                 bit_6
#define prisoner_eyebot_bit                  bit_7
#define prisoner_rae_bit                     bit_8
#define prisoner_vasquez_bit                 bit_9

#define set_p_prisoner_bit(bit, state)       if (state) then begin                                    \
                                                set_gvar_bit_on(GVAR_PARTY_MEMBERS_PRISONER, bit);    \
                                             end else begin                                           \
                                                set_gvar_bit_off(GVAR_PARTY_MEMBERS_PRISONER, bit);   \
                                             end
#define set_ian_prisoner(state)              set_p_prisoner_bit(prisoner_ian_bit, state)     \
                                             party_remove(Ian_ptr)
#define set_dog_prisoner(state)              set_p_prisoner_bit(prisoner_dog_bit, state)     \
                                             party_remove(Dog_ptr)
#define set_tycho_prisoner(state)            set_p_prisoner_bit(prisoner_tycho_bit, state)   \
                                             party_remove(Tycho_ptr)
#define set_katja_prisoner(state)            set_p_prisoner_bit(prisoner_katja_bit, state)   \
                                             party_remove(Katja_ptr)
#define set_tandi_prisoner(state)            set_p_prisoner_bit(prisoner_tandi_bit, state)   \
                                             party_remove(Tandi_ptr)
#define set_mrhandy_prisoner(state)          set_p_prisoner_bit(prisoner_mrhandy_bit, state) \
                                             party_remove(Handy_ptr)
#define set_eyebot_prisoner(state)           set_p_prisoner_bit(prisoner_eyebot_bit, state)  \
                                             party_remove(Eyebot_ptr)
#define set_rae_prisoner(state)              set_p_prisoner_bit(prisoner_rae_bit, state)     \
                                             party_remove(Rae_ptr)
#define set_vasquez_prisoner(state)          set_p_prisoner_bit(prisoner_vasquez_bit, state) \
                                             party_remove(Vasquez_ptr)

#define party_bit_prisoner(x)                (gvar_bit(GVAR_PARTY_MEMBERS_PRISONER, x))
#define ian_is_prisoner                      party_bit_prisoner(prisoner_ian_bit)
#define dog_is_prisoner                      party_bit_prisoner(prisoner_dog_bit)
#define tycho_is_prisoner                    party_bit_prisoner(prisoner_tycho_bit)
#define katja_is_prisoner                    party_bit_prisoner(prisoner_katja_bit)
#define tandi_is_prisoner                    party_bit_prisoner(prisoner_tandi_bit)
#define mrhandy_is_prisoner                  party_bit_prisoner(prisoner_mrhandy_bit)
#define eyebot_is_prisoner                   party_bit_prisoner(prisoner_eyebot_bit)
#define rae_is_prisoner                      party_bit_prisoner(prisoner_rae_bit)
#define vasquez_is_prisoner                  party_bit_prisoner(prisoner_vasquez_bit)

/***************************************************************************************
   This is to check to see if there are any party members within range of the door
   so it doesn't close.
****************************************************************************************/

/* How far do party members have to be from the door before it closes */
#define PARTY_CLOSE_DIST                (5)

#define CHECKMEMBERNEARDOOR(inparty, obj)                                           \
         if (inparty) then begin                                                    \
            if (tile_distance_objs(self_obj, obj) <= PARTY_CLOSE_DIST) then begin   \
               return 1;                                                            \
            end                                                                     \
         end

procedure checkPartyMembersNearDoor begin
   CHECKMEMBERNEARDOOR(Ian_In_Party, Ian_ptr)
   CHECKMEMBERNEARDOOR(Tycho_In_Party, Tycho_ptr)
   CHECKMEMBERNEARDOOR(Dog_In_Party, Dog_ptr)
   CHECKMEMBERNEARDOOR(Katja_In_Party, Katja_ptr)
   CHECKMEMBERNEARDOOR(Tandi_In_Party, Tandi_ptr)
   CHECKMEMBERNEARDOOR(MrHandyC_In_Party, Handy_ptr)
   CHECKMEMBERNEARDOOR(Eyebot_In_Party, Eyebot_ptr)
   CHECKMEMBERNEARDOOR(Rae_In_Party, Rae_ptr)
   CHECKMEMBERNEARDOOR(Vasquez_In_Party, Vasquez_ptr)
   return 0;
end

/***************************************************************************************
   Get who has the highest skill in the party
****************************************************************************************/
procedure get_highest_skill_in_party(variable skill) begin
   variable who, max;
   foreach (who in party_member_list_critters) begin
      if (has_skill(who, skill) > max) then begin
         max := has_skill(who, skill);
      end
   end
   return max;
end

#define has_skill_party(x) \
   get_highest_skill_in_party(x)
