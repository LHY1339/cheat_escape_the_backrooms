#include "menu.h"

#include "render.h"
#include "_sdk.h"
#include "gvalue.h"
#include "gui.h"

enum class e_page
{
	visual,
	player,
	item,
	misc
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
		SDK::FLinearColor(0.2f, 0.2f, 0.2f, 1.0f)
	);
	render::fill_box(
		SDK::FVector2D(menu_x, menu_y),
		SDK::FVector2D(menu_w, menu_h),
		SDK::FLinearColor(0.01f, 0.01f, 0.01f, 1.0f)
	);

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
	auto button_01 = [](const UC::FString& text, const SDK::FVector2D& pos)
	{
		const SDK::FLinearColor normal_col(0.04f, 0.04f, 0.04f, 1.0f);
		const SDK::FLinearColor hover_col(0.06f, 0.06f, 0.06f, 1.0f);
		const SDK::FLinearColor press_col(0.1f, 0.1f, 0.1f, 1.0f);
		const SDK::FLinearColor text_col(1.0f, 1.0f, 1.0f, 1.0f);

		return gui::button_color_text(
			pos,
			SDK::FVector2D(60, 20),
			text,
			gvalue::engine->MediumFont,
			text_col,
			normal_col,
			hover_col,
			press_col
		);
	};

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
		system("start https://space.bilibili.com/669462200");
	}

	if (button_01(L"视觉", SDK::FVector2D(menu_x + 10, menu_y + 10)))
	{
		page = e_page::visual;
	}

	if (button_01(L"玩家", SDK::FVector2D(menu_x + 10, menu_y + 40)))
	{
		page = e_page::player;
	}

	if (button_01(L"物品", SDK::FVector2D(menu_x + 10, menu_y + 70)))
	{
		page = e_page::item;
	}

	if (button_01(L"杂项", SDK::FVector2D(menu_x + 10, menu_y + 100)))
	{
		page = e_page::misc;
	}
}

void menu::visual()
{
	auto text_01 = [](const UC::FString& text, const SDK::FVector2D& pos, const bool& mid_x, const bool& mid_y)
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
	};

	auto check_box_01 = [](const SDK::FVector2D& pos, bool* ptr)
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
	};

	auto button_01 = [](const UC::FString& text, const SDK::FVector2D& pos, const SDK::FVector2D& size)
	{
		const SDK::FLinearColor normal_col(0.04f, 0.04f, 0.04f, 1.0f);
		const SDK::FLinearColor hover_col(0.06f, 0.06f, 0.06f, 1.0f);
		const SDK::FLinearColor press_col(0.1f, 0.1f, 0.1f, 1.0f);
		const SDK::FLinearColor text_col(1.0f, 1.0f, 1.0f, 1.0f);

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
	};

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

	text_01(L"玩家", SDK::FVector2D(menu_x + 100, menu_y + 40), false, false);
	text_01(L"实体", SDK::FVector2D(menu_x + 100, menu_y + 70), false, false);
	text_01(L"物品", SDK::FVector2D(menu_x + 100, menu_y + 100), false, false);
	text_01(L"互动", SDK::FVector2D(menu_x + 100, menu_y + 130), false, false);

	text_01(L"启用", SDK::FVector2D(menu_x + 140, menu_y + 20), false, false);
	text_01(L"方框", SDK::FVector2D(menu_x + 180, menu_y + 20), false, false);
	text_01(L"名称", SDK::FVector2D(menu_x + 220, menu_y + 20), false, false);
	text_01(L"距离", SDK::FVector2D(menu_x + 260, menu_y + 20), false, false);
	text_01(L"连线", SDK::FVector2D(menu_x + 300, menu_y + 20), false, false);
	text_01(L"范围", SDK::FVector2D(menu_x + 340, menu_y + 20), false, false);

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

	if (button_01(std::wstring(L"透视距离：" + std::to_wstring(gvalue::visual_distance) + L"米").c_str(), SDK::FVector2D(menu_x + 100, menu_y + 180), SDK::FVector2D(140, 20)))
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

	text_01(L"绘制周围网格体", SDK::FVector2D(menu_x + 100, menu_y + 207), false, false);
	check_box_01(SDK::FVector2D(menu_x + 210, menu_y + 207), &gvalue::draw_mesh);

	if (button_01(std::wstring(L"网格体距离：" + std::to_wstring(gvalue::draw_mesh_distance) + L"米").c_str(), SDK::FVector2D(menu_x + 100, menu_y + 230), SDK::FVector2D(140, 20)))
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

	if (button_01(std::wstring(L"视野：" + std::to_wstring(gvalue::fov)).c_str(), SDK::FVector2D(menu_x + 270, menu_y + 180), SDK::FVector2D(110, 20)))
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

	text_01(L"禁用后处理", SDK::FVector2D(menu_x + 270, menu_y + 207), false, false);
	check_box_01(SDK::FVector2D(menu_x + 350, menu_y + 207), &gvalue::disable_post);

	text_01(L"第三人称", SDK::FVector2D(menu_x + 270, menu_y + 232), false, false);
	check_box_01(SDK::FVector2D(menu_x + 340, menu_y + 232), &gvalue::third_person);

	if (button_01(std::wstring(L"摇臂长度：" + std::to_wstring(gvalue::third_distance)).c_str(), SDK::FVector2D(menu_x + 270, menu_y + 255), SDK::FVector2D(110, 20)))
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
	render::draw_text(
		gvalue::engine->MediumFont,
		L"玩家",
		SDK::FVector2D(menu_x + 100.0f, menu_y + 10.0f),
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

void menu::item()
{
	render::draw_text(
		gvalue::engine->MediumFont,
		L"物品",
		SDK::FVector2D(menu_x + 100.0f, menu_y + 10.0f),
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

void menu::misc()
{
	render::draw_text(
		gvalue::engine->MediumFont,
		L"杂项",
		SDK::FVector2D(menu_x + 100.0f, menu_y + 10.0f),
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
