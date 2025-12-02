#include "gui.h"

#include "gvalue.h"
#include "gconst.h"

bool left_click_down = false;
bool left_was_down = false;

void gui::main()
{
	if (gvalue::mouse.left)
	{
		if (!left_was_down)
		{
			left_click_down = true;
			left_was_down = true;
		}
		else
		{
			left_click_down = false;
		}
	}
	else
	{
		left_click_down = false;
		left_was_down = false;
	}
}

bool gui::button(D2D1_RECT_F rect, const wchar_t* in_text)
{
	bool value = false;
	D2D1_COLOR_F color;

	if (is_hover(rect))
	{
		value = left_click_down;
		color = gvalue::mouse.left ? gconst::press_col : gconst::hover_col;
	}
	else
	{
		value = false;
		color = gconst::normal_col;
	}

	gvalue::brush->SetColor(color);
	gvalue::render_target->FillRectangle(rect, gvalue::brush);

	gvalue::brush->SetColor(gconst::text_col);
	gvalue::f15->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	gvalue::f15->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	gvalue::render_target->DrawTextW(
		in_text,
		(UINT32)wcslen(in_text),
		gvalue::f15,
		rect,
		gvalue::brush
	);

	return value;
}

bool gui::is_hover(D2D1_RECT_F rect)
{
	if (gvalue::mouse.x > rect.left &&
		gvalue::mouse.y > rect.top &&
		gvalue::mouse.x < rect.right &&
		gvalue::mouse.y < rect.bottom)
	{
		return true;
	}
	return false;
}
