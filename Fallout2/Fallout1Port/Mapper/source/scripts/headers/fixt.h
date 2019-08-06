/*

	Fixt related defines

*/

#ifndef FIXT_H
#define FIXT_H

// TODO: Check if this is even necessary anymore
#define fixt_critter_healing 			if (map_first_run) then begin \
											if get_critter_stat(self_obj, STAT_max_hp) > 0 then begin \
												critter_heal(self_obj, 999); \
											end \
										end
										
/*===============================================================
	Armor equip mod is disabled for now
===============================================================*/
/*
#define fixt_critter_healing 			if local_var(12) != 1 then begin  \
											if (map_first_run) then begin \
												if metarule(22, 0) == 0 then begin \
													if get_critter_stat(self_obj, STAT_max_hp) > 0 then begin  \
														critter_heal(self_obj, 999);  \
													end  \
													if global_var(ARMOR_EQUIP_MOD) then begin  \
														if critter_inven_obj(self_obj, 0) <= 0 then begin \
															variable A;  \
															if obj_carrying_pid_obj(self_obj, PID_COMBAT_ARMOR) then begin  \
																debug_msg("Fallout Fixt - Warning: CRITTER " + obj_pid(self_obj) + " HAD ARMOR BUT EMPTY ARMOR SLOT. EQUIPPING COMBAT ARMOR...");  \
																A := obj_carrying_pid_obj(self_obj, PID_COMBAT_ARMOR);  \
															end \
															else if obj_carrying_pid_obj(self_obj, PID_METAL_ARMOR) then begin \
																debug_msg("Fallout Fixt - Warning: CRITTER " + obj_pid(self_obj) + " HAD ARMOR BUT EMPTY ARMOR SLOT. EQUIPPING METAL ARMOR..."); \
																A := obj_carrying_pid_obj(self_obj, PID_METAL_ARMOR); \
															end \
															else if obj_carrying_pid_obj(self_obj, PID_LEATHER_ARMOR) then begin \
																debug_msg("Fallout Fixt - Warning: CRITTER " + obj_pid(self_obj) + " HAD ARMOR BUT EMPTY ARMOR SLOT. EQUIPPING LEATHER ARMOR..."); \
																A := obj_carrying_pid_obj(self_obj, PID_LEATHER_ARMOR); \
															end \
															else if obj_carrying_pid_obj(self_obj, PID_LEATHER_JACKET) then begin \
																debug_msg("Fallout Fixt - Warning: CRITTER " + obj_pid(self_obj) + " HAD ARMOR BUT EMPTY ARMOR SLOT. EQUIPPING LEATHER JACKET..."); \
																A := obj_carrying_pid_obj(self_obj, PID_LEATHER_JACKET); \
															end \
															else if obj_carrying_pid_obj(self_obj, PID_PURPLE_ROBE) then begin \
																debug_msg("Fallout Fixt - Warning: CRITTER " + obj_pid(self_obj) + " HAD ARMOR BUT EMPTY ARMOR SLOT. EQUIPPING ROBES..."); \
																A := obj_carrying_pid_obj(self_obj, PID_PURPLE_ROBE); \
															end \
															rm_obj_from_inven(self_obj, A); \
															add_obj_to_inven(self_obj, A); \
															wield_obj_critter(self_obj, A); \
														end \
													end\
													set_local_var(12, 1); \
												end\
											end\
										end 
*/

/*===============================================================
	"ARMOR DESTROY ON DEATH" MOD:
===============================================================*/
#define fixt_destroy_armor 				if global_var(ARMOR_DESTROY_MOD) then begin \
											if (critter_inven_obj(self_obj, 0) > 0) then begin \
												variable slot0 := 0; \
												slot0 := critter_inven_obj(self_obj, 0); \
												rm_obj_from_inven(self_obj, slot0); \
												destroy_object(slot0); \
											end \
											else if (critter_wearing_armor(PID_LEATHER_JACKET) > 0) then begin \
												rm_obj_from_inven(self_obj, PID_LEATHER_JACKET); \
												destroy_object(PID_LEATHER_JACKET); \
											end \
											else if (critter_wearing_armor(PID_LEATHER_ARMOR) > 0) then begin \
												rm_obj_from_inven(self_obj, PID_LEATHER_ARMOR); \
												destroy_object(PID_LEATHER_ARMOR); \
											end \
											else if (critter_wearing_armor(PID_PURPLE_ROBE) > 0) then begin \
												rm_obj_from_inven(self_obj, PID_PURPLE_ROBE); \
												destroy_object(PID_PURPLE_ROBE); \
											end \
											else if (critter_wearing_armor(PID_METAL_ARMOR) > 0) then begin \
												rm_obj_from_inven(self_obj, PID_METAL_ARMOR); \
												destroy_object(PID_METAL_ARMOR); \
											end \
											else if (critter_wearing_armor(PID_COMBAT_ARMOR) > 0) then begin \
												rm_obj_from_inven(self_obj, PID_COMBAT_ARMOR); \
												destroy_object(PID_COMBAT_ARMOR); \
											end \
											else if (critter_wearing_armor(PID_BROTHERHOOD_COMBAT_ARMOR) > 0) then begin \
												rm_obj_from_inven(self_obj, PID_BROTHERHOOD_COMBAT_ARMOR); \
												destroy_object(PID_BROTHERHOOD_COMBAT_ARMOR); \
											end \
											else if (critter_wearing_armor(PID_POWERED_ARMOR) > 0) then begin \
												rm_obj_from_inven(self_obj, PID_POWERED_ARMOR); \
												destroy_object(PID_POWERED_ARMOR); \
											end \
											else if (critter_wearing_armor(PID_HARDENED_POWER_ARMOR) > 0) then begin \
												rm_obj_from_inven(self_obj, PID_HARDENED_POWER_ARMOR); \
												destroy_object(PID_HARDENED_POWER_ARMOR); \
											end \
											else if (critter_wearing_armor(PID_TESLA_ARMOR) > 0) then begin \
												rm_obj_from_inven(self_obj, PID_TESLA_ARMOR); \
												destroy_object(PID_TESLA_ARMOR); \
											end \
										end

#endif // FIXT_H
