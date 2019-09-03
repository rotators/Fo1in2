#ifndef __GLOBAL__
#define __GLOBAL__

// vanilla

#define GVAR_CHILD_KILLER_SHADY           (0)  // Has the player killed children in Shady Sands?
#define GVAR_CHILD_KILLER_HUB             (1)  // Has the player killed children in Hub
#define GVAR_NUM_RADSCORPIONS             (2)  // How many RadScorpions are still around in cave
#define GVAR_CHILD_KILLER_ADYTUM          (3)  // Has player killed children in Adytum
#define GVAR_DOGS_KILLED                  (4)  // Number of Dogs killed
#define GVAR_DOG_EMPATHY                  (5)  // Dogs and player like each other
#define GVAR_QUEST_PEOPLE                 (6)  // Number of Quest people killed
#define GVAR_FOLLOWERS_INVADED            (7)  // Number of cows killed
#define GVAR_MAP_ENTRANCE_NUMBER          (8)  // Where did the player enter the map
#define GVAR_DAYS_TO_VAULT13_DISCOVERY    (9)  // How long before the vault is discovered?
#define GVAR_VAULT_WATER                  (10) // How long for the water supply :=0;              //  (see below)
#define GVAR_VAULT_INVADED                (11) // Has Vault 13 been invaded?
#define GVAR_SHADY_SANDS_INVADED          (12) // Has Shady Sands been invaded?
#define GVAR_NECROPOLIS_INVADED           (13) // Has Necropolis been invaded
#define GVAR_HUB_INVADED                  (14) // Has Hub been invaded
#define GVAR_JUNKTOWN_INVADED             (15) // Has Junktown been invaded?
#define GVAR_BROTHERHOOD_INVADED          (16) // Has the Brotherhood of Steel been invaded?
#define GVAR_VATS_BLOWN                   (17) // Have the Vats been destroyed? :=0;              //  (see below)
#define GVAR_MASTER_BLOWN                 (18) // Has the Master been destroyed? :=0;              //  (see below)
#define GVAR_NECROPOLIS_VISITED           (19) // Has Necropolis been visited?
#define GVAR_NECROPOLIS_KNOWN             (20) // Is Necropolis known to the player?
#define GVAR_MOTEL_OF_DOOM_VISITED        (21) // Has Motel of Doom been visited?
#define GVAR_HALL_OF_THE_DEAD_VISITED     (22) // Has Hall of the Dead been visited?
#define GVAR_WATERSHED_VISITED            (23) // Has the Watershed been visited?
#define GVAR_NECROPOLIS_VAULT_VISITED     (24) // Has the Necropolis Vault been visited?
#define GVAR_TANDI_X                      (25) // For Tandi's special endings
#define GVAR_TANDI_STATUS                 (26) // Is Tandi :=0;              //  (free, kidnapped,rescued) :=0;              //  (see below)
#define GVAR_TANDI_DEAD                   (27) // Is Tandi Dead?
#define GVAR_RADSCORPIONS_KILLED          (28) // Are the Rad Scorpions killed or contained?
#define GVAR_NECROP_MUTANTS_KILLED        (29) // Are the Super Mutants killed in Necropolis?
#define GVAR_NECROP_WATER_CHIP_TAKEN      (30) // When was the Water Chip Taken from Necropolis
#define GVAR_NECROP_WATER_PUMP_FIXED      (31) // Is the Water Pump fixed for Necropolis?
#define GVAR_LOAD_MAP_INDEX               (32) // Which part of a town map are you going to jump to
#define GVAR_ANIMALS_KILLED               (33) // How many animals are killed?
#define GVAR_HUMANS_KILLED                (34) // How many people are killed?
#define GVAR_SUPER_MUTANTS_KILLED         (35) // How many Super Mutants are killed?
#define GVAR_HIRED_BY_KILLIAN             (36) // Has Killian hired the player to trap Gizmo?
#define GVAR_KILLIAN_DEAD                 (37) // Is Killian dead?
#define GVAR_GIZMO_DEAD                   (38) // Is Gizmo Dead?
#define GVAR_HIRED_BY_GIZMO               (39) // Was the player hired by Gizmo to kill Killian?
#define GVAR_IN_JAIL                      (40) // Is the player in Jail?
#define GVAR_BUG_PLANTED                  (41) // Is the Bug planted?
#define GVAR_GOT_CONFESSION               (42) // Did the player tape Gizmo's confession?
#define GVAR_RADSCORPION_SEED             (43) // Is the player off killing the Rad Scorpions?
#define GVAR_DEATHCLAW_SEED               (44) // Is the player off looking for the Deathclaw?
#define GVAR_BROTHERHOOD_SEED             (45) // Is the player trying to :=0;              //  (become initiate/capture initiate)?
#define GVAR_HUB_SEED                     (46) //
#define GVAR_PLAYER_LOCATION              (47) // Where is the player in the World Map
#define GVAR_LOXLEY_X                     (48) // Special ending for Loxley :=0;              //  (see below)
#define GVAR_MAXSON_X                     (49) // Special endings for Maxson
#define GVAR_CATHEDRAL                    (50) //
#define GVAR_VATS_STATUS                  (51) // Have the Vats been destroyed?
#define GVAR_CHILDREN_STATUS              (52) //
#define GVAR_MASTER_DEAD                  (53) // Is the Master Dead?
#define GVAR_LIEUTENANTS_DEAD             (54) // How many Lieutenants are dead? :=0;              //  (see below)
#define GVAR_COUNTDOWN_TO_DESTRUCTION     (55) // how much time before the bomb goes off
#define GVAR_BOMB_DISARMED                (56) // is the Bomb disarmed?
#define GVAR_ENTERING_VATS_HOW            (57) // How did the player enter the vats? :=0;              //  (see below)
#define GVAR_WATER_SHED_STATUS            (58) // Are there Super Mutants in the Water shed :=0;              //  (see below)
#define GVAR_PLAYER_CAPTURED              (59) // Has the player been captured?
#define GVAR_SIGNAL_REWARD                (60) // How much of a reward is Set telling Garret to give to player
#define GVAR_SHADOW_PASSWORD              (61) // did Nicole give player the 'Shadow' password?
#define GVAR_FOLLOWER_STEALTH_HELP        (62) // did the Followers offer to sneak player in Children of Cathedral?
#define GVAR_FOLLOWER_MACHO_HELP          (63) // are Followers going to attack Children of Cathedral?
#define GVAR_KNIGHT_WARNING               (64) // will the Knight need to warn player of his manners?
#define GVAR_WORLD_TERRAIN                (65) // what is the terrain the player is on :=0;              //  (see below)
#define GVAR_NECROP_WATER                 (66) // what is the status of the water level in Necop?
#define GVAR_VAULT_13                     (67)
#define GVAR_SHADY_SANDS                  (68)
#define GVAR_RAIDERS                      (69)
#define GVAR_BURIED_VAULT                 (70)
#define GVAR_JUNKTOWN                     (71)
#define GVAR_NECROPOLIS                   (72)
#define GVAR_THE_HUB                      (73)
#define GVAR_BROTHERHOOD_OF_STEEL         (74)
#define GVAR_ANGELS_BONEYARD              (75)
#define GVAR_THE_GLOW                     (76)
#define GVAR_CHILDREN_OF_CATHEDRAL        (77)
#define GVAR_THE_VATS                     (78)
#define GVAR_MASTERS_LAIR                 (79)
#define GVAR_BROTHERHOOD_12               (80)  // BROHD12.MAP
#define GVAR_BROTHERHOOD_34               (81)  // BROHD34.MAP
#define GVAR_BROTHERHOOD_ENTRANCE         (82)  // BROHDENT.MAP
#define GVAR_CAVES                        (83)  // CAVES.MAP
#define GVAR_CHILDREN_1                   (84)  // CHILDRN1.MAP
#define GVAR_DESERT_1                     (85)  // DESERT1.MAP
#define GVAR_DESERT_2                     (86)  // DESERT2.MAP
#define GVAR_DESERT_3                     (87)  // DESERT3.MAP
#define GVAR_HALL_OF_THE_DEAD             (88)  // HALLDED.MAP
#define GVAR_HOTEL_OF_DOOM                (89)  // HOTEL.MAP
#define GVAR_JUNKTOWN_CASINO              (90)  // JUNKCSNO.MAP
#define GVAR_JUNKTOWN_ENTRANCE            (91)  // JUNKENT.MAP
#define GVAR_JUNKTOWN_KILLIAN             (92)  // JUNKKILL.MAP
#define GVAR_SHADY_SANDS_EAST             (93)  // SHADYE.MAP
#define GVAR_SHADY_SANDS_WEST             (94)  // SHADYW.MAP
#define GVAR_VAULT_13_MAP                 (95)  // VAULT13.MAP
#define GVAR_BURIED_VAULT_MAP             (96)  // VAULTBUR.MAP
#define GVAR_VAULT_ENTRANCE               (97)  // VAULTENT.MAP
#define GVAR_NECROP_VAULT                 (98)  // VAULTNEC.MAP
#define GVAR_WATERSHED                    (99)  // WATRSHD.MAP
#define GVAR_KILL_DEATHCLAW               (100) // Starts in Hub
#define GVAR_FIND_WATER_CHIP              (101) // Starts in Vault 13 :=0;              //  (ends in Necropolis)
#define GVAR_KILL_RADSCORPIONS            (102) // Starts in Shady Sands
#define GVAR_RESCUE_TANDI                 (103) // Starts in Shady Sands :=0;              //  (ends in Raiders
#define GVAR_CAPTURE_GIZMO                (104) // In Junktown
#define GVAR_KILL_KILLIAN                 (105) // In Junktown
#define GVAR_MISSING_CARAVAN              (106) // Starts in Hub
#define GVAR_STEAL_NECKLACE               (107) // In The Hub
#define GVAR_BECOME_AN_INITIATE           (108) // Starts in the Brotherhood of Steel
#define GVAR_FIND_LOST_INITIATE           (109) // Starts in the Brotherhood of Steel
#define GVAR_WARNED_BROTHERHOOD           (110) // Starts in the Brotherhood of Steel
#define GVAR_KILL_MERCHANT                (111) // In the Hub
#define GVAR_KILL_JAIN                    (112) // In the Hub
#define GVAR_KILL_SUPER_MUTANTS           (113) // In Necropolis
#define GVAR_GARL_DEAD                    (114) // Is Garl Dead
#define GVAR_TOTAL_RAIDERS                (115) // The total number of raiders alive
#define GVAR_MISTAKEN_ID                  (116) // Do the Raiders think you are Garl's dad?
#define GVAR_WITH_CARAVAN                 (117) // Is the player travelling w/ caravans?
#define GVAR_IAN_STATUS                   (118) // Ian from Shady Sands :=0;              //  (Alive/Dead/Where)
#define GVAR_TOLYA_STATUS                 (119) // Tolya the Raider
#define GVAR_PETROX_STATUS                (120) // Petrox the Raider
#define GVAR_HERNANDEZ_STATUS             (121) // Hernandez from Junktown/Hub
#define GVAR_KENJI_STATUS                 (122) // Kenji the thug Junktow/Hub
#define GVAR_HUNTER_STATUS                (123) // Chris, the Bounty hunter
#define GVAR_SETH_STATUS                  (124) // Seth from Shady Sands
#define GVAR_TRENT_STATUS                 (125) // Trent from the Hub and random encounter
#define GVAR_JASON_STATUS                 (126) // Jason from the Adytum
#define GVAR_ROMEO_JULIET                 (127) // Romeo and Juliet quest
#define GVAR_GANG_WAR                     (128) // are the gangs gone?
#define GVAR_DESTROY_FOLLOWERS            (129) // did the player deliver the bomb?
#define GVAR_LOST_BROTHER                 (130) // look for the lost brother of the Blades in the Runners
#define GVAR_BLADES_HELP                  (131) // will the blades help you knock out the children?
#define GVAR_TRAIN_FOLLOWERS              (132) // did the player train the followers?
#define GVAR_FIND_AGENT                   (133) // find the double agent in the followers
#define GVAR_TANGLER_DEAD                 (134) // is Tangler dead?
#define GVAR_BECOME_BLADE                 (135) // are you a Blade?
#define GVAR_BLADES_LEFT                  (136) // How many Blades are left
#define GVAR_RIPPERS_LEFT                 (137) // How many Rippers are left
#define GVAR_FIX_FARM                     (138) // Fix the underground Farm
#define GVAR_START_POWER                  (139) // has the power been started in the Glow?
#define GVAR_WEAPONS_ARMED                (140) // are the weapons armed in the Glow?
#define GVAR_FOUND_DISK                   (141) // have you found the access code disk?
#define GVAR_WEAPON_LOCKER                (142) // are the weapon depot security systems armed?
#define GVAR_SAVE_SINTHIA                 (143) // Cell baby held hostage in Junktown
#define GVAR_SAUL_QUEST                   (144) // some quest which still needs to be written
#define GVAR_TRISH_QUEST                  (145) // some quest not written yet
#define GVAR_VATS_ALERT                   (146) // are the Vats on Alert?
#define GVAR_VATS_COUNTDOWN               (147)
#define GVAR_FOLLOWERS_INVADED_DATE       (148)
#define GVAR_NECROPOLIS_INVADED_DATE      (149)
#define GVAR_THE_HUB_INVADED_DATE         (150)
#define GVAR_BROTHERHOOD_INVADED_DATE     (151)
#define GVAR_JUNKTOWN_INVADED_DATE        (152)
#define GVAR_SHADY_SANDS_INVADED_DATE     (153)
#define GVAR_VAULT_13_INVADED_DATE        (154)
#define GVAR_PLAYER_REPUATION             (155)
#define GVAR_BERSERKER_REPUTATION         (156)
#define GVAR_CHAMPION_REPUTATION          (157)
#define GVAR_CHILDKILLER_REPUATION        (158)
#define GVAR_GOOD_MONSTER                 (159)
#define GVAR_BAD_MONSTER                  (160)
#define GVAR_ARTIFACT_DISK                (161) // Brotherhood artifact disk
#define GVAR_FEV_DISK                     (162) // describes the FEV virus
#define GVAR_SECURITY_DISK                (163) // has the security code to lower weapons
#define GVAR_ALPHA_DISK                   (164) // experiment. random stuff
#define GVAR_DELTA_DISK                   (165) // just another experiment
#define GVAR_VREE_DISK                    (166) // has the autopsy of the Super Mutants
#define GVAR_HONOR_DISK                   (167) // has the honor code of the Brotherhood
#define GVAR_RENT_TIME                    (168) // how long the player rents the room
#define GVAR_SAUL_STATUS                  (169) // What is the status of Saul?
#define GVAR_GIZMO_STATUS                 (170) // How is Gizmo doing?
#define GVAR_GANGS                        (171)
#define GVAR_GANG_BEGONE                  (172)
#define GVAR_GANG_1                       (173)
#define GVAR_GANG_2                       (174)
#define GVAR_FOOLS_SCOUT                  (175)
#define GVAR_FSCOUT_1                     (176)
#define GVAR_CRYPTS_SCOUT                 (177)
#define GVAR_CSCOUT_1                     (178)
#define GVAR_POWER                        (179)
#define GVAR_POWER_GENERATOR              (180)
#define GVAR_GENERATOR_1                  (181)
#define GVAR_GENERATOR_2                  (182)
#define GVAR_GENERATOR_3                  (183)
#define GVAR_PEASANTS                     (184)
#define GVAR_DOG_PHIL                     (185)
#define GVAR_DOG_1                        (186)
#define GVAR_DOG_2                        (187)
#define GVAR_WATER_THIEF                  (188)
#define GVAR_NUKA_COLA_ADDICT             (189)
#define GVAR_BUFF_OUT_ADDICT              (190)
#define GVAR_MENTATS_ADDICT               (191)
#define GVAR_PSYCHO_ADDICT                (192)
#define GVAR_RADAWAY_ADDICT               (193)
#define GVAR_ALOCHOL_ADDICT               (194) // makes the names go together better
#define GVAR_CATHEDRAL_ENEMY              (195)
#define GVAR_MORPHEUS_KNOWN               (196)
#define GVAR_KNOW_NIGHTKIN                (197)
#define GVAR_PC_WANTED                    (198)
#define GVAR_CRIMSON_CARAVANS_STATUS      (199)
#define GVAR_WATER_MERCHANTS_STATUS       (200)
#define GVAR_FARGO_TRADERS_STATUS         (201)
#define GVAR_UNDERGROUND_STATUS           (202)
#define GVAR_DECKER_STATUS                (203)
#define GVAR_CC_JOB                       (204)
#define GVAR_WATER_JOB                    (205)
#define GVAR_FARGO_JOB                    (206)
#define GVAR_Loxley_known                 (207)
#define GVAR_MARK_DEATHCLAW               (208)
#define GVAR_MUTANT_DISK                  (209)
#define GVAR_BROTHER_HISTORY              (210)
#define GVAR_SOPHIA_DISK                  (211)
#define GVAR_MAXSON_DISK                  (212)
#define GVAR_TANDI_ESCAPE                 (213)
#define GVAR_RAID_LOOTING                 (214)
#define GVAR_CVAN_DRIVER                  (215)
#define GVAR_CVAN_GUARD                   (216)
#define GVAR_TANDI_HEREBEFORE             (217)
#define GVAR_TALKED_ABOUT_TANDI           (218)
#define GVAR_DECKER_KNOWN                 (219)
#define GVAR_WANTED_FOR_MURDER            (220)
#define GVAR_GREENE_DEAD                  (221)
#define GVAR_WANTED_THEFT                 (222)
#define GVAR_BROTHERHOOD_INVASION         (223)
#define GVAR_GLOW_POWER                   (224)
#define GVAR_HUB_FILLER_28                (225)
#define GVAR_HUB_FILLER_29                (226)
#define GVAR_HUB_FILLER_30                (227)
#define GVAR_NUM_RADIO                    (228)
#define GVAR_RADIO_MISTAKE                (229)
#define GVAR_CHANNEL_SLOT_DOWN            (230)
#define GVAR_MASTER_FILLER_4              (231)
#define GVAR_MASTER_FILLER_5              (232)
#define GVAR_MASTER_FILLER_6              (233)
#define GVAR_MASTER_FILLER_7              (234)
#define GVAR_MASTER_FILLER_8              (235)
#define GVAR_MASTER_FILLER_9              (236)
#define GVAR_MASTER_FILLER_10             (237)
#define GVAR_CALM_REBELS                  (238)
#define GVAR_CURE_JARVIS                  (239)
#define GVAR_MAKE_ANTIDOTE                (240)
#define GVAR_MORPHEUS_DELIVERS_PLAYER     (241)
#define GVAR_DESTROY_VATS                 (242)
#define GVAR_DESTROY_MASTER               (243)
#define GVAR_KATJA_STATUS                 (244)
#define GVAR_ENEMY_VAULT_13               (245)
#define GVAR_ENEMY_SHADY_SANDS            (246)
#define GVAR_ENEMY_JUNKTOWN               (247)
#define GVAR_ENEMY_HUB                    (248)
#define GVAR_ENEMY_NECROPOLIS             (249)
#define GVAR_ENEMY_BROTHERHOOD            (250)
#define GVAR_ENEMY_ADYTUM                 (251)
#define GVAR_ENEMY_RIPPERS                (252)
#define GVAR_ENEMY_BLADES                 (253)
#define GVAR_ENEMY_RAIDERS                (254)
#define GVAR_ENEMY_CATHEDRAL              (255)
#define GVAR_ENEMY_FOLLOWERS              (256)
#define GVAR_GENERIC_FILLER_20            (257)
#define GVAR_WATER_CHIP_1                 (258)
#define GVAR_WATER_CHIP_2                 (259)
#define GVAR_WATER_CHIP_3                 (260)
#define GVAR_WATER_CHIP_4                 (261)
#define GVAR_WATER_CHIP_5                 (262)
#define GVAR_WATER_CHIP_6                 (263)
#define GVAR_WATER_CHIP_7                 (264)
#define GVAR_WATER_CHIP_8                 (265)
#define GVAR_WATER_CHIP_9                 (266)
#define GVAR_WATER_CHIP_10                (267)
#define GVAR_WATER_CHIP_11                (268)
#define GVAR_WATER_CHIP_12                (269)
#define GVAR_WATER_CHIP_13                (270)
#define GVAR_WATER_CHIP_14                (271)
#define GVAR_WATER_CHIP_15                (272)
#define GVAR_DESTROY_VATS_1               (273)
#define GVAR_DESTROY_VATS_2               (274)
#define GVAR_DESTROY_VATS_3               (275)
#define GVAR_DESTROY_VATS_4               (276)
#define GVAR_DESTROY_VATS_5               (277)
#define GVAR_DESTROY_VATS_6               (278)
#define GVAR_DESTROY_VATS_7               (279)
#define GVAR_DESTROY_VATS_8               (280)
#define GVAR_DESTROY_VATS_9               (281)
#define GVAR_DESTROY_VATS_10              (282)
#define GVAR_DESTROY_VATS_11              (283)
#define GVAR_DESTROY_VATS_12              (284)
#define GVAR_DESTROY_VATS_13              (285)
#define GVAR_DESTROY_VATS_14              (286)
#define GVAR_DESTROY_VATS_15              (287)
#define GVAR_WATER_THIEF_1                (288)
#define GVAR_WATER_THIEF_2                (289)
#define GVAR_WATER_THIEF_3                (290)
#define GVAR_WATER_THIEF_4                (291)
#define GVAR_WATER_THIEF_5                (292)
#define GVAR_WATER_THIEF_6                (293)
#define GVAR_WATER_THIEF_7                (294)
#define GVAR_WATER_THIEF_8                (295)
#define GVAR_WATER_THIEF_9                (296)
#define GVAR_WATER_THIEF_10               (297)
#define GVAR_CALM_REBELS_1                (298)
#define GVAR_CALM_REBELS_2                (299)
#define GVAR_CALM_REBELS_3                (300)
#define GVAR_CALM_REBELS_4                (301)
#define GVAR_CALM_REBELS_5                (302)
#define GVAR_CALM_REBELS_6                (303)
#define GVAR_CALM_REBELS_7                (304)
#define GVAR_DESTROY_MASTER_1             (305)
#define GVAR_DESTROY_MASTER_2             (306)
#define GVAR_DESTROY_MASTER_3             (307)
#define GVAR_DESTROY_MASTER_4             (308)
#define GVAR_DESTROY_MASTER_5             (309)
#define GVAR_DESTROY_MASTER_6             (310)
#define GVAR_DESTROY_MASTER_7             (311)
#define GVAR_DESTROY_MASTER_8             (312)
#define GVAR_DESTROY_MASTER_9             (313)
#define GVAR_DESTROY_MASTER_10            (314)
#define GVAR_DESTROY_MASTER_11            (315)
#define GVAR_DESTROY_MASTER_12            (316)
#define GVAR_DESTROY_MASTER_13            (317)
#define GVAR_DESTROY_MASTER_14            (318)
#define GVAR_DESTROY_MASTER_15            (319)
#define GVAR_STOP_SCORPIONS_1             (320)
#define GVAR_STOP_SCORPIONS_2             (321)
#define GVAR_STOP_SCORPIONS_3             (322)
#define GVAR_STOP_SCORPIONS_4             (323)
#define GVAR_STOP_SCORPIONS_5             (324)
#define GVAR_STOP_SCORPIONS_6             (325)
#define GVAR_STOP_SCORPIONS_7             (326)
#define GVAR_STOP_SCORPIONS_8             (327)
#define GVAR_STOP_SCORPIONS_9             (328)
#define GVAR_STOP_SCORPIONS_10            (329)
#define GVAR_SAVE_TANDI_1                 (330)
#define GVAR_SAVE_TANDI_2                 (331)
#define GVAR_SAVE_TANDI_3                 (332)
#define GVAR_SAVE_TANDI_4                 (333)
#define GVAR_SAVE_TANDI_5                 (334)
#define GVAR_SAVE_TANDI_6                 (335)
#define GVAR_SAVE_TANDI_7                 (336)
#define GVAR_SAVE_TANDI_8                 (337)
#define GVAR_SAVE_TANDI_9                 (338)
#define GVAR_SAVE_TANDI_10                (339)
#define GVAR_CURE_JARVIS_1                (340)
#define GVAR_CURE_JARVIS_2                (341)
#define GVAR_CURE_JARVIS_3                (342)
#define GVAR_CURE_JARVIS_4                (343)
#define GVAR_CURE_JARVIS_5                (344)
#define GVAR_CURE_JARVIS_6                (345)
#define GVAR_CURE_JARVIS_7                (346)
#define GVAR_CURE_JARVIS_8                (347)
#define GVAR_CURE_JARVIS_9                (348)
#define GVAR_CURE_JARVIS_10               (349)
#define GVAR_MAKE_ANTIDOTE_1              (350)
#define GVAR_MAKE_ANTIDOTE_2              (351)
#define GVAR_MAKE_ANTIDOTE_3              (352)
#define GVAR_MAKE_ANTIDOTE_4              (353)
#define GVAR_MAKE_ANTIDOTE_5              (354)
#define GVAR_MAKE_ANTIDOTE_6              (355)
#define GVAR_MAKE_ANTIDOTE_7              (356)
#define GVAR_MAKE_ANTIDOTE_8              (357)
#define GVAR_MAKE_ANTIDOTE_9              (358)
#define GVAR_MAKE_ANTIDOTE_10             (359)
#define GVAR_KILL_MUTANTS_1               (360)
#define GVAR_KILL_MUTANTS_2               (361)
#define GVAR_KILL_MUTANTS_3               (362)
#define GVAR_KILL_MUTANTS_4               (363)
#define GVAR_KILL_MUTANTS_5               (364)
#define GVAR_KILL_MUTANTS_6               (365)
#define GVAR_KILL_MUTANTS_7               (366)
#define GVAR_KILL_MUTANTS_8               (367)
#define GVAR_KILL_MUTANTS_9               (368)
#define GVAR_KILL_MUTANTS_10              (369)
#define GVAR_FIX_NECROP_PUMP_1            (370)
#define GVAR_FIX_NECROP_PUMP_2            (371)
#define GVAR_FIX_NECROP_PUMP_3            (372)
#define GVAR_FIX_NECROP_PUMP_4            (373)
#define GVAR_FIX_NECROP_PUMP_5            (374)
#define GVAR_FIX_NECROP_PUMP_6            (375)
#define GVAR_FIX_NECROP_PUMP_7            (376)
#define GVAR_FIX_NECROP_PUMP_8            (377)
#define GVAR_FIX_NECROP_PUMP_9            (378)
#define GVAR_FIX_NECROP_PUMP_10           (379)
#define GVAR_KILL_KILLIAN_1               (380)
#define GVAR_KILL_KILLIAN_2               (381)
#define GVAR_KILL_KILLIAN_3               (382)
#define GVAR_KILL_KILLIAN_4               (383)
#define GVAR_KILL_KILLIAN_5               (384)
#define GVAR_KILL_KILLIAN_6               (385)
#define GVAR_KILL_KILLIAN_7               (386)
#define GVAR_KILL_KILLIAN_8               (387)
#define GVAR_KILL_KILLIAN_9               (388)
#define GVAR_KILL_KILLIAN_10              (389)
#define GVAR_STOP_GIZMO_1                 (390)
#define GVAR_STOP_GIZMO_2                 (391)
#define GVAR_STOP_GIZMO_3                 (392)
#define GVAR_STOP_GIZMO_4                 (393)
#define GVAR_STOP_GIZMO_5                 (394)
#define GVAR_STOP_GIZMO_6                 (395)
#define GVAR_STOP_GIZMO_7                 (396)
#define GVAR_STOP_GIZMO_8                 (397)
#define GVAR_STOP_GIZMO_9                 (398)
#define GVAR_STOP_GIZMO_10                (399)
#define GVAR_SAVE_SINTHIA_1               (400)
#define GVAR_SAVE_SINTHIA_2               (401)
#define GVAR_SAVE_SINTHIA_3               (402)
#define GVAR_SAVE_SINTHIA_4               (403)
#define GVAR_SAVE_SINTHIA_5               (404)
#define GVAR_SAVE_SINTHIA_6               (405)
#define GVAR_SAVE_SINTHIA_7               (406)
#define GVAR_SAVE_SINTHIA_8               (407)
#define GVAR_SAVE_SINTHIA_9               (408)
#define GVAR_SAVE_SINTHIA_10              (409)
#define GVAR_TRISH_QUEST_1                (410)
#define GVAR_TRISH_QUEST_2                (411)
#define GVAR_TRISH_QUEST_3                (412)
#define GVAR_TRISH_QUEST_4                (413)
#define GVAR_TRISH_QUEST_5                (414)
#define GVAR_TRISH_QUEST_6                (415)
#define GVAR_TRISH_QUEST_7                (416)
#define GVAR_TRISH_QUEST_8                (417)
#define GVAR_TRISH_QUEST_9                (418)
#define GVAR_TRISH_QUEST_10               (419)
#define GVAR_SAUL_QUEST_1                 (420)
#define GVAR_SAUL_QUEST_2                 (421)
#define GVAR_SAUL_QUEST_3                 (422)
#define GVAR_SAUL_QUEST_4                 (423)
#define GVAR_SAUL_QUEST_5                 (424)
#define GVAR_SAUL_QUEST_6                 (425)
#define GVAR_SAUL_QUEST_7                 (426)
#define GVAR_SAUL_QUEST_8                 (427)
#define GVAR_SAUL_QUEST_9                 (428)
#define GVAR_SAUL_QUEST_10                (429)
#define GVAR_STEAL_NECKLACE_1             (430)
#define GVAR_STEAL_NECKLACE_2             (431)
#define GVAR_STEAL_NECKLACE_3             (432)
#define GVAR_STEAL_NECKLACE_4             (433)
#define GVAR_STEAL_NECKLACE_5             (434)
#define GVAR_STEAL_NECKLACE_6             (435)
#define GVAR_STEAL_NECKLACE_7             (436)
#define GVAR_STEAL_NECKLACE_8             (437)
#define GVAR_STEAL_NECKLACE_9             (438)
#define GVAR_STEAL_NECKLACE_10            (439)
#define GVAR_KILL_JAIN_1                  (440)
#define GVAR_KILL_JAIN_2                  (441)
#define GVAR_KILL_JAIN_3                  (442)
#define GVAR_KILL_JAIN_4                  (443)
#define GVAR_KILL_JAIN_5                  (444)
#define GVAR_KILL_JAIN_6                  (445)
#define GVAR_KILL_JAIN_7                  (446)
#define GVAR_KILL_JAIN_8                  (447)
#define GVAR_KILL_JAIN_9                  (448)
#define GVAR_KILL_JAIN_10                 (449)
#define GVAR_KILL_MERCHANT_1              (450)
#define GVAR_KILL_MERCHANT_2              (451)
#define GVAR_KILL_MERCHANT_3              (452)
#define GVAR_KILL_MERCHANT_4              (453)
#define GVAR_KILL_MERCHANT_5              (454)
#define GVAR_KILL_MERCHANT_6              (455)
#define GVAR_KILL_MERCHANT_7              (456)
#define GVAR_KILL_MERCHANT_8              (457)
#define GVAR_KILL_MERCHANT_9              (458)
#define GVAR_KILL_MERCHANT_10             (459)
#define GVAR_DEATHCLAW_SEED_1             (460)
#define GVAR_DEATHCLAW_SEED_2             (461)
#define GVAR_DEATHCLAW_SEED_3             (462)
#define GVAR_DEATHCLAW_SEED_4             (463)
#define GVAR_DEATHCLAW_SEED_5             (464)
#define GVAR_DEATHCLAW_SEED_6             (465)
#define GVAR_DEATHCLAW_SEED_7             (466)
#define GVAR_DEATHCLAW_SEED_8             (467)
#define GVAR_DEATHCLAW_SEED_9             (468)
#define GVAR_FRY_DEAD                     (469)
#define GVAR_MISSING_CARAVAN_1            (470)
#define GVAR_MISSING_CARAVAN_2            (471)
#define GVAR_MISSING_CARAVAN_3            (472)
#define GVAR_MISSING_CARAVAN_4            (473)
#define GVAR_MISSING_CARAVAN_5            (474)
#define GVAR_MISSING_CARAVAN_6            (475)
#define GVAR_MISSING_CARAVAN_7            (476)
#define GVAR_MISSING_CARAVAN_8            (477)
#define GVAR_MISSING_CARAVAN_9            (478)
#define GVAR_MISSING_CARAVAN_10           (479)
#define GVAR_BECOME_INITIATE_1            (480)
#define GVAR_BECOME_INITIATE_2            (481)
#define GVAR_BECOME_INITIATE_3            (482)
#define GVAR_BECOME_INITIATE_4            (483)
#define GVAR_BECOME_INITIATE_5            (484)
#define GVAR_BECOME_INITIATE_6            (485)
#define GVAR_BECOME_INITIATE_7            (486)
#define GVAR_BECOME_INITIATE_8            (487)
#define GVAR_BECOME_INITIATE_9            (488)
#define GVAR_BECOME_INITIATE_10           (489)
#define GVAR_FIND_INITIATE_1              (490)
#define GVAR_FIND_INITIATE_2              (491)
#define GVAR_FIND_INITIATE_3              (492)
#define GVAR_FIND_INITIATE_4              (493)
#define GVAR_FIND_INITIATE_5              (494)
#define GVAR_FIND_INITIATE_6              (495)
#define GVAR_FIND_INITIATE_7              (496)
#define GVAR_FIND_INITIATE_8              (497)
#define GVAR_FIND_INITIATE_9              (498)
#define GVAR_FIND_INITIATE_10             (499)
#define GVAR_ROMEO_JULIET_1               (500)
#define GVAR_STOP_GANGS_1                 (501)
#define GVAR_STOP_GANGS_2                 (502)
#define GVAR_STOP_GANGS_3                 (503)
#define GVAR_STOP_GANGS_4                 (504)
#define GVAR_STOP_GANGS_5                 (505)
#define GVAR_STOP_GANGS_6                 (506)
#define GVAR_STOP_GANGS_7                 (507)
#define GVAR_STOP_GANGS_8                 (508)
#define GVAR_STOP_GANGS_9                 (509)
#define GVAR_CATCH_SPY_1                  (510)
#define GVAR_CATCH_SPY_2                  (511)
#define GVAR_CATCH_SPY_3                  (512)
#define GVAR_CATCH_SPY_4                  (513)
#define GVAR_CATCH_SPY_5                  (514)
#define GVAR_CATCH_SPY_6                  (515)
#define GVAR_CATCH_SPY_7                  (516)
#define GVAR_CATCH_SPY_8                  (517)
#define GVAR_CATCH_SPY_9                  (518)
#define GVAR_CATCH_SPY_10                 (519)
#define GVAR_CATCH_SPY_11                 (520)
#define GVAR_CATCH_SPY_12                 (521)
#define GVAR_CATCH_SPY_13                 (522)
#define GVAR_CATCH_SPY_14                 (523)
#define GVAR_CATCH_SPY_15                 (524)
#define GVAR_CATCH_SPY_16                 (525)
#define GVAR_CATCH_SPY_17                 (526)
#define GVAR_CATCH_SPY_18                 (527)
#define GVAR_CATCH_SPY_19                 (528)
#define GVAR_BECOME_BLADE_1               (529)
#define GVAR_BECOME_BLADE_2               (530)
#define GVAR_BECOME_BLADE_3               (531)
#define GVAR_BECOME_BLADE_4               (532)
#define GVAR_DELIVER_PACKAGE_1            (533)
#define GVAR_DELIVER_PACKAGE_2            (534)
#define GVAR_DELIVER_PACKAGE_3            (535)
#define GVAR_DELIVER_PACKAGE_4            (536)
#define GVAR_DELIVER_PACKAGE_5            (537)
#define GVAR_FIX_FARM_1                   (538)
#define GVAR_FIX_FARM_2                   (539)
#define GVAR_FIX_FARM_3                   (540)
#define GVAR_FIX_FARM_4                   (541)
#define GVAR_LOST_BROTHER_1               (542)
#define GVAR_LOST_BROTHER_2               (543)
#define GVAR_LOST_BROTHER_3               (544)
#define GVAR_LOST_BROTHER_4               (545)
#define GVAR_LOST_BROTHER_5               (546)
#define GVAR_POWER_GLOW_1                 (547)
#define GVAR_DISARM_TRAPS_1               (548)
#define GVAR_DISARM_TRAPS_2               (549)
#define GVAR_DISARM_TRAPS_3               (550)
#define GVAR_MAX_MUTANTS                  (551)
#define GVAR_TIME_CHIP_GONE               (552)
#define GVAR_SET_DEAD                     (553)
#define GVAR_MUTANTS_GONE                 (554)
#define GVAR_BUST_SKULZ                   (555) // Helping Lars to bust the Skulz gang in Junktown
#define GVAR_SHERRY_TURNS                 (556) // Sherry gives information on the Skulz.
#define GVAR_TRISH_STATUS                 (557) // Tells if dude has met Trish in Junktown.
#define GVAR_MARK_V13_1                   (558)
#define GVAR_MARK_V13_2                   (559)
#define GVAR_MARK_V13_3                   (560)
#define GVAR_MARK_V13_4                   (561)
#define GVAR_MARK_V15_1                   (562)
#define GVAR_MARK_V15_2                   (563)
#define GVAR_MARK_V15_3                   (564)
#define GVAR_MARK_V15_4                   (565)
#define GVAR_MARK_SHADY_1                 (566)
#define GVAR_MARK_SHADY_2                 (567)
#define GVAR_MARK_SHADY_3                 (568)
#define GVAR_MARK_JUNK_1                  (569)
#define GVAR_MARK_JUNK_2                  (570)
#define GVAR_MARK_JUNK_3                  (571)
#define GVAR_MARK_RAIDERS_1               (572)
#define GVAR_MARK_NECROP_1                (573)
#define GVAR_MARK_NECROP_2                (574)
#define GVAR_MARK_NECROP_3                (575)
#define GVAR_MARK_HUB_1                   (576)
#define GVAR_MARK_HUB_2                   (577)
#define GVAR_MARK_HUB_3                   (578)
#define GVAR_MARK_HUB_4                   (579)
#define GVAR_MARK_HUB_5                   (580)
#define GVAR_MARK_HUB_6                   (581)
#define GVAR_MARK_BROTHER_1               (582)
#define GVAR_MARK_BROTHER_2               (583)
#define GVAR_MARK_BROTHER_3               (584)
#define GVAR_MARK_BROTHER_4               (585)
#define GVAR_MARK_BROTHER_5               (586)
#define GVAR_MARK_BASE_1                  (587)
#define GVAR_MARK_BASE_2                  (588)
#define GVAR_MARK_BASE_3                  (589)
#define GVAR_MARK_BASE_4                  (590)
#define GVAR_MARK_BASE_5                  (591)
#define GVAR_MARK_GLOW_1                  (592)
#define GVAR_MARK_GLOW_2                  (593)
#define GVAR_MARK_LA_1                    (594)
#define GVAR_MARK_LA_2                    (595)
#define GVAR_MARK_LA_3                    (596)
#define GVAR_MARK_LA_4                    (597)
#define GVAR_MARK_LA_5                    (598)
#define GVAR_MARK_CHILD_1                 (599)
#define GVAR_MARK_CHILD_2                 (600)
#define GVAR_STRANGER_STATUS              (601)
#define GVAR_GAME_DIFFICULTY              (602)
#define GVAR_RUNNING_BURNING_GUY          (603)
#define GVAR_ARADESH_STATUS               (604)
#define GVAR_RHOMBUS_STATUS               (605)
#define GVAR_KIND_TO_HAROLD               (606)
#define GVAR_GARRET_STATUS                (607)
#define GVAR_RADIO_COMPUTER_OFF           (608)
#define GVAR_FORCE_FIELDS_OFF             (609)
#define GVAR_FIELD_COMPUTER_MODIFIED      (610)
#define GVAR_GARLS_FRIEND                 (611)
#define GVAR_ZIMMERMAN                    (612) // Mikey's stuff for Boneyard.
#define GVAR_BLADES                       (613)
#define GVAR_GUN_RUNNER                   (614)
#define GVAR_CHEMISTRY_BOOK               (615)
#define GVAR_ENEMY_REGULATOR              (616)
#define GVAR_ENEMY_BLADE                  (617)

// TeamX

#define GVAR_IAN_LEVEL                    (618)
#define GVAR_IAN_DUDE_LAST_LEVEL          (619)
#define GVAR_KATYA_LEVEL                  (620)
#define GVAR_KATYA_DUDE_LAST_LEVEL        (621)
#define GVAR_TYCHO_LEVEL                  (622)
#define GVAR_TYCHO_DUDE_LAST_LEVEL        (623)
#define GVAR_LARS_DEAD                    (624)
#define GVAR_LARS_N_KILLIAN_ON_CASINO     (625)
#define GVAR_ENEMY_SKULZ                  (626)
#define GVAR_ENEMY_JUNK_BOXER             (627)
#define GVAR_ENEMY_JUNK_CITIZEN           (628)

#endif // __GLOBAL__ //
