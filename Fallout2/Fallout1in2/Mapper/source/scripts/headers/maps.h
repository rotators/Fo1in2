#ifndef MAPS_H
#define MAPS_H

/*******************************************************************************
 Location numbers
*******************************************************************************/
#define AREA_WORLDMAP             (-1)

#define AREA_VAULT_13             (0)
#define AREA_VAULT_15             (1)
#define AREA_SHADY_SANDS          (2)
#define AREA_JUNKTOWN             (3)
#define AREA_RAIDERS              (4)
#define AREA_NECROPOLIS           (5)
#define AREA_HUB                  (6)
#define AREA_BROTHERHOOD          (7)
#define AREA_MILITARY_BASE        (8)
#define AREA_GLOW                 (9)
#define AREA_BONEYARD             (10)
#define AREA_CATHEDRAL            (11)

#define AREA_CAR_OUTTA_GAS        (21)

#define AREA_RND_ENC_DESERT       (26)
#define AREA_RND_ENC_MOUNTAIN     (27)
#define AREA_RND_ENC_CITY         (28)
#define AREA_RND_ENC_COAST        (29)

#define AREA_CARAVAN_ENCOUNTER    (44)
#define AREA_SHADOW_MAPS          (47)

#define AREA_RND_DESERT           (49) // "Manual" player encounter
#define AREA_RND_MOUNTAIN         (50) // "Manual" player encounter
#define AREA_RND_CITY             (51) // "Manual" player encounter
#define AREA_RND_COAST            (52) // "Manual" player encounter

#define AREA_SPECIAL_RND_FOOT     (53)
#define AREA_SPECIAL_RND_TARDIS   (54)
#define AREA_SPECIAL_RND_USEDCAR  (55)
#define AREA_SPECIAL_RND_COLATRUK (56)
#define AREA_SPECIAL_RND_FSAUSER  (57)
#define AREA_SPECIAL_RND_TALKCOW  (58)
#define AREA_SPECIAL_RND_TEMPLE   (59)

#define AREA_SCRAPHEAP            (60)

#define AREA_SHADY_CAVES          (61)
#define AREA_HUB_FARM             (62)
#define AREA_HUB_LAIR             (63)

/*******************************************************************************
 Current City Index
*******************************************************************************/

#define CUR_AREA_VAULT_13             (cur_town == AREA_VAULT_13)
#define CUR_AREA_VAULT_15             (cur_town == AREA_VAULT_15)
#define CUR_AREA_SHADY_SANDS          (cur_town == AREA_SHADY_SANDS)
#define CUR_AREA_JUNKTOWN             (cur_town == AREA_JUNKTOWN)
#define CUR_AREA_RAIDERS              (cur_town == AREA_RAIDERS)
#define CUR_AREA_NECROPOLIS           (cur_town == AREA_NECROPOLIS)
#define CUR_AREA_HUB                  (cur_town == AREA_HUB)
#define CUR_AREA_BROTHERHOOD          (cur_town == AREA_BROTHERHOOD)
#define CUR_AREA_MILITARY_BASE        (cur_town == AREA_MILITARY_BASE)
#define CUR_AREA_GLOW                 (cur_town == AREA_GLOW)
#define CUR_AREA_BONEYARD             (cur_town == AREA_BONEYARD)
#define CUR_AREA_CATHEDRAL            (cur_town == AREA_CATHEDRAL)
#define CUR_AREA_CAR_OUTTA_GAS        (cur_town == AREA_CAR_OUTTA_GAS)
#define CUR_AREA_SPECIAL_RND_FOOT     (cur_town == AREA_SPECIAL_RND_FOOT)
#define CUR_AREA_SPECIAL_RND_TARDIS   (cur_town == AREA_SPECIAL_RND_TARDIS)
#define CUR_AREA_SPECIAL_RND_USEDCAR  (cur_town == AREA_SPECIAL_RND_USEDCAR)
#define CUR_AREA_SPECIAL_RND_COLATRUK (cur_town == AREA_SPECIAL_RND_COLATRUK)
#define CUR_AREA_SPECIAL_RND_FSAUSER  (cur_town == AREA_SPECIAL_RND_FSAUSER)
#define CUR_AREA_SPECIAL_RND_TALKCOW  (cur_town == AREA_SPECIAL_RND_TALKCOW)
#define CUR_AREA_SPECIAL_RND_TEMPLE   (cur_town == AREA_SPECIAL_RND_TEMPLE)
#define CUR_AREA_SCRAPHEAP            (cur_town == AREA_SCRAPHEAP)
#define CUR_AREA_SHADY_CAVES          (cur_town == AREA_SHADY_CAVES)
#define CUR_AREA_HUB_FARM             (cur_town == AREA_HUB_FARM)
#define CUR_AREA_HUB_LAIR             (cur_town == AREA_HUB_LAIR)

#define CUR_AREA_RND_DESERT           (cur_town == AREA_RND_DESERT or cur_town == AREA_RND_ENC_DESERT)
#define CUR_AREA_RND_MOUNTAIN         (cur_town == AREA_RND_MOUNTAIN or cur_town == AREA_RND_ENC_MOUNTAIN)
#define CUR_AREA_RND_CITY             (cur_town == AREA_RND_CITY or cur_town == AREA_RND_ENC_CITY)
#define CUR_AREA_RND_COAST            (cur_town == AREA_RND_COAST or cur_town == AREA_RND_ENC_COAST)

#define CUR_AREA_WORLDMAP             (cur_town == AREA_WORLDMAP)

/*******************************************************************************
 Map Numbers
*******************************************************************************/

#define MAP_DESERT0         (0)
#define MAP_DESERT2         (1)
#define MAP_DESERT3         (2)
#define MAP_HALLDED         (3)
#define MAP_HOTEL           (4)
#define MAP_WATRSHD         (5)
#define MAP_VAULT13         (6)
#define MAP_VAULTENT        (7)
#define MAP_VAULTBUR        (8)
#define MAP_VAULTNEC        (9)
#define MAP_JUNKENT         (10)
#define MAP_JUNKCSNO        (11)
#define MAP_JUNKKILL        (12)
#define MAP_BROHDENT        (13)
#define MAP_BROHD12         (14)
#define MAP_BROHD34         (15)
#define MAP_CAVES           (16)
#define MAP_CHILDRN1        (17)
#define MAP_CHILDRN2        (18)
#define MAP_CITY1           (19)
#define MAP_COAST1          (20)
#define MAP_COAST2          (21)
#define MAP_COLATRUK        (22)
#define MAP_FSAUSER         (23)
#define MAP_RAIDERS         (24)
#define MAP_SHADYE          (25)
#define MAP_SHADYW          (26)
#define MAP_GLOWENT         (27)
#define MAP_LAADYTUM        (28)
#define MAP_LAFOLLWR        (29)
#define MAP_MBENT           (30)
#define MAP_MBSTRG12        (31)
#define MAP_MBVATS12        (32)
#define MAP_MSTRLR12        (33)
#define MAP_MSTRLR34        (34)
#define MAP_V13ENT          (35)
#define MAP_HUBENT          (36)
#define MAP_DETHCLAW        (37)
#define MAP_HUBDWNTN        (38)
#define MAP_HUBHEIGT        (39)
#define MAP_HUBOLDTN        (40)
#define MAP_HUBWATER        (41)
#define MAP_GLOW1           (42)
#define MAP_GLOW2           (43)
#define MAP_LABLADES        (44)
#define MAP_LARIPPER        (45)
#define MAP_LAGUNRUN        (46)
#define MAP_CHILDEAD        (47)
#define MAP_MBDEAD          (48)
#define MAP_MOUNTN1         (49)
#define MAP_MOUNTN2         (50)
#define MAP_FOOT            (51)
#define MAP_TARDIS          (52)
#define MAP_CAR_DESERT      (53)
#define MAP_USEDCAR         (54)
#define MAP_BRODEAD         (55)
#define MAP_DESCRVN1        (56)
#define MAP_DESCRVN2        (57)
#define MAP_MNTCRVN1        (58)
#define MAP_MNTCRVN2        (59)
#define MAP_DESCRVN3        (60)
#define MAP_MNTCRVN3        (61)
#define MAP_DESCRVN4        (62)
#define MAP_MNTCRVN4        (63)
#define MAP_DESERT1         (64)
#define MAP_HUBMIS0         (65)
#define MAP_HUBMIS1         (66)
#define MAP_RNDDESER        (67)
#define MAP_RNDMOUNT        (68)
#define MAP_RNDCITY         (69)
#define MAP_RNDCOAST        (70)
#define MAP_TALKCOW         (71)
#define MAP_ARTEMPLE        (72)
#define MAP_ARCAVES         (73)
#define MAP_GUARDIAN        (74)
#define MAP_SCRAPHEAP       (75)

#define MAP_CITY2           (79)
#define MAP_CITY3           (80)
#define MAP_CAVE0           (81)
#define MAP_CAVE1           (82)
#define MAP_CAVE2           (83)
#define MAP_CAVE3           (84)
#define MAP_CAVE4           (85)
#define MAP_CAVE5           (86)

/*******************************************************************************
 Map Names (Strings)
*******************************************************************************/
#define MAPSTR(map) #map ".MAP"

#define MAPSTR_DESERT1  "DESERT1.MAP"
#define MAPSTR_DESERT2  "DESERT2.MAP"
#define MAPSTR_DESERT3  "DESERT3.MAP"
#define MAPSTR_HALLDED  "HALLDED.MAP"
#define MAPSTR_HOTEL    "HOTEL.MAP"
#define MAPSTR_WATRSHD  "WATRSHD.MAP"
#define MAPSTR_VAULT13  "VAULT13.MAP"
#define MAPSTR_VAULTENT "VAULTENT.MAP"
#define MAPSTR_VAULTBUR "VAULTBUR.MAP"
#define MAPSTR_VAULTNEC "VAULTNEC.MAP"
#define MAPSTR_JUNKENT  "JUNKENT.MAP"
#define MAPSTR_JUNKCSNO "JUNKCSNO.MAP"
#define MAPSTR_JUNKKILL "JUNKKILL.MAP"
#define MAPSTR_BROHDENT "BROHDENT.MAP"
#define MAPSTR_BROHD12  "BROHD12.MAP"
#define MAPSTR_BROHD34  "BROHD34.MAP"
#define MAPSTR_CAVES    "CAVES.MAP"
#define MAPSTR_CHILDRN1 "CHILDRN1.MAP"
#define MAPSTR_CHILDRN2 "CHILDRN2.MAP"
#define MAPSTR_CITY1    "CITY1.MAP"
#define MAPSTR_COAST1   "COAST1.MAP"
#define MAPSTR_COAST2   "COAST2.MAP"
#define MAPSTR_COLATRUK "COLATRUK.MAP"
#define MAPSTR_FSAUSER  "FSAUSER.MAP"
#define MAPSTR_RAIDERS  "RAIDERS.MAP"
#define MAPSTR_SHADYE   "SHADYE.MAP"
#define MAPSTR_SHADYW   "SHADYW.MAP"
#define MAPSTR_GLOWENT  "GLOWENT.MAP"
#define MAPSTR_LAADYTUM "LAADYTUM.MAP"
#define MAPSTR_LAFOLLWR "LAFOLLWR.MAP"
#define MAPSTR_MBENT    "MBENT.MAP"
#define MAPSTR_MBSTRG12 "MBSTRG12.MAP"
#define MAPSTR_MBVATS12 "MBVATS12.MAP"
#define MAPSTR_MSTRLR12 "MSTRLR12.MAP"
#define MAPSTR_MSTRLR34 "MSTRLR34.MAP"
#define MAPSTR_V13ENT   "V13ENT.MAP"
#define MAPSTR_HUBENT   "HUBENT.MAP"
#define MAPSTR_DETHCLAW "DETHCLAW.MAP"
#define MAPSTR_HUBDWNTN "HUBDWNTN.MAP"
#define MAPSTR_HUBHEIGT "HUBHEIGT.MAP"
#define MAPSTR_HUBOLDTN "HUBOLDTN.MAP"
#define MAPSTR_HUBWATER "HUBWATER.MAP"
#define MAPSTR_GLOW1    "GLOW1.MAP"
#define MAPSTR_GLOW2    "GLOW2.MAP"
#define MAPSTR_LABLADES "LABLADES.MAP"
#define MAPSTR_LARIPPER "LARIPPER.MAP"
#define MAPSTR_LAGUNRUN "LAGUNRUN.MAP"
#define MAPSTR_CHILDEAD "CHILDEAD.MAP"
#define MAPSTR_MBDEAD   "MBDEAD.MAP"
#define MAPSTR_MOUNTN1  "MOUNTN1.MAP"
#define MAPSTR_MOUNTN2  "MOUNTN2.MAP"
#define MAPSTR_FOOT     "FOOT.MAP"
#define MAPSTR_TARDIS   "TARDIS.MAP"
#define MAPSTR_TALKCOW  "TALKCOW.MAP"
#define MAPSTR_USEDCAR  "USEDCAR.MAP"
#define MAPSTR_BRODEAD  "BRODEAD.MAP"
#define MAPSTR_DESCRVN1 "DESCRVN1.MAP"
#define MAPSTR_DESCRVN2 "DESCRVN2.MAP"
#define MAPSTR_MNTCRVN1 "MNTCRVN1.MAP"
#define MAPSTR_MNTCRVN2 "MNTCRVN2.MAP"
#define MAPSTR_DESCRVN3 "DESCRVN3.MAP"
#define MAPSTR_MNTCRVN3 "MNTCRVN3.MAP"
#define MAPSTR_DESCRVN4 "DESCRVN4.MAP"
#define MAPSTR_MNTCRVN4 "MNTCRVN4.MAP"

#define MAPSTR_ARTEMPLE "artemple.MAP"
#define MAPSTR_ARCAVES  "arcaves.MAP"

/*******************************************************************************
 Current map index
*******************************************************************************/

#define CUR_MAP_DESERT0     (cur_map_index ==  MAP_DESERT0)
#define CUR_MAP_DESERT1     (cur_map_index ==  MAP_DESERT1)
#define CUR_MAP_DESERT2     (cur_map_index ==  MAP_DESERT2)
#define CUR_MAP_DESERT3     (cur_map_index ==  MAP_DESERT3)
#define CUR_MAP_HALLDED     (cur_map_index ==  MAP_HALLDED)
#define CUR_MAP_HOTEL       (cur_map_index ==  MAP_HOTEL)
#define CUR_MAP_WATRSHD     (cur_map_index ==  MAP_WATRSHD)
#define CUR_MAP_VAULT13     (cur_map_index ==  MAP_VAULT13)
#define CUR_MAP_VAULTENT    (cur_map_index ==  MAP_VAULTENT)
#define CUR_MAP_VAULTBUR    (cur_map_index ==  MAP_VAULTBUR)
#define CUR_MAP_VAULTNEC    (cur_map_index ==  MAP_VAULTNEC)
#define CUR_MAP_JUNKENT     (cur_map_index ==  MAP_JUNKENT)
#define CUR_MAP_JUNKCSNO    (cur_map_index ==  MAP_JUNKCSNO)
#define CUR_MAP_JUNKKILL    (cur_map_index ==  MAP_JUNKKILL)
#define CUR_MAP_BROHDENT    (cur_map_index ==  MAP_BROHDENT)
#define CUR_MAP_BROHD12     (cur_map_index ==  MAP_BROHD12)
#define CUR_MAP_BROHD34     (cur_map_index ==  MAP_BROHD34)
#define CUR_MAP_CAVES       (cur_map_index ==  MAP_CAVES)
#define CUR_MAP_CHILDRN1    (cur_map_index ==  MAP_CHILDRN1)
#define CUR_MAP_CHILDRN2    (cur_map_index ==  MAP_CHILDRN2)
#define CUR_MAP_CITY1       (cur_map_index ==  MAP_CITY1)
#define CUR_MAP_COAST1      (cur_map_index ==  MAP_COAST1)
#define CUR_MAP_COAST2      (cur_map_index ==  MAP_COAST2)
#define CUR_MAP_COLATRUK    (cur_map_index ==  MAP_COLATRUK)
#define CUR_MAP_FSAUSER     (cur_map_index ==  MAP_FSAUSER)
#define CUR_MAP_RAIDERS     (cur_map_index ==  MAP_RAIDERS)
#define CUR_MAP_SHADYE      (cur_map_index ==  MAP_SHADYE)
#define CUR_MAP_SHADYW      (cur_map_index ==  MAP_SHADYW)
#define CUR_MAP_GLOWENT     (cur_map_index ==  MAP_GLOWENT)
#define CUR_MAP_LAADYTUM    (cur_map_index ==  MAP_LAADYTUM)
#define CUR_MAP_LAFOLLWR    (cur_map_index ==  MAP_LAFOLLWR)
#define CUR_MAP_MBENT       (cur_map_index ==  MAP_MBENT)
#define CUR_MAP_MBSTRG12    (cur_map_index ==  MAP_MBSTRG12)
#define CUR_MAP_MBVATS12    (cur_map_index ==  MAP_MBVATS12)
#define CUR_MAP_MSTRLR12    (cur_map_index ==  MAP_MSTRLR12)
#define CUR_MAP_MSTRLR34    (cur_map_index ==  MAP_MSTRLR34)
#define CUR_MAP_V13ENT      (cur_map_index ==  MAP_V13ENT)
#define CUR_MAP_HUBENT      (cur_map_index ==  MAP_HUBENT)
#define CUR_MAP_DETHCLAW    (cur_map_index ==  MAP_DETHCLAW)
#define CUR_MAP_HUBDWNTN    (cur_map_index ==  MAP_HUBDWNTN)
#define CUR_MAP_HUBHEIGT    (cur_map_index ==  MAP_HUBHEIGT)
#define CUR_MAP_HUBOLDTN    (cur_map_index ==  MAP_HUBOLDTN)
#define CUR_MAP_HUBWATER    (cur_map_index ==  MAP_HUBWATER)
#define CUR_MAP_GLOW1       (cur_map_index ==  MAP_GLOW1)
#define CUR_MAP_GLOW2       (cur_map_index ==  MAP_GLOW2)
#define CUR_MAP_LABLADES    (cur_map_index ==  MAP_LABLADES)
#define CUR_MAP_LARIPPER    (cur_map_index ==  MAP_LARIPPER)
#define CUR_MAP_LAGUNRUN    (cur_map_index ==  MAP_LAGUNRUN)
#define CUR_MAP_CHILDEAD    (cur_map_index ==  MAP_CHILDEAD)
#define CUR_MAP_MBDEAD      (cur_map_index ==  MAP_MBDEAD)
#define CUR_MAP_MOUNTN1     (cur_map_index ==  MAP_MOUNTN1)
#define CUR_MAP_MOUNTN2     (cur_map_index ==  MAP_MOUNTN2)
#define CUR_MAP_FOOT        (cur_map_index ==  MAP_FOOT)
#define CUR_MAP_TARDIS      (cur_map_index ==  MAP_TARDIS)
#define CUR_MAP_TALKCOW     (cur_map_index ==  MAP_TALKCOW)
#define CUR_MAP_USEDCAR     (cur_map_index ==  MAP_USEDCAR)
#define CUR_MAP_BRODEAD     (cur_map_index ==  MAP_BRODEAD)
#define CUR_MAP_DESCRVN1    (cur_map_index ==  MAP_DESCRVN1)
#define CUR_MAP_DESCRVN2    (cur_map_index ==  MAP_DESCRVN2)
#define CUR_MAP_MNTCRVN1    (cur_map_index ==  MAP_MNTCRVN1)
#define CUR_MAP_MNTCRVN2    (cur_map_index ==  MAP_MNTCRVN2)
#define CUR_MAP_DESCRVN3    (cur_map_index ==  MAP_DESCRVN3)
#define CUR_MAP_MNTCRVN3    (cur_map_index ==  MAP_MNTCRVN3)
#define CUR_MAP_DESCRVN4    (cur_map_index ==  MAP_DESCRVN4)
#define CUR_MAP_MNTCRVN4    (cur_map_index ==  MAP_MNTCRVN4)
#define CUR_MAP_HUBMIS0     (cur_map_index ==  MAP_HUBMIS0)
#define CUR_MAP_RNDDESER    (cur_map_index ==  MAP_RNDDESER)
#define CUR_MAP_RNDMOUNT    (cur_map_index ==  MAP_RNDMOUNT)
#define CUR_MAP_RNDCITY     (cur_map_index ==  MAP_RNDCITY)
#define CUR_MAP_RNDCOAST    (cur_map_index ==  MAP_RNDCOAST)
#define CUR_MAP_ARTEMPLE    (cur_map_index ==  MAP_ARTEMPLE)
#define CUR_MAP_ARCAVES     (cur_map_index ==  MAP_ARCAVES)
#define CUR_MAP_GUARDIAN    (cur_map_index ==  MAP_GUARDIAN)
#define CUR_MAP_SCRAPHEAP   (cur_map_index ==  MAP_SCRAPHEAP)

#define CUR_MAP_CITY2       (cur_map_index ==  MAP_CITY2)
#define CUR_MAP_CITY3       (cur_map_index ==  MAP_CITY3)
#define CUR_MAP_CAVE0       (cur_map_index ==  MAP_CAVE0)
#define CUR_MAP_CAVE1       (cur_map_index ==  MAP_CAVE1)
#define CUR_MAP_CAVE2       (cur_map_index ==  MAP_CAVE2)
#define CUR_MAP_CAVE3       (cur_map_index ==  MAP_CAVE3)
#define CUR_MAP_CAVE4       (cur_map_index ==  MAP_CAVE4)
#define CUR_MAP_CAVE5       (cur_map_index ==  MAP_CAVE5)

// Force player position when loading map
#define override_map_start_hex(x,y,z)   override_map_start(x%200,x/200,y,z)

/******************************************************************
 General commands getting information about cities
******************************************************************/
#define vault_13_visible_on_map             (town_known(AREA_VAULT_13) != MARK_STATE_UNKNOWN)
#define vault_15_visible_on_map             (town_known(AREA_VAULT_15) != MARK_STATE_UNKNOWN)
#define shady_sands_visible_on_map          (town_known(AREA_SHADY_SANDS) != MARK_STATE_UNKNOWN)
#define junktown_visible_on_map             (town_known(AREA_JUNKTOWN) != MARK_STATE_UNKNOWN)
#define raiders_visible_on_map              (town_known(AREA_RAIDERS) != MARK_STATE_UNKNOWN)
#define necropolis_visible_on_map           (town_known(AREA_NECROPOLIS) != MARK_STATE_UNKNOWN)
#define hub_visible_on_map                  (town_known(AREA_HUB) != MARK_STATE_UNKNOWN)
#define brotherhood_visible_on_map          (town_known(AREA_BROTHERHOOD) != MARK_STATE_UNKNOWN)
#define military_base_visible_on_map        (town_known(AREA_MILITARY_BASE) != MARK_STATE_UNKNOWN)
#define glow_visible_on_map                 (town_known(AREA_GLOW) != MARK_STATE_UNKNOWN)
#define boneyard_visible_on_map             (town_known(AREA_BONEYARD) != MARK_STATE_UNKNOWN)
#define cathedral_visible_on_map            (town_known(AREA_CATHEDRAL) != MARK_STATE_UNKNOWN)

#define shady_caves_visible_on_map          (town_known(AREA_SHADY_CAVES) != MARK_STATE_UNKNOWN)
#define hub_farm_visible_on_map             (town_known(AREA_HUB_FARM) != MARK_STATE_UNKNOWN)
#define hub_lair_visible_on_map             (town_known(AREA_HUB_LAIR) != MARK_STATE_UNKNOWN)

#define vault_13_visit                      (town_known(AREA_VAULT_13) == MARK_STATE_VISITED)
#define vault_15_visit                      (town_known(AREA_VAULT_15) == MARK_STATE_VISITED)
#define shady_sands_visit                   (town_known(AREA_SHADY_SANDS) == MARK_STATE_VISITED)
#define junktown_visit                      (town_known(AREA_JUNKTOWN) == MARK_STATE_VISITED)
#define raiders_visit                       (town_known(AREA_RAIDERS) == MARK_STATE_VISITED)
#define necropolis_visit                    (town_known(AREA_NECROPOLIS) == MARK_STATE_VISITED)
#define hub_visit                           (town_known(AREA_HUB) == MARK_STATE_VISITED)
#define brotherhood_visit                   (town_known(AREA_BROTHERHOOD) == MARK_STATE_VISITED)
#define military_base_visit                 (town_known(AREA_MILITARY_BASE) == MARK_STATE_VISITED)
#define glow_visit                          (town_known(AREA_GLOW) == MARK_STATE_VISITED)
#define boneyard_visit                      (town_known(AREA_BONEYARD) == MARK_STATE_VISITED)
#define cathedral_visit                     (town_known(AREA_CATHEDRAL) == MARK_STATE_VISITED)

#define shady_caves_visit                 (town_known(AREA_SHADY_CAVES) != MARK_STATE_UNKNOWN)
#define hub_farm_visit                    (town_known(AREA_HUB_FARM) != MARK_STATE_UNKNOWN)
#define hub_lair_visit                    (town_known(AREA_HUB_LAIR) != MARK_STATE_UNKNOWN)

#define mark_on_map(x)                      if (town_known(x) == MARK_STATE_UNKNOWN) then begin          \
                                               debug_msg("  mark_on_map("+x+")");                        \
                                               mark_area_known(MARK_TYPE_TOWN, x, MARK_STATE_KNOWN);     \
                                            end

#define unmark_on_map(x)                    if (town_known(x) != MARK_STATE_UNKNOWN) then begin          \
                                               debug_msg(" unmark_on_map("+x+")");                       \
                                               mark_area_known(MARK_TYPE_TOWN, x, MARK_STATE_UNKNOWN);   \
                                            end

#define invisible_on_map(x)                 if (town_known(x) != MARK_STATE_UNKNOWN) then begin          \
                                               debug_msg(" invisible_on_map("+x+")");                    \
                                               mark_area_known(MARK_TYPE_TOWN, x, MARK_STATE_INVISIBLE); \
                                            end

#define mark_vault_13_on_map              mark_on_map(AREA_VAULT_13)
#define mark_vault_15_on_map              mark_on_map(AREA_VAULT_15)
#define mark_shady_sands_on_map           mark_on_map(AREA_SHADY_SANDS)
#define mark_junktown_on_map              mark_on_map(AREA_JUNKTOWN)
#define mark_raiders_on_map               mark_on_map(AREA_RAIDERS)
#define mark_necropolis_on_map            mark_on_map(AREA_NECROPOLIS)
#define mark_hub_on_map                   mark_on_map(AREA_HUB)
#define mark_brotherhood_on_map           mark_on_map(AREA_BROTHERHOOD)
#define mark_military_base_on_map         mark_on_map(AREA_MILITARY_BASE)
#define mark_glow_on_map                  mark_on_map(AREA_GLOW)
#define mark_boneyard_on_map              mark_on_map(AREA_BONEYARD)
#define mark_cathedral_on_map             mark_on_map(AREA_CATHEDRAL)
#define mark_shady_caves_on_map           mark_on_map(AREA_SHADY_CAVES)
#define mark_hub_farm_on_map              mark_on_map(AREA_HUB_FARM)
#define mark_hub_lair_on_map              mark_on_map(AREA_HUB_LAIR)

#define unmark_vault_13_on_map            unmark_on_map(AREA_VAULT_13)
#define unmark_vault_15_on_map            unmark_on_map(AREA_VAULT_15)
#define unmark_shady_sands_on_map         unmark_on_map(AREA_SHADY_SANDS)
#define unmark_junktown_on_map            unmark_on_map(AREA_JUNKTOWN)
#define unmark_raiders_on_map             unmark_on_map(AREA_RAIDERS)
#define unmark_necropolis_on_map          unmark_on_map(AREA_NECROPOLIS)
#define unmark_hub_on_map                 unmark_on_map(AREA_HUB)
#define unmark_brotherhood_on_map         unmark_on_map(AREA_BROTHERHOOD)
#define unmark_military_base_on_map       unmark_on_map(AREA_MILITARY_BASE)
#define unmark_glow_on_map                unmark_on_map(AREA_GLOW)
#define unmark_boneyard_on_map            unmark_on_map(AREA_BONEYARD)
#define unmark_cathedral_on_map           unmark_on_map(AREA_CATHEDRAL)
#define unmark_shady_caves_on_map         unmark_on_map(AREA_SHADY_CAVES)
#define unmark_hub_farm_on_map            unmark_on_map(AREA_HUB_FARM)
#define unmark_hub_lair_on_map            unmark_on_map(AREA_HUB_LAIR)

#define unmark_car_outta_gas_on_map       mark_area_known(MARK_TYPE_TOWN, AREA_CAR_OUTTA_GAS, MARK_STATE_UNKNOWN)

/******************************************************************
 Advance the game time when using NPCs from encounter to travel
******************************************************************/
variable get_wm_distance;
#define advance_time_travel_to_shady               advance_time_wm_travel(1073,  72,   MAP_SHADYW,    1)
#define advance_time_travel_to_raiders             advance_time_wm_travel(1123,  172,  MAP_RAIDERS,   0)
#define advance_time_travel_to_junktown            advance_time_wm_travel(873,   522,  MAP_JUNKENT,   1)
#define advance_time_travel_to_hub                 advance_time_wm_travel(873,   722,  MAP_HUBENT,    1)
#define advance_time_travel_to_necropolis          advance_time_wm_travel(1123,  672,  MAP_HOTEL,     1)
#define advance_time_travel_to_boneyard            advance_time_wm_travel(773,   922,  MAP_LAADYTUM,  1)
#define advance_time_travel_to_bos                 advance_time_wm_travel(623,   472,  MAP_BROHDENT,  0)
#define advance_time_travel_to_mbase_vats          advance_time_wm_travel(173,   72,   MAP_MBVATS12,  5)
#define advance_time_travel_to_master              advance_time_wm_travel(773,   1022, MAP_MSTRLR34,  12)

#define advance_time_wm_travel(x,y,map,index)      get_wm_distance := sqrt((x - worldmap_xpos)^2 + (y - worldmap_ypos)^2);                                  \
                                                   get_wm_distance := round(get_wm_distance) / 50;                                                          \
                                                   debug("Advancing " + get_wm_distance + " days by wm teleport!");                                         \
                                                   game_time_advance(game_ticks((ONE_GAME_DAY * get_wm_distance) + (ONE_GAME_MINUTE * random(-300,300))));  \
                                                   load_map(map, index)

/******************************************************************
 Random Encounters
******************************************************************/
/* The following define is to force critter X to face critter Y */
#define Face_Critter(Y,X)           anim(X,ANIMATE_ROTATION,rotation_to_tile(tile_num(X),tile_num(Y)))

/* The following define will set a rotation arc for placement of critters. */
#define FixRotationArc(X)           while (X < 0) do begin      \
                                        X += 6;                 \
                                    end                         \
                                    if (X > 5) then             \
                                        X := X%6


/* The following define will give you the inverse (Y) of a rotation (X) */
#define InvertRotation(X,Y)         X+=3;                       \
                                    FixRotationArc(X)


#endif // MAPS_H
