#include "kismet.h"

#include "gvalue.h"

#include <Windows.h>

bool kismet::is_key_down(const int& key)
{
	return (GetAsyncKeyState(key) & 0x8000) && GetForegroundWindow() == get_window();
}

HWND kismet::get_window()
{
	return FindWindowW(L"UnrealWindow", L"EscapeTheBackrooms  ");
}
