#include "..\headers\debugger.h"
#include "..\headers\structs.h"
#include "..\Lib\diStorm\distorm.h"

AsmLine codeDisplay[500000];
int parsedLines;
DWORD currentParsedOffset;

BOOL InitInstance(HINSTANCE, int);

int APIENTRY ui_init(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine,  _In_ int  nCmdShow);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    ui_init(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}

HANDLE GetProcessByName(const wchar_t* processName)
{
    DWORD pid = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 process;
    ZeroMemory(&process, sizeof(process));
    process.dwSize = sizeof(process);

    // Walkthrough all processes.
    if (Process32First(snapshot, &process))
    {
        do
        {
            if (wcscmp(process.szExeFile, processName) == 0)
            {
                pid = process.th32ProcessID;
                break;
            }
        } while (Process32Next(snapshot, &process));
    }

    CloseHandle(snapshot);
    if (pid != 0)
    {
        return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    }

    return NULL;
}

void ReadBytes(HANDLE fo2, HWND window, LPCVOID baseOffset, int bytes)
{
    char hexbuf[3];
    char* buf = new char[(bytes * 2)];
    char* out = new char[(bytes*2)+1];
    
    //disassembled = new _DecodedInst[10000];

    SIZE_T bytesRead;

    ReadProcessMemory(fo2, baseOffset, buf, bytes, &bytesRead);
   /* for (int i = 0; i < bytes; i++) {
        sprintf_s(hexbuf, "%x", buf[i] & 0xFF);
        out[(i * 2)] = hexbuf[0];
        out[(i * 2) + 1] = hexbuf[1];
    }
    out[(bytes * 2)] = '\0';*/
    _DecodeResult result;
    _DecodedInst disassembled[500];
    unsigned int instructionCount = 0;
    result = distorm_decode(0, (const unsigned char*)buf, bytes, Decode32Bits, disassembled, 500, &instructionCount);
    if (result != DECRES_SUCCESS)
    {
        MessageBoxA(NULL, "diStorm was unable to disassemble code.", "", MB_OK);
        return;
    }

    //DWORD currentOffset = 0;
    //ZeroMemory(codeDisplay, sizeof(AsmLine) * 1500);
    //codeLines = instructionCount;
    for (unsigned int i = 0; i < instructionCount; i++)
    {
        currentParsedOffset = (DWORD)((DWORD)baseOffset + disassembled[i].offset);
        codeDisplay[parsedLines].bytes = disassembled[i].size;
        codeDisplay[parsedLines].disasmlen = disassembled[i].mnemonic.length+disassembled[i].operands.length+1;
        codeDisplay[parsedLines].disasm = new char[codeDisplay[parsedLines].disasmlen + 1];
        codeDisplay[parsedLines].instructionhexlen = disassembled[i].instructionHex.length;
        //codeDisplay[parsedLines].instructionhex = (char*)disassembled[i].instructionHex.p;
        codeDisplay[parsedLines].instructionhex = new char[disassembled[i].instructionHex.length+1];
        memcpy_s(codeDisplay[parsedLines].instructionhex, disassembled[i].instructionHex.length, disassembled[i].instructionHex.p, disassembled[i].instructionHex.length);
        codeDisplay[parsedLines].instructionhex[disassembled[i].instructionHex.length] = '\0';
        sprintf_s(codeDisplay[parsedLines].disasm, size_t(codeDisplay[parsedLines].disasmlen)+1, "%s %s", (char*)disassembled[i].mnemonic.p, (char*)disassembled[i].operands.p);
        codeDisplay[parsedLines].offset = currentParsedOffset;
        parsedLines++;
        //sprintf_s(, "%x", codeDisplay, currentOffset, (char*)disassembled[i].mnemonic.p, (char*)disassembled[i].operands.p);
    }

    InvalidateRect(window, 0, TRUE);
}
