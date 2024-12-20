#pragma once

/*********************************************************
 define file for AI Packets.

 All defines in this file are to be prepended with AI_

 Contents of the File:
        I.      Team Numbers
*********************************************************/

#define AI_PLAYER                   (0)
#define AI_BERZERKER                (1)
#define AI_CAREFUL                  (2)
#define AI_COW                      (3)
#define AI_GUARD                    (4)
#define AI_LOSER                    (5)
#define AI_PEASANT                  (6)
#define AI_SUPER_MUTANT             (7)
#define AI_DOG                      (8)
#define AI_GHOUL                    (9)
#define AI_MUTANT_GUARDS            (10)
#define AI_BOUNCER                  (11)
#define AI_RATS                     (12)
#define AI_MOLE_RATS                (13)
#define AI_RADSCORPION              (14)
#define AI_GUARD_GUNG_HO            (15)
#define AI_GUARD_SADISTIC           (16)
#define AI_GUARD_HUMOROUS           (17)
#define AI_GUARD_QUIET              (18)
#define AI_GUARD_SMARTASS           (19)
#define AI_GENERIC_RAIDER           (20)
#define AI_RAIDER_GUARD             (21)
#define AI_RAIDER_LEADER            (22)
#define AI_SHADY_SANDS_PEASANT      (23)
#define AI_SHADY_SANDS_GUARD        (24)
#define AI_SHADY_SANDS_LEADER       (25)
#define AI_RIPPERS                  (26)
#define AI_BLADES                   (27)
#define AI_GUNRUNNERS               (28)
#define AI_REGULATORS               (29)
#define AI_ADYTOWNER                (30)
#define AI_GENERIC_FOLLOWER         (31)
#define AI_FOLLOWER_SCOUT           (32)
#define AI_FOLLOWER_GUARD           (33)
#define AI_FOLLOWER_LEADER          (34)
#define AI_RIPPER_LEADER            (35)
#define AI_BLADE_SCOUT              (36)
#define AI_BLADE_LEADER             (37)
#define AI_GUNRUNNER_LEADER         (38)
#define AI_ADYTUM_LEADER            (39)
#define AI_GHOUL_COWARD             (40)
#define AI_GHOUL_NORMAL             (41)
#define AI_GHOUL_BRAVE              (42)
#define AI_GARL_HONOR               (43)
#define AI_PIG_RATS                 (44) // Was AI_EMPTY_SLOT_1, but wanrats script is using this?
#define AI_EMPTY_SLOT_2             (45)
#define AI_SUPER_MUTANT_GUARD       (46)
#define AI_SUPER_MUTANT_NORMAL      (47)
#define AI_SUPER_MUTANT_AGGRESSIVE  (48)
#define AI_SUPER_MUTANT_SGT         (49)
#define AI_MERCHANT                 (50)
#define AI_HUB_PEASANTS             (51)
#define AI_HUB_THIEF                (52)
#define AI_HUB_MUTANTS              (53)
#define AI_DEATHCLAW                (54)
#define AI_JUNKTOWN_PEASANT         (55)
#define AI_JUNKTOWN_GUARD           (56)
#define AI_KILLIAN                  (57)
#define AI_JUNKTOWN_THUG            (58)
#define AI_SKULZ                    (59)
#define AI_GIZMO                    (60)
#define AI_SELLBABIES               (61)
#define AI_BROTHERHOOD_INITIATE     (62)
#define AI_BROTHERHOOD_SCRIBE       (63)
#define AI_BROTHERHOOD_KNIGHT       (64)
#define AI_BROTHERHOOD_PALADIN      (65)
#define AI_NIGHTKIN                 (66)
#define AI_BRAINWASHED_CHILDREN     (67)
#define AI_LITTLE_KIDS              (68)
#define AI_CHILDREN_TRUE            (69)
#define AI_MASTER                   (70)
#define AI_ROBOTS                   (71)
#define AI_CENTAUR                  (72)
#define AI_FLOATER                  (73)
#define AI_EYEBALL                  (74)
#define AI_MARCELLES                (75)
#define AI_GUARD_ROOKIE             (76)
#define AI_COC_HUB_BRAINWASHED      (77)
#define AI_GHOUL_NASTY              (78)
#define AI_SUPER_MUTANT_NECRO       (79)
#define AI_BOS_ELDERS               (80)
#define AI_BOS_RHOMBUS              (81)
#define AI_COC_MORPHEUS             (82)
#define AI_COC_LASHER               (83)
#define AI_COC_JAIN                 (84)
#define AI_HUB_UNDERGROUND          (85)
#define AI_HUB_POLICE               (86)
#define AI_DECKER                   (87)
#define AI_KAIN                     (88)
#define AI_IAN                      (89) // DEPRECATED!
#define AI_TYCHO                    (90) // DEPRECATED!
#define AI_VAULTDWELLER             (91)
#define AI_STRANGER                 (92)
#define AI_GHOUL_MINDLESS           (93)
#define AI_RUNAWAY                  (94)

#define AI_PARTY_IAN_BERSERK     (95)
#define AI_PARTY_IAN_AGGRESSIVE     (96)
#define AI_PARTY_IAN_DEFENSIVE      (97)
#define AI_PARTY_IAN_COWARD         (98)
#define AI_PARTY_IAN_CUSTOM         (99)

#define AI_PARTY_TYCHO_BERSERK      (100)
#define AI_PARTY_TYCHO_AGGRESSIVE   (101)
#define AI_PARTY_TYCHO_DEFENSIVE (102)
#define AI_PARTY_TYCHO_COWARD    (103)
#define AI_PARTY_TYCHO_CUSTOM    (104)

#define AI_KATJA              (105) // DEPRECATED!
#define AI_PARTY_KATJA_BERSERK      (106)
#define AI_PARTY_KATJA_AGGRESSIVE   (107)
#define AI_PARTY_KATJA_DEFENSIVE (108)
#define AI_PARTY_KATJA_COWARD    (109)
#define AI_PARTY_KATJA_CUSTOM    (110)

#define AI_TANDI              (111) // DEPRECATED!
#define AI_PARTY_TANDI_BERSERK      (112) // unused
#define AI_PARTY_TANDI_AGGRESSIVE   (113) // unused
#define AI_PARTY_TANDI_DEFENSIVE (114) // unused
#define AI_PARTY_TANDI_COWARD    (115) // unused
#define AI_PARTY_TANDI_CUSTOM    (116) // unused

#define AI_DOGMEAT               (117) // DEPRECATED!
#define AI_PARTY_DOGMEAT_BERSERK (118)
#define AI_PARTY_DOGMEAT_AGGRESSIVE (119)
#define AI_PARTY_DOGMEAT_DEFENSIVE  (120)
#define AI_PARTY_DOGMEAT_COWARD     (121)
#define AI_PARTY_DOGMEAT_CUSTOM     (122)

#define AI_MYSTERIOUS_STRANGER      (123)

#define AI_PARTY_MRHANDY_BERSERK (124)
#define AI_PARTY_MRHANDY_AGGRESSIVE (125)
#define AI_PARTY_MRHANDY_DEFENSIVE  (126)
#define AI_PARTY_MRHANDY_COWARD     (127)
#define AI_PARTY_MRHANDY_CUSTOM     (128)

#define AI_SPORE_PLANT              (129) // 5
#define AI_TOUGH_BOT                (130) // 32
#define AI_GECKO                    (131) // 26
