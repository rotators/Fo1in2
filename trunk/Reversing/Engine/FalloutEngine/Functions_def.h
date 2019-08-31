/**
	X-Macro for defining engine function wrappers.

	Add one line for every function you want to call from C++ code.

	Format:
	WRAP_WATCOM_FUNCX(retType, name, argType1, argName1, ...)
	- X - number of arguments
	- retType - function return type
	- name - function name (without trailing underscore)
	- argType - type of argument
	- argName - name of argument (repeat for all of X arguments)

	NOTES: be careful not to use reserved words, including ASM instructions (push, pop, mov, div, etc.)
*/
#include "Structs.h";

// For functions that have 3 or more arguments, it is preferable to use the fastcall calling convention
// because the compiler builds the better/optimized code when calling the engine functions
WRAP_WATCOM_FFUNC4(long, _word_wrap, const char*, text, int, maxWidth, DWORD*, buf, BYTE*, count)
WRAP_WATCOM_FFUNC7(long, createWindow, const char*, winName, long, x, long, y, long, width, long, height, long, bgColorIndex, long, flags)
WRAP_WATCOM_FFUNC3(void, display_inventory, long, inventoryOffset, long, visibleOffset, long, mode)
WRAP_WATCOM_FFUNC4(void, display_target_inventory, long, inventoryOffset, long, visibleOffset, DWORD*, targetInventory, long, mode)
WRAP_WATCOM_FFUNC3(FrmFrameData*, frame_ptr, FrmHeaderData*, frm, long, frame, long, direction)
WRAP_WATCOM_FFUNC7(void, make_straight_path_func, GameObject*, objFrom, DWORD, tileFrom, DWORD, tileTo, void*, rotationPtr, DWORD*, result, long, flags, void*, func)
WRAP_WATCOM_FFUNC3(long, object_under_mouse, long, crSwitch, long, inclDude, long, elevation)
WRAP_WATCOM_FFUNC3(long, scr_get_local_var, long, sid, long, varId, long*, value)
WRAP_WATCOM_FFUNC3(long, scr_set_local_var, long, sid, long, varId, long, value)

// stdcall
WRAP_WATCOM_FUNC1(AIcap*, ai_cap, GameObject*, critter)
WRAP_WATCOM_FUNC1(Program*, allocateProgram, const char*, filePath)
WRAP_WATCOM_FUNC0(void, art_flush)
WRAP_WATCOM_FUNC1(const char*, art_get_name, long, artFID)
WRAP_WATCOM_FUNC5(long, art_id, long, artType, long, lstIndex, long, animCode, long, weaponCode, long, directionCode)
WRAP_WATCOM_FUNC3(BYTE*, art_frame_data, FrmHeaderData*, frm, long, frameNum, long, rotation)
WRAP_WATCOM_FUNC3(long, art_frame_width, FrmHeaderData*, frm, long, frameNum, long, rotation)
WRAP_WATCOM_FUNC3(long, art_frame_length, FrmHeaderData*, frm, long, frameNum, long, rotation)
WRAP_WATCOM_FUNC2(FrmHeaderData*, art_ptr_lock, long, frmId, DWORD*, lockPtr)
WRAP_WATCOM_FUNC4(BYTE*, art_ptr_lock_data, long, frmId, long, frameNum, long, rotation, DWORD*, lockPtr)
WRAP_WATCOM_FUNC4(BYTE*, art_lock, long, frmId, DWORD*, lockPtr, long*, widthOut, long*, heightOut)
WRAP_WATCOM_FUNC1(long, art_ptr_unlock, DWORD, lockId)
WRAP_WATCOM_FUNC2(long, barter_compute_value, GameObject*, source, GameObject*, target)
WRAP_WATCOM_FUNC1(DWORD, check_move, int, numTiles);
WRAP_WATCOM_FUNC1(void*, dbase_open, const char*, fileName)
WRAP_WATCOM_FUNC1(void, dbase_close, void*, dbPtr)
WRAP_WATCOM_FUNC3(long, db_freadShortCount, DbFile*, file, WORD*, dest, long, count)
WRAP_WATCOM_FUNC3(long, db_freadIntCount, DbFile*, file, DWORD*, dest, long, count)
WRAP_WATCOM_FUNC2(long, db_fwriteByte, DbFile*, file, long, value)
WRAP_WATCOM_FUNC2(long, db_fwriteInt, DbFile*, file, long, value)
WRAP_WATCOM_FUNC0(void, display_stats)
WRAP_WATCOM_FUNC1(void, dude_run, int, actionPoints)
// perform combat turn for a given critter
WRAP_WATCOM_FUNC2(long, combat_turn, GameObject*, critter, long, isDudeTurn)
WRAP_WATCOM_FUNC1(long, critter_is_dead, GameObject*, critter)
WRAP_WATCOM_FUNC1(void, EndLoad, DbFile*, file)
WRAP_WATCOM_FUNC1(long, folder_print_line, const char*, text)
WRAP_WATCOM_FUNC1(long, folder_print_seperator, const char*, text)
WRAP_WATCOM_FUNC1(long, game_get_global_var, long, globalVar)
WRAP_WATCOM_FUNC1(void, gdialogDisplayMsg, const char*, message)
WRAP_WATCOM_FUNC1(long, gmouse_3d_set_mode, long, mode)
WRAP_WATCOM_FUNC1(long, gmouse_set_cursor, long, picNum)
WRAP_WATCOM_FUNC1(Window*, GNW_find, long, winRef)
WRAP_WATCOM_FUNC2(long, intface_get_attack, DWORD*, hitMode, DWORD*, isSecondary)
WRAP_WATCOM_FUNC0(long, intface_is_item_right_hand)
// redraws the main game interface windows (useful after changing some data like active hand, etc.)
WRAP_WATCOM_FUNC0(void, intface_redraw)
WRAP_WATCOM_FUNC0(void, intface_toggle_item_state)
WRAP_WATCOM_FUNC0(void, intface_use_item)
WRAP_WATCOM_FUNC0(long, is_pc_sneak_working)
WRAP_WATCOM_FUNC1(long, item_c_curr_size, GameObject*, critter)
WRAP_WATCOM_FUNC1(long, item_caps_total, GameObject*, object)
WRAP_WATCOM_FUNC1(long, item_size, GameObject*, item)
WRAP_WATCOM_FUNC1(long, item_total_cost, GameObject*, object)
WRAP_WATCOM_FUNC1(long, item_w_anim_code, GameObject*, item)
WRAP_WATCOM_FUNC2(long, item_w_anim_weap, GameObject*, item, DWORD, hitMode)
WRAP_WATCOM_FUNC2(long, item_w_compute_ammo_cost, GameObject*, item, DWORD*, rounds)
WRAP_WATCOM_FUNC1(long, item_w_curr_ammo, GameObject*, item)
WRAP_WATCOM_FUNC2(long, item_w_damage, GameObject*, critter, long, hitMode)
WRAP_WATCOM_FUNC1(long, item_w_dam_div, GameObject*, item)
WRAP_WATCOM_FUNC1(long, item_w_dam_mult, GameObject*, item)
WRAP_WATCOM_FUNC1(long, item_w_dr_adjust, GameObject*, item)
WRAP_WATCOM_FUNC1(long, item_w_rounds, GameObject*, item)
WRAP_WATCOM_FUNC1(long, item_w_max_ammo, GameObject*, item)
WRAP_WATCOM_FUNC1(long, item_weight, GameObject*, item)
// returns light level at given tile
WRAP_WATCOM_FUNC2(long, light_get_tile, long, elevation, long, tileNum)
WRAP_WATCOM_FUNC2(long, load_frame, const char*, filename, FrmFile**, frmPtr)
WRAP_WATCOM_FUNC2(void, MapDirErase, const char*, folder, const char*, ext)
WRAP_WATCOM_FUNC2(void, mouse_get_position, long*, outX, long*, outY)
WRAP_WATCOM_FUNC0(void, mouse_show)
WRAP_WATCOM_FUNC0(void, mouse_hide)
// calculates path and returns it's length
WRAP_WATCOM_FUNC6(long, make_path_func, GameObject*, objectFrom, long, tileFrom, long, tileTo, char*, pathDataBuffer, long, arg5, void*, blockingFunc)
WRAP_WATCOM_FUNC0(long, new_obj_id)
// calculates bounding box (rectangle) for a given object
WRAP_WATCOM_FUNC2(void, obj_bound, GameObject*, object, BoundRect*, boundRect)
WRAP_WATCOM_FUNC2(long, obj_erase_object, GameObject*, object, BoundRect*, boundRect)
WRAP_WATCOM_FUNC0(GameObject*, obj_find_first)
WRAP_WATCOM_FUNC0(GameObject*, obj_find_next)
WRAP_WATCOM_FUNC2(long, obj_pid_new, GameObject*, object, long, pid)
// checks/unjams jammed locks
WRAP_WATCOM_FUNC1(long, obj_lock_is_jammed, GameObject*, object)
WRAP_WATCOM_FUNC1(void, obj_unjam_lock, GameObject*, object)
WRAP_WATCOM_FUNC1(void, pc_flag_on, long, flag)
WRAP_WATCOM_FUNC2(void, perk_add_effect, GameObject*, critter, long, perkId)
WRAP_WATCOM_FUNC2(long, perk_can_add, GameObject*, critter, long, perkId)
//WRAP_WATCOM_FUNC2(void, perk_remove_effect,  GameObject*, critter, long, perkId)
WRAP_WATCOM_FUNC6(long, pick_death, GameObject*, attacker, GameObject*, target, GameObject*, weapon, long, amount, long, anim, long, hitFromBack)
WRAP_WATCOM_FUNC0(void, process_bk)
WRAP_WATCOM_FUNC0(void, proto_dude_update_gender)
WRAP_WATCOM_FUNC2(long*, queue_find_first, GameObject*, object, long, qType)
WRAP_WATCOM_FUNC2(long*, queue_find_next, GameObject*, object, long, qType)
WRAP_WATCOM_FUNC3(long, register_object_animate, GameObject*, object, long, anim, long, delay)
WRAP_WATCOM_FUNC3(long, register_object_animate_and_hide, GameObject*, object, long, anim, long, delay)
// WRAP_WATCOM_FUNC3(long, register_object_animate_and_move_straight_, GameObject*, object;
// WRAP_WATCOM_FUNC3(long, register_object_animate_forever_, GameObject*, object;
// WRAP_WATCOM_FUNC3(long, register_object_animate_reverse_, GameObject*, object;
WRAP_WATCOM_FUNC3(long, register_object_change_fid, GameObject*, object, long, artFid, long, delay)
// WRAP_WATCOM_FUNC3(long, register_object_check_falling_, GameObject*, object;
WRAP_WATCOM_FUNC1(long, register_object_dec_rotation, GameObject*, object)
WRAP_WATCOM_FUNC1(long, register_object_erase, GameObject*, object)
WRAP_WATCOM_FUNC3(long, register_object_funset, GameObject*, object, long, action, long, delay)
WRAP_WATCOM_FUNC1(long, register_object_inc_rotation, GameObject*, object)
WRAP_WATCOM_FUNC3(long, register_object_light, GameObject*, object, long, lightRadius, long, delay)
// WRAP_WATCOM_FUNC3(long, register_object_move_on_stairs_, GameObject*, object;
// WRAP_WATCOM_FUNC3(long, register_object_move_straight_to_tile_, GameObject*, object;
// WRAP_WATCOM_FUNC3(long, register_object_move_to_object_, GameObject*, object;
 WRAP_WATCOM_FUNC5(int, register_object_move_to_tile, GameObject*, object, DWORD, dstTile, int, prop, int, unknown, int, unknown2)
// WRAP_WATCOM_FUNC3(long, register_object_must_call_, GameObject*, object;
WRAP_WATCOM_FUNC1(long, register_object_must_erase, GameObject*, object)
// WRAP_WATCOM_FUNC3(long, register_object_outline_, GameObject*, object;
// WRAP_WATCOM_FUNC3(long, register_object_play_sfx_, GameObject*, object;
// WRAP_WATCOM_FUNC3(long, register_object_run_to_object_, GameObject*, object;
// WRAP_WATCOM_FUNC3(long, register_object_run_to_tile_, GameObject*, object;
WRAP_WATCOM_FUNC1(void, register_begin, int, unknown);
WRAP_WATCOM_FUNC0(void, register_end);
WRAP_WATCOM_FUNC3(long, register_object_take_out, GameObject*, object, long, holdFrameId, long, nothing)
WRAP_WATCOM_FUNC3(long, register_object_turn_towards, GameObject*, object, long, tileNum, long, nothing)
WRAP_WATCOM_FUNC2(long, skill_dec_point_force, GameObject*, critter, long, skill)
WRAP_WATCOM_FUNC2(long, skill_inc_point_force, GameObject*, critter, long, skill)
WRAP_WATCOM_FUNC1(long, skill_is_tagged, long, skill)
WRAP_WATCOM_FUNC2(long, stat_get_base_direct, GameObject*, critter, long, statID)
WRAP_WATCOM_FUNC2(long, stat_get_bonus, GameObject*, critter, long, statID)
WRAP_WATCOM_FUNC3(long, stat_set_bonus, GameObject*, critter, long, statID, long, amount)
// adds experience points to PC
WRAP_WATCOM_FUNC1(void, stat_pc_add_experience, long, amount)
WRAP_WATCOM_FUNC1(long, text_font, long, fontNum)
// redraws the whole screen
WRAP_WATCOM_FUNC0(void, tile_refresh_display)
// redraws the given rectangle on screen
WRAP_WATCOM_FUNC2(void, tile_refresh_rect, BoundRect*, boundRect, long, elevation)
WRAP_WATCOM_FUNC1(long, trait_level, long, traitID)
WRAP_WATCOM_FUNC6(DWORD, win_add, long, x, long, y, long, width, long, height, long, bgColorIndex, long, flags)
WRAP_WATCOM_FUNC1(void, win_show, DWORD, winRef)
WRAP_WATCOM_FUNC1(void, win_hide, DWORD, winRef)
WRAP_WATCOM_FUNC1(BYTE*, win_get_buf, DWORD, winRef)
WRAP_WATCOM_FUNC1(void, win_draw, DWORD, winRef)
WRAP_WATCOM_FUNC1(void, win_delete, DWORD, winRef)
WRAP_WATCOM_FUNC0(long, windowWidth)
WRAP_WATCOM_FUNC1(void, wmCarUseGas, long, gasAmount)
WRAP_WATCOM_FUNC0(void, wmPartyWalkingStep)
WRAP_WATCOM_FUNC2(DbFile*, xfopen, const char*, fileName, const char*, flags)
WRAP_WATCOM_FUNC3(long, xfseek, DbFile*, file, long, fOffset, long, origin)
