#ifndef COMMAND_H
#define COMMAND_H

#define critter_is_armed(x)                 (((obj_item_subtype(critter_inven_obj(x,INVEN_TYPE_RIGHT_HAND))) == item_type_weapon) orElse \
                                             ((obj_item_subtype(critter_inven_obj(x,INVEN_TYPE_LEFT_HAND))) == item_type_weapon))

#define critter_weight_calc(x)              (100 + ((get_critter_stat(x,STAT_gender) == GENDER_MALE) * 50) + (get_critter_stat(x,STAT_st) * 5) - ((get_critter_stat(x,STAT_ag) + get_critter_stat(x,STAT_en))/3))
#define critter_weight(x)                   get_critter_stat(x, STAT_carry_amt)
#define critter_wearing_armor(x)            (obj_item_subtype(critter_inven_obj(x,INVEN_TYPE_WORN)) == item_type_armor)

#define dude_is_stupid                      (dude_iq <= 3)
#define dude_name                           (obj_name(dude_obj))
#define dude_gender                         (get_critter_stat(dude_obj,STAT_gender))
#define dude_strength                       (get_critter_stat(dude_obj,STAT_st))
#define dude_perception                     (get_critter_stat(dude_obj,STAT_pe))
#define dude_endurance                      (get_critter_stat(dude_obj,STAT_en))
#define dude_charisma                       (get_critter_stat(dude_obj,STAT_ch))
#define dude_iq                             (get_critter_stat(dude_obj,STAT_iq))
#define dude_agility                        (get_critter_stat(dude_obj,STAT_ag))
#define dude_luck                           (get_critter_stat(dude_obj,STAT_lu))
#define dude_level                          (get_pc_stat(PCSTAT_level))
#define dude_age                            (get_critter_stat(dude_obj,STAT_age))
#define dude_weight                         critter_weight(dude_obj)
#define dude_cur_weight                     who_carry_amount(dude_obj)

#define dude_moron_not_vegetable            (((get_critter_stat(dude_obj,STAT_iq)) > 1) andAlso ((get_critter_stat(dude_obj,STAT_iq)) < 3) )

#define dude_is_male                        (dude_gender == GENDER_MALE)
#define dude_is_female                      (dude_gender == GENDER_FEMALE)
#define dude_is_armed                       critter_is_armed(dude_obj)
#define dude_wearing_armor                  critter_wearing_armor(dude_obj)

#define dude_has_power_armor                (((obj_is_carrying_obj_pid(dude_obj, PID_POWERED_ARMOR)) +            \
                                              (obj_is_carrying_obj_pid(dude_obj, PID_ADVANCED_POWER_ARMOR)) +     \
                                              (obj_is_carrying_obj_pid(dude_obj, PID_ADVANCED_POWER_ARMOR_MK2)) + \
                                              (obj_is_carrying_obj_pid(dude_obj, PID_HARDENED_POWER_ARMOR))) > 0)

#define dude_wielding_knife                 ((obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_RIGHT_HAND)) == PID_KNIFE) orElse                \
                                             (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_RIGHT_HAND)) == PID_THROWING_KNIFE) orElse       \
                                             (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_RIGHT_HAND)) == PID_RIPPER) orElse               \
                                             (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_RIGHT_HAND)) == PID_COMBAT_KNIFE) orElse         \
                                             (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_LEFT_HAND)) == PID_KNIFE) orElse                 \
                                             (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_LEFT_HAND)) == PID_THROWING_KNIFE) orElse        \
                                             (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_LEFT_HAND)) == PID_RIPPER) orElse                \
                                             (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_LEFT_HAND)) == PID_COMBAT_KNIFE))

#define dude_wearing_power_armor            ((obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_WORN)) == PID_POWERED_ARMOR) orElse \
                                             (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_WORN)) == PID_ADVANCED_POWER_ARMOR) orElse \
                                             (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_WORN)) == PID_ADVANCED_POWER_ARMOR_MK2) orElse \
                                             (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_WORN)) == PID_HARDENED_POWER_ARMOR))

#define dude_wearing_leather_armor          ((obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_WORN)) == PID_LEATHER_ARMOR) orElse \
                                             (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_WORN)) == PID_LEATHER_JACKET) orElse \
                                             (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_WORN)) == PID_LEATHER_ARMOR_MK_II) orElse \
                                             (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_WORN)) == PID_CURED_LEATHER_ARMOR))

#define dude_wearing_combat_armor           ((obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_WORN)) == PID_COMBAT_ARMOR) orElse \
                                             (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_WORN)) == PID_BROTHERHOOD_COMBAT_ARMOR) orElse \
                                             (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_WORN)) == PID_COMBAT_ARMOR_MK_II))

#define dude_wearing_metal_armor            ((obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_WORN)) == PID_METAL_ARMOR) orElse \
                                             (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_WORN)) == PID_METAL_ARMOR_MK_II))

#define dude_has_gambling_skills            ((dude_iq > 3) andAlso (has_skill(dude_obj, SKILL_GAMBLING) >= 25))

#define dude_is_sneaking                    (using_skill(dude_obj,SKILL_SNEAK))
#define dude_is_walking                     (art_anim(obj_art_fid(dude_obj)) == ANIM_walk)
#define dude_is_running                     (art_anim(obj_art_fid(dude_obj)) == ANIM_running)
#define dude_is_poisoned                    (get_poison(dude_obj))
#define dude_is_irradiated                  (get_critter_stat(dude_obj, STAT_current_rad))
#define dude_is_crippled                    ((critter_state(dude_obj) bwand DAM_CRIP_LEG_LEFT)  orElse \
                                             (critter_state(dude_obj) bwand DAM_CRIP_LEG_RIGHT) orElse \
                                             (critter_state(dude_obj) bwand DAM_CRIP_ARM_LEFT)  orElse \
                                             (critter_state(dude_obj) bwand DAM_CRIP_ARM_RIGHT))

#define dude_cur_rot                        (has_trait(TRAIT_OBJECT,dude_obj,OBJECT_CUR_ROT))
#define dude_inv_rot                        ((dude_cur_rot + 3)%6)
#define dude_tile                           (tile_num(dude_obj))
#define dude_elevation                      (elevation(dude_obj))

#define tile_behind_obj(who)                (tile_num_in_direction(tile_num(who),((has_trait(TRAIT_OBJECT,who,OBJECT_CUR_ROT) + 3) % 6), 1))

#define dude_cur_hits                       (get_critter_stat(dude_obj,STAT_current_hp))
#define dude_max_hits                       (get_critter_stat(dude_obj,STAT_max_hp))

#define dude_mental_block                   (has_trait(TRAIT_PERK,dude_obj,PERK_mental_block))
#define dude_presence                       (has_trait(TRAIT_PERK,dude_obj,PERK_presence))
#define dude_awareness                      (has_trait(TRAIT_PERK,dude_obj,PERK_bonus_awareness))
#define dude_fortune_finder                 (has_trait(TRAIT_PERK,dude_obj,PERK_fortune_finder))
#define dude_smooth_talker                  (has_trait(TRAIT_PERK,dude_obj,PERK_smooth_talker))

#define dude_caps                           (item_caps_total(dude_obj))

#define dude_has_car                        (global_var(GVAR_PLAYER_GOT_CAR))
#define dude_is_pornstar                    dude_has_porn_star_rep
#define dude_is_high                        drug_influence(dude_obj)

#define dude_stat_win(X,Y)                  ((do_check(dude_obj,X,Y)) > (do_check(self_obj,X,0)))
#define dude_stat_lose(X,Y)                 ((do_check(dude_obj,X,Y)) < (do_check(self_obj,X,0)))
#define dude_stat_tie(X,Y)                  ((do_check(dude_obj,X,Y)) == (do_check(self_obj,X,0)))
#define dude_can_see_self                   obj_can_see_obj(dude_obj,self_obj)

#define dude_item(x)                        obj_carrying_pid_obj(dude_obj, x)
#define dude_item_count(x)                  obj_is_carrying_obj_pid(dude_obj, x)

#define dude_is_addict                      (has_trait(TRAIT_TRAIT, dude_obj, TRAIT_drug_addict))

#define self_name                           (obj_name(self_obj))
#define self_gender                         (get_critter_stat(self_obj,STAT_gender))
#define self_strength                       (get_critter_stat(self_obj,STAT_st))
#define self_perception                     (get_critter_stat(self_obj,STAT_pe))
#define self_endurance                      (get_critter_stat(self_obj,STAT_en))
#define self_charisma                       (get_critter_stat(self_obj,STAT_ch))
#define self_iq                             (get_critter_stat(self_obj,STAT_iq))
#define self_agility                        (get_critter_stat(self_obj,STAT_ag))
#define self_luck                           (get_critter_stat(self_obj,STAT_lu))

#define self_is_male                        (self_gender == GENDER_MALE)
#define self_is_female                      (self_gender == GENDER_FEMALE)
#define self_is_armed                       critter_is_armed(self_obj)
#define self_wearing_armor                  critter_wearing_armor(self_obj)

#define self_carrying_laser_pistol          ((obj_pid(critter_inven_obj(self_obj,INVEN_TYPE_LEFT_HAND)) == PID_LASER_PISTOL) orElse \
                                             (obj_pid(critter_inven_obj(self_obj,INVEN_TYPE_RIGHT_HAND)) == PID_LASER_PISTOL))

#define self_is_sneaking                    (using_skill(self_obj,SKILL_SNEAK))
#define self_is_walking                     (art_anim(obj_art_fid(self_obj)) == ANIM_walk)
#define self_is_running                     (art_anim(obj_art_fid(self_obj)) == ANIM_running)
#define self_is_poisoned                    (get_poison(self_obj))

#define self_cur_rot                        (has_trait(TRAIT_OBJECT,self_obj,OBJECT_CUR_ROT))
#define self_inv_rot                        ((self_cur_rot + 3)%6)
#define self_tile                           (tile_num(self_obj))
#define self_elevation                      (elevation(self_obj))

#define self_pid                            (obj_pid(self_obj))
#define self_team                           has_trait(TRAIT_OBJECT,self_obj,OBJECT_TEAM_NUM)
#define self_ai                             has_trait(TRAIT_OBJECT,self_obj,OBJECT_AI_PACKET)
#define self_visible                        obj_is_visible_flag(self_obj)

#define self_cur_hits                       (get_critter_stat(self_obj,STAT_current_hp))
#define self_max_hits                       (get_critter_stat(self_obj,STAT_max_hp))

#define self_mental_block                   (has_trait(TRAIT_PERK,self_obj,PERK_mental_block))
#define self_presence                       (has_trait(TRAIT_PERK,self_obj,PERK_presence))
#define self_awareness                      (has_trait(TRAIT_PERK,self_obj,PERK_bonus_awareness))
#define self_fortune_finder                 (has_trait(TRAIT_PERK,self_obj,PERK_fortune_finder))

#define self_caps                           (item_caps_total(self_obj))
#define self_fid                            (obj_art_fid(self_obj))

#define skill_success(x,y,z)                (is_success(roll_vs_skill(x,y,z)))
#define stat_success(x,y,z)                 (is_success(do_check(x,y,z)))

#define self_can_see_dude                   obj_can_see_obj(self_obj,dude_obj)
#define self_distance_from_dude             tile_distance(self_tile, dude_tile)
#define self_is_high                        drug_influence(self_obj)

#define self_item(x)                        obj_carrying_pid_obj(self_obj, x)
#define self_item_count(x)                  obj_is_carrying_obj_pid(self_obj, x)


// some timer event macros
#define check_set_obj_visiblility(the_obj, x)      if (obj_is_visible_flag(the_obj) == x) then set_obj_visibility(the_obj, x)

#define flush_add_timer_event(obj, time, param)    rm_fixed_timer_event(obj, param);               \
                                                   add_timer_event(obj, time, param)

#define flush_add_timer_event_sec(obj, sec, param) flush_add_timer_event(obj, game_ticks(sec), param)

/******************************************************************
 General commands getting information about time
******************************************************************/

#define morning                             ((game_time_hour >= 600) andAlso  (game_time_hour < 700))
#ifndef day
#define day                                 ((game_time_hour >= 700) andAlso  (game_time_hour < 1800))
#endif
#define evening                             ((game_time_hour >= 1800) andAlso (game_time_hour < 1900))
#ifndef night
#define night                               ((game_time_hour >= 1900) orElse  (game_time_hour < 600))
#endif

#define GAME_TIME_SUBSECOND_RESOLUTION  (10)
#define SECONDS_PER_MINUTE              (60)
#define MINUTES_PER_HOUR                (60)
#define HOURS_PER_DAY                   (24)
#define DAYS_PER_YEAR                   (365)
                                // Seconds Minutes Hours Days Months ==> Year
#define GAME_TIME_IN_YEARS   (game_time / (GAME_TIME_SUBSECOND_RESOLUTION * SECONDS_PER_MINUTE * MINUTES_PER_HOUR * HOURS_PER_DAY * DAYS_PER_YEAR))
#define GAME_TIME_IN_DAYS    (game_time / (GAME_TIME_SUBSECOND_RESOLUTION * 60 * 60 * 24))
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
#define floater(x)              float_msg(self_obj, message_str(NAME,x), FLOAT_COLOR_NORMAL)
#define floater_rand(x,y)       floater(random(x,y))

#define dude_floater(x)         float_msg(dude_obj, message_str(NAME,x), FLOAT_COLOR_NORMAL)
#define dude_floater_rand(x,y)  dude_floater(random(x,y))
#define dude_floater_bad(x)     float_msg(dude_obj, message_str(NAME,x), FLOAT_COLOR_BAD)
#define dude_floater_sick(x)    float_msg(dude_obj, message_str(NAME,x), FLOAT_COLOR_SICK)

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
#define g_mstr(x)                   message_str(SCRIPT_GENERIC,x)
#define g_grunt                     g_mstr(random(300,303))
#define g_bye                       g_mstr(random(375,376))

#define LOW_IQ                      (-3)

#define Reply(x)                    gSay_Reply(NAME,x)
#define Reply_Rand(x,y)             Reply(random(x,y))
#define GMessage(x)                 gSay_Message(NAME,x,GOOD_REACTION)
#define NMessage(x)                 gSay_Message(NAME,x,NEUTRAL_REACTION)
#define BMessage(x)                 gSay_Message(NAME,x,BAD_REACTION)

// this converts a number from 0-100 to the text representing the number, ie: 1 -> "one", 40 -> "forty-one"
#define num_to_num_text(x)          g_mstr(2000+x)

// Option(Message Number, Node Number, IQ)         ==>     giQ_Option(IQ, Message Number, Node Number)      -rwh2 (11/12/97)
#define GOption(x,y,z)              giQ_Option(z,NAME,x,y,GOOD_REACTION)
#define NOption(x,y,z)              giQ_Option(z,NAME,x,y,NEUTRAL_REACTION)
#define BOption(x,y,z)              giQ_Option(z,NAME,x,y,BAD_REACTION)
#define GLowOption(x,y)             giQ_Option(LOW_IQ,NAME,x,y,GOOD_REACTION)
#define NLowOption(x,y)             giQ_Option(LOW_IQ,NAME,x,y,NEUTRAL_REACTION)
#define BLowOption(x,y)             giQ_Option(LOW_IQ,NAME,x,y,BAD_REACTION)

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
#define critter_is_male         (get_critter_stat(self_obj,STAT_gender) == GENDER_MALE)
#define critter_is_female       (get_critter_stat(self_obj,STAT_gender) == GENDER_FEMALE)

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

#define status_is_alive(status_var)                   (not (status_is_killed(status_var) orElse status_is_assassinated(status_var) orElse status_is_dead(status_var)))


/******************************************************************
 General commands getting information about cities
******************************************************************/
#define mark_on_map(x)                      if (town_known(x) == MARK_STATE_UNKNOWN) then begin          \
                                               debug_msg("  mark_on_map("+x+")");                        \
                                               mark_area_known(MARK_TYPE_TOWN, x, MARK_STATE_KNOWN);     \
                                            end

#define unmark_on_map(x)                    if (town_known(x) != MARK_STATE_UNKNOWN) then begin          \
                                               debug_msg(" unmark_on_map("+x+")");                       \
                                               mark_area_known(MARK_TYPE_TOWN, x, MARK_STATE_UNKNOWN);   \
                                            end

/*******************************************************************************************************************
********** These represent the players acomplishments through the game *********************************************
********** Note: these reflect the Fallout2 variable designers put in the scripts assuming we were *****************
********** going to have a magic variable to keep track of the player stats throught the game **********************
*******************************************************************************************************************/

// Info relating to carry weight, how much something costs, and weights
#define pid_weight(x)                                   proto_data(x,it_weight)
#define obj_weight(x)                                   pid_weight(obj_pid(x))
#define pid_cost(x)                                     proto_data(x, it_cost)
#define obj_cost(x)                                     pid_cost(obj_pid(x))

#define amt_cost_barter(who1, who2, x)                  floor(2 * x * ((160.0 + has_skill(who2,SKILL_BARTER)) / (160.0 + has_skill(who1,SKILL_BARTER))))
#define pid_cost_barter(who1, who2, x)                  amt_cost_barter(who1, who2, pid_cost(x))
#define obj_cost_barter(who1, who2, x)                  pid_cost_barter(who1, who2, obj_pid(x))
#define who_max_carry(x)                                get_critter_stat(x,STAT_carry_amt)
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


#endif // COMMAND_H
