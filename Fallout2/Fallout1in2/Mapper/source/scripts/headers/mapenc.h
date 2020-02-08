/*

   Generic Encounters

*/

#ifndef MAPENC_H
#define MAPENC_H

/************************************************
    Generic Defines
************************************************/

// All Map Vars need to start w/ MVAR_
#define MVAR_Hostile_Total             (0)   // Number of monsters created
#define MVAR_CARVN_LEAD                (1)
#define MVAR_CAVERN_TYPE               (2)

// Cavern Type for random scenery spawn
#define TOXIC_CAVE         (1)
#define GOLD_MINE          (2)
#define HIDEOUT_1          (3)

#define set_gold_mine      set_map_var(MVAR_CAVERN_TYPE, GOLD_MINE)
#define set_toxic_cave     set_map_var(MVAR_CAVERN_TYPE, TOXIC_CAVE)
#define set_hideout_1      set_map_var(MVAR_CAVERN_TYPE, HIDEOUT_1)

#define cave_is_gold_mine  (map_var(MVAR_CAVERN_TYPE) == GOLD_MINE)
#define cave_is_radiated   (map_var(MVAR_CAVERN_TYPE) == TOXIC_CAVE)
#define cave_is_hideout_1  (map_var(MVAR_CAVERN_TYPE) == HIDEOUT_1)

//==================================================================
#define spawn_dead_critter(x,y,z)      \
   Critter_type := x;                  \
   Critter_script := y;                \
   Critter_direction := random(0, 5);  \
   call Place_critter;                 \
   anim(Critter, 1000, random(0, 5));  \
   kill_critter(Critter, z)

#define enc_group_angle(x)                   \
   if (group_angle == 0) then begin          \
      x := 3;                                \
   end                                       \
   else if (group_angle == 1) then begin     \
      x := 4;                                \
   end                                       \
   else if (group_angle == 2) then begin     \
      x := 5;                                \
   end                                       \
   else if (group_angle == 3) then begin     \
      x := 0;                                \
   end                                       \
   else if (group_angle == 4) then begin     \
      x := 1;                                \
   end                                       \
   else if (group_angle == 5) then begin     \
      x := 2;                                \
   end

// Ranger-Perk encounter re-roll
#define ranger_perk_reroll_enc(a,b,c,d,e) \
   while (Ranger_rerolls > 0) do begin                                                                                                       \
      Ranger_rerolls := (Ranger_rerolls - 1);                                                                                                \
      if ((Encounter_Num == a) or (Encounter_Num == b) or (Encounter_Num == c) or (Encounter_Num == d) or (Encounter_Num == e)) then begin   \
         debug("Ranger Perk: Re-roll encounter! " + Encounter_Num);                                                                          \
         call roll_encounter;                                                                                                                \
      end                                                                                                                                    \
   end \
   noop

// Temp variables
variable group_angle;
variable Critter;
variable Critter_direction;
variable Critter_script := -1;
variable Critter_tile;
variable Critter_type;
variable CritterXpos;// ---------------RNDMTN ONLY
variable CritterYpos;// ---------------RNDMTN ONLY

variable Skill_roll;

variable Inner_ring;
variable Item;
variable Outer_ring;

procedure Place_critter;

/************************************************
    Mysterious Stranger
************************************************/
procedure Add_Mysterious_Stranger begin
   variable Critter;
   variable Critter_Tile;
   variable Die_Roll;
   variable Stranger_Chance;
   variable val;

   Die_Roll:=random(0,99);
   Stranger_Chance:=30 + (2 * dude_luck);

   if ((map_first_run) and (not(get_stranger_flag(STRANGER_DEAD))) and (Die_Roll < Stranger_Chance) and ((has_trait(TRAIT_PERK,dude_obj,PERK_mysterious_stranger)))) then begin
       if (not(get_stranger_flag(STRANGER_GENDER))) then begin
           set_stranger_flag(STRANGER_GENDER);
           if (random(0,99) < 50) then begin
               set_stranger_flag(STRANGER_FEMALE);
           end
       end
       if (get_stranger_flag(STRANGER_FEMALE)) then
           Critter:=create_object_sid(PID_MYSTERIOUS_STRANGER_FEMALE,0,0,SCRIPT_MYSTSTRN);
       else
           Critter:=create_object_sid(PID_MYSTERIOUS_STRANGER_MALE,0,0,SCRIPT_MYSTSTRN);
       Critter_Tile:=tile_num_in_direction(tile_num(dude_obj),random(0,5),random(5,10));
       critter_attempt_placement(Critter,Critter_Tile,elevation(dude_obj));
       val := critter_add_trait(Critter,TRAIT_OBJECT,OBJECT_TEAM_NUM,TEAM_PLAYER);
       item_caps_adjust(Critter,random(30,60));
       anim(Critter,ANIMATE_ROTATION,dude_cur_rot);
   end
end

// Fallout 1 mysterious stranger:
/*
procedure stranger begin
   if (dude_perk( PERK_mysterious_stranger ) and (global_var( GVAR_MYST_STRANGER_DEAD ) == 0) and random(0, 1)) then begin
      Critter_type := PID_MYSTERIOUS_STRANGER;
      Critter_script := SCRIPT_MYSTSTRN;
      Critter_direction := random(0, 5);
      Outer_ring := 7;
      Inner_ring := 4;

      call Place_critter;

      Critter_direction := dude_cur_rot + (random(0, 2) - 1);
      while (Critter_direction < 0) do begin
         Critter_direction := Critter_direction + 6;
      end
      if (Critter_direction > 5) then begin
         Critter_direction := Critter_direction % 6;
      end

      Item := create_object( PID_PURPLE_ROBE, 0, 0 );
      add_obj_to_inven(Critter, Item);
      Item := create_object( PID_SPEAR, 0, 0 );
      add_obj_to_inven(Critter, Item);
      Item := create_object( PID_STIMPAK, 0, 0 );
      add_mult_objs_to_inven(Critter, Item, 2);
      Item := item_caps_adjust(Critter, random(7, 30) * (dude_fortune_finder * global_var( GVAR_FORTUNE_FINDER_HOW_MUCH )));
      set_global_var( GVAR_MYST_STRANGER_ITEM, 10 );
   end
end
*/

/************************************************
    Avellone, the Bounty Hunter + his crew
************************************************/
procedure hunters begin
   display_msg(message_str(SCRIPT_RNDDESRT, 402));

   Inner_ring := 8;
   Outer_ring := 5;
   group_angle := random(0, 5);
   Critter_direction := group_angle + random(0, 3 * 2) - 3;
   while(Critter_direction < 0) do begin
      Critter_direction := Critter_direction + 6;
   end
   if (Critter_direction > 5) then begin
      Critter_direction := Critter_direction % 6;
   end

   // Avellone
   Critter_type := PID_AVELLONE;
   Critter_script := SCRIPT_HUNTER;
   call Place_critter;
   obj_rotate(Critter, rotation_to_tile(tile_num(Critter), dude_tile));

   Item := create_object(PID_ASSAULT_RIFLE, 0, 0);
   add_obj_to_inven(Critter, Item);
   Item := create_object(PID_5MM_AP, 0, 0);
   add_mult_objs_to_inven(Critter, Item, 4 * (dude_perk(PERK_scrounger) + 1));
   if not(fo1in2_destroy_armor_disabled) then begin
      Item := create_object(PID_COMBAT_ARMOR, 0, 0);
      add_obj_to_inven(Critter, Item);
      wield_obj_critter(Critter, Item);
   end
   item_caps_adjust(Critter, random(5, 30) * (dude_fortune_finder * global_var(GVAR_FORTUNE_FINDER_HOW_MUCH)));
   Item := create_object(PID_SUPER_STIMPAK, 0, 0);
   add_mult_objs_to_inven(Critter, Item, 2);

   Critter_direction := group_angle + random(0, 3 * 2) - 3;
   while(Critter_direction < 0) do begin
      Critter_direction := Critter_direction + 6;
   end
   if (Critter_direction > 5) then begin
      Critter_direction := Critter_direction % 6;
   end

   // Thug #1
   Critter_type := PID_THUG_FEMALE_YELLOW;
   Critter_script := SCRIPT_THUG;
   call Place_critter;
   obj_rotate(Critter, rotation_to_tile(tile_num(Critter), dude_tile));

   if (random(0,1) == 1) then begin
      Item := create_object(PID_SPEAR, 0, 0);
      add_obj_to_inven(Critter, Item);
   end
   else begin
      Item := create_object(PID_RIPPER, 0, 0);
      add_obj_to_inven(Critter, Item);
   end
   wield_obj_critter(Critter, Item);

   Item := create_object(PID_STIMPAK, 0, 0);
   add_mult_objs_to_inven(Critter, Item, 3);

   if not(fo1in2_destroy_armor_disabled) then begin
      Item := create_object(PID_METAL_ARMOR, 0, 0);
      add_obj_to_inven(Critter, Item);
      wield_obj_critter(Critter, Item);
   end
   if (random(0, 2) == 0) then begin
      item_caps_adjust(Critter, random(5, 30) * (dude_fortune_finder * global_var(GVAR_FORTUNE_FINDER_HOW_MUCH)));
   end

   Critter_direction := group_angle + random(0, 3 * 2) - 3;
   while(Critter_direction < 0) do begin
      Critter_direction := Critter_direction + 6;
   end
   if (Critter_direction > 5) then begin
      Critter_direction := Critter_direction % 6;
   end

   // Thug #2
   Critter_type := PID_THUG_MALE_METAL;
   Critter_script := SCRIPT_THUG;
   call Place_critter;
   obj_rotate(Critter, rotation_to_tile(tile_num(Critter), dude_tile));

   Item := create_object(PID_SNIPER_RIFLE, 0, 0);
   add_obj_to_inven(Critter, Item);
   Item := create_object(PID_223_FMJ, 0, 0);
   add_mult_objs_to_inven(Critter, Item, 3 * (dude_perk(PERK_scrounger) + 1));
   if not(fo1in2_destroy_armor_disabled) then begin
      Item := create_object(PID_METAL_ARMOR, 0, 0);
      add_obj_to_inven(Critter, Item);
      wield_obj_critter(Critter, Item);
   end
   Item := create_object(PID_EXPLOSIVE_ROCKET, 0, 0);
   add_mult_objs_to_inven(Critter, Item, 2 * (dude_perk(PERK_scrounger) + 1));
   if (random(0, 2) == 0) then begin
      item_caps_adjust(Critter, random(5, 40) * (dude_fortune_finder * global_var(GVAR_FORTUNE_FINDER_HOW_MUCH)));
   end

   Critter_direction := group_angle + random(0, 3 * 2) - 3;
   while(Critter_direction < 0) do begin
      Critter_direction := Critter_direction + 6;
   end
   if (Critter_direction > 5) then begin
      Critter_direction := Critter_direction % 6;
   end

   // Thug #3
   Critter_type := PID_THUG_BLACK_METAL;
   Critter_script := SCRIPT_THUG;
   call Place_critter;
   obj_rotate(Critter, rotation_to_tile(tile_num(Critter), dude_tile));

   Item := create_object(PID_DESERT_EAGLE, 0, 0);
   add_obj_to_inven(Critter, Item);
   Item := create_object(PID_44_MAGNUM_JHP, 0, 0);
   add_mult_objs_to_inven(Critter, Item, 2 * (dude_perk(PERK_scrounger) + 1));
   if not(fo1in2_destroy_armor_disabled) then begin
      Item := create_object(PID_METAL_ARMOR, 0, 0);
      add_obj_to_inven(Critter, Item);
      wield_obj_critter(Critter, Item);
   end
   if (random(0, 2) == 0) then begin
      item_caps_adjust(Critter, random(5, 30) * (dude_fortune_finder * global_var(GVAR_FORTUNE_FINDER_HOW_MUCH)));
   end

   call Add_Mysterious_Stranger;
end

/************************************************
    Dehydration encounters
************************************************/
#define mstr_item_supply      (message_str(SCRIPT_RNDDESRT, 1250) + obj_name(Item) + message_str(SCRIPT_RNDDESRT, 1251))

#define dude_has_water_items  ((dude_item_count(PID_NUKA_COLA) +           \
                              dude_item_count(PID_WATER_FLASK) +           \
                              dude_item_count(PID_BEER) +                  \
                              dude_item_count(PID_BOOZE) +                 \
                              dude_item_count(PID_ROENTGEN_RUM) +          \
                              dude_item_count(PID_GAMMA_GULP_BEER)) > 0)

#define drink_water_item \
   if (dude_item_count(PID_NUKA_COLA)) then              \
      Item := dude_item(PID_NUKA_COLA);                  \
   else if (dude_item_count(PID_WATER_FLASK)) then       \
      Item := dude_item(PID_WATER_FLASK);                \
   else if (dude_item_count(PID_BEER)) then              \
      Item := dude_item(PID_BEER);                       \
   else if (dude_item_count(PID_BOOZE)) then             \
      Item := dude_item(PID_BOOZE);                      \
   else if (dude_item_count(PID_ROENTGEN_RUM)) then      \
      Item := dude_item(PID_ROENTGEN_RUM);               \
   else if (dude_item_count(PID_GAMMA_GULP_BEER)) then   \
      Item := dude_item(PID_GAMMA_GULP_BEER);            \
   if (obj_pid(Item) == PID_WATER_FLASK) then            \
      display_msg(message_str(SCRIPT_RNDDESRT, 125));    \
   else                                                  \
      display_msg(mstr_item_supply);                     \
   set_global_var(GVAR_OBJ_DUDE_USE_DRUG, Item)

// Necropolis, Junktown, Brotherhood of Steel, North Table, South Table, Shady Sands, Vats Table
variable TimeHours := 0;
variable hpDamage := 0;
procedure dehydration_a begin
   TimeHours := random(1, 6);
   if dude_has_water_items then begin
      drink_water_item;
   end
   else begin
      Skill_roll := roll_vs_skill(dude_obj, SKILL_OUTDOORSMAN, 20 * dude_perk(PERK_survivalist));
      if (is_success(Skill_roll)) then begin
         if (TimeHours == 1) then
            display_msg(message_str(SCRIPT_RNDDESRT, 109));
         else
            display_msg(message_str(SCRIPT_RNDDESRT, 110) + TimeHours + message_str(SCRIPT_RNDDESRT, 111));
      end
      else begin
         if (is_critical(Skill_roll)) then begin
            hpDamage := random(15, 24 + TimeHours); // Fo1: 2 to 4
            if (hpDamage >= dude_cur_hp) then hpDamage := dude_cur_hp - 1;
            if (TimeHours == 1) then
               display_msg(message_str(SCRIPT_RNDDESRT, 112) + hpDamage + message_str(SCRIPT_RNDDESRT, 113));
            else
               display_msg(message_str(SCRIPT_RNDDESRT, 114) + TimeHours + message_str(SCRIPT_RNDDESRT, 115) + hpDamage + message_str(SCRIPT_RNDDESRT, 116));
         end
         else begin
            hpDamage := random(6, 12 + TimeHours); // Fo1: 1 to 2
            if (hpDamage >= dude_cur_hp) then hpDamage := dude_cur_hp - 1;
            if (TimeHours == 1) then begin
               if (hpDamage == 1) then
                  display_msg(message_str(SCRIPT_RNDDESRT, 117));
               else
                  display_msg(message_str(SCRIPT_RNDDESRT, 118) + hpDamage + message_str(SCRIPT_RNDDESRT, 119));
            end
            else begin
               if (hpDamage == 1) then
                  display_msg(message_str(SCRIPT_RNDDESRT, 120) + TimeHours + message_str(SCRIPT_RNDDESRT, 121));
               else
                  display_msg(message_str(SCRIPT_RNDDESRT, 122) + TimeHours + message_str(SCRIPT_RNDDESRT, 123) + hpDamage + message_str(SCRIPT_RNDDESRT, 124));
            end
         end
         if (hpDamage >= 20) then begin
            dude_knockdown_nosfx;
         end
         critter_heal(dude_obj, -hpDamage); // This will not show another message log entry
      end
      TimeHours := TimeHours * ONE_GAME_HOUR;
      game_time_advance(game_ticks(TimeHours));
   end
end

// Hub, Death(claw) table
procedure dehydration_b begin
   TimeHours := random(1, 6) + 2;
   if dude_has_water_items then begin
      drink_water_item;
   end
   else begin
      Skill_roll := roll_vs_skill(dude_obj, SKILL_OUTDOORSMAN, 20 * has_trait(TRAIT_PERK, dude_obj, PERK_survivalist));
      if (is_success(Skill_roll)) then begin
         display_msg(message_str(SCRIPT_RNDDESRT, 110) + TimeHours + message_str(SCRIPT_RNDDESRT, 111));
      end
      else begin
         if (is_critical(Skill_roll)) then begin
            hpDamage := random(15, 24 + TimeHours); // Fo1: 2 to 4
         end
         else begin
            hpDamage := random(6, 12 + TimeHours); // Fo1: 2 to 3
         end
         if (hpDamage >= dude_cur_hp) then hpDamage := dude_cur_hp - 1;
         if (hpDamage == 1) then
            display_msg(message_str(SCRIPT_RNDDESRT, 114) + TimeHours + message_str(SCRIPT_RNDDESRT, 115) + hpDamage + message_str(SCRIPT_RNDDESRT, 1160));
         else
            display_msg(message_str(SCRIPT_RNDDESRT, 114) + TimeHours + message_str(SCRIPT_RNDDESRT, 115) + hpDamage + message_str(SCRIPT_RNDDESRT, 116));
         if (hpDamage >= 20) then begin
            dude_knockdown_nosfx;
         end
         critter_heal(dude_obj, -hpDamage); // This will not show another message log entry
      end
      TimeHours := TimeHours * ONE_GAME_HOUR;
      game_time_advance(game_ticks(TimeHours));
   end
end

#endif // MAPENC_H
