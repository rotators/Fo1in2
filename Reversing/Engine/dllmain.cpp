#pragma once

#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include "Memory/SafeWrite.h";
#include "FalloutEngine/Fallout2.h";
#include "Source/dude.h";

void Hook() {
	sfall::HookCall(0x44C0CB, dude::hook_move);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
		switch (ul_reason_for_call)
		{
		case DLL_PROCESS_ATTACH:
			Hook();
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
		}
		return TRUE;
}