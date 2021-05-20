#pragma once

#define TOWN_REPUTATION                 global_var(TOWN_REP_VAR)

/* This set of procedures will find out what the reaction level is. Additionally,
it will find out what the reaction level is in terms of Good, Neutral, or Bad.
It will also write in how to modify the reaction level by a level. */

#define NO_REACTION                     (0)
#define BAD                             (1)
#define NEUTRAL                         (2)
#define GOOD                            (3)

// Fo1 was 0 to 100, in Fo2 it is -100 to 100, so we are trying to adapt
#define LOW_REACTION                    (-50)   // Fo1: (25)
#define BASE_REACTION                   (0)     // Fo1: (50)
#define HIGH_REACTION                   (50)    // Fo1: (75)

#define MIN_REACTION                    (-100)  // Fo1: (0)
#define MAX_REACTION                    (100)   // Fo1: (100)

#define NORMAL_BOOST                    (20)    // Fo1: (10)
#define HUGE_BOOST                      (50)    // Fo1: (25)

#define REACTION_BONUS_BERSERKER        (40)    // Fo1: (20)
#define REACTION_BONUS_CHAMPION         (40)    // Fo1: (20)
#define REACTION_BONUS_CHILDKILLER      (60)    // Fo1: (30)

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
#define reaction_level                  local_var(LVAR_reaction_level)
#define horrible_critter_reaction       (local_var(LVAR_reaction_level) <= NO_REACTION)
#define bad_critter_reaction            (local_var(LVAR_reaction_level) <= BAD)
#define neutral_critter_reaction        (local_var(LVAR_reaction_level) == NEUTRAL)
#define good_critter_reaction           (local_var(LVAR_reaction_level) >= GOOD)


#define get_reaction    if (local_var(LVAR_got_reaction) == 0) then begin  \
                           set_local_var(LVAR_reaction, BASE_REACTION);    \
                           set_local_var(LVAR_reaction_level, NEUTRAL);    \
                           set_local_var(LVAR_got_reaction, 1);            \
                                                  /* We double the reaction check, because -100 to 100 instead of 0 to 100! */      \
                           set_local_var(LVAR_reaction, local_var(LVAR_reaction) + (2 * ((5 * dude_charisma) - 25)));               \
                           set_local_var(LVAR_reaction, local_var(LVAR_reaction) + (2 * (10 * dude_perk(PERK_presence))));          \
                           if dude_perk(PERK_karma_beacon_perk) then begin /* Added support for Fo2 perk */                         \
                              set_local_var(LVAR_reaction, local_var(LVAR_reaction) * 2);                                           \
                           end                                                                                                      \
                           if dude_perk(PERK_cult_of_personality) then begin                                                        \
                              if (global_var(GVAR_PLAYER_REPUTATION) > 0) then begin                                                \
                                 set_local_var(LVAR_reaction, local_var(LVAR_reaction) + (2 * global_var(GVAR_PLAYER_REPUTATION))); \
                              end                                                                                                   \
                              else begin                                                                                            \
                                 set_local_var(LVAR_reaction, local_var(LVAR_reaction) - (2 * global_var(GVAR_PLAYER_REPUTATION))); \
                              end                                                                                                   \
                           end                                                                                                      \
                           else if (local_var(LVAR_base_reaction) == 1) then begin                                                  \
                              set_local_var(LVAR_reaction, local_var(LVAR_reaction) - (2 * global_var(GVAR_PLAYER_REPUTATION)));    \
                           end                                                                                                      \
                           else begin                                                                                               \
                              set_local_var(LVAR_reaction, local_var(LVAR_reaction) + (2 * global_var(GVAR_PLAYER_REPUTATION)));    \
                           end                                                                                                      \
                           if has_rep_childkiller then begin                                                         \
                              set_local_var(LVAR_reaction, local_var(LVAR_reaction) - REACTION_BONUS_CHILDKILLER);   \
                           end                                                                                       \
                           if has_rep_champion then begin                                                            \
                              set_local_var(LVAR_reaction, local_var(LVAR_reaction) + REACTION_BONUS_CHAMPION);      \
                           end                                                                                       \
                           if has_rep_berserker then begin                                                           \
                              set_local_var(LVAR_reaction, local_var(LVAR_reaction) - REACTION_BONUS_BERSERKER);     \
                           end                                                                                       \
                           ReactToLevel                                                                              \
                        end

#define ReactToLevel    if (local_var(LVAR_reaction) <= LOW_REACTION) then begin    \
                           set_local_var(LVAR_reaction_level, BAD);                 \
                        end                                                         \
                        else                                                        \
                        if (local_var(LVAR_reaction) <= HIGH_REACTION) then begin   \
                           set_local_var(LVAR_reaction_level, NEUTRAL);             \
                        end                                                         \
                        else begin                                                  \
                           set_local_var(LVAR_reaction_level, GOOD);                \
                        end


#define LevelToReact    if (local_var(LVAR_reaction_level) == BAD) then begin       \
                           /*set_local_var(LVAR_reaction, random(1, 25));*/         \
                           set_local_var(LVAR_reaction, random(-99, -50));          \
                        end                                                         \
                        else                                                        \
                        if (local_var(LVAR_reaction_level) == NEUTRAL) then begin   \
                           /*set_local_var(LVAR_reaction, random(26, 75));*/        \
                           set_local_var(LVAR_reaction, random(-49, 50));           \
                        end                                                         \
                        else begin                                                  \
                           /*set_local_var(LVAR_reaction, random(76, 100));*/       \
                           set_local_var(LVAR_reaction, random(51, 100));           \
                        end


#define UpReact      set_local_var(LVAR_reaction, local_var(LVAR_reaction) + NORMAL_BOOST); \
                     ReactToLevel


#define DownReact    set_local_var(LVAR_reaction, local_var(LVAR_reaction) - NORMAL_BOOST); \
                     ReactToLevel


#define BottomReact  set_local_var(LVAR_reaction_level, BAD); \
                     set_local_var(LVAR_reaction, MIN_REACTION);

#define TopReact     set_local_var(LVAR_reaction, MAX_REACTION);   \
                     set_local_var(LVAR_reaction_level, GOOD);

#define BigUpReact   set_local_var(LVAR_reaction, local_var(LVAR_reaction) + HUGE_BOOST); \
                     ReactToLevel

#define BigDownReact set_local_var(LVAR_reaction, local_var(LVAR_reaction) - HUGE_BOOST); \
                     ReactToLevel

#define UpReactLevel set_local_var(LVAR_reaction_level, local_var(LVAR_reaction_level) + 1);    \
                     if (local_var(LVAR_reaction_level) > GOOD) then begin                      \
                        set_local_var(LVAR_reaction_level, GOOD);                               \
                     end                                                                        \
                     LevelToReact

#define DownReactLevel  set_local_var(LVAR_reaction_level, local_var(LVAR_reaction_level) - 1); \
                        if (local_var(LVAR_reaction_level) < BAD) then begin                    \
                           set_local_var(LVAR_reaction_level, BAD);                             \
                        end                                                                     \
                        LevelToReact

//variable exit_line;
//#define Goodbyes     exit_line := message_str(SCRIPT_MODREACT, random(100, 105))
#define exit_line      message_str(SCRIPT_MODREACT, random(100, 105))
