#include "gui.h"

#include "_sdk.h"
#include "gvalue.h"
#include "render.h"

bool left_click = false;
bool left_was_down = false;

void gui::main()
{
	if (gvalue::mouse_input.left)
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
}

bool gui::button(const SDK::FVector2D& pos, const SDK::FVector2D& size)
{
	if (is_hover(pos, size) && left_click)
	{
		return true;
	}
	return false;
}

bool gui::button_color(const SDK::FVector2D& pos, const SDK::FVector2D& size, const SDK::FLinearColor& normal_col, const SDK::FLinearColor& hover_col, const SDK::FLinearColor& press_col)
{
	bool value = false;
	SDK::FLinearColor color;

	if (is_hover(pos, size))
	{
		value = left_click;
		color = gvalue::mouse_input.left ? press_col : hover_col;
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

bool gui::button_text(const SDK::FVector2D& pos, const SDK::FVector2D& size, const UC::FString& text, SDK::UFont* font, const SDK::FLinearColor& normal_col, const SDK::FLinearColor& hover_col, const SDK::FLinearColor& press_col)
{
	bool value = false;
	SDK::FLinearColor color;

	if (is_hover(pos, size))
	{
		value = left_click;
		color = gvalue::mouse_input.left ? press_col : hover_col;
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

bool gui::button_color_text(const SDK::FVector2D& pos, const SDK::FVector2D& size, const UC::FString& text, SDK::UFont* font, const SDK::FLinearColor& text_col, const SDK::FLinearColor& normal_col, const SDK::FLinearColor& hover_col, const SDK::FLinearColor& press_col)
{
	bool value = false;
	SDK::FLinearColor color;

	if (is_hover(pos, size))
	{
		value = left_click;
		color = gvalue::mouse_input.left ? press_col : hover_col;
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

void gui::check_box(const SDK::FVector2D& pos, const SDK::FVector2D& size, const SDK::FVector2D& check_size, const SDK::FLinearColor& check_col, const SDK::FLinearColor& normal_col, const SDK::FLinearColor& hover_col, const SDK::FLinearColor& press_col, bool* ptr)
{
	SDK::FLinearColor color;

	if (is_hover(pos, size))
	{
		if (left_click)
		{
			(*ptr) = !(*ptr);
		}
		color = gvalue::mouse_input.left ? press_col : hover_col;
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

bool gui::is_hover(const SDK::FVector2D& pos, const SDK::FVector2D& size)
{
	if (gvalue::mouse_input.x > pos.X &&
		gvalue::mouse_input.y > pos.Y &&
		gvalue::mouse_input.x < pos.X + size.X &&
		gvalue::mouse_input.y < pos.Y + size.Y)
	{
		return true;
	}
	return false;
}
