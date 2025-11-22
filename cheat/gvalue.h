#pragma once
#include <Windows.h>
#include <string>

using fn_post_render = void(__thiscall*)(void*, void*);
using fn_wnd_proc = WNDPROC;

struct s_mouse
{
	int x = 0;
	int y = 0;
	bool left = false;
};

struct s_esp
{
	bool enable = true;
	bool box = true;
	bool name = true;
	bool distance = true;
	bool line = false;
	bool extent = false;
};

namespace SDK
{
	class UWorld;
	class APlayerController;
	class UCanvas;
	class UEngine;
	class APawn;
}

namespace gvalue
{
	inline void** vtb;
	inline fn_post_render def_post_render;
	inline fn_wnd_proc def_wnd_proc;
	inline HINSTANCE dll_inst;

	inline bool menu_open = true;
	inline s_mouse mouse_input = {};
	inline bool is_exit = false;
	inline bool is_clean = false;
	inline int x_offset = 0.0f;
	inline int y_offset = 0.0f;
	
	inline s_esp esp_player;
	inline s_esp esp_entity;
	inline s_esp esp_item;
	inline s_esp esp_interact;
	inline int esp_distance = 100;
	inline bool draw_mesh = false;
	inline int draw_mesh_distance = 10;
	inline int fov = 120;
	inline bool disable_post = false;
	inline bool third_person = false;
	inline int third_distance = 200;

	inline bool inf_stamina = true;
	inline bool inf_sanity = true;
	inline bool no_balance = true;
	inline bool inf_jump = false;
	inline int walk_speed = 250;
	inline int run_speed = 500;
	inline int crouch_speed = 100;
	inline float speedup_multi = 1;
	inline bool ghost_mode = false;
	inline bool fly_mode = false;
	inline float fly_speed = 5.0f;
	inline bool x_delete = false;

	inline std::string key_open_menu = "ins";
	inline std::string key_close_menu = "del";
	inline std::string key_draw_mesh = "none";
	inline std::string key_third_person = "none";
	inline std::string key_ghost_mode = "none";
	inline std::string key_inf_jump = "none";
	inline std::string key_fly_mode = "none";
	inline std::string key_x_delete = "none";
	inline std::string key_kill_all = "none";

	inline SDK::UWorld* world;
	inline SDK::APlayerController* controller;
	inline SDK::UCanvas* canvas;
	inline SDK::UEngine* engine;
	inline SDK::APawn* player_pawn = nullptr;
}