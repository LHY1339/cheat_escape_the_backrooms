#pragma once

#include "_d2d.h"

#include <string>
#include <filesystem>

class loader
{
public:
	static int main();
private:
	static void window();
	static void d2d();
	static void loop();

	static LRESULT CALLBACK wnd_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
	static void render();
	static void clean();

	static DWORD find_process(const wchar_t* name);
	static BOOL inject(const wchar_t* dll_path, DWORD proc_id);
	static std::wstring get_abs_path(const std::filesystem::path& rel_path);
	static bool is_load(DWORD pid, const wchar_t* dll_name);
};

