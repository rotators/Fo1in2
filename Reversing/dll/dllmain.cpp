#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>

FILE* f;

void _stdcall SafeWrite32(DWORD addr, DWORD data) {
    DWORD oldProtect;

    VirtualProtect((void*)addr, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
    *((DWORD*)addr) = data;
    VirtualProtect((void*)addr, 4, oldProtect, &oldProtect);
}

void _stdcall SafeWriteJmp(DWORD addr, void* func) {
    DWORD oldProtect;
    DWORD data = (DWORD)func - (addr + 5);
    VirtualProtect((void*)addr, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
    *((BYTE*)addr) = 0xE9;
    *((DWORD*)(addr + 1)) = data;
    VirtualProtect((void*)addr, 5, oldProtect, &oldProtect);
}

void HookCall(DWORD addr, void* func) {
    SafeWrite32(addr + 1, (DWORD)func - (addr + 5));
}

void Hook() { }

void Init() {
    Hook();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
		switch (ul_reason_for_call)
		{
		    case DLL_PROCESS_ATTACH:
                Init();
		    case DLL_THREAD_ATTACH:
		    case DLL_THREAD_DETACH:
		    case DLL_PROCESS_DETACH:
			    break;
		}
		return TRUE;
}