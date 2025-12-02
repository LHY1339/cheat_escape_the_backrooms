#pragma once
#include <Windows.h>

#include "cheat.h"
#include "gvalue.h"

BOOL WINAPI DllMain(
	HINSTANCE h_inst_dll,
	DWORD fdw_reason,
	LPVOID lpv_reserved
)
{
	if (fdw_reason == DLL_PROCESS_ATTACH)
	{
		gvalue::dll_inst = h_inst_dll;
		HANDLE h_thread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)cheat::main, NULL, NULL, NULL);
		if (h_thread)
		{
			CloseHandle(h_thread);
		}
	}
	return TRUE;
}