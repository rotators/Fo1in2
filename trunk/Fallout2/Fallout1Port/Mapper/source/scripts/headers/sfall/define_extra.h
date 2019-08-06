#ifndef DEFINE_EXTRA_H
#define DEFINE_EXTRA_H

#define OBJ_TYPE_ITEM       (0)
#define OBJ_TYPE_CRITTER    (1)
#define OBJ_TYPE_SCENERY    (2)
#define OBJ_TYPE_WALL       (3)
#define OBJ_TYPE_TILE       (4)
#define OBJ_TYPE_MISC       (5)
#define OBJ_TYPE_SPATIAL    (6)

/* Item Common Flags */
#define HIDDEN_ITEM     134217728  // 0x08000000 - Hidden Item

#define ITEM_ACTION_USE      2048  // 0x00000800 - Use (can be used)
#define ITEM_ACTION_USEON    4096  // 0x00001000 - Use On Smth (can be used on anything)
#define ITEM_ACTION_PICKUP  32768  // 0x00008000 - PickUp

#define WEAPON_BIGGUN         256  // 0x00000100 - Big Gun
#define WEAPON_2HAND          512  // 0x00000200 - 2Hnd (weapon is two-handed)

#define ATKMODE_PRI_NONE        0
#define ATKMODE_PRI_PUNCH       1
#define ATKMODE_PRI_KICK        2
#define ATKMODE_PRI_SWING       3
#define ATKMODE_PRI_THRUST      4
#define ATKMODE_PRI_THROW       5
#define ATKMODE_PRI_SINGLE      6
#define ATKMODE_PRI_BURST       7
#define ATKMODE_PRI_FLAME       8
#define ATKMODE_SEC_NONE        0
#define ATKMODE_SEC_PUNCH      16  // 0x00000010
#define ATKMODE_SEC_KICK       32  // 0x00000020
#define ATKMODE_SEC_SWING      48  // 0x00000030
#define ATKMODE_SEC_THRUST     64  // 0x00000040
#define ATKMODE_SEC_THROW      80  // 0x00000050
#define ATKMODE_SEC_SINGLE     96  // 0x00000060
#define ATKMODE_SEC_BURST     112  // 0x00000070
#define ATKMODE_SEC_FLAME     128  // 0x00000080

/* Object flags */
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


/* Critter Flags */
#define CFLG_BARTER             2  // 0x00000002 - Barter (can trade with)
#define CFLG_NOSTEAL           32  // 0x00000020 - Steal (cannot steal from)
#define CFLG_NODROP            64  // 0x00000040 - Drop (doesn't drop items)
#define CFLG_NOLIMBS          128  // 0x00000080 - Limbs (cannot lose limbs)
#define CFLG_NOAGES           256  // 0x00000100 - Ages (dead body does not disappear)
#define CFLG_NOHEAL           512  // 0x00000200 - Heal (damage is not cured with time)
#define CFLG_INVULN          1024  // 0x00000400 - Invulnerable (cannot be hurt)
#define CFLG_FLATTN          2048  // 0x00000800 - Flatten (leaves no dead body)
#define CFLG_SPECIAL         4096  // 0x00001000 - Special (there is a special type of death)
#define CFLG_RANGED          8192  // 0x00002000 - Range (melee attack is possible at a distance)
#define CFLG_NOKNOCKDOWN    16384  // 0x00004000 - Knock (cannot be knocked down)

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

// offsets for get_proto_data
#define PROTO_PID             (1)
#define PROTO_TEXTID          (4)

// items
#define PROTO_IT_FLAGS       (24)
#define PROTO_IT_TYPE        (32)
#define PROTO_IT_MATERIAL   (108)
#define PROTO_IT_SIZE       (112)
#define PROTO_IT_WEIGHT     (116)
#define PROTO_IT_COST       (120)
#define PROTO_IT_INV_FID    (124)

// weapons
#define PROTO_WP_ANIM        (36)
#define PROTO_WP_DMG_MIN     (40)
#define PROTO_WP_DMG_MAX     (44)
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
#define PROTO_CR_ACTION_FLAGS    (32)
#define PROTO_CR_HEAD_FID        (40)
#define PROTO_CR_AI_PACKET       (44)
#define PROTO_CR_TEAM_NUM        (48)
#define PROTO_CR_FLAGS           (52)
#define PROTO_CR_BODY_TYPE      (388)
#define PROTO_CR_KILL_EXP       (392)
#define PROTO_CR_KILL_TYPE      (396)
#define PROTO_CR_DMG_TYPE       (400)

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
#define PERK_add_nuka            (53)
#define PERK_add_buffout         (54)
#define PERK_add_mentats         (55)
#define PERK_add_psycho          (56)
#define PERK_add_radaway         (57)
#define PERK_weapon_long_range   (58)
#define PERK_weapon_accurate     (59)
#define PERK_weapon_penetrate    (60)
#define PERK_weapon_knockback    (61)
#define PERK_armor_powered       (62)
#define PERK_armor_combat        (63)
#define PERK_weapon_scope_range  (64)
#define PERK_weapon_fast_reload  (65)
#define PERK_weapon_night_sight  (66)
#define PERK_weapon_flameboy     (67)
#define PERK_armor_advanced_1    (68)
#define PERK_armor_advanced_2    (69)
#define PERK_add_jet             (70)
#define PERK_add_tragic          (71)
#define PERK_armor_charisma      (72)

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

#endif // DEFINE_EXTRA_H