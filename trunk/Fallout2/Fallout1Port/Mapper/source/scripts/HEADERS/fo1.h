/*

	Generic Fo1 defines
	
*/


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
									metarule(13, 0); \
								end \
								if (global_var(FOLLOWERS_INVADED_DATE) <= (game_time / (10 * 60 * 60 * 24))) then begin \
									set_global_var(FOLLOWERS_INVADED, 1); \
								end \
							end
							
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
