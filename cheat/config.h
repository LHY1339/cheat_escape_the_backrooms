#pragma once
#include <string>
#include <vector>

class config
{
public:
	static void create(const std::string& path);
	static void load(const std::string& path);
	static bool file_exists(const std::string& path);

private:
	static std::vector<std::string> get_command(const std::string& line, bool& success);
	static void execute(const std::vector<std::string>& param);
};