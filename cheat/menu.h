#pragma once

#include <string>

class menu
{
public:
	static void main();
private:
	static void lable();
	static void base();

	static void base_logic();
	static void base_draw();
	static void base_cursor();

	static void left_bar();
	static void visual();
	static void player();
	static void item();
	static void entity();
	static void misc();

	static std::wstring f_to_ws(const float& f);
};

