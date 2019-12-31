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

void HookCall(DWORD addr, void* func) {
	SafeWrite32(addr + 1, (DWORD)func - (addr + 5));
}

int wmPlayerX = 0;
int wmPlayerY = 0;
int wmPixelX = 0;
int wmPixelY = 0;
int wmOffsetX = 0;
int wmOffsetY = 0;
int wmTargetX = 0;
int wmTargetY = 0;
int bufPtr;

void Log(const char* text, ...)
{
    if (f == NULL) 
        return;
    char buffer[4096];
    va_list args;
    va_start(args, text);
    vsprintf_s(buffer, 4096, text, args);
    va_end(args);
    fputs(buffer, f);
    fflush(f);
}

HANDLE fo2;

#define FO2_MEM(type, val, offset) *(type*)&val = *(type*)((DWORD)(offset))

void getPlayerPos() {
    FO2_MEM(int, wmPlayerX, 0x672e0c);
    FO2_MEM(int, wmPlayerY, 0x672e10);
    FO2_MEM(int, wmTargetX, 0x672e20);
    FO2_MEM(int, wmTargetY, 0x672e24);
}

void updateWmInfo() {
    FO2_MEM(int, wmOffsetX, 0x51de2c);
    FO2_MEM(int, wmOffsetY, 0x51de30);
    FO2_MEM(int, bufPtr, 0x51de24);
}

const DWORD transBuftoBuf = 0x004D3704;

#define AMOUNT_OF_DOTS 1024

int dots_x[AMOUNT_OF_DOTS];
int dots_y[AMOUNT_OF_DOTS];
short dots = 0;
short dotIdx = 0;
ULONGLONG lastDotTick = 0;

void clearDots() {
    dots = 0;
    dotIdx = 0;
    ZeroMemory(dots_x, sizeof(int) * AMOUNT_OF_DOTS);
    ZeroMemory(dots_y, sizeof(int) * AMOUNT_OF_DOTS);
}

void newDot() {
    ULONGLONG tick = GetTickCount64();
    if (tick - lastDotTick >= 150) {
        lastDotTick = tick;
        dots_x[dotIdx] = wmPlayerX;
        dots_y[dotIdx] = wmPlayerY;
        if (dots != AMOUNT_OF_DOTS) {
            dots++;
        }
        dotIdx++;
        if (dotIdx == AMOUNT_OF_DOTS) {
            dotIdx = 0;
        }

    }
}

// Implements https://github.com/rotators/Fo1in2/issues/3
void wmPutRedPixel(int wmX, int wmY)
{
    wmPixelX = wmX;
    wmPixelY = wmY;

    // calculation code from 0x4c41ec - wmDrawCursorStopped
    __asm {
        pushad
        mov ecx, [wmPixelY]
        mov ebx, [wmPixelX]
        cmp ebx, edi
        jl oob // the pixel is off screen
        cmp ecx, dword ptr ds : [0x51DE30]
        jl oob // the pixel is off screen
        mov edi, [wmOffsetX]
        mov eax, 0x16
        sub eax, edi
        mov edi, [wmOffsetY]
        add ebx, eax
        mov eax, 0x15
        mov edx, 1 // width
        sar edx, 0x1F
        sub eax, edi
        add ecx, eax
        mov eax, 1 // width
        sub eax, edx
        sar eax, 1
        mov edi, ebx
        sub edi, eax
        mov eax, 1 // height
        mov edx, 1 // height
        sar edx, 0x1F
        sub eax, edx
        sar eax, 1
        sub ecx, eax
        imul ecx, ecx, 0x37A
        mov eax, dword ptr ds : [bufPtr]
        add ecx, edi
        add ecx, eax
        cmp ecx, eax
        jle oob
        mov byte ptr ds : [ecx], 133 // red pixel in palette - R=252, G=0, B=0
    oob: // the pixel is off screen
        popad
    }
}

const DWORD drawSubTile = 0x004C40E4;
const DWORD drawCursorStopped = 0x004C41EC;
const DWORD wmWorldmapReset = 0x004BCEF8;
int i = 0;
void __declspec(naked) wmInterfaceRefreshHook() {
    __asm { pushad }

    getPlayerPos();
    updateWmInfo();
    newDot();
    if (wmTargetX + wmTargetY > 0) // otherwise it'll draw a red dot under the hotspot icon after entering the wm fr
    {
        for (i = 0; i < dots; i++) {
            wmPutRedPixel(dots_x[i], dots_y[i]);
        }
    }
    __asm {
        popad;
        jmp drawSubTile;
    }
}

void __declspec(naked) wmStopHook() {
    __asm { pushad }
    getPlayerPos();
    if (wmTargetX == 0 && wmTargetY == 0)
        clearDots();
    __asm {
        popad;
        jmp drawCursorStopped;
    }
}

void __declspec(naked) wmResetHook() {
    __asm { pushad }
    clearDots();
    __asm {
        popad;
        jmp wmWorldmapReset;
    }
}

void Hook() {
    HookCall(0x4C3BE6, wmInterfaceRefreshHook); // when calling wmInterfaceDrawSubTileList
    HookCall(0x4C3C7E, wmStopHook);
    HookCall(0x442BFD, wmResetHook);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
		switch (ul_reason_for_call)
		{
		    case DLL_PROCESS_ATTACH:
                fo2 = GetCurrentProcess();
               // fopen_s(&f, ".\\test.log", "a+");
			    Hook();
		    case DLL_THREAD_ATTACH:
		    case DLL_THREAD_DETACH:
		    case DLL_PROCESS_DETACH:
			    break;
		}
		return TRUE;
}