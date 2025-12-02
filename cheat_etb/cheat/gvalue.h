#pragma once
#include <Windows.h>

using fn_post_render = void(__thiscall*)(void*, void*);
using fn_wnd_proc = WNDPROC;

struct s_mouse
{
	int x = 0;
	int y = 0;
	bool left = false;
};

namespace SDK
{
	class UWorld;
	class APlayerController;
	class UCanvas;
	class UEngine;
}

namespace gvalue
{
	inline void** vtb;
	inline HINSTANCE dll_inst;
	inline fn_post_render def_post_render;
	inline fn_wnd_proc def_wnd_proc;

	inline SDK::UWorld* world;
	inline SDK::APlayerController* controller;
	inline SDK::UCanvas* canvas;
	inline SDK::UEngine* engine;

	inline bool menu_open = true;
	inline bool is_exit = false;
	inline bool is_clean = false;
	inline s_mouse mouse = {};
}