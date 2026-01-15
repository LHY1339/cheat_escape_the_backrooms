#include "gui.h"

#include "_sdk.h"
#include "gvalue.h"
#include "render.h"

bool left_click= false;
bool left_was_down = false;

bool right_click = false;
bool right_was_down = false;

std::string focus_name = "";

void gui::main()
{
	if (gvalue::mouse.left)
	{
		if (!left_was_down)
		{
			left_click = true;
			left_was_down = true;
		}
		else
		{
			left_click = false;
		}
	}
	else
	{
		left_click = false;
		left_was_down = false;
	}

	if (gvalue::mouse.right)
	{
		if (!right_was_down)
		{
			right_click = true;
			right_was_down = true;
		}
		else
		{
			right_click = false;
		}
	}
	else
	{
		right_click = false;
		right_was_down = false;
	}

	if (!gvalue::mouse.left)
	{
		focus_name = "";
	}
}

bool gui::button(const std::string& name, const SDK::FVector2D& pos, const SDK::FVector2D& size)
{
	if (is_hover(pos, size, name) && left_click && is_focus(name))
	{
		return true;
	}
	return false;
}

bool gui::button_color(const std::string& name, const SDK::FVector2D& pos, const SDK::FVector2D& size, const SDK::FLinearColor& normal_col, const SDK::FLinearColor& hover_col, const SDK::FLinearColor& press_col)
{
	bool value = false;
	SDK::FLinearColor color;

	if (is_hover(pos, size, name))
	{
		if (is_focus(name))
		{
			value = left_click;
		}
		color = gvalue::mouse.left ? press_col : hover_col;
	}
	else
	{
		value = false;
		color = normal_col;
	}

	render::fill_box(
		pos,
		size,
		color
	);

	return value;
}

bool gui::button_text(const std::string& name, const SDK::FVector2D& pos, const SDK::FVector2D& size, const UC::FString& text, SDK::UFont* font, const SDK::FLinearColor& normal_col, const SDK::FLinearColor& hover_col, const SDK::FLinearColor& press_col)
{
	bool value = false;
	SDK::FLinearColor color;

	if (is_hover(pos, size, name))
	{
		if (is_focus(name))
		{
			value = left_click;
		}
		color = gvalue::mouse.left ? press_col : hover_col;
	}
	else
	{
		value = false;
		color = normal_col;
	}

	render::draw_text(
		font,
		text,
		SDK::FVector2D(pos.X + size.X / 2, pos.Y + size.Y / 2),
		SDK::FVector2D(1.0f, 1.0f),
		color,
		1.0f,
		SDK::FLinearColor(0.0f, 0.0f, 0.0f, 0.0f),
		SDK::FVector2D(0.0f, 0.0f),
		true,
		true,
		false,
		SDK::FLinearColor(0.0f, 0.0f, 0.0f, 0.0f)
	);

	return value;
}

bool gui::button_color_text(const std::string& name, const SDK::FVector2D& pos, const SDK::FVector2D& size, const UC::FString& text, SDK::UFont* font, const SDK::FLinearColor& text_col, const SDK::FLinearColor& normal_col, const SDK::FLinearColor& hover_col, const SDK::FLinearColor& press_col)
{
	bool value = false;
	SDK::FLinearColor color;

	if (is_hover(pos, size, name))
	{
		if (is_focus(name))
		{
			value = left_click;
		}
		color = gvalue::mouse.left ? press_col : hover_col;
	}
	else
	{
		value = false;
		color = normal_col;
	}

	render::fill_box(
		pos,
		size,
		color
	);

	render::draw_text(
		font,
		text,
		SDK::FVector2D(pos.X + size.X / 2, pos.Y + size.Y / 2),
		SDK::FVector2D(1.0f, 1.0f),
		text_col,
		1.0f,
		SDK::FLinearColor(0.0f, 0.0f, 0.0f, 0.0f),
		SDK::FVector2D(0.0f, 0.0f),
		true,
		true,
		false,
		SDK::FLinearColor(0.0f, 0.0f, 0.0f, 0.0f)
	);

	return value;
}

void gui::check_box(const std::string& name, const SDK::FVector2D& pos, const SDK::FVector2D& size, const SDK::FVector2D& check_size, const SDK::FLinearColor& check_col, const SDK::FLinearColor& normal_col, const SDK::FLinearColor& hover_col, const SDK::FLinearColor& press_col, bool* ptr)
{
	SDK::FLinearColor color;

	if (is_hover(pos, size, name))
	{
		if (left_click && is_focus(name))
		{
			(*ptr) = !(*ptr);
		}
		color = gvalue::mouse.left ? press_col : hover_col;
	}
	else
	{
		color = normal_col;
	}

	render::fill_box(
		pos,
		size,
		color
	);

	if (*ptr)
	{
		render::fill_box(
			SDK::FVector2D(pos.X + (size.X - check_size.X) / 2, pos.Y + (size.Y - check_size.Y) / 2), 
			check_size,
			check_col
		);
	}
}

void gui::drag_bar(const std::string& name, const SDK::FVector2D& pos, const SDK::FVector2D& size, const SDK::FVector2D& bar_size, const SDK::FLinearColor& bar_col, const SDK::FLinearColor& normal_col, const SDK::FLinearColor& hover_col, const SDK::FLinearColor& press_col, float* ptr)
{
	SDK::FLinearColor color;

	if (is_hover(pos, size, name))
	{
		color = gvalue::mouse.left ? press_col : hover_col;
	}
	else
	{
		color = normal_col;
	}

	if (gvalue::mouse.left && is_focus(name))
	{
		const float val = (gvalue::mouse.x - pos.X) / (size.X);
		const float min = val < 0.0f ? 0.0f : val;
		const float max = min > 1.0f ? 1.0f : min;
		(*ptr) = max;
	}

	render::fill_box(
		pos,
		size,
		color
	);

	render::fill_box(
		SDK::FVector2D(pos.X + size.X * (*ptr) - bar_size.X / 2, pos.Y), 
		bar_size,
		bar_col
	);
}

void gui::drag(SDK::FVector2D& pos, SDK::FVector2D& size, SDK::FVector2D& drag_pos, bool& is_drag)
{
	if (!gvalue::mouse.left || focus_name != "")
	{
		is_drag = false;
		return;
	}

	if (gvalue::mouse.x > pos.X &&
		gvalue::mouse.y > pos.Y &&
		gvalue::mouse.x < pos.X + size.X &&
		gvalue::mouse.y < pos.Y + size.Y &&
		left_click)
	{
		is_drag = true;
		drag_pos.X = gvalue::mouse.x - pos.X;
		drag_pos.Y = gvalue::mouse.y - pos.Y;
	}

	if (is_drag)
	{
		pos.X = gvalue::mouse.x - drag_pos.X;
		pos.Y = gvalue::mouse.y - drag_pos.Y;
	}
}

bool gui::is_hover(const SDK::FVector2D& pos, const SDK::FVector2D& size, const std::string& name)
{
	if (gvalue::mouse.x > pos.X &&
		gvalue::mouse.y > pos.Y &&
		gvalue::mouse.x < pos.X + size.X &&
		gvalue::mouse.y < pos.Y + size.Y)
	{
		if (left_click)
		{
			focus_name = name;
		}
		return true;
	}
	return false;
}

bool gui::is_focus(const std::string& name)
{
	return name == focus_name;
}
