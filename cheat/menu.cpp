#include "menu.h"

#include "render.h"
#include "_sdk.h"
#include "gvalue.h"

float menu_x = 100.0f;
float menu_y = 100.0f;
float menu_w = 400.0f;
float menu_h = 300.0f;

bool left_down = false;
bool menu_drag = false;
float drag_x = 0.0f;
float drag_y = 0.0f;

void menu::main()
{
	lable();
	base();
}

void menu::lable()
{
	render::draw_text(
		gvalue::engine->MediumFont,
		L"按下 Ins（Insert）显示/隐藏菜单\n按下 Del（Delete）退出",
		SDK::FVector2D(10.0f, 10.0f),
		SDK::FVector2D(1.0f, 1.0f),
		SDK::FLinearColor(1.0f, 1.0f, 1.0f, 1.0f),
		1.0f,
		SDK::FLinearColor(0.0f, 0.0f, 0.0f, 0.0f),
		SDK::FVector2D(0.0f, 0.0f),
		false,
		false,
		false,
		SDK::FLinearColor(0.0f, 0.0f, 0.0f, 0.0f)
	);
}

void menu::base()
{
	if (!gvalue::menu_open)
	{
		return;
	}

	base_logic();
	base_draw();
	base_cursor();
}

void menu::base_logic()
{
	if (gvalue::mouse_input.left)
	{
		if (!left_down)
		{
			if (gvalue::mouse_input.x > menu_x &&
				gvalue::mouse_input.y > menu_y &&
				gvalue::mouse_input.x < menu_x + menu_w &&
				gvalue::mouse_input.y < menu_y + menu_h)
			{
				menu_drag = true;
				drag_x = gvalue::mouse_input.x - menu_x;
				drag_y = gvalue::mouse_input.y - menu_y;
			}
			left_down = true;
		}
	}
	else
	{
		left_down = false;
		menu_drag = false;
	}

	if (menu_drag)
	{
		menu_x = gvalue::mouse_input.x - drag_x;
		menu_y = gvalue::mouse_input.y - drag_y;
	}
}

void menu::base_draw()
{
	render::fill_box(
		SDK::FVector2D(menu_x - 2, menu_y - 2),
		SDK::FVector2D(menu_w + 4, menu_h + 4), 
		SDK::FLinearColor(0.2f, 0.2f, 0.6f, 1.0f)
	);

	render::fill_box(
		SDK::FVector2D(menu_x, menu_y),
		SDK::FVector2D(menu_w, menu_h),
		SDK::FLinearColor(0.02f, 0.02f, 0.06f, 1.0f)
	);
}

void menu::base_cursor()
{
	render::fill_box(
		SDK::FVector2D(gvalue::mouse_input.x - 2, gvalue::mouse_input.y - 2),
		SDK::FVector2D(4, 4),
		SDK::FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)
	);
}