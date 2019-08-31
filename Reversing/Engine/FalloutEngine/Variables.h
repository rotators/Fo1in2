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

#include <cassert>

#include "VariableOffsets.h"
#include "Structs.h"

//
// Global variable pointers.
//
// In normal CPP code use: fo::var::var_name to read/write value or &fo::var::var_name to use as pointer.
//
namespace fo
{
namespace var
{

template <typename T, int Size>
struct ArrayWrapper {
	T vals[Size];

	T& operator[] (int idx) {
		assert(idx >= 0 && idx < Size);
		return vals[idx];
	}

	operator T* () {
		return static_cast<T*>(vals);
	}

	operator const void* () {
		return static_cast<const void*>(this);
	}
};

// defines reference to an engine variable 
#define VAR_(name, type)	\
	extern type& name;

// defines reference to static array
#define VARA(name, type, size)	\
	extern ArrayWrapper<type, size> &name;

// defines reference to static 2-dimensional array
#define VAR2(name, type, size1, size2)	\
	extern ArrayWrapper<ArrayWrapper<type, size2>, size1> &name;

// defines reference to static 3-dimensional array
#define VAR3(name, type, size1, size2, size3)	\
	extern ArrayWrapper<ArrayWrapper<ArrayWrapper<type, size3>, size2>, size1> &name;

// defines const pointer to variable (useful for static arrays, when exact size is unknown)
#define VARP(name, type)	\
	extern type* const name;

// TODO: assign appropriate types (arrays, structs, strings, etc.) for all variables
#include "Variables_def.h"

}
}
