/*

    General Scrapheap header
    Used to track quest states.

*/

#ifndef SCRAPHEAP_H
#define SCRAPHEAP_H

/************************************************
    Generic Defines
************************************************/

#define KNOWS_FOOLS           (map_var(MVAR_Know_Fools) > 0)
#define KNOWS_CRYPTS          (map_var(MVAR_Know_Crypts) > 0)
#define KNOWS_POWER           (map_var(MVAR_Know_Power) > 0)

#define set_knows_fools       set_map_var(MVAR_Know_Fools, 1)
#define set_knows_crypts      set_map_var(MVAR_Know_Crypts, 1)
#define set_knows_power       set_map_var(MVAR_Know_Power, 1)

#define DUDE_IS_FOOL          (map_var(MVAR_Is_Fool) > 0)
#define DUDE_IS_CRYPT         (map_var(MVAR_Is_Crypt) > 0)

#define set_dude_is_fool      set_map_var(MVAR_Is_Fool, 1); \
                              set_map_var(MVAR_Is_Crypt, 0)
#define set_dude_is_crypt     set_map_var(MVAR_Is_Crypt, 1); \
                              set_map_var(MVAR_Is_Fool, 0)

#define dec_fools_counter     set_map_var(MVAR_Fool_Counter, map_var(MVAR_Fool_Counter) - 1)
#define dec_crypt_counter     set_map_var(MVAR_Crypt_Counter, map_var(MVAR_Crypt_Counter) - 1)

#define FOOLS_COUNTER         map_var(MVAR_Fool_Counter)
#define CRYPT_COUNTER         map_var(MVAR_Crypt_Counter)

// Gang War
#define get_demo_gangwar_inactive   (global_var(GVAR_QUEST_DEMO_GANG_WAR) == 0)
#define get_demo_gangwar_active     (global_var(GVAR_QUEST_DEMO_GANG_WAR) == 1)
#define get_demo_gangwar_completed  (global_var(GVAR_QUEST_DEMO_GANG_WAR) == 2)

#define set_demo_gangwar_inactive   set_global_var(GVAR_QUEST_DEMO_GANG_WAR, 0)
#define set_demo_gangwar_active     set_global_var(GVAR_QUEST_DEMO_GANG_WAR, 1)
#define set_demo_gangwar_completed  set_global_var(GVAR_QUEST_DEMO_GANG_WAR, 2)

// Fix the generator
#define get_demo_fix_power_inactive (global_var(GVAR_QUEST_DEMO_FIX_POWER) == 0)
#define get_demo_fix_power_active   (global_var(GVAR_QUEST_DEMO_FIX_POWER) == 1)

// Start the Gang War
variable I_Am_A_Fool;
variable I_Am_A_Crypt;
import variable Fool_Taunt;
import variable Crypt_Taunt;
import variable Crypt_Pointer;
import variable Fool_Pointer;
procedure Start_War begin
	if (fixed_param == 1) then begin
		set_demo_gangwar_inactive;
		if (I_Am_A_Fool) then begin
			Fool_Taunt := 1;
			float_msg(self_obj, message_str(SCRIPT_JUNKDEMO, random(100, 115)), FLOAT_MSG_SEQUENTIAL);
		end
		else begin
			Crypt_Taunt := 1;
			float_msg(self_obj, message_str(SCRIPT_JUNKDEMO, random(200, 218)), FLOAT_MSG_SEQUENTIAL);
		end
		add_timer_event(self_obj, 4, 2);
	end
	else begin
		if (fixed_param == 2) then begin
			if (I_Am_A_Fool) then begin
				attack(Crypt_Pointer);
			end
			else begin
				attack(Fool_Pointer);
			end
		end
	end
end

#endif // SCRAPHEAP_H




