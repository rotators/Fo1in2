
#ifndef DEFINE_EXTRA_H
#define DEFINE_EXTRA_H

/* Combat Flags */
#define DAM_PRESERVE_FLAGS	0x80000000 // keeping the existing result flags when sets new flags in the attack_complex function (for sfall)

#define BODY_HIT_HEAD       (0)
#define BODY_HIT_LEFT_ARM   (1)
#define BODY_HIT_RIGHT_ARM  (2)
#define BODY_HIT_TORSO      (3)
#define BODY_HIT_RIGHT_LEG  (4)
#define BODY_HIT_LEFT_LEG   (5)
#define BODY_HIT_EYES       (6)
#define BODY_HIT_GROIN      (7)
#define BODY_UNCALLED       (8)

#define OBJ_TYPE_ITEM       (0)
#define OBJ_TYPE_CRITTER    (1)
#define OBJ_TYPE_SCENERY    (2)
#define OBJ_TYPE_WALL       (3)
#define OBJ_TYPE_TILE       (4)
#define OBJ_TYPE_MISC       (5)
#define OBJ_TYPE_SPATIAL    (6)

#define ART_TYPE_INTERFACE  (6)
#define ART_TYPE_INVENT     (7)
#define ART_TYPE_HEADS      (8)
#define ART_TYPE_BACKGRND   (9)
#define ART_TYPE_SKILLDEX   (10)

#define WEAPON_TYPE_NONE    (0)
#define WEAPON_TYPE_UNARMED (1)
#define WEAPON_TYPE_MELEE   (2)
#define WEAPON_TYPE_THROWN  (3)
#define WEAPON_TYPE_GUNS    (4)

/* Item Common Flags */
#define HIDDEN_ITEM     134217728  // 0x08000000 - Hidden Item

#define ITEM_ACTION_USE      2048  // 0x00000800 - Use (can be used)
#define ITEM_ACTION_USEON    4096  // 0x00001000 - Use On Smth (can be used on anything)
#define ITEM_ACTION_PICKUP  32768  // 0x00008000 - PickUp

#define WEAPON_BIGGUN         256  // 0x00000100 - Big Gun
#define WEAPON_2HAND          512  // 0x00000200 - 2Hnd (weapon is two-handed)
#define WEAPON_ENERGY        1024  // 0x00000400 - Energy Weapon (forces weapon to use Energy Weapons skill)

#define ATKMODE_PRI_NONE        0
#define ATKMODE_PRI_PUNCH       1  // 0001
#define ATKMODE_PRI_KICK        2  // 0010
#define ATKMODE_PRI_SWING       3  // 0011
#define ATKMODE_PRI_THRUST      4  // 0100
#define ATKMODE_PRI_THROW       5  // 0101
#define ATKMODE_PRI_SINGLE      6  // 0110
#define ATKMODE_PRI_BURST       7  // 0111
#define ATKMODE_PRI_FLAME       8  // 1000
#define ATKMODE_SEC_NONE        0
#define ATKMODE_SEC_PUNCH      16  // 0x00000010
#define ATKMODE_SEC_KICK       32  // 0x00000020
#define ATKMODE_SEC_SWING      48  // 0x00000030
#define ATKMODE_SEC_THRUST     64  // 0x00000040
#define ATKMODE_SEC_THROW      80  // 0x00000050
#define ATKMODE_SEC_SINGLE     96  // 0x00000060
#define ATKMODE_SEC_BURST     112  // 0x00000070
#define ATKMODE_SEC_FLAME     128  // 0x00000080

/* Object flags for get/set_flags */
#define FLAG_MOUSE_3D            (0x1)
#define FLAG_WALKTHRU            (0x4)
#define FLAG_FLAT                (0x8)
#define FLAG_NOBLOCK            (0x10)
#define FLAG_LIGHTING           (0x20)
#define FLAG_TEMP              (0x400)
#define FLAG_MULTIHEX          (0x800)
#define FLAG_NOHIGHLIGHT      (0x1000)
#define FLAG_USED             (0x2000)
#define FLAG_TRANSRED         (0x4000)
#define FLAG_TRANSNONE        (0x8000)
#define FLAG_TRANSWALL       (0x10000)
#define FLAG_TRANSGLASS      (0x20000)
#define FLAG_TRANSSTEAM      (0x40000)
#define FLAG_TRANSENERGY     (0x80000)
#define FLAG_LEFT_HAND     (0x1000000)
#define FLAG_RIGHT_HAND    (0x2000000)
#define FLAG_WORN          (0x4000000)
#define FLAG_HIDDENITEM    (0x8000000)
#define FLAG_WALLTRANSEND (0x10000000)
#define FLAG_LIGHTTHRU    (0x20000000)
#define FLAG_SEEN         (0x40000000)
#define FLAG_SHOOTTHRU    (0x80000000)

/* Critter flags */
#define CFLG_BARTER             2  // 0x00000002 - Barter (can trade with)
#define CFLG_NOSTEAL           32  // 0x00000020 - Steal (cannot be stolen from)
#define CFLG_NODROP            64  // 0x00000040 - Drop (doesn't drop items)
#define CFLG_NOLIMBS          128  // 0x00000080 - Limbs (cannot lose limbs)
#define CFLG_NOAGES           256  // 0x00000100 - Ages (dead body does not disappear)
#define CFLG_NOHEAL           512  // 0x00000200 - Heal (damage is not healed with time)
#define CFLG_INVULN          1024  // 0x00000400 - Invulnerable (cannot be hurt)
#define CFLG_FLATTN          2048  // 0x00000800 - Flatten (leaves no dead body)
#define CFLG_SPECIAL         4096  // 0x00001000 - Special (has a special type of death)
#define CFLG_RANGED          8192  // 0x00002000 - Range (has extra hand-to-hand range)
#define CFLG_NOKNOCKBACK    16384  // 0x00004000 - Knock (cannot be knocked back)
#define CFLG_NOKNOCKDOWN    CFLG_NOKNOCKBACK  // obsolete

/* Window flags */
#define WIN_FLAG_DONTMOVE           (0x2) // does not move the window to the foreground when clicking on the window
#define WIN_FLAG_MOVEONTOP          (0x4) // places a window on top of other windows
#define WIN_FLAG_HIDDEN             (0x8) // hidden window 
#define WIN_FLAG_EXCLUSIVE         (0x10)
#define WIN_FLAG_TRANSPARENT       (0x20) // transparent window flag, the window color with index 0 will be transparent

/* Message window flags */
#define MSGBOX_AUTOSIZE             (0x0)
#define MSGBOX_NORMAL               (0x1)
#define MSGBOX_SMALL                (0x2)
#define MSGBOX_ALIGN_LEFT           (0x4) // text aligned to left
#define MSGBOX_ALIGN_TOP            (0x8) // text aligned to top
#define MSGBOX_YESNO               (0x10) // use YES/NO buttons instead of DONE
#define MSGBOX_CLEAN               (0x20) // no buttons

//remove inven obj defines
#define RMOBJ_CONSUME_DRUG        4666772
#define RMOBJ_CONTAINER           4683293  // same as RMOBJ_TRADE
#define RMOBJ_USE_OBJ             4666865
#define RMOBJ_EQUIP_ARMOR         4658121
#define RMOBJ_EQUIP_WEAPON        4658675
#define RMOBJ_UNLOAD_WEAPON       4667030
//#define RMOBJ_LOAD_WEAPON       4831349  // same as RMOBJ_DROP
#define RMOBJ_USE_DRUG_ON         4834866
#define RMOBJ_STEAL_VIEW          4668206
//#define RMOBJ_DROP_DYNAMITE     4666865  // same as USE_OBJ
#define RMOBJ_ITEM_DESTROYED      4543215
#define RMOBJ_ITEM_REMOVED        4548572
#define RMOBJ_ARMOR_EQUIPED       4651961
#define RMOBJ_LEFT_HAND_EQUIPED   4651899
#define RMOBJ_RIGHT_HAND_EQUIPED  4651934
#define RMOBJ_RM_MULT_OBJS        4563866
#define RMOBJ_REPLACE_WEAPON      4658526
#define RMOBJ_THROW               4266040
#define RMOBJ_SUB_CONTAINER       4683191  // search and remove the item from nested containers in the inventory

// common prototype offsets for get/set_proto_data
#define PROTO_PID             (1)
#define PROTO_TEXTID          (4)
#define PROTO_FID             (8)
#define PROTO_LDIST          (12)
#define PROTO_LINT           (16)
#define PROTO_FLAG           (20)
#define PROTO_FLAG_EXT       (24)
#define PROTO_SCRIPTID       (28)

// items
#define PROTO_IT_LDIST       PROTO_LDIST
#define PROTO_IT_LINT        PROTO_LINT
#define PROTO_IT_FLAG        PROTO_FLAG
#define PROTO_IT_FLAGS       PROTO_FLAG_EXT
#define PROTO_IT_SCRIPTID    PROTO_SCRIPTID
#define PROTO_IT_TYPE        (32)
#define PROTO_IT_MATERIAL   (108)
#define PROTO_IT_SIZE       (112)
#define PROTO_IT_WEIGHT     (116)
#define PROTO_IT_COST       (120)
#define PROTO_IT_INV_FID    (124)
#define PROTO_IT_SOUND      (128)  // byte

// weapons
#define PROTO_WP_ANIM        (36)
#define PROTO_WP_DMG_MIN     (40)
#define PROTO_WP_DMG_MAX     (44)
#define PROTO_WP_DMG_TYPE    (48)
#define PROTO_WP_RANGE_1     (52)
#define PROTO_WP_RANGE_2     (56)
#define PROTO_WP_PROJ_PID    (60)
#define PROTO_WP_MIN_ST      (64)
#define PROTO_WP_APCOST_1    (68)
#define PROTO_WP_APCOST_2    (72)
#define PROTO_WP_CRIT_FAIL   (76)
#define PROTO_WP_PERK        (80)
#define PROTO_WP_BURST       (84)
#define PROTO_WP_CALIBER     (88)
#define PROTO_WP_AMMO_PID    (92)
#define PROTO_WP_MAG_SIZE    (96)
#define PROTO_WP_SOUND      (100)

// armor
#define PROTO_AR_AC           (36)
#define PROTO_AR_DR_NORMAL    (40)
#define PROTO_AR_DR_LASER     (44)
#define PROTO_AR_DR_FIRE      (48)
#define PROTO_AR_DR_PLASMA    (52)
#define PROTO_AR_DR_ELECTRICAL   (56)
#define PROTO_AR_DR_EMP       (60)
#define PROTO_AR_DR_EXPLOSION (64)
#define PROTO_AR_DT_NORMAL    (68)
#define PROTO_AR_DT_LASER     (72)
#define PROTO_AR_DT_FIRE      (76)
#define PROTO_AR_DT_PLASMA    (80)
#define PROTO_AR_DT_ELECTRICAL   (84)
#define PROTO_AR_DT_EMP       (88)
#define PROTO_AR_DT_EXPLOSION (92)
#define PROTO_AR_PERK         (96)
#define PROTO_AR_FID_MALE    (100)
#define PROTO_AR_FID_FEMALE  (104)

// containers
#define PROTO_CN_MAX_SIZE     (36)
#define PROTO_CN_FLAGS        (40)

// ammo
#define PROTO_AM_CALIBER      (36)
#define PROTO_AM_PACK_SIZE    (40)
#define PROTO_AM_AC_MOD       (44)
#define PROTO_AM_DR_MOD       (48)
#define PROTO_AM_DMG_MULT     (52)
#define PROTO_AM_DMG_DIV      (56)

// misc items
#define PROTO_MI_POWER_PID    (36)
#define PROTO_MI_CALIBER      (40)
#define PROTO_MI_CHARGES      (44)

// drugs
#define PROTO_DR_STAT_A          (36)
#define PROTO_DR_STAT_B          (40)
#define PROTO_DR_STAT_C          (44)
#define PROTO_DR_AMOUNT_1_A      (48)
#define PROTO_DR_AMOUNT_1_B      (52)
#define PROTO_DR_AMOUNT_1_C      (56)
#define PROTO_DR_DURATION_1      (60)
#define PROTO_DR_AMOUNT_2_A      (64)
#define PROTO_DR_AMOUNT_2_B      (68)
#define PROTO_DR_AMOUNT_2_C      (72)
#define PROTO_DR_DURATION_2      (76)
#define PROTO_DR_AMOUNT_3_A      (80)
#define PROTO_DR_AMOUNT_3_B      (84)
#define PROTO_DR_AMOUNT_3_C      (88)
#define PROTO_DR_ADDICT_CHANCE   (92)
#define PROTO_DR_ADDICT_PERK     (96)
#define PROTO_DR_ADDICT_DELAY   (100)

// critters
#define PROTO_CR_FLAGS                   (32)  // Critter Flags
#define PROTO_CR_BONUS_SRENGTH          (176)
#define PROTO_CR_BONUS_PRCEPTION        (180)
#define PROTO_CR_BONUS_ENDURANCE        (184)
#define PROTO_CR_BONUS_CHARISMA         (188)
#define PROTO_CR_BONUS_INTELLIGENCE     (192)
#define PROTO_CR_BONUS_AGILITY          (196)
#define PROTO_CR_BONUS_LUCK             (200)
#define PROTO_CR_BONUS_HP               (204)
#define PROTO_CR_BONUS_AP               (208)
#define PROTO_CR_BONUS_AC               (212)
#define PROTO_CR_BONUS_UNARMED_DAMAGE   (216)
#define PROTO_CR_BONUS_MELEE_DAMAGE     (220)
#define PROTO_CR_BONUS_CARRY_WEIGHT     (224)
#define PROTO_CR_BONUS_SEQUENCE         (228)
#define PROTO_CR_BONUS_HEALING_RATE     (232)
#define PROTO_CR_BONUS_CRITICAL_CHANCE  (236)
#define PROTO_CR_BONUS_BETTER_CRITICALS (240)
#define PROTO_CR_BODY_TYPE              (388)
#define PROTO_CR_KILL_EXP               (392)
#define PROTO_CR_KILL_TYPE              (396)
#define PROTO_CR_DMG_TYPE               (400)
#define PROTO_CR_HEAD_FID               (404)
#define PROTO_CR_AI_PACKET              (408)
#define PROTO_CR_TEAM_NUM               (412)

// weapon calibers
#define CALIBER_NONE                 (0)
#define CALIBER_ROCKET               (1)
#define CALIBER_FLAMER_FUEL          (2)
#define CALIBER_SMALL_ENERGY_CELL    (3)
#define CALIBER_MICRO_FUSION_CELL    (4)
#define CALIBER_223                  (5)
#define CALIBER_5MM                  (6)
#define CALIBER_40                   (7)
#define CALIBER_10MM                 (8)
#define CALIBER_44                   (9)
#define CALIBER_14MM                (10)
#define CALIBER_12_GAUGE            (11)
#define CALIBER_9MM                 (12)
#define CALIBER_BB                  (13)
#define CALIBER_45                  (14)
#define CALIBER_2MM                 (15)
#define CALIBER_4_7MM_CASELESS      (16)
#define CALIBER_HN_NEEDLER          (17)
#define CALIBER_7_62MM              (18)

// hidden perks
#define PERK_add_nuka               (53)
#define PERK_add_buffout            (54)
#define PERK_add_mentats            (55)
#define PERK_add_psycho             (56)
#define PERK_add_radaway            (57)
#define PERK_weapon_long_range      (58)
#define PERK_weapon_accurate        (59)
#define PERK_weapon_penetrate       (60)
#define PERK_weapon_knockback       (61)
#define PERK_armor_powered          (62)
#define PERK_armor_combat           (63)
#define PERK_weapon_scope_range     (64)
#define PERK_weapon_fast_reload     (65)
#define PERK_weapon_night_sight     (66)
#define PERK_weapon_flameboy        (67)
#define PERK_armor_advanced_1       (68)
#define PERK_armor_advanced_2       (69)
#define PERK_add_jet                (70)
#define PERK_add_tragic             (71)
#define PERK_armor_charisma         (72)

#define WPN_ANIM_NONE               (0x00) // (A)
#define WPN_ANIM_KNIFE              (0x01) // (D)
#define WPN_ANIM_CLUB               (0x02) // (E)
#define WPN_ANIM_SLEDGEHAMMER       (0x03) // (F)
#define WPN_ANIM_SPEAR              (0x04) // (G)
#define WPN_ANIM_PISTOL             (0x05) // (H)
#define WPN_ANIM_SMG                (0x06) // (I)
#define WPN_ANIM_RIFLE              (0x07) // (J)
#define WPN_ANIM_BIG_GUN            (0x08) // (K)
#define WPN_ANIM_MINIGUN            (0x09) // (L)
#define WPN_ANIM_ROCKET_LAUNCHER    (0x0A) // (M)

// AI data parameters
#define AI_CAP_AGGRESSION              (0)
#define AI_CAP_AREA_ATTACK_MODE        (1)
#define AI_CAP_ATTACK_WHO              (2)
#define AI_CAP_BEST_WEAPON             (3)
#define AI_CAP_CHEM_USE                (4)
#define AI_CAP_DISPOSITION             (5)
#define AI_CAP_DISTANCE                (6)
#define AI_CAP_MAX_DISTANCE            (7)
#define AI_CAP_MIN_HP                  (8)
#define AI_CAP_MIN_TO_HIT              (9)
#define AI_CAP_HURT_TOO_MUCH          (10) // DAM_BLIND/DAM_CRIP_* flags
#define AI_CAP_RUN_AWAY_MODE          (11)
#define AI_CAP_SECONDARY_FREQ         (12)
#define AI_CAP_CALLED_FREQ            (13)
#define AI_CAP_CHEM_PRIMARY_DESIRE    (14) // array pid list

// AI attack area mode values
#define ai_area_always                 (0)
#define ai_area_sometimes              (1)
#define ai_area_be_sure                (2)
#define ai_area_be_careful             (3)
#define ai_area_be_absolutely_sure     (4)

// AI attack who mode values
#define ai_attack_whomever_attacking_me (0)
#define ai_attack_strongest            (1)
#define ai_attack_weakest              (2)
#define ai_attack_whomever             (3)
#define ai_attack_closest              (4)

// AI run away mode values
#define ai_run_away_none               (0)
#define ai_run_away_coward             (1)
#define ai_run_away_finger_hurts       (3)
#define ai_run_away_bleeding           (4)
#define ai_run_away_not_feeling_good   (5)
#define ai_run_away_tourniquet         (6)
#define ai_run_away_never              (7)

// AI disposition values
#define ai_disposition_none            (-1)
#define ai_disposition_custom          (0)
#define ai_disposition_coward          (1)
#define ai_disposition_defensive       (2)
#define ai_disposition_aggressive      (3)
#define ai_disposition_berserk         (4)

// AI distance values
#define ai_distance_stay_close         (0)
#define ai_distance_charge             (1)
#define ai_distance_snipe              (2)
#define ai_distance_on_your_own        (3)
#define ai_distance_stay               (4)

// AI best weapon pref values
#define ai_weapon_no_pref              (0)
#define ai_weapon_melee                (1)
#define ai_weapon_melee_over_ranged    (2)
#define ai_weapon_ranged_over_melee    (3)
#define ai_weapon_ranged               (4)
#define ai_weapon_unarmed              (5)
#define ai_weapon_unarmed_over_thrown  (6)
#define ai_weapon_random               (7)

// AI chem use mode values
#define ai_chem_clean                  (0)
#define ai_chem_stims_when_hurt_little (1) // use only stimpak/super stimpak/healing powder
#define ai_chem_stims_when_hurt_lots   (2) // use only stimpak/super stimpak/healing powder
#define ai_chem_sometimes              (3)
#define ai_chem_anytime                (4)
#define ai_chem_always                 (5)

// common object data offsets
#define OBJ_DATA_ID                 (0x00)
#define OBJ_DATA_TILENUM            (0x04)
#define OBJ_DATA_CUR_FRM            (0x18) // current frame number
#define OBJ_DATA_ROTATION           (0x1C)
#define OBJ_DATA_FID                (0x20)
#define OBJ_DATA_ELEVATION          (0x28)
#define OBJ_DATA_PID                (0x64)
#define OBJ_DATA_CID                (0x68) // combat ID, used for savegame
#define OBJ_DATA_SID                (0x78) // script ID
#define OBJ_DATA_SCRIPT_INDEX       (0x80) // script index number in scripts.lst
// items
#define OBJ_DATA_CUR_CHARGES        (0x3C) // for key items it's the key code
// critters
#define OBJ_DATA_COMBAT_STATE       (0x3C) // flags: 1 - combat, 2 - target is out of range, 4 - flee
#define OBJ_DATA_CUR_ACTION_POINT   (0x40)
#define OBJ_DATA_DAMAGE_LAST_TURN   (0x48)
#define OBJ_DATA_WHO_HIT_ME         (0x54) // current target of the critter

// compute attack result data offsets
#define C_ATTACK_SOURCE             (0x00)
#define C_ATTACK_HIT_MODE           (0x04)
#define C_ATTACK_WEAPON             (0x08)
#define C_ATTACK_UNUSED             (0x0C)
#define C_ATTACK_DAMAGE_SOURCE      (0x10) // Amount
#define C_ATTACK_FLAGS_SOURCE       (0x14) // see DAM_* values in define.h
#define C_ATTACK_ROUNDS             (0x18)
#define C_ATTACK_MESSAGE            (0x1C) // message number set from the critical table
#define C_ATTACK_TARGET             (0x20)
#define C_ATTACK_BODY_PART          (0x28)
#define C_ATTACK_DAMAGE_TARGET      (0x2C) // Amount
#define C_ATTACK_FLAGS_TARGET       (0x30) // see DAM_*
#define C_ATTACK_KNOCKBACK_VALUE    (0x34)
#define C_ATTACK_MAIN_TARGET        (0x38)
#define C_ATTACK_AROUND_NUMBER      (0x3C) // The number of critters around the target
#define C_ATTACK_TARGET1            (0x40)
#define C_ATTACK_TARGET2            (0x44)
#define C_ATTACK_TARGET3            (0x48)
#define C_ATTACK_TARGET4            (0x4C)
#define C_ATTACK_TARGET5            (0x50)
#define C_ATTACK_TARGET6            (0x54)
#define C_ATTACK_BODY_PART1         (0x58)
#define C_ATTACK_BODY_PART2         (0x5C)
#define C_ATTACK_BODY_PART3         (0x60)
#define C_ATTACK_BODY_PART4         (0x64)
#define C_ATTACK_BODY_PART5         (0x68)
#define C_ATTACK_BODY_PART6         (0x6C)
#define C_ATTACK_DAMAGE_TARGET1     (0x70) // Amount
#define C_ATTACK_DAMAGE_TARGET2     (0x74)
#define C_ATTACK_DAMAGE_TARGET3     (0x78)
#define C_ATTACK_DAMAGE_TARGET4     (0x7C)
#define C_ATTACK_DAMAGE_TARGET5     (0x80)
#define C_ATTACK_DAMAGE_TARGET6     (0x84)
#define C_ATTACK_FLAGS_TARGET1      (0x88) // see DAM_*
#define C_ATTACK_FLAGS_TARGET2      (0x8C)
#define C_ATTACK_FLAGS_TARGET3      (0x90)
#define C_ATTACK_FLAGS_TARGET4      (0x94)
#define C_ATTACK_FLAGS_TARGET5      (0x98)
#define C_ATTACK_FLAGS_TARGET6      (0x9C)
#define C_ATTACK_KNOCKBACK_VALUE1   (0xA0)
#define C_ATTACK_KNOCKBACK_VALUE2   (0xA4)
#define C_ATTACK_KNOCKBACK_VALUE3   (0xA8)
#define C_ATTACK_KNOCKBACK_VALUE4   (0xAC)
#define C_ATTACK_KNOCKBACK_VALUE5   (0xB0)
#define C_ATTACK_KNOCKBACK_VALUE6   (0xB4)

/* Playback mode defines for the soundplay function */
#define soundraw        (0x80000000) // sfall flag
#define Stereo8bit      (soundstereo)
#define Stereo8bitLoop  (soundstereo bwor soundloop)
#define Mono16bit       (sound16bit)
#define Mono16bitLoop   (sound16bit bwor soundloop)
#define Stereo16bit     (soundstereo bwor sound16bit)
#define Stereo16bitLoop (soundstereo bwor sound16bit bwor soundloop)

// Adjust (reduce) volume for soundplay and play_sfall_sound
// range: 0x0000XXXX (max volume) - 0x7FFFXXXX (mute)
#define SoundVolume25   (0x20000000)
#define SoundVolumeHalf (0x40000000)
#define SoundVolume75   (0x60000000)

#endif // DEFINE_EXTRA_H
