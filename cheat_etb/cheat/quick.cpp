#include "quick.h"
#include "kismet.h"
#include "gvalue.h"
#include "gui.h"
#include "_sdk.h"
#include "render.h"
#include "color.h"
#include "entity.h"
#include "config.h"
#include "item.h"

class function
{
public:
	static void set_font(const int& size)
	{
		gvalue::engine->TinyFont->LegacyFontSize = size;
	}

	static bool button(const SDK::FVector2D& pos, const SDK::FVector2D& size, const std::wstring& str, bool* ptr)
	{
		auto color_add = [&](const SDK::FLinearColor& col1, const SDK::FLinearColor& col2)
			{
				return SDK::FLinearColor(col1.R + col2.R, col1.G + col2.G, col1.B + col2.B, col1.A + col2.A);
			};

		SDK::FLinearColor col = (*ptr) ? SDK::FLinearColor(0, 0.4f, 0, 1) : SDK::FLinearColor(0.4f, 0, 0, 1);
		std::wstring render_str = str + ((*ptr) ? L"：开启" : L"：关闭");

		const bool value = gui::button_color_text(
			" ",
			pos,
			SDK::FVector2D(size.X, size.Y),
			render_str.c_str(),
			gvalue::engine->TinyFont,
			SDK::FLinearColor(1, 1, 1, 1), 
			col,
			color_add(col, SDK::FLinearColor(0.02f, 0.02f, 0.02f)) ,
			color_add(col, SDK::FLinearColor(0.05f, 0.05f, 0.05f)),
			SDK::FVector2D(1,1)
		);

		if (value)
		{
			(*ptr) = !(*ptr);
		}

		return value;
	}

	static bool button_color_text(const SDK::FVector2D& pos, const SDK::FVector2D& size, const SDK::FString& str)
	{
		return gui::button_color_text(
			" ",
			pos,
			SDK::FVector2D(size.X, size.Y),
			str,
			gvalue::engine->TinyFont,
			color::get()->text_col,
			color::get()->normal_col,
			color::get()->hover_col,
			color::get()->press_col,
			SDK::FVector2D(1, 1)
		);
	}
};

quick* quick::get()
{
	static quick inst;
	return &inst;
}

void quick::init()
{

}

void quick::main()
{
	gvalue::quick_menu_open = kismet::is_key_down(VK_TAB);

	if (!gvalue::quick_menu_open)
	{
		return;
	}

	function::set_font(14);
	visual();
	player();
	entity();
	item();
	misc();
	cursor();
}

void quick::visual()
{
	render::fill_box(
		SDK::FVector2D(10, 10),
		SDK::FVector2D(220, 110), 
		SDK::FLinearColor(0.01f, 0.01f, 0.02f, 1)
	);

#define BUTTON(_y_,_name_,_param_) \
function::button(SDK::FVector2D(20, _y_), SDK::FVector2D(200, 40), L#_name_, &gvalue::_param_);

	BUTTON(20, 绘制网格体, draw_mesh);
	BUTTON(70, 第三人称, third_person);

#undef BUTTON
}

void quick::player()
{
	render::fill_box(
		SDK::FVector2D(10, 130),
		SDK::FVector2D(220, 360),
		SDK::FLinearColor(0.01f, 0.01f, 0.02f, 1)
	);

#define BUTTON(_y_,_name_,_param_) \
function::button(SDK::FVector2D(20, _y_), SDK::FVector2D(200, 40), L#_name_, &gvalue::_param_);

	BUTTON(140, 飞行模式, fly_mode);
	BUTTON(190, 无敌模式, inf_health);
	BUTTON(240, 灵魂出窍, ghost_mode);
	BUTTON(290, X键删除, x_delete);
	BUTTON(340, 反自瞄, spin);
	BUTTON(390, T字姿势, t_pos);
	BUTTON(440, 右键移动, rb_move);

#undef BUTTON
}

void quick::entity()
{
	render::fill_box(
		SDK::FVector2D(240, 10),
		SDK::FVector2D(220, 110),
		SDK::FLinearColor(0.01f, 0.01f, 0.02f, 1)
	);

#define BUTTON(_y_,_name_) \
const bool b = function::button_color_text(SDK::FVector2D(250, _y_), SDK::FVector2D(200, 40), L#_name_);

	{
		BUTTON(20, 杀死所有实体);
		if (b)
		{
			entity::get()->kill_all();
		}
	}


	{
		BUTTON(70, 取消控制实体);
		if (b)
		{
			entity::get()->unposs();
		}
	}

#undef BUTTON
}

void quick::item()
{
	render::fill_box(
		SDK::FVector2D(240, 130),
		SDK::FVector2D(220, 60),
		SDK::FLinearColor(0.01f, 0.01f, 0.02f, 1)
	);

#define BUTTON(_y_,_name_) \
const bool b = function::button_color_text(SDK::FVector2D(250, _y_), SDK::FVector2D(200, 40), L#_name_);

{
	BUTTON(140, 吸附所有磁带);
	if (b)
	{
		item::get()->interact_all("Tape_BP_C");
	}
}

#undef BUTTON
}

void quick::misc()
{
	render::fill_box(
		SDK::FVector2D(470, 10),
		SDK::FVector2D(220, 60),
		SDK::FLinearColor(0.01f, 0.01f, 0.02f, 1)
	);

#define BUTTON(_y_,_name_) \
function::button_color_text(SDK::FVector2D(480, _y_), SDK::FVector2D(200, 40), L#_name_);

	{
		const bool b = BUTTON(20, 保存配置);
		if (b)
		{
			config::get()->save();
		}
	}

#undef BUTTON
}

void quick::cursor()
{
	render::fill_box(
		SDK::FVector2D(gvalue::mouse.x - 4, gvalue::mouse.y - 4),
		SDK::FVector2D(8, 8),
		SDK::FLinearColor(1, 1, 1, 1)
	);
	render::fill_box(
		SDK::FVector2D(gvalue::mouse.x - 2, gvalue::mouse.y - 2),
		SDK::FVector2D(4, 4),
		SDK::FLinearColor(0, 0, 0, 0)
	);
}