#pragma once

#include <initializer_list>
#include <Windows.h>

namespace sfall 
{

template<typename T> void _stdcall SafeWrite(DWORD addr, T data) {
	DWORD	oldProtect;
	VirtualProtect((void *)addr, sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect);
	*((T*)addr) = data;
	VirtualProtect((void *)addr, sizeof(T), oldProtect, &oldProtect);
}

template <typename T, class ForwardIteratorType>
void _stdcall SafeWriteBatch(T data, ForwardIteratorType begin, ForwardIteratorType end) {
	for (auto it = begin; it != end; ++it) {
		SafeWrite<T>(*it, data);
	}
}

template <class T, size_t N>
void _stdcall SafeWriteBatch(T data, const DWORD (&addrs)[N]) {
	SafeWriteBatch<T>(data, std::begin(addrs), std::end(addrs));
}

template <typename T>
void _stdcall SafeWriteBatch(T data, std::initializer_list<DWORD> addrs) {
	SafeWriteBatch<T>(data, addrs.begin(), addrs.end());
}

void _stdcall SafeWrite8(DWORD addr, BYTE data);
void _stdcall SafeWrite16(DWORD addr, WORD data);
void _stdcall SafeWrite32(DWORD addr, DWORD data);
void _stdcall SafeWriteStr(DWORD addr, const char* data);

void SafeMemSet(DWORD addr, BYTE val, int len);
void SafeWriteBytes(DWORD addr, BYTE* data, int count);

void HookCall(DWORD addr, void* func);
void MakeCall(DWORD addr, void* func);
void MakeCall(DWORD addr, void* func, int len);
void MakeJump(DWORD addr, void* func);
void MakeJump(DWORD addr, void* func, int len);
void BlockCall(DWORD addr);

void HookCalls(void* func, std::initializer_list<DWORD> addrs);
void MakeCalls(void* func, std::initializer_list<DWORD> addrs);

}
