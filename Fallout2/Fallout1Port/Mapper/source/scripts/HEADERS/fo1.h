/*

	Generic Fo1 defines

*/

#include "debug.h"

/*********************************************************
	General stats stuff. Moved here because of Wipe.
*********************************************************/
// Trait defines //
#define TRAIT_PERK  (0)
#define TRAIT_OBJECT (1)
#define TRAIT_TRAIT  (2)

/*********************************************************
	Generic:
	Note: If the player decides to continue after finishing the game,
	He will be moved to a new random position on the worldmap.
*********************************************************/
#define set_story_finished				set_world_map_pos(random(780,990),random(130,260));	\
										set_global_var(GAME_CONTINUES,100); 				\
										if (dude_is_male) then 								\
											play_gmovie(WALKM_MOVIE); 						\
										else 												\
											play_gmovie(WALKW_MOVIE); 						\
										endgame_movie; 										\
										gfade_out(1);										\
										party_member_unhide_all								\
										/*world_map;*/load_map(MAP_RNDDESER,0);				\
										gfade_in(1)
										
#define is_story_finished				(global_var(GAME_CONTINUES) > 0)

#define military_base_destoryed 		(global_var(VATS_BLOWN_CUTSCENE_DONE) > 0)
#define cathedral_destroyed 			(global_var(MASTER_BLOWN_CUTSCENE) > 0)

// Send NPCs from "day" to "night" position:
#define sleeping 	/*debug("sleeping tile: " + sleep_tile + " and home tile: " + home_tile);*/ \
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

#define dude_is_animal_friend 			(has_trait(TRAIT_PERK, dude_obj, PERK_animal_friend) == 1)

#define dude_look_at_critter			anim(dude_obj, 1000, rotation_to_tile(tile_num(dude_obj), tile_num(self_obj)))
#define self_look_at_dude 				anim(self_obj, 1000, rotation_to_tile(tile_num(self_obj), tile_num(dude_obj)))

#define map_cow_can_push 			((cur_map_index != MAP_DESCRVN1) and 	\
									(cur_map_index != MAP_DESCRVN2) and  	\
									(cur_map_index != MAP_MNTCRVN1) and  	\
									(cur_map_index != MAP_MNTCRVN2) and  	\
									(cur_map_index != MAP_MNTCRVN3) and  	\
									(cur_map_index != MAP_DESCRVN4) and  	\
									(cur_map_index != MAP_MNTCRVN4) and 	\
									(cur_map_index != MAP_DESERT1))
									
#define map_is_caravan_escort 		(cur_map_index == MAP_DESCRVN1) or		\
									(cur_map_index == MAP_DESCRVN2) or		\
									(cur_map_index == MAP_DESCRVN3) or		\
									(cur_map_index == MAP_DESCRVN4) or		\
									(cur_map_index == MAP_MNTCRVN1) or		\
									(cur_map_index == MAP_MNTCRVN2) or		\
									(cur_map_index == MAP_MNTCRVN3) or		\
									(cur_map_index == MAP_MNTCRVN4)
									
#define dude_wearing_coc_robe	    (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_WORN)) == PID_PURPLE_ROBE)
#define coc_disguise_check 			if dude_wearing_coc_robe then begin \
										if (party_size > 1) then begin	\
											DISGUISED := 0;				\
										end								\
										else begin						\
											DISGUISED := 1;				\
										end								\
									end

#define obj_invisible(x)			set_obj_visibility(x,1)
#define obj_visible(x)				set_obj_visibility(x,0)
#define set_self_obj_invisible		obj_invisible(self_obj)
#define set_self_obj_visible		obj_visible(self_obj)
#define is_visible(x)				(obj_is_visible_flag(x))
#define is_self_visible				(obj_is_visible_flag(self_obj))
#define is_map(x)					(cur_map_index == x)
			

/*********************************************************
	Settings:
*********************************************************/
#define fo1in2_fluff_enc_disabled 		((global_var(GVAR_DISABLE_FLUFF_ENCOUNTER) > 0) or get_car_from_worldmap)
#define fo1in2_armor_change_disabled 	(global_var(GVAR_ALLOW_PARTY_ARMOR_CHANGE) == 0)
#define fo1in2_auto_doors_closing 		(global_var(GVAR_AUTO_DOORS_CLOSING) > 0)
#define fo1in2_motorcycle_disabled 		(global_var(GVAR_ENABLE_MOTORCYCLE) == 0)

/*********************************************************
	Pick dead body type:
*********************************************************/
#define pick_dead_body_type 			variable LVar0 := 0; \
										LVar0 := (random(0, 6) + random(0, 6) + random(0, 6)); \
										if (LVar0 <= 5) then begin/*// 31.5%*/ \
											DeathType := 57;/*//		burnt, face down  [FLAMER]*/ \
										end \
										else if (LVar0 <= 10) then begin/*// 26%*/ \
											DeathType := 56;/*//		cut in half  [LASER RIFLE, GATLING LASER]*/ \
										end \
										else if (LVar0 <= 14) then begin/*// 21%*/ \
											DeathType := 53;/*//		head & arm gone - full auto  [MINIGUN]*/ \
										end \
										else if (LVar0 <= 16) then begin/*// 10.5%*/ \
											DeathType := 63;/*//		face down, blood pool  (generic death, no weapon associated)*/ \
										end \
										else begin/*// <--------------------	16%*/ \
											variable LVar1 := 0; \
											LVar1 := random(0, 2); \
											if (LVar1 == 0) then begin \
												DeathType := 54;/*// bullet holes - full auto partial hit*/ \
											end \
											else if (LVar1 == 1) then begin \
												DeathType := 59;/*// exploded  [ROCKET LAUNCHER]*/ \
											end \
											else if (LVar1 == 2) then begin \
												DeathType := 60;/*// melted pile  [PLASMA RIFLE]*/ \
											end \
										end

/*********************************************************
	Water Chip related:
*********************************************************/
#define get_days_passed					(GAME_TIME_IN_DAYS - global_var(VAULT13_WATER_DAYS_COUNTER) / (GAME_TIME_SUBSECOND_RESOLUTION * 60 * 60 * 24))
#define get_water_days_left 			(global_var(VAULT13_WATER_DAYS_LEFT) - get_days_passed)


/*********************************************************
	Invasion related:
*********************************************************/
#define v13_invaded 						(global_var(GVAR_VAULT_13_WAS_INVADED) == 1)
#define hub_invaded							(global_var(GVAR_THE_HUB_WAS_INVADED) == 1)
#define bos_invaded							(global_var(GVAR_BROTHERHOOD_WAS_INVADED) == 1)
#define boneyard_invaded					(global_var(GVAR_FOLLOWERS_INVADED) == 1)
#define necropolis_invaded 					(global_var(GVAR_NECROPOLIS_WAS_INVADED) == 1)
#define shady_invaded 						(global_var(GVAR_SHADY_SANDS_WAS_INVADED) == 1)
#define junktown_invaded 					(global_var(GVAR_JUNKTOWN_WAS_INVADED) == 1)

#define v13_invasion_date 					(get_days_passed + (ONE_GAME_DAY * GVAR_VAULT_13_INVADED_DATE))
#define get_v13_days_left 					(global_var(GVAR_VAULT_13_INVADED_DATE) - get_days_passed)
#define set_v13_days_left(x)				set_global_var(GVAR_VAULT_13_INVADED_DATE, (get_v13_days_left + x))

#define hub_invasion_date 					(get_days_passed + (ONE_GAME_DAY * GVAR_THE_HUB_INVADED_DATE))
#define get_hub_days_left 					(global_var(GVAR_THE_HUB_INVADED_DATE) - get_days_passed)

#define bos_invasion_date 					(get_days_passed + (ONE_GAME_DAY * GVAR_BROTHERHOOD_INVADED_DATE))
#define get_bos_days_left 					(global_var(GVAR_BROTHERHOOD_INVADED_DATE) - get_days_passed)

#define boneyard_invasion_date 				(get_days_passed + (ONE_GAME_DAY * GVAR_FOLLOWERS_INVADED_DATE))
#define get_boneyard_days_left 				(global_var(GVAR_FOLLOWERS_INVADED_DATE) - get_days_passed)

#define necropolis_invasion_date 			(get_days_passed + (ONE_GAME_DAY * GVAR_NECROPOLIS_INVADED_DATE))
#define get_necropolis_days_left 			(global_var(GVAR_NECROPOLIS_INVADED_DATE) - get_days_passed)

#define shady_invasion_date 				(get_days_passed + (ONE_GAME_DAY * GVAR_SHADY_SANDS_INVADED_DATE))
#define get_shady_days_left 				(global_var(GVAR_SHADY_SANDS_INVADED_DATE) - get_days_passed)

#define junktown_invasion_date 				(get_days_passed + (ONE_GAME_DAY * GVAR_JUNKTOWN_INVADED_DATE))
#define get_junktown_days_left 				(global_var(GVAR_JUNKTOWN_INVADED_DATE) - get_days_passed)


/*********************************************************
	Party related:
*********************************************************/
#define unlimited_party_members 		global_var(GVAR_UNLIMITED_PARTY_MEMBERS) == 1


/*********************************************************
	Quests:
*********************************************************/
#define necropolis_wpump_fixed				(global_var(NECROP_WATER_PUMP_FIXED) == 2)
#define followers_trained 					(global_var(SLIDE_TRAIN_FOLLOWERS) == 1)

#define get_raiders_alive 					global_var(TOTAL_RAIDERS)

#define is_tandi_alive 						(global_var(TANDI_HIRELING_STATUS) < 3) 
#define is_aradesh_alive 					(global_var(ARADESH_STATUS) == 0) 
#define is_killian_alive 					(global_var(KILLIAN_DEAD) == 0) 
#define is_gizmo_alive 						(global_var(GIZMO_DEAD) == 0) 
#define is_rhombus_alive 					(global_var(RHOMBUS_STATUS) == 0)
#define is_garl_alive 					 	(global_var(GARL_DEAD) == 0)


/*********************************************************
	Endgame slideshow
*********************************************************/
#define set_end_Vats 						set_global_var(GVAR_ENDGAME_MOVIE_MUTANTS,1)
#define set_end_Master 						set_global_var(GVAR_ENDGAME_MOVIE_MUTANTS,2)

#define set_end_necropolis_dehydrated 		set_global_var(GVAR_ENDGAME_MOVIE_NECROPOLIS,1)
#define set_end_necropolis_survived 		set_global_var(GVAR_ENDGAME_MOVIE_NECROPOLIS,2)
#define set_end_necropolis_invaded			set_global_var(GVAR_ENDGAME_MOVIE_NECROPOLIS,3)

#define set_end_foa_trained 				set_global_var(GVAR_ENDGAME_MOVIE_BONEYARD,1)
#define set_end_foa_invaded 				set_global_var(GVAR_ENDGAME_MOVIE_BONEYARD,2)

#define set_end_shady_good					set_global_var(GVAR_ENDGAME_MOVIE_SHADY,1)
#define set_end_shady_tandi_dead			set_global_var(GVAR_ENDGAME_MOVIE_SHADY,2)
#define set_end_shady_aradesh_dead			set_global_var(GVAR_ENDGAME_MOVIE_SHADY,3)
#define set_end_shady_bad					set_global_var(GVAR_ENDGAME_MOVIE_SHADY,4)
#define set_end_shady_invaded				set_global_var(GVAR_ENDGAME_MOVIE_SHADY,5)

#define set_end_junktown_killian			set_global_var(GVAR_ENDGAME_MOVIE_JUNKTOWN,1)
#define set_end_junktown_gizmo				set_global_var(GVAR_ENDGAME_MOVIE_JUNKTOWN,2)
#define set_end_junktown_invaded			set_global_var(GVAR_ENDGAME_MOVIE_JUNKTOWN,3)

#define set_end_bos_good					set_global_var(GVAR_ENDGAME_MOVIE_BOS,1)
#define set_end_bos_bad						set_global_var(GVAR_ENDGAME_MOVIE_BOS,2)
#define set_end_bos_invaded					set_global_var(GVAR_ENDGAME_MOVIE_BOS,3)

#define set_end_hub_good					set_global_var(GVAR_ENDGAME_MOVIE_HUB,1)
#define set_end_hub_bad						set_global_var(GVAR_ENDGAME_MOVIE_HUB,2)

#define set_end_raiders_dead				set_global_var(GVAR_ENDGAME_MOVIE_KHANS,1)
#define set_end_raiders_hurt				set_global_var(GVAR_ENDGAME_MOVIE_KHANS,2)
#define set_end_raiders_alive				set_global_var(GVAR_ENDGAME_MOVIE_KHANS,3)

#define set_end_ending_vd 					set_global_var(GVAR_ENDGAME_MOVIE_VD,1)
