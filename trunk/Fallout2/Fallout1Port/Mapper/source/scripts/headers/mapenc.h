/*

	Generic Encounters

*/

#ifndef MAPENC_H
#define MAPENC_H

/************************************************
    Generic Defines
************************************************/

// All Map Vars need to start w/ MVAR_
#define MVAR_Hostile_Total             	(0)   // Number of monsters created
#define MVAR_CARVN_LEAD 				(1)

//==================================================================
#define spawn_dead_critter(x,y,z)		Critter_type := x; 	      \
										Critter_script := y;				      \
										Critter_direction := random(0, 5); 	\
										call Place_critter; 				      \
										anim(Critter, 1000, random(0, 5)); 	\
										kill_critter(Critter, z)

#define enc_group_angle(x) 			if (group_angle == 0) then begin \
										x := 3;								         \
									end										         \
									else if (group_angle == 1) then begin	   \
										x := 4;								         \
									end										         \
									else if (group_angle == 2) then begin	   \
										x := 5;								         \
									end										         \
									else if (group_angle == 3) then begin	   \
										x := 0;								         \
									end										         \
									else if (group_angle == 4) then begin	   \
										x := 1;								         \
									end										         \
									else if (group_angle == 5) then begin	   \
										x := 2;								         \
									end

/************************************************
    Mysterious Stranger Fo1
************************************************/
variable Critter;
variable Critter_direction;
variable Critter_script := -1;
variable Critter_tile;
variable Critter_type;
variable CritterXpos;// ---------------RNDMTN ONLY
variable CritterYpos;// ---------------RNDMTN ONLY

variable Inner_ring;
variable Item;
variable Outer_ring;

procedure Place_critter;

procedure Add_Mysterious_Stranger begin
   variable Critter;
   variable Critter_Tile;
   variable Die_Roll;
   variable Stranger_Chance;
   variable val;

   Die_Roll:=random(0,99);
   Stranger_Chance:=30 + (2 * dude_luck);

   debug("spawn fo2 stranger!");

   if ((map_first_run) and (not(get_stranger_flag(STRANGER_DEAD))) and (Die_Roll < Stranger_Chance) and ((has_trait(TRAIT_PERK,dude_obj,PERK_mysterious_stranger)))) then begin
       if (not(get_stranger_flag(STRANGER_GENDER))) then begin
           set_stranger_flag(STRANGER_GENDER);
           if (random(0,99) < 50) then
               set_stranger_flag(STRANGER_FEMALE);
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

#endif // MAPENC_H
