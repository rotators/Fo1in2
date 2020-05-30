/*

    This file contains generic information for the cave random encounters

*/

#ifndef CVGENENC_H
#define CVGENENC_H

variable
   i, count, chance,

   encounter_pid1 := 0,
   encounter_pid2 := 0,
   encounter_pid3 := 0,
   encounter_pid4 := 0,
   encounter_pid5 := 0,
   encounter_pid6 := 0,

   encounter_sid1 := 0,
   encounter_sid2 := 0,
   encounter_sid3 := 0,
   encounter_sid4 := 0,
   encounter_sid5 := 0,
   encounter_sid6 := 0,

   active_encounter_pids := 0,
   total_encounter_mobs := 0, //Per area in map
   baseElevation := 0,

   special_spawn_critters := 1,
   special_spawn_container := 0,
   special_spawn_container_weapons := 0,

   choose_enc_pid := 0,
   choose_enc_sid := 0,

   Area_List, Exit_List := -1, Chest_List, SceneryPos_List := -1, Items_List,
   Choose_Scenery,
   Scenery_Chance,
   Active_Scenery_List := 1,
   Scenery1_Range, Scenery1_List, Scenery1_Script := -1,
   Scenery2_Range, Scenery2_List, Scenery2_Script := -1,
   Scenery3_Range, Scenery3_List, Scenery3_Script := -1;

procedure Choose_Encounter begin
   variable
      val := Random(1, 6),
      rnd_chest := random(1, 100),
      rnd_critter;

   if (rnd_chest < 50 and (stat_success(dude_obj, STAT_lu, 0))) then
      special_spawn_container := 1;
   else
      special_spawn_container := 0;

   // DEBUG
   //val := 0;

   // Geckos
   if (val == 1) then begin
      active_encounter_pids := 1;
      rnd_critter := random(1, 100);
      if (rnd_critter < 65 - dude_level) then begin
         if (random(0, 4) == 1) or (global_var(GVAR_WORLDMAP_TABLE) == 3) then begin // 3 == South Table
            encounter_pid1 := PID_GOLDEN_GECKO;
            encounter_sid1 := SCRIPT_ECGECKO;
            total_encounter_mobs := Random(2, 4);
         end
         else begin
            encounter_pid1 := PID_GECKO;
            encounter_sid1 := SCRIPT_ECGECKO;
            total_encounter_mobs := Random(1, 4);
         end
      end else if (rnd_critter < 80 - dude_level) then begin
         encounter_pid1 := PID_GOLDEN_GECKO;
         encounter_sid1 := SCRIPT_ECGECKO;
         total_encounter_mobs := Random(2, 3);
      end else begin
         encounter_pid1 := PID_FIRE_GECKO;
         encounter_sid1 := SCRIPT_ECGECKO;
         total_encounter_mobs := Random(2, 4);
      end
   end

   // Radscorpions
   else if (val == 2) then begin
      active_encounter_pids := 1;
      rnd_critter := random(1, 100);
      if (rnd_critter < 50) then begin
         encounter_pid1 := PID_SMALL_RADSCORPION;
         encounter_sid1 := SCRIPT_RADSCORP;
         total_encounter_mobs := Random(3, 5);
      end else if (rnd_critter < 75) then begin
         active_encounter_pids := 2;
         encounter_pid1 := PID_SMALL_RADSCORPION;
         encounter_sid1 := SCRIPT_RADSCORP;
         encounter_pid2 := PID_NASTY_RADSCORPION;
         encounter_sid2 := SCRIPT_RADSCORP;
         total_encounter_mobs := Random(3, 5);
      end else begin
         active_encounter_pids := 2;
         encounter_pid1 := PID_RADSCORPION;
         encounter_sid1 := SCRIPT_RADSCORP;
         encounter_pid2 := PID_NASTY_RADSCORPION;
         encounter_sid2 := SCRIPT_RADSCORP;
         total_encounter_mobs := Random(3, 5);
      end
   end

   // Rats
   else if (val == 3) then begin
      active_encounter_pids := 1;
      rnd_critter := random(1, 100);

      if (rnd_critter < 50 - dude_level) then begin
         encounter_pid1 := PID_RAT_CAVE;
         encounter_sid1 := SCRIPT_WANRATS;
         total_encounter_mobs := Random(3, 5);
      end else if (rnd_critter < 75 - dude_level) then begin
         active_encounter_pids := 1;
         encounter_pid1 := PID_PIGRAT;
         encounter_sid1 := SCRIPT_WANRATS;
         total_encounter_mobs := Random(2, 4);
      end else begin
         active_encounter_pids := 2;
         encounter_pid1 := PID_GREATER_MOLE_RAT;
         encounter_sid1 := SCRIPT_WANRATS;
         encounter_pid2 := PID_PIGRAT;
         encounter_sid2 := SCRIPT_WANRATS;
         total_encounter_mobs := 4;
      end
   end

   // Ants
   else if (val == 4) then begin
      active_encounter_pids := 1;
      encounter_pid1 := PID_ANT;
      encounter_sid1 := SCRIPT_WANRATS;
      total_encounter_mobs := Random(3, 5);
   end

   // Mantis
   else if (val == 5) then begin
      if ((dude_level <= 10) or (random(1, 100) <= 75)) then begin
         if (random(1, 100) <= 40) then begin
            active_encounter_pids := 2;
            encounter_pid1 := PID_MANTIS;
            encounter_sid1 := SCRIPT_MANTIS;
            encounter_pid2 := PID_SPORE_PLANT;
            encounter_sid2 := SCRIPT_ECPLANT;
            total_encounter_mobs := Random(3, 6);
         end
         else begin
            active_encounter_pids := 1;
            encounter_pid1 := PID_MANTIS;
            encounter_sid1 := SCRIPT_MANTIS;
            total_encounter_mobs := Random(1, 3);
         end
      end
      else begin
         active_encounter_pids := 2;
         encounter_pid1 := PID_DEATHCLAW;
         encounter_sid1 := SCRIPT_WANRATS;
         encounter_pid2 := PID_DEATHCLAW_SMALL;
         encounter_sid2 := SCRIPT_WANRATS;
         total_encounter_mobs := Random(1, 3);
      end
   end

   // Wild Dogs
   else if (val == 6) then begin
      active_encounter_pids := 1;
      encounter_pid1 := PID_WILD_DOG;
      encounter_sid1 := SCRIPT_ECWLDDOG;
      total_encounter_mobs := Random(3, 4);
   end
end

procedure Choose_Pid begin
    variable val;

    val := Random(1, active_encounter_pids);
    if (val == 1) then begin
        choose_enc_pid := encounter_pid1;
        choose_enc_sid := encounter_sid1;
    end else if (val == 2) then begin
        choose_enc_pid := encounter_pid2;
        choose_enc_sid := encounter_sid2;
    end else if (val == 3) then begin
        choose_enc_pid := encounter_pid3;
        choose_enc_sid := encounter_sid3;
    end else if (val == 4) then begin
        choose_enc_pid := encounter_pid4;
        choose_enc_sid := encounter_sid4;
    end else if (val == 5) then begin
        choose_enc_pid := encounter_pid5;
        choose_enc_sid := encounter_sid5;
    end else if (val == 6) then begin
        choose_enc_pid := encounter_pid6;
        choose_enc_sid := encounter_sid6;
    end
    else begin
        choose_enc_pid := encounter_pid6;
        choose_enc_sid := encounter_sid6;
    end
end

procedure placeCritter(variable pid, variable sid, variable baseTile) begin
   variable tile;
   variable i;

   if (pid >= 1) then begin
      tile := tile_num_in_direction(baseTile, Random(0, 5), Random(1, 3));

      Critter := create_object_sid(pid, 0, 0, sid);
      critter_attempt_placement(Critter, tile, baseElevation);
      obj_rotate(Critter, random(0, 5));

      while ((tile_distance(tile_num(Critter),baseTile) > 5) and (i < 4)) do begin
         tile := tile_num_in_direction(baseTile, Random(0, 5), Random(1, 2));
         debug_msg("tile_num == "+tile);
         i+=1;
      end

      if ((i >= 4) and (tile > 0)) then begin
         critter_attempt_placement(Critter, baseTile, baseElevation);
      end

      if (tile_distance(tile_num(Critter), baseTile) > 5) then begin
         destroy_object(Critter);
         debug_msg("Couldn't find Safe spot. Destroying Ptr.");
      end
   end
   else begin
      debug_msg("ERROR: Pid < 1. Pid == "+pid+".");
   end
end

procedure placeScenery begin
   // TODO: Improve this shit
   if (Active_Scenery_List >= 1) then begin
      Scenery_Creation := array_random_value(Scenery1_List);
      Scenery_Creation := create_object_sid(Scenery_Creation, 0, 0, Scenery1_Script);
      Scenery_Creation_Hex := tile_num_in_direction(i, random(0, 5), Scenery1_Range);
      critter_attempt_placement(Scenery_Creation, Scenery_Creation_Hex, 1);
   end
   if (Active_Scenery_List >= 2) then begin
      Scenery_Creation := array_random_value(Scenery2_List);
      Scenery_Creation := create_object_sid(Scenery_Creation, 0, 0, Scenery2_Script);
      Scenery_Creation_Hex := tile_num_in_direction(i, random(0, 5), Scenery2_Range);
      critter_attempt_placement(Scenery_Creation, Scenery_Creation_Hex, 1);
   end
   if (Active_Scenery_List >= 3) then begin
      Scenery_Creation := array_random_value(Scenery3_List);
      Scenery_Creation := create_object_sid(Scenery_Creation, 0, 0, Scenery3_Script);
      Scenery_Creation_Hex := tile_num_in_direction(i, random(0, 5), Scenery3_Range);
      critter_attempt_placement(Scenery_Creation, Scenery_Creation_Hex, 1);
   end
end

/****************************************
   Scenery Types
****************************************/
procedure gold_mine begin
   foreach (i in SceneryPos_List) begin
      if (random(0, 2) == 1) then begin
         count := random(1, 6);
         while (count > 0) do begin
            count--;
            Scenery1_Range := random(0, 4);
            Scenery1_List := [PID_GOLD_NUGGET];

            Scenery_Chance := random(1, 100);
            if (Scenery_Chance <= 25) then begin
               Active_Scenery_List := 2;
               Scenery2_Range := random(0, 4);
               Scenery2_List := [PID_ROCK];
            end

            if (Scenery_Chance <= 10) then begin
               Active_Scenery_List := 3;
               Scenery3_Range := random(0, 4);
               Scenery3_List := [PID_SHOVEL, PID_FLARE, PID_HUNTING_RIFLE, PID_10MM_PISTOL, PID_SLEDGEHAMMER];
            end
            call placeScenery;
         end
      end
   end
end

procedure toxic_cave begin
   foreach (i in SceneryPos_List) begin
      if (random(0, 100) > 10) then begin
         count := random(3, 8);
         while (count > 0) do begin
            count--;
            Scenery1_Range := random(0, 2);
            Scenery1_List := [PID_BARREL_TOXIC_EMPTY, PID_BARREL_TOXIC_EMPTY,
                              PID_BARREL_TOXIC_FULL, PID_BARREL_TOXIC_FULL, PID_BARREL_TOXIC_FULL, PID_BARREL_TOXIC_FULL,
                              PID_BARREL_ALT_1,
                              PID_BARREL_STACK_2];

            Scenery_Chance := random(1, 100);
            if (Scenery_Chance <= 85) then begin
               Active_Scenery_List := 2;
               Scenery2_Range := random(0, 1);
               Scenery2_Script := SCRIPT_KTGOO;
               Scenery2_List := [PID_RAD_GOO_1, PID_RAD_GOO_3, PID_RAD_GOO_3, PID_RAD_GOO_4, PID_RAD_GOO_4];
            end
            call placeScenery;
         end
      end
   end

   // Add destroyed Mr.Handy
   Scenery_Chance := random(1, 100);
   if (Scenery_Chance <= 15) then begin
      Items_List := [PID_SMALL_ENERGY_CELL, PID_MICRO_FUSION_CELL, PID_FLAMETHROWER_FUEL];
      Scenery_Creation_Hex := array_random_value(Chest_List);

      Critter := create_object(PID_MRHANDY, 0, 0);
      critter_attempt_placement(Critter, Scenery_Creation_Hex, 1);
      obj_rotate(Critter, random(0,5));
      kill_critter(Critter, ANIM_exploded_to_nothing_sf);
      Item := array_random_value(Items_List);
      Item := create_object(Item, Critter_spawn_hex, 1);
      add_mult_objs_to_inven(Critter, Item, fortune_finder(1));
   end
end

procedure abandoned_hideout begin
   special_spawn_container_weapons := 1;

   foreach (i in SceneryPos_List) begin
      if (random(0, 100) > 10) then begin
         count := 1;
         while (count > 0) do begin
            count--;
            Scenery1_Range := random(0, 2);
            Scenery1_List := [PID_MATTRESS_1, PID_MATTRESS_2, PID_BED_1, PID_BED_2];

            Scenery_Chance := random(1, 100);
            if (Scenery_Chance <= 15) then begin
               Active_Scenery_List := 2;
               Scenery2_Range := random(0, 3);
               Scenery2_List := [PID_ARMCHAIR_1, PID_ARMCHAIR_2, PID_OLD_CHAIR,
                                 PID_METAL_BARREL_1, PID_TRASH_1, PID_TRASH_2, PID_TRASH_3, PID_TRASH_4,
                                 PID_POT, PID_WOODEN_TABLE_1];
            end
            call placeScenery;
         end
      end
   end
end

procedure dead_bodies begin
   Critter_spawn_hex := array_random_value(Area_List);
   i := Critter_spawn_hex; // Remember the position for placeScenery()
   Outer_ring := 6;
   Inner_ring := 1;
   Critter_script := -1;
   Scenery1_List := [PID_PEASANT_BLACK, PID_PEASANT_BLACK, PID_MERCHANT, PID_PEASANT_YELLOW_FEMALE, PID_LEATHER_ARMOR_MALE, PID_ZOMBIE_GUARD, PID_MERCHANT];
   foreach (Item in Scenery1_List) begin
      Scenery_Chance := random(1, 100);
      if (Scenery_Chance <= 95) then begin
         spawn_dead_critter(Item, Critter_script, random(48, 57));
         critter_attempt_placement(Critter, tile_num(Critter), 1);
         if (random(0,2) == 1) then item_caps_adjust(Critter, fortune_finder(random(1, 25)));
      end
   end

   Items_List := {PID_BONES_1: 75, PID_BONES_2: 75,
                  PID_SPEAR: 50, PID_KNIFE: 50, PID_KNIFE: 40, PID_SLEDGEHAMMER: 35, PID_CROWBAR: 45, PID_10MM_PISTOL: 15,
                  PID_44_FMJ_MAGNUM: 60, PID_10MM_AP: 60, PID_SHOTGUN_SHELLS: 50,
                  PID_DYNAMITE: 10, PID_BEER: 25,
                  PID_BOTTLE_CAPS: 50, PID_BOTTLE_CAPS: 50, PID_BOTTLE_CAPS: 50, PID_BOTTLE_CAPS: 45, PID_BOTTLE_CAPS: 40, PID_BOTTLE_CAPS: 40};
   foreach (Item : chance in Items_List) begin
      Scenery1_Range := random(0, 4);
      Scenery_Chance := random(1, 100);
      if (Scenery_Chance <= chance) then begin
         Scenery1_List := [Item];
         call placeScenery;
      end
   end
end

procedure cleaning_robot begin
   special_spawn_critters := 0;
   special_spawn_container_weapons := 1;
   debug("Spawn Cleaning Robot!");

   Outer_ring := 5;
   Inner_ring := 1;
   Critter_script := -1;
   Scenery1_List := [PID_ANT, PID_GECKO, PID_RAT_CAVE];
   Scenery1_List := array_random_value(Scenery1_List);
   foreach (i in Area_List) begin
      Critter_spawn_hex := i;
      count := random(2, 4);
      while (count > 0) do begin
         count--;
         spawn_dead_critter(Scenery1_List, Critter_script, random(48, 57));
         critter_attempt_placement(Critter, tile_num(Critter), 1);
      end
   end

   Critter_spawn_hex := array_random_value(Area_List);
   Critter_type := PID_MRHANDY;
   Critter_script := SCRIPT_ROBOT;
   call Place_critter;
   critter_attempt_placement(Critter, tile_num(Critter), 1);

   Items_List := [PID_SMALL_ENERGY_CELL, PID_MICRO_FUSION_CELL, PID_FLAMETHROWER_FUEL];
   Item := array_random_value(Items_List);
   Item := create_object(Item, Critter_spawn_hex, 1);
   add_mult_objs_to_inven(Critter, Item, fortune_finder(1));
end

procedure centaur_handler begin
   special_spawn_critters := 0;
   special_spawn_container_weapons := 1;

   // Spawn Handler
   Outer_ring := 2;
   Inner_ring := 1;
   Critter_script := SCRIPT_ECHANDLR;
   Critter_type := PID_MEAN_SUPER_MUTANT;
   Critter_spawn_hex := array_random_value(Area_List);
   call Place_critter;
   critter_attempt_placement(Critter, tile_num(Critter), 1);
   obj_rotate(Critter, random(0,5));

   arm_obj(Critter, PID_POWER_FIST, 1, PID_SMALL_ENERGY_CELL, 1)
   Item := create_object(PID_MEAT_JERKY, 0, 0);
   add_mult_objs_to_inven(Critter, Item, random(3,5));

   // Spawn Centaurs around Handler
   Outer_ring := 2;
   Inner_ring := 1;
   Critter_script := SCRIPT_ECHCENTR;
   Critter_type := PID_GREATER_CENTAUR;
   count := 1;
   while (count > 0) do begin
      count--;
      call Place_critter;
      critter_attempt_placement(Critter, tile_num(Critter), 1);
   end

   // Fill up the cave
   foreach (i in Area_List) begin
      Scenery_Chance := random(1, 100);
      if (Scenery_Chance <= 45) then begin
         Critter_spawn_hex := i;
         Scenery1_List := [PID_CENTAUR_LESSER, PID_GREATER_CENTAUR];
         Scenery1_List := array_random_value(Scenery1_List);
         count := random(1, 2);
         while (count > 0) do begin
            count--;
            Critter_type := Scenery1_List;
            call Place_critter;
            critter_attempt_placement(Critter, tile_num(Critter), 1);
         end
      end
   end
end

/****************************************
   Select Scenery Type
****************************************/
procedure LoadScenery begin
   if (SceneryPos_List > 0) then begin
      Choose_Scenery := random(1, 20);
      Active_Scenery_List := 1;

      // DEBUG:
      //Choose_Scenery := 8;

      if (Choose_Scenery == 1 and map_is_mine) then begin
         set_gold_mine;
         call gold_mine;
      end else if (Choose_Scenery >= 2 and Choose_Scenery <= 3) then begin
         set_toxic_cave;
         call toxic_cave;
      end else if (Choose_Scenery >= 4 and Choose_Scenery <= 5) then begin
         set_hideout_1;
         call abandoned_hideout;
      end else if (Choose_Scenery == 6) then begin
         set_dead_bodies;
         call dead_bodies;
      end else if (Choose_Scenery == 7) then begin
         set_robot_cleaner;
         call cleaning_robot;
      end else if (Choose_Scenery == 8 and global_var(GVAR_WORLDMAP_TABLE) == 11) then begin
         set_centaur_handler;
         call centaur_handler;
         call dead_bodies;
      end
   end
end

procedure LoadExitScenery begin
   Outer_ring := 8;
   Inner_ring := 3;
   Critter_spawn_hex := array_random_value(Exit_List);

   // Spawn Ladder
   if (CUR_MAP_MINE2 or CUR_MAP_MINE3) then begin
      Item := create_object_sid(PID_LADDER_HOLE, Critter_spawn_hex, 2, SCRIPT_ESLADDER);
      Item := create_object(PID_BLOCKING_HEX, Critter_spawn_hex, 2);
      set_map_var(MVAR_CAVERN_LADDER_ELEV2, tile_num_in_direction(Critter_spawn_hex, 2, 2));

      // Cover ladder with some dirt
      Scenery_Creation_Hex := tile_num_in_direction(Critter_spawn_hex, 1, 1);
      Scenery_Creation_Hex := tile_num_in_direction(Scenery_Creation_Hex, 2, 1);
      Scenery_Creation := create_object(PID_BLOCKING_HEX, Scenery_Creation_Hex, 2);
      Scenery_Creation := create_object(random(PID_JUNK_TOILET, PID_JUNK_DIRT_2), Scenery_Creation_Hex, 2);
      Scenery_Creation_Hex := tile_num_in_direction(Scenery_Creation_Hex, 4, 1);
      Scenery_Creation := create_object(PID_BLOCKING_HEX, Scenery_Creation_Hex, 2);
      Scenery_Creation_Hex := tile_num_in_direction(Scenery_Creation_Hex, 4, 2);
      Scenery_Creation := create_object(random(PID_DIRT_CORNER_1, PID_DIRT_CORNER_8), Scenery_Creation_Hex, 2);
   end

   // Spawn Scenery
   if map_is_mine then
      call Scenes(2);

   chance := random(1, 100);
   if (chance <= 8) or (map_is_mine and chance <= 80) then begin
      Create_Boxes_2(tile_num_in_direction(Critter_spawn_hex + random(0, 8) - 4, random(0, 5), random(5, 9)), 2)
      Create_Boxes_3(tile_num_in_direction(Critter_spawn_hex + random(0, 8) - 4, random(0, 5), random(5, 9)), 2)
      Create_Boxes_4(tile_num_in_direction(Critter_spawn_hex + random(0, 8) - 4, random(0, 5), random(5, 9)), 2)

      if map_is_mine then
         Item := create_object(PID_TRASH_CAN, tile_num_in_direction(Critter_spawn_hex + random(0, 8) - 4, random(0, 5), random(5, 9)), 2);

      Create_Junk_Barrel(tile_num_in_direction(Critter_spawn_hex + random(0, 8) - 4, random(0, 5), random(5, 9)), 2)
      Create_Junk_Dirt_1(tile_num_in_direction(Critter_spawn_hex + random(0, 8) - 4, random(0, 5), random(5, 9)), 2)
      Create_Junk_Dirt_2(tile_num_in_direction(Critter_spawn_hex + random(0, 8) - 4, random(0, 5), random(5, 9)), 2)
      Create_Junk_Tire(tile_num_in_direction(Critter_spawn_hex + random(0, 8) - 4, random(0, 5), random(5, 9)), 2)
   end

   // Dead Traveler
   chance := random(1, 100);
   if (chance <= 35) then begin
      Critter_type := PID_DEAD_TRAVELER;
      Critter_script := -1;
      call Place_critter;
      critter_attempt_placement(Critter, tile_num(Critter), 2);
      obj_rotate(Critter, random(0, 5));
      item_caps_adjust(Critter, fortune_finder(random(0, 60)));
      if (random(1, 4) == 4) then begin
         Item := create_object(PID_STIMPAK, 0, 0);
         add_obj_to_inven(Critter, Item);
      end
      if (random(1, 4) == 4) then begin
         Items_List := [PID_10MM_PISTOL, PID_GREASE_GUN, PID_SHOTGUN, PID_SPEAR, PID_SHARP_SPEAR];
         Item := create_object(array_random_value(Items_List), 0, 0);
         add_obj_to_inven(Critter, Item);
      end
      if (random(1, 4) == 4) then begin
         Items_List := [PID_10MM_JHP, PID_9MM_AMMO, PID_7_62MM_AMMO, PID_SHOTGUN_SHELLS, PID_5MM_JHP];
         Item := create_object(array_random_value(Items_List), 0, 0);
         add_mult_objs_to_inven(Critter, Item, 1 + dude_perk(PERK_scrounger));
      end
      if (random(1, 6) == 4) then begin
         Item := create_object(PID_BACKPACK, 0, 0);
         add_obj_to_inven(Critter, Item);
      end
      kill_critter(Critter, ANIM_fall_back_sf);
   end

   // Spawn Alcohol
   if map_is_mine then begin
      chance := random(1, 100);
      if (chance <= 25) then begin
         Items_List := [PID_BEER, PID_BOOZE, PID_GAMMA_GULP_BEER, PID_ROENTGEN_RUM];
         Critter_type := array_random_value(Items_List);
         count := random(1, 6);
         while (count > 0) do begin
            count--;
            call Place_critter;
            critter_attempt_placement(Critter, tile_num(Critter), 2);
         end
      end
   end

   // Bag of caps
   chance := random(1, 100);
   if (chance <= 15) then begin
      Critter_type := PID_BAG;
      call Place_critter;
      critter_attempt_placement(Critter, tile_num(Critter), 2);
      item_caps_adjust(Critter, fortune_finder(random(20, 70)));
   end

   // Spawn Mobs
   chance := random(1, 100);
   if (chance <= 50) then begin
      call Choose_Encounter;
      Outer_ring := 12;
      Inner_ring := 6;
      baseElevation := 2;
      count := total_encounter_mobs;
      while (count > 0) do begin
         variable Facing := 0;
         variable Distance := 0;
         variable Ring := 0;

         call Choose_Pid;
         call placeCritter(choose_enc_pid, choose_enc_sid, Critter_spawn_hex);
         count -= 1;

         Ring := random(Inner_ring, Outer_ring);
         Facing := random(0, 5);
         Critter_tile := tile_num_in_direction(Critter_spawn_hex, random(0, 5), Ring);
         Distance := tile_num_in_direction(Critter_tile, Facing, (Ring / 2));
         if ((tile_distance(Critter_spawn_hex, Distance) <= Outer_ring) and (tile_distance(Critter_spawn_hex, Distance) >= Inner_ring)) then begin
            Critter_tile := tile_num_in_direction(Critter_tile, Facing, (Ring / 2));
         end
         critter_attempt_placement(Critter, Critter_tile, 2);
      end
   end

   // Spawn camp fire with sleeping bag
   chance := random(1, 100);
   if (chance <= 50) then begin
      // TODO: Rewrite this
      CritterXpos := (Critter_tile % 200) - 4;
      CritterYpos := Critter_tile / 200;
      Item := create_object(PID_FIRE_PIT, 0, 0);
      critter_attempt_placement(Item, ((CritterYpos + 4) * 200) + (CritterXpos - 2), 2);
      Item := create_object(PID_BED_1, 0, 0);
      critter_attempt_placement(Item, ((CritterYpos + 4) * 200) + (CritterXpos - 4), 2);
   end
end

/****************************************
   Load random container
****************************************/
procedure LoadChests begin
   variable
      container,
      container_type,
      count;

   // Spawn fancy weapons container
   chance := random(1, 100);
   if (chance <= (70 + dude_luck) and (map_is_mine or special_spawn_container_weapons == 1)) then begin
      Scenery_Creation_Hex := array_random_value(Chest_List);
      debug("SPAWN FANCY WEAPON CONTAINER!");

      // Container #1
      chance := random(1, 100);
      if (chance <= (70 + dude_luck)) then begin
         Scenery_Creation := create_object(PID_BLOCKING_HEX, Scenery_Creation_Hex, 1);
         Scenery_Creation_Hex := tile_num_in_direction(Scenery_Creation_Hex, 2, 1);
         Scenery_Creation := create_object(PID_BLOCKING_HEX, Scenery_Creation_Hex, 1);
         container := create_object(PID_CRATE_BRWN_STACK2, Scenery_Creation_Hex, 1);

         // Add a weapon
         Items_List := [PID_HUNTING_RIFLE, PID_SCOPED_HUNTING_RIFLE, PID_ASSAULT_RIFLE, PID_ASSAULT_RIFLE_EXT_MAG, PID_FN_FAL, PID_SNIPER_RIFLE, PID_TOMMY_GUN,
                        PID_COMBAT_SHOTGUN, PID_HK_CAWS, PID_PANCOR_JACKHAMMER, PID_SAWED_OFF_SHOTGUN,
                        PID_MINIGUN, PID_LIGHT_SUPPORT_WEAPON, PID_BOZAR, PID_GATLING_LASER, PID_IMPROVED_FLAMETHROWER,
                        PID_SUPER_SLEDGE, PID_POWER_FIST, PID_MEGA_POWER_FIST, PID_RIPPER,
                        PID_LASER_RIFLE_EXT_CAP, PID_YK32_PULSE_PISTOL, PID_LASER_PISTOL, PID_PLASMA_PISTOL, PID_MAGNETO_LASER_PISTOL,
                        PID_10MM_PISTOL, PID_10MM_SMG, PID_14MM_PISTOL, PID_HK_P90C, PID_GREASE_GUN,
                        PID_DESERT_EAGLE, PID_DESERT_EAGLE_EXT_MAG, PID_44_MAGNUM_REVOLVER, PID_44_MAGNUM_SPEEDLOADER];
         if (container) then begin
            Item := array_random_value(Items_List);
            add_obj_to_inven(container, create_object(Item, 0, 0));

            chance := random(1, 100);
            if (chance < 50) then begin
               Item := array_random_value(Items_List);
               add_obj_to_inven(container, create_object(Item, 0, 0));
            end
         end
      end

      // Container #2
      chance := random(1, 100);
      if (chance <= (75 + dude_luck)) then begin
         Scenery_Creation_Hex := tile_num_in_direction(Scenery_Creation_Hex, 1, 1);
         Scenery_Creation := create_object(PID_BLOCKING_HEX, Scenery_Creation_Hex, 1);
         Scenery_Creation_Hex := tile_num_in_direction(Scenery_Creation_Hex, 2, 1);
         Scenery_Creation := create_object(PID_BLOCKING_HEX, Scenery_Creation_Hex, 1);
         container := create_object(random(PID_CRATE_BRWN_1, PID_CRATE_BRWN_2), Scenery_Creation_Hex, 1);

         // Add ammo
         Items_List := [PID_EXPLOSIVE_ROCKET, PID_ROCKET_AP, PID_10MM_JHP, PID_10MM_AP, PID_44_MAGNUM_JHP,
                        PID_FLAMETHROWER_FUEL,PID_14MM_AP, PID_223_FMJ, PID_5MM_JHP, PID_5MM_AP,
                        PID_SMALL_ENERGY_CELL, PID_MICRO_FUSION_CELL, PID_SHOTGUN_SHELLS, PID_44_FMJ_MAGNUM,
                        PID_45_CALIBER_AMMO, PID_7_62MM_AMMO];
         if (container) then begin
            count := random(1, 3);
            while (count > 0) do begin
               count--;
               Item := array_random_value(Items_List);
               add_obj_to_inven(container, create_object(Item, 0, 0));
            end

            // 2nd ammo batch
            chance := random(1, 100);
            if (chance < 50) then begin
               count := random(1, 5);
               while (count > 0) do begin
                  count--;
                  Item := array_random_value(Items_List);
                  add_obj_to_inven(container, create_object(Item, 0, 0));
               end
            end
         end
      end

      // Container #3
      chance := random(1, 100);
      if (chance <= (80 + dude_luck)) then begin
         Scenery_Creation_Hex := tile_num_in_direction(Scenery_Creation_Hex, 4, 2);
         Scenery_Creation := create_object(PID_BLOCKING_HEX, Scenery_Creation_Hex, 1);
         Scenery_Creation_Hex := tile_num_in_direction(Scenery_Creation_Hex, 2, 1);
         Scenery_Creation := create_object(PID_BLOCKING_HEX, Scenery_Creation_Hex, 1);
         container := create_object(random(PID_CRATE_BRWN_1, PID_CRATE_BRWN_2), Scenery_Creation_Hex, 1);

         // Add Meds
         Items_List := [PID_STIMPAK, PID_STIMPAK, PID_STIMPAK, PID_STIMPAK, PID_STIMPAK, PID_SUPER_STIMPAK, PID_FIRST_AID_BOOK, PID_FIRST_AID_KIT, PID_DOCTORS_BAG,
                        PID_MOTION_SENSOR, PID_MULTI_TOOL];
         count := random(1, 4);
         if (container) then begin
            while (count > 0) do begin
               count--;
               Item := array_random_value(Items_List);
               add_obj_to_inven(container, create_object(Item, 0, 0));
            end
         end
      end
   end
   else if (special_spawn_container == 1) then begin
      Items_List := [ PID_ROCK, PID_ROPE, PID_FLARE, PID_STIMPAK,
                      PID_10MM_JHP, PID_10MM_AP, PID_223_FMJ, PID_44_MAGNUM_JHP, PID_MICRO_FUSION_CELL, PID_SMALL_ENERGY_CELL,
                      PID_SPEAR, PID_KNIFE, PID_THROWING_KNIFE, PID_CATTLE_PROD ];

      Scenery_Creation_Hex := array_random_value(Chest_List);
      container_type := [PID_CHEST, PID_BAG, PID_BACKPACK, PID_BROWN_BAG];
      container_type := array_random_value(container_type);
      container := create_object(container_type, Scenery_Creation_Hex, 1);
      count := random(1, 4);
      if (container) then begin
         while (count > 0) do begin
            count--;
            Item := array_random_value(Items_List);
            add_obj_to_inven(container, create_object(Item, 0, 0));
         end
         if (random(0, 1) == 1) then
            item_caps_adjust(container, fortune_finder(10 * Random(1, dude_luck) + random(0, 9)));
      end

      // Rubber Boots
      if cave_is_toxic then begin
         if (random(0, 2) == 1) then
            add_obj_to_inven(container, create_object(PID_RUBBER_BOOTS, 0, 1));
      end
   end
end


#endif // CVGENENC_H
