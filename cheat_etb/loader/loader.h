#pragma once
#include <Windows.h>
#include <string>
#include <filesystem>

class loader
{
public:
	static loader* get();
	int main();
private:
	loader() = default;

	void print_log();
	DWORD find_process(const wchar_t* name);
	BOOL inject(const wchar_t* dll_path, DWORD proc_id);
	std::wstring get_abs_path(const std::filesystem::path& rel_path);
	bool is_load(DWORD pid, const wchar_t* dll_name);
};