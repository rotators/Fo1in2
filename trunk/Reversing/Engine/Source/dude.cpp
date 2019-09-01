#include "..//FalloutEngine/Fallout2.h";
#include "..//FalloutEngine/Structs.h";

// TODO: Yes, this isn't supposed to be here, it's because of experimentation...

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

namespace dude {

	static int ret;
	int __stdcall check_move(int actionPoints)
	{
		// this code sucks...
		__asm { 
				push actionPoints;
				mov eax, esp;
				call fo::funcoffs::check_move_
				mov ret, eax;
				add esp, 4 };
		return ret;
	}

	// dude_run, 0x0041810C
	void __stdcall run(int actionPoints)
	{
		DWORD dstTile;
		// Check to which tile we are moving
		dstTile = check_move(actionPoints);
		if (dstTile == -1) // Can't go there, not enough actionpoints or invalid tile.
			return;

		fo::GameObject* obj_dude = *reinterpret_cast<fo::GameObject * *>(FO_VAR_obj_dude);
		if (fo::func::perk_level(obj_dude, fo::Perk::PERK_silent_running) == 0)
			fo::func::pc_flag_off(0); // Turn off sneak flag is we don't have silent running

		fo::func::register_begin(2);
		int prop = *(int*)((DWORD)(&obj_dude + 0x28)); // not sure what this property is?
		fo::func::register_object_run_to_tile(obj_dude, dstTile, prop, actionPoints, 0);
		fo::func::register_end();
	}

	/*
	dude_move, 0x4180B4
	Move dude to a tile, used when clicking on a hex.
	actionPoints == -1 when not in combat
	*/
	void __stdcall move(int actionPoints) 
	{
		DWORD dstTile;
		// Check to which tile we are moving
		dstTile = check_move(actionPoints);
		if (dstTile == -1) // Can't go there, not enough actionpoints or invalid tile.
			return;

		DWORD lastDest = *reinterpret_cast<DWORD*>(FO_VAR_lastDest);
		if (lastDest != dstTile) 
		{
			*(DWORD*)((DWORD)FO_VAR_lastDest) = dstTile; // save the tile we're going to.
			fo::func::register_begin(2);
			fo::GameObject* obj_dude = *reinterpret_cast<fo::GameObject**>(FO_VAR_obj_dude);
			int prop = *(int*)((DWORD)(&obj_dude + 0x28)); // not sure what this property is?
			fo::func::register_object_move_to_tile(obj_dude, dstTile, prop, actionPoints, 0);
			fo::func::register_end();
		}
		else { // if last tile was the same one, run there instead.
			//fo::func::dude_run(actionPoints);
			run(actionPoints);
		}
	}



	void __declspec(naked) hook_run() {
		__asm {
			_asm { push eax }
			_asm { call run }
			_asm { ret }
		}
	}

	// TODO: Autogenerate
	void __declspec(naked) hook_move() {
		__asm {
			_asm { push eax }
			_asm { call move }
			_asm { ret }
		}
	}

	/*void __declspec(naked) hook_test() {
		__asm {
			push ebx;
			push ecx;
			push edx;
			sub esp, 4;
			mov dword ptr ss : [esp] , eax;
			mov eax, esp;
			call fo::funcoffs::check_move_;
			mov edx, eax;
			cmp eax, 0xFFFFFFFF;
			je end;
			cmp eax, dword ptr ds: [FO_VAR_lastDest]
			jne register_move
			mov eax, dword ptr ss: [esp]
			call fo::funcoffs::dude_run_
			jmp end;
register_move:
			mov dword ptr ds : [FO_VAR_lastDest] , eax
			mov eax, 2
			call fo::funcoffs::register_begin_;
			mov eax, dword ptr ds : [FO_VAR_obj_dude]
			push 0
			mov ecx, dword ptr ss : [esp + 0x4]
			mov ebx, dword ptr ds : [eax + 0x28]
			call fo::funcoffs::register_object_move_to_tile_
			call fo::funcoffs::register_end_;
end:
			add esp, 4
			pop edx
			pop ecx
			pop ebx
			ret
		}
	}*/


}
