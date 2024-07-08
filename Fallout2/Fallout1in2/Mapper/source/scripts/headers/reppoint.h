/*
   Copyright 1998-2003 Interplay Entertainment Corp.  All rights reserved.
*/

#pragma once

/*********************************************************
 Here is all of the reputation defines for the game
*********************************************************/


/*-----------------9/16/97 7:41:M-------------------
 General format for this file is:

 I. General reputations and modifiers which need to be read by scripts and the
        engine
    A. Increase and decrease general reputation
    B. Add/remove champion/berserker reputation
    C. Increment good/evil kill counter

 II. Reputation for Enemy of Towns

 III. Reputation for Champion of Towns

 IV. Reputaion for completing seeds
--------------------------------------------------*/


/*********************************************************
 General Reputation
*********************************************************/
// macros for general town status
// good
#define town_rep_is_idolized                       (global_var(TOWN_REP_VAR) >= 30)
#define town_rep_is_liked                          (global_var(TOWN_REP_VAR) >= 15)
#define town_rep_is_accepted                       (global_var(TOWN_REP_VAR) >= 1)
// neutral
#define town_rep_is_neutral                        (global_var(TOWN_REP_VAR) == 0)
// bad
#define town_rep_is_antipaty                       (global_var(TOWN_REP_VAR) <= -1)
#define town_rep_is_hated                          (global_var(TOWN_REP_VAR) <= -15)
#define town_rep_is_vilified                       (global_var(TOWN_REP_VAR) <= -30)

#define REP_BONUS_KILLED_GOOD_CRITTER       (-2)   // Fo2: -10
#define REP_BONUS_KILLED_CHILD              (-4)   // Fo2: -15
#define REP_BONUS_KILLED_EVIL_CRITTER       (1)    // Fo2: 5
#define REP_BONUS_KILLED_NEUTRAL_CRITTER    (0)    // Fo2: 0

// General Town Rep
#define REP_TOWN_KILL_GOOD                      (-5)  // Fo2: -5
#define REP_TOWN_KILL_CHILD                     (-8)  // Fo2: -8
#define REP_TOWN_KILL_EVIL                      (2)   // Fo2: 2

#define inc_general_rep(x)      set_global_var(GVAR_PLAYER_REPUTATION, (global_var(GVAR_PLAYER_REPUTATION) + x));               \
                                debug_msg("Player gains "+x+" Karma Points.");                                                  \
                                CheckKarma

#define dec_general_rep(x)      set_global_var(GVAR_PLAYER_REPUTATION, (global_var(GVAR_PLAYER_REPUTATION) - x));               \
                                CheckKarma

#define check_general_rep       global_var(GVAR_PLAYER_REPUTATION)


#ifdef TOWN_REP_VAR
#define inc_childkiller         if (source_obj == dude_obj) then begin                                                               \
                                    remove_champion;                                                                                 \
                                    set_global_var(GVAR_CHILDKILLER_REPUTATION, (global_var(GVAR_CHILDKILLER_REPUTATION) +1));       \
                                    inc_general_rep(REP_BONUS_KILLED_CHILD);                                                         \
                                    set_global_var(TOWN_REP_VAR,(global_var(TOWN_REP_VAR)+REP_TOWN_KILL_CHILD));                     \
                                    debug_msg("Added "+REP_TOWN_KILL_CHILD+" to Town Rep");                                          \
                                end
#else
#define inc_childkiller         if (source_obj == dude_obj) then begin                                                               \
                                    remove_champion;                                                                                 \
                                    set_global_var(GVAR_CHILDKILLER_REPUTATION, (global_var(GVAR_CHILDKILLER_REPUTATION) +1));       \
                                    inc_general_rep(REP_BONUS_KILLED_CHILD);                                                         \
                                end
#endif

/*-----------------9/16/97 7:40:M-------------------
 The following check to see if the player has the particular reputations as per design
--------------------------------------------------*/

/* Karma Levels */
#define KARMA_HOLY_WARRIOR                  (1000)
#define KARMA_GUARDIAN_OF_THE_WASTES        (750)
#define KARMA_SHIELD_OF_HOPE                (500)
#define KARMA_DEFENDER                      (250)
#define KARMA_WANDERER                      (0)
#define KARMA_BETRAYER                      (-250)
#define KARMA_SWORD_OF_DESPAIR              (-500)
#define KARMA_SCOURGE_OF_THE_WASTES         (-750)
#define KARMA_DEMON_SPAWN                   (-1000)

/* Reputation Checks */
#define has_rep_childkiller     (global_var(GVAR_CHILDKILLER_REPUTATION) >= 2)

#define has_rep_champion        (((global_var(GVAR_BAD_MONSTER) + global_var(GVAR_GOOD_MONSTER)) >= 25) and                          \
                                ((global_var(GVAR_BAD_MONSTER) > (3 * global_var(GVAR_GOOD_MONSTER))) or                             \
                                (global_var(GVAR_CHAMPION_REPUTATION) == 1)) and (global_var(GVAR_CHILDKILLER_REPUTATION) == 0))

#define has_rep_berserker       (((global_var(GVAR_BAD_MONSTER) + global_var(GVAR_GOOD_MONSTER)) >= 25) and \
                                ((global_var(GVAR_GOOD_MONSTER) > (2 * global_var(GVAR_BAD_MONSTER))) or    \
                                (global_var(GVAR_BERSERKER_REPUTATION) == 1)))

#define has_rep_slaver          (global_var(GVAR_REPUTATION_SLAVER) == 1)

#define has_rep_slave_owner     (global_var(GVAR_REPUTATION_SLAVE_OWNER) == 1)

#define ClearReps               set_global_var(GVAR_KARMA_HOLY_WARRIOR,0);                                      \
                                set_global_var(GVAR_KARMA_GUARDIAN_OF_THE_WASTES,0);                            \
                                set_global_var(GVAR_KARMA_SHIELD_OF_HOPE,0);                                    \
                                set_global_var(GVAR_KARMA_DEFENDER,0);                                          \
                                set_global_var(GVAR_KARMA_WANDERER,0);                                          \
                                set_global_var(GVAR_KARMA_BETRAYER,0);                                          \
                                set_global_var(GVAR_KARMA_SWORD_OF_DESPAIR,0);                                  \
                                set_global_var(GVAR_KARMA_SCOURGE_OF_THE_WASTES,0);                              \
                                set_global_var(GVAR_KARMA_DEMON_SPAWN,0)

#define CheckKarma              ClearReps;                                                                      \
                                if (check_general_rep >= KARMA_HOLY_WARRIOR) then                               \
                                    set_global_var(GVAR_KARMA_HOLY_WARRIOR,1);                                  \
                                else if (check_general_rep >= KARMA_GUARDIAN_OF_THE_WASTES) then                \
                                    set_global_var(GVAR_KARMA_GUARDIAN_OF_THE_WASTES,1);                        \
                                else if (check_general_rep >= KARMA_SHIELD_OF_HOPE) then                        \
                                    set_global_var(GVAR_KARMA_SHIELD_OF_HOPE,1);                                \
                                else if (check_general_rep >= KARMA_DEFENDER) then                              \
                                    set_global_var(GVAR_KARMA_DEFENDER,1);                                      \
                                else if (check_general_rep > KARMA_BETRAYER) then                               \
                                    set_global_var(GVAR_KARMA_WANDERER,1);                                      \
                                else if (check_general_rep > KARMA_SWORD_OF_DESPAIR) then                       \
                                    set_global_var(GVAR_KARMA_BETRAYER,1);                                      \
                                else if (check_general_rep > KARMA_SCOURGE_OF_THE_WASTES) then                  \
                                    set_global_var(GVAR_KARMA_SWORD_OF_DESPAIR,1);                              \
                                else if (check_general_rep > KARMA_DEMON_SPAWN) then                            \
                                    set_global_var(GVAR_KARMA_SCOURGE_OF_THE_WASTES,1);                         \
                                else                                                                            \
                                    set_global_var(GVAR_KARMA_DEMON_SPAWN,1)

#define has_rep_holy_warrior    (global_var(GVAR_KARMA_HOLY_WARRIOR) == 1)
#define has_rep_guardian        (global_var(GVAR_KARMA_GUARDIAN_OF_THE_WASTES) == 1)
#define has_rep_shield          (global_var(GVAR_KARMA_SHIELD_OF_HOPE) == 1)
#define has_rep_defender        (global_var(GVAR_KARMA_DEFENDER) == 1)
#define has_rep_wanderer        (global_var(GVAR_KARMA_WANDERER) == 1)
#define has_rep_betrayer        (global_var(GVAR_KARMA_BETRAYER) == 1)
#define has_rep_sword           (global_var(GVAR_KARMA_SWORD_OF_DESPAIR) == 1)
#define has_rep_scourge         (global_var(GVAR_KARMA_SCOURGE_OF_THE_WASTES) == 1)
#define has_rep_demon_spawn     (global_var(GVAR_KARMA_DEMON_SPAWN) == 1)

/*-----------------9/16/97 7:40:M-------------------
 The following will add or remove the reputations of champion or berserker
--------------------------------------------------*/

#define give_champion           set_global_var(GVAR_CHAMPION_REPUTATION,1)
#define give_berserker          set_global_var(GVAR_BERSERKER_REPUTATION,1)
#define remove_champion         set_global_var(GVAR_CHAMPION_REPUTATION,0)
#define remove_berserker        set_global_var(GVAR_BERSERKER_REPUTATION,0)


/*-----------------9/16/97 7:38:M-------------------
 This will check to see if the player has killed enough bad people to be
 considered a champion of the world. it will remove the berserker reputation
 and give the champion reputation
--------------------------------------------------*/

#define CHECK_REP_CHAMPION      if (has_rep_champion) then begin      \
                                        give_champion;                \
                                        remove_berserker;             \
                                end


/*-----------------9/16/97 7:38:M-------------------
 This will check to see if the player has killed too many people and will
 remove the reputation of champion to give the reputation berserker
--------------------------------------------------*/

#define CHECK_REP_BERSERKER     if (has_rep_berserker) then begin     \
                                        give_berserker;               \
                                        remove_champion;              \
                                end


/**************************************************************************
 Every time that an good critter dies, it will increase the number of good
 critters killed. inc_good_critter will keep track of the kills and give or
 remove reputatins based on what has been killed
**************************************************************************/

#ifdef TOWN_REP_VAR
#define inc_good_critter        if (source_obj == dude_obj) then begin                                          \
                                    set_global_var(GVAR_GOOD_MONSTER, (global_var(GVAR_GOOD_MONSTER) + 1));     \
                                    CHECK_REP_CHAMPION                                                          \
                                    if (critter_kill_type(self_obj) == KILL_TYPE_children_kills) then begin     \
                                        inc_childkiller                                                         \
                                    end                                                                         \
                                    CHECK_REP_BERSERKER                                                         \
                                    inc_general_rep(REP_BONUS_KILLED_GOOD_CRITTER);                             \
                                    set_global_var(TOWN_REP_VAR,(global_var(TOWN_REP_VAR)+REP_TOWN_KILL_GOOD)); \
                                    debug_msg("Added "+REP_TOWN_KILL_GOOD+" to Town Rep");                      \
                                end

#define inc_inv_good_crit       if (source_obj == dude_obj) then begin                                          \
                                    set_global_var(GVAR_GOOD_MONSTER, (global_var(GVAR_GOOD_MONSTER) + 1));     \
                                    CHECK_REP_CHAMPION                                                          \
                                    if (critter_kill_type(self_obj) == KILL_TYPE_children_kills) then begin     \
                                        inc_childkiller                                                         \
                                    end                                                                         \
                                    CHECK_REP_BERSERKER                                                         \
                                    inc_general_rep(REP_BONUS_KILLED_GOOD_CRITTER);                             \
                                    set_global_var(TOWN_REP_VAR,(global_var(TOWN_REP_VAR)+REP_TOWN_KILL_EVIL)); \
                                    debug_msg("Added "+REP_TOWN_KILL_GOOD+" to Town Rep");                      \
                                end

#else
#define inc_good_critter        if (source_obj == dude_obj) then begin                                          \
                                    set_global_var(GVAR_GOOD_MONSTER, (global_var(GVAR_GOOD_MONSTER) + 1));     \
                                    if (critter_kill_type(self_obj) == KILL_TYPE_children_kills) then begin     \
                                        inc_childkiller                                                         \
                                    end                                                                         \
                                    CHECK_REP_CHAMPION                                                          \
                                    CHECK_REP_BERSERKER                                                         \
                                    inc_general_rep(REP_BONUS_KILLED_GOOD_CRITTER);                             \
                                end

#endif

#define inc_neutral_critter     if (source_obj == dude_obj) then begin                                          \
                                    CHECK_REP_CHAMPION                                                          \
                                    if (critter_kill_type(self_obj) == KILL_TYPE_children_kills) then begin     \
                                        inc_childkiller                                                         \
                                    end                                                                         \
                                    CHECK_REP_BERSERKER                                                         \
                                    inc_general_rep(REP_BONUS_KILLED_NEUTRAL_CRITTER);                          \
                                end

/**************************************************************************
 Every time that an evil critter dies, it will increase the number of evil
 critters killed. inc_evil_critter will keep track of the kills and give or
 remove reputations based on what has been killed
**************************************************************************/

#ifdef TOWN_REP_VAR
#define inc_evil_critter        if (source_obj == dude_obj) then begin                                          \
                                    set_global_var(GVAR_BAD_MONSTER, (global_var(GVAR_BAD_MONSTER) + 1));       \
                                    if (critter_kill_type(self_obj) == KILL_TYPE_children_kills) then begin     \
                                        inc_childkiller                                                         \
                                    end                                                                         \
                                    CHECK_REP_BERSERKER                                                         \
                                    CHECK_REP_CHAMPION                                                          \
                                    inc_general_rep(REP_BONUS_KILLED_EVIL_CRITTER);                             \
                                    set_global_var(TOWN_REP_VAR,(global_var(TOWN_REP_VAR)+REP_TOWN_KILL_EVIL)); \
                                    debug_msg("Added "+REP_TOWN_KILL_EVIL+" to Town Rep");                      \
                                end

#define inc_inv_evil_crit       if (source_obj == dude_obj) then begin                                          \
                                    set_global_var(GVAR_BAD_MONSTER, (global_var(GVAR_BAD_MONSTER) + 1));       \
                                    if (critter_kill_type(self_obj) == KILL_TYPE_children_kills) then begin     \
                                        inc_childkiller                                                         \
                                    end                                                                         \
                                    CHECK_REP_BERSERKER                                                         \
                                    CHECK_REP_CHAMPION                                                          \
                                    inc_general_rep(REP_BONUS_KILLED_EVIL_CRITTER);                             \
                                    set_global_var(TOWN_REP_VAR,(global_var(TOWN_REP_VAR)+REP_TOWN_KILL_GOOD)); \
                                    debug_msg("Added "+REP_TOWN_KILL_EVIL+" to Town Rep");                      \
                                end

#else
#define inc_evil_critter        if (source_obj == dude_obj) then begin                                          \
                                    set_global_var(GVAR_BAD_MONSTER, (global_var(GVAR_BAD_MONSTER) + 1));       \
                                    if (critter_kill_type(self_obj) == KILL_TYPE_children_kills) then begin     \
                                        inc_childkiller                                                         \
                                    end                                                                         \
                                    CHECK_REP_BERSERKER                                                         \
                                    CHECK_REP_CHAMPION                                                          \
                                    inc_general_rep(REP_BONUS_KILLED_EVIL_CRITTER);                             \
                                end
#endif

/**************************************************************************
 Enemy of a City Reputation
 These will need to be defined as:
    REP_ENEMY_town
**************************************************************************/


// Fallout 1 default
#define REP_ENEMY_VAULT13                       (global_var(GVAR_VAULT_13_HOSTILE) == 1)
#define REP_ENEMY_SHADY_SANDS                   (global_var(GVAR_ENEMY_SHADY_SANDS) == 1)
#define REP_ENEMY_JUNKTOWN                      (global_var(GVAR_ENEMY_JUNKTOWN) == 1)
#define REP_ENEMY_JUNKTOWN_CITIZENS             (global_var(GVAR_DUDE_ENEMY_JUNK_CITIZEN) == 1)
#define REP_ENEMY_JUNKTOWN_BOXER                (global_var(GVAR_DUDE_ENEMY_JUNK_BOXER) == 1)
#define REP_ENEMY_JUNKTOWN_GIZMO                (global_var(GVAR_ENEMY_GIZMOS_GANG) == 1)
#define REP_ENEMY_JUNKTOWN_SKULZ                (global_var(GVAR_DUDE_ENEMY_SKULZ) == 1)
#define REP_ENEMY_RAIDERS                       (global_var(GVAR_ENEMY_RAIDERS) == 1)
#define REP_ENEMY_HUB                           (global_var(GVAR_ENEMY_HUB) == 1)
#define REP_ENEMY_BOS                           (global_var(GVAR_ENEMY_BROTHERHOOD) == 1)
#define REP_ENEMY_LA_ADYTUM                     (global_var(GVAR_ENEMY_ADYTUM) == 1)
#define REP_ENEMY_LA_BLADES                     (global_var(GVAR_ENEMY_BLADES) == 1)
#define REP_ENEMY_LA_REGULATORS                 (global_var(GVAR_DUDE_ENEMY_REGULATORS) == 1)
#define REP_ENEMY_LA_GUNRUNNERS                 (global_var(GVAR_ENEMY_GUN_RUNNERS) == 1)
#define REP_ENEMY_ENCOUNTER                     (global_var(GVAR_ENEMY_RANDOM_ENC) == 1)

/**************************************************************************
 Reputation for Solving Seeds
 These will need to be defined as:
    REP_BONUS_seed
**************************************************************************/


// Vault 13
#define REP_BONUS_GAME_STARTED                  (20)
#define REP_BONUS_RETURNED_WATERCHP             (100)
#define inc_v13_rep(x)                          inc_global_var_amt(GVAR_TOWN_REP_V13, x)

// Vault 15
#define inc_v15_rep(x)                          inc_global_var_amt(GVAR_TOWN_REP_V15, x)

// Shady Sands
#define REP_BONUS_INSULTED_ARADESH              (-20)
#define REP_BONUS_HELPING_JARVIS                (3)
#define REP_BONUS_RADSCORPIONS_GONE             (15)
#define REP_BONUS_TANDI_RESCUED                 (30)
#define REP_BONUS_CROP_ROTATION                 (5)
#define REP_BONUS_COMPLIMENT_FOOD               (1)
#define inc_shady_rep(x)                        inc_global_var_amt(GVAR_TOWN_REP_SHADYSANDS, x)

// Raiders
#define REP_BONUS_KILLED_RAIDER                 (-1)
#define REP_BONUS_GARL_KILLED                   (-10)
#define inc_raiders_rep(x)                      inc_global_var_amt(GVAR_TOWN_REP_RAIDERS, x)

// Junktown
#define REP_BONUS_KILLED_SKULZ                  (5)
#define REP_BONUS_KILLED_NEAL                   (-5)
#define REP_BONUS_KILLED_GIZMO                  (10)
#define REP_BONUS_KILLED_KILLIAN                (-10)
#define REP_BONUS_FLEEING_JAIL                  (-5)
#define REP_BONUS_HELPED_TRISH_AND_SAUL         (1)
#define REP_BONUS_SINTHIA_RESCUED               (5)
#define REP_BONUS_SINTHIA_KILLED                (-2)
#define inc_junktown_rep(x)                     inc_global_var_amt(GVAR_TOWN_REP_JUNKTOWN, x)

// Hub
#define REP_BONUS_MISSING_CARAVANS              (5)
#define REP_BONUS_BOB_JAILED                    (5)
#define REP_BONUS_BOB_REPORT_FAILED             (-2)
#define REP_BONUS_KILLED_DECKER                 (15)
#define REP_BONUS_KILLED_HIGHTOWER              (-10)
#define REP_BONUS_NECKLACE_STOLEN               (-3)
#define REP_BONUS_KIND_TO_HAROLD                (1)
#define REP_BONUS_DAN_AND_BILLY                 (1)
#define REP_BONUS_SPARED_DEADGUY                (1)
#define inc_hub_rep(x)                          inc_global_var_amt(GVAR_TOWN_REP_HUB, x)

// Boneyard
#define REP_BONUS_FARM_REPAIRED                 (3)
#define REP_BONUS_RAZOR_DEAD                    (-5)
#define REP_BONUS_GABRIEL_DEAD                  (-2)
#define REP_BONUS_ZIMMERMAN_DEAD                (2)
#define REP_BONUS_BLADES_DEAD                   (-10)
#define REP_BONUS_GUNRNR_DEAD                   (-5)
#define REP_BONUS_DEATHCLAWS_DEAD               (5)
#define REP_BONUS_REGULATORS_DEAD               (25)
#define REP_BONUS_HELPED_TALIUS                 (2)
#define REP_BONUS_REFUSING_MIKE_REWARD          (1)
#define inc_boneyard_rep(x)                     inc_global_var_amt(GVAR_TOWN_REP_BONEYARD, x)

// Necropolis
#define REP_BONUS_WATERCHIP_TAKEN               (-25)
#define REP_BONUS_WATER_PUMP_FIXED              (25)
#define REP_BONUS_WATERSHED_MUTANTS_DEAD        (10)
#define inc_necropolis_rep(x)                   inc_global_var_amt(GVAR_TOWN_REP_NECROPOLIS, x)

// Glow
#define REP_BONUS_DEFEAT_ZAX                    (25)
#define REP_BONUS_DISABLED_TRAPS                (1)
#define inc_glow_rep(x)                         inc_global_var_amt(GVAR_TOWN_REP_GLOW, x)

// BOS
#define REP_BONUS_KICKED_OUT                    (-25)
#define REP_BONUS_LIED_TO_LARRY                 (-1)
#define inc_bos_rep(x)                          inc_global_var_amt(GVAR_TOWN_REP_BOS, x)

// Mariposa
#define REP_BONUS_BLOWN_UP_VATS                 (-100)
#define inc_mbase_rep(x)                        inc_global_var_amt(GVAR_TOWN_REP_MBASE, x)

// Cathedral
#define REP_BONUS_BLOWN_UP_MASTER               (-100)
#define inc_cathedral_rep(x)                    inc_global_var_amt(GVAR_TOWN_REP_CATHEDRAL, x)

// Scrapheap
#define REP_BONUS_GENERATOR_BROKEN              (-30)
#define REP_BONUS_DEFEATED_GANGS                (30)
#define inc_scrapheap_rep(x)                    inc_global_var_amt(GVAR_TOWN_REP_SCRAPHEAP, x)
