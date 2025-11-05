#pragma once

#include <Windows.h>

namespace SDK
{
	class UCanvas;
}

class cheat
{
public:
	static void main();
private:
	static void console();
	static void init();
	static void hook();
	static void exit();

	static void hk_post_render(void* thisptr, SDK::UCanvas* canvas);
	static LRESULT CALLBACK hk_wnd_proc(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param);
};

