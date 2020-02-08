/*
	Copyright 1998-2003 Interplay Entertainment Corp.  All rights reserved.
*/

#ifndef CVGENENC_H
#define CVGENENC_H
/*
    This file contains generic information for the cave random encounters
*/

variable begin
   encounter_pid1 := 0;
   encounter_pid2 := 0;
   encounter_pid3 := 0;
   encounter_pid4 := 0;
   encounter_pid5 := 0;
   encounter_pid6 := 0;

   encounter_sid1 := 0;
   encounter_sid2 := 0;
   encounter_sid3 := 0;
   encounter_sid4 := 0;
   encounter_sid5 := 0;
   encounter_sid6 := 0;

   active_encounter_pids := 0;
   total_encounter_mobs := 0; //Per area in map


   special_theif_encounter := 0;

   choose_enc_pid := 0;
   choose_enc_sid := 0;
end

procedure Choose_Encounter begin
   variable 
      val := Random(1, 4),
      rnd_chest := random(1, 100),
      rnd_critter;

   if (rnd_chest > 40 and (stat_success(dude_obj, STAT_lu, 0))) then
      special_theif_encounter := 1;
   else
      special_theif_encounter := 0;

   // Geckos
   if (val == 1) then begin
      active_encounter_pids := 1;
      rnd_critter := random(1, 100);
      if (rnd_critter < 75) then begin
         encounter_pid1 := PID_GECKO;
         encounter_sid1 := SCRIPT_ECGECKO;
         if (random(0, 4) == 1) then begin
            encounter_pid2 := PID_GOLDEN_GECKO;
            encounter_sid2 := SCRIPT_ECGECKO;
            active_encounter_pids := 2;
         end
         total_encounter_mobs := Random(1, 3);
      end else if (rnd_critter < 90) then begin
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
         active_encounter_pids := 1;
         encounter_pid1 := PID_RADSCORPION;
         encounter_sid1 := SCRIPT_RADSCORP;
         total_encounter_mobs := Random(3, 5);
      end else begin
         active_encounter_pids := 2;
         encounter_pid1 := PID_SMALL_RADSCORPION;
         encounter_pid2 := PID_RADSCORPION;
         encounter_sid1 := SCRIPT_RADSCORP;
         encounter_sid2 := SCRIPT_RADSCORP;
         total_encounter_mobs := Random(3, 5);
      end
   end
   
   // Rats
   else if (val == 3) then begin
      active_encounter_pids := 1;
      rnd_critter := random(1, 100);
      
      if (rnd_critter < 50) then begin
         encounter_pid1 := PID_RAT_CAVE;
         encounter_sid1 := SCRIPT_WANRATS;
         total_encounter_mobs := Random(3, 5);
      end else if (rnd_critter < 75) then begin
         active_encounter_pids := 1;
         encounter_pid1 := PID_PIGRAT;
         encounter_sid1 := SCRIPT_WANRATS;
         total_encounter_mobs := Random(2, 4);
      end else begin
         active_encounter_pids := 2;
         encounter_pid1 := PID_GREATER_MOLE_RAT;
         encounter_pid1 := PID_PIGRAT;
         encounter_sid1 := SCRIPT_WANRATS;
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
   
   // Raiders
   /*
   else if (val == 8) then begin
      if (stat_success(dude_obj, STAT_lu, 0)) then begin
         special_theif_encounter := 1;
         active_encounter_pids := 2;

         encounter_pid1 := PID_GEN_TRAVELER;
         encounter_pid2 := PID_TRAVELER_BALD_LEATHER;
         encounter_sid1 := SCRIPT_GENRAIDA;
         encounter_sid2 := SCRIPT_GENRAIDA;
         total_encounter_mobs := Random(2, 3);
      end
   end
   */
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
   variable obj;
   variable i;

   if (pid >= 1) then begin
      tile := tile_num_in_direction(baseTile, Random(0, 5), Random(1, 3));

      obj := create_object_sid(pid, 0, 0, sid);
      critter_attempt_placement(obj, tile, 1);
      obj_rotate(obj, random(0, 5));
         
      while ((tile_distance(tile_num(obj),baseTile) > 5) and (i < 4)) do begin
         tile := tile_num_in_direction(baseTile, Random(0, 5), Random(1, 2));
         debug_msg("tile_num == "+tile);
         i+=1;
      end

      if ((i >= 4) and (tile > 0)) then begin
         critter_attempt_placement(obj,baseTile,1);
      end

      if (tile_distance(tile_num(obj),baseTile) > 5) then begin
         destroy_object(obj);
         debug_msg("Couldn't find Safe spot. Destroying Ptr.");
      end
   end
   else begin
      debug_msg("ERROR: Pid < 1. Pid == "+pid+".");
   end
end

#endif // CVGENENC_H
