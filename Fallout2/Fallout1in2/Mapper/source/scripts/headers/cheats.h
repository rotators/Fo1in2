#pragma once

/*******************************************************************************
                    This file is included in OBJ_DUDE.ssl!
*******************************************************************************/

procedure Cheater00;
procedure Cheater00a;
procedure Cheater00b;
procedure Cheater00c;
procedure Cheater00d;
procedure Cheater00d1;
procedure Cheater00e;
procedure Cheater01;
procedure Cheater02;
procedure Cheater03;
procedure Cheater04;
procedure Cheater05;
procedure Cheater05b;
procedure Cheater05c;
procedure Cheater06;
procedure Cheater06a;
procedure Cheater06b;
procedure Cheater06c;
procedure Cheater06d;
procedure Cheater06e;
procedure Cheater07;
procedure Cheater08;
procedure Cheater09;
procedure Cheater10;
procedure Cheater11;
procedure Cheater12;
procedure Cheater13;
procedure Cheater14;
procedure Cheater15;
procedure Cheater18;
procedure Cheater19;
procedure Cheater19a;
procedure Cheater19b;
procedure Cheater19c;
procedure Cheater19d;
procedure Cheater19e;
procedure Cheater19f;
procedure Cheater19g;
procedure Cheater19h;
procedure CheaterEnd;

procedure ChangeTheClock;//used for the two procs below this one
procedure RollBack;// subtract amount from game_time (time-travel to the past!!)
procedure SpringForward;// add to game_time (back to the future!!)
procedure Teleport;// to move around to different maps

procedure TARDIS_1;
procedure TARDIS_2;
procedure TARDIS_3;
procedure TARDIS_4;
procedure TARDIS_5;
procedure TARDIS_6;
procedure TARDIS_7;
procedure TARDIS_8;
procedure TARDIS_9;
procedure Nec1;
procedure Nec2;
procedure Nec3;
procedure Nec4;
procedure v13_1;
procedure v13_2;
procedure v15_1;
procedure v15_2;
procedure Junk1;
procedure Junk2;
procedure Junk3;
procedure Bro1;
procedure Bro2;
procedure Bro3;
procedure Bro4;
procedure City;
procedure Child1;
procedure Child2;
procedure Master1;
procedure Master2;
procedure Coast1;
procedure Coast2;
procedure Mountain1;
procedure Mountain2;
procedure Hub1;
procedure Hub2;
procedure Hub3;
procedure Hub4;
procedure Hub5;
procedure Hub6;
procedure Hub7;
procedure Deathcave;
procedure Ady1;
procedure Ady2;
procedure Ady3;
procedure Ady4;
procedure Ady5;
procedure Ady6;
procedure Raid1;
procedure Raid2;
procedure Shad1;
procedure Shad2;
procedure Shad3;
procedure MB1;
procedure MB2;
procedure MB3;
procedure MB4;
procedure Glow1;
procedure Glow2;
procedure Glow3;
procedure Des1;
procedure Des2;
procedure Des3;
procedure DesCrv1;
procedure DesCrv2;
procedure DesCrv3;
procedure DesCrv4;
procedure MntCrv1;
procedure MntCrv2;
procedure MntCrv3;
procedure MntCrv4;
procedure ColaTruk;
procedure Ufo;
procedure BigFoot;
procedure PoliceBox;
procedure TalkCow;
procedure UsedCar;
procedure Scrapheap;

procedure CheaterTimers;
procedure CheaterTimersV13Invasion;
procedure CheaterTimersV13Water;
procedure CheaterTimersUp;
procedure CheaterTimersDown;

variable TimeFlag;

#define timerUPandDown \
   giq_option(1, SCRIPT_CHEATER, 1020, CheaterTimersUp, NEUTRAL_REACTION);    \
   giq_option(1, SCRIPT_CHEATER, 1030, CheaterTimersDown, NEUTRAL_REACTION);  \
   NOption(g_bye, CheaterEnd, 001)

procedure CheaterEnd begin
end

procedure Cheater19a
begin
   critter_heal(dude_obj, -1);
end

procedure Cheater19b
begin
   critter_heal(dude_obj, -5);
end

procedure Cheater19c
begin
   critter_heal(dude_obj, -10);
end

procedure Cheater19d
begin
   critter_heal(dude_obj, -20);
end

procedure Cheater19e
begin
   critter_heal(dude_obj, -30);
end

procedure Cheater19f
begin
   critter_heal(dude_obj, -40);
end

procedure Cheater19g
begin
   critter_heal(dude_obj, -50);
end

procedure Cheater19h
begin
   critter_heal(dude_obj, -999);
end

procedure Cheater06a
begin
   critter_injure(dude_obj, 4);//    DAM_CRIP_LEG_LEFT      4
   gsay_message(SCRIPT_CHEATER, 221, 50);
end

procedure Cheater06b
begin
   critter_injure(dude_obj, 8);//    DAM_CRIP_LEG_RIGHT     8
   gsay_message(SCRIPT_CHEATER, 221, 50);
end

procedure Cheater06c
begin
   critter_injure(dude_obj, 16);//    DAM_CRIP_ARM_LEFT     16
   gsay_message(SCRIPT_CHEATER, 221, 50);
end

procedure Cheater06d
begin
   critter_injure(dude_obj, 32);//    DAM_CRIP_ARM_RIGHT    32
   gsay_message(SCRIPT_CHEATER, 221, 50);
end

procedure Cheater06e
begin
   critter_injure(dude_obj, 64);//    DAM_BLIND             64
   gsay_message(SCRIPT_CHEATER, 221, 50);
end

procedure Cheater00c begin
   set_global_var( GVAR_MASTER_BLOWN, 1 );
   call CheaterEnd;
end

procedure Cheater00d begin
   set_global_var( GVAR_VATS_BLOWN, 1 );
   call CheaterEnd;
end

procedure Cheater00d1 begin
   set_global_var( GVAR_VATS_BLOWN, 1 );
   set_global_var( GVAR_QUEST_VAULT13_3_KILL_VATS, 2 );
   set_global_var( GVAR_VATS_COUNTDOWN, (game_time / 10) + 300 );
end

procedure Cheater00e begin
   set_waterchip_returned;

   if (global_var(GVAR_QUEST_VAULT13_1_REBELS) > 0) then
      set_global_var(GVAR_QUEST_VAULT13_1_REBELS, 3);
   if (global_var(GVAR_QUEST_VAULT13_5_WTR_THIEF) > 0) then
      set_global_var(GVAR_QUEST_VAULT13_5_WTR_THIEF, 3);

   call CheaterEnd;
end

procedure Cheater00b begin
   Reply("Master or Vats?");
   NOption("Water Chip brought back", Cheater00e, 001);
   NOption("Master", Cheater00C, 001);
   NOption("Vats", Cheater00d, 001);
   NOption("Start Vats destruction timer!", Cheater00d1, 001);
   NOption(g_bye, CheaterEnd, 004);
end

procedure Slideshow begin
   set_waterchip_returned;
   set_global_var( GVAR_MASTER_BLOWN, 1 );
   set_global_var( GVAR_VATS_BLOWN, 1 );

   load_map(MAP_V13ENT, -1);
end

procedure Cheater01
begin
   give_exp_points(500);
// gsay_message(SCRIPT_CHEATER, 240, 50);
   call Cheater00;
end

procedure Cheater02
begin
   give_exp_points(1000);
// gsay_message(SCRIPT_CHEATER, 240, 50);
   call Cheater00;
end

procedure Cheater03
begin
   give_exp_points(5000);
// gsay_message(SCRIPT_CHEATER, 240, 50);
   call Cheater00;
end

procedure Cheater04
begin
   give_exp_points(10000);
// gsay_message(SCRIPT_CHEATER, 240, 50);
   call Cheater00;
end

procedure Cheater05
begin
   give_exp_points(50000);
// gsay_message(SCRIPT_CHEATER, 240, 50);
   call Cheater00;
end

procedure Cheater05b
begin
   give_exp_points(210000);
// gsay_message(SCRIPT_CHEATER, 240, 50);
// call Cheater00;
end

procedure Cheater05c
begin
// variable LVar0;
// pc_stat(1) := 10;
   give_exp_points(-5000);
// gsay_message(SCRIPT_CHEATER, 240, 50);
   call Cheater00;
end

procedure Cheater07
begin
   display_msg(message_str(SCRIPT_CHEATER, 213) + dude_poison_stat + " ");
   poison(dude_obj, 100);
   display_msg(message_str(SCRIPT_CHEATER, 214)  + dude_poison_stat + " ");
// gsay_message(SCRIPT_CHEATER, 215, 50);
   call Cheater06;
end

procedure Cheater08
begin
   display_msg(message_str(SCRIPT_CHEATER, 213) + dude_rads + " ");
   radiation_inc(dude_obj, 50);
   display_msg(message_str(SCRIPT_CHEATER, 214)  + dude_rads + " ");
// gsay_message(SCRIPT_CHEATER, 216, 50);
   call Cheater06;
end

procedure Cheater09
begin
   variable LVar0;
   if TimeFlag then begin
      LVar0 := (0 - 10);
   end
   else begin
      LVar0 := (0 + 10);
   end
   game_time_advance(LVar0);
end

procedure Cheater10
begin
   variable LVar0;
   if TimeFlag then begin
      LVar0 := (0 - (10 * 60));
   end
   else begin
      LVar0 := (0 + (10 * 60));
   end
   game_time_advance(LVar0);
end

procedure Cheater11
begin
   variable LVar0;
   if TimeFlag then begin
      LVar0 := (0 - (10 * 60 * 60));
   end
   else begin
      LVar0 := (0 + (10 * 60 * 60));
   end
   game_time_advance(LVar0);
end

procedure Cheater12
begin
   variable LVar0;
   if TimeFlag then begin
      LVar0 := (0 - (10 * 60 * 60 * 24));
   end
   else begin
      LVar0 := (0 + (10 * 60 * 60 * 24));
   end
   game_time_advance(LVar0);
end

procedure Cheater13
begin
   variable LVar0;
   if TimeFlag then begin
      LVar0 := (0 - (10 * 60 * 60 * 24 * 7));
   end
   else begin
      LVar0 := (0 + (10 * 60 * 60 * 24 * 7));
   end
   game_time_advance(LVar0);
end

procedure Cheater14
begin
   variable LVar0;
   if TimeFlag then begin
      LVar0 := (0 - (10 * 60 * 60 * 24 * 30));
   end
   else begin
      LVar0 := (0 + (10 * 60 * 60 * 24 * 30));
   end
   game_time_advance(LVar0);
end

procedure Cheater15
begin
   variable LVar0;
   if TimeFlag then begin
      LVar0 := (0 - (10 * 60 * 60 * 24 * 30 * 6));
   end
   else begin
      LVar0 := (0 + (10 * 60 * 60 * 24 * 30 * 6));
   end
   game_time_advance(LVar0);
end

procedure Cheater18
begin
   variable LVar0;
   if TimeFlag then begin
      LVar0 := ((0 - (10 * 60 * 60 * 24 * 365) * 13));
   end
   else begin
      LVar0 := ((0 + (10 * 60 * 60 * 24 * 365) * 13));
   end
   game_time_advance(LVar0);
end

procedure Cheater00// GIVE EXPERIENCE
begin
   gsay_reply(SCRIPT_CHEATER, 241);
   giq_option( 1, SCRIPT_CHEATER, 232, Cheater01, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 233, Cheater02, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 234, Cheater03, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 235, Cheater04, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 236, Cheater05, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 237, Cheater05b, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 238, Cheater05c, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 239, Cheater00a, NEUTRAL_REACTION );
end


procedure Cheater06
begin
   gsay_reply(SCRIPT_CHEATER, 222);
   giq_option( 1, SCRIPT_CHEATER, 223, Cheater06a, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 224, Cheater06b, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 225, Cheater06c, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 226, Cheater06d, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 227, Cheater06e, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 203, Cheater07, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 204, Cheater08, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 228, Cheater00a, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 242, Cheater19, NEUTRAL_REACTION );
end

procedure Cheater19
begin
   gsay_reply(SCRIPT_CHEATER, 243);
   giq_option( 1, SCRIPT_CHEATER, 244, Cheater19a, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 245, Cheater19b, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 246, Cheater19c, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 247, Cheater19d, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 248, Cheater19e, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 249, Cheater19f, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 250, Cheater19g, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 228, Cheater00a, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 251, Cheater19h, NEUTRAL_REACTION );
end

procedure Teleport begin
   gsay_reply(SCRIPT_CHEATER, 262);
   giq_option( 1, SCRIPT_CHEATER, 269, TARDIS_1, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 270, TARDIS_2, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 271, TARDIS_3, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 272, TARDIS_4, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 273, TARDIS_5, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 274, TARDIS_6, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 275, TARDIS_7, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 276, TARDIS_8, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 277, TARDIS_9, NEUTRAL_REACTION );
end

procedure TARDIS_1 begin
   gsay_reply(SCRIPT_CHEATER, 262);
   giq_option( 1, SCRIPT_CHEATER, 303, Nec1, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 309, Nec2, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 304, Nec3, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 305, Nec4, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 306, v13_1, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 335, v13_2, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 308, v15_1, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 307, v15_2, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 278, Cheater00a, NEUTRAL_REACTION );
end

procedure Nec1
begin
   load_map(MAP_HALLDED, 2);
end

procedure Nec2
begin
   load_map(MAP_VAULTNEC, -1);
end

procedure Nec3
begin
   load_map(MAP_HOTEL, -1);
end

procedure Nec4
begin
   load_map(MAP_WATRSHD, -1);
end

procedure v13_1
begin
   load_map(MAP_VAULT13, -1);
end

procedure v13_2
begin
   load_map(MAP_V13ENT, -1);
end

procedure v15_1
begin
   load_map(MAP_VAULTBUR, -1);
end

procedure v15_2
begin
   load_map(MAP_VAULTENT, -1);
end

procedure TARDIS_2
begin
   gsay_reply(SCRIPT_CHEATER, 262);
   giq_option( 1, SCRIPT_CHEATER, 310, Junk1, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 311, Junk2, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 312, Junk3, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 313, Bro1, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 314, Bro2, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 315, Bro3, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 355, Bro4, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 319, City, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 278, Cheater00a, NEUTRAL_REACTION );
end

procedure Junk1
begin
   load_map(MAP_JUNKENT, -1);
end

procedure Junk2
begin
   load_map(MAP_JUNKCSNO, -1);
end

procedure Junk3
begin
   load_map(MAP_JUNKKILL, -1);
end

procedure Bro1
begin
   load_map(MAP_BROHDENT, -1);
end

procedure Bro2
begin
   load_map(MAP_BROHD12, -1);
end

procedure Bro3
begin
   load_map(MAP_BROHD34, -1);
end

procedure Bro4
begin
   load_map(MAP_BRODEAD, -1);
end

procedure City
begin
   load_map(MAP_CITY1, -1);
end

procedure TARDIS_3
begin
   gsay_reply(SCRIPT_CHEATER, 262);
   giq_option( 1, SCRIPT_CHEATER, 317, Child1, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 318, Child2, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 333, Master1, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 334, Master2, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 320, Coast1, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 321, Coast2, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 349, Mountain1, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 350, Mountain2, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 278, Cheater00a, NEUTRAL_REACTION );
end

procedure Child1
begin
   load_map(MAP_CHILDRN1, -1);
end

procedure Child2
begin
   load_map(MAP_CHILDRN2, -1);
end

procedure Master1
begin
   load_map(MAP_MSTRLR12, -1);
end

procedure Master2
begin
   load_map(MAP_MSTRLR34, -1);
end

procedure Coast1
begin
   load_map(MAP_COAST1, -1);
end

procedure Coast2
begin
   load_map(MAP_COAST2, -1);
end

procedure Mountain1
begin
   load_map(MAP_MOUNTN1, -1);
end

procedure Mountain2
begin
   load_map(MAP_MOUNTN2, -1);
end

procedure TARDIS_4
begin
   gsay_reply(SCRIPT_CHEATER, 262);
   giq_option( 1, SCRIPT_CHEATER, 336, Hub1, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 338, Hub2, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 339, Hub3, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 340, Hub4, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 341, Hub5, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 365, Hub6, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 366, Hub7, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 337, Deathcave, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 278, Cheater00a, NEUTRAL_REACTION );
end

procedure Hub1
begin
   load_map(MAP_HUBENT, -1);
end

procedure Hub2
begin
   load_map(MAP_HUBDWNTN, -1);
end

procedure Hub3
begin
   load_map(MAP_HUBHEIGT, -1);
end

procedure Hub4
begin
   load_map(MAP_HUBOLDTN, -1);
end

procedure Hub5
begin
   load_map(MAP_HUBWATER, -1);
end

procedure Hub6
begin
   load_map(MAP_HUBMIS0, -1);
end

procedure Hub7
begin
   load_map(MAP_HUBMIS1, -1);
end

procedure Deathcave
begin
   load_map(MAP_DETHCLAW, -1);
end

procedure TARDIS_5
begin
   gsay_reply(SCRIPT_CHEATER, 262);
   giq_option( 1, SCRIPT_CHEATER, 328, Ady1, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 329, Ady2, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 344, Ady3, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 345, Ady4, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 346, Ady5, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 347, Ady6, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 324, Raid1, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 360, Raid2, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 278, Cheater00a, NEUTRAL_REACTION );
end

procedure Ady1
begin
   load_map(MAP_LAADYTUM, -1);
end

procedure Ady2
begin
   load_map(MAP_LAFOLLWR, -1);
end

procedure Ady3
begin
   load_map(MAP_LABLADES, -1);
end

procedure Ady4
begin
   load_map(MAP_LARIPPER, -1);
end

procedure Ady5
begin
   load_map(MAP_LAGUNRUN, -1);
end

procedure Ady6
begin
   load_map(MAP_CHILDEAD, -1);
end

procedure Raid1
begin
   load_map(MAP_RAIDERS, -1);
end

procedure Raid2
begin
   load_map(MAP_VIPERS, -1);
end

procedure TARDIS_6
begin
   gsay_reply(SCRIPT_CHEATER, 262);
   giq_option( 1, SCRIPT_CHEATER, 325, Shad1, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 326, Shad2, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 316, Shad3, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 330, MB1, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 331, MB2, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 332, MB3, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 348, MB4, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 239, Cheater00a, NEUTRAL_REACTION );
end

procedure Shad1
begin
   load_map(MAP_SHADYE, -1);
end

procedure Shad2
begin
   load_map(MAP_SHADYW, -1);
end

procedure Shad3
begin
   load_map(MAP_CAVES, -1);
end

procedure MB1 begin
   load_map(MAP_MBENT, 0);
end

procedure MB2
begin
   load_map(MAP_MBSTRG12, -1);
end

procedure MB3
begin
   load_map(MAP_MBVATS12, 3);
end

procedure MB4
begin
   load_map(MAP_MBDEAD, -1);
end

procedure TARDIS_7
begin
   gsay_reply(SCRIPT_CHEATER, 262);
   giq_option( 1, SCRIPT_CHEATER, 327, Glow1, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 342, Glow2, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 343, Glow3, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 300, Des1, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 301, Des2, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 302, Des3, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 279, Cheater00a, NEUTRAL_REACTION );
end

procedure Glow1
begin
   load_map(MAP_GLOWENT, -1);
end

procedure Glow2
begin
   load_map(MAP_GLOW1, -1);
end

procedure Glow3
begin
   load_map(MAP_GLOW2, -1);
end

procedure Des1
begin
   load_map(MAP_DESERT0, -1);
end

procedure Des2
begin
   load_map(MAP_DESERT2, -1);
end

procedure Des3
begin
   load_map(MAP_DESERT3, -1);
end

procedure TARDIS_8
begin
   gsay_reply(SCRIPT_CHEATER, 262);
   giq_option( 1, SCRIPT_CHEATER, 356, DesCrv1, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 357, DesCrv2, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 361, DesCrv3, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 363, DesCrv4, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 358, MntCrv1, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 359, MntCrv2, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 362, MntCrv3, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 363, MntCrv4, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 278, Cheater00a, NEUTRAL_REACTION );
end

procedure DesCrv1
begin
   load_map(MAP_DESCRVN1, -1);
end

procedure DesCrv2
begin
   load_map(MAP_DESCRVN2, -1);
end

procedure DesCrv3
begin
   load_map(MAP_MNTCRVN3, -1);
end

procedure DesCrv4
begin
   load_map(MAP_MNTCRVN4, -1);
end

procedure MntCrv1
begin
   load_map(MAP_MNTCRVN1, -1);
end

procedure MntCrv2
begin
   load_map(MAP_MNTCRVN2, -1);
end

procedure MntCrv3
begin
   load_map(MAP_DESCRVN4, -1);
end

procedure MntCrv4
begin
   load_map(MAP_MNTCRVN4, -1);
end

procedure TARDIS_9 begin
   gsay_reply(SCRIPT_CHEATER, 262);
   giq_option( 1, SCRIPT_CHEATER, 322, ColaTruk, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 323, Ufo, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 351, BigFoot, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 352, PoliceBox, NEUTRAL_REACTION );
   //qiq_option(1, 621, 353, TalkCow, 50);
   giq_option( 1, SCRIPT_CHEATER, 354, UsedCar, NEUTRAL_REACTION );
   NOption("Scrapheap", Scrapheap, 1);
   giq_option( 1, SCRIPT_CHEATER, 279, Cheater00a, NEUTRAL_REACTION );
end

procedure ColaTruk
begin
   load_map(MAP_COLATRUK, -1);
end

procedure Ufo
begin
   load_map(MAP_FSAUSER, -1);
end

procedure BigFoot
begin
   load_map(MAP_FOOT, -1);
end

procedure PoliceBox
begin
   load_map(MAP_TARDIS, -1);
end

procedure TalkCow
begin
   //load_map(MAP_TALKCOW, -1);
end

procedure UsedCar begin
   load_map(MAP_USEDCAR, -1);
end

procedure Scrapheap begin
   load_map(MAP_SCRAPHEAP, -1);
end

procedure ChangeTheClock
begin
   gsay_reply(SCRIPT_CHEATER, 266);
   giq_option( 1, SCRIPT_CHEATER, 1000, CheaterTimers, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 101, RollBack, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 111, SpringForward, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 125, Cheater00a, NEUTRAL_REACTION );
end

procedure RollBack
begin
   TimeFlag := 1;
   gsay_reply(SCRIPT_CHEATER, 102);
   giq_option( 1, SCRIPT_CHEATER, 103, Cheater09, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 104, Cheater10, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 105, Cheater11, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 106, Cheater12, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 107, Cheater13, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 108, Cheater14, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 109, Cheater15, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 309, Cheater18, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 110, Cheater00a, NEUTRAL_REACTION );
end

procedure SpringForward
begin
   TimeFlag := 0;
   gsay_reply(SCRIPT_CHEATER, 112);
   giq_option( 1, SCRIPT_CHEATER, 113, Cheater09, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 114, Cheater10, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 115, Cheater11, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 116, Cheater12, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 117, Cheater13, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 118, Cheater14, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 119, Cheater15, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 319, Cheater18, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 120, Cheater00a, NEUTRAL_REACTION );
end

procedure Cheater00a//  MAIN MENU    MAIN MENU     MAIN MENU      MAIN MENU
begin
// set_global_var(VATS_BLOWN, 1);
//
   gsay_reply(SCRIPT_CHEATER, 200);
   giq_option( 1, SCRIPT_CHEATER, 201, Cheater00, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 202, Cheater06, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 263, ChangeTheClock, NEUTRAL_REACTION );
   //giq_option( 1, SCRIPT_CHEATER, 121, IDKFA, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 280, Slideshow, NEUTRAL_REACTION );
   giq_option( 1, SCRIPT_CHEATER, 252, Teleport, NEUTRAL_REACTION );
   NOption("Kill Master or Vats", Cheater00b, 001);
   NOption(g_bye, CheaterEnd, 001);
end

procedure CheaterTimers begin
   gsay_reply(SCRIPT_CHEATER, 1000);
   giq_option(1, SCRIPT_CHEATER, 1011, CheaterTimersV13Water, NEUTRAL_REACTION);
   giq_option(1, SCRIPT_CHEATER, 1010, CheaterTimersV13Invasion, NEUTRAL_REACTION);
   NOption(g_bye, CheaterEnd, 001);
end

procedure CheaterTimersV13Invasion begin
   TimeFlag := "V13Invasion";
   gsay_reply(SCRIPT_CHEATER, 1010);
   timerUPandDown;
end

procedure CheaterTimersV13Water begin
   TimeFlag := "V13Water";
   gsay_reply(SCRIPT_CHEATER, 1011);
   timerUPandDown;
end

procedure CheaterTimersUp begin
   gsay_reply(SCRIPT_CHEATER, 1020);

   if (TimeFlag == "V13Invasion") then begin
      inc_v13_days_left(100);
   end
   else if (TimeFlag == "V13Water") then begin
      inc_water_days(100);
   end

   timerUPandDown;
end

procedure CheaterTimersDown begin
   gsay_reply(SCRIPT_CHEATER, 1030);

   if (TimeFlag == "V13Invasion") then begin
      dec_v13_days_left(100);
   end
   else if (TimeFlag == "V13Water") then begin
      dec_water_days(100);
   end

   timerUPandDown;
end
