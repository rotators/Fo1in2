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

#include <cassert>

#include "Functions.h"
#include "FunctionOffsets.h"
#include "Structs.h"
#include "Variables.h"
#include "VariableOffsets.h"

#include "EngineUtils.h"

// TODO: split these functions into several files
namespace fo
{

static MessageNode messageBuf;

const char* _stdcall GetMessageStr(const MessageList* fileAddr, long messageId) {
	return fo::func::getmsg(fileAddr, &messageBuf, messageId);
}

const char* _stdcall MessageSearch(const MessageList* fileAddr, long messageId) {
	messageBuf.number = messageId;
	if (fo::func::message_search(fileAddr, &messageBuf) == 1) {
		return messageBuf.message;
	}
	return nullptr;
}

long AnimCodeByWeapon(GameObject* weapon) {
	if (weapon != nullptr) {
		Proto* proto = GetProto(weapon->protoId);
		if (proto != nullptr && proto->item.type == item_type_weapon) {
			return proto->item.weapon.animationCode;
		}
	}
	return 0;
}

Proto* GetProto(long pid) {
	Proto* protoPtr;
	if (fo::func::proto_ptr(pid, &protoPtr) != -1) {
		return protoPtr;
	}
	return nullptr;
}

bool CritterCopyProto(long pid, long* &proto_dst) {
	fo::Proto* protoPtr;
	if (fo::func::proto_ptr(pid, &protoPtr) == -1) return false;
	/*if (!proto_dst)*/ proto_dst = new long[104];
	memcpy(proto_dst, protoPtr, 416);
	return true;
}

void SkillGetTags(long* result, long num) {
	if (num > 4) {
		num = 4;
	}
	fo::func::skill_get_tags(result, num);
}

void SkillSetTags(long* tags, long num) {
	if (num > 4) {
		num = 4;
	}
	fo::func::skill_set_tags(tags, num);
}

long __fastcall GetItemType(GameObject* item) {
	return fo::func::item_get_type(item);
}

__declspec(noinline) GameObject* GetItemPtrSlot(GameObject* critter, InvenType slot) {
	GameObject* itemPtr = nullptr;
	switch (slot) {
		case fo::INVEN_TYPE_LEFT_HAND:
			itemPtr = fo::func::inven_left_hand(critter);
			break;
		case fo::INVEN_TYPE_RIGHT_HAND:
			itemPtr = fo::func::inven_right_hand(critter);
			break;
		case fo::INVEN_TYPE_WORN:
			itemPtr = fo::func::inven_worn(critter);
			break;
	}
	return itemPtr;
}

long& GetActiveItemMode() {
	return fo::var::itemButtonItems[fo::var::itemCurrentItem].mode;
}

GameObject* GetActiveItem() {
	return fo::var::itemButtonItems[fo::var::itemCurrentItem].item;
}

long GetCurrentAttackMode() {
	long hitMode = -1;
	if (fo::var::interfaceWindow != -1) {
		long activeHand = fo::var::itemCurrentItem; // 0 - left, 1 - right
		switch (fo::var::itemButtonItems[activeHand].mode) {
		case 1:
		case 2: // 2 - called shot
			hitMode = fo::var::itemButtonItems[activeHand].primaryAttack;
			break;
		case 3:
		case 4: // 4 - called shot
			hitMode = fo::var::itemButtonItems[activeHand].secondaryAttack;
			break; 
		case 5: // reload mode
			hitMode = fo::ATKTYPE_LWEAPON_RELOAD + activeHand;
		}
	}
	return hitMode;
}

bool HeroIsFemale() {
	return (fo::func::stat_level(fo::var::obj_dude, fo::Stat::STAT_gender) == fo::Gender::GENDER_FEMALE);
}

long CheckAddictByPid(fo::GameObject* critter, long pid) {
	__asm {
		mov  eax, pid;
		mov  esi, critter;
		call fo::funcoffs::item_d_check_addict_;
	}
	/* keyword 'return' is not needed, the compiler will do everything correctly */
}

void ToggleNpcFlag(fo::GameObject* npc, long flag, bool set) {
	Proto* protoPtr;
	if (fo::func::proto_ptr(npc->protoId, &protoPtr) != -1) {
		long bit = (1 << flag);
		if (set) {
			protoPtr->critter.critterFlags |= bit;
		} else {
			protoPtr->critter.critterFlags &= ~bit;
		}
	}
}

// Returns the number of party members in the existing table (begins from 1)
long IsPartyMemberByPid(long pid) {
	size_t patryCount = fo::var::partyMemberMaxCount;
	if (patryCount) {
		DWORD* memberPids = fo::var::partyMemberPidList; // pids from party.txt
		for (size_t i = 0; i < patryCount; i++) {
			if (memberPids[i] == pid) return i + 1;
		}
	}
	return 0;
}

bool IsPartyMember(fo::GameObject* critter) {
	if (critter->id < PLAYER_ID) return false;
	return (IsPartyMemberByPid(critter->protoId) > 0);
}

// Returns the number of local variables of the object script
long GetScriptLocalVars(long sid) {
	fo::ScriptInstance* script = nullptr;
	fo::func::scr_ptr(sid, &script);
	return (script) ? script->numLocalVars : 0;
}

//---------------------------------------------------------
//print text to surface
void PrintText(char *DisplayText, BYTE ColourIndex, DWORD Xpos, DWORD Ypos, DWORD TxtWidth, DWORD ToWidth, BYTE *ToSurface) {
	DWORD posOffset = Ypos * ToWidth + Xpos;
	__asm {
		xor  eax, eax;
		mov  al, ColourIndex;
		push eax;
		mov  edx, DisplayText;
		mov  ebx, TxtWidth;
		mov  ecx, ToWidth;
		mov  eax, ToSurface;
		add  eax, posOffset;
		call dword ptr ds:[FO_VAR_text_to_buf];
	}
}

//---------------------------------------------------------
//gets the height of the currently selected font
DWORD GetTextHeight() {
	DWORD TxtHeight;
	__asm {
		call dword ptr ds:[FO_VAR_text_height]; //get text height
		mov  TxtHeight, eax;
	}
	return TxtHeight;
}

//---------------------------------------------------------
//gets the length of a string using the currently selected font
DWORD GetTextWidth(char *TextMsg) {
	DWORD TxtWidth;
	__asm {
		mov  eax, TextMsg;
		call dword ptr ds:[FO_VAR_text_width]; //get text width
		mov  TxtWidth, eax;
	}
	return TxtWidth;
}

//---------------------------------------------------------
//get width of Char for current font
DWORD GetCharWidth(char CharVal) {
	DWORD charWidth;
	__asm {
		mov  al, CharVal;
		call dword ptr ds:[FO_VAR_text_char_width];
		mov  charWidth, eax;
	}
	return charWidth;
}

//---------------------------------------------------------
//get maximum string length for current font - if all characters were maximum width
DWORD GetMaxTextWidth(char *TextMsg) {
	DWORD msgWidth;
	__asm {
		mov  eax, TextMsg;
		call dword ptr ds:[FO_VAR_text_mono_width];
		mov  msgWidth, eax;
	}
	return msgWidth;
}

//---------------------------------------------------------
//get number of pixels between characters for current font
DWORD GetCharGapWidth() {
	DWORD gapWidth;
	__asm {
		call dword ptr ds:[FO_VAR_text_spacing];
		mov  gapWidth, eax;
	}
	return gapWidth;
}

//---------------------------------------------------------
//get maximum character width for current font
DWORD GetMaxCharWidth() {
	DWORD charWidth = 0;
	__asm {
		call dword ptr ds:[FO_VAR_text_max];
		mov  charWidth, eax;
	}
	return charWidth;
}

void RedrawObject(GameObject* obj) {
	BoundRect rect;
	func::obj_bound(obj, &rect);
	func::tile_refresh_rect(&rect, obj->elevation);
}

/////////////////////////////////////////////////////////////////UNLISTED FRM FUNCTIONS////////////////////////////////////////////////////////////////////////

static bool LoadFrmHeader(UnlistedFrm *frmHeader, fo::DbFile* frmStream) {
	if (fo::func::db_freadInt(frmStream, &frmHeader->version) == -1)
		return false;
	else if (fo::func::db_freadShort(frmStream, &frmHeader->FPS) == -1)
		return false;
	else if (fo::func::db_freadShort(frmStream, &frmHeader->actionFrame) == -1)
		return false;
	else if (fo::func::db_freadShort(frmStream, &frmHeader->numFrames) == -1)
		return false;
	else if (fo::func::db_freadShortCount(frmStream, frmHeader->xCentreShift, 6) == -1)
		return false;
	else if (fo::func::db_freadShortCount(frmStream, frmHeader->yCentreShift, 6) == -1)
		return false;
	else if (fo::func::db_freadIntCount(frmStream, frmHeader->oriOffset, 6) == -1)
		return false;
	else if (fo::func::db_freadInt(frmStream, &frmHeader->frameAreaSize) == -1)
		return false;

	return true;
}

static bool LoadFrmFrame(UnlistedFrm::Frame *frame, fo::DbFile* frmStream) {

	//FRMframe *frameHeader = (FRMframe*)frameMEM;
	//BYTE* frameBuff = frame + sizeof(FRMframe);

	if (fo::func::db_freadShort(frmStream, &frame->width) == -1)
		return false;
	else if (fo::func::db_freadShort(frmStream, &frame->height) == -1)
		return false;
	else if (fo::func::db_freadInt(frmStream, &frame->size) == -1)
		return false;
	else if (fo::func::db_freadShort(frmStream, &frame->x) == -1)
		return false;
	else if (fo::func::db_freadShort(frmStream, &frame->y) == -1)
		return false;

	frame->indexBuff = new BYTE[frame->size];
	if (fo::func::db_fread(frame->indexBuff, frame->size, 1, frmStream) != 1)
		return false;

	return true;
}

UnlistedFrm *LoadUnlistedFrm(char *frmName, unsigned int folderRef) {

	if (folderRef > fo::OBJ_TYPE_SKILLDEX) return nullptr;

	char *artfolder = fo::var::art[folderRef].path; // address of art type name
	char frmPath[MAX_PATH];

	sprintf_s(frmPath, MAX_PATH, "art\\%s\\%s", artfolder, frmName);

	UnlistedFrm *frm = new UnlistedFrm;

	auto frmStream = fo::func::xfopen(frmPath, "rb");

	if (frmStream != nullptr) {
		if (!LoadFrmHeader(frm, frmStream)) {
			fo::func::db_fclose(frmStream);
			delete frm;
			return nullptr;
		}

		DWORD oriOffset_1st = frm->oriOffset[0];
		DWORD oriOffset_new = 0;
		frm->frames = new UnlistedFrm::Frame[6 * frm->numFrames];
		for (int ori = 0; ori < 6; ori++) {
			if (ori == 0 || frm->oriOffset[ori] != oriOffset_1st) {
				frm->oriOffset[ori] = oriOffset_new;
				for (int fNum = 0; fNum < frm->numFrames; fNum++) {
					if (!LoadFrmFrame(&frm->frames[oriOffset_new + fNum], frmStream)) {
						fo::func::db_fclose(frmStream);
						delete frm;
						return nullptr;
					}
				}
				oriOffset_new += frm->numFrames;
			} else {
				frm->oriOffset[ori] = 0;
			}
		}

		fo::func::db_fclose(frmStream);
	} else {
		delete frm;
		return nullptr;
	}
	return frm;
}

}
