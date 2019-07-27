#ifndef MODREACT_H
#define MODREACT_H

/* This set of procedures will find out what the reaction level is. Additionally,
it will find out what the reaction level is in terms of Good, Neutral, or Bad.
It will also write in how to modify the reaction level by a level. */

#define NO_REACTION                     (0)
#define BAD                             (1)
#define NEUTRAL                         (2)
#define GOOD                            (3)

#define TINY_DROP                       (-5)
#define MINOR_DROP                      (-10)
#define MODERATE_DROP                   (-20)
#define MAJOR_DROP                      (-30)
#define HUGE_DROP                       (-50)

#define BASE_REACTION                   (50)
#define LOW_REACTION                    (25)
#define HIGH_REACTION                   (75)

#define MIN_REACTION                    (0)
#define MAX_REACTION                    (100)

variable Static_Reaction:=0;            // This adds in Reputations, Perks, Karma, and such
variable Evil_Critter:=0;               // 0 == Good Critter, 1 == Bad Critter
variable Slavery_Tolerant:=2;           // 0 == very intolerant, 1 == intolerant, 2 == tolerant, 3 == Happy
variable Karma_Perception:=0;           // see defines for values
variable reaction_bonus_town_rep:=0;
variable reaction_bonus_karma:=0;

// LOCAL VARS WHICH WILL BE SAVED FOR EACH CRITTER

#define LVAR_reaction                   (0)             // Holds reaction number value.
#define LVAR_reaction_level             (1)             // Holds reaction level: BAD, NEUTRAL, GOOD.
#define LVAR_got_reaction               (2)             // Makes sure to modify reaction only once.
#define LVAR_base_reaction              (3)

// Manipulation of Reaction Levels

// Checks the reaction_levels from a critter
#define horrible_critter_reaction       (local_var(LVAR_reaction_level) <= NO_REACTION)
#define bad_critter_reaction            (local_var(LVAR_reaction_level) <= BAD)
#define neutral_critter_reaction        (local_var(LVAR_reaction_level) == NEUTRAL)
#define good_critter_reaction           (local_var(LVAR_reaction_level) >= GOOD)


#define get_reaction  	if (local_var(LVAR_got_reaction) == 0) then begin 		\
							set_local_var(LVAR_reaction, 50); 					\
							set_local_var(LVAR_reaction_level, 2); 				\
							set_local_var(LVAR_got_reaction, 1); 				\
							set_local_var(LVAR_reaction, local_var(LVAR_reaction) + (5 * get_critter_stat(dude_obj, STAT_ch)) - 25); \
							set_local_var(LVAR_reaction, local_var(LVAR_reaction) + (10 * has_trait(TRAIT_PERK, dude_obj, PERK_presence))); \
							if (has_trait(TRAIT_PERK, dude_obj, PERK_cult_of_personality)) then begin \
								if ( global_var( GVAR_PLAYER_REPUTATION )  > 0) then begin \
									set_local_var(LVAR_reaction, local_var(LVAR_reaction) +  global_var( GVAR_PLAYER_REPUTATION ) ); \
								end \
								else begin \
									set_local_var(LVAR_reaction, local_var(LVAR_reaction) -  global_var( GVAR_PLAYER_REPUTATION ) ); \
								end \
							end \
							else \
							if (local_var(3) == 1) then begin \
								set_local_var(LVAR_reaction, local_var(LVAR_reaction) -  global_var( GVAR_PLAYER_REPUTATION ) ); \
							end \
							else begin \
								set_local_var(LVAR_reaction, local_var(LVAR_reaction) +  global_var( GVAR_PLAYER_REPUTATION ) ); \
							end \
							if ( global_var( GVAR_CHILDKILLER_REPUTATION )  >= 1) then begin \
								set_local_var(LVAR_reaction, local_var(LVAR_reaction) - 30); \
							end \
							if ((( global_var( GVAR_BAD_MONSTER )  +  global_var( GVAR_GOOD_MONSTER ) ) >= 25) and (( global_var( GVAR_BAD_MONSTER )  > (3 *  global_var( GVAR_GOOD_MONSTER ) )) or ( global_var( GVAR_CHAMPION_REPUTATION )  == 1))) then begin \
								set_local_var(LVAR_reaction, local_var(LVAR_reaction) + 20); \
							end \
							if ((( global_var( GVAR_BAD_MONSTER )  +  global_var( GVAR_GOOD_MONSTER ) ) >= 25) and (( global_var( GVAR_GOOD_MONSTER )  > (2 *  global_var( GVAR_BAD_MONSTER ) )) or ( global_var( GVAR_BERSERKER_REPUTATION )  == 1))) then begin \
								set_local_var(LVAR_reaction, local_var(LVAR_reaction) - 20); \
							end \
							ReactToLevel \
						end

#define ReactToLevel 	if (local_var(LVAR_reaction) <= 25) then begin \
							set_local_var(LVAR_reaction_level, 1); \
						end \
						else \
						if (local_var(LVAR_reaction) <= 75) then begin \
							set_local_var(LVAR_reaction_level, 2); \
						end \
						else begin \
							set_local_var(LVAR_reaction_level, 3); \
						end \


#define LevelToReact 	if (local_var(LVAR_reaction_level) == 1) then begin \
							set_local_var(LVAR_reaction, random(1, 25)); \
						end \
						else \
						if (local_var(LVAR_reaction_level) == 2) then begin \
							set_local_var(LVAR_reaction, random(26, 75)); \
						end \
						else begin \
							set_local_var(LVAR_reaction, random(76, 100)); \
						end


#define UpReact 		set_local_var(LVAR_reaction, local_var(LVAR_reaction) + 10); \
						ReactToLevel


#define DownReact 		set_local_var(LVAR_reaction, local_var(LVAR_reaction) - 10); \
						ReactToLevel


#define BottomReact 	set_local_var(LVAR_reaction_level, 1); \
						set_local_var(LVAR_reaction, 1);

#define TopReact 		set_local_var(LVAR_reaction, 100); \
						set_local_var(LVAR_reaction_level, 3);

#define BigUpReact 		set_local_var(LVAR_reaction, local_var(LVAR_reaction) + 25); \
						ReactToLevel

#define BigDownReact 	set_local_var(LVAR_reaction, local_var(LVAR_reaction) - 25); \
						ReactToLevel

#define UpReactLevel 	set_local_var(LVAR_reaction_level, local_var(LVAR_reaction_level) + 1); \
						if (local_var(LVAR_reaction_level) > 3) then begin \
							set_local_var(LVAR_reaction_level, 3); \
						end \
						LevelToReact

#define DownReactLevel 	set_local_var(LVAR_reaction_level, local_var(LVAR_reaction_level) - 1); \
						if (local_var(LVAR_reaction_level) < 1) then begin \
							set_local_var(LVAR_reaction_level, 1); \
						end \
						LevelToReact

variable exit_line;
#define Goodbyes		exit_line := message_str(SCRIPT_MODREACT, random(100, 105))
#endif // MODREACT_H
