/*

    Generic Fo1 defines

*/

#ifndef FO1_H
#define FO1_H

#include "debug.h"

/*********************************************************
    General stats stuff. Moved here because of Wipe.
*********************************************************/
// Trait defines //
#define TRAIT_PERK   (0)
#define TRAIT_OBJECT (1)
#define TRAIT_TRAIT  (2)

/*********************************************************
    Settings:
*********************************************************/
#define fo1in2_fluff_enc_disabled       ((global_var(GVAR_DISABLE_FLUFF_ENCOUNTER) > 0) or get_car_from_worldmap)
#define fo1in2_auto_doors_closing       (global_var(GVAR_AUTO_DOORS_CLOSING) > 0)
#define fo1in2_motorcycle_disabled      (global_var(GVAR_ENABLE_MOTORCYCLE) == 0)
#define fo1in2_destroy_armor_disabled   (global_var(GVAR_ARMOR_DESTROY_MOD) == 0)
#define fo1in2_merch_restock_disabled   (global_var(GVAR_ENABLE_FO2_MERCHANT_RESTOCK) == 0)
#define fo1in2_satellite_loc_disabled   (global_var(GVAR_ENABLE_SATELLITE_LOCATIONS) == 0)
#define fo1in2_unlimited_hpa_disabled   (global_var(GVAR_ENABLE_UNLIMITED_HPA) == 0)
#define fo1in2_maltese_singer_disabled  (global_var(GVAR_ENABLE_MALTESE_SINGER) == 0)
#define fo1in2_party_limit_disabled     (global_var(GVAR_ENABLE_FO2_PARTY_LIMIT) == 0)

#define fixt_enabled                    (global_var(GVAR_FIXT_ENABLED) == 1)
#define fixt_disabled                   not(fixt_enabled)

/*********************************************************
    Generic:
    Note: If the player decides to continue after finishing the game,
    He will be moved to a new random position on the worldmap.
*********************************************************/
#define set_story_finished          set_world_map_pos(random(780,990),random(130,260));   \
                                    set_global_var(GVAR_GAME_CONTINUES,100);              \
                                    mark_map_entrance_state(MAP_VAULT13,0);               \
                                    mark_map_entrance_elev_state(MAP_VAULT13,0,0);        \
                                    mark_map_entrance_elev_state(MAP_VAULT13,1,0);        \
                                    mark_map_entrance_elev_state(MAP_VAULT13,2,0);        \
                                    if (dude_is_male) then                                \
                                       play_gmovie(WALKM_MOVIE);                          \
                                    else                                                  \
                                       play_gmovie(WALKW_MOVIE);                          \
                                    endgame_movie;                                        \
                                    gfade_out(1);                                         \
                                    party_member_unhide_all                               \
                                    /*world_map;*/load_map(MAP_RNDDESER,0);               \
                                    gfade_in(1)

#define is_story_finished           (global_var(GVAR_GAME_CONTINUES) > 0)

/*********************************************************
    Quests:
*********************************************************/
#define waterchip_returned                  (global_var(GVAR_QUEST_VAULT13_4_WATERCHIP) >= 2)
#define set_waterchip_returned              set_global_var(GVAR_QUEST_VAULT13_4_WATERCHIP, 2)

#define get_quest_vats_active               ((global_var(GVAR_QUEST_VAULT13_3_KILL_VATS) > 0) and not(military_base_destoryed))
#define get_quest_master_active             ((global_var(GVAR_QUEST_VAULT13_2_MASTER) > 0) and not(cathedral_destroyed))

#define military_base_destoryed             (global_var(GVAR_VATS_BLOWN_CUTSCENE_DONE) > 0)
#define cathedral_destroyed                 (global_var(GVAR_MASTER_BLOWN_CUTSCENE) > 0)
#define set_military_base_destoryed         set_global_var(GVAR_VATS_BLOWN_CUTSCENE_DONE, 1); \
                                            set_end_Vats
#define set_cathedral_destroyed             set_global_var( GVAR_MASTER_BLOWN_CUTSCENE, 1); \
                                            set_end_Master

#define necropolis_wpump_fixed              (global_var(GVAR_NECROP_WATER_PUMP_FIXED) == 2)

#define followers_trained                   (global_var(GVAR_SLIDE_TRAIN_FOLLOWERS) == 1)

#define get_raiders_alive                   global_var(GVAR_TOTAL_RAIDERS)

#define is_tandi_alive                      (global_var(GVAR_TANDI_HIRELING_STATUS) < 3)
#define is_aradesh_alive                    (global_var(GVAR_ARADESH_STATUS) == 0)
#define is_killian_alive                    (global_var(GVAR_KILLIAN_DEAD) == 0)
#define is_gizmo_alive                      (global_var(GVAR_GIZMO_DEAD) == 0)
#define is_rhombus_alive                    (global_var(GVAR_RHOMBUS_STATUS) == 0)
#define is_garl_alive                       (global_var(GVAR_GARL_DEAD) == 0)
#define is_nicole_alive                     (global_var(GVAR_NICOLE_DEAD) == 0)

#define is_laura_alive                      (global_var(GVAR_IS_LAURA_ALIVE) != 1)
#define set_laura_escaping                  set_global_var(GVAR_IS_LAURA_ALIVE,2)
#define is_laura_escaping                   (global_var(GVAR_IS_LAURA_ALIVE) == 2)
#define set_laura_escaped                   set_global_var(GVAR_IS_LAURA_ALIVE,3)
#define is_laura_escaped                    (global_var(GVAR_IS_LAURA_ALIVE) == 3)

#define set_hunter_killed                   set_global_var(GVAR_HUNTER_STATUS,3)
#define bounty_hunter_killed                (global_var(GVAR_HUNTER_STATUS) == 3)

#define tandi_is_kidnapped                  (global_var(GVAR_TANDI_HIRELING_STATUS) == 1)
#define tandi_not_kidnapped                 not(tandi_is_kidnapped)
#define tandi_is_rescued                    (global_var(GVAR_TANDI_HIRELING_STATUS) == 2)

/*********************************************************
    TMA / Tell Me About
*********************************************************/
// msg string source
#define tma_source_critter      (get_script(critter) + 1)
#define tma_source_generic      (SCRIPT_OBJ_DUDE)

// generic defines
#define TMA_MSG_NAME_START      (970)
#define TMA_MSG_NAME_END        (972)

#define TMA_MSG_DONTKNOW_START  (980)
#define TMA_MSG_DONTKNOW_END    (982)

// (location) types from OBJ_DUDE.msg
#define TMA_MSG_HALLDED         (2800)
#define TMA_MSG_HOTEL           (3400)
#define TMA_MSG_WATRSHD         (4000)
#define TMA_MSG_VAULT13         (4600)
#define TMA_MSG_JUNKENT         (7000)
#define TMA_MSG_JUNKCSNO        (7600)
#define TMA_MSG_JUNKKILL        (8200)
#define TMA_MSG_BOS             (8800)
#define TMA_MSG_COC             (11200)
#define TMA_MSG_RAIDERS         (15400)
#define TMA_MSG_SHADYE          (16000)
#define TMA_MSG_SHADYW          (16600)
#define TMA_MSG_MBASE           (19000)
#define TMA_MSG_HUBENT          (22600)
#define TMA_MSG_HUBDWNTN        (23800)
#define TMA_MSG_HUBHEIGT        (24400)
#define TMA_MSG_HUBOLDTN        (25000)
#define TMA_MSG_HUBWATER        (25600)
#define TMA_MSG_ADYTUM_LVL1     (17800) // [People who know nothing]
#define TMA_MSG_ADYTUM_LVL2     (18000) // [People who know something]
#define TMA_MSG_ADYTUM_LVL3     (18200) // [People who know more than something but less than everything]
#define TMA_MSG_FOLLOWER_LVL1   (18400)
#define TMA_MSG_FOLLOWER_LVL2   (18600)
#define TMA_MSG_FOLLOWER_LVL3   (18800)
#define TMA_MSG_BLADES_LVL1     (27400)
#define TMA_MSG_BLADES_LVL2     (27600)
#define TMA_MSG_BLADES_LVL3     (27800)
#define TMA_MSG_GUNRUNNR_LVL1   (28600)
#define TMA_MSG_GUNRUNNR_LVL2   (28800)
#define TMA_MSG_GUNRUNNR_LVL3   (29000)

variable tma_data_array;
variable tma_gvar_array;
#define set_tma_data(source, reply_str, name_str_start, name_str_end, unknown_str_start, unknown_str_end)       \
    if (tma_data_array == 0) then begin                                                                         \
        tma_data_array := get_sfall_global_int("TMA_DATA");                                                     \
    end                                                                                                         \
    tma_data_array[0] := source;                                                                                \
    tma_data_array[1] := reply_str;                                                                             \
    tma_data_array[2] := name_str_start;                                                                        \
    tma_data_array[3] := name_str_end;                                                                          \
    tma_data_array[4] := unknown_str_start;                                                                     \
    tma_data_array[5] := unknown_str_end

// Shortcut
#define set_tma_data_generic(x)     set_tma_data(tma_source_generic, x, TMA_MSG_NAME_START, TMA_MSG_NAME_END, TMA_MSG_DONTKNOW_START, TMA_MSG_DONTKNOW_END)

// If reply <line> is triggered, set <GVAR_> to <val>
// Must be placed in the critter talk_p_proc.
// TODO: Allow multiple GVARs and condition checks at some point? Not sure how necessary that will be, though.
#define set_tma_gvar(line_num,gvar,val)                     \
    if (tma_gvar_array == 0) then begin                     \
        tma_gvar_array := get_sfall_global_int("TMA_GVAR"); \
    end                                                     \
    tma_gvar_array[0] := line_num;                          \
    tma_gvar_array[1] := gvar;                              \
    tma_gvar_array[2] := val

// Reset TMA data (after dialog ended)
// This is used in party member talk_p_proc to workaround a reset-bug!
#define reset_tma_data      tma_data_array[0] := 0; \
                            tma_gvar_array[0] := 0

/*********************************************************
    Game time Limits
*********************************************************/
// GVAR_VAULT13_WATER_DAYS_COUNTER is set in the start procedure of OBJ_DUDE.
// We need this to keep track of the correct time (start time is advanced randomly by a few hours).
#define get_days_passed                     (GAME_TIME_IN_DAYS - global_var(GVAR_VAULT13_WATER_DAYS_COUNTER) / (GAME_TIME_SUBSECOND_RESOLUTION * 60 * 60 * 24))

/*********************************************************
            Water Chip related:
*********************************************************/
#define get_water_days_left                 (global_var(GVAR_VAULT13_WATER_DAYS) - get_days_passed)

#define TIME_LIMIT_1                        (100)
#define TIME_LIMIT_2                        (50)
#define TIME_LIMIT_3                        (0)

#define reached_tl_1                        (get_water_days_left <= TIME_LIMIT_1)
#define reached_tl_2                        (get_water_days_left <= TIME_LIMIT_2)
#define reached_tl_3                        (get_water_days_left <= TIME_LIMIT_3)

/*********************************************************
            Invasion related:
*********************************************************/
#define v13_invaded                         (global_var(GVAR_VAULT_13_WAS_INVADED) == 1)
#define hub_invaded                         (global_var(GVAR_THE_HUB_WAS_INVADED) == 1)
#define bos_invaded                         (global_var(GVAR_BROTHERHOOD_WAS_INVADED) == 1)
#define boneyard_invaded                    (global_var(GVAR_FOLLOWERS_INVADED) == 1)
#define necropolis_invaded                  (global_var(GVAR_NECROPOLIS_WAS_INVADED) == 1)
#define shady_invaded                       (global_var(GVAR_SHADY_SANDS_WAS_INVADED) == 1)
#define junktown_invaded                    (global_var(GVAR_JUNKTOWN_WAS_INVADED) == 1)

#define get_v13_days_left                   (global_var(GVAR_VAULT_13_INVASION_DAYS) - get_days_passed)
#define set_v13_days_left(x)                set_global_var(GVAR_VAULT_13_INVASION_DAYS, (get_v13_days_left + x))

#define get_hub_days_left                   (global_var(GVAR_THE_HUB_INVASION_DAYS) - get_days_passed)
#define get_bos_days_left                   (global_var(GVAR_BROTHERHOOD_INVASION_DAYS) - get_days_passed)
#define get_boneyard_days_left              (global_var(GVAR_BONEYARD_INVASION_DAYS) - get_days_passed)
#define get_necropolis_days_left            (global_var(GVAR_NECROPOLIS_INVASION_DAYS) - get_days_passed)
#define get_shady_days_left                 (global_var(GVAR_SHADY_SANDS_INVASION_DAYS) - get_days_passed)
#define get_junktown_days_left              (global_var(GVAR_JUNKTOWN_INVASION_DAYS) - get_days_passed)

/*********************************************************
    Endgame slideshow
*********************************************************/
#define set_end_Vats                        set_global_var(GVAR_ENDGAME_MOVIE_MUTANTS,1)
#define set_end_Master                      set_global_var(GVAR_ENDGAME_MOVIE_MUTANTS,2)

#define set_end_necropolis_dehydrated       set_global_var(GVAR_ENDGAME_MOVIE_NECROPOLIS,1)
#define set_end_necropolis_survived         set_global_var(GVAR_ENDGAME_MOVIE_NECROPOLIS,2)
#define set_end_necropolis_invaded          set_global_var(GVAR_ENDGAME_MOVIE_NECROPOLIS,3)

#define set_end_foa_trained                 set_global_var(GVAR_ENDGAME_MOVIE_BONEYARD,1)
#define set_end_foa_invaded                 set_global_var(GVAR_ENDGAME_MOVIE_BONEYARD,2)

#define set_end_shady_good                  set_global_var(GVAR_ENDGAME_MOVIE_SHADY,1)
#define set_end_shady_tandi_dead            set_global_var(GVAR_ENDGAME_MOVIE_SHADY,2)
#define set_end_shady_aradesh_dead          set_global_var(GVAR_ENDGAME_MOVIE_SHADY,3)
#define set_end_shady_bad                   set_global_var(GVAR_ENDGAME_MOVIE_SHADY,4)
#define set_end_shady_invaded               set_global_var(GVAR_ENDGAME_MOVIE_SHADY,5)

#define set_end_junktown_killian            set_global_var(GVAR_ENDGAME_MOVIE_JUNKTOWN,1)
#define set_end_junktown_gizmo              set_global_var(GVAR_ENDGAME_MOVIE_JUNKTOWN,2)
#define set_end_junktown_invaded            set_global_var(GVAR_ENDGAME_MOVIE_JUNKTOWN,3)

#define set_end_bos_good                    set_global_var(GVAR_ENDGAME_MOVIE_BOS,1)
#define set_end_bos_bad                     set_global_var(GVAR_ENDGAME_MOVIE_BOS,2)
#define set_end_bos_invaded                 set_global_var(GVAR_ENDGAME_MOVIE_BOS,3)

#define set_end_hub_good                    set_global_var(GVAR_ENDGAME_MOVIE_HUB,1)
#define set_end_hub_bad                     set_global_var(GVAR_ENDGAME_MOVIE_HUB,2)

#define set_end_raiders_dead                set_global_var(GVAR_ENDGAME_MOVIE_KHANS,1)
#define set_end_raiders_hurt                set_global_var(GVAR_ENDGAME_MOVIE_KHANS,2)
#define set_end_raiders_alive               set_global_var(GVAR_ENDGAME_MOVIE_KHANS,3)

#define set_end_ending_vd                   set_global_var(GVAR_ENDGAME_MOVIE_VD,1)

/*********************************************************
    Invasions
*********************************************************/
// Pick dead body type:
#define invasion_kill_critter                          	\
	variable DeathType := 56;                        	\
	variable LVar0 := random(0, 18);                 	\
	if (LVar0 <= 5) then begin/*// 31.5%*/            	\
		DeathType := ANIM_burned_to_nothing_sf;       	\
	end                                                	\
	else if (LVar0 <= 10) then begin/*// 26%*/       	\
		DeathType := ANIM_sliced_in_half_sf;         	\
	end                                                	\
	else if (LVar0 <= 14) then begin/*// 21%*/       	\
		DeathType := ANIM_chunks_of_flesh_sf;          	\
	end                                               	\
	else if (LVar0 <= 16) then begin/*// 10.5%*/      	\
		DeathType := ANIM_fall_front_blood_sf;         	\
	end                                               	\
	else begin/*// <--------------------    16%*/      	\
		variable LVar1 := 0;                          	\
		LVar1 := random(0, 2);                         	\
		if (LVar1 == 0) then begin                    	\
			DeathType := ANIM_dancing_autofire_sf;     	\
		end                                           	\
		else if (LVar1 == 1) then begin                	\
			DeathType := ANIM_exploded_to_nothing_sf;	\
		end                                            	\
		else if (LVar1 == 2) then begin             	\
			DeathType := ANIM_melted_to_nothing_sf;   	\
		end                                          	\
	end                                               	\
	kill_critter(self_obj, DeathType)

/*********************************************************
    Other stuff
*********************************************************/
// Send NPCs from "day" to "night" position:
#define sleeping    /*debug("sleeping tile: " + sleep_tile + " and home tile: " + home_tile);*/ \
                    if (local_var(LVAR_Sleeping) == 1) then begin \
                        if (not(night_person) and (game_time_hour >= wake_time) and (game_time_hour < sleep_time) or (night_person and ((game_time_hour >= wake_time) or (game_time_hour < sleep_time)))) then begin \
                            if (((game_time_hour - wake_time) < 10) and ((game_time_hour - wake_time) > 0)) then begin \
                                if (tile_num(self_obj) != home_tile) then begin \
                                    animate_move_obj_to_tile(self_obj, home_tile, 0); \
                                end \
                                else begin \
                                    set_local_var(LVAR_Sleeping, 0); \
                                end \
                            end \
                            else begin \
                                move_to(self_obj, home_tile, elevation(self_obj)); \
                                if (tile_num(self_obj) == home_tile) then begin \
                                    set_local_var(LVAR_Sleeping, 0); \
                                end \
                            end \
                        end \
                    end \
                    else begin \
                        if (night_person and (game_time_hour >= sleep_time) and (game_time_hour < wake_time) or (not(night_person) and ((game_time_hour >= sleep_time) or (game_time_hour < wake_time)))) then begin \
                            if (((game_time_hour - sleep_time) < 10) and ((game_time_hour - sleep_time) > 0)) then begin \
                                if (tile_num(self_obj) != sleep_tile) then begin \
                                    animate_move_obj_to_tile(self_obj, self_obj, 0); \
                                end \
                                else begin \
                                    set_local_var(LVAR_Sleeping, 1); \
                                end \
                            end \
                            else begin \
                                if (tile_num(self_obj) != sleep_tile) then begin \
                                    move_to(self_obj, sleep_tile, elevation(self_obj)); \
                                end \
                                else begin \
                                    set_local_var(LVAR_Sleeping, 1); \
                                end \
                            end \
                        end \
                    end

procedure flee_dude begin
    variable LVar0 := 0;
    variable LVar1 := 0;
    variable LVar2 := 0;
    while(LVar1 < 5) do begin
        if (tile_distance(tile_num(dude_obj), tile_num_in_direction(tile_num(self_obj), LVar1, 3)) > LVar2) then begin
            LVar0 := tile_num_in_direction(tile_num(self_obj), LVar1, 3);
            LVar2 := tile_distance(tile_num(dude_obj), LVar0);
        end
        LVar1 := LVar1 + 1;
    end
    animate_move_obj_to_tile(self_obj, LVar0, 1);
end

#define map_is_caravan_escort       (cur_map_index == MAP_DESCRVN1) or      \
                                    (cur_map_index == MAP_DESCRVN2) or      \
                                    (cur_map_index == MAP_DESCRVN3) or      \
                                    (cur_map_index == MAP_DESCRVN4) or      \
                                    (cur_map_index == MAP_MNTCRVN1) or      \
                                    (cur_map_index == MAP_MNTCRVN2) or      \
                                    (cur_map_index == MAP_MNTCRVN3) or      \
                                    (cur_map_index == MAP_MNTCRVN4)

#define map_is_mountain_caravan_escort  (cur_map_index == MAP_MNTCRVN1) or  \
                                        (cur_map_index == MAP_MNTCRVN2) or  \
                                        (cur_map_index == MAP_MNTCRVN3) or  \
                                        (cur_map_index == MAP_MNTCRVN4)

#define dude_wearing_coc_robe       (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_WORN)) == PID_PURPLE_ROBE)
#define coc_disguise_check          if dude_wearing_coc_robe then begin \
                                        if (party_size > 1) then begin  \
                                            DISGUISED := 0;             \
                                        end                             \
                                        else begin                      \
                                            DISGUISED := 1;             \
                                        end                             \
                                    end

#define self_is_child 				(self_pid == PID_GIRL or self_pid == PID_BOY)

// both blocks below should be moved to command.h at some point
#define is_visible(cr)              has_trait(TRAIT_OBJECT,cr,OBJECT_VISIBILITY) // aka obj_is_visible_flag(x)
#define self_visible                is_visible(self_obj)

#define set_obj_invisible(cr)       set_obj_visibility(cr,1)
#define set_obj_visible(cr)         set_obj_visibility(cr,0)
#define set_self_invisible          set_obj_invisible(self_obj)
#define set_self_visible            set_obj_visible(self_obj)

// Merchant stuff
#define set_disable_barter          set_proto_data(self_pid, PROTO_CR_FLAGS, get_proto_data(self_pid, PROTO_CR_FLAGS) bwand bwnot(CFLG_BARTER))
#define set_enable_barter           set_proto_data(self_pid, PROTO_CR_FLAGS, get_proto_data(self_pid, PROTO_CR_FLAGS) bwor CFLG_BARTER)

variable tmp_merch_box;
variable merch_slot_1;
variable merch_slot_1_flags;
variable merch_slot_2;
variable merch_slot_2_flags;
variable merch_slot_armor;
variable merch_slot_armor_flags;
#define get_barter_inven(x)         merch_slot_1 := critter_inven_obj(self_obj, INVEN_TYPE_LEFT_HAND);  \
                                    merch_slot_2 := critter_inven_obj(self_obj, INVEN_TYPE_RIGHT_HAND); \
                                    merch_slot_armor := critter_inven_obj(self_obj,INVEN_TYPE_WORN);    \
                                    if (merch_slot_1 > 0) then                                          \
                                        merch_slot_1_flags := get_flags(merch_slot_1);                  \
                                    if (merch_slot_2 > 0) then                                          \
                                        merch_slot_2_flags := get_flags(merch_slot_2);                  \
                                    if (merch_slot_armor > 0) then                                      \
                                        merch_slot_armor_flags := get_flags(merch_slot_armor);          \
                                    tmp_merch_box := create_object(PID_CONTAINER_WOOD_CRATE, 0, 0);     \
                                    move_obj_inven_to_obj(self_obj, tmp_merch_box);                     \
                                    /* This is just for the visuals in dialog interface */              \
                                    if (merch_slot_2 > 0) then                                          \
                                        wield_obj(merch_slot_2);                                        \
                                    /* Move the barter inventory to merchant */                         \
                                    move_obj_inven_to_obj(x, self_obj)

#define put_barter_inven(x)         /* Move the barter inventory back into the trade box */             \
                                    move_obj_inven_to_obj(self_obj, x);                                 \
                                    /* Now give his inventory back and get rid of the temp box */       \
                                    move_obj_inven_to_obj(tmp_merch_box, self_obj);                     \
                                    /* Wield all items as before */                                     \
                                    if (merch_slot_1 > 0) then                                          \
                                        set_flags(merch_slot_1, merch_slot_1_flags);                    \
                                    if (merch_slot_2 > 0) then                                          \
                                        set_flags(merch_slot_2, merch_slot_2_flags);                    \
                                    if (merch_slot_armor > 0) then                                      \
                                        set_flags(merch_slot_armor, merch_slot_armor_flags);            \
                                    destroy_object(tmp_merch_box)

/*********************************************************
                        THE END
*********************************************************/

#endif // FO1_H
