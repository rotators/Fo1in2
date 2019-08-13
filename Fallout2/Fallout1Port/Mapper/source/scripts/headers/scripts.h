#ifndef SCRIPTS_H
#define SCRIPTS_H

/*******************************************************************************
                               Номера скриптов
*******************************************************************************/

#define SCRIPT_OBJ_DUDE  (1)  //  obj_dude.int   ; player script -- was cr_dialg.int  ; Testing
#define SCRIPT_ELDER     (2)  //  elder.int      ; The Elder from Shady Sands
#define SCRIPT_BARTER    (3)  //  barter.int     ; The Barterman from Shady Sands
#define SCRIPT_BGUARD    (4)  //  bguard.int     ; Only a bodyguard from Shady Sands for the Barterman
#define SCRIPT_COW       (5)  //  cow.int        ; It's just a cow.
#define SCRIPT_MOATGRD   (6)  //  MoatGrd.int    ; Moat guard for the Gunrunners
#define SCRIPT_GUARD     (7)  //  guard.int      ; Guard from Shady Sands
#define SCRIPT_LOSER     (8)  //  loser.int      ; The loser from Shady Sands
#define SCRIPT_PLEASANT  (9)  //  pleasant.int   ; The pleasant peasant from Shady Sands                                        
#define SCRIPT_GUNRNR    (10)  //  GunRnr.int     ; generic gunrunner
#define SCRIPT_MAP_INIT  (11)  //  map_init.int   ; Map for the Vault for the E3 demo                                            
#define SCRIPT_RADSCORP  (12)  //  radscorp.int   ; Radiation Scorpions near Shady Sands                                         
#define SCRIPT_MUTANT2   (13)  //  mutant2.int    ; Invisible Mutants
#define SCRIPT_SSWELL    (14)  //  sswell.int     ; Shady Sands well
#define SCRIPT_SET       (15)  //  set.int        ; Set, the leader of Necropolis
#define SCRIPT_HARRY     (16)  //  harry.int      ; Harry the Super mutant
#define SCRIPT_STIMPACK  (17)  //  stimpack.int   ; Stimpack script to heal players when used
#define SCRIPT_COVER     (18)  //  cover.int      ; A cover for the Manhole
#define SCRIPT_MANHOLE   (19)  //  manhole.int    ; A manhole that leads to the Necropolis Sewers
#define SCRIPT_LADDER    (20)  //  ladder.int     ; Ladder leading down to the Necropolis Sewers
#define SCRIPT_CHAIR     (21)  //  chair.int      ; A chairs in the hotel which you shouldn't sit on
#define SCRIPT_COKE      (22)  //  coke.int       ; Nuka-Cola machine which lucky players can get money
#define SCRIPT_COMPUTER  (23)  //  computer.int   ; A broken computer in the managers office.                                    
#define SCRIPT_DEAD      (24)  //  dead.int       ; Look at the dead bodies, daddy
#define SCRIPT_DESK      (25)  //  desk.int       ; Standard, Master-issued desk, complete with nothing
#define SCRIPT_1DEDGUL1  (26)  //  1dedgul1.int   ; Dead ghouls (?)                                                              
#define SCRIPT_1MOLRAT1  (27)  //  1molrat1.int   ; Mole Rat in Necropolis (?)                                                   
#define SCRIPT_1MANHOL1  (28)  //  1manhol1.int   ; Manhole to get to the Sewers in Necropolis (?)                               
#define SCRIPT_1LADDER1  (29)  //  1ladder1.int   ; Ladder for the Manhole in Necropolis (?)                                     
#define SCRIPT_GHOUL     (30)  //  ghoul.int      ; Ghoul manager of the Necropolis hotel
#define SCRIPT_ALPHHOTL  (31)  //  alphhotl.int   ; Map Script for Pre-Alpha demo                                                
#define SCRIPT_GENGHOUL  (32)  //  genghoul.int   ; Generic Ghoul from Necropolis
#define SCRIPT_ARADESH   (33)  //  Aradesh.int    ; Aradesh NPC from Shady Sands
#define SCRIPT_BRAHMIN   (34)  //  Brahmin.int    ; Brahmin (cows) from Junktown who just stand there
#define SCRIPT_COUGAR    (35)  //  Cougar.int     ; Doc Morbid's Assistant, Cougar, from Junktown
#define SCRIPT_FLASH     (36)  //  Flash.int      ; Doc Morbid's Assistant, Flash, from Junktown
#define SCRIPT_JTGENGRD  (37)  //  JtGenGrd.int   ; Generic guards from Junktown                                                 
#define SCRIPT_JTPEASNT  (38)  //  JtPeasnt.int   ; Generic peasants from Junktown                                               
#define SCRIPT_BUTCH     (39)  //  Butch.int      ; Butch, leader of some merchants in Hub
#define SCRIPT_CABBOT    (40)  //  Cabbot.int     ; Cabbot, the initiate from the Brotherhood of Steel
#define SCRIPT_CHILDMEM  (41)  //  Childmem.int   ; Children of the Cathedral member                                             
#define SCRIPT_DECKER    (42)  //  Decker.int     ; Decker, the head of the Hub Underground
#define SCRIPT_CRVNDRVR2  (43)  //  crvndrvr.int   ; Caravan driver for the random encounters      DEPRECATED!!!!
#define SCRIPT_GIZMO     (44)  //  Gizmo.int      ; Gizmo, the casino owner in Junktown
#define SCRIPT_HAROLD    (45)  //  Harold.int     ; Harold, the old mutant from the Hub
#define SCRIPT_JAIN      (46)  //  Jain.int       ; Jain, Priestess of the Children of the Cathedral
#define SCRIPT_KILLIAN   (47)  //  Killian.int    ; Killian, law enforcement in Junktown
#define SCRIPT_LAURA     (48)  //  Laura.int      ; Laura, the spy for the Followers of the Apocalypse
#define SCRIPT_LOXLEY    (49)  //  Loxley.int     ; Loxley, head of the Thieve's Guild in the hub
#define SCRIPT_LT        (50)  //  Lt.int         ; The Lieutenant of the Master's army
#define SCRIPT_MASTER    (51)  //  Master.int     ; The general Bad guy of the entire game
#define SCRIPT_MAXSON    (52)  //  Maxson.int      ; General John Maxson, High Elder of the Brotherhood of Steel
#define SCRIPT_MORPH     (53)  //  Morph.int       ; Morpheus (not relation to Orpheus) of the Children (power hungry)
#define SCRIPT_NICOLE    (54)  //  Nicole.int      ; Yes, it is the same Nicole from the Followers of the Apocalypse
#define SCRIPT_OVER      (55)  //  Over.int        ; The great Overseer of Vault 13 (chicken)
#define SCRIPT_RHOMBUS   (56)  //  Rhombus.int     ; Rhombus, the Armsmaster for the Brotherhood of Steel
#define SCRIPT_TANDI     (57)  //  Tandi.int       ; Tandi, the minx from Shady Sands
#define SCRIPT_VREE      (58)  //  Vree.int        ; Vree, the Scribe from the Brotherhood of Steel
#define SCRIPT_1MOLERAT  (59)  //  1MoleRat.int    ; Mole Rat Boss (nasty guy)                                                   
#define SCRIPT_AIRLOCK   (60)  //  AirLock.int     ; Open this Airlock, and we all look at space
#define SCRIPT_BARRY     (61)  //  Barry.int       ; Barry the Super Mutant
#define SCRIPT_DEADCOMP  (62)  //  DeadComp.int    ; Capt'n, the Computer's dead.                                                
#define SCRIPT_DOOR      (63)  //  Door.int        ; Sorry, the door has a lock on it. Try to pick it.
#define SCRIPT_GANGER    (64)  //  Ganger.int      ; I'm afraid of all these Ganger ghouls.
#define SCRIPT_GARY      (65)  //  Gary.int        ; Uh oh. It's Gary the Super Mutant
#define SCRIPT_GENERIC   (66)  //  Generic.int     ; Hey Mom! Look at the generic Ghouls
#define SCRIPT_DEPRECATED_9 (67) //SCRIPT_GENGHOUL  (67)  //  GenGhoul.int    ; scripts.lst - DONOTUSE wtf??????                          
#define SCRIPT_GENGLOW1  (68)  //  GenGlow1.int    ; It's a Generic Glowing One                                                  
#define SCRIPT_GHDEAD    (69)  //  GhDead.int      ; It's a dead ghoul that we see here.
#define SCRIPT_GHDORGRD  (70)  //  GhDorGrd.int    ; Ghoul Door Guard.                                                           
#define SCRIPT_GHGENDED  (71)  //  GhGenDed.int    ; Generic dead ghouls for Necropolis.                                         
#define SCRIPT_GHGUARD   (72)  //  GhGuard.int     ; Ghoul guard for Set.
#define SCRIPT_DEPRECATED_10 (73) //SCRIPT_GHOUL     (73)  //  Ghoul.int       ; scripts.lst - DONOTUSE wtf??????
#define SCRIPT_GHREFUGE  (74)  //  GhRefuge.int    ; Ghoul Refugee hiding the the Zombie hideout                                 
#define SCRIPT_GHZERO    (75)  //  GhZero.int      ; A ghoul guard
#define SCRIPT_GLOWONE   (76)  //  GlowOne.int     ; Glowing Ones that are caged by Set.
#define SCRIPT_GROUNDR   (77)  //  Groundr.int     ; Necropolis Undergrounders
#define SCRIPT_DEPRECATED_11 (78) //SCRIPT_GUARD     (78)  //  Guard.int       ; scripts.lst - DONOTUSE wtf??????
#define SCRIPT_DEPRECATED_12 (79) //SCRIPT_HARRY     (79)  //  Harry.int       ; scripts.lst - DONOTUSE wtf??????
#define SCRIPT_LARRY     (80)  //  Larry.int       ; Larry the Super Mutant
#define SCRIPT_LEADER    (81)  //  Leader.int      ; The ghoul leader in Necropolis (Ganger?)
#define SCRIPT_DEPRECATED_13 (82) //SCRIPT_MANAGER   (82)  //  Manager.int     ; scripts.lst - DONOTUSE wtf??????
#define SCRIPT_MANGLED   (83)  //  Mangled.int     ; Some mangled bodies in Necropolis.
#define SCRIPT_MEANDER   (84)  //  Meander.int     ; Some meandering ghouls
#define SCRIPT_DEPRECATED_14 (85) //SCRIPT_MUTANT2   (85)  //  Mutant2.int     ; scripts.lst - DONOTUSE wtf??????
#define SCRIPT_NH2OCOMP  (86)  //  NH2OComp.int    ; Necropolis Water Computer                                                   
#define SCRIPT_NH2OPUMP  (87)  //  NH2OPump.int    ; Necropolis Water Pump                                                       
#define SCRIPT_ODDWALL   (88)  //  OddWall.int     ; There is something odd about this wall in Necropolis
#define SCRIPT_PRISONR   (89)  //  Prisonr.int     ; Prisoner of the Super Mutants in Necropolis
#define SCRIPT_SALLY     (90)  //  Sally.int       ; Sally the male Super Mutant (sex change??)
#define SCRIPT_GRAFFITI  (91)  //  graffiti.int    ; generic graffiti on the walls                                               
#define SCRIPT_SETCOLER  (92)  //  SetColer.int    ; Cooler in Set's room which has goodies.                                     
#define SCRIPT_SETDESK   (93)  //  SetDesk.int     ; Set's desk which has a note on it
#define SCRIPT_SETDOOR1  (94)  //  SetDoor1.int    ; Door to Set's room that is trapped                                          
#define SCRIPT_SETGUARD  (95)  //  SetGuard.int    ; Guards to protect Set from Harm.                                            
#define SCRIPT_SETSCTDR  (96)  //  SetSctDr.int    ; Set's Secret Door.                                                          
#define SCRIPT_SMELL     (97)  //  Smell.int       ; It's an odd smell in Necropolis (must be ghouls?)
#define SCRIPT_DEPRECATED_15 (98) //SCRIPT_STIMPACK  (98)  //  StimPack.int    ; scripts.lst - DONOTUSE wtf??????                                              
#define SCRIPT_STOREROM  (99)  //  StoreRom.int    ; Spacial script for the Necropolis store room                                
#define SCRIPT_SUPER     (100)  //  Super.int       ; Super Mutants from the city Necropolis
#define SCRIPT_TERRY     (101)  //  Terry.int       ; Terry the Super Mutant (fly away)
#define SCRIPT_GARRET    (102)  //  Garret.int      ; Set's lacky in Necropolis
#define SCRIPT_GRETCH    (103)  //  Gretch.int      ; Gretch, Doctor Morbid's Assistant
#define SCRIPT_MORBID    (104)  //  Morbid.int      ; Doctor in Junktown known for taking body parts
#define SCRIPT_DUMAR     (105)  //  Dumar.int       ; Dumar, Acrolyte of the Children
#define SCRIPT_BARSTOW   (106)  //  Barstow.int     ; Zack Barstow, Initiate of the Children
#define SCRIPT_GENINT    (107)  //  Genint.int      ; generic initiates for Children
#define SCRIPT_JCHIDMEM  (108)  //  JChidMem.int    ; Junktown Children of the Cathedral Member                                   
#define SCRIPT_LOOKOUT   (109)  //  Lookout.int     ; Necropolis Undergrounder Lookout
#define SCRIPT_MACHIV    (110)  //  MachIV.int      ; Mach IV computer in Buried Vaul that is broken
#define SCRIPT_BLKROOM   (111)  //  BlkRoom.int     ; Spacial to say the room is blocked in the Buried Vault
#define SCRIPT_RNDDESRT  (112)  //  RndDesrt.int    ; Random Encounter Desert Map                                                 
#define SCRIPT_TGUARD    (113)  //  TGuard.int      ; Tower Guard for Shady Sands
#define SCRIPT_COOK      (114)  //  cook.int        ; A cook from Shady Sands kitchen
#define SCRIPT_CITIZEN   (115)  //  citizen.int     ; Random Citizen from Shady Sands
#define SCRIPT_HOUSCHAR  (116)  //  HousChar.int    ; A chair in the House of a citizen from Shady Sands                          
#define SCRIPT_AGATHBED  (117)  //  AgathBed.int    ; Bed in Agatha's room from Shady Sands                                       
#define SCRIPT_ROZBED    (118)  //  RozBed.int      ; Bed in Razlo's room from Shady sands
#define SCRIPT_WIFE      (119)  //  Wife.int        ; Razlo's wife from Shady Sands
#define SCRIPT_SDRESSER  (120)  //  SDresser.int    ; Dresser for Razlo or Agatha in Shady Sands                                  
#define SCRIPT_SHADYRUG  (121)  //  ShadyRug.int    ; Generic Rugs in Shady Sands                                                 
#define SCRIPT_SBOKCASE  (122)  //  SBokcase.int    ; Shady Sands bookcase with books                                             
#define SCRIPT_MUTEJAR   (123)  //  MuteJar.int     ; A jar of Mutated Fruit from Shady Sands
#define SCRIPT_SHADDESK  (124)  //  ShadDesk.int    ; Desk in Aradesh's room from Shady Sands                                     
#define SCRIPT_COOKSHEL  (125)  //  CookShel.int    ; Shelf with food on them for the Kitchen in Shady Sands                      
#define SCRIPT_COOKTABL  (126)  //  CookTabl.int    ; Table in the Kitchen in Shady Sands which holds food.                       
#define SCRIPT_FRUIT     (127)  //  Fruit.int       ; Mutated fruit in the Gardens of Shady Sands
#define SCRIPT_PENSMELL  (128)  //  PenSmell.int    ; Spacial script for the smell around the Brahmin Pen                         
#define SCRIPT_RAZLO     (129)  //  Razlo.int       ; Razlo from Shady Sands. Local Healer
#define SCRIPT_VALTCTZN  (130)  //  ValtCtzn.int    ; Vault 13 citizen with random lines                                          
#define SCRIPT_VALTLOCK  (131)  //  ValtLock.int    ; Vault 13 airlock.                                                           
#define SCRIPT_VALTMON   (132)  //  ValtMon.int     ; Vault 13 Monitor in the Meeting Room
#define SCRIPT_CORECOMP  (133)  //  CoreComp.int    ; Central Core computers in Vault 13                                          
#define SCRIPT_LIBCOMP   (134)  //  LibComp.int     ; Library computer in Vault 13
#define SCRIPT_ASSBLOW   (135)  //  Assblow.int     ; Guard in Junktown, real name is now Kalnor
#define SCRIPT_GENRAIDR  (136)  //  GenRaidr.int    ; Generic Raiders                                                             
#define SCRIPT_GARL      (137)  //  Garl.int        ; Garl from the Raiders' camp
#define SCRIPT_RAIDPRIS  (138)  //  RaidPris.int    ; Raider prisoner in the camp                                                 
#define SCRIPT_PETROX    (139)  //  Petrox.int      ; Petrox, a Raider from the camp
#define SCRIPT_TOLYA     (140)  //  Tolya.int       ; Tolya, a Desert Raider
#define SCRIPT_GWEN      (141)  //  Gwen.int        ; One of Garl's "Advisors." She is mean.
#define SCRIPT_DIANA     (142)  //  Diana.int       ; One of the Raiders who repairs raider equipment.
#define SCRIPT_ALYA      (143)  //  Alya.int        ; High spirited female Raider
#define SCRIPT_LIVINGQ   (144)  //  LivingQ.int     ; Spacial in the living quarters of the Buried Vault
#define SCRIPT_MEETING   (145)  //  Meeting.int     ; Spacial in the Meeting room of the Buried Vault
#define SCRIPT_BVSTORE   (146)  //  BVStore.int     ; Spacial in the Storage room of the Buried Vault
#define SCRIPT_BVLIB     (147)  //  BVLib.int       ; Spacial in the Library of the Buried Vault.
#define SCRIPT_BVCORE    (148)  //  BVCore.int      ; Spacial in the Central Core of the Buried Vault
#define SCRIPT_BVMEET    (149)  //  BVMeet.int      ; Spacial in the Meeting room of Buried Vault (rat tunnel).
#define SCRIPT_BVLIVE    (150)  //  BVLive.int      ; Spacial in the Living Quarters of Buried Vault (key in chair).
#define SCRIPT_UNDRBED   (151)  //  UndrBed.int     ; Spacial in Living Quarters of Buried Vault (under bed)
#define SCRIPT_RUBCHIP   (152)  //  RubChip.int     ; Spacial in Rubble of Buried Vault. Chip is buried
#define SCRIPT_RUBCORE   (153)  //  RubCore.int     ; Spacial in Rubble of Buried Vault. Core is buried
#define SCRIPT_BVAIRL    (154)  //  BVAirL.int      ; Spacial for Buried Vault. (Airlock)
#define SCRIPT_HALLDED1  (155)  //  HallDed1.int    ; Map script for Hall of Dead                                                 
#define SCRIPT_GABRIEL   (156)  //  Gabriel.int     ; Gabe, the leader of the GunRunners
#define SCRIPT_HICRAPS   (157)  //  HiCraps.int     ; Hi stakes craps game
#define SCRIPT_NUP2DWN1  (158)  //  NUp2Dwn1.int    ; jump from Ground-level to Sewers (Northern most) (Hall Dead)      
#define SCRIPT_NUP2DWN2  (159)  //  NUp2Dwn2.int    ; jump from Ground-level to Sewers (Southern most) (Hall Dead)      
#define SCRIPT_NDWN2UP1  (160)  //  NDwn2Up1.int    ; jump from Sewers to Ground-level (Northern most) (Hall Dead)      
#define SCRIPT_NDWN2UP2  (161)  //  NDwn2Up2.int    ; jump from Sewers to Ground-level (Southern most) (Hall Dead)      
#define SCRIPT_GATEDEMO  (162)  //  GateDemo.int    ; Generic gate guard for the demo                                             
#define SCRIPT_WTRGRD    (163)  //  WtrGrd.int       ; Water guard for Vault 13
#define SCRIPT_WATRSHED  (164)  //  WatrShed.int    ; Map script for the Necrop Water                                             
#define SCRIPT_NWUP2DN1  (165)  //  NWUp2Dn1.int    ; jump from Ground-level to Sewers (West) (Necrop Water Shed)       
#define SCRIPT_NWUP2DN2  (166)  //  NWUp2Dn2.int    ; jump from Ground-level to Sewers (North) (Necrop Water Shed)      
#define SCRIPT_NWUP2DN3  (167)  //  NWUp2Dn3.int    ; jump from Ground-level to Sewers (South) (Necrop Water Shed)      
#define SCRIPT_CINDY     (168)  //  Cindy.int        ; Person getting rations from Vault 13
#define SCRIPT_NWDN2UP1  (169)  //  NWDn2Up1.int    ; jump from Sewers to Ground-level (North) (Necrop Water Shed)      
#define SCRIPT_NWDN2UP2  (170)  //  NWDn2Up2.int    ; jump from Sewers to Ground-level (West) (Necrop Water Shed)       
#define SCRIPT_NWDN2UP3  (171)  //  NWDn2Up3.int    ; jump from Sewers to Ground-level (South) (Necrop Water Shed)      
#define SCRIPT_ANDREW    (172)  //  Andrew.int      ; Jail gaurd for the junktown cells
#define SCRIPT_HOTELMAP  (173)  //  HotelMap.int    ; Map script for Necrop Hotel                                                 
#define SCRIPT_LORRAINE  (174)  //  Lorraine.int    ; Lorraine from the Boneyard                                                  
#define SCRIPT_NHUP2DN1  (175)  //  NHUp2Dn1.int    ; jump from Ground-level to Sewers (North) (Necrop Hotel)           
#define SCRIPT_NHUP2DN2  (176)  //  NHUp2Dn2.int    ; jump from Ground-level to Sewers (West) (Necrop Hotel)            
#define SCRIPT_NHUP2DN3  (177)  //  NHUp2Dn3.int    ; jump from Ground-level to Sewers (East) (Necrop Hotel)            
#define SCRIPT_OFFICER   (178)  //  Officer.int       ; Officer from Vault 13
#define SCRIPT_NHDN2UP1  (179)  //  NHDn2Up1.int    ; jump from Sewers to Ground-level (North) (Necrop Hotel)           
#define SCRIPT_NHDN2UP2  (180)  //  NHDn2Up2.int    ; jump from Sewers to Ground-level (West) (Necrop Hotel)            
#define SCRIPT_NHDN2UP3  (181)  //  NHDn2Up3.int    ; jump from Sewers to Ground-level (East) (Necrop Hotel)            
#define SCRIPT_RADSCAVE  (182)  //  RadSCave.int    ; Map Script for Rad Scorpion Caves                                           
#define SCRIPT_SETH      (183)  //  Seth.int        ; Seth from Shady Sands to transport to Rad Scorpion Caves.
#define SCRIPT_MEDIC     (184)  //  Medic.int       ; Medic from Vault 13.
#define SCRIPT_GENVAULT  (185)  //  GenVault.int    ; Generic Vault 13 dweller.                                                   
#define SCRIPT_JUNKCAS   (186)  //  JunkCas.int     ; Map Script for Casino area in Junktown
#define SCRIPT_JUNKKILL  (187)  //  JunkKill.int    ; Map Script for Killian's area in Junktown                                   
#define SCRIPT_JUNKENT   (188)  //  JunkEnt.int     ; Map Script for Entrance to Junktown
#define SCRIPT_BLKROM    (189)  //  BLKROM.int       ; blocked room in the buried vault
#define SCRIPT_BVAIR     (190)  //  BVAIR.int       ; buried vault air lock
#define SCRIPT_BVCACHE   (191)  //  BVCache.int       ; cache of medical suppies in the buried vault
#define SCRIPT_BVENT     (192)  //  BVEnt.int       ; Buried Vault ENtrance
#define SCRIPT_SHADYET   (193)  //  ShadyEt.int     ; Map Script for Shady Sands East
#define SCRIPT_SHADYWST  (194)  //  ShadyWst.int    ; Map Script for Shady Sands West                                             
#define SCRIPT_MEDLAB    (195)  //  MEDLAB.int       ; medlab in front of the buried vault
#define SCRIPT_SHACK     (196)  //  Shack.int       ; Shack above the buried vault
#define SCRIPT_SETH2     (197)  //  Seth2.int       ; Seth from Rad Scorpion Caves to transport to Shady Sands
#define SCRIPT_SCRIBEA   (198)  //  scribeA.int       ; Scribe from the brotherhood
#define SCRIPT_VAULT13   (199)  //  Vault13.int     ; Map Script for Vault 13
#define SCRIPT_BVELV1W   (200)  //  BVElv1W.int     ; Buried Vault Elevator. Level 1 West --> Level 2 East
#define SCRIPT_BVELV2E   (201)  //  BVElv2E.int     ; Buried Vault Elevator. Level 2 East --> Level 1 West
#define SCRIPT_BVELV2W   (202)  //  BVElv2W.int     ; Buried Vault Elevator. Level 2 West --> Level 3
#define SCRIPT_BVELV3    (203)  //  BVElv3.int      ; Buried Vault Elevator. Level 3 --> Level 2 West
#define SCRIPT_BVBROKEN  (204)  //  BVBroken.int    ; Buried Vault. The elevator is broken                                        
#define SCRIPT_BROHDENT  (205)  //  BroHdEnt.int    ; Map Script for Brotherhood of Steel Entrance                                
#define SCRIPT_RATPIT    (206)  //  RatPit.int      ; Breeding Pit of rats in Vault 13 area
#define SCRIPT_FEARDARK  (207)  //  FearDark.int    ; Vault 13. If the player is afraid of the dark                               
#define SCRIPT_VALTLEAV  (208)  //  ValtLeav.int    ; First time leaving Vault 13                                                 
#define SCRIPT_VALTCUPL  (209)  //  ValtCupl.int    ; Couple from Vault 13 who take your room                                     
#define SCRIPT_YOURROOM  (210)  //  YourRoom.int    ; Spacial Script for your room.                                               
#define SCRIPT_SSGUIDE   (211)  //  SSGuide.int     ; Shady Sands Guide to help the player get started.
#define SCRIPT_LITELEAV  (212)  //  LiteLeav.int    ; Light showing from outside world                                  
#define SCRIPT_VALTCORE  (213)  //  ValtCore.int    ; Spacial Script for Vault 13 Central Core                                    
#define SCRIPT_VCOMPOP   (214)  //  VCompOp.int     ; Water Computer in Vault 13 Operations Room
#define SCRIPT_VALTOP    (215)  //  ValtOp.int      ; Spacial Script for Vault 13 Operations
#define SCRIPT_VALTSEC   (216)  //  ValtSec.int     ; Spacial Script for Vault 13 Security
#define SCRIPT_VALTSTOR  (217)  //  ValtStor.int    ; Spacial Script for Vault 13 Storage                                         
#define SCRIPT_VALTMEET  (218)  //  ValtMeet.int    ; Spacial Script for Vault 13 Meeting room                                    
#define SCRIPT_VALTMED   (219)  //  ValtMed.int     ; Spacial Script for Vault 13 Medical Lab
#define SCRIPT_JUNKDEMO  (220)  //  JunkDemo.int    ; Map Script for Junkdemo.Map (for demo)                                      
#define SCRIPT_GUARDEMO  (221)  //  GuarDemo.int    ; Junktown guard w/ pickpocket (for demo)                                     
#define SCRIPT_WANRATS   (222)  //  WanRats.int     ; Wandering, Hostile rats
#define SCRIPT_FLARE     (223)  //  Flare.int       ; flares to light the player's way
#define SCRIPT_VALEL1    (224)  //  ValEl1.int      ; Vault 13 Elevator level 1
#define SCRIPT_VALEL2W   (225)  //  ValEl2w.int     ; Vault 13 Elevator level 2 west
#define SCRIPT_VALEL2E   (226)  //  ValEl2e.int     ; Vault 13 Elevator level 2 east
#define SCRIPT_VALEL3    (227)  //  ValEl3.int      ; Vault 13 Elevator level 3
#define SCRIPT_VAULTBUR  (228)  //  Vaultbur.int    ; Map Script for Buried Vault                                                 
#define SCRIPT_DOG       (229)  //  dog.int         ; a dog that wanders around
#define SCRIPT_GHRNDGRD  (230)  //  GhRndGrd.int    ; Random Ghoul Guard in Necropolis                                            
#define SCRIPT_GHKICK    (231)  //  GhKick.int      ; Ghoul who is going to kick your...
#define SCRIPT_MUTANT3   (232)  //  Mutant3.int     ; Super Mutant in Hall Dead. Guards door (no move)
#define SCRIPT_MUTANT4   (233)  //  Mutant4.int     ; Super Mutant in Hall Dead. Guards door (paces/checks for dead mutant3)
#define SCRIPT_MUTANT5   (234)  //  Mutant5.int     ; Super Mutant in Necropolis (place holder)
#define SCRIPT_IAN       (235)  //  Ian.int         ; Injured Shady Sands guard
#define SCRIPT_CURTIS    (236)  //  Curtis.int      ; Shady Sands farmer
#define SCRIPT_CHILD     (237)  //  Child.int       ; a generic Child
#define SCRIPT_RAIDMAP   (238)  //  RaidMap.int     ; Map Script for the Raider Camp
#define SCRIPT_MUTFRUIT  (239)  //  MutFruit.int    ; Mutated Fruits (heals but gives rad damage)                                 
#define SCRIPT_RAIDGRD   (240)  //  RaidGrd.int     ; Raider Guard
#define SCRIPT_HUNTER    (241)  //  Hunter.int      ; Bounty Hunter collecting on the Child killer's head
#define SCRIPT_DOG2      (242)  //  Dog2.int        ; Dog that follows you around if you are Mad Maxx
#define SCRIPT_DUC       (243)  //  Duc.int         ; Trader to Shady Sands
#define SCRIPT_RNDCITY   (244)  //  RndCity.int     ; Map Script for Random City encounter
#define SCRIPT_RNDCOAST  (245)  //  RndCoast.int    ; Map Script for Random Coastal encounters                                    
#define SCRIPT_RNDMTN    (246)  //  RndMtn.int      ; Map Script for Random Mountain encounters
#define SCRIPT_GAMBLER   (247)  //  Gambler.int     ; Gambler in Junktown who appears in The Hub later on.
#define SCRIPT_VAULTENT  (248)  //  VaultEnt.int    ; Map script for Vault Entrance                                               
#define SCRIPT_MILES     (249)  //  Miles.int       ; The chemist of Adytum
#define SCRIPT_SMITTY    (250)  //  Smitty.int      ; Adytum's blacksmith
#define SCRIPT_ADYTOWNR  (251)  //  Adytownr.int    ; Generic script for an Adytowner                                             
#define SCRIPT_REGULATR  (252)  //  Regulatr.int    ; Generic Regulator, guard of Adytown                               
#define SCRIPT_DEPRECATED_16 (253) //SCRIPT_LORRI     (253)  //  scripts.lst - DONOTUSE wtf??????
#define SCRIPT_SAMMAEL   (254)  //  Sammael.int     ; Scav from Adytum
#define SCRIPT_CALEB     (255)  //  Caleb.int       ; Head of the Regulators from Adytum
#define SCRIPT_TAYLOR    (256)  //  Taylor.int      ; Shop keeper/trader from Adytum
#define SCRIPT_JULIANNA  (257)  //  Julianna.int       ; Julianna from the Adytum                                                 
#define SCRIPT_FOLSCHOL  (258)  //  FolSchol.int    ; A scholar from the Followers                                                
#define SCRIPT_FOLINIT   (259)  //  FolInit.int     ; An initiate from the Follower
#define SCRIPT_FLSUPMUT  (260)  //  FlSupMut.int    ; Super Mutant in the Followers area                                          
#define SCRIPT_CHIDSCOL  (261)  //  ChidScol.int    ; a scholar from the Children                                                 
#define SCRIPT_CHIDINIT  (262)  //  ChidInit.int    ; An Initiate from the Children                                               
#define SCRIPT_FOLSCOUT  (263)  //  FolScout.int    ; A Scout for the Followers                                                   
#define SCRIPT_FOLGUARD  (264)  //  FolGuard.int    ; A Guard for the Followers                                                   
#define SCRIPT_THSUPMUT  (265)  //  ThSupMut.int    ; Generic Thinker Super Mutant in the Boneyard                                
#define SCRIPT_HEATHER   (266)  //  Heather.int     ; Heather, a spy for the Children
#define SCRIPT_PETER     (267)  //  Peter.int       ; Head of the Follower's scouts
#define SCRIPT_JAKE      (268)  //  Jake.int        ; second in command of the Followers
#define SCRIPT_ORFEO     (269)  //  Orfeo.int       ; Senior Children member in Boneyard
#define SCRIPT_MARNEY    (270)  //  Marney.int      ; The Doctor/Nurse of the Followers
#define SCRIPT_NEIL      (271)  //  Neil.int        ; Neil, head of the Followers guard
#define SCRIPT_AMBER     (272)  //  Amber.int       ; teacher for the Followers
#define SCRIPT_UTHERN    (273)  //  Uthern.int      ; Leader of the Super Mutant Scouts in Boneyard
#define SCRIPT_TALIUS    (274)  //  Talius.int      ; A ghoul Follower in the Boneyard
#define SCRIPT_CHDGUARD  (275)  //  ChdGuard.int    ; Generic Children guard in Boneyard                                          
#define SCRIPT_CHDSCOUT  (276)  //  ChdScout.int    ; Generic Children scout in Boneyard                                          
#define SCRIPT_SCSUPMUT  (277)  //  ScSupMut.int    ; Generic Scout Super Mutant in the Boneyard                                  
#define SCRIPT_RAZOR     (278)  //  Razor.int       ; Razor, leader of the Blades
#define SCRIPT_BLADE     (279)  //  Blade.int       ; Generic Blades from the Boneyard
#define SCRIPT_FIRE      (280)  //  Fire.int        ; Fire, second in command of the Blades
#define SCRIPT_BECA      (281)  //  Beca.int        ; Beca and Jade. Quartermistress of the Blades
#define SCRIPT_DOLGAN    (282)  //  Dolgan.int      ; Dolgan, the weaponmaster from the Blades
#define SCRIPT_MICHELLE  (283)  //  Michelle.int    ; Michelle, leader of the scouts for the Blades                               
#define SCRIPT_DRAGON    (284)  //  Dragon.int      ; Dragon, Night watchman for the Blades
#define SCRIPT_ROMERO    (285)  //  Romero.int      ; Just a Blade in love w/ some chick in Adytum
#define SCRIPT_BROHD12   (286)  //  Brohd12.int     ; Map Script of the Brotherhood of Steel (level 1,2)
#define SCRIPT_BROHD34   (287)  //  Brohd34.int     ; Map Script for Brotherhood of Steel (level 3,4)
#define SCRIPT_JON       (288)  //  Jon.int         ; John Zimmerman from the Adytum
#define SCRIPT_RIPPPRIS  (289)  //  RippPris.int    ; Ripper Prisoner in the Boneyard                                             
#define SCRIPT_SCRIBEB   (290)  //  ScribeB.int       ; Another scribe from the brotherhood
#define SCRIPT_BVLAD     (291)  //  BVLad.int       ; Buried Vault Ladder which leads to the Surface
#define SCRIPT_CHARBODY  (292)  //  CharBody.int    ; A charred body in the Glow                                                  
#define SCRIPT_BONEBODY  (293)  //  BoneBody.int    ; dry bones from a body in the Glow                                           
#define SCRIPT_DEADBRO   (294)  //  DeadBro.int     ; the corpses of dead Brotherhood people
#define SCRIPT_GENDISK   (295)  //  GenDisk.int     ; Generic  Holodisks found in the Glow
#define SCRIPT_HOTSPOT   (296)  //  HotSpot.int     ; Radiation Hot Spot in the Glow (Spatial script)
#define SCRIPT_PERNPWR   (297)  //  PerNPwr.int     ; Dead person in Power Armour in the Glow.
#define SCRIPT_GLO1WEAP  (298)  //  Glo1Weap.int    ; Glow Level 1 Weapon Depot door.                                             
#define SCRIPT_GLOCOMP   (299)  //  GloComp.int     ; Computer ZR32 from the Glow.
#define SCRIPT_GLO3SUPL  (300)  //  Glo3Supl.int    ; Glow Level 3 Supply Depot door.                                             
#define SCRIPT_GLOWGEN   (301)  //  GlowGen.int     ; The generator for the Glow.
#define SCRIPT_GLOWPUMP  (302)  //  GlowPump.int    ; The water pump from the Glow                                                
#define SCRIPT_SCIROOM   (303)  //  SciRoom.int     ; The living quarters of the Esteemed scientists.
#define SCRIPT_SENTRYGN  (304)  //  SentryGn.int    ; Sentry Gun trap in the Glow                                                 
#define SCRIPT_GLORDDOR  (305)  //  GloRdDor.int    ; The Red Pass Key doors in the Glow                                          
#define SCRIPT_GLOBLDOR  (306)  //  GloBlDor.int    ; The Blue Pass Key doors in the Glow                                         
#define SCRIPT_GLO3WEP   (307)  //  Glo3Wep.int     ; Glow, Level 3, Weapon Depot door.
#define SCRIPT_GLWBOX    (308)  //  GlwBox.int      ; On Level 4 of the glow, Security Check Lockbox
#define SCRIPT_TYLIER    (309)  //  Tylier.int      ; Tylier, the security computer in the Glow
#define SCRIPT_GLOWCAGE  (310)  //  GlowCage.int    ; Cage for the animals in the Glow                                            
#define SCRIPT_GLOWTABL  (311)  //  GlowTabl.int    ; Table in the Glow                                                           
#define SCRIPT_ZAX       (312)  //  Zax.int         ; Zax the AI computer from the Glow
#define SCRIPT_GLWALIEN  (313)  //  GlwAlien.int    ; Skeleton of a dead alien body                                               
#define SCRIPT_FREEZER   (314)  //  Freezer.int     ; Note in the freezer of the Glow.
#define SCRIPT_FARLI     (315)  //  Farli.int       ; Farli from the Brotherhood of Steel
#define SCRIPT_DARREL    (316)  //  Darrel.int      ; Darrel, Cabbot's replacement in the Brotherhood
#define SCRIPT_PALGUARD  (317)  //  PalGuard.int    ; Paladin Guard in the Brotherhood surface (Caravan Guard)                    
#define SCRIPT_TALUS     (318)  //  Talus.int       ; Talus, Rombus's second in command.
#define SCRIPT_SOPHIA    (319)  //  Sophia.int      ; Sophia, an instructor for the Brotherhood
#define SCRIPT_MICHAEL   (320)  //  Michael.int     ; Distributes weapons to initiates.
#define SCRIPT_GLO4WEAP  (321)  //  Glo4Weap.int    ; Weapon depot on level 4 of the Glow                                         
#define SCRIPT_DEPRECATED_17 (322) //SCRIPT_SCRIBEA   (322)  //  scripts.lst - DONOTUSE wtf??????
#define SCRIPT_DEPRECATED_18 (323) //SCRIPT_SCRIBEB   (323)  //  scripts.lst - DONOTUSE wtf??????
#define SCRIPT_SENTRY    (324)  //  Sentry.int      ; Paladin guard after invasion
#define SCRIPT_PALADINA  (325)  //  PaladinA.int    ; Paladin in the Hall of the Brotherhood.                                     
#define SCRIPT_PALADINB  (326)  //  PaladinB.int    ; Paladin in the Guard room                                                   
#define SCRIPT_PALADINC  (327)  //  PaladinC.int    ; Paladin in the Main Computer Room                                           
#define SCRIPT_GLOBLELV  (328)  //  GloBlElv.int    ; Blue Elevator in the Glow.                                                  
#define SCRIPT_KNIGHTA   (329)  //  KnightA.int     ; Knight in the Computer Room
#define SCRIPT_KNIGHTB   (330)  //  KnightB.int     ; generic Knights in the Brotherhood.
#define SCRIPT_GLOWDESK  (331)  //  GlowDesk.int    ; a jammed desk in the Glow.                                                  
#define SCRIPT_WEAPSYS   (332)  //  WeapSys.int     ; Spatial warning that the weapon system is armed.
#define SCRIPT_ARTIFACT  (333)  //  Artifact.int    ; the artifact the Brotherhood sends you to find.                             
#define SCRIPT_GLOCABN   (334)  //  GloCabn.int     ; locked cabinet in the Glow.
#define SCRIPT_GASTRAP   (335)  //  GasTrap.int     ; Gas Trap in the Glow
#define SCRIPT_LAZRTRAP  (336)  //  LazrTrap.int    ; Laser beam trap in the Glow.                                                
#define SCRIPT_JTRAIDER  (337)  //  JtRaider.int    ; A crazy Raider in Junktown                                                  
#define SCRIPT_SINTHIA   (338)  //  Sinthia.int     ; Sinthia, the Sell Baby in Junktown
#define SCRIPT_MARCELLE  (339)  //  Marcelle.int    ; Owner of the Crash House in Junktown                                        
#define SCRIPT_KILLSAFE  (340)  //  KillSafe.int    ; Killian's personal safe.                                          
#define SCRIPT_JTBOB     (341)  //  JtBob.int       ; Bob from Junktown. Pretty much a dead beat
#define SCRIPT_TRISH     (342)  //  Trish.int       ; Trish, a waitress in Junktown's Skum Pit
#define SCRIPT_V13DOOR   (343)  //  V13Door.int     ; Main door to Vault 13
#define SCRIPT_V13COMP   (344)  //  V13Comp.int     ; Computer to open Vault 13 door.
#define SCRIPT_DISKA     (345)  //  DiskA.int       ; Holodisk w/ Alpha Experiment in the Glow
#define SCRIPT_DISKD     (346)  //  DiskD.int       ; Holodisk w/ Delta Experiment in the Glow
#define SCRIPT_FEVDISK   (347)  //  FEVDisk.int     ; Holodisk w/ FEV Experiment in the Glow
#define SCRIPT_VREEDISK  (348)  //  VreeDisk.int    ; Holodisk w/ Vree's report                                                   
#define SCRIPT_SECDISK   (349)  //  SecDisk.int     ; Holodisk w/ Security Code for the Glow
#define SCRIPT_CODEDISK  (350)  //  CodeDisk.int    ; Holodisk w/ Brotherhood Honor Code                                          
#define SCRIPT_GENGAMBL  (351)  //  GenGambl.int    ; generic gambler in junktown                                                 
#define SCRIPT_PHIL      (352)  //  Phil.int        ; Phil is trying to get into his Junktown Condo
#define SCRIPT_DOGMEAT   (353)  //  Junkdog.int     ; dog who is blocking phil from the Condo
#define SCRIPT_CHEPSLOT  (354)  //  ChepSlot.int    ; cheapy slot machine                                               
#define SCRIPT_GOODSLOT  (355)  //  GoodSlot.int    ; Good paying slot machine                                          
#define SCRIPT_LOWJACK   (356)  //  LowJack.int     ; low stakes Blackjack
#define SCRIPT_HIGHJACK  (357)  //  HighJack.int    ; high stakes Blackjack.                                            
#define SCRIPT_CHOCTECH  (358)  //  ChocTech.int    ; Children of the Cathedral Technician in the Military Base                   
#define SCRIPT_ABEL      (359)  //  Abel.int        ; Abel, lowers the Force Shield E
#define SCRIPT_FIELDA    (360)  //  FieldA.int      ; Force Field A
#define SCRIPT_RADIO     (361)  //  Radio.int       ; Radio for the Military Base
#define SCRIPT_VATSIGN   (362)  //  VatSign.int     ; Sign to the Vats Control Room
#define SCRIPT_VCONDOOR  (363)  //  VConDoor.int    ; Door to get into the Vats Control Room                                      
#define SCRIPT_FORCCOMP  (364)  //  ForcComp.int    ; Force Field Controller Computer in the Vats                                 
#define SCRIPT_MRHANDYA  (365)  //  MrHandyA.int    ; Mr. Handy from the Vats                                                     
#define SCRIPT_MRHANDYB  (366)  //  MrHandyB.int    ; Mr. Handy from the Vats                                                     
#define SCRIPT_FLIP      (367)  //  Flip.int        ; Recent Convert to the Nightkin
#define SCRIPT_ROBCTRL   (368)  //  RobCtrl.int     ; No, this does not control me, It controls the Robots
#define SCRIPT_VSGTEAM9  (369)  //  VSgTeam9.int    ; Vats, Sargeant of Team 9 Nightkin                                           
#define SCRIPT_VATTEAM9  (370)  //  VatTeam9.int    ; Vats, Team 9 member                                                         
#define SCRIPT_VCONCOMP  (371)  //  VConComp.int    ; Vats Control Computer                                                       
#define SCRIPT_PEASANTD  (372)  //  PeasantD.int    ; This is Phil's smart-alec friend                                            
#define SCRIPT_DEMOCOMP  (373)  //  DemoComp.int    ; Computer for the demo                                                       
#define SCRIPT_DEMODOG   (374)  //  DemoDog.int     ; dog for the Demo
#define SCRIPT_DEMOPEAS  (375)  //  DemoPeas.int    ; Phil's smart-alec friend for the Demo                             
#define SCRIPT_DEMOPHIL  (376)  //  DemoPhil.int    ; Phil in the dog scenerio for demo                                 
#define SCRIPT_ZACK      (377)  //  Zack.int        ; some loser from the Gunrunners
#define SCRIPT_THERESA   (378)  //  Theresa.int     ; Faction leader in the Vault trying to get out of the Vault (not from MI)
#define SCRIPT_REBEL     (379)  //  Rebel.int       ; Rebels against the Empire and the Emperor Overseer
#define SCRIPT_DEMODOOR  (380)  //  DemoDoor.int    ; locked freezer in the demo                                                  
#define SCRIPT_SCRIBEC   (381)  //  ScribeC.int     ; a third scribe from the brotherhood
#define SCRIPT_JASON     (382)  //  Jason.int       ; Jason from Adytum.
#define SCRIPT_THUG      (383)  //  Thug.int        ; generic thug from the boneyard
#define SCRIPT_LASHER    (384)  //  Lasher.int      ; Lasher from the Children of the Cathedral
#define SCRIPT_VINNIE    (385)  //  Vinnie.int      ; Leader of the Skuls gang in Junktown
#define SCRIPT_VICTOR    (386)  //  Victor.int      ; Skulz Sociopath
#define SCRIPT_SHARK     (387)  //  Shark.int       ; Skulz ganger in the Scum Pit
#define SCRIPT_SHERRY    (388)  //  Sherry.int      ; Another member of the Skulz
#define SCRIPT_TYCHO     (389)  //  Tycho.int       ; Desert Ranger in Junktown
#define SCRIPT_GENSKULZ  (390)  //  GenSkulz.int    ; generic Skulz member                                                        
#define SCRIPT_SLUMMER   (391)  //  Slummer.int     ; Brainwashed member of the Children
#define SCRIPT_ZARK      (392)  //  Zark.int        ; Cathedral Thug
#define SCRIPT_CALDER    (393)  //  Calder.int      ; Flower child of the Children
#define SCRIPT_CHIDNITE  (394)  //  ChidNite.int    ; Generic Nightkin at the Cathedral                                           
#define SCRIPT_CHIDGAB   (395)  //  ChidGAB.int     ; Children Generic Attitude Boy
#define SCRIPT_GENCHANT  (396)  //  GenChant.int    ; Generic Chanter from the Children                                           
#define SCRIPT_BARRACUS  (397)  //  Barracus.int    ; Leader of the Thug faction in the Children                                  
#define SCRIPT_CHANTER   (398)  //  Chanter.int     ; Generic Chanter 1 from the Children
#define SCRIPT_FRANCIS   (399)  //  Francis.int     ; Sister Francis from the Children
#define SCRIPT_DOCWU     (400)  //  DocWu.int       ; foul-mouthed doc from the Children
#define SCRIPT_RUTGER    (401)  //  Rutger.int      ; second in command of the Far Go Traders
#define SCRIPT_PHRAX     (402)  //  Phrax.int       ; From the Demo, guard for the Crypts.
#define SCRIPT_DEMOGEN   (403)  //  DemoGen.int     ; Generator for the demo
#define SCRIPT_DEMOCRYP  (404)  //  DemoCryp.int    ; generic Crypt ganger member for the demo                                    
#define SCRIPT_DEMOFOOL  (405)  //  DemoFool.int    ; generic Fool ganger memeber for the demo                                    
#define SCRIPT_LENNY     (406)  //  Lenny.int       ; the Bhrama master for the demo
#define SCRIPT_ICEPICK   (407)  //  Icepick.int     ; Leader of the Fools.
#define SCRIPT_SKIZZER   (408)  //  Skizzer.int     ; gate guard for the demo
#define SCRIPT_PEZ       (409)  //  Pez.int         ; generic peasant for the demo
#define SCRIPT_ROCK      (410)  //  Rock.int        ; another guard for the demo
#define SCRIPT_LEX       (411)  //  Lex.int         ; Leader of Scrapheap for the demo
#define SCRIPT_RAYZE     (412)  //  Rayze.int       ; leader of the Crypts for the demo
#define SCRIPT_SKIPPY    (413)  //  Skippy.int      ; Lead wirecutter boy
#define SCRIPT_BAKA      (414)  //  Baka.int        ; Leader of the Fools
#define SCRIPT_SCOUTC    (415)  //  ScoutC.int      ; has the player scouted the Crypts?
#define SCRIPT_SCOUTF    (416)  //  ScoutF.int      ; has the player scouted the Fools?
#define SCRIPT_FOLLMAP   (417)  //  FollMap.int     ; this is the map for the Followers in the Boneyard
#define SCRIPT_SEMICOMP  (418)  //  SemiComp.int    ; Computer that is barely functional in Necrop Vault                          
#define SCRIPT_RADRAT    (419)  //  RadRat.int      ; Rats which make you have a healthly glow
#define SCRIPT_NGARFRDG  (420)  //  NGarFrdg.int    ; Necropolis, Garret's Fridge                                       
#define SCRIPT_WTRLADR   (421)  //  WtrLadr.int     ; Ladder. Leads to ground  [from the sewers above NecVault]
#define SCRIPT_NECVLADR  (422)  //  NecVLadr.int    ; Ladder leading from the Necrop vault to the sewers                          
#define SCRIPT_NECVHOLE  (423)  //  NecVHole.int    ; Manhole leading to the Necrop Vault                                         
#define SCRIPT_WTRHOLE   (424)  //  WtrHole.int     ; Manhole. Leads to Sewers [towards NecVault]
#define SCRIPT_VALTNEC   (425)  //  ValtNec.int     ; Map Script for the Necrop Vault
#define SCRIPT_TOWNMAP   (426)  //  TownMap.int     ; This will bring up the townmap if the player tries using the obj.
#define SCRIPT_MVAIRLOC  (427)  //  MVAirloc.ssl    ;  Master's Vault: Airlock door                                     
#define SCRIPT_MVBSHELF  (428)  //  MVBShelf.ssl    ;  Master's Vault: Bookshelf                                                  
#define SCRIPT_MVSCTSHF  (429)  //  MVSctShf.ssl    ;  Master's Vault: Bookshelf with secret door                                 
#define SCRIPT_V13CAVE   (430)  //  V13Cave.int     ; Map Script for the Vault 13 cave
#define SCRIPT_MVRCRDOR  (431)  //  MVRCrDor.int    ; Reactor Core Door in the Master's Vault                                     
#define SCRIPT_COMMAND   (432)  //  Command.int     ; something for the military base
#define SCRIPT_GENSUPR   (433)  //  GenSupr.int     ; Generic super mutant in the military base
#define SCRIPT_KRUPPER   (434)  //  Krupper.int     ; Krupper from the military base
#define SCRIPT_VANHAG    (435)  //  Vanhag.int      ; Vanhaggen from the military base
#define SCRIPT_VASQUEZ   (436)  //  Vasquez.int     ; Vasquez from junktown
#define SCRIPT_JNKSCOUT  (437)  //  JnkScout.int    ; Scout in Junktown                                                           
#define SCRIPT_PEASANTC  (438)  //  PeasantC.int    ; peasant in Junktown                                                         
#define SCRIPT_GENRAID2  (439)  //  GenRaid2.int    ; another type of generic Raider                                              
#define SCRIPT_JARVIS    (440)  //  Jarvis.int      ; Some guy from Shady Sands
#define SCRIPT_MBSTRONG  (441)  //  MBStrong.int    ; Map Script for the Military Base  [Stronghold]                              
#define SCRIPT_MBVATS    (442)  //  MBVats.int      ; Map Script for the Military Base  [Vats]
#define SCRIPT_MBENT     (443)  //  MBEnt.int       ; Map Script for the Military Base  [Entrance]
#define SCRIPT_CHILDRN1  (444)  //  Childrn1.int    ; Map Script for the lower level of the Children of the Cathedral             
#define SCRIPT_CHILDRN2  (445)  //  Childrn2.int    ; Map Script for the Towers of the Children of the Cathedral                  
#define SCRIPT_MASTER1   (446)  //  Master1.int     ; Map Script for the upper 2 level of the Master's Vault
#define SCRIPT_MASTER2   (447)  //  Master2.int     ; Map Script for the lower 2 level of the Master's Vault
#define SCRIPT_MVCOMP    (448)  //  MVComp.int      ; Nuclear warhead control computer in the Master's Vault
#define SCRIPT_MVNUKE    (449)  //  MVNuke.int      ; The nuclear warhead in the Master's Vault
#define SCRIPT_MVDWN2UP  (450)  //  MVDwn2Up.int    ; go from the lower layers of Master's Vault to the upper                     
#define SCRIPT_MVUP2DWN  (451)  //  MVUp2Dwn.int    ; go from the upper layers to the lower layers of Master's Vault              
#define SCRIPT_CHID2MAS  (452)  //  Chid2Mas.int    ; go from the Children of the Cathedral to the Master's Lair                  
#define SCRIPT_MAS2CHID  (453)  //  Mas2Chid.int    ; go from the Master's Lair to the Children                                   
#define SCRIPT_CHID2TWR  (454)  //  Chid2Twr.int    ; go from the main floor to tower of the Children                             
#define SCRIPT_TOW2CHID  (455)  //  Tow2Chid.int    ; go from the tower to main floor of the Children                             
#define SCRIPT_COCDOOR   (456)  //  COCDoor.int     ; Transport from outside to inside of Children
#define SCRIPT_CAVE2V13  (457)  //  Cave2v13.int    ; Vault 13 caves to Vault 13                                                  
#define SCRIPT_V132CAVE  (458)  //  V132Cave.int    ; Vault 13 to Vault13 caves                                                   
#define SCRIPT_SECDOOR   (459)  //  SecDoor.int     ; door to vault 13 armory
#define SCRIPT_SPOTLITE  (460)  //  SpotLite.int    ; affect the light level of the light scenery                       
#define SCRIPT_WTRTHIEF  (461)  //  WtrThief.int    ; Water Thief from Vault 13                                                   
#define SCRIPT_JENNIFER  (462)  //  Jennifer.int    ; Jennifer from the Brotherhood of Steel                                      
#define SCRIPT_BLAST     (463)  //  Blast.int       ; an explosion for the Buried Vault
#define SCRIPT_UZCHAIR   (464)  //  UzChair.int     ; Use a chair from the Buried Vault
#define SCRIPT_CAVEWALL  (465)  //  CaveWall.int    ; the portion of the cave wall which can be destroyed                         
#define SCRIPT_ELEV0     (466)  //  elev0.int       ; Bos1 (Brotherhood of Steel)
#define SCRIPT_ELEV1     (467)  //  elev1.int       ; Bos2 (entrance)
#define SCRIPT_ELEV2     (468)  //  elev2.int       ; Master1
#define SCRIPT_ELEV3     (469)  //  elev3.int       ; Master2 (lower-level)
#define SCRIPT_ELEV4     (470)  //  elev4.int       ; Military Base 1
#define SCRIPT_ELEV5     (471)  //  elev5.int       ; Military Base 2 (lower-level)
#define SCRIPT_ELEV6     (472)  //  elev6.int       ; Vault13
#define SCRIPT_BARFLY    (473)  //  Barfly.int      ; some loser in the bar in Junktown
#define SCRIPT_BV2VAULT  (474)  //  BV2Vault.int    ; Teleports player from the Shack to the Buried Vault                         
#define SCRIPT_COLATRUK  (475)  //  ColaTruk.int    ; Map Script for special random encounter Cola Truck                          
#define SCRIPT_FSAUSER   (476)  //  FSauser.int     ; Map Script for special random encounter Flying Sauser
#define SCRIPT_GLOWENT   (477)  //  Glowent.int     ; Map Script for Glow Entrance
#define SCRIPT_GLOWMAP1  (478)  //  GlowMap1.int    ; Map Script for Glow (levels 1-3)                                            
#define SCRIPT_GLOWMAP2  (479)  //  GlowMap2.int    ; Map Script for Glow (Levels 4-6)                                            
#define SCRIPT_LAADYTUM  (480)  //  LAAdytum.int    ; Map Script for Adytum                                                       
#define SCRIPT_LABLADES  (481)  //  LABlades.int    ; Map Script for the Blades from the Boneyard                                 
#define SCRIPT_LAGUNRUN  (482)  //  LAGunRun.int    ; Map Script for Gunrunners from the Boneyard                                 
#define SCRIPT_LARIPPER  (483)  //  LARipper.int    ; Map Script for the Rippers from the Boneyard                                
#define SCRIPT_HUBENT    (484)  //  HubEnt.int      ; Map Script for Hub Entrance
#define SCRIPT_HUBDWNTN  (485)  //  HubDwnTn.int    ; Map Script for Downtown Hub                                                 
#define SCRIPT_HUBHEIGT  (486)  //  HubHeigt.int    ; Map Script for The Heights of Hub                                           
#define SCRIPT_HUBOLDTN  (487)  //  HubOldTn.int    ; Map Script for Old Towne Hub                                                
#define SCRIPT_HUBWATER  (488)  //  HubWater.int    ; Map Script for Water Merchants of Hub                                       
#define SCRIPT_DETHCAVE  (489)  //  DethCave.int    ; Map Script for Deathclaw Cave                                               
#define SCRIPT_DRWHOMAP  (490)  //  DrWhoMap.int    ; Map Script for Dr. Who special encounter                                    
#define SCRIPT_LGFTPRNT  (491)  //  LgFtPrnt.int    ; Map Script for Large Foot Print special encounter                           
#define SCRIPT_USEDCAR   (492)  //  UsedCar.int     ; Map Script for Used Car Salesman special encounter
#define SCRIPT_TALKCOWS  (493)  //  TalkCows.int    ; Map Script for Talking Cows special encounter                               
#define SCRIPT_JTUP2DN   (494)  //  JTUp2Dn.int     ; Getting from Garage to Morbid's Lab
#define SCRIPT_JTDN2UP   (495)  //  JTDn2Up.int     ; getting from Morbid's lab to Garage
#define SCRIPT_VIOLA     (496)  //  Viola.int       ; convert from the Followers to the Children
#define SCRIPT_SURF      (497)  //  Surf.int        ; dude, what's with these Children?
#define SCRIPT_CHOCDOOR  (498)  //  ChocDoor.int    ; Door to get out of the Children of the Cathedral                            
#define SCRIPT_DANE      (499)  //  Dane.int        ; psycho person who knows too much
#define SCRIPT_JONATHAN  (500)  //  Jonathan.int    ; someone from the Brotherhood                                                
#define SCRIPT_STUDENT   (501)  //  Student.int     ; student who is learning combat in the brotherhood
#define SCRIPT_CATH2MV   (502)  //  Cath2MV.int     ; spacial to take you from the Cathedral to the Master's Lair
#define SCRIPT_GLO4SUPL  (503)  //  Glo4Supl.int    ; level 4 of the Glow, Supply Room                                            
#define SCRIPT_HALL2MTL  (504)  //  Hall2Mtl.int    ; spatial script to take you from the Hall of the Dead to Motel sewers        
#define SCRIPT_HALL2SHD  (505)  //  Hall2Shd.int    ; spatial to take you from the Hall to the Watershed                          
#define SCRIPT_MOTEL2HL  (506)  //  Motel2Hl.int    ; spatial from the Motel to the Hall                                          
#define SCRIPT_LYLE      (507)  //  Lyle.int        ; man who actually had some water rations stolen
#define SCRIPT_NEAL      (508)  //  Neal.int        ; the bartender for the Skum Pitt.
#define SCRIPT_TRAPFLOR  (509)  //  TrapFlor.int    ; there is a trap on the floor in the glow                                    
#define SCRIPT_KENJI     (510)  //  Kenji.int       ; Gunman hired by Gizmo to kill Killian
#define SCRIPT_GENT2LV1  (511)  //  GEnt2Lv1.int    ; spatial. Glow entrance to Level 1 of the glow                               
#define SCRIPT_GLV12ENT  (512)  //  GLv12Ent.int    ; Use the rocks to go from the Glow Level 1 to Entrance                       
#define SCRIPT_CTOWER1   (513)  //  CTower1.int     ; Catherdral Tower to level 1
#define SCRIPT_CTOWER2   (514)  //  CTower2.int     ; Catherdral Tower to level 2
#define SCRIPT_CTOWER3   (515)  //  CTower3.int     ; Catherdral Tower to level 3
#define SCRIPT_EXITBASE  (516)  //  ExitBase.int    ; Spatial script which will allow you to get out of the Military Base         
#define SCRIPT_SSRADSCO  (517)  //  SSRadSco.int    ; Shady Sands Radscorpions for the Quest                                      
#define SCRIPT_LARS      (518)  //  Lars.int        ; Sergeant of the guards in Junktown.
#define SCRIPT_ELEV6_M1  (519)  //  elev6_m1.int    ; Glow Elevator 1 (really *6*, but vault13 is in place there)                 
#define SCRIPT_ELEV7     (520)  //  elev7.int       ; Glow Elevator 2
#define SCRIPT_ELEV9     (521)  //  elev9.int       ; Necropolis Elevator
#define SCRIPT_ELEV10    (522)  //  elev10.int      ; Extra Milb Elevator
#define SCRIPT_ELEV11    (523)  //  elev11.int      ; Extra Glow Elevator
#define SCRIPT_GENMUTAN  (524)  //  GenMutan.int    ; Generic mutant in the master's vault                                        
#define SCRIPT_GENSARG   (525)  //  GenSarg.int     ; Generic sargent mutant in the master's vault
#define SCRIPT_MBOUT2IN  (526)  //  MBOut2In.int    ; door script to allow the player to get into the Military Base               
#define SCRIPT_TROPHY    (527)  //  Trophy.int      ; Neal's bowling trophy.
#define SCRIPT_SAUL      (528)  //  Saul.int        ; Saul, boxer for Gizmo
#define SCRIPT_GUSTOFER  (529)  //  Gustofer.int    ; Saul's Manager                                                              
#define SCRIPT_ROBOT     (530)  //  Robot.int       ; Robots from the master's lair
#define SCRIPT_VGATEMUT  (531)  //  VGateMut.int    ; Super mutant patrolling gate of the Vats.                                   
#define SCRIPT_VPLOTMUT  (532)  //  VPLotMut.int    ; Super mutant sergeant patrolling parking lot.                               
#define SCRIPT_VFENCEMT  (533)  //  VFenceMt.int    ; Super mutant patrolling fence of the Vats.                                  
#define SCRIPT_DOORCODE  (534)  //  DoorCode.int    ; Script for the tape with the Vats door code.                                
#define SCRIPT_GUARD2    (535)  //  Guard2.int      ; Second Garret in Watershed Map
#define SCRIPT_VDOORMUT  (536)  //  VDoorMut.int    ; Vats Door Mutant                                                            
#define SCRIPT_FIELDB    (537)  //  FieldB.int      ; Force Field B: Stronghold generic
#define SCRIPT_FIELDC    (538)  //  FieldC.int      ; Force Field C: Stronghold east side
#define SCRIPT_FIELDD    (539)  //  FieldD.int      ; Force Field D: Stronghold north side
#define SCRIPT_FIELDE    (540)  //  FieldE.int      ; Force Field E: Stronghold south side
#define SCRIPT_FIELDF    (541)  //  FieldF.int      ; Force Field F: Vats security hall
#define SCRIPT_FIELDG    (542)  //  FieldG.int      ; Force Field G: Vats elevator A
#define SCRIPT_FIELDH    (543)  //  FieldH.int      ; Force Field H: Vats control room
#define SCRIPT_FIELDI    (544)  //  FieldI.int      ; Force Field I: Vats hallway
#define SCRIPT_FORCECON  (545)  //  ForceCon.int    ; Generic force field controller script                             
#define SCRIPT_VTEAM1    (546)  //  VTeam1.int      ; Mutant team num 1 in Vats
#define SCRIPT_VTEAM2    (547)  //  VTeam2.int      ; Mutant team num 2 in Vats
#define SCRIPT_VTEAM3    (548)  //  VTeam3.int      ; Mutant team num 3 in Vats
#define SCRIPT_VTEAM4    (549)  //  VTeam4.int      ; Mutant team num 4 in Vats
#define SCRIPT_VTEAM5    (550)  //  VTeam5.int      ; Mutant team num 5 in Vats
#define SCRIPT_VTEAM6    (551)  //  VTeam6.int      ; Mutant team num 6 in Vats
#define SCRIPT_VTEAM7    (552)  //  VTeam7.int      ; Mutant team num 7 in Vats
#define SCRIPT_VTEAM8    (553)  //  VTeam8.int      ; Mutant team num 8 in Vats
#define SCRIPT_AVERY     (554)  //  avery.int       ; guard for Lorenzo in the Hub
#define SCRIPT_BILL      (555)  //  bill.int        ; guard for Lorenzo in the Hub
#define SCRIPT_BILLY     (556)  //  billy.int       ; boy who works for Dan the Brahmin Man
#define SCRIPT_BOB       (557)  //  bob.int         ; Bob's Iguana Bits owner
#define SCRIPT_BOBSIGN   (558)  //  bobsign.int     ; Sign outside Bob's Iguana Bits
#define SCRIPT_CALLY     (559)  //  cally.int       ; Another bodyguard for Lorenzo
#define SCRIPT_CLEO      (560)  //  cleo.int        ; Guard for Lorenzo in the Hub
#define SCRIPT_CRVNDRVR  (561)  //  crvndrvr.int   ; Caravan driver for the random encounters           
#define SCRIPT_DAN       (562)  //  dan.int         ; Dan 'the Brahmin Man'. sells Brahmin
#define SCRIPT_DANWIFE   (563)  //  danwife.int     ; Dan's Wife
#define SCRIPT_DEADGUY   (564)  //  deadguy.int     ; Someone who was stupid enough to mess w/ Decker
#define SCRIPT_DECKGRD   (565)  //  deckgrd.int     ; One of Decker's Guards
#define SCRIPT_DEMETRE   (566)  //  demetre.int     ; Demetre, head of the Crimson Caravans
#define SCRIPT_FRY       (567)  //  fry.int         ; Deputy Fry of the Hub Police
#define SCRIPT_DEPRECATED_19 (568) //SCRIPT_DOGMEAT   (568)  //  scripts.lst - DONOTUSE wtf??????
#define SCRIPT_ELECDOOR  (569)  //  elecdoor.int    ; Electronic lock on a door in the Hub                                        
#define SCRIPT_ELECTRAP  (570)  //  electrap.int    ; Electronic Trap in the Thieves' Circle                                      
#define SCRIPT_FEMFARMR  (571)  //  femfarmr.int    ; Female Farmer for the Hub                                                   
#define SCRIPT_FGTGARD   (572)  //  fgtgard.int     ; Far Go Trader generic Guard
#define SCRIPT_GENCOP    (573)  //  gencop.int      ; Generic police force in the Hub
#define SCRIPT_GENFGT    (574)  //  genfgt.int      ; Generic Far Go Trader
#define SCRIPT_GENSKAG   (575)  //  genskag.int     ; Generic Skag of the Hub
#define SCRIPT_GUIDO     (576)  //  guido.int       ; Guido, Manager of the Friendly Lending Company
#define SCRIPT_GUNLOCK   (577)  //  gunlock.int     ; Lock on the gun storage
#define SCRIPT_HBODGRD2  (578)  //  hbodgrd2.int    ; Bodyguard in the Hub                                                        
#define SCRIPT_HCHDGRD   (579)  //  hchdgrd.int     ; Hub Children guard
#define SCRIPT_HGENFARM  (580)  //  hgenfarm.int    ; Generic Farmer in the Hub                                                   
#define SCRIPT_HGENGRD   (581)  //  hgengrd.int     ; Generic Guard in the hub
#define SCRIPT_HIGHTOWR  (582)  //  hightowr.int    ; Daren Hightower, leader of the Water Merchants                              
#define SCRIPT_HTWRGRD   (583)  //  htwrgrd.int     ; One of Hightower's Guards
#define SCRIPT_HTWRWIFE  (584)  //  htwrwife.int    ; Hightower's wife                                                            
#define SCRIPT_HUBBER    (585)  //  hubber.int      ; Generic Hubber (Hub Dweller)
#define SCRIPT_HUBCARVN  (586)  //  hubcarvn.int    ; Hub Caravan (generic)                                             
#define SCRIPT_HUBCOP    (587)  //  hubcop.int      ; Generic Hub Cop
#define SCRIPT_HUBFLRCD  (588)  //  hubflrcd.int    ; Flower Child in the Hub                                                     
#define SCRIPT_HUBJAKE   (589)  //  hubjake.int     ; Jacob of the Weapons Shop. Sells big toys
#define SCRIPT_HUBPATNT  (590)  //  hubpatnt.int    ; Patient in the Children's hospital in the Hub                               
#define SCRIPT_HUBSMITY  (591)  //  hubsmity.int    ; Smitty from the Hub                                                         
#define SCRIPT_JASMINE   (592)  //  jasmine.int     ; Jasmine, second in command of the Thieves Guild
#define SCRIPT_JOBPOST   (593)  //  jobpost.int     ; Job Post where all the jobs in the Hub are posted
#define SCRIPT_KANE      (594)  //  kane.int        ; Kane, second in command of the Underground
#define SCRIPT_KERI      (595)  //  keri.int        ; Keri, Demetre's daughter. in the Crimson Caravans
#define SCRIPT_LEON      (596)  //  leon.int        ; Leon, one of Guido's Guards
#define SCRIPT_LORENZO   (597)  //  lorenzo.int     ; Lorenzo, seedy character who occasionally helps the Underground
#define SCRIPT_MSTMERCH  (598)  //  mstmerch.int    ; Master Merchant from the hub                                                
#define SCRIPT_RICHIE    (599)  //  richie.int      ; Richie, guards a safe in the Hub
#define SCRIPT_RUFUS     (600)  //  rufus.int       ; Rufus, cyber hack in the Hub
#define SCRIPT_DEPRECATED_20 (601) //SCRIPT_RUTGER    (601)  //  scripts.lst - DONOTUSE wtf??????
#define SCRIPT_SID       (602)  //  sid.int         ; Sid, annoying little twit who helps Beth
#define SCRIPT_THORNDYK  (603)  //  thorndyk.int    ; Thorndyke, Dr. in the Children in the Hub                                   
#define SCRIPT_TROY      (604)  //  troy.int        ; Troy, a super mutant in the Hub
#define SCRIPT_WMCARVN   (605)  //  wmcarvn.int     ; Water Merchants Caravan
#define SCRIPT_WTRMGRD   (606)  //  wtrMGrd.int     ; Water Merchant Guards
#define SCRIPT_RADIOCOM  (607)  //  RadioCom.int    ; Radio control computer in the Vats.                               
#define SCRIPT_COMPTROL  (608)  //  Comptrol.int    ; Super Mutant comptroller.                                                   
#define SCRIPT_HGENCVAN  (609)  //  HGenCvan.int    ; Generic Hub Caravan                                                         
#define SCRIPT_VATWARN   (610)  //  VatWarn.int     ; Warning of trap corridor in the Vats.
#define SCRIPT_VATALERT  (611)  //  VatAlert.int    ; Spatial to set off the alarm in the Vats.                                   
#define SCRIPT_VPLASMA   (612)  //  VPlasma.int     ; Plasma trap in the Vats.
#define SCRIPT_VBOOM     (613)  //  VBOOM.int       ; Explosive trap in the Vats.
#define SCRIPT_VLASER    (614)  //  VLaser.int      ; Laser trap in the Vats.
#define SCRIPT_VMONOWIR  (615)  //  VMonowir.int    ; Monowire trap in the Vats.                                                  
#define SCRIPT_VLOCKER   (616)  //  VLocker.int     ; Trapped locker in the Vats.
#define SCRIPT_HBETH     (617)  //  HBeth.int       ; Beth who runs the general store in the Hub
#define SCRIPT_HALLGRD   (618)  //  HallGrd.int     ; Generic Gaurd in the Brotherhood Hallways
#define SCRIPT_ROOMGRD   (619)  //  RoomGrd.int     ; Generic Room guard in the Brotherhood
#define SCRIPT_SPAR      (620)  //  Spar.int        ; Sparing match for the brotherhoodd
#define SCRIPT_CHEATER   (621)  //  Cheater.int     ; Cheat for QA
#define SCRIPT_IZO       (622)  //  Izo.int         ; Gizmo's nijamatic bodyguard
#define SCRIPT_KATJA     (623)  //  Katja.int       ; Skulk in Boneyard area
#define SCRIPT_ADY2STOR  (624)  //  Ady2Stor.int    ; Ladder from Adytum to the store.                                            
#define SCRIPT_STOR2ADY  (625)  //  Stor2Ady.int    ; Ladder from store to Adytum.                                                
#define SCRIPT_FOLDN2UP  (626)  //  FolDn2Up.int    ; Followers, from cellar up.                                                  
#define SCRIPT_FOLUP2DN  (627)  //  FolUp2Dn.int    ; Followers, from main level to cellar.                                       
#define SCRIPT_HDTDN2UP  (628)  //  HDtDn2Up.int    ; Hub, Downtown, ladder going down to up                                      
#define SCRIPT_HDTUP2DN  (629)  //  HDtUp2Dn.int    ; Hub, Downtown, ladder going up to down                                      
#define SCRIPT_HDTVAULT  (630)  //  HDtVault.int    ; Vault to FLC in the Hub                                           
#define SCRIPT_MRHANDYC  (631)  //  MrHandyC.int    ; Mr. Handy for cleaning up the Vats.                                         
#define SCRIPT_DEPRECATED_1 	(632) //SCRIPT_STUDENT   (632)  //  scripts.lst - DONOTUSE wtf??????
#define SCRIPT_THOMAS    (633)  //  Thomas.int      ; trainer in the Brotherhood
#define SCRIPT_MODREACT  (634)  //  ModReact.int    ; DO NOT ATTACH TO ANYTHING. JUST IN TO MAKE THINGS COMPILE                   
#define SCRIPT_ADY2FARM  (635)  //  Ady2Farm.int    ; Moves dude from Adytum to hydroponic farms                                  
#define SCRIPT_FARM2ADY  (636)  //  Farm2Ady.int    ; Moves dude from hydroponic farms to Adytum                                  
#define SCRIPT_ADY2CELL  (637)  //  Ady2Cell.int    ; Moves dude from Adytum to cellars                                           
#define SCRIPT_CELL2ADY  (638)  //  Cell2Ady.int    ; Moves dude from cellars to Adytum                                           
#define SCRIPT_GIZGUARD  (639)  //  GizGuard.int    ; Gizmo's casino guards                                                       
#define SCRIPT_RIPPER    (640)  //  Ripper.int      ; generic ripper for the boneyard
#define SCRIPT_MUTDISK   (641)  //  MutDisk.int     ; disk w/ transmissions from mutants in deathclaw cave
#define SCRIPT_DETHCLAW  (642)  //  DethClaw.int    ; deathclaw from the Hub                                                      
#define SCRIPT_DEATHSPR  (643)  //  Deathspr.int    ; Deathclaw spore                                                             
#define SCRIPT_FISHRMAN  (644)  //  FishrMan.int    ; Random fisherman.                                                           
#define SCRIPT_FISHRSON  (645)  //  FishrSon.int    ; Random fisherman's son.                                                     
#define SCRIPT_TARDIS    (646)  //  Tardis.int      ; Script for the special Tardis encounter.
#define SCRIPT_FOOTMAP   (647)  //  FootMap.int     ; Map script for giant footprint.
#define SCRIPT_WHOMAP    (648)  //  WhoMap.int      ; Map script for the Tardis map.
#define SCRIPT_TALKCOW   (649)  //  TalkCow.int     ; Script for the talking Brahmin.
#define SCRIPT_TCOWMAP   (650)  //  TCowMap.int     ; Map script for the talking cows.
#define SCRIPT_MISSBRO   (651)  //  MissBro.int     ; Missing Brotherhood initiate in the Hub
#define SCRIPT_HUBCAPTR  (652)  //  HubCaptr.int    ; Captors of the missing initiate                                             
#define SCRIPT_ANIMFRVR  (653)  //  animfrvr.int    ; This is a script for animating background scenery                 
#define SCRIPT_THFU2D    (654)  //  ThfU2D.int      ; ladder to go from ground to cellar of the Thieves' Circle
#define SCRIPT_THFD2U    (655)  //  ThfD2U.int      ; ladder to go from cellar to ground of the Thieves' Circle
#define SCRIPT_MVNEWS    (656)  //  MVNews.int      ; Newspaper machine in the Master's Vault
#define SCRIPT_DEALER    (657)  //  Dealer.int      ; Insane used car dealer.
#define SCRIPT_DEPRECATED_2 (658) //SCRIPT_USEDCAR   (658)  //  scripts.lst - DONOTUSE wtf??????
#define SCRIPT_BRODEAD   (659)  //  BroDead.int     ; Map script for Brotherhood of Steel, destroyed version.
#define SCRIPT_CHILDEAD  (660)  //  ChilDead.int    ; Map script for Cathedral, destroyed version.                                
#define SCRIPT_MBDEAD    (661)  //  MBDead.int      ; Map script for Military Base, destroyed version.
#define SCRIPT_SARAH     (662)  //  Sarah.int       ; Sarah, girlfriend to the mutant Flip.
#define SCRIPT_AGATHA    (663)  //  Agatha.int      ; The old storyteller of Shady Sands, Agatha.
#define SCRIPT_CHUCK     (664)  //  Chuck.int       ; Gypsy fortune-teller of Adytum.
#define SCRIPT_ALAN      (665)  //  Alan.int        ; Recent enthusiastic Follower convert.
#define SCRIPT_BRENDEN   (666)  //  Brenden.int     ; New Initiate of the BOS.
#define SCRIPT_PATRICK   (667)  //  Patrick.int     ; Strange Celtic wanderer.
#define SCRIPT_ISMARC    (668)  //  Ismarc.int      ; Extremely annoyed musician.
#define SCRIPT_ENEMY     (669)  //  Enemy.int       ; Responses from people who don't want to talk to the dude.
#define SCRIPT_ALEX      (670)  //  Alex.int        ; Night watch Regulator for Adytum.
#define SCRIPT_GIDEON    (671)  //  Gideon.int      ; Leader of the prisoners in the Master's Lair
#define SCRIPT_JEREM     (672)  //  Jerem.int       ; Captive in the masters Lair
#define SCRIPT_AIRGRD    (673)  //  AirGrd.int      ; Gaurd in the Master's Lair
#define SCRIPT_AIRGRD2   (674)  //  AirGrd2.int     ; Another type of Guard in the Master's Lair
#define SCRIPT_BOSLORRI  (675)  //  BOSLori.int     ; Brotherhood of Steel Doctor
#define SCRIPT_MOORE     (676)  //  Moore.int       ; person in the master's lair
#define SCRIPT_LUCY      (677)  //  Lucy.int        ; person in the master's lair
#define SCRIPT_WIGGUP    (678)  //  Wiggup.int      ; mutant in the master's lair
#define SCRIPT_MADSCI    (679)  //  MadSci.int      ; mad scientist in the master's lair
#define SCRIPT_VINCENT   (680)  //  Vincent.int     ; mutant in the master's lair
#define SCRIPT_FARMPART  (681)  //  FARMPART.int    ; farm parts for adytum                                                       
#define SCRIPT_MLPRISON  (682)  //  MLPrison.int    ; Master's lair Prisoner                                                      
#define SCRIPT_GENPRIS   (683)  //  GenPris.int     ; Generic prisoner in the Master's Lair
#define SCRIPT_PRISCON   (684)  //  PrisCon.int     ; Prison Control force Fields
#define SCRIPT_THOMAS2   (685)  //  thomas2.int     ; Thomas from the Brotherhood (on another map)
#define SCRIPT_MONSTER   (686)  //  Monster.int     ; Monsters in the Master's Vault.
#define SCRIPT_PSYCON    (687)  //  PsyCon.int      ; Psychic control comupter.
#define SCRIPT_RAE       (688)  //  Rae.int         ; Confused mutant in the Master's Vault
#define SCRIPT_BHDOOR    (689)  //  BHDoor.int      ; main door to the brotherhood of steel
#define SCRIPT_BOSASIS   (690)  //  BOSAsIs.int     ; Brotherhood Dr. Assistant
#define SCRIPT_RD1INIT   (691)  //  RD1Init.int     ; Roommate in the Brotherhood
#define SCRIPT_GENINIT   (692)  //  GenInit.int     ; Generic Initiate in the Brotherhood
#define SCRIPT_COYOTE    (693)  //  Coyote.int      ; random dog in the wild
#define SCRIPT_SMONE     (694)  //  Smone.int       ; Mutants from the Master's Lair
#define SCRIPT_SMTWO     (695)  //  SmTwo.int       ; Mutants from the Master's Lair
#define SCRIPT_JUSTIN    (696)  //  Justin.int      ; Sherrif of Hub
#define SCRIPT_FALCON1   (697)  //  Falcon1.int     ; Bartender at the Falcon
#define SCRIPT_MERCH1    (698)  //  Merch1.int      ; Merchant from the Hub
#define SCRIPT_LANCE     (699)  //  Lance.int       ; Shady Sands guard on long patrol.
#define SCRIPT_LONERAID  (700)  //  LoneRaid.int    ; Lone Raider trying to get to camp.                                          
#define SCRIPT_DEPRECATED_3 (701) //SCRIPT_RNDMERCH  (701)  //  scripts.lst - DONOTUSE wtf??????                                                    
#define SCRIPT_PALSCOUT  (702)  //  PalScout.int    ; Random Paladin scouts.                                                      
#define SCRIPT_TRENT     (703)  //  Trent.int       ; Survivor of a Deathclaw attack.
#define SCRIPT_HDEALER   (704)  //  HDealer.int     ; dealer in the falcon for craps
#define SCRIPT_HSLOTS    (705)  //  HSlots.int      ; slot machines in the Hub
#define SCRIPT_HRNDBAR   (706)  //  HRndBar.int     ; Random dialog in the bar of the HUb
#define SCRIPT_HGENGAMB  (707)  //  HGenGamb.int    ; generic gamblers in the hub                                                 
#define SCRIPT_HHOOKER   (708)  //  HHooker.int     ; Hooker in the Falcon
#define SCRIPT_HJOHN     (709)  //  HJohn.int       ; Hooker's customer in the Falcon
#define SCRIPT_HGENDEAL  (710)  //  HGenDeal.int    ; Generic Dealer in the Falcon                                                
#define SCRIPT_SMPRAY    (711)  //  smpray.int      ; praying mutants in masters vault
#define SCRIPT_CPRAY     (712)  //  cpray.int       ; praying children in masters vault
#define SCRIPT_PEASVICT  (713)  //  PeasVict.int    ; Peasant victim for random encounters.                                       
#define SCRIPT_HROULET   (714)  //  HRoulet.int     ; roulette dealer from the hub
#define SCRIPT_JUNKPEAS  (715)  //  JunkPeas.int    ; generic peasant in Junktown                                                 
#define SCRIPT_TEACHER   (716)  //  Teacher.int     ; Teacher in the Brotherhood.
#define SCRIPT_GENSCRIB  (717)  //  Genscrib.int    ; Scribe in Brotherhood                                                       
#define SCRIPT_GENKNIGH  (718)  //  Genknigh.int    ; Knight in Brotherhood                                                       
#define SCRIPT_GENPALAD  (719)  //  Genpalad.int    ; Paladin in Brotherhood                                                      
#define SCRIPT_LAKIDS    (720)  //	LAKIDS.int 		; Children swarming the motorcycle in Blades territory
#define SCRIPT_RIPUP2DN  (721)  //  RipUp2Dn.int    ; Stairs up from the Rippers' cellar.                                         
#define SCRIPT_RIPDN2UP  (722)  //  RipDn2Up.int    ; Stairs down from the Rippers' hideout.                                      
#define SCRIPT_RD1SCRB1  (723)  //  Rd1Scrb1.int    ; Random Scribe from the Brotherhood                                          
#define SCRIPT_RD1KNIG   (724)  //  Rd1Knig.int     ; Random Dialog for the Knights in the Brotherhood
#define SCRIPT_TERM      (725)  //  term.int        ; terminal in the Brotherhood
#define SCRIPT_TERM1     (726)  //  term1.int       ; terminal in the Brotherhood
#define SCRIPT_TERM2     (727)  //  term2.int       ; terminal in the Brotherhood
#define SCRIPT_TERM3     (728)  //  term3.int       ; terminal in the Brotherhood
#define SCRIPT_TERM4     (729)  //  term4.int       ; terminal in the Brotherhood
#define SCRIPT_TERM5     (730)  //  term5.int       ; terminal in the Brotherhood
#define SCRIPT_TERM6     (731)  //  term6.int       ; terminal in the Brotherhood
#define SCRIPT_TERM7     (732)  //  term7.int       ; terminal in the Brotherhood
#define SCRIPT_TERM8     (733)  //  term8.int       ; terminal in the Brotherhood
#define SCRIPT_LOCKER    (734)  //  Locker.int      ; generic locked locker
#define SCRIPT_MANTIS    (735)  //  Mantis.int      ; preying Mantis
#define SCRIPT_WORKROOM  (736)  //  WorkRoom.int    ; exploding work table in the Brotherhood                           
#define SCRIPT_MADBROT   (737)  //  MadBrot.int     ; mad scientist in the brotherhood
#define SCRIPT_WOMEN     (738)  //  Women.int       ; women in the raiders camp which can be killed
#define SCRIPT_SINK      (739)  //  Sink.int        ; You can use this sink to dirty your hands
#define SCRIPT_REVULSE   (740)  //  Revulse.int     ; Corridor of revulsion
#define SCRIPT_FIELDGEN  (741)  //  fieldgen.int    ; field generator in the military base                                        
#define SCRIPT_ELEVCON   (742)  //  ElevCon.int     ; Elevator Control for the Force Fields to the Nuke Bomb
#define SCRIPT_GENZOMBI  (743)  //  genzombi.int	; Generic "Zombie Guard" in worldmap encounters
#define SCRIPT_BROHIST   (744)  //  BroHist.int     ; Holodisk for the Brotherhood history
#define SCRIPT_SOPDISK   (745)  //  SopDisk.int     ; Sophia's History disk of the Brotherhood
#define SCRIPT_MAXDISK   (746)  //  MaxDisk.int     ; Maxson's Version of the history of the Brotherhood
#define SCRIPT_LOOT      (747)  //  Loot.int        ; Fridge in the Raiders camp
#define SCRIPT_HUBSAFE   (748)  //  HubSafe.int     ; safe for Lorenzo's stuff
#define SCRIPT_GENRAIDA  (749)  //  GenRaidA.int    ; Generic raider for random encounter                                         
#define SCRIPT_GENRAIDB  (750)  //  GenRaidB.int    ; Generic raider for random encounter                                         
#define SCRIPT_GENRAIDC  (751)  //  GenRaidC.int    ; Generic raider for random encounter                                         
#define SCRIPT_GENMERCA  (752)  //  GenMercA.int    ; Generic Merchant for random encounter                                       
#define SCRIPT_GENMERCB  (753)  //  GenMercB.int    ; Generic merchant for random encounter                                       
#define SCRIPT_GENMERCC  (754)  //  GenMercC.int    ; Generic merchant for random encounter                                       
#define SCRIPT_GENGRDA   (755)  //  GenGrdA.int     ; Generic guard for random encounter
#define SCRIPT_GENGRDB   (756)  //  GenGrdB.int     ; Generic guard for random encounter
#define SCRIPT_GENGRDC   (757)  //  GenGrdC.int     ; Generic guard for random encounter
#define SCRIPT_GENPALA   (758)  //  GenPalA.int     ; Generic paladin for random encounter
#define SCRIPT_GENPALB   (759)  //  GenPalB.int     ; Generic paladin for random encounter
#define SCRIPT_GENPALC   (760)  //  GenPalC.int     ; Generic paladin for random encounter
#define SCRIPT_CRVNTEAM  (761)  //  CrvnTeam.int    ; Caravan team for the random encounters                                      
#define SCRIPT_CRVNMSTR  (762)  //  CrvnMstr.int    ; Animals who attack the caravan                                              
#define SCRIPT_CRVNENMY  (763)  //  CrvnEnmy.int    ; People who attack the caravans                                              
#define SCRIPT_KILLSTOR  (764)  //  KillStor.int    ; stuff for Killian's store                                         
#define SCRIPT_CARENCTR  (765)  //  CarEnctr.int    ; Caravan Random Encounters                                                   
#define SCRIPT_GENCHAT   (766)  //  GenChat.int     ; generic messagage file
#define SCRIPT_CCVAN     (767)  //  CCVan.int       ; Crimson Caravan Dealer (gives jobs) (temp)
#define SCRIPT_FGTVAN    (768)  //  FGTVan.int      ; Far Go Traders Dealer (Gives jobs) (temp)
#define SCRIPT_WMVAN     (769)  //  WMVan.int       ; Water Merchants Dealer (gives jobs) (temp)
#define SCRIPT_LARYKNIG  (770)  //  LaryKnig.int    ; Knight Larry in the Brotherhood                                             
#define SCRIPT_VRESCRIB  (771)  //  VreScrib.int    ; Vree's scribe in the brotherhood                                            
#define SCRIPT_VREGRD    (772)  //  vregrd.int      ; Vree's guard
#define SCRIPT_MAXGRD    (773)  //  MaxGrd.int      ; Maxson's guard
#define SCRIPT_JEREM2    (774)  //  Jerem2.int      ; Jeremia from the Master's Lair
#define SCRIPT_WOODDOOR  (775)  //  WoodDoor.int    ; wooden door script to blow up doors                                         
#define SCRIPT_METLDOOR  (776)  //  MetlDoor.int    ; metal door script to blow up doors                                          
#define SCRIPT_HUBENCTR  (777)  //  HubEnctr.int    ; Caravan Random encounters return to the hub                                 
#define SCRIPT_HGENVAN2  (778)  //  HGenVan2.int    ; caravan people who are leaving the hub (generic)                            
#define SCRIPT_FGTRTNVN  (779)  //  FGTRtnVn.int    ; Far Go Traders Return to the Hub                                            
#define SCRIPT_CCRTNVN   (780)  //  CCRtnVn.int     ; Crimson Caravans Return to the Hub
#define SCRIPT_WMRTNVN   (781)  //  WMRtnVn.int     ; Water Merchants Return to the Hub
#define SCRIPT_ALLNONE   (782)  //  AllNOne.int     ; Merchant for the All in One Store
#define SCRIPT_ARMORY    (783)  //  Armory.int      ; merchant for the Armory Store
#define SCRIPT_ADYSTORE  (784)  //  AdyStore.int    ; store in Adytum                                                   
#define SCRIPT_EXITLITE  (785)  //  ExitLite.int    ; lights for scenery objects                                                  
#define SCRIPT_ROPE      (786)  //  Rope.int        ; for message file
#define SCRIPT_ARMSDEAL  (787)  //  ArmsDeal.int    ; Jake the Arms Dealer in the Hub                                             
#define SCRIPT_GDOOR     (788)  //  GDoor.int       ; Ghoul Door in Necropolis
#define SCRIPT_JUNKJAIL  (789)  //  JunkJail.int    ; spatial script for the junktown jail cell                                   
#define SCRIPT_TREAD     (790)  //  Tread.int       ; ghoul near vault door in Necrop
#define SCRIPT_DIRTNAP   (791)  //  Dirtnap.int     ; ghouls near water chip in Necrop
#define SCRIPT_VALTGLO   (792)  //  Valtglo.int     ; generic ghouls in Necrop Vault
#define SCRIPT_VALTCOMP  (793)  //  ValtComp.int    ; generic computer for Vault 13                                               
#define SCRIPT_REDFARM   (794)  //  RedFarm.int     ; red peasant farmer in the Hub
#define SCRIPT_GRNFARM   (795)  //  GrnFarm.int     ; green farmer in the Hub
#define SCRIPT_HCARAVN1  (796)  //  HCaravn1.int    ; Generic Caravan Merchant Gaurd                                    
#define SCRIPT_HCARAVN2  (797)  //  HCaravn2.int    ; Generic Caravan Merchant Gaurd                                    
#define SCRIPT_HCARAVN3  (798)  //  HCaravn3.int    ; Generic Caravan Merchant Gaurd                                    
#define SCRIPT_HCARAVN4  (799)  //  HCaravn4.int    ; Generic Caravan Merchant Gaurd                                    
#define SCRIPT_CREDDOOR  (800)  //  CRedDoor.int    ; Locked door needing the red COC Badge                             
#define SCRIPT_CBLKDOOR  (801)  //  CBlkDoor.int    ; Locked door needing the Black COC Badge                           
#define SCRIPT_MAT       (802)  //  Mat.int         ; Caravan driver at the Hub Entrance
#define SCRIPT_LUKE      (803)  //  Luke.int        ; Caravan driver at the Hub Entrance
#define SCRIPT_JOHN      (804)  //  John.int        ; Security guard at the Entrance of the Hub
#define SCRIPT_JDOOR     (805)  //  JDoor.int       ; Jeremiah's secret door in the master's lair
#define SCRIPT_LIBRARY   (806)  //  Library.int     ; Library in the Vault 13
#define SCRIPT_CRASHRM   (807)  //  CrashRm.int     ; Spatial for room #1 in the Junktown crash house
#define SCRIPT_JAKEDOOR  (808)  //  JakeDoor.int    ; Door to Jake's shop in the Hub                                    
#define SCRIPT_JAKEDESK  (809)  //  JakeDesk.int    ; Desk in Jake's Shop in the Hub                                              
#define SCRIPT_BOOKCASE  (810)  //  Bookcase.int    ; bookcase in master's lair                                                   
#define SCRIPT_MLOPS     (811)  //  MLOps.int       ; Master's lair Ops Control center
#define SCRIPT_VISCIOUS  (812)  //  Viscious.int    ; Viscious from the Master's Lair                                             
#define SCRIPT_VAULTBOX  (813)  //  VaultBox.int    ; Water storage box in V 13                                         
#define SCRIPT_MSTRCOMP  (814)  //  MstrComp.int    ; Computer in the Master's Lair                                               
#define SCRIPT_CHILDOOR  (815)  //  Childoor.int    ; Secure door in the Children in the Hub                                      
#define SCRIPT_HWMHOST   (816)  //  HWMHost.int     ; just a guy who tells you things in the area
#define SCRIPT_CARVLEAD  (817)  //  CarvLead.int    ; Generic destination person who will give you $$                   
#define SCRIPT_GENBCASE  (818)  //  GenBCase.int    ; generic Bookcase                                                            
#define SCRIPT_BROINVAD  (819)  //  BroInvad.int    ; Brotherhood Paladins who help invade the Cathedral                
#define SCRIPT_FOLINVAD  (820)  //  FolInvad.int    ; Followers Invaders who help invade the Cathedral                  
#define SCRIPT_MIKE      (821)  //  Mike.int        ; Mike, the Old town guide
#define SCRIPT_VANCE     (822)  //  Vance.int       ; Vance, the drug dealer in the Hub
#define SCRIPT_JUNKIE    (823)  //  Junkie.int      ; Drug Junkie in the Hub
#define SCRIPT_NDEBRIS   (824)  //  NDebris.int     ; North Debris
#define SCRIPT_SDEBRIS   (825)  //  SDebris.int     ; South Debris
#define SCRIPT_EDEBRIS   (826)  //  EDebris.int     ; East Debris
#define SCRIPT_WDEBRIS   (827)  //  WDebris.int     ; West Debris
#define SCRIPT_GPWRTERM  (828)  //  GPwrTerm.int    ; Power Terminals in the Glow                                                 
#define SCRIPT_FOOTPRNT  (829)  //  FootPrnt.int    ; Spatial of Ghoul footprints leading to the sewer                            
#define SCRIPT_WMGUARD   (830)  //  WMGuard.int     ; Water Merchant Gaurd
#define SCRIPT_GSENROB   (831)  //  GSenRob.int     ; sentry droid for the Glow
#define SCRIPT_GLOYLDOR  (832)  //  GloYlDor.int    ; Yellow security door in the Glow                                            
#define SCRIPT_WMGROUP   (833)  //  WMGroup.int     ; Water Merchants--generic ppl around the merchants
#define SCRIPT_CCGUARD   (834)  //  CCGuard.int     ; Crimson Caravan guards from the Hub
#define SCRIPT_BOXGUARD  (835)  //  BoxGuard.int    ; guards around the boxing arena in Junktown                                  
#define SCRIPT_GUNCACHE  (836)  //  GunCache.int    ; Cache of Gunrunners weapons                                       
#define SCRIPT_SDOOR     (837)  //  SDoor.int       ; Door that can't be openned
#define SCRIPT_POWERMUT  (838)  //  PowerMut.int    ; Super mutant guarding power armour                                          
#define SCRIPT_BULLBORD  (839)  //  bullbord.int    ; Bulletin board outside of the hub                                           
#define SCRIPT_GUNCASE   (840)  //  GunCase.int     ; Suitcase that the gunrunners give you
#define SCRIPT_GUNTHER   (841)  //  Gunther.int     ; Just some guy in the Hub
#define SCRIPT_SLAPPY    (842)  //  Slappy.int      ; Crazed bum in the Hub
#define SCRIPT_CATHSHOP  (843)  //  CathShop.int    ; Person in the Cathedral who sells things                          
#define SCRIPT_CATHCASE  (844)  //  CathCase.int    ; Bookcase in the cathedral to hold items                           
#define SCRIPT_KYLE      (845)  //  Kyle.int        ; Kyle from the Brotherhood
#define SCRIPT_LEMMY     (846)  //  Lemmy.int       ; guy that Gus designed to point you around
#define SCRIPT_BETHGRD   (847)  //  Bethgrd.int     ; guys outside the weapons shop
#define SCRIPT_DCMUTANT  (848)  //  DCMutant.int    ; Dying Mutant in the deathclaw cave                                          
#define SCRIPT_FGTCARVN  (849)  //  FGTCarvn.int    ; Far Go Trader caravan peoples                                               
#define SCRIPT_MUTAMBSH  (850)  //  MutAmbsh.int    ; Mutant Ambush for the Random Encounters                                     
#define SCRIPT_DOCLOCKR  (851)  //  DocLockr.int    ; Doc Morbid's locker                                                         
#define SCRIPT_CRASHBOX  (852)  //  CrashBox.int    ; Crash house fridge                                                          
#define SCRIPT_SKUMDOOR  (853)  //  SkumDoor.int    ; Skum Pit door                                                     
#define SCRIPT_SUPAMBSH  (854)  //  SupAmbsh.int    ; Super Mutant Ambush for random encounters                                   
#define SCRIPT_MOATCHEK  (855)  //  MoatChek.int    ; dex check for the moat                                                      
#define SCRIPT_MYSTSTRN  (856)  //  MystStrn.int    ; Mysterious Stranger Script                                                  
#define SCRIPT_SUPGRD    (857)  //  SupGrd.int      ; Supply guards for the Brotherhood
#define SCRIPT_SUPDOOR   (858)  //  SupDoor.int     ; Supply door in the Brotherhood
#define SCRIPT_VWEPLOKR  (859)  //  VWepLokr.int    ; Vats Weapon Locker                                                
#define SCRIPT_BROLOCK   (860)  //  BroLock.int     ; Brotherhood footlockers
#define SCRIPT_VALTDISK  (861)  //  ValtDisk.int    ; Holodisk that gives all vault locations                                     
#define SCRIPT_STAPLE    (862)  //  Staple.int      ; Mrs. Stapleton in the Hub (librarian)
#define SCRIPT_KLAXON    (863)  //  Klaxon.int      ; Alarm in the Vats
#define SCRIPT_TOGGLE    (864)  //  Toggle.int      ; Toggle switch for the Vats
#define SCRIPT_PAUL      (865)  //  Paul.int        ; Paul from the weapons division in the Brotherhood
#define SCRIPT_HTWRLEON  (866)  //  HtwrLeon.int    ; Leon the guard at the Hightower place                                       
#define SCRIPT_VPLSTRAP  (867)  //  VPlsTrap.int    ; Vats Plasma Trrap                                                           
#define SCRIPT_VEXDTRAP  (868)  //  VExdTrap.int    ; Vats Explosion trap                                                         
#define SCRIPT_VELCTRAP  (869)  //  VElcTrap.int    ; Vats Electric Trap                                                          
#define SCRIPT_HTWRGRGE  (870)  //  HtwrGrge.int    ; George the guard for the hightowers                                         
#define SCRIPT_HTWRRICK  (871)  //  HtwrRick.int    ; Rick, yet another of hightwoers guards
#define SCRIPT_HTWRBOX   (872)  //  HtwrBox.int     ; strongbox w/ a necklace in it
#define SCRIPT_KILDOOR1  (873)  //  KilDoor1.int    ; Killian Door 1                                                    
#define SCRIPT_KILDOOR2  (874)  //  KilDoor2.int    ; Killian Door 2                                                    
#define SCRIPT_EMITER1A  (875)  //  Emiter1a.int    ; Force Field Emitter 1a for MBStrg12                               
#define SCRIPT_FIELD1A   (876)  //  Field1a.int     ; Force Field for Emitter 1a
#define SCRIPT_MORBCOOL  (877)  //  MorbCool.int    ; Morbid's cooler                                                             
#define SCRIPT_HTWRDOOR  (878)  //  HtwrDoor.int    ; Front door to the Hightower's place                                         
#define SCRIPT_FIELD2A   (879)  //  Field2a.int     ; Force Field for Emitter 2a
#define SCRIPT_EMITER2A  (880)  //  Emiter2a.int    ; Force Field Emitter 2a for MBStrg12                               
#define SCRIPT_FIELD3A   (881)  //  Field3a.int     ; Force Field for Emitter 3a
#define SCRIPT_EMITER3A  (882)  //  Emiter3a.int    ; Force Field Emitter 3a for MBStrg12                               
#define SCRIPT_FIELD4A   (883)  //  Field4a.int     ; Force Field for Emitter 4a
#define SCRIPT_EMITER4A  (884)  //  Emiter4a.int    ; Force Field Emitter 4a for MBStrg12                               
#define SCRIPT_FIELD5A   (885)  //  Field5a.int     ; Force Field for Emitter 5a
#define SCRIPT_EMITER5A  (886)  //  Emiter5a.int    ; Force Field Emitter 5a for MBStrg12                               
#define SCRIPT_FIELD6A   (887)  //  Field6a.int     ; Force Field for Emitter 6a
#define SCRIPT_EMITER6A  (888)  //  Emiter6a.int    ; Force Field Emitter 6a for MBStrg12                               
#define SCRIPT_FLOATER   (889)  //  Floater.int     ; Generic Floaters for Random Encounters
#define SCRIPT_LENORE    (890)  //  Lenore.int      ; Denizen of Junktown
#define SCRIPT_BITSBOB   (891)  //  BitsBob.int     ; Iguna Bob from the Hub
#define SCRIPT_KANEDOOR  (892)  //  KaneDoor.int    ; Door for Kane in the Hub                                                    
#define SCRIPT_FIELD1B   (893)  //  Field1b.int     ; Force Field for Emitter 2a
#define SCRIPT_EMITER1B  (894)  //  Emiter1b.int    ; Force Field Emitter 2a for MBStrg12                               
#define SCRIPT_FIELD2B   (895)  //  Field2b.int     ; Force Field for Emitter 3a
#define SCRIPT_EMITER2B  (896)  //  Emiter2b.int    ; Force Field Emitter 3a for MBStrg12                               
#define SCRIPT_PAINFELD  (897)  //  PainFeld.int    ; Pain Field in the Vats                                                      
#define SCRIPT_FIELD1C   (898)  //  Field1c.int     ; Force Field for Emitter 2a
#define SCRIPT_EMITER1C  (899)  //  Emiter1c.int    ; Force Field Emitter 2a for MBStrg12                               
#define SCRIPT_FIELD2C   (900)  //  Field2c.int     ; Force Field for Emitter 3a
#define SCRIPT_EMITER2C  (901)  //  Emiter2c.int    ; Force Field Emitter 3a for MBStrg12                               
#define SCRIPT_FIELD1D   (902)  //  Field1d.int     ; Force Field for Emitter 2a
#define SCRIPT_EMITER1D  (903)  //  Emiter1d.int    ; Force Field Emitter 2a for MBStrg12                               
#define SCRIPT_VBROKELV  (904)  //  VBrokElv.int    ; Broken elevator in the Vats                                                 
#define SCRIPT_STUFF     (905)  //  Stuff.int       ; the Ghouls stuff in Necropolis
#define SCRIPT_ARMDOOR   (906)  //  ArmDoor.int     ; armory door in the Vats
#define SCRIPT_REGGUARD  (907)  //  RegGuard.int    ; Regulator guard for the boneyard                                            
#define SCRIPT_HOTGHOUL  (908)  //  HotGhoul.int    ; ghoul in the Hotel of Doom                                                  
#define SCRIPT_LTGUARD   (909)  //  LtGuard.int     ; guards near the Lt.
#define SCRIPT_MORPCOMP  (910)  //  MorpComp.int    ; computer in morpheus' room                                                  
#define SCRIPT_SETDOOR   (911)  //  SetDoor.int     ; trapped and locked door
#define SCRIPT_INVADER   (912)  //  Invader.int     ; Invader for Necropolis
#define SCRIPT_PGUARD    (913)  //  PGuard.int      ; Personal guard to Zimmerman
#define SCRIPT_FRYSTUB   (914)  //  FryStub.int     ; a short dep Fry. in Decker's hideout
#define SCRIPT_NUKEGRD   (915)  //  Nukegrd.int     ; guard for nuke in masters vault
#define SCRIPT_HORD      (916)  //  Hord.int        ; hord of troops called by master
#define SCRIPT_DUGAN     (917)  //  Dugan.int       ; The Weez
#define SCRIPT_MACRAE    (918)  //  MacRae.int      ; Helper Blade to find Leader of Blades
#define SCRIPT_CCGUARD1  (919)  //  CCGuard1.int    ; Crimson Caravan Guard 1                                                     
#define SCRIPT_CCGUARD2  (920)  //  CCGuard2.int    ; Crimson Caravan Guard 2                                                     
#define SCRIPT_MOMCLAW   (921)  //  MomClaw.int     ; Mother Deathclaw
#define SCRIPT_ROAMCLAW  (922)  //  RoamClaw.int    ; Roaming Deathclaw                                                           
#define SCRIPT_BYMIKE    (923)  //  BYMike.int      ; Mike from the Boneyard (Blade)
#define SCRIPT_BYCHRIS   (924)  //  BYChris.int     ; Blade Chris from the Boneyard
#define SCRIPT_BYGREG    (925)  //  BYGreg.int      ; Blade Greg from the Boneyard
#define SCRIPT_INBLADE   (926)  //  InBlade.int     ; Invasion Blades
#define SCRIPT_EGGCLAW   (927)  //  EggClaw.int     ; Deathclaw egg
#define SCRIPT_RADSCOR2  (928)  //  Radscor2.int    ; Doesn't start out hostile.                                                  
#define SCRIPT_VANCEBOX  (929)  //  VanceBox.int    ; Box where vance keeps his trading items                           
#define SCRIPT_BETHBOX   (930)  //  BethBox.int     ; Box where Beth keeps his trading items
#define SCRIPT_EMITERH   (931)  //  EmiterH.int     ; force ield emiter for Vat Control Room
#define SCRIPT_RHOMDOOR  (932)  //  RhomDoor.int    ; Door to rhombus's area                                            
#define SCRIPT_RHOMLOCK  (933)  //  RhomLock.int    ; Locker in rhombus' room                                           
#define SCRIPT_WANRAT2   (934)  //  WanRat2.int     ; Non-hostile Rats
#define SCRIPT_IRWIN     (935)  //  Irwin.int       ; farmer who lost his farm
#define SCRIPT_ARMOR     (936)  //  Armor.int       ; Armor on Kyle's worktable
#define SCRIPT_MITCHBOX  (937)  //  MitchBox.int    ; Mitch's box of inven                                                        
#define SCRIPT_FARMRAID  (938)  //  FarmRaid.int    ; Raider who is attacking a farm in the Hub                                   
#define SCRIPT_MATHIA    (939)  //  Mathia.int      ; Maxson's Assistant
#define SCRIPT_JTILE     (940)  //  JTile.int       ; Spatial script to trigger door in the Master's Vault
#define SCRIPT_STAMPEDE  (941)  //  Stampede.int    ; stampede random encounter                                                   
#define SCRIPT_HIGHELD   (942)  //  HighEld.int     ; Elders for the Brotherhood
#define SCRIPT_MOLERAT2  (943)  //  MoleRat2.int    ; Another stupid molerat                                                      
#define SCRIPT_BROELD    (944)  //  BroEld.int      ; Brotherhood elder (generic)
#define SCRIPT_GRIFFBED  (945)  //  GRIFFBED.int 	; Fuel Cell Controller stash                                     
#define SCRIPT_ICECHEST  (946)  //  IceChest.int    ; box where Garl can place player's stuff                           
#define SCRIPT_LTCODES   (947)  //  LtCodes.int     ; Codes the Lt is holding
#define SCRIPT_PRISFELD  (948)  //  PrisFeld.int    ; prisoner force field in the master's lair                         
#define SCRIPT_PSYFIELD  (949)  //  PsyField.int    ; psycker's force field in the master's lair                        
#define SCRIPT_KENNY     (950)  //  Kenny.int       ; They killed Kenny!
#define SCRIPT_SUPLYGRD  (951)  //  SuplyGrd.int    ; supply guards for 1st level brotherhood                                     
#define SCRIPT_HUBMIS1   (952)  //  HubMis1.int     ; map script for HubMis1.map
#define SCRIPT_GRIFFITH  (953)  //  Necropolis ghoul related to motorcycle
#define SCRIPT_GENLOCK   (954)  //  GenLock.int     ; generic foot locker which is locked
#define SCRIPT_REGDISK   (955)  //  RegDisk.int     ; Rugulator holodisk
#define SCRIPT_HUBPRIS   (956)  //  HubPris.int     ; Prisoner in the Hub
#define SCRIPT_LAFOLLWR  (957)  //  LAFollwr.int    ; map script for the followers                                                
#define SCRIPT_RAIDDOOR  (958)  //  RaidDoor.int    ; the cell door for tandi in the raiders                                      
#define SCRIPT_GENEMIT   (959)  //  GenEmit.int     ; generic damaged force field emitter
#define SCRIPT_TEST      (960)  //  Test.int        ; testing scripts

//FalloutFIXT
#define SCRIPT_CHITEM    (961)
#define SCRIPT_CARCUST   (962)
#define SCRIPT_JBOXER    (963)
#define SCRIPT_STAPBOX   (964)
#define SCRIPT_INVADED   (965)
#define SCRIPT_CARCOW    (966)
#define SCRIPT_FKE_DUDE  (967)
#define SCRIPT_ALLDOGS   (968)
#define SCRIPT_BOBSTAND  (969)
#define SCRIPT_HHOOKER2  (970)
#define SCRIPT_MASSACRE  (971)
#define SCRIPT_REDFIELD  (972)

// Stuff from scripts.lst
#define SCRIPT_GRNMTARM  (973)
//#define SCRIPT_MYSTSTRN  (974)

//Lexx
#define SCRIPT_CHEATBOX  (975)
#define SCRIPT_NIF2HINT  (976)  // niF2Hint.int    ; New Reno Fallout 2 Hintbook
#define SCRIPT_RNDENC 	 (977)	// Random encounter map selector script
#define SCRIPT_MOTRCYCL  (978)	// Drivable vehicle 
#define SCRIPT_MOTRTRNK  (979)  // Motorcycle trunk
#define SCRIPT_ZIBRAPOO  (980)  // ziBraPoo.int    ; Generic BRAHMIN SHIT!!! YES YES YES

#endif // SCRIPTS_H
