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
                                    if (critter_kill_type(self_obj) == KILL_TYPE_children_kills) then           \
                                        inc_childkiller                                                         \
                                    CHECK_REP_BERSERKER                                                         \
                                    inc_general_rep(REP_BONUS_KILLED_GOOD_CRITTER);                             \
                                    set_global_var(TOWN_REP_VAR,(global_var(TOWN_REP_VAR)+REP_TOWN_KILL_GOOD)); \
                                    debug_msg("Added "+REP_TOWN_KILL_GOOD+" to Town Rep");                      \
                                end

#define inc_inv_good_crit       if (source_obj == dude_obj) then begin                                          \
                                    set_global_var(GVAR_GOOD_MONSTER, (global_var(GVAR_GOOD_MONSTER) + 1));     \
                                    CHECK_REP_CHAMPION                                                          \
                                    if (critter_kill_type(self_obj) == KILL_TYPE_children_kills) then           \
                                        inc_childkiller                                                         \
                                    CHECK_REP_BERSERKER                                                         \
                                    inc_general_rep(REP_BONUS_KILLED_GOOD_CRITTER);                             \
                                    set_global_var(TOWN_REP_VAR,(global_var(TOWN_REP_VAR)+REP_TOWN_KILL_EVIL)); \
                                    debug_msg("Added "+REP_TOWN_KILL_GOOD+" to Town Rep");                      \
                                end

#else
#define inc_good_critter        if (source_obj == dude_obj) then begin                                          \
                                    set_global_var(GVAR_GOOD_MONSTER, (global_var(GVAR_GOOD_MONSTER) + 1));     \
                                    if (critter_kill_type(self_obj) == KILL_TYPE_children_kills) then           \
                                        inc_childkiller                                                         \
                                    CHECK_REP_CHAMPION                                                          \
                                    CHECK_REP_BERSERKER                                                         \
                                    inc_general_rep(REP_BONUS_KILLED_GOOD_CRITTER);                             \
                                end

#endif

#define inc_neutral_critter     if (source_obj == dude_obj) then begin                                          \
                                    CHECK_REP_CHAMPION                                                          \
                                    if (critter_kill_type(self_obj) == KILL_TYPE_children_kills) then           \
                                        inc_childkiller                                                         \
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
                                    if (critter_kill_type(self_obj) == KILL_TYPE_children_kills) then           \
                                        inc_childkiller                                                         \
                                    CHECK_REP_BERSERKER                                                         \
                                    CHECK_REP_CHAMPION                                                          \
                                    inc_general_rep(REP_BONUS_KILLED_EVIL_CRITTER);                             \
                                    set_global_var(TOWN_REP_VAR,(global_var(TOWN_REP_VAR)+REP_TOWN_KILL_EVIL)); \
                                    debug_msg("Added "+REP_TOWN_KILL_EVIL+" to Town Rep");                      \
                                end

#define inc_inv_evil_crit       if (source_obj == dude_obj) then begin                                          \
                                    set_global_var(GVAR_BAD_MONSTER, (global_var(GVAR_BAD_MONSTER) + 1));       \
                                    if (critter_kill_type(self_obj) == KILL_TYPE_children_kills) then           \
                                        inc_childkiller                                                         \
                                    CHECK_REP_BERSERKER                                                         \
                                    CHECK_REP_CHAMPION                                                          \
                                    inc_general_rep(REP_BONUS_KILLED_EVIL_CRITTER);                             \
                                    set_global_var(TOWN_REP_VAR,(global_var(TOWN_REP_VAR)+REP_TOWN_KILL_GOOD)); \
                                    debug_msg("Added "+REP_TOWN_KILL_EVIL+" to Town Rep");                      \
                                end

#else
#define inc_evil_critter        if (source_obj == dude_obj) then begin                                          \
                                    set_global_var(GVAR_BAD_MONSTER, (global_var(GVAR_BAD_MONSTER) + 1));       \
                                    if (critter_kill_type(self_obj) == KILL_TYPE_children_kills) then           \
                                        inc_childkiller                                                         \
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


// Fallout 2 default
#define REP_ENEMY_ARROYO                        (global_var(GVAR_ENEMY_ARROYO) == 1)
#define REP_ENEMY_DEN                           (global_var(GVAR_ENEMY_DEN) == 1)
#define REP_ENEMY_KLAMATH                       (global_var(GVAR_ENEMY_KLAMATH) == 1)
#define REP_ENEMY_VAULT_VILLAGE                 (global_var(GVAR_ENEMY_VAULT_VILLAGE) == 1)
#define REP_ENEMY_VAULT_CITY                    (global_var(GVAR_ENEMY_VAULT_CITY) == 1)
#define REP_ENEMY_GECKO                         (global_var(GVAR_ENEMY_GECKO) == 1)

// Vault City Town Rep
#define REP_TOWN_SEXED_UP_AMANDA                (-10)
#define REP_TOWN_RESCUED_JOSHUA_NO_SEX          (3)
#define REP_TOWN_TOLD_ANDREW_NO_REWARD          (1)
#define REP_TOWN_FIXED_AUTODOC                  (1)
#define REP_TOWN_CASSIDY_JOINED                 (1)
#define REP_TOWN_DELIVERED_BOOZE                (3)
#define REP_TOWN_CURED_CHARLIE                  (3)
#define REP_TOWN_TORTURED_CURTIS                (-3)
#define REP_TOWN_RETURNED_CURTIS_DOLL           (1)
#define REP_TOWN_GAVE_TROY_FORMULA              (3)
#define REP_TOWN_BLACKMAILED_TROY               (-3)
#define REP_TOWN_PASSED_CITIZENSHIP_TEST        (10)
#define REP_TOWN_TELL_KOHL_YOU_LIKE_BOOKS       (1)
#define REP_TOWN_TOLD_LYNETTE_ABOUT_RAIDERS     (10)
#define REP_TOWN_EXPOSED_MOORE                  (3)
#define REP_TOWN_EXPOSED_BISHOP_RAIDERS         (5)
#define REP_TOWN_EXPOSED_BISHOP_NCR             (5)
#define REP_TOWN_GOT_LYNETTE_HOLODISK_BACK      (5)
#define REP_TOWN_CAPTAIN_GUARD                  (10)
#define REP_TOWN_EXILE_TROY                     (-5)
#define REP_TOWN_VALERIE_TOOLS                  (1)
#define REP_TOWN_PISSED_MCCLURE                 (-5)
#define REP_TOWN_MCCLURE_REDDING_PROBLEM        (1)
#define REP_TOWN_MCCLURE_ANTIDOTE_DELIVERED     (5)
#define REP_TOWN_MCCLURE_CITIZENSHIP            (10)
#define REP_TOWN_INSULT_GREETER                 (-3)
#define REP_TOWN_BLACKMAIL_MOORE                (-1)
#define REP_TOWN_SMITH_HELP_FREE                (3)
#define REP_TOWN_SCREW_SMITHS                   (-3)
#define REP_TOWN_DONATE_GREAT                   (3)
#define REP_TOWN_DONATE_GOOD                    (1)
#define REP_TOWN_PHYLLIS_STERILITY              (3)
#define REP_TOWN_PISSED_RANDAL                  (-5)
#define REP_TOWN_PULLED_RANK_ON_STARK           (-3)
#define REP_TOWN_SCOUTED_GECKO                  (1)
#define REP_TOWN_SCOUTED_NCR                    (3)
#define REP_TOWN_PISSED_WALLACE                 (-1)
#define REP_TOWN_KICKED_OUT                     (-30)

// broken hills town rep
#define REP_TOWN_MIGHTY_SUCCESS                 (2)
#define REP_TOWN_PREACHED_TO_MANSON             (2)
#define REP_TOWN_JAILBREAK_SUCCESS              (-10)
#define REP_TOWN_PURIFIER_FIXED                 (10)
#define REP_TOWN_PURIFIER_DESTROYED             (-30)
#define REP_TOWN_CONSPIRACY_EXPOSED             (10)
#define REP_TOWN_BODIES_FOUND                   (5)
#define REP_TOWN_CONFRONTED_FRANCIS             (5)
#define REP_TOWN_RETURNED_ORE_TO_CITY           (5)
#define REP_TOWN_RETURNED_ORE_TO_CITY_FOR_CASH  (-5)
#define REP_TOWN_SHOVELED_ALL_CRAP              (-5)
#define REP_TOWN_GAVE_ERIC_POWER                (2)
#define REP_TOWN_OPTIMIZED_POWER_GRID           (4)
#define REP_TOWN_MARCUS_IN_PARTY                (5)
#define REP_TOWN_REPLANTED_SEYMOUR              (5)
#define REP_TOWN_TYPHON_TOLD_TREASURE           (5)

// modoc town rep
#define REP_TOWN_SAVE_JONNY                     (10)
#define REP_TOWN_SOLVE_FAMILY_FEUD_BEST         (10)
#define REP_TOWN_SOLVE_FAMILY_FEUD_WORST        (-10)
#define REP_TOWN_FINISH_BRAHMIN_SEED            (2)
#define REP_TOWN_FINISH_VERMIN_HUNT             (2)
#define REP_TOWN_GAVE_ROSE_DOG                  (-1)
#define REP_TOWN_HARRASS_MIRIA                  (-20)
#define REP_TOWN_SOLVE_GHOST_FARM_BEST          (30)
#define REP_TOWN_SOLVE_GHOST_FARM_REGULAR       (15)
#define REP_TOWN_SOLVE_GHOST_FARM_BAD           (-5)
#define REP_TOWN_SOLVE_GHOST_FARM_WORST         (-20)
#define REP_TOWN_SEND_KARL_HOME                 (3)
#define REP_TOWN_DRIVE_KARL_NUTS                (-3)
#define REP_TOWN_JO_CHOP_FINGER                 (-10)

// den town rep
#define REP_TOWN_BURY_ANNA                      (5)
#define REP_TOWN_DEN_KILL_METZGER               (30)
#define REP_TOWN_DEN_KILL_BECKY                 (-50)
#define REP_TOWN_DEN_JOIN_SLAVERS               (-20)
#define REP_TOWN_DEN_KILL_MOM                   (-20)
#define inc_den_rep(x)                          inc_global_var(GVAR_TOWN_REP_THE_DEN, x)

// new reno rep mods
/**************************************************************************
 Champion of a City Reputation
 These will need to be defined as:
    REP_HERO_town
**************************************************************************/

//NCR
#define REP_HERO_NCR_SOLVED_V15                  (20)
#define REP_HERO_NCR_FOUND_V13                   (15)
#define REP_HERO_NCR_FOUND_SPY                   (5)
#define REP_HERO_NCR_STOPED_BRAHMIN_RAIDS        (5)
#define REP_HERO_NCR_BECAME_RANGER               (5)
#define REP_HERO_NCR_TALKED_JACK                 (10)

#define inc_ncr_rep(x)     set_global_var(GVAR_TOWN_REP_NCR, global_var(GVAR_TOWN_REP_NCR) + x)

//Vault 15
#define REP_HERO_V15_CRISSY_ALIVE                (10)
#define REP_HERO_V15_CRISSY_DEAD                  (5)
#define REP_HERO_V15_KILL_DARION                 (25)

#define inc_vault15_rep(x)  set_global_var(GVAR_TOWN_REP_VAULT_15, global_var(GVAR_TOWN_REP_VAULT_15) + x)

//Vault 13
#define REP_HERO_V13_FIX_COMPUTER                (30)

#define inc_vault13_rep(x)  set_global_var(GVAR_TOWN_REP_VAULT_13, global_var(GVAR_TOWN_REP_VAULT_13) + x)

//San Fran Town Rep
#define REP_HERO_SAN_FRAN_SAVE_GIRL_DEAD        2
#define REP_HERO_SAN_FRAN_SAVE_GIRL_ALIVE       5
#define REP_HERO_SAN_FRAN_KILL_DRAGON           5
#define REP_HERO_SAN_FRAN_KILL_DRAGON_LOPAN    10
#define REP_HERO_SAN_FRAN_FUEL_EMP             -5
#define REP_HERO_SAN_FRAN_ELRON_ADJUST         -5
#define REP_HERO_SAN_FRAN_ELRON_KILL_BADGER    -7
#define REP_HERO_SAN_FRAN_ELRON_KILL_EMP       -5
#define REP_HERO_SAN_FRAN_ELRON_VERTIBIRD      -5
#define REP_HERO_SAN_FRAN_ELRON_FORMAT          3
#define REP_HERO_SAN_FRAN_KILL_LOPAN            5
#define REP_HERO_SAN_FRAN_KILL_LOPAN_DRAGON    10
#define REP_HERO_SAN_FRAN_HACKED_SHI_BAD      -10
#define REP_HERO_SAN_FRAN_KILL_OZ9              5
#define REP_HERO_SAN_FRAN_SHI_VERTIBIRD         2
#define REP_HERO_SAN_FRAN_SPLEEN_DEADWONG       2
#define REP_HERO_SAN_FRAN_SPLEEN_FOUND          4
#define REP_HERO_SAN_FRAN_SPLEEN_REINSTERTED    6
#define REP_HERO_SAN_FRAN_TANKER_FUEL_DAVE_EL   4
#define REP_HERO_SAN_FRAN_TANKER_FUEL_DAVE_SHI -4
#define REP_HERO_SAN_FRAN_BOS_QUEST             5
#define REP_HERO_SAN_FRAN_ARMOR                 3
#define REP_HERO_SAN_FRAN_GAS                   0

#define inc_san_fran_rep(x) inc_global_var(GVAR_TOWN_REP_SAN_FRANCISCO, x)

// new reno
#define REP_NEW_RENO_BOXER_LEVEL_1              (1)
#define REP_NEW_RENO_BOXER_LEVEL_2              (2)
#define REP_NEW_RENO_BOXER_LEVEL_3              (5)
#define REP_NEW_RENO_BOXER_LEVEL_4              (15)
#define REP_NEW_RENO_FEED_CODY                  (1)
#define REP_NEW_RENO_PORN_STAR                  (15)
#define REP_NEW_RENO_MOORE_BRIEFCASE            (5)
#define REP_NEW_RENO_ASSASINATE_WESTIN          (5)
#define REP_NEW_RENO_ASSASSINATE_CARLSON        (5)
#define REP_NEW_RENO_STEAL_POOR_BOX             (-1)
#define REP_NEW_RENO_DONATE_POOR_BOX            (1)
#define REP_NEW_RENO_MADE_MAN_BISHOP            (15)
#define REP_NEW_RENO_SCARE_JULES                (3)
#define REP_NEW_RENO_KITTY_DATE                 (10)
#define REP_NEW_RENO_KITTY_MAGAZINES            (1)
#define REP_NEW_RENO_MRS_BISHOP_CONVINCE        (1)
#define REP_NEW_RENO_DESTROY_WRIGHT_STILLS      (-5)
#define REP_NEW_RENO_SOLVE_MURDER               (5)
#define REP_NEW_RENO_SOLVE_MURDER_BONUS         (5)
#define REP_NEW_RENO_MADE_MAN_WRIGHT            (10)
#define REP_NEW_RENO_RESOLVE_LLOYD_SITUATION    (5)
#define REP_NEW_RENO_SALVATORE_TRIBUTE          (5)
#define REP_NEW_RENO_MADE_MAN_SALVATORE         (10)
#define REP_NEW_RENO_KILLED_BOSS_SALVATORE      (5)
#define REP_NEW_RENO_NON_VIOLENT_CAR_RECOVER    (2)
#define REP_NEW_RENO_BIG_JESUS_TRIBUTE          (5)
#define REP_NEW_RENO_MADE_MAN_MORDINO           (15)
#define REP_NEW_RENO_ELDRIDGE_LASER             (1)
#define REP_NEW_RENO_RAMIREZ_PACKAGE            (3)
#define REP_NEW_RENO_KILLED_BOSS                (-25)

#define inc_reno_rep(x)    inc_global_var(GVAR_TOWN_REP_NEW_RENO, x)




/**************************************************************************
 Reputation for Solving Seeds
 These will need to be defined as:
    REP_BONUS_seed
**************************************************************************/


// Vault 13
#define REP_BONUS_GAME_STARTED                  (25)
#define REP_BONUS_RETURNED_WATERCHP             (100)
#define inc_v13_rep(x)                          inc_global_var_amt(GVAR_TOWN_REP_V13, x)

// Vault 15
#define inc_v15_rep(x)                          inc_global_var_amt(GVAR_TOWN_REP_V15, x)

// Shady Sands
#define REP_BONUS_INSULTED_ARADESH              (-20)
#define REP_BONUS_HELPING_JARVIS                (3)
#define REP_BONUS_RADSCORPIONS_GONE             (15)
#define REP_BONUS_TANDI_RESCUED                 (30)
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
