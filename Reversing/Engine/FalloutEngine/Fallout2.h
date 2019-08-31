/*
* sfall
* Copyright (C) 2008-2017 The sfall team
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

/* 
* FALLOUT2.EXE structs, function offsets and wrappers are included from here.
*/

#include "Enums.h"
#include "FunctionOffsets.h"
#include "Structs.h"
#include "EngineUtils.h"
#include "Variables.h"
#include "Functions.h"


// TODO: move/rename these
#define MSG_FILE_COMBAT		(0x56D368)
#define MSG_FILE_AI			(0x56D510)
#define MSG_FILE_SCRNAME	(0x56D754)
#define MSG_FILE_MISC		(0x58E940)
#define MSG_FILE_CUSTOM		(0x58EA98)
#define MSG_FILE_INVENTRY	(0x59E814)
#define MSG_FILE_ITEM		(0x59E980)
#define MSG_FILE_LSGAME		(0x613D28)
#define MSG_FILE_MAP		(0x631D48)
#define MSG_FILE_OPTIONS	(0x6637E8)
#define MSG_FILE_PERK		(0x6642D4)
#define MSG_FILE_PIPBOY		(0x664348)
#define MSG_FILE_QUESTS		(0x664410)
#define MSG_FILE_PROTO		(0x6647FC)
#define MSG_FILE_SCRIPT		(0x667724)
#define MSG_FILE_SKILL		(0x668080)
#define MSG_FILE_SKILLDEX	(0x6680F8)
#define MSG_FILE_STAT		(0x66817C)
#define MSG_FILE_TRAIT		(0x66BE38)
#define MSG_FILE_WORLDMAP	(0x672FB0)

/*
	Gets argument from stack to eax and puts its type to edx register
	eax register must contain the script_ptr
	jlabel - name of the jump label in case the value type is not INT
*/
#define _GET_ARG_INT(jlabel) __asm {				\
	__asm mov  edx, eax								\
	__asm call fo::funcoffs::interpretPopShort_		\
	__asm xchg eax, edx								\
	__asm call fo::funcoffs::interpretPopLong_		\
	__asm cmp  dx, VAR_TYPE_INT						\
	__asm jnz  jlabel								\
}

/*
	Returns the value to the script
	eax register must contain the script_ptr
	edx register must contain the returned value
	rscript - register name for temporarily saving script_ptr
*/
#define _RET_VAL_INT(rscript) __asm {				\
	__asm mov  rscript, eax 						\
	__asm call fo::funcoffs::interpretPushLong_		\
	__asm mov  edx, VAR_TYPE_INT					\
	__asm mov  eax, rscript							\
	__asm call fo::funcoffs::interpretPushShort_	\
}
