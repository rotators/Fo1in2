#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>

int main()
{
    DWORD processId = 0;
    PROCESS_INFORMATION procInfo;
    STARTUPINFOA startupInfo = { 0 };
    const char* name = "fallout2.exe";
    const char* dll_name = "fo1in2.dll";
    CreateProcessA(name, (LPSTR)name, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &procInfo);
    processId = procInfo.dwProcessId;
    Sleep(100);
    HANDLE Proc;
    LPVOID RemoteString, LoadLibraryAddress;
    Proc = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, processId);
    if (!Proc)
        exit(-1);

    LoadLibraryAddress = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
    RemoteString = (LPVOID)VirtualAllocEx(Proc, NULL, strlen(dll_name), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (!WriteProcessMemory(Proc, (LPVOID)RemoteString, dll_name, strlen(dll_name), NULL))
        exit(-1);
    if (!CreateRemoteThread(Proc, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryAddress, (LPVOID)RemoteString, NULL, NULL))
        exit(-1);
    CloseHandle(Proc);
    return 0;
}