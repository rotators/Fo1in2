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

int wmPlayerX = 0;
int wmPlayerY = 0;
int wmPixelX = 0;
int wmPixelY = 0;
int wmOffsetX = 0;
int wmOffsetY = 0;
int wmTargetX = 0;
int wmTargetY = 0;
int curFont = 0;
int wmBuffer;

int curSubtile = 0;
int curTerrain = 0;

int hoveringHotspot = 0;

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


int fmtextToBufFunc = 0x004422B4;
int setFontFunc = 0x004D58DC;
void textToBuffer(void* buffer, char* text, BYTE colorIndex, DWORD x, DWORD y, DWORD txtWidth, DWORD bufferWidth)
{
    DWORD posOffset = y * bufferWidth + x;
    __asm {
        xor eax, eax
        mov al, colorIndex
        push eax
        mov eax, buffer
        add eax, posOffset
        mov edx, text
        mov ebx, txtWidth
        mov ecx, bufferWidth
        call fmtextToBufFunc
    }
}

void wmDraw(char* text, BYTE colorIndex, DWORD x, DWORD y, DWORD txtWidth) {
    textToBuffer((void*)wmBuffer, text, colorIndex, x, y, txtWidth, 890); // 890=width of wm buffer
}

void setFont(int fontId)
{
    __asm {
        mov eax, fontId
        call setFontFunc
    }
}

void getPlayerPos() {
    FO2_MEM(int, wmPlayerX, 0x672e0c);
    FO2_MEM(int, wmPlayerY, 0x672e10);
    FO2_MEM(int, wmTargetX, 0x672e20);
    FO2_MEM(int, wmTargetY, 0x672e24);
}

enum TerrainType {
    DESERT,
    MOUNTAIN,
    CITY,
    OCEAN
};

char* currentTerrainStr;
TerrainType getCurrentTerrain() {
    int c = -1;
    __asm {
        mov eax, dword ptr ds : [0x672E14]
        cmp eax, 0
        je exit
        mov edx, dword ptr ds : [eax]
        mov c, edx
    exit:
    }
    auto t = (TerrainType)c;
    switch (c) {
        case DESERT: 
            sprintf(currentTerrainStr, "Desert"); break;
        case MOUNTAIN: 
            sprintf(currentTerrainStr, "Mountain"); break;
        case CITY: 
            sprintf(currentTerrainStr, "City"); break;
        case OCEAN:
            sprintf(currentTerrainStr, "Ocean"); break;
    }
    return (TerrainType)c;
}

bool isMovingOnWM() {
    return wmTargetX + wmTargetY > 0;
}

//char* displayTerrain;
void updateWmInfo() {
    FO2_MEM(int, wmOffsetX, 0x51de2c);
    FO2_MEM(int, wmOffsetY, 0x51de30);
    FO2_MEM(int, wmBuffer, 0x51de24);
    FO2_MEM(int, curFont, 0x51e3B0);
   // FO2_MEM(int, curSubtile, 0x672E14);
    //*(int*)&curTerrain = curSubtile;
    //FO2_MEM(int, curTerrain, curSubtile);
    
    getCurrentTerrain();
    setFont(0x65);
    if (hoveringHotspot == 1 && !isMovingOnWM()) {
        //sprintf(displayTerrain, "%s", currentTerrainStr);
        wmDraw(currentTerrainStr, 228, wmPlayerX-wmOffsetX, (wmPlayerY-wmOffsetY) + 5, 60); // Shadow
        wmDraw(currentTerrainStr, 215, wmPlayerX - wmOffsetX - 1, (wmPlayerY - wmOffsetY) + 4, 60);
    }
    setFont(curFont);
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
        mov edi, [wmOffsetX]
        cmp ebx, edi
        jl oob // the pixel is off screen
        cmp ecx, dword ptr ds : [0x51DE30]
        jl oob // the pixel is off screen
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
        mov eax, dword ptr ds : [wmBuffer]
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
    if (isMovingOnWM()) // otherwise it'll draw a red dot under the hotspot icon after entering the wm from map
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
    if (!isMovingOnWM())
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

    updateWmInfo();
}

int jmpBack = 0x4BFE89;
int refreshwm = 0x4C3830;
void __declspec(naked) wmDetectHotspotHover() {
    __asm {
        
        push edi
        push ebp
        push eax
        push edx
        push ecx
        mov ecx, hoveringHotspot // to check if hovering changed
        mov edi, dword ptr ss : [esp + 28] // [esp + 8], since we pushed some registers
        mov ebp, dword ptr ds : [0x51DE2C]
        mov eax, dword ptr ds : [0x51DE30]
        add edi, ebp // edi = wmMouseX
        mov ebp, dword ptr ss : [esp + 24] // [esp + 4]
        add ebp, eax // ebp = wmMouseY
        sub edi, 20
        sub ebp, 20
        // check if the cursor is inside
        mov eax, dword ptr ds : [0x672E0C]
        sub eax, edi
        cdq
        xor eax, edx
        sub eax, edx
        cmp eax, 5
        jge unset
        mov eax, dword ptr ds : [0x672E10]
        sub eax, ebp
        cdq
        xor eax, edx
        sub eax, edx
        cmp eax, 5
        jge unset
        mov hoveringHotspot, 1
        jmp change_check
    unset:
        mov hoveringHotspot, 0
    change_check:
        cmp ecx, hoveringHotspot
        je cleanup
        call refreshwm // if value has changed, refresh wm
    cleanup:
        pop ecx
        pop edx
        pop eax
        pop ebp
        pop edi
        mov eax, dword ptr ds : [0x51DE30] // we overwrote it in jmp, so it's here
        jmp jmpBack
    }
}

void Hook() {
    HookCall(0x4C3BE6, wmInterfaceRefreshHook); // when calling wmInterfaceDrawSubTileList
    HookCall(0x4C3C7E, wmStopHook);
    HookCall(0x442BFD, wmResetHook);
    SafeWriteJmp(0x4BFE84, wmDetectHotspotHover);
}

void Init() {
    currentTerrainStr = new char[32];
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
                fo2 = GetCurrentProcess();
               // fopen_s(&f, ".\\test.log", "a+");
                Init();
			    
		    case DLL_THREAD_ATTACH:
		    case DLL_THREAD_DETACH:
		    case DLL_PROCESS_DETACH:
			    break;
		}
		return TRUE;
}