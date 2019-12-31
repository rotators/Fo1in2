/*
   Copyright 1998-2003 Interplay Entertainment Corp.  All rights reserved.
*/

#ifndef SCENEPID_H
#define SCENEPID_H

/***********************************************************
   Filename: ScenePid.h

    Purpose: This file stores all of the Pid Numbers for
             scenery objects. All defines within here need
             to be prepended w/ PID_

    Created: December 19, 1997
***********************************************************/

variable Scenery_Creation;
variable Scenery_Creation_Hex;
variable Scenery_Creation_Count;
variable Temp_Scenery_Creation_Hex;
variable Scenery_Creation_Ptr;

// dummies
// they should get proper names at some point in future~
#define PID_33554439 (33554439)
#define PID_33554471 (33554471)
#define PID_33554834 (33554834)
#define PID_33554835 (33554835)
#define PID_33555090 (33555090)
#define PID_33555118 (33555118)
#define PID_33555119 (33555119)

#define PID_BLOCKING_HEX                    (33554499)
#define PID_BLOWN_ARROYO_CAVE_DOOR          (33555365)
#define PID_ARROYO_CAVE_DOOR                (33555366)
#define PID_TEMPLE_SKULL_POLE               (33555374)
#define PID_RED_ARMCHAIR                    (33554665)

#define PID_BUSH_GREEN_1                    (33555375)
#define PID_BUSH_GREEN_2                    (33555376)

#define PID_PUNCHING_BAG                    (33554969)

// BOS Entrance scenery
#define PID_EW_BOS_DOOR                     (33554585)
#define PID_BOS_ELEVATOR_TOP                (33554613)
#define PID_BOS_MARKER                      (33554589)

// Navarro Door
#define PID_NS_NAVARRO_BUNKER_DOOR          (33554450)

// Sierra Base Entrance Door
#define PID_SIERRA_ENTRANCE_DOOR            (33555779)
#define PID_SIERRA_ENTRANCE_DOOR_EXP        (33555780)

// Enclave Puzzle Room Doors
#define PID_ENCLAVE_PUZZLE_DOOR_EW          (33556005)
#define PID_ENCLAVE_PUZZLE_DOOR_NS          (33556006)

// Klaxon Light
#define PID_EW_LIGHT                        (33555259)
#define PID_NS_LIGHT                        (33555260)
#define PID_EW_FLASHING_LIGHT               (33555339)
#define PID_NS_FLASHING_LIGHT               (33555340)

// Misc Trap Info
#define PID_CAVE_FLOOR_TRAP_VISIBLE         (33555383)
#define PID_CAVE_FLOOR_TRAP_DISARMED        (33555384)
#define PID_CAVE_FLOOR_TRAP_DEPRESSED       (33555385)

#define PID_METAL_FLOOR_TRAP_VISIBLE        (33555429)
#define PID_METAL_FLOOR_TRAP_DISARMED       (33555430)
#define PID_METAL_FLOOR_TRAP_DEPRESSED      (33555431)

// Mining Carts
#define PID_MINING_CART                     (33555584)
#define PID_MINING_CART_PLANK               (33555585)
#define PID_MINING_CART_EXPLOSIVE           (33555586)
#define PID_MINING_CART_DESTROYED           (33556060)

// military base enterance
#define PID_MB_DESTROYED_ROCKS_1            (33556235)
#define PID_MB_DESTROYED_ROCKS_2            (33556236)
#define PID_MB_DESTROYED_ROCKS_3            (33556237)
#define PID_MB_DESTROYED_ROCKS_4            (33556238)

// Force Fields
#define PID_NS_FORCE_FIELD                  (33554921)
#define PID_EW_FORCE_FIELD                  (33554922)
#define PID_EW_PAIN_FIELD                   (33554923)
#define PID_NS_PAIN_FIELD                   (33554924)
#define PID_EW_ANIM_FIELD                   (33555980)
#define PID_NS_ANIM_FIELD                   (33555981)

// Rocks Info
#define PID_BLUE_ROCK_PILE_SMALL_1          (33554511)
#define PID_BLUE_ROCK_PILE_SMALL_2          (33554512)
#define PID_LARGE_BLUE_ROCK_PILE            (33554513)
#define PID_CAVE_IN_ROCKS                   (33554839)

// grave site
#define PID_GRAVE_SITE                      (33555444)
#define PID_GRAVE_HEADSTONE_1               (33555445)
#define PID_GRAVE_HEADSTONE_2               (33555446)
#define PID_GRAVE_HEADSTONE_3               (33555447)
#define PID_GRAVE_HEADSTONE_4               (33555448)

// grave site crosses
#define PID_GRAVE_CROSS_1                   (33555669)
#define PID_GRAVE_CROSS_2                   (33555670)
#define PID_GRAVE_CROSS_3                   (33555671)
#define PID_GRAVE_CROSS_4                   (33555672)
#define PID_GRAVE_CROSS_5                   (33555673)
#define PID_GRAVE_CROSS_6                   (33555674)

// Car
#define PID_DRIVABLE_CAR                    (33555441)

// Caravans
#define PID_EW_RED_CARAVAN                  (33554959)
#define PID_EW_GREY_CARAVAN                 (33554960)
#define PID_NS_RED_CARAVAN                  (33554961)
#define PID_RED_CARAVAN_HANDLE              (33554962)
#define PID_NS_GREY_CARAVAN                 (33554963)
#define PID_GREY_CARAVAN_HANDLE             (33554964)

// Broken Brain Bot
#define PID_BROKEN_BRAINBOT                 (33555662)

//VDU Looks like a computer with a lot of monitors
#define PID_VDU_WORKING                     (33554488)
#define PID_VDU_NOT_WORKING                 (33555233)

// BRAHMIN CHUNKS
#define PID_BRAHMIN_CHUNK_1                 (33555731)
#define PID_BRAHMIN_CHUNK_2                 (33555732)
#define PID_BRAHMIN_CHUNK_3                 (33555733)
#define PID_BRAHMIN_CHUNK_4                 (33555734)
#define PID_BRAHMIN_CHUNK_5                 (33555735)
#define PID_BRAHMIN_CHUNK_6                 (33555736)

// Blood
#define PID_BLOOD_1                         (33555753)   // no bones
#define PID_BLOOD_2                         (33555754)
#define PID_BLOOD_3                         (33555755)
#define PID_BLOOD_4                         (33555756)
#define PID_BLOOD_5                         (33555757)
#define PID_BLOOD_6                         (33555758)
#define PID_BLOOD_7                         (33555759)   // bones
#define PID_BLOOD_8                         (33555760)
#define PID_BLOOD_9                         (33555761)

// Ghost Farm Stakes
#define PID_STAKE_1                         (33555648)   // with body
#define PID_STAKE_2                         (33555649)
#define PID_STAKE_3                         (33555650)
#define PID_STAKE_4                         (33555651)
#define PID_STAKE_5                         (33555652)
#define PID_STAKE_6                         (33555653)
#define PID_STAKE_7                         (33555654)   // with skull
#define PID_STAKE_8                         (33555655)
#define PID_STAKE_9                         (33555656)   // plain stake
#define PID_STAKE_10                        (33555657)
#define PID_STAKE_11                        (33555658)
#define PID_STAKE_12                        (33555659)

// Corn stalks
#define PID_CORN_1                          (33555395)
#define PID_CORN_2                          (33555396)
#define PID_CORN_3                          (33555397)
#define PID_CORN_4                          (33555398)
#define PID_CORN_5                          (33555399)
#define PID_CORN_6                          (33555400)

// small goo
#define PID_SMALL_GOO_1                     (33555178)
#define PID_SMALL_GOO_2                     (33555179)
#define PID_SMALL_GOO_3                     (33555180)

// radioactive goo
#define PID_RAD_GOO_1                       (33555417)
#define PID_RAD_GOO_2                       (33555418)
#define PID_RAD_GOO_3                       (33555419)
#define PID_RAD_GOO_4                       (33555420)

// Doors
#define PID_JAIL_DOOR_N_S                   (33555013)

// Slagged Door
#define PID_SLAGGED_DOOR_BOTTOM             (33555810)
#define PID_SLAGGED_DOOR_TOP                (33555811)

// out of business sighns
#define PID_OUT_OF_BUSINESS_NORTH           (33555587)
#define PID_OUT_OF_BUSINESS_EAST            (33555588)

// slot machines
#define PID_SLOT_FACING_2                   (33554898)
#define PID_SLOT_FACING_3                   (33554897)

// Sewer hole cover / door
#define PID_SEWER_COVER                     (33554576)

// New Fallout 1:
#define PID_BEAM_1                          (33554999)
#define PID_BEAM_2                          (33555000)
#define PID_BED_1                           (33554640)
#define PID_BED_2                           (33554641)
#define PID_BONES_1                         (33554514)
#define PID_BONES_2                         (33554515)
#define PID_BONES_3                         (33554516)
#define PID_BONES_4                         (33554517)
#define PID_BONES_5                         (33554518)
#define PID_BOXES_1                         (33554652)
#define PID_BOXES_2                         (33554653)
#define PID_BOXES_3                         (33554654)
#define PID_BOXES_4                         (33554655)
#define PID_BURNING_BARREL                  (33554433)
#define PID_CACTUS_1                        (33554496)
#define PID_CACTUS_2                        (33554497)
#define PID_OLD_CHAIR                       (33554667)
#define PID_CART                            (33554800)
#define PID_CHAIR                           (33555207)
#define PID_CHAIR_1                         (33554527)
#define PID_CHAIR_2                         (33554528)
#define PID_CHAIR_3                         (33554529)
#define PID_CHAIR_4                         (33554530)
#define PID_DIRT_1                          (33554551)
#define PID_DIRT_2                          (33554552)
#define PID_DIRT_3                          (33554553)
#define PID_DIRT_4                          (33554554)
#define PID_DIRT_5                          (33554555)
#define PID_DIRT_6                          (33554556)
#define PID_ELEVATOR_SHAFT_1                (33555333)
#define PID_ELEVATOR_SHAFT_2                (33555334)
#define PID_FIRE_PIT                        (33555044)
#define PID_JUNK                            (33554541)
#define PID_METAL_BARREL_1                  (33554437)
#define PID_POT                             (33554804)
#define PID_ROCKS_1                         (33554522)
#define PID_ROCKS_2                         (33554523)
#define PID_ROCKS_3                         (33554524)
#define PID_ROCKS_4                         (33554525)
#define PID_ROCKS_5                         (33554542)
#define PID_ROCKS_6                         (33554710)
#define PID_ROCKS_7                         (33554711)
#define PID_ROCKS_8                         (33554712)
#define PID_ROCKS_9                         (33554860)
#define PID_ROCKS_10                        (33554861)
#define PID_ROCKS_11                        (33554862)
#define PID_ROCKS_12                        (33554863)
#define PID_ROCKS_13                        (33554864)
#define PID_ROCKS_14                        (33554865)
#define PID_ROCKS_15                        (33554866)
#define PID_ROCKS_16                        (33554867)
#define PID_RUG_1                           (33554808)
#define PID_RUG_2                           (33554809)
#define PID_RUG_3                           (33554810)
#define PID_SCRUB_1                         (33554534)
#define PID_SCRUB_2                         (33554535)
#define PID_SCRUB_3                         (33554536)
#define PID_SCRUB_4                         (33554537)
#define PID_TIRE                            (33554533)
#define PID_TRASH_1                         (33554743)
#define PID_TRASH_2                         (33554744)
#define PID_TRASH_3                         (33554745)
#define PID_TRASH_4                         (33554746)
#define PID_TRASH_CAN                       (33554747)
#define PID_TREE_1                          (33554748)
#define PID_TREE_2                          (33554749)
#define PID_TREE_3                          (33554750)
#define PID_TREE_4                          (33554751)
#define PID_TREE_5                          (33554752)
#define PID_TREE_6                          (33554753)
#define PID_TREE_OLD                        (33554498)
#define PID_WEED_1                          (33554557)
#define PID_WEED_2                          (33554558)
#define PID_WEED_3                          (33554559)
#define PID_WEEDS                           (33554540)
#define PID_WOODEN_TABLE_1                  (33554435)

// Door types:
#define PID_DOOR_METAL_EW                   (33554913)
#define PID_DOOR_METAL_NS                   (33554914)
#define PID_VDOOR_OLD_METAL_NS              (33554574)
#define PID_VDOOR_OLD_METAL_EW              (33554575)
#define PID_VDOOR_V13_METAL_EW              (33554454)
#define PID_VDOOR_V13_METAL_NS              (33554455)

// Fo1in2:
#define PID_RATHOLE                         (33556295)
#define PID_GIZMO_SIGN_OFF                  (33556296)
#define PID_TROPHY                          (33555332) // Junktown urn

// Destroyed Force Field Emitter - WALL PIDs!
#define PID_EMITTER_MBASE_NS                (50332785)
#define PID_EMITTER_MBASE_EW                (50332784)
#define PID_EMITTER_DESTROYED_NS            (50333282)
#define PID_EMITTER_DESTROYED_EW            (50333283)

// Motorcycle
#define PID_DRIVABLE_MOTO1                  (33556292)
#define PID_DRIVABLE_MOTO2                  (33556293)
#define PID_SIDECAR                         (33556294)

// Motorcycle Trunk
#define FID_MOTOTRUNK1                      (16777408)
#define FID_MOTOTRUNK2                      (16777409)

// Misc Commands

/************************************************
   Motorcycle
************************************************/
#define Create_Moto1(Hex_Num,Elevation)   if ((not(is_loading_game)) /*and (global_var(GVAR_PLAYER_GOT_CAR) != 0)*/) then begin               \
                                            Scenery_Creation:=create_object_sid(PID_DRIVABLE_MOTO1,Hex_Num,Elevation, SCRIPT_MOTRCYCL);   \
                                            Scenery_Creation_Hex:=Hex_Num;                                                                \
                                            Blocking_Cycle(5,1,Elevation)                                                                 \
                                            Blocking_Cycle(3,1,Elevation)                                                                 \
                                            Blocking_Cycle(1,2,Elevation)                                                                 \
                                            if (Trunk_Ptr != 0) then begin                                                                \
                                                move_to(Trunk_Ptr,Scenery_Creation_Hex,Elevation);                                        \
                                                debug_msg("Moving the Car Trunk");                                                        \
                                            end                                                                                           \
                                            else begin                                                                                    \
                                                create_object_sid(PID_MOTO1_TRUNK,Scenery_Creation_Hex,Elevation,SCRIPT_MOTRTRNK);        \
                                                debug_msg("Making new Trunk.");                                                           \
                                            end                                                                                           \
                                 Blocking_Cycle(2,1,Elevation)                                                                 \
                                 Blocking_Cycle(4,1,Elevation)                                                                 \
                                 /*debug("create motorcycle");*/ \
                                          end

#define Create_Moto2(Hex_Num,Elevation)   if (not(is_loading_game)) then begin                                                  \
                                            Scenery_Creation:=create_object_sid(PID_DRIVABLE_MOTO2,Hex_Num,Elevation, SCRIPT_MOTRCYCL);   \
                                            Scenery_Creation_Hex:=Hex_Num;                                                                \
                                            Blocking_Cycle(2,2,Elevation)                                                                 \
                                            Blocking_Cycle(4,2,Elevation)                                                                 \
                                 Blocking_Cycle(5,1,Elevation)                                                                 \
                                            if (Trunk_Ptr != 0) then begin                                                                \
                                                move_to(Trunk_Ptr,Scenery_Creation_Hex,Elevation);                                        \
                                                debug_msg("Moving the Car Trunk");                                                        \
                                            end                                                                                           \
                                            else begin                                                                                    \
                                                create_object_sid(PID_MOTO1_TRUNK,Scenery_Creation_Hex,Elevation,SCRIPT_MOTRTRNK);        \
                                                debug_msg("Making new Trunk.");                                                           \
                                            end                                                                                           \
                                 Blocking_Cycle(5,0,Elevation)                                                                 \
                                 Blocking_Cycle(0,1,Elevation)                                                                 \
                                 Blocking_Cycle(1,1,Elevation)                                                                 \
                                 /*debug("create motorcycle 2");*/ \
                                          end

#define Dest_Moto(Hex_Num,Elevation)      if (not(is_loading_game)) then begin                                                     \
                                            Scenery_Creation_Ptr:=tile_contains_pid_obj(Hex_Num,Elevation,PID_DRIVABLE_MOTO1);       \
                                            if (tile_contains_obj_pid(Hex_Num,Elevation,PID_DRIVABLE_MOTO1)) then begin              \
                                                destroy_object(Scenery_Creation_Ptr);                                              \
                                                Scenery_Creation_Hex:=Hex_Num;                                                     \
                                                Dest_Block_Cycle(5,1,Elevation)                                                    \
                                                Dest_Block_Cycle(3,1,Elevation)                                                    \
                                                Dest_Block_Cycle(1,2,Elevation)                                                    \
                                                Dest_Block_Cycle(2,1,Elevation)                                                    \
                                                Dest_Block_Cycle(4,1,Elevation)                                                    \
                                            end                                                                                    \
                                            Scenery_Creation_Ptr:=tile_contains_pid_obj(Hex_Num,Elevation,PID_DRIVABLE_MOTO2);     \
                                            if (tile_contains_obj_pid(Hex_Num,Elevation,PID_DRIVABLE_MOTO2)) then begin            \
                                                destroy_object(Scenery_Creation_Ptr);                                              \
                                                Scenery_Creation_Hex:=Hex_Num;                                                     \
                                                Dest_Block_Cycle(2,2,Elevation)                                                    \
                                                Dest_Block_Cycle(4,2,Elevation)                                                    \
                                                Dest_Block_Cycle(5,2,Elevation)                                                    \
                                                Dest_Block_Cycle(0,1,Elevation)                                                    \
                                                Dest_Block_Cycle(1,1,Elevation)                                                     \
                                            end                                                                                     \
                                          end

// This will make the car that the player drives along the world map
#define Create_Car(Hex_Num,Elevation)     if (global_var(GVAR_PLAYER_GOT_CAR)== 1) then begin         \
                                             Create_Moto1(Hex_Num,Elevation)                          \
                                          end                                                         \
                                          else if (global_var(GVAR_PLAYER_GOT_CAR)== 2) then begin    \
                                             Create_Moto2(Hex_Num,Elevation)                          \
                                          end

#define Dest_Car(Hex_Num,Elevation)     Dest_Moto(Hex_Num,Elevation)
#define Upgrade_Car(Hex_Num,Elevation)  if (global_var(GVAR_PLAYER_GOT_CAR)== 2) and (tile_contains_obj_pid(Hex_Num,Elevation,PID_DRIVABLE_MOTO1)) then begin \
                                 Dest_Moto(Hex_Num,Elevation)  \
                                 Create_Moto2(Hex_Num,Elevation) \
                              end


/************************************************
    Caravan carts
************************************************/
// This will make the East-West Caravans
#define Create_EW_Caravan(Pid,Hex_Num,Elevation)    Scenery_Creation:=create_object(Pid,Hex_Num,Elevation);                     \
                                                    Scenery_Creation_Hex:=Hex_Num;                                              \
                                                    Blocking_Cycle(1,1,Elevation)                                              \
                                                    Blocking_Cycle(3,2,Elevation)                                              \
                                                    Blocking_Cycle(4,2,Elevation)                                              \
                                                    Blocking_Cycle(5,1,Elevation)                                              \
                                                    Blocking_Cycle(0,1,Elevation)                                              \
                                                    Blocking_Cycle(5,1,Elevation)                                              \
                                                    Blocking_Cycle(1,2,Elevation)

#define Create_EW_Red_Caravan(Hex_Num,Elevation)    Create_EW_Caravan(PID_EW_RED_CARAVAN,Hex_Num,Elevation)
#define Create_EW_Grey_Caravan(Hex_Num,Elevation)   Create_EW_Caravan(PID_EW_GREY_CARAVAN,Hex_Num,Elevation)
#define Create_EW_Wood_Caravan(Hex_Num,Elevation)   Create_EW_Caravan(PID_EW_WOOD_CARAVAN,Hex_Num,Elevation)

#define Dest_Caravan_Cycle(Rot,Count,Elevation)   Scenery_Creation_Count:=0;                                                                             \
                                                while (Scenery_Creation_Count < Count) do begin                                                          \
                                                    Scenery_Creation_Hex:=tile_num_in_direction(Scenery_Creation_Hex,Rot,1);                             \
                                                    Scenery_Creation_Ptr:=tile_contains_pid_obj(Scenery_Creation_Hex,Elevation,PID_BLOCKING_HEX);        \
                                                    destroy_object(Scenery_Creation_Ptr);                                                                \
                                                    Scenery_Creation_Ptr:=tile_contains_pid_obj(Scenery_Creation_Hex,Elevation,PID_RED_CARAVAN_HANDLE);  \
                                                    destroy_object(Scenery_Creation_Ptr);                                                                \
                                                    Scenery_Creation_Ptr:=tile_contains_pid_obj(Scenery_Creation_Hex,Elevation,PID_GREY_CARAVAN_HANDLE); \
                                                    destroy_object(Scenery_Creation_Ptr);                                                                \
                                                    Scenery_Creation_Count+=1;                                                                           \
                                                end

// This will destroy the East-West Caravans
// TODO: Add wood caravan wagon from SD3!
#define Destroy_EW_Caravan(Hex_Num,Elevation)   if (not(is_loading_game)) then begin                                                  \
                                                /*Scenery_Creation_Ptr:=tile_contains_pid_obj(Hex_Num,Elevation,PID_EW_WOOD_CARAVAN);*/   \
                                                /*destroy_object(Scenery_Creation_Ptr);*/                                                 \
                                                Scenery_Creation_Ptr:=tile_contains_pid_obj(Hex_Num,Elevation,PID_EW_RED_CARAVAN);    \
                                                destroy_object(Scenery_Creation_Ptr);                                                 \
                                                Scenery_Creation_Ptr:=tile_contains_pid_obj(Hex_Num,Elevation,PID_EW_GREY_CARAVAN);   \
                                                destroy_object(Scenery_Creation_Ptr);                                                 \
                                                Scenery_Creation_Hex:=Hex_Num;                                                        \
                                                   Dest_Caravan_Cycle(1,1,Elevation)                                                  \
                                                   Dest_Caravan_Cycle(3,2,Elevation)                                                  \
                                                   Dest_Caravan_Cycle(4,2,Elevation)                                                  \
                                                   Dest_Caravan_Cycle(5,1,Elevation)                                                  \
                                                   Dest_Caravan_Cycle(0,1,Elevation)                                                  \
                                                   Dest_Caravan_Cycle(5,1,Elevation)                                                  \
                                                   Dest_Caravan_Cycle(1,2,Elevation)                                                  \
                                                end

// This will make North-South Caravans
#define Create_NS_Caravan(Pid,Hex_Num,Elevation)   Scenery_Creation:=create_object(Pid,Hex_Num,Elevation);     \
                                                   Scenery_Creation_Hex:=Hex_Num;                              \
                                                   Blocking_Cycle(5,1,Elevation)                              \
                                                   Blocking_Cycle(4,1,Elevation)                              \
                                                   if (Pid == PID_NS_RED_CARAVAN) then                                                              \
                                                      Scenery_Creation:=create_object(PID_RED_CARAVAN_HANDLE,Scenery_Creation_Hex,Elevation);      \
                                                   else                                                                                             \
                                                      Scenery_Creation:=create_object(PID_GREY_CARAVAN_HANDLE,Scenery_Creation_Hex,Elevation);     \
                                                    Blocking_Cycle(5,1,Elevation)                              \
                                                    Blocking_Cycle(1,2,Elevation)                              \
                                                    Blocking_Cycle(2,3,Elevation)                              \
                                                    Blocking_Cycle(3,2,Elevation)                              \
                                                    Blocking_Cycle(4,1,Elevation)                              \
                                                    Blocking_Cycle(5,3,Elevation)

#define Create_NS_Red_Caravan(Hex_Num,Elevation)   Create_NS_Caravan(PID_NS_RED_CARAVAN,Hex_Num,Elevation)
#define Create_NS_Grey_Caravan(Hex_Num,Elevation)  Create_NS_Caravan(PID_NS_GREY_CARAVAN,Hex_Num,Elevation)

// This will destroy the North-South Caravans
#define Destroy_NS_Caravan(Hex_Num,Elevation)   if (not(is_loading_game)) then begin                                                  \
                                                Scenery_Creation_Ptr:=tile_contains_pid_obj(Hex_Num,Elevation,PID_NS_RED_CARAVAN);    \
                                                destroy_object(Scenery_Creation_Ptr);                                                 \
                                                Scenery_Creation_Ptr:=tile_contains_pid_obj(Hex_Num,Elevation,PID_NS_GREY_CARAVAN);   \
                                                destroy_object(Scenery_Creation_Ptr);                                                 \
                                                Scenery_Creation_Hex:=Hex_Num;                                                        \
                                                   Dest_Caravan_Cycle(5,1,Elevation)                                                  \
                                                   Dest_Caravan_Cycle(4,1,Elevation)                                                  \
                                                Scenery_Creation_Ptr:=tile_contains_pid_obj(Hex_Num,Elevation,PID_RED_CARAVAN_HANDLE);   \
                                                destroy_object(Scenery_Creation_Ptr);                                                    \
                                                Scenery_Creation_Ptr:=tile_contains_pid_obj(Hex_Num,Elevation,PID_GREY_CARAVAN_HANDLE);  \
                                                destroy_object(Scenery_Creation_Ptr);                                                    \
                                                   Dest_Caravan_Cycle(5,1,Elevation)                                                  \
                                                   Dest_Caravan_Cycle(1,2,Elevation)                                                  \
                                                   Dest_Caravan_Cycle(2,3,Elevation)                                                  \
                                                   Dest_Caravan_Cycle(3,2,Elevation)                                                  \
                                                   Dest_Caravan_Cycle(4,1,Elevation)                                                  \
                                                   Dest_Caravan_Cycle(5,3,Elevation)                                                  \
                                                end

/************************************************
    Other stuff
************************************************/
// This will make the cave-in rocks with all the blocking Hexes
#define Create_Cave_In(Hex_Num,Elevation)   Scenery_Creation:=create_object(PID_CAVE_IN_ROCKS,Hex_Num,Elevation);                \
                                 Scenery_Creation_Hex:=tile_num_in_direction(Hex_Num,2,2);                               \
                                 Blocking_Cycle(1,1,Elevation)                                                           \
                                 Blocking_Cycle(2,1,Elevation)                                                           \
                                 Blocking_Cycle(1,1,Elevation)                                                           \
                                 Blocking_Cycle(0,3,Elevation)                                                           \
                                 Blocking_Cycle(5,1,Elevation)                                                           \
                                 Blocking_Cycle(0,1,Elevation)                                                           \
                                 Blocking_Cycle(5,4,Elevation)                                                           \
                                 Blocking_Cycle(0,1,Elevation)                                                           \
                                 Blocking_Cycle(5,3,Elevation)                                                           \
                                 Blocking_Cycle(4,1,Elevation)                                                           \
                                 Blocking_Cycle(3,6,Elevation)                                                           \
                                 Blocking_Cycle(2,1,Elevation)                                                           \
                                 Blocking_Cycle(3,1,Elevation)                                                           \
                                 Blocking_Cycle(2,1,Elevation)                                                           \
                                 Blocking_Cycle(3,1,Elevation)                                                           \
                                 Blocking_Cycle(2,2,Elevation)                                                           \
                                 Blocking_Cycle(1,2,Elevation)

// Blocking Hex Cycle
#define create_blocking_hex(the_tile, the_elev) move_to(create_object(PID_BLOCKING_HEX, the_tile, the_elev), the_tile, the_elev)
#define Blocking_Cycle(Rot,Count,Elevation)     Scenery_Creation_Count:=0;                                                              \
                                                while (Scenery_Creation_Count < Count) do begin                                         \
                                                    Scenery_Creation_Hex:=tile_num_in_direction(Scenery_Creation_Hex,Rot,1);            \
                                                    Scenery_Creation:=create_object(PID_BLOCKING_HEX,Scenery_Creation_Hex,Elevation);   \
                                                    Scenery_Creation_Count+=1;                                                          \
                                                end

#define remove_blocking_hex(the_tile, the_elev) destroy_object(tile_contains_pid_obj(the_tile,the_elev,PID_BLOCKING_HEX))
#define Dest_Block_Cycle(Rot,Count,Elevation)   Scenery_Creation_Count:=0;                                                              \
                                                while (Scenery_Creation_Count < Count) do begin                                         \
                                                    Scenery_Creation_Hex:=tile_num_in_direction(Scenery_Creation_Hex,Rot,1);            \
                                                    Scenery_Creation_Ptr:=tile_contains_pid_obj(Scenery_Creation_Hex,Elevation,PID_BLOCKING_HEX);   \
                                                    destroy_object(Scenery_Creation_Ptr);                                               \
                                                    Scenery_Creation_Count+=1;                                                          \
                                                end

// This will make the broken vault door
#define Create_Broken_VDoor(Pid,Hex_Num,Elevation)  Scenery_Creation:=create_object(Pid,Hex_Num,Elevation);                     \
                                                    Scenery_Creation_Hex:=Hex_Num;                                              \
                                                    Blocking_Cycle(1,1,Elevation)                                              \
                                                    Blocking_Cycle(2,2,Elevation)                                              \
                                                    Blocking_Cycle(3,2,Elevation)                                              \
                                                    Blocking_Cycle(4,1,Elevation)                                              \
                                                    Blocking_Cycle(5,3,Elevation)                                              \
                                                    Blocking_Cycle(0,2,Elevation)                                              \
                                                    Blocking_Cycle(1,1,Elevation)

// Destroyed vault door
#define Create_Vault_Door_Broken(Hex_Num,Elevation)    Create_Broken_VDoor(PID_VAULT_DOOR_BROKEN,Hex_Num,Elevation)

// This will see if a tile is blocked by a blocking hex
#define tile_is_blocked(the_tile, the_elev)        (tile_contains_pid_obj(the_tile, the_elev, PID_BLOCKING_HEX) != 0)

#endif // SCENEPID_H
