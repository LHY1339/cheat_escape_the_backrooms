#pragma once
#include <vector>
#include <string>

struct keybind_event
{
	std::string key = "";
	std::vector<std::string> cmd;
	int index = 0;

	void run();
};

class keybind
{
public:
	static keybind* get();

	void empty_bind();
	void add_bind(const std::string& key, const std::vector<std::string>& cmd);
	void call_bind(int w_param);

private:
	keybind() = default;

	std::vector<keybind_event> bind_list;
};

