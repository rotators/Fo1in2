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
#pragma once

#include <string>

#include "Functions.h"
#include "Enums.h"

//
// Various utility functions, based on FO engine functions
//

namespace fo
{

// returns weapon animation code
long AnimCodeByWeapon(GameObject* weapon);

inline void DisplayPrint(const std::string& str) {
	fo::func::display_print(str.c_str());
}

// returns message string from given file or "Error" when not found
const char* _stdcall GetMessageStr(const MessageList* fileAddr, long messageId);

// similar to GetMessageStr, but returns nullptr when no message is found
const char* _stdcall MessageSearch(const MessageList* fileAddr, long messageId);

// returns pointer to prototype by PID, or nullptr on failure
Proto* GetProto(long pid);

bool CritterCopyProto(long pid, long* &proto_dst);

// wrapper for skill_get_tags with bounds checking
void SkillGetTags(long* result, long num);

// wrapper for skill_set_tags with bounds checking
void SkillSetTags(long* tags, long num);

long __fastcall GetItemType(GameObject* item);

__declspec(noinline) GameObject* GetItemPtrSlot(GameObject* critter, InvenType slot);

long& GetActiveItemMode();

GameObject* GetActiveItem();

long GetCurrentAttackMode();

bool HeroIsFemale();

long CheckAddictByPid(fo::GameObject* critter, long pid);

void ToggleNpcFlag(fo::GameObject* npc, long flag, bool set);

// Returns the number of party members in the existing table (begins from 1)
long IsPartyMemberByPid(long pid);

bool IsPartyMember(fo::GameObject* critter);

// Returns the number of local variables of the object script
long GetScriptLocalVars(long sid);

// Print text to surface
void PrintText(char *displayText, BYTE colorIndex, DWORD x, DWORD y, DWORD textWidth, DWORD destWidth, BYTE *surface);
// gets the height of the currently selected font
DWORD GetTextHeight();
// gets the length of a string using the currently selected font
DWORD GetTextWidth(char *textMsg);
// get width of Char for current font
DWORD GetCharWidth(char charVal);
// get maximum string length for current font - if all characters were maximum width
DWORD GetMaxTextWidth(char *textMsg);
// get number of pixels between characters for current font
DWORD GetCharGapWidth();
// get maximum character width for current font
DWORD GetMaxCharWidth();

// Redraw the given object on screen (does not always redraws the whole object)
void RedrawObject(GameObject* obj);

UnlistedFrm *LoadUnlistedFrm(char *frmName, unsigned int folderRef);

}
