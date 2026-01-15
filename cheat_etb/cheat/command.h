#pragma once
#include <string>
#include <vector>

class command
{
public:
	static command* get();

	void init();
	void run(const std::string& cmd);
	std::vector<std::string> value_to_cmd();
private:
	command() = default;

	std::vector<std::string> split(const std::string& str);
};

