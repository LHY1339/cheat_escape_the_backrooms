#pragma once
#include "_d2d.h"

class gui
{
public:
	static void main();
	static bool button(D2D1_RECT_F rect, const wchar_t* in_text);

private:
	static bool is_hover(D2D1_RECT_F rect);
};

