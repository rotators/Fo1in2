/*
* sfall
* Copyright (C) 2008-2016 The sfall team
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "FunctionOffsets.h"

#include "Functions.h"

namespace fo
{
namespace func
{

// Fallout2.exe was compiled using WATCOM compiler, which uses Watcom register calling convention.
// In this convention, up to 4 arguments are passed via registers in this order: EAX, EDX, EBX, ECX.

#define WRAP_WATCOM_CALL0(offs) \
	__asm call fo::funcoffs::offs

#define WRAP_WATCOM_CALL1(offs, arg1) \
	__asm mov eax, arg1				\
	WRAP_WATCOM_CALL0(offs)

#define WRAP_WATCOM_CALL2(offs, arg1, arg2) \
	__asm mov edx, arg2				\
	WRAP_WATCOM_CALL1(offs, arg1)

#define WRAP_WATCOM_CALL3(offs, arg1, arg2, arg3) \
	__asm mov ebx, arg3				\
	WRAP_WATCOM_CALL2(offs, arg1, arg2)

#define WRAP_WATCOM_CALL4(offs, arg1, arg2, arg3, arg4) \
	__asm mov ecx, arg4				\
	WRAP_WATCOM_CALL3(offs, arg1, arg2, arg3)

#define WRAP_WATCOM_CALL5(offs, arg1, arg2, arg3, arg4, arg5) \
	__asm push arg5				\
	WRAP_WATCOM_CALL4(offs, arg1, arg2, arg3, arg4)

#define WRAP_WATCOM_CALL6(offs, arg1, arg2, arg3, arg4, arg5, arg6) \
	__asm push arg6				\
	WRAP_WATCOM_CALL5(offs, arg1, arg2, arg3, arg4, arg5)

#define WRAP_WATCOM_CALL7(offs, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
	__asm push arg7				\
	WRAP_WATCOM_CALL6(offs, arg1, arg2, arg3, arg4, arg5, arg6)

// defines wrappers for __fastcall
#define WRAP_WATCOM_FCALL1(offs, arg1) \
	__asm mov eax, ecx				\
	WRAP_WATCOM_CALL0(offs)

#define WRAP_WATCOM_FCALL2(offs, arg1, arg2) \
	WRAP_WATCOM_FCALL1(offs, arg1)

#define WRAP_WATCOM_FCALL3(offs, arg1, arg2, arg3) \
	__asm mov ebx, arg3				\
	WRAP_WATCOM_FCALL1(offs, arg1)

#define WRAP_WATCOM_FCALL4(offs, arg1, arg2, arg3, arg4) \
	__asm mov eax, ecx				\
	__asm mov ebx, arg3				\
	__asm mov ecx, arg4				\
	WRAP_WATCOM_CALL0(offs)

#define WRAP_WATCOM_FCALL5(offs, arg1, arg2, arg3, arg4, arg5) \
	__asm push arg5				\
	WRAP_WATCOM_FCALL4(offs, arg1, arg2, arg3, arg4)

#define WRAP_WATCOM_FCALL6(offs, arg1, arg2, arg3, arg4, arg5, arg6) \
	__asm push arg6				\
	WRAP_WATCOM_FCALL5(offs, arg1, arg2, arg3, arg4, arg5)

#define WRAP_WATCOM_FCALL7(offs, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
	__asm push arg7				\
	WRAP_WATCOM_FCALL6(offs, arg1, arg2, arg3, arg4, arg5, arg6)


bool __stdcall art_exists(long artFid) {
	WRAP_WATCOM_CALL1(art_exists_, artFid)
}

// Returns the name of the critter
const char* __stdcall critter_name(GameObject* critter) {
	WRAP_WATCOM_CALL1(critter_name_, critter)
}

// Change the name of playable character
void critter_pc_set_name(const char* newName) {
	WRAP_WATCOM_CALL1(critter_pc_set_name_, newName)
}

bool __stdcall db_access(const char* fileName) {
	WRAP_WATCOM_CALL1(db_access_, fileName)
}

long __stdcall db_fclose(DbFile* file) {
	WRAP_WATCOM_CALL1(db_fclose_, file)
}

DbFile* __stdcall db_fopen(const char* path, const char* mode) {
	WRAP_WATCOM_CALL2(db_fopen_, path, mode)
}

long __stdcall db_fgetc(DbFile* file) {
	WRAP_WATCOM_CALL1(db_fgetc_, file)
}

char* __stdcall db_fgets(char* buf, long max_count, DbFile* file) {
	WRAP_WATCOM_CALL3(db_fgets_, buf, max_count, file)
}

long __stdcall db_fread(void* buf, long elsize, long count, DbFile* file) {
	WRAP_WATCOM_CALL4(db_fread_, buf, elsize, count, file)
}

long __stdcall db_fseek(DbFile* file, long pos, long origin) {
	WRAP_WATCOM_CALL3(db_fseek_, file, pos, origin)
}

long __stdcall db_freadByte(DbFile* file, BYTE* _out) {
	WRAP_WATCOM_CALL2(db_freadByte_, file, _out)
}

long __stdcall db_freadByteCount(DbFile* file, BYTE* cptr, long count) {
	WRAP_WATCOM_CALL3(db_freadByteCount_, file, cptr, count)
}

long __stdcall db_freadShort(DbFile* file, WORD* _out) {
	WRAP_WATCOM_CALL2(db_freadShort_, file, _out)
}

long __stdcall db_freadInt(DbFile* file, DWORD* _out) {
	WRAP_WATCOM_CALL2(db_freadInt_, file, _out)
}

void __stdcall db_free_file_list(char* * *fileList, DWORD arg2) {
	WRAP_WATCOM_CALL2(db_free_file_list_, fileList, arg2)
}

long __stdcall db_fwriteByteCount(DbFile* file, const BYTE* cptr, long count) {
	WRAP_WATCOM_CALL3(db_fwriteByteCount_, file, cptr, count)
}

long __stdcall db_get_file_list(const char* searchMask, char* * *fileList) {
	WRAP_WATCOM_CALL2(db_get_file_list_, searchMask, fileList)
}

long __stdcall db_init(const char* path_dat, const char* path_patches) {
	WRAP_WATCOM_CALL3(db_init_, path_dat, 0, path_patches)
}

// Check fallout file and get file size (result 0 - file exists)
long __stdcall db_dir_entry(const char *fileName, DWORD *sizeOut) {
	WRAP_WATCOM_CALL2(db_dir_entry_, fileName, sizeOut)
}

// prints message to debug.log file
void __declspec(naked) debug_printf(const char* fmt, ...) {
	__asm jmp fo::funcoffs::debug_printf_
}

// Displays message in main UI console window
void display_print(const char* msg) {
	WRAP_WATCOM_CALL1(display_print_, msg)
}

void executeProcedure(Program* sptr, long procNum) {
	WRAP_WATCOM_CALL2(executeProcedure_, sptr, procNum)
}

long __stdcall get_input() {
	WRAP_WATCOM_CALL0(get_input_)
}

// returns the name of current procedure by program pointer
const char* __stdcall findCurrentProc(Program* program) {
	WRAP_WATCOM_CALL1(findCurrentProc_, program)
}

const char* _stdcall getmsg(const MessageList* fileAddr, MessageNode* result, long messageId) {
	WRAP_WATCOM_CALL3(getmsg_, fileAddr, result, messageId)
}

void __stdcall gsound_play_sfx_file(const char* name) {
	WRAP_WATCOM_CALL1(gsound_play_sfx_file_, name)
}

long __stdcall interpret(Program* program, long arg2) {
	WRAP_WATCOM_CALL2(interpret_, program, arg2)
}

long __stdcall interpretFindProcedure(Program* scriptPtr, const char* procName) {
	WRAP_WATCOM_CALL2(interpretFindProcedure_, scriptPtr, procName)
}

// pops value type from Data stack (must be followed by InterpretPopLong)
DWORD __stdcall interpretPopShort(Program* scriptPtr) {
	WRAP_WATCOM_CALL1(interpretPopShort_, scriptPtr)
}

// pops value from Data stack (must be preceded by InterpretPopShort)
DWORD __stdcall interpretPopLong(Program* scriptPtr) {
	WRAP_WATCOM_CALL1(interpretPopLong_, scriptPtr)
}

// pushes value to Data stack (must be followed by InterpretPushShort)
void __stdcall interpretPushLong(Program* scriptPtr, DWORD val) {
	WRAP_WATCOM_CALL2(interpretPushLong_, scriptPtr, val)
}

// pushes value type to Data stack (must be preceded by InterpretPushLong)
void __stdcall interpretPushShort(Program* scriptPtr, DWORD valType) {
	WRAP_WATCOM_CALL2(interpretPushShort_, scriptPtr, valType)
}

DWORD __stdcall interpretAddString(Program* scriptPtr, const char* strval) {
	WRAP_WATCOM_CALL2(interpretAddString_, scriptPtr, strval)
}

const char* __stdcall interpretGetString(Program* scriptPtr, DWORD dataType, DWORD strId) {
	WRAP_WATCOM_CALL3(interpretGetString_, scriptPtr, dataType, strId)
}

// prints scripting error in debug.log and stops current script execution by performing longjmp
// USE WITH CAUTION
void __declspec(naked) interpretError(const char* fmt, ...) {
	__asm jmp fo::funcoffs::interpretError_
}

long _stdcall isPartyMember(GameObject* obj) {
	WRAP_WATCOM_CALL1(isPartyMember_, obj)
}

long __stdcall item_get_type(GameObject* item) {
	WRAP_WATCOM_CALL1(item_get_type_, item)
}

long __stdcall item_m_dec_charges(GameObject* item) {
	WRAP_WATCOM_CALL1(item_m_dec_charges_, item) //Returns -1 if the item has no charges
}

GameObject* __stdcall inven_pid_is_carried_ptr(GameObject* invenObj, long pid) {
	WRAP_WATCOM_CALL2(inven_pid_is_carried_ptr_, invenObj, pid)
}

// critter worn item (armor)
GameObject* __stdcall inven_worn(GameObject* critter) {
	WRAP_WATCOM_CALL1(inven_worn_, critter)
}

// item in critter's left hand slot
GameObject* __stdcall inven_left_hand(GameObject* critter) {
	WRAP_WATCOM_CALL1(inven_left_hand_, critter)
}

// item in critter's right hand slot
GameObject* __stdcall inven_right_hand(GameObject* critter) {
	WRAP_WATCOM_CALL1(inven_right_hand_, critter)
}

Program* __stdcall loadProgram(const char* fileName) {
	WRAP_WATCOM_CALL1(loadProgram_, fileName)
}

void* __stdcall mem_realloc(void* lpmem, DWORD msize) {
	WRAP_WATCOM_CALL2(mem_realloc_, lpmem, msize)
}

long __stdcall message_add(MessageList* file, MessageNode* msg) {
	WRAP_WATCOM_CALL2(message_add_, file, msg)
}

long __stdcall message_filter(MessageList* file) {
	WRAP_WATCOM_CALL1(message_filter_, file)
}

long __stdcall message_make_path(char* outpath, char* path) {
	WRAP_WATCOM_CALL2(message_make_path_, outpath, path)
}

long __stdcall message_search(const MessageList* file, MessageNode* msg) {
	WRAP_WATCOM_CALL2(message_search_, file, msg)
}

long __stdcall message_load(MessageList *msgList, const char *msgFilePath) {
	WRAP_WATCOM_CALL2(message_load_, msgList, msgFilePath)
}

long __stdcall message_exit(MessageList *msgList) {
	WRAP_WATCOM_CALL1(message_exit_, msgList)
}

GameObject* __fastcall obj_blocking_at_wrapper(GameObject* obj, DWORD tile, DWORD elevation, void* func) {
	__asm {
		mov  eax, ecx;
		mov  ebx, elevation;
		call func;
	}
}

GameObject* __stdcall obj_find_first_at_tile(long elevation, long tileNum) {
	WRAP_WATCOM_CALL2(obj_find_first_at_tile_, elevation, tileNum)
}

GameObject* __stdcall obj_find_next_at_tile() {
	WRAP_WATCOM_CALL0(obj_find_next_at_tile_)
}

long _stdcall partyMemberGetCurLevel(GameObject* obj) {
	WRAP_WATCOM_CALL1(partyMemberGetCurLevel_, obj)
}

long _stdcall perk_level(GameObject* critter, long perkId) {
	WRAP_WATCOM_CALL2(perk_level_, critter, perkId)
}

long proto_ptr(long pid, Proto* *ptrPtr) {
	WRAP_WATCOM_CALL2(proto_ptr_, pid, ptrPtr)
}

DWORD* __stdcall runProgram(Program* progPtr) {
	WRAP_WATCOM_CALL1(runProgram_, progPtr)
}

ScriptInstance* __stdcall scr_find_first_at(long elevation) {
	WRAP_WATCOM_CALL1(scr_find_first_at_, elevation)
}

ScriptInstance* __stdcall scr_find_next_at() {
	WRAP_WATCOM_CALL0(scr_find_next_at_)
}

GameObject* __stdcall scr_find_obj_from_program(Program* program) {
	WRAP_WATCOM_CALL1(scr_find_obj_from_program_, program)
}

// Saves pointer to script object into scriptPtr using scriptID.
// Returns 0 on success, -1 on failure.
long __stdcall scr_ptr(long scriptId, ScriptInstance** scriptPtr) {
	WRAP_WATCOM_CALL2(scr_ptr_, scriptId, scriptPtr)
}

void skill_get_tags(long* result, long num) {
	WRAP_WATCOM_CALL2(skill_get_tags_, result, num)
}

void skill_set_tags(long* tags, long num) {
	WRAP_WATCOM_CALL2(skill_set_tags_, tags, num)
}

long __stdcall stat_level(GameObject* critter, long statId) {
	WRAP_WATCOM_CALL2(stat_level_, critter, statId)
}

long __stdcall win_register_button(DWORD winRef, long xPos, long yPos, long width, long height, long hoverOn, long hoverOff, long buttonDown, long buttonUp, BYTE* pictureUp, BYTE* pictureDown, long arg12, long buttonType) {
	__asm {
		push buttonType
		push arg12
		push pictureDown
		push pictureUp
		push buttonUp
		push buttonDown
		push hoverOff
		push hoverOn
		push height
		mov ecx, width
		mov ebx, yPos
		mov edx, xPos
		mov eax, winRef
		call fo::funcoffs::win_register_button_
	}
}

void __stdcall DialogOut(const char* text) {
	__asm {
		push 1;          // flag
		xor  eax, eax;
		push eax;        // ColorMsg
		push eax;        // DisplayMsg
		mov  al, byte ptr ds:[0x6AB718];
		push eax;        // ColorIndex
		push 116;        // y
		mov  ecx, 192;   // x
		mov  eax, text;  // DisplayText
		xor  ebx, ebx;   // ?
		xor  edx, edx;   // ?
		call fo::funcoffs::dialog_out_;
	}
}

void __fastcall DrawWinLine(int winRef, DWORD startXPos, DWORD endXPos, DWORD startYPos, DWORD endYPos, BYTE colour) {
	__asm {
		xor  eax, eax;
		mov  al, colour;
		push eax;
		push endYPos;
		mov  eax, ecx; // winRef
		mov  ecx, endXPos;
		mov  ebx, startYPos;
		//mov  edx, xStartPos;
		call fo::funcoffs::win_line_;
	}
}

// draws an image to the buffer without scaling and with transparency display toggle
void __fastcall windowDisplayBuf(long x, long width, long y, long height, void* data, long noTrans) {
	__asm {
		push height;
		push edx;       // from_width
		push y;
		mov  eax, data; // from
		mov  ebx, fo::funcoffs::windowDisplayTransBuf_;
		cmp  noTrans, 0;
		cmovnz ebx, fo::funcoffs::windowDisplayBuf_;
		call ebx; // *data<eax>, from_width<edx>, unused<ebx>, X<ecx>, Y, width, height
	}
}

// draws an image in the window and scales it to fit the window
void __fastcall displayInWindow(long w_here, long width, long height, void* data) {
	__asm {
		mov  ebx, height;
		mov  eax, data;
		call fo::funcoffs::displayInWindow_; // *data<eax>, width<edx>, height<ebx>, where<ecx>
	}
}

void __fastcall trans_cscale(long i_width, long i_height, long s_width, long s_height, long xy_shift, long w_width, void* data) {
	__asm {
		push w_width;
		push s_height;
		push s_width;
		mov  ebx, edx; // i_height
		mov  edx, ecx; // i_width
		call fo::funcoffs::windowGetBuffer_;
		add  eax, xy_shift;
		push eax;      // to_buff
		mov  eax, data;
		call fo::funcoffs::trans_cscale_; // *from_buff<eax>, i_width<edx>, i_height<ebx>, i_width2<ecx>, to_buff, width, height, to_width
	}
}


#define WRAP_WATCOM_FUNC0(retType, name) \
	retType __stdcall name() { \
		WRAP_WATCOM_CALL0(name##_) \
	}

#define WRAP_WATCOM_FUNC1(retType, name, arg1t, arg1) \
	retType __stdcall name(arg1t arg1) { \
		WRAP_WATCOM_CALL1(name##_, arg1) \
	}

#define WRAP_WATCOM_FUNC2(retType, name, arg1t, arg1, arg2t, arg2) \
	retType __stdcall name(arg1t arg1, arg2t arg2) { \
		WRAP_WATCOM_CALL2(name##_, arg1, arg2) \
	}

#define WRAP_WATCOM_FUNC3(retType, name, arg1t, arg1, arg2t, arg2, arg3t, arg3) \
	retType __stdcall name(arg1t arg1, arg2t arg2, arg3t arg3) { \
		WRAP_WATCOM_CALL3(name##_, arg1, arg2, arg3) \
	}

#define WRAP_WATCOM_FUNC4(retType, name, arg1t, arg1, arg2t, arg2, arg3t, arg3, arg4t, arg4) \
	retType __stdcall name(arg1t arg1, arg2t arg2, arg3t arg3, arg4t arg4) { \
		WRAP_WATCOM_CALL4(name##_, arg1, arg2, arg3, arg4) \
	}

#define WRAP_WATCOM_FUNC5(retType, name, arg1t, arg1, arg2t, arg2, arg3t, arg3, arg4t, arg4, arg5t, arg5) \
	retType __stdcall name(arg1t arg1, arg2t arg2, arg3t arg3, arg4t arg4, arg5t arg5) { \
		WRAP_WATCOM_CALL5(name##_, arg1, arg2, arg3, arg4, arg5) \
	}

#define WRAP_WATCOM_FUNC6(retType, name, arg1t, arg1, arg2t, arg2, arg3t, arg3, arg4t, arg4, arg5t, arg5, arg6t, arg6) \
	retType __stdcall name(arg1t arg1, arg2t arg2, arg3t arg3, arg4t arg4, arg5t arg5, arg6t arg6) { \
		WRAP_WATCOM_CALL6(name##_, arg1, arg2, arg3, arg4, arg5, arg6) \
	}


#define WRAP_WATCOM_FFUNC1(retType, name, arg1t, arg1) \
	retType __fastcall name(arg1t arg1) { \
		WRAP_WATCOM_FCALL1(name##_, arg1) \
	}

#define WRAP_WATCOM_FFUNC2(retType, name, arg1t, arg1, arg2t, arg2) \
	retType __fastcall name(arg1t arg1, arg2t arg2) { \
		WRAP_WATCOM_FCALL2(name##_, arg1, arg2) \
	}

#define WRAP_WATCOM_FFUNC3(retType, name, arg1t, arg1, arg2t, arg2, arg3t, arg3) \
	retType __fastcall name(arg1t arg1, arg2t arg2, arg3t arg3) { \
		WRAP_WATCOM_FCALL3(name##_, arg1, arg2, arg3) \
	}

#define WRAP_WATCOM_FFUNC4(retType, name, arg1t, arg1, arg2t, arg2, arg3t, arg3, arg4t, arg4) \
	retType __fastcall name(arg1t arg1, arg2t arg2, arg3t arg3, arg4t arg4) { \
		WRAP_WATCOM_FCALL4(name##_, arg1, arg2, arg3, arg4) \
	}

#define WRAP_WATCOM_FFUNC5(retType, name, arg1t, arg1, arg2t, arg2, arg3t, arg3, arg4t, arg4, arg5t, arg5) \
	retType __fastcall name(arg1t arg1, arg2t arg2, arg3t arg3, arg4t arg4, arg5t arg5) { \
		WRAP_WATCOM_FCALL5(name##_, arg1, arg2, arg3, arg4, arg5) \
	}

#define WRAP_WATCOM_FFUNC6(retType, name, arg1t, arg1, arg2t, arg2, arg3t, arg3, arg4t, arg4, arg5t, arg5, arg6t, arg6) \
	retType __fastcall name(arg1t arg1, arg2t arg2, arg3t arg3, arg4t arg4, arg5t arg5, arg6t arg6) { \
		WRAP_WATCOM_FCALL6(name##_, arg1, arg2, arg3, arg4, arg5, arg6) \
	}

#define WRAP_WATCOM_FFUNC7(retType, name, arg1t, arg1, arg2t, arg2, arg3t, arg3, arg4t, arg4, arg5t, arg5, arg6t, arg6, arg7t, arg7) \
	retType __fastcall name(arg1t arg1, arg2t arg2, arg3t arg3, arg4t arg4, arg5t arg5, arg6t arg6, arg7t arg7) { \
		WRAP_WATCOM_FCALL7(name##_, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
	}

#include "Functions_def.h"

}
}
