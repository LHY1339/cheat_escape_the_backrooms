#pragma once
#include <filesystem>

class config
{
public:
	static config* get();

	void save();
	void load(std::filesystem::path file_path);

private:
	config() = default;
};

