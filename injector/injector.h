#pragma once
#include <Windows.h>
#include <string>
#include <filesystem>

class injector
{
public:
	static int main();
private:
	static DWORD find_process(const wchar_t* name);
	static BOOL inject(const wchar_t* dll_path, DWORD proc_id);
	static std::wstring get_abs_path(const std::filesystem::path& rel_path);
};

