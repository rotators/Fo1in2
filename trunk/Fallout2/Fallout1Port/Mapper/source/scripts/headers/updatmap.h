/*
	Copyright 1998-2003 Interplay Entertainment Corp.  All rights reserved.
*/

#ifndef UPDATMAP_H
#define UPDATMAP_H

// Fallout 1 lighting:
// Lighting Information
#define BRIGHT_LIGHT                    (100)
#define CAVERN_LIGHT                    (50)
#define DUSK_LIGHT                      (40)
#define INDOOR_LIGHT                    (60)
#define BASEMENT_LIGHT                  (50)
#define MILITARY_BASE_LIGHTING          (75)

#define Lighting 	         if ((game_time_hour >= 600) and (game_time_hour < 700)) then begin 			\
      								set_light_level(game_time_hour - 600 + DUSK_LIGHT);						   \
      							end																			               \
      							else if ((game_time_hour >= 700) and (game_time_hour < 1800)) then begin   \
      								set_light_level(BRIGHT_LIGHT);											         \
      							end																			               \
      							else if ((game_time_hour >= 1800) and (game_time_hour < 1900)) then begin  \
      								set_light_level(BRIGHT_LIGHT - (game_time_hour - 1800));				      \
      							end																			               \
      							else 																		                  \
      								set_light_level(DUSK_LIGHT)

#define GlowLighting 	   if (global_var(GVAR_GLOW_POWER) == 2) then begin      \
								      set_light_level(BRIGHT_LIGHT);					      \
      							end																	\
      							else if (global_var(GVAR_GLOW_POWER) == 1) then begin \
      								Darkness;														\
      							end																	\
      							else													            \
      								set_light_level(0)						               \

#define Darkness 			   set_light_level(DUSK_LIGHT)

#define Cavern_Lighting 	set_light_level(CAVERN_LIGHT)

// Fallout 2 lighting:
/*
// Lighting Information
#define BRIGHT_LIGHT                    (100)
#define CAVERN_LIGHT                    (50)
#define DUSK_LIGHT                      (40)
#define ENCLAVE_LIGHT                   (60)
#define INDOOR_LIGHT                    (60)
#define BASEMENT_LIGHT                  (50)
#define MILITARY_BASE_LIGHTING          (75)

#define WINTER_MORNING                  (700)
#define SPRING_MORNING                  (600)
#define SUMMER_MORNING                  (500)
#define FALL_MORNING                    (600)

#define WINTER_EVENING                  (1700)
#define SPRING_EVENING                  (1800)
#define SUMMER_EVENING                  (1900)
#define FALL_EVENING                    (1800)

#define season_morning(when)            ((game_time_hour >= (when)) and (game_time_hour < (when + 100)))
#define season_day(sunrise,sunset)      ((game_time_hour >= (sunrise + 100)) and (game_time_hour < sunset))
#define season_evening(when)            ((game_time_hour >= (when)) and (game_time_hour < (when + 100)))

#define Spring_Lighting                 if (season_morning(SPRING_MORNING)) then                                \
                                            set_light_level((game_time_hour - SPRING_MORNING) + DUSK_LIGHT);    \
                                        else if (season_day(SPRING_MORNING,SPRING_EVENING)) then                \
                                            set_light_level(100);                                               \
                                        else if (season_evening(SPRING_EVENING)) then                           \
                                            set_light_level(BRIGHT_LIGHT - (game_time_hour - SPRING_EVENING));  \
                                        else                                                                    \
                                            set_light_level(DUSK_LIGHT)

#define Summer_Lighting                 if (season_morning(SUMMER_MORNING)) then                                \
                                            set_light_level((game_time_hour - SUMMER_MORNING) + DUSK_LIGHT);    \
                                        else if (season_day(SUMMER_MORNING,SUMMER_EVENING)) then                \
                                            set_light_level(100);                                               \
                                        else if (season_evening(SUMMER_EVENING)) then                           \
                                            set_light_level(BRIGHT_LIGHT - (game_time_hour - SUMMER_EVENING));  \
                                        else                                                                    \
                                            set_light_level(DUSK_LIGHT)

#define Fall_Lighting                   if (season_morning(FALL_MORNING)) then                                  \
                                            set_light_level((game_time_hour - FALL_MORNING) + DUSK_LIGHT);      \
                                        else if (season_day(FALL_MORNING,FALL_EVENING)) then                    \
                                            set_light_level(100);                                               \
                                        else if (season_evening(FALL_EVENING)) then                             \
                                            set_light_level(BRIGHT_LIGHT - (game_time_hour - FALL_EVENING));    \
                                        else                                                                    \
                                            set_light_level(DUSK_LIGHT)

#define Winter_Lighting                 if (season_morning(WINTER_MORNING)) then                                \
                                            set_light_level((game_time_hour - WINTER_MORNING) + DUSK_LIGHT);    \
                                        else if (season_day(WINTER_MORNING,WINTER_EVENING)) then                \
                                            set_light_level(100);                                               \
                                        else if (season_evening(WINTER_EVENING)) then                           \
                                            set_light_level(BRIGHT_LIGHT - (game_time_hour - WINTER_EVENING));  \
                                        else                                                                    \
                                            set_light_level(DUSK_LIGHT)

#define Lighting                        if ((get_month >= 3) and (get_month < 5)) then                          \
                                            Spring_Lighting;                                                    \
                                        else if ((get_month >= 5) and (get_month < 9)) then                     \
                                            Summer_Lighting;                                                    \
                                        else if ((get_month >= 9) and (get_month < 11)) then                    \
                                            Fall_Lighting;                                                      \
                                        else                                                                    \
                                            Winter_Lighting

#define Darkness                        set_light_level(DUSK_LIGHT)

#define Cavern_Lighting                 set_light_level(CAVERN_LIGHT)

#define Full_Light                      set_light_level(BRIGHT_LIGHT)

#define Enclave_Lighting                set_light_level(ENCLAVE_LIGHT)

#define Indoor_Lighting                 set_light_level(INDOOR_LIGHT)

#define Basement_Lighting               set_light_level(BASEMENT_LIGHT)

#define Military_Base_Lighting          set_light_level(MILITARY_BASE_LIGHTING)
*/



#define set_cur_exit                wm_area_set_pos(AREA_RND_MOUNTAIN,worldmap_xpos,worldmap_ypos)

// Car Information
#define trunk_size_small				(40)
#define trunk_size_big					(80)

#define dude_has_bike 		         (global_var(GVAR_PLAYER_GOT_CAR) == 1)
#define dude_has_upgraded_bike 	   (global_var(GVAR_PLAYER_GOT_CAR) == 2)

#define get_car_current_map 			global_var(GVAR_CAR_CUR_MAP)
#define get_car_in_cur_map 			get_car_current_map == cur_map_index
#define set_car_current_map    		set_global_var(GVAR_CAR_CUR_MAP,cur_map_index)
#define set_car_worldmap     			set_global_var(GVAR_CAR_CUR_MAP,-1)
#define get_car_from_worldmap 		(global_var(GVAR_CAR_CUR_MAP) == -1)

#define set_car_out_of_fuel 			set_global_var(GVAR_BIKE_OUT_OF_FUEL,1)
#define get_car_out_of_fuel 			(global_var(GVAR_BIKE_OUT_OF_FUEL) != 0)

#define set_car_exit_map 				if (global_var(GVAR_PLAYER_GOT_CAR) != 0) and car_in_any_encounter then begin \
													set_car_worldmap; 																			\
													car_give_to_party; 																			\
												end

#define car_in_any_encounter 	  		((car_current_town == AREA_RND_DESERT) or 			\
												(car_current_town == AREA_RND_MOUNTAIN) or  			\
												(car_current_town == AREA_RND_CITY) or  				\
												(car_current_town == AREA_RND_COAST) or 				\
												(car_current_town == AREA_RND_ENC_DESERT) or  		\
												(car_current_town == AREA_RND_ENC_MOUNTAIN) or  	\
												(car_current_town == AREA_RND_ENC_CITY) or  			\
												(car_current_town == AREA_RND_ENC_COAST) or  		\
												(car_current_town == AREA_SPECIAL_RND_FOOT) or  	\
												(car_current_town == AREA_SPECIAL_RND_TARDIS) or  	\
												(car_current_town == AREA_SPECIAL_RND_USEDCAR) or  \
												(car_current_town == AREA_SPECIAL_RND_COLATRUK) or \
												(car_current_town == AREA_SPECIAL_RND_FSAUSER) or  \
												(car_current_town == AREA_SPECIAL_RND_TALKCOW))


//        City Car is At                Tile Num For Car
#define CAR_UNCLAIMED_HEX                    (18704)         // When you don't have the car
#define CAR_UNCLAIMED_ELEV                   (1)
#define CAR_CAR_OUTTA_GAS_HEX                (19100)
#define CAR_CAR_OUTTA_GAS_ELEV               (0)

#define CAR_UPGRADE_HEX              		   (18691)

#define CAR_RND_DESERT_HEX                 	(19096)
#define CAR_RND_DESERT_ELEV                	(0)
#define CAR_RND_MOUNTAIN_HEX               	(17875)
#define CAR_RND_MOUNTAIN_ELEV                (0)
#define CAR_RND_CITY_HEX                   	(12693)
#define CAR_RND_CITY_ELEV                 	(0)
#define CAR_RND_COAST_HEX                	   (20106)
#define CAR_RND_COAST_ELEV                 	(0)

#define CAR_V13_HEX							      (25953)
#define CAR_V15_HEX							      (24712)
#define CAR_SHADY_HEX						      (10510)
#define CAR_JUNKTOWN_NORTH_HEX				   (11900)
#define CAR_JUNKTOWN_SOUTH_HEX				   (28117)
#define CAR_RAIDERS_HEX						      (27693)
#define CAR_NECROPOLIS_HOTEL_HEX 			   (24079)
#define CAR_NECROPOLIS_HALLDEAD_HEX 		   (19955)
#define CAR_NECROPOLIS_WATERSHED_HEX 		   (8937)
#define CAR_NECROPOLIS_ELEV 				      (1)
#define CAR_HUB_HEX 						         (14698)
#define CAR_BOS_HEX							      (26315)
#define CAR_MBASE_HEX						      (18334)
#define CAR_MBASE_DEAD_HEX					      (21124)
#define CAR_GLOW_HEX						         (22533)
#define CAR_BONEYARD_ADY_HEX				      (9495)
#define CAR_BONEYARD_BLADES_HEX				   (28720)
#define CAR_BONEYARD_LIBRARY_HEX			      (18125)
#define CAR_CATHEDRAL_HEX					      (21475)
#define CAR_CATHEDRAL_DEAD_HEX				   (21901)

#define CAR_RND_FOREVER_HEX                  (18904)

#define CAR_RANDOM_DESERT_HEX                (20106)
#define CAR_RANDOM_COAST_HEX                 (20106)
#define CAR_RANDOM_MOUNTAIN_HEX              (18909)

#define CAR_RND_DESERT1_HEX                  (19096)
#define CAR_RND_DESERT2_HEX                  (19094)
#define CAR_RND_DESERT3_HEX                  (18894)
#define CAR_RND_DESERT4_HEX                  (19718)
#define CAR_RND_DESERT5_HEX                  (24112)
#define CAR_RND_DESERT6_HEX                  (18914)
#define CAR_RND_DESERT7_HEX                  (24525)
#define CAR_RND_DESERT8_HEX                  (17890)
#define CAR_RND_DESERT9_HEX                  (22880)
#define CAR_RND_DESERT10_HEX                 (22880)
#define CAR_RND_DESERT11_HEX                 (20692)
#define CAR_RND_DESERT12_HEX                 (21308)
#define CAR_RND_DESERT13_HEX                 (17896)

#define CAR_RND_MOUNTAIN1_HEX                (17875)
#define CAR_RND_MOUNTAIN2_HEX                (17876)
#define CAR_RND_MOUNTAIN3_HEX                (19478)
#define CAR_RND_MOUNTAIN4_HEX                (19099)
#define CAR_RND_MOUNTAIN5_HEX                (20678)
#define CAR_RND_MOUNTAIN6_HEX                (20073)

#define CAR_RND_CAVE1_HEX                    (26508)
#define CAR_RND_CAVE2_HEX                    (24706)
#define CAR_RND_CAVE3_HEX                    (24915)
#define CAR_RND_CAVE4_HEX                    (27512)
#define CAR_RND_CAVE5_HEX                    (26292)
#define CAR_RND_CAVE6_HEX                    (21681)
#define CAR_RND_CAVE7_HEX                    (19078)

#define CAR_RND_CITY1_HEX                    (12693)
#define CAR_RND_CITY2_HEX                    (9898)
#define CAR_RND_CITY3_HEX                    (23542)
#define CAR_RND_CITY4_HEX                    (28089)
#define CAR_RND_CITY5_HEX                    (20464)
#define CAR_RND_CITY6_HEX                    (29496)
#define CAR_RND_CITY7_HEX                    (19535)
#define CAR_RND_CITY8_HEX                    (21702)

#define CAR_RND_COAST1_HEX                   (18086)
#define CAR_RND_COAST2_HEX                   (19089)
#define CAR_RND_COAST3_HEX                   (19279)
#define CAR_RND_COAST4_HEX                   (19278)
#define CAR_RND_COAST5_HEX                   (23500)
#define CAR_RND_COAST6_HEX                   (22291)
#define CAR_RND_COAST7_HEX                   (16518)
#define CAR_RND_COAST8_HEX                   (23718)
#define CAR_RND_COAST9_HEX                   (21107)
#define CAR_RND_COAST10_HEX                  (17919)
#define CAR_RND_COAST11_HEX                  (20079)
#define CAR_RND_COAST12_HEX                  (25515)

#endif // UPDATMAP_H
