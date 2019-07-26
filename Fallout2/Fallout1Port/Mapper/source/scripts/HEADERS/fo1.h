/*

	Generic Fo1 defines

*/

#include "debug.h"

//==============================================================
// Generic:
#define set_story_finished 		 		set_global_var(GAME_CONTINUES,100); \
										if (dude_is_male) then \
											play_gmovie(WALKM_MOVIE); \
										else \
											play_gmovie(WALKW_MOVIE); \
										endgame_movie; \
										gfade_out(1); \
										world_map; \
										gfade_in(1)
										
#define is_story_finished				(global_var(GAME_CONTINUES) > 0)

//==============================================================
// Settings:
#define fo1in2_fluff_enc_disabled 		(global_var(GVAR_DISABLE_FLUFF_ENCOUNTER) > 0)

//==============================================================
// Pick dead body type:
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

//==============================================================
// Water Timer related:
#define get_days_passed					(GAME_TIME_IN_DAYS - global_var(VAULT13_WATER_DAYS_COUNTER) / (GAME_TIME_SUBSECOND_RESOLUTION * 60 * 60 * 24))
#define get_water_days_left 			(global_var(VAULT13_WATER_DAYS_LEFT) - get_days_passed)

//==============================================================
// Invasion related:

#define hub_invaded							(global_var(THE_HUB_WAS_INVADED) == 1)
#define bos_invaded							(global_var(BROTHERHOOD_WAS_INVADED) == 1)
#define boneyard_invaded					(global_var(FOLLOWERS_INVADED) == 1)
#define necropolis_invaded 					(global_var(NECROPOLIS_WAS_INVADED) == 1)
#define shady_invaded 						(global_var(SHADY_SANDS_WAS_INVADED) == 1)
#define junktown_invaded 					(global_var(JUNKTOWN_WAS_INVADED) == 1)

#define check_invasion		if (global_var(MASTER_BLOWN) == 0) then begin \
								if (global_var(NECROPOLIS_INVADED_DATE) <= (game_time / (10 * 60 * 60 * 24))) then begin \
									set_global_var(NECROPOLIS_WAS_INVADED, 1); \
								end \
								if (global_var(THE_HUB_INVADED_DATE) <= (game_time / (10 * 60 * 60 * 24))) then begin \
									set_global_var(THE_HUB_WAS_INVADED, 1); \
								end \
								if (global_var(BROTHERHOOD_INVADED_DATE) <= (game_time / (10 * 60 * 60 * 24))) then begin \
									set_global_var(BROTHERHOOD_WAS_INVADED, 1); \
									set_global_var(MARK_BROTHER_2, 0); \
									set_global_var(MARK_BROTHER_3, 0); \
									set_global_var(MARK_BROTHER_4, 0); \
									set_global_var(MARK_BROTHER_5, 0); \
								end \
								if (global_var(JUNKTOWN_INVADED_DATE) <= (game_time / (10 * 60 * 60 * 24))) then begin \
									set_global_var(JUNKTOWN_WAS_INVADED, 1); \
								end \
								if (global_var(SHADY_SANDS_INVADED_DATE) <= (game_time / (10 * 60 * 60 * 24))) then begin \
									set_global_var(SHADY_SANDS_WAS_INVADED, 1); \
								end \
								if (global_var(VAULT_13_INVADED_DATE) <= (game_time / (10 * 60 * 60 * 24))) then begin \
									set_global_var(VAULT_13_WAS_INVADED, 1); \
									play_gmovie(OVERRUN_MOVIE); /*//------ Vault 13 is invaded by mutants and killed. You lose. -- was 7 before*/  \
									signal_end_game; \
								end \
								if (global_var(FOLLOWERS_INVADED_DATE) <= (game_time / (10 * 60 * 60 * 24))) then begin \
									set_global_var(FOLLOWERS_INVADED, 1); \
								end \
							end

//==============================================================
// Party related:
// TODO: Replace with Fo2 party management!

#define set_remove_party 		if (global_var(IAN_HIRELING_STATUS) == 2) then begin \
									set_global_var(IAN_HIRELING_STATUS, 2); \
								end \
								if (global_var(DOGMEAT_HIRELING_STATUS)) then begin \
									set_global_var(DOGMEAT_HIRELING_STATUS, 1); \
								end \
								if (global_var(TYCHO_HIRELING_STATUS) == 2) then begin \
									set_global_var(TYCHO_HIRELING_STATUS, 2); \
								end \
								if (global_var(KATJA_HIRELING_STATUS) == 2) then begin \
									set_global_var(KATJA_HIRELING_STATUS, 2); \
								end \
								if (global_var(TANDI_HIRELING_STATUS) == 5) then begin \
								end

#define set_add_party			if global_var(TANDI_HIRELING_STATUS) == 5 then begin \
									if Tandi_ptr != 0 then begin \
										critter_add_trait(Tandi_ptr, 1, 6, 0); \
										party_add(Tandi_ptr); \
									end \
								end \
								if global_var(IAN_HIRELING_STATUS) == 2 then begin \
									if Ian_ptr != 0 then begin \
										critter_add_trait(Ian_ptr, 1, 6, 0); \
										party_add(Ian_ptr); \
									end \
								end \
								if global_var(DOGMEAT_HIRELING_STATUS) then begin \
									if Dog_ptr != 0 then begin \
										critter_add_trait(Dog_ptr, 1, 6, 0); \
										party_add(Dog_ptr); \
									end \
								end \
								if global_var(TYCHO_HIRELING_STATUS) == 2 then begin \
									if Tycho_ptr != 0 then begin \
										critter_add_trait(Tycho_ptr, 1, 6, 0); \
										party_add(Tycho_ptr); \
									end \
								end \
								if global_var(KATJA_HIRELING_STATUS) == 2 then begin \
									if Katja_ptr != 0 then begin \
										critter_add_trait(Katja_ptr, 1, 6, 0); \
										party_add(Katja_ptr); \
									end \
								end

#define set_update_party 		if party_elevation != elevation(dude_obj) then begin \
									party_elevation := elevation(dude_obj); \
									if global_var(IAN_HIRELING_STATUS) == 2 then begin \
										if Ian_ptr != 0 then begin \
											move_to(Ian_ptr, tile_num_in_direction(tile_num(dude_obj), 1, 2), elevation(dude_obj)); \
										end \
									end \
									if global_var(DOGMEAT_HIRELING_STATUS) then begin \
										if Dog_ptr != 0 then begin \
											move_to(Dog_ptr, tile_num_in_direction(tile_num(dude_obj), 0, 1), elevation(dude_obj)); \
										end \
									end \
									if global_var(TYCHO_HIRELING_STATUS) == 2 then begin \
										if Tycho_ptr != 0 then begin \
											move_to(Tycho_ptr, tile_num_in_direction(tile_num(dude_obj), 3, 2), elevation(dude_obj)); \
										end \
									end \
									if global_var(KATJA_HIRELING_STATUS) == 2 then begin \
										if Katja_ptr != 0 then begin \
											move_to(Katja_ptr, tile_num_in_direction(tile_num(dude_obj), 3, 1), elevation(dude_obj)); \
										end \
									end \
									if global_var(TANDI_HIRELING_STATUS) == 5 then begin \
										if Tandi_ptr != 0 then begin \
											move_to(Tandi_ptr, tile_num_in_direction(tile_num(dude_obj), 4, 1), elevation(dude_obj)); \
										end \
									end \
								end

								
//==============================================================
// Party member map commentary


//==============================================================
// Quests
#define necropolis_wpump_fixed				(global_var(NECROP_WATER_PUMP_FIXED) == 2)
#define followers_trained 					(global_var(SLIDE_TRAIN_FOLLOWERS) == 1)

#define get_raiders_alive 					global_var(TOTAL_RAIDERS)

#define is_tandi_alive 						(global_var(TANDI_HIRELING_STATUS) < 3) 
#define is_aradesh_alive 					(global_var(ARADESH_STATUS) == 0) 
#define is_killian_alive 					(global_var(KILLIAN_DEAD) == 0) 
#define is_gizmo_alive 						(global_var(GIZMO_DEAD) == 0) 
#define is_rhombus_alive 					(global_var(RHOMBUS_STATUS) == 0)
#define is_garl_alive 					 	(global_var(GARL_DEAD) == 0)

//==============================================================
// Endgame slideshow
#define set_end_Master 						set_global_var(GVAR_ENDGAME_MOVIE_MUTANTS,1)
#define set_end_Vats 						set_global_var(GVAR_ENDGAME_MOVIE_MUTANTS,2)

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
