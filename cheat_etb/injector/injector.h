#pragma once
#include <Windows.h>
#include <string>
#include <filesystem>

class injector
{
public:
	static injector* get();
	int main();
private:
	injector() = default;

	void print_log();
	DWORD find_process(const wchar_t* name);
	BOOL inject(const wchar_t* dll_path, DWORD proc_id);
	std::wstring get_abs_path(const std::filesystem::path& rel_path);
	bool is_load(DWORD pid, const wchar_t* dll_name);
};