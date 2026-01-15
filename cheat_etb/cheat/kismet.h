#pragma once
#include <Windows.h>

class kismet
{
public:
	static bool is_key_down(const int& key);
	static HWND get_window();
};

