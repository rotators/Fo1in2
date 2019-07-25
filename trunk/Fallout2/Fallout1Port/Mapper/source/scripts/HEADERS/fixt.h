/*

	Fixt related defines

*/

#ifndef FIXT_H
#define FIXT_H

#define fixt_critter_healing 			if local_var(12) != 1 then begin /* Fallout Fixt lvar12 - this code block heals critter to full HP one time (first time player enters the map) to make sure they always start with full HP.*/ \
											if (map_first_run) then begin /* Fallout Fixt lvar12 - first visit to map?*/ \
												if metarule(22, 0) == 0 then begin /* Fallout Fixt lvar12 - Not currently loading a save?*/ \
													if get_critter_stat(self_obj, STAT_max_hp) > 0 then begin  \
														critter_heal(self_obj, 999);  \
													end  \
													if global_var(ARMOR_EQUIP_MOD) then begin  \
														if critter_inven_obj(self_obj, 0) <= 0 then begin \
															/* Equip held armor if not currently wearing any.*/ \
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
													set_local_var(12, 1);\
												end\
											end\
										end
								
#endif // FIXT_H
