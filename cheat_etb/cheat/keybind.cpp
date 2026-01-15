#include "keybind.h"

#include <unordered_map>
#include <Windows.h>

#include "command.h"

std::unordered_map<int, std::string> key_map =
{
    {VK_INSERT, "ins"},
    {VK_DELETE, "del"},
    {VK_HOME, "home"},
    {VK_END, "end"},
    {VK_PRIOR, "pgup"},
    {VK_NEXT, "pgdn"},
    {VK_UP, "up"},
    {VK_DOWN, "down"},
    {VK_LEFT, "left"},
    {VK_RIGHT, "right"},
    {VK_ESCAPE, "esc"},
    {VK_TAB, "tab"},
    {VK_RETURN, "enter"},
    {VK_SPACE, "space"},
    {VK_BACK, "back"},

    {VK_F1, "f1"}, {VK_F2, "f2"}, {VK_F3, "f3"}, {VK_F4, "f4"},
    {VK_F5, "f5"}, {VK_F6, "f6"}, {VK_F7, "f7"}, {VK_F8, "f8"},
    {VK_F9, "f9"}, {VK_F10, "f10"}, {VK_F11, "f11"}, {VK_F12, "f12"},

    {'0', "0"}, {'1', "1"}, {'2', "2"}, {'3', "3"}, {'4', "4"},
    {'5', "5"}, {'6', "6"}, {'7', "7"}, {'8', "8"}, {'9', "9"},

    {'A', "a"}, {'B', "b"}, {'C', "c"}, {'D', "d"}, {'E', "e"},
    {'F', "f"}, {'G', "g"}, {'H', "h"}, {'I', "i"}, {'J', "j"},
    {'K', "k"}, {'L', "l"}, {'M', "m"}, {'N', "n"}, {'O', "o"},
    {'P', "p"}, {'Q', "q"}, {'R', "r"}, {'S', "s"}, {'T', "t"},
    {'U', "u"}, {'V', "v"}, {'W', "w"}, {'X', "x"}, {'Y', "y"},
    {'Z', "z"},

    {-114514, "none"}
};

keybind* keybind::get()
{
	static keybind inst;
	return &inst;
}

void keybind::empty_bind()
{
	bind_list.clear();
}

void keybind::add_bind(const std::string& key, const std::vector<std::string>& cmd)
{
	keybind_event event;
	event.key = key;
	event.cmd = cmd;
	bind_list.emplace_back(event);
}

void keybind::call_bind(int w_param)
{
    auto it = key_map.find(w_param);
    if (it == key_map.end())
    {
        return;
    }

    for (keybind_event& event : bind_list)
    {
        if (it->second == event.key)
        {
            event.run();
            break;
        }
    }
}

void keybind_event::run()
{
    command::get()->run(cmd[index]);
    index++;
    if (index >= cmd.size())
    {
        index = 0;
    }
}
