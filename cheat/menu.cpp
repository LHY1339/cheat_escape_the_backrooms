#include "menu.h"

#include "render.h"
#include "_sdk.h"
#include "gvalue.h"
#include "gui.h"
#include "glanguage.h"
#include "item.h"
#include "entity.h"
#include "level.h"
#include "config.h"
#include "visual.h"

#include <sstream>
#include <iomanip>
#include <string>

enum class e_page
{
	visual,
	player,
	item,
	entity,
	level,
	misc,
};

float menu_x = 100.0f;
float menu_y = 100.0f;
float menu_w = 400.0f;
float menu_h = 300.0f;

bool left_down = false;
bool menu_drag = false;
float drag_x = 0.0f;
float drag_y = 0.0f;

e_page page = e_page::visual;

const SDK::FLinearColor normal_col(0.04f, 0.04f, 0.04f, 1.0f);
const SDK::FLinearColor hover_col(0.06f, 0.06f, 0.06f, 1.0f);
const SDK::FLinearColor press_col(0.1f, 0.1f, 0.1f, 1.0f);
const SDK::FLinearColor text_col(1.0f, 1.0f, 1.0f, 1.0f);

bool button_01(const UC::FString& text, const SDK::FVector2D& pos, const SDK::FVector2D& size)
{
	return gui::button_color_text(
		pos,
		size,
		text,
		gvalue::engine->MediumFont,
		text_col,
		normal_col,
		hover_col,
		press_col
	);
}

void text_01(const UC::FString& text, const SDK::FVector2D& pos, const bool& mid_x, const bool& mid_y)
{
	render::draw_text(
		gvalue::engine->MediumFont,
		text,
		pos,
		SDK::FVector2D(1.0f, 1.0f),
		SDK::FLinearColor(1.0f, 1.0f, 1.0f, 1.0f),
		1.0f,
		SDK::FLinearColor(0.0f, 0.0f, 0.0f, 0.0f),
		SDK::FVector2D(0.0f, 0.0f),
		mid_x,
		mid_y,
		false,
		SDK::FLinearColor(0.0f, 0.0f, 0.0f, 0.0f)
	);
}

void check_box_01(const SDK::FVector2D& pos, bool* ptr)
{
	gui::check_box(
		pos,
		SDK::FVector2D(15, 15),
		SDK::FVector2D(9, 9),
		SDK::FLinearColor(0.4f, 0.4f, 0.4f, 1.0f),
		SDK::FLinearColor(0.06f, 0.06f, 0.06f, 1.0f),
		SDK::FLinearColor(0.08f, 0.08f, 0.08f, 1.0f),
		SDK::FLinearColor(0.12f, 0.12f, 0.12f, 1.0f),
		ptr
	);
}

std::wstring f_to_ws(const float& f)
{
	std::wostringstream woss;
	woss << std::fixed << std::setprecision(1) << f;
	return woss.str();
}

void menu::main()
{
	lable();
	base();
}

void menu::lable()
{
	render::draw_text(
		gvalue::engine->MediumFont,
		glanguage::lable,
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
		SDK::FLinearColor(0.2f, 0.2f, 0.2f, 1.0f)
	);
	render::fill_box(
		SDK::FVector2D(menu_x, menu_y),
		SDK::FVector2D(menu_w, menu_h),
		SDK::FLinearColor(0.01f, 0.01f, 0.01f, 1.0f)
	);

	render::fill_box(
		SDK::FVector2D(menu_x - 2, menu_y + menu_h + 8),
		SDK::FVector2D(menu_w + 4, 29),
		SDK::FLinearColor(0.3f, 0.1f, 0.0f, 1.0f)
	);
	render::fill_box(
		SDK::FVector2D(menu_x, menu_y + menu_h + 10), 
		SDK::FVector2D(menu_w, 25),
		SDK::FLinearColor(0.1f, 0.06f, 0.0f, 1.0f)
	);
	text_01(
		L"±¾ÐÞ¸ÄÆ÷ÓÀ¾ÃÃâ·Ñ¿ªÔ´£¬ÎÊÌâ·´À¡QQ£º3201548104",
		SDK::FVector2D(menu_x + 5, menu_y + menu_h + 15),
		false,
		false
	);

	menu_w = 400;
	left_bar();
	switch (page)
	{
	case e_page::visual:
		visual();
		break;
	case e_page::player:
		player();
		break;
	case e_page::item:
		item();
		break;
	case e_page::entity:
		entity();
		break;
	case e_page::level:
		level();
		break;
	case e_page::misc:
		misc();
		break;
	}
}

void menu::base_cursor()
{
	render::fill_box(
		SDK::FVector2D(gvalue::mouse_input.x - 2, gvalue::mouse_input.y - 2),
		SDK::FVector2D(4, 4),
		SDK::FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)
	);
}

void menu::left_bar()
{
	render::fill_box(
		SDK::FVector2D(menu_x, menu_y),
		SDK::FVector2D(80, menu_h),
		SDK::FLinearColor(0.02f, 0.02f, 0.02f, 1.0f)
	);

	render::draw_text(
		gvalue::engine->MediumFont,
		L"LHY1339",
		SDK::FVector2D(menu_x + 38, menu_y + menu_h - 20), 
		SDK::FVector2D(1.0f, 1.0f),
		SDK::FLinearColor(0.5f, 0.5f, 0.5f, 1.0f),
		1.0f,
		SDK::FLinearColor(0.0f, 0.0f, 0.0f, 0.0f),
		SDK::FVector2D(0.0f, 0.0f),
		true,
		true,
		false,
		SDK::FLinearColor(0.0f, 0.0f, 0.0f, 0.0f)
	);

	if (gui::button(SDK::FVector2D(menu_x, menu_y + menu_h - 30), SDK::FVector2D(80, 20)))
	{
		system("start https://github.com/LHY1339/cheat_escape_the_backrooms");
	}

	if (button_01(glanguage::visual, SDK::FVector2D(menu_x + 10, menu_y + 10), SDK::FVector2D(60, 20)))
	{
		page = e_page::visual;
	}

	if (button_01(glanguage::player, SDK::FVector2D(menu_x + 10, menu_y + 40), SDK::FVector2D(60, 20)))
	{
		page = e_page::player;
	}

	if (button_01(glanguage::item, SDK::FVector2D(menu_x + 10, menu_y + 70), SDK::FVector2D(60, 20)))
	{
		page = e_page::item;
	}

	if (button_01(glanguage::entity, SDK::FVector2D(menu_x + 10, menu_y + 100), SDK::FVector2D(60, 20)))
	{
		page = e_page::entity;
	}

	if (button_01(glanguage::level, SDK::FVector2D(menu_x + 10, menu_y + 130), SDK::FVector2D(60, 20)))
	{
		page = e_page::level;
	}

	if (button_01(glanguage::misc, SDK::FVector2D(menu_x + 10, menu_y + 160), SDK::FVector2D(60, 20)))
	{
		page = e_page::misc;
	}
}

void menu::visual()
{
	render::fill_box(
		SDK::FVector2D(menu_x + 90, menu_y + 10),
		SDK::FVector2D(menu_w - 100, 150), 
		SDK::FLinearColor(0.02f, 0.02f, 0.02f, 1.0f)
	);

	render::fill_box(
		SDK::FVector2D(menu_x + 90, menu_y + 170),
		SDK::FVector2D(160, 120),
		SDK::FLinearColor(0.02f, 0.02f, 0.02f, 1.0f)
	);

	render::fill_box(
		SDK::FVector2D(menu_x + 260, menu_y + 170),
		SDK::FVector2D(130, 120),
		SDK::FLinearColor(0.02f, 0.02f, 0.02f, 1.0f)
	);

	//up

	text_01(glanguage::player, SDK::FVector2D(menu_x + 100, menu_y + 40), false, false);
	text_01(glanguage::entity, SDK::FVector2D(menu_x + 100, menu_y + 70), false, false);
	text_01(glanguage::item, SDK::FVector2D(menu_x + 100, menu_y + 100), false, false);
	text_01(glanguage::interact, SDK::FVector2D(menu_x + 100, menu_y + 130), false, false);

	text_01(glanguage::enable, SDK::FVector2D(menu_x + 140, menu_y + 20), false, false);
	text_01(glanguage::box, SDK::FVector2D(menu_x + 180, menu_y + 20), false, false);
	text_01(glanguage::name, SDK::FVector2D(menu_x + 220, menu_y + 20), false, false);
	text_01(glanguage::distance, SDK::FVector2D(menu_x + 260, menu_y + 20), false, false);
	text_01(glanguage::line, SDK::FVector2D(menu_x + 300, menu_y + 20), false, false);
	text_01(glanguage::extent, SDK::FVector2D(menu_x + 340, menu_y + 20), false, false);

	check_box_01(SDK::FVector2D(menu_x + 145, menu_y + 40), &gvalue::visual_player.enable);
	check_box_01(SDK::FVector2D(menu_x + 185, menu_y + 40), &gvalue::visual_player.box);
	check_box_01(SDK::FVector2D(menu_x + 225, menu_y + 40), &gvalue::visual_player.name);
	check_box_01(SDK::FVector2D(menu_x + 265, menu_y + 40), &gvalue::visual_player.distance);
	check_box_01(SDK::FVector2D(menu_x + 305, menu_y + 40), &gvalue::visual_player.line);
	check_box_01(SDK::FVector2D(menu_x + 345, menu_y + 40), &gvalue::visual_player.extent);

	check_box_01(SDK::FVector2D(menu_x + 145, menu_y + 70), &gvalue::visual_entity.enable);
	check_box_01(SDK::FVector2D(menu_x + 185, menu_y + 70), &gvalue::visual_entity.box);
	check_box_01(SDK::FVector2D(menu_x + 225, menu_y + 70), &gvalue::visual_entity.name);
	check_box_01(SDK::FVector2D(menu_x + 265, menu_y + 70), &gvalue::visual_entity.distance);
	check_box_01(SDK::FVector2D(menu_x + 305, menu_y + 70), &gvalue::visual_entity.line);
	check_box_01(SDK::FVector2D(menu_x + 345, menu_y + 70), &gvalue::visual_entity.extent);

	check_box_01(SDK::FVector2D(menu_x + 145, menu_y + 100), &gvalue::visual_item.enable);
	check_box_01(SDK::FVector2D(menu_x + 185, menu_y + 100), &gvalue::visual_item.box);
	check_box_01(SDK::FVector2D(menu_x + 225, menu_y + 100), &gvalue::visual_item.name);
	check_box_01(SDK::FVector2D(menu_x + 265, menu_y + 100), &gvalue::visual_item.distance);
	check_box_01(SDK::FVector2D(menu_x + 305, menu_y + 100), &gvalue::visual_item.line);
	check_box_01(SDK::FVector2D(menu_x + 345, menu_y + 100), &gvalue::visual_item.extent);

	check_box_01(SDK::FVector2D(menu_x + 145, menu_y + 130), &gvalue::visual_interact.enable);
	check_box_01(SDK::FVector2D(menu_x + 185, menu_y + 130), &gvalue::visual_interact.box);
	check_box_01(SDK::FVector2D(menu_x + 225, menu_y + 130), &gvalue::visual_interact.name);
	check_box_01(SDK::FVector2D(menu_x + 265, menu_y + 130), &gvalue::visual_interact.distance);
	check_box_01(SDK::FVector2D(menu_x + 305, menu_y + 130), &gvalue::visual_interact.line);
	check_box_01(SDK::FVector2D(menu_x + 345, menu_y + 130), &gvalue::visual_interact.extent);

	//left

	if (button_01(std::wstring(glanguage::esp_distance + std::to_wstring(gvalue::visual_distance) + glanguage::meter).c_str(), SDK::FVector2D(menu_x + 100, menu_y + 180), SDK::FVector2D(140, 20)))
	{
		const int dist_list[10] = {
			10,30,50,80,100,
			300,500,800,1000,9999
		};

		for (int i = 0; i < 10; i++)
		{
			if (gvalue::visual_distance == dist_list[i])
			{
				gvalue::visual_distance = i < 9 ? dist_list[i + 1] : dist_list[0];
				break;
			}
		}
	}

	text_01(glanguage::draw_mesh, SDK::FVector2D(menu_x + 100, menu_y + 207), false, false);
	check_box_01(SDK::FVector2D(menu_x + 210, menu_y + 207), &gvalue::draw_mesh);

	if (button_01(std::wstring(glanguage::draw_mesh_distance + std::to_wstring(gvalue::draw_mesh_distance) + glanguage::meter).c_str(), SDK::FVector2D(menu_x + 100, menu_y + 230), SDK::FVector2D(140, 20)))
	{
		const int dist_list[10] = {
			10,30,50,80,100,
			300,500,800,1000,9999
		};

		for (int i = 0; i < 10; i++)
		{
			if (gvalue::draw_mesh_distance == dist_list[i])
			{
				gvalue::draw_mesh_distance = i < 9 ? dist_list[i + 1] : dist_list[0];
				break;
			}
		}
	}

	//right

	if (button_01(std::wstring(glanguage::fov + std::to_wstring(gvalue::fov)).c_str(), SDK::FVector2D(menu_x + 270, menu_y + 180), SDK::FVector2D(110, 20)))
	{
		const int fov_list[10] = {
			80,90,100,110,120,
			130,140,150,160,170
		};

		for (int i = 0; i < 10; i++)
		{
			if (gvalue::fov == fov_list[i])
			{
				gvalue::fov = i < 9 ? fov_list[i + 1] : fov_list[0];
				break;
			}
		}
	}

	text_01(glanguage::disable_post, SDK::FVector2D(menu_x + 270, menu_y + 207), false, false);
	check_box_01(SDK::FVector2D(menu_x + 350, menu_y + 207), &gvalue::disable_post);

	text_01(glanguage::third_person, SDK::FVector2D(menu_x + 270, menu_y + 232), false, false);
	check_box_01(SDK::FVector2D(menu_x + 340, menu_y + 232), &gvalue::third_person);

	if (button_01(std::wstring(glanguage::camera_len + std::to_wstring(gvalue::third_distance)).c_str(), SDK::FVector2D(menu_x + 270, menu_y + 255), SDK::FVector2D(110, 20)))
	{
		const int len_list[10] = {
			100,150,200,250,300,
			400,500,600,700,800
		};

		for (int i = 0; i < 10; i++)
		{
			if (gvalue::third_distance == len_list[i])
			{
				gvalue::third_distance = i < 9 ? len_list[i + 1] : len_list[0];
				break;
			}
		}
	}
}

void menu::player()
{
	render::fill_box(
		SDK::FVector2D(menu_x + 90, menu_y + 10),
		SDK::FVector2D(170, menu_h - 20), 
		SDK::FLinearColor(0.02f, 0.02f, 0.02f, 1.0f)
	);

	render::fill_box(
		SDK::FVector2D(menu_x + 270, menu_y + 10),
		SDK::FVector2D(120, menu_h - 20),
		SDK::FLinearColor(0.02f, 0.02f, 0.02f, 1.0f)
	);

	text_01(glanguage::inf_stamina, SDK::FVector2D(menu_x + 100, menu_y + 22), false, false);
	check_box_01(SDK::FVector2D(menu_x + 160, menu_y + 22), &gvalue::inf_stamina);

	text_01(glanguage::inf_sanity, SDK::FVector2D(menu_x + 100, menu_y + 52), false, false);
	check_box_01(SDK::FVector2D(menu_x + 170, menu_y + 52), &gvalue::inf_sanity);

	text_01(glanguage::auto_balance, SDK::FVector2D(menu_x + 100, menu_y + 82), false, false);
	check_box_01(SDK::FVector2D(menu_x + 160, menu_y + 82), &gvalue::no_balance);

	text_01(glanguage::ghost_mode, SDK::FVector2D(menu_x + 100, menu_y + 112), false, false);
	check_box_01(SDK::FVector2D(menu_x + 200, menu_y + 112), &gvalue::ghost_mode);

	if (button_01(std::wstring(glanguage::walk_speed + std::to_wstring(gvalue::walk_speed)).c_str(), SDK::FVector2D(menu_x + 100, menu_y + 140), SDK::FVector2D(150, 20)))
	{
		const int list[10] = {
			250,300,350,400,500,
			600,800,1000,2000,4000
		};

		for (int i = 0; i < 10; i++)
		{
			if (gvalue::walk_speed == list[i])
			{
				gvalue::walk_speed = i < 9 ? list[i + 1] : list[0];
				break;
			}
		}
	}

	if (button_01(std::wstring(glanguage::run_speed + std::to_wstring(gvalue::run_speed)).c_str(), SDK::FVector2D(menu_x + 100, menu_y + 170), SDK::FVector2D(150, 20)))
	{
		const int list[10] = {
			450,500,550,600,800,
			1000,2000,4000,8000,20000
		};

		for (int i = 0; i < 10; i++)
		{
			if (gvalue::run_speed == list[i])
			{
				gvalue::run_speed = i < 9 ? list[i + 1] : list[0];
				break;
			}
		}
	}

	if (button_01(std::wstring(glanguage::crouch_speed + std::to_wstring(gvalue::crouch_speed)).c_str(), SDK::FVector2D(menu_x + 100, menu_y + 200), SDK::FVector2D(150, 20)))
	{
		const int list[10] = {
			100,150,200,300,400,
			500,600,800,1000,2000
		};

		for (int i = 0; i < 10; i++)
		{
			if (gvalue::crouch_speed == list[i])
			{
				gvalue::crouch_speed = i < 9 ? list[i + 1] : list[0];
				break;
			}
		}
	}

	if (button_01(std::wstring(glanguage::all_speedup + f_to_ws(gvalue::speedup_multi)).c_str(), SDK::FVector2D(menu_x + 100, menu_y + 230), SDK::FVector2D(150, 20)))
	{
		const float list[10] = {
			1.0f,1.1f,1.2f,1.5f,2.0f,
			3.0f,5.0f,10.0f,15.0f,20.0f
		};

		for (int i = 0; i < 10; i++)
		{
			if (gvalue::speedup_multi == list[i])
			{
				gvalue::speedup_multi = i < 9 ? list[i + 1] : list[0];
				break;
			}
		}
	}

	text_01(glanguage::inf_jump, SDK::FVector2D(menu_x + 280, menu_y + 22), false, false);
	check_box_01(SDK::FVector2D(menu_x + 350, menu_y + 22), &gvalue::inf_jump);

	text_01(glanguage::fly_mode, SDK::FVector2D(menu_x + 280, menu_y + 52), false, false);
	check_box_01(SDK::FVector2D(menu_x + 350, menu_y + 52), &gvalue::fly_mode);

	if (button_01(std::wstring(glanguage::speed + f_to_ws(gvalue::fly_speed)).c_str(), SDK::FVector2D(menu_x + 280, menu_y + 80), SDK::FVector2D(100, 20)))
	{
		const float list[11] = {
			5.0f,10.0f,20.0f,30.0f,40.0f,
			50.0f,60.0f,70.0f,80.0f,90.0f,
			100.0f
		};

		for (int i = 0; i < 11; i++)
		{
			if (gvalue::fly_speed == list[i])
			{
				gvalue::fly_speed = i < 10 ? list[i + 1] : list[0];
				break;
			}
		}
	}

	text_01(glanguage::x_delete, SDK::FVector2D(menu_x + 280, menu_y + 112), false, false);
	check_box_01(SDK::FVector2D(menu_x + 350, menu_y + 112), &gvalue::x_delete);
}

void menu::item()
{
	menu_w = 380;

	render::fill_box(
		SDK::FVector2D(menu_x + 90, menu_y + 10),
		SDK::FVector2D(menu_w - 100, menu_h - 20), 
		SDK::FLinearColor(0.02f, 0.02f, 0.02f, 1.0f)
	);

	// line 1

	if (button_01(L"¹ûÖ­", SDK::FVector2D(menu_x + 100, menu_y + 20), SDK::FVector2D(80, 20)))
	{
		item::spawn(SDK::ABP_DroppedItem_Juice_C::StaticClass());
	}

	if (button_01(L"ÐÓÈÊË®", SDK::FVector2D(menu_x + 100, menu_y + 50), SDK::FVector2D(80, 20)))
	{
		item::spawn(SDK::ABP_DroppedItem_AlmondWater_C::StaticClass());
	}

	if (button_01(L"ÊÖµçÍ²", SDK::FVector2D(menu_x + 100, menu_y + 80), SDK::FVector2D(80, 20)))
	{
		item::spawn(SDK::ABP_DroppedItem_Flashlight_C::StaticClass());
	}

	if (button_01(L"ÒºÌ¬Í´¿à", SDK::FVector2D(menu_x + 100, menu_y + 110), SDK::FVector2D(80, 20)))
	{
		item::spawn(SDK::ABP_DroppedItem_LiquidPain_C::StaticClass());
	}

	if (button_01(L"ÄÜÁ¿°ô", SDK::FVector2D(menu_x + 100, menu_y + 140), SDK::FVector2D(80, 20)))
	{
		item::spawn(SDK::ABP_DroppedItem_EnergyBar_C::StaticClass());
	}

	if (button_01(L"Ç±Ë®Í·¿ø", SDK::FVector2D(menu_x + 100, menu_y + 170), SDK::FVector2D(80, 20)))
	{
		item::spawn(SDK::ABP_DroppedItem_DivingHelmet_C::StaticClass());
	}

	if (button_01(L"ÐÅºÅÇ¹", SDK::FVector2D(menu_x + 100, menu_y + 200), SDK::FVector2D(80, 20)))
	{
		item::spawn(SDK::ABP_DroppedItem_FlareGun_C::StaticClass());
	}

	if (button_01(L"Éþ×Ó", SDK::FVector2D(menu_x + 100, menu_y + 230), SDK::FVector2D(80, 20)))
	{
		item::spawn(SDK::ABP_DroppedItem_Rope_C::StaticClass());
	}

	if (button_01(L"¶Ô½²»ú", SDK::FVector2D(menu_x + 100, menu_y + 260), SDK::FVector2D(80, 20)))
	{
		item::spawn(SDK::ABP_DroppedItem_WalkieTalkie_C::StaticClass());
	}

	// line 2

	if (button_01(L"µç¾â", SDK::FVector2D(menu_x + 190, menu_y + 20), SDK::FVector2D(80, 20)))
	{
		item::spawn(SDK::ABP_DroppedItem_Chainsaw_C::StaticClass());
	}

	if (button_01(L"ÑÌ»¨", SDK::FVector2D(menu_x + 190, menu_y + 50), SDK::FVector2D(80, 20)))
	{
		item::spawn(SDK::ABP_DroppedItem_Firework_C::StaticClass());
	}

	if (button_01(L"»ÆÉ«Ó«¹â°ô", SDK::FVector2D(menu_x + 190, menu_y + 80), SDK::FVector2D(80, 20)))
	{
		item::spawn(SDK::ABP_DroppedItem_Glowstick_Yellow_C::StaticClass());
	}

	if (button_01(L"À¶É«Ó«¹â°ô", SDK::FVector2D(menu_x + 190, menu_y + 110), SDK::FVector2D(80, 20)))
	{
		item::spawn(SDK::ABP_DroppedItem_Glowstick_Blue_C::StaticClass());
	}

	if (button_01(L"ºìÉ«Ó«¹â°ô", SDK::FVector2D(menu_x + 190, menu_y + 140), SDK::FVector2D(80, 20)))
	{
		item::spawn(SDK::ABP_Item_Glowstick_Red_C::StaticClass());
	}

	if (button_01(L"Ó«¹â°ô", SDK::FVector2D(menu_x + 190, menu_y + 170), SDK::FVector2D(80, 20)))
	{
		item::spawn(SDK::ABP_DroppedItem_Glowstick_C::StaticClass());
	}

	if (button_01(L"É±³æÅçÎí", SDK::FVector2D(menu_x + 190, menu_y + 200), SDK::FVector2D(80, 20)))
	{
		item::spawn(SDK::ABP_DroppedItem_BugSpray_C::StaticClass());
	}

	if (button_01(L"Ïà»ú", SDK::FVector2D(menu_x + 190, menu_y + 230), SDK::FVector2D(80, 20)))
	{
		item::spawn(SDK::ABP_DroppedItem_Camera_C::StaticClass());
	}

	if (button_01(L"ÇË¹÷", SDK::FVector2D(menu_x + 190, menu_y + 260), SDK::FVector2D(80, 20)))
	{
		item::spawn(SDK::ABP_DroppedItem_Crowbar_C::StaticClass());
	}

	// line 3

	if (button_01(L"ÎÂ¶È¼Æ", SDK::FVector2D(menu_x + 280, menu_y + 20), SDK::FVector2D(80, 20)))
	{
		item::spawn(SDK::ABP_DroppedItem_Thermometer_C::StaticClass());
	}

	if (button_01(L"É¨ÃèÒÇ", SDK::FVector2D(menu_x + 280, menu_y + 50), SDK::FVector2D(80, 20)))
	{
		item::spawn(SDK::ABP_DroppedItem_LiDAR_C::StaticClass());
	}

	if (button_01(L"Íæ¾ß", SDK::FVector2D(menu_x + 280, menu_y + 80), SDK::FVector2D(80, 20)))
	{
		item::spawn(SDK::ABP_DroppedItem_Toy_C::StaticClass());
	}

	if (button_01(L"µ¶", SDK::FVector2D(menu_x + 280, menu_y + 110), SDK::FVector2D(80, 20)))
	{
		item::spawn(SDK::ABP_DroppedItem_Knife_C::StaticClass());
	}

	if (button_01(L"¹û¶³", SDK::FVector2D(menu_x + 280, menu_y + 140), SDK::FVector2D(80, 20)))
	{
		item::spawn(SDK::ABP_DroppedItem_Jelly_C::StaticClass());
	}

	if (button_01(L"¿ìËÙµç¾â", SDK::FVector2D(menu_x + 280, menu_y + 170), SDK::FVector2D(80, 20)))
	{
		item::spawn(SDK::ABP_DroppedItem_Chainsaw_Fast_C::StaticClass());
	}
}

void menu::entity()
{
	static std::vector<SDK::ACharacter*> pawn_list;
	static SDK::APawn* last_pawn = nullptr;

	auto flush_list = []()
		{
			pawn_list.clear();
			SDK::TArray<SDK::AActor*> actor_list;
			SDK::UGameplayStatics::GetAllActorsOfClass(gvalue::world, SDK::ACharacter::StaticClass(), &actor_list);
			for (SDK::AActor* actor : actor_list)
			{
				if (actor->IsA(SDK::ABP_Explorer_C::StaticClass())||
					actor->IsA(SDK::ABPCharacter_Demo_C::StaticClass()))
				{
					continue;
				}
				SDK::ACharacter* cur_pawn = static_cast<SDK::ACharacter*>(actor);
				pawn_list.emplace_back(cur_pawn);
			}
		};

	auto entity_box = [&](SDK::ACharacter* pawn, SDK::FVector2D pos)
		{
			if (!pawn)
			{
				return;
			}
			render::fill_box(pos, SDK::FVector2D(240, 30.0f), SDK::FLinearColor(0.02f, 0.02f, 0.02f, 1.0f));
			const std::wstring name = visual::find_name(SDK::UKismetStringLibrary::Conv_NameToString(pawn->Class->Name).ToWString());
			text_01(
				name.c_str(),
				pos + SDK::FVector2D(10.0f, 8.0f),
				false,
				false
			);

			if (button_01(L"¿ØÖÆ", pos + SDK::FVector2D(90, 5), SDK::FVector2D(40, 20)))
			{
				entity::poss(pawn);
			}

			if (button_01(L"È¡Ïû", pos + SDK::FVector2D(140, 5), SDK::FVector2D(40, 20)))
			{
				entity::unposs();
			}

			if (button_01(L"É¾³ý", pos + SDK::FVector2D(190, 5), SDK::FVector2D(40, 20)))
			{
				pawn->K2_DestroyActor();
				flush_list();
			}
		};

	if (last_pawn != gvalue::controller->Pawn)
	{
		pawn_list.clear();
		last_pawn = gvalue::controller->Pawn;
		flush_list();
	}

	render::fill_box(
		SDK::FVector2D(menu_x + 90, menu_y + 10),
		SDK::FVector2D(120, menu_h - 20),
		SDK::FLinearColor(0.02f, 0.02f, 0.02f, 1.0f)
	);

	render::fill_box(
		SDK::FVector2D(menu_x + 220, menu_y + 10),
		SDK::FVector2D(170, 130),
		SDK::FLinearColor(0.02f, 0.02f, 0.02f, 1.0f)
	);

	render::fill_box(
		SDK::FVector2D(menu_x + 420 - 2, menu_y - 2),
		SDK::FVector2D(260 + 4, 40 + pawn_list.size() * 40 + 4),
		SDK::FLinearColor(0.2f, 0.2f, 0.2f, 1.0f)
	);

	render::fill_box(
		SDK::FVector2D(menu_x + 420, menu_y),
		SDK::FVector2D(260, 40 + pawn_list.size() * 40),
		SDK::FLinearColor(0.01f, 0.01f, 0.01f, 1.0f)
	);

	//left

	if (button_01(L"¸ÉËÀËùÓÐÊµÌå", SDK::FVector2D(menu_x + 100, menu_y + 20), SDK::FVector2D(100, 20)))
	{
		entity::kill_all();
	}

	if (button_01(L"É¾³ýÏ¸¾ú", SDK::FVector2D(menu_x + 100, menu_y + 50), SDK::FVector2D(100, 20)))
	{
		entity::kill("Bacteria_Roaming_BP_C");
		entity::kill("Bacteria_BP_C");
	}

	if (button_01(L"É¾³ýÐ¦÷Ê", SDK::FVector2D(menu_x + 100, menu_y + 80), SDK::FVector2D(100, 20)))
	{
		entity::kill("Smiler_BP2_C");
		entity::kill("BP_Roaming_Smiler_C");
		entity::kill("BP_Smiler_Dash_C");
	}

	if (button_01(L"É¾³ýÅÉ¶Ô¿Í", SDK::FVector2D(menu_x + 100, menu_y + 110), SDK::FVector2D(100, 20)))
	{
		entity::kill("BP_RoamingPartygoer_Idle_C");
		entity::kill("BP_RoamingPartygoer_C");
		entity::kill("BP_RoamingPartygoer_Slow_C");
		entity::kill("Smiler_BP2_C");
		entity::kill("BP_DarkPartyGoer_C");
		entity::kill("BP_HidingPartyGoer_C");
	}

	if (button_01(L"É¾³ýËÀÍö·É¶ê", SDK::FVector2D(menu_x + 100, menu_y + 140), SDK::FVector2D(100, 20)))
	{
		entity::kill("BP_Moth_C");
		entity::kill("BP_Cave_Moth_C");
	}

	if (button_01(L"É¾³ýÇÔÆ¤Õß", SDK::FVector2D(menu_x + 100, menu_y + 170), SDK::FVector2D(100, 20)))
	{
		entity::kill("BP_SkinStealer_C");
		entity::kill("BP_SkinStealer_Cave_C");
		entity::kill("BP_SkinStealer_Level07_C");
		entity::kill("BP_SkinStealer_Hotel_C");
	}

	if (button_01(L"É¾³ýÁÔÈ®", SDK::FVector2D(menu_x + 100, menu_y + 200), SDK::FVector2D(100, 20)))
	{
		entity::kill("BP_Hound_C");
		entity::kill("BP_Hound_Hotel_C");
	}

	if (button_01(L"É¾³ý±¯Ê¬", SDK::FVector2D(menu_x + 100, menu_y + 230), SDK::FVector2D(100, 20)))
	{
		entity::kill("BP_Wretch_C");
		entity::kill("BP_Wretch_House_C");
	}

	//right

	if (button_01(L"Ï¸¾ú1", SDK::FVector2D(menu_x + 230, menu_y + 20), SDK::FVector2D(70, 20)))
	{
		entity::spawn(SDK::ABacteria_BP_C::StaticClass());
	}

	if (button_01(L"Ï¸¾ú2", SDK::FVector2D(menu_x + 230, menu_y + 50), SDK::FVector2D(70, 20)))
	{
		entity::spawn(SDK::ABacteria_Roaming_BP_C::StaticClass());
	}

	if (button_01(L"ÇÔÆ¤Õß1", SDK::FVector2D(menu_x + 230, menu_y + 80), SDK::FVector2D(70, 20)))
	{
		entity::spawn(SDK::ABP_SkinStealer_C::StaticClass());
	}

	if (button_01(L"ÇÔÆ¤Õß2", SDK::FVector2D(menu_x + 230, menu_y + 110), SDK::FVector2D(70, 20)))
	{
		entity::spawn(SDK::ABP_SkinStealer_Level07_C::StaticClass());
	}

	if (button_01(L"Ð¦÷Ê", SDK::FVector2D(menu_x + 310, menu_y + 20), SDK::FVector2D(70, 20)))
	{
		entity::spawn(SDK::ABP_Roaming_Smiler_C::StaticClass());
	}

	if (button_01(L"¶¯»­", SDK::FVector2D(menu_x + 310, menu_y + 50), SDK::FVector2D(70, 20)))
	{
		entity::spawn(SDK::ABP_Animation_C::StaticClass());
	}

	if (button_01(L"ËÀÍö·É¶ê", SDK::FVector2D(menu_x + 310, menu_y + 80), SDK::FVector2D(70, 20)))
	{
		entity::spawn(SDK::ABP_Moth_C::StaticClass());
	}

	if (button_01(L"ÁÔÈ®", SDK::FVector2D(menu_x + 310, menu_y + 110), SDK::FVector2D(70, 20)))
	{
		entity::spawn(SDK::ABP_Hound_C::StaticClass());
	}

	//control

	if (button_01(L"Ë¢ÐÂÊµÌåÁÐ±í", SDK::FVector2D(menu_x + 430, menu_y + 10), SDK::FVector2D(240, 20)))
	{
		flush_list();
	}

	for (int i = 0; i < pawn_list.size(); i++)
	{
		entity_box(pawn_list[i], SDK::FVector2D(menu_x + 430, menu_y + 40 * (i + 1)));
	}
}

void menu::level()
{
	menu_w = 470;

	render::fill_box(
		SDK::FVector2D(menu_x + 90, menu_y + 10),
		SDK::FVector2D(menu_w - 100, menu_h - 20),
		SDK::FLinearColor(0.02f, 0.02f, 0.02f, 1.0f)
	);

	//printf("%s\n", gvalue::world->Name.ToString().c_str());

	if (button_01(L"Level0", SDK::FVector2D(menu_x + 100, menu_y + 20), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel Level0", gvalue::controller);
	}

	if (button_01(L"Level1", SDK::FVector2D(menu_x + 100, menu_y + 50), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel TopFloor", gvalue::controller);
	}

	if (button_01(L"Level2", SDK::FVector2D(menu_x + 100, menu_y + 80), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel Pipes", gvalue::controller);
	}

	if (button_01(L"Level3", SDK::FVector2D(menu_x + 100, menu_y + 110), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel ElectricalStation", gvalue::controller);
	}

	if (button_01(L"Level4", SDK::FVector2D(menu_x + 100, menu_y + 140), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel Office", gvalue::controller);
	}

	if (button_01(L"Level5", SDK::FVector2D(menu_x + 100, menu_y + 170), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel Hotel", gvalue::controller);
	}

	if (button_01(L"LevelFun", SDK::FVector2D(menu_x + 100, menu_y + 200), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel LevelFun", gvalue::controller);
	}

	if (button_01(L"Level37", SDK::FVector2D(menu_x + 100, menu_y + 230), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel Poolrooms", gvalue::controller);
	}

	if (button_01(L"Level!", SDK::FVector2D(menu_x + 100, menu_y + 260), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel LevelRun", gvalue::controller);
	}

	//line 2

	if (button_01(L"LevelEnd", SDK::FVector2D(menu_x + 190, menu_y + 20), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel TheEnd", gvalue::controller);
	}

	if (button_01(L"Level94", SDK::FVector2D(menu_x + 190, menu_y + 50), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel Level94", gvalue::controller);
	}

	if (button_01(L"Level6", SDK::FVector2D(menu_x + 190, menu_y + 80), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel LightsOut", gvalue::controller);
	}

	if (button_01(L"Level7", SDK::FVector2D(menu_x + 190, menu_y + 110), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel OceanMap", gvalue::controller);
	}

	if (button_01(L"Level8", SDK::FVector2D(menu_x + 190, menu_y + 140), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel CaveLevel", gvalue::controller);
	}

	if (button_01(L"Level6", SDK::FVector2D(menu_x + 190, menu_y + 170), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel LightsOut", gvalue::controller);
	}

	if (button_01(L"Level0.11", SDK::FVector2D(menu_x + 190, menu_y + 200), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel Level05", gvalue::controller);
	}

	if (button_01(L"Level9", SDK::FVector2D(menu_x + 190, menu_y + 230), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel Level9", gvalue::controller);
	}

	if (button_01(L"Level10", SDK::FVector2D(menu_x + 190, menu_y + 260), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel Level10", gvalue::controller);
	}

	//line 3

	if (button_01(L"Level3999", SDK::FVector2D(menu_x + 280, menu_y + 20), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel Level3999", gvalue::controller);
	}

	if (button_01(L"Level0.2", SDK::FVector2D(menu_x + 280, menu_y + 50), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel Level07", gvalue::controller);
	}

	if (button_01(L"ÁãÊ³ÎÝ", SDK::FVector2D(menu_x + 280, menu_y + 80), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel Snackrooms", gvalue::controller);
	}

	if (button_01(L"Level!-!", SDK::FVector2D(menu_x + 280, menu_y + 110), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel LevelDash", gvalue::controller);
	}

	if (button_01(L"Level188", SDK::FVector2D(menu_x + 280, menu_y + 140), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel Level188_Expanded", gvalue::controller);
	}

	if (button_01(L"Level37.2", SDK::FVector2D(menu_x + 280, menu_y + 170), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel Poolrooms_Expanded", gvalue::controller);
	}

	if (button_01(L"LevelFun+", SDK::FVector2D(menu_x + 280, menu_y + 200), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel LevelFun_Expanded", gvalue::controller);
	}

	if (button_01(L"Level52", SDK::FVector2D(menu_x + 280, menu_y + 230), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel Level52", gvalue::controller);
	}

	if (button_01(L"Level55.1", SDK::FVector2D(menu_x + 280, menu_y + 260), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel TunnelLevel", gvalue::controller);
	}

	//line 4
	if (button_01(L"Level922", SDK::FVector2D(menu_x + 370, menu_y + 20), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel Level922", gvalue::controller);
	}

	if (button_01(L"Level974", SDK::FVector2D(menu_x + 370, menu_y + 50), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel Level974", gvalue::controller);
	}

	if (button_01(L"¹ý¶ÈÉú³¤", SDK::FVector2D(menu_x + 370, menu_y + 80), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel GraffitiLevel", gvalue::controller);
	}

	if (button_01(L"²ÝÎÝ", SDK::FVector2D(menu_x + 370, menu_y + 110), SDK::FVector2D(80, 20)))
	{
		SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, L"ServerTravel Grassrooms_Expanded", gvalue::controller);
	}
}

void menu::misc()
{
	render::fill_box(
		SDK::FVector2D(menu_x + 90, menu_y + 10),
		SDK::FVector2D(menu_w - 100, menu_h - 20),
		SDK::FLinearColor(0.02f, 0.02f, 0.02f, 1.0f)
	);

	if (button_01(L"¼ÓÔØ°´¼üÅäÖÃ", SDK::FVector2D(menu_x + 100, menu_y + 20), SDK::FVector2D(120, 20)))
	{
		config::load("C:/LHY1339/escape_the_backrooms/key.txt");
	}

	if (button_01(L"´ò¿ªÅäÖÃÎÄ¼þ", SDK::FVector2D(menu_x + 100, menu_y + 50), SDK::FVector2D(120, 20)))
	{
		system("start C:/LHY1339/escape_the_backrooms/key.txt");
	}
}
