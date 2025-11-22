#include "menu.h"

#include "render.h"
#include "_sdk.h"
#include "gvalue.h"
#include "gui.h"
#include "glanguage.h"
#include "item.h"
#include "entity.h"
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
		L"[默认配置下]\n按下 Ins（Insert）显示/隐藏菜单\n按下 Del（Delete）退出",
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
		L"本修改器永久免费开源，问题反馈QQ：3201548104",
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

#define SELECT_PAGE(_name,_page,_y_pos) \
if (button_01(L#_name, SDK::FVector2D(menu_x + 10, menu_y + _y_pos), SDK::FVector2D(60, 20))) \
{ \
	page = e_page::##_page; \
} \

	SELECT_PAGE(视觉, visual, 10);
	SELECT_PAGE(玩家, player, 40);
	SELECT_PAGE(物品, item, 70);
	SELECT_PAGE(实体, entity, 100);
	SELECT_PAGE(关卡, level, 130);
	SELECT_PAGE(杂项, misc, 160);
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

	check_box_01(SDK::FVector2D(menu_x + 145, menu_y + 40), &gvalue::esp_player.enable);
	check_box_01(SDK::FVector2D(menu_x + 185, menu_y + 40), &gvalue::esp_player.box);
	check_box_01(SDK::FVector2D(menu_x + 225, menu_y + 40), &gvalue::esp_player.name);
	check_box_01(SDK::FVector2D(menu_x + 265, menu_y + 40), &gvalue::esp_player.distance);
	check_box_01(SDK::FVector2D(menu_x + 305, menu_y + 40), &gvalue::esp_player.line);
	check_box_01(SDK::FVector2D(menu_x + 345, menu_y + 40), &gvalue::esp_player.extent);

	check_box_01(SDK::FVector2D(menu_x + 145, menu_y + 70), &gvalue::esp_entity.enable);
	check_box_01(SDK::FVector2D(menu_x + 185, menu_y + 70), &gvalue::esp_entity.box);
	check_box_01(SDK::FVector2D(menu_x + 225, menu_y + 70), &gvalue::esp_entity.name);
	check_box_01(SDK::FVector2D(menu_x + 265, menu_y + 70), &gvalue::esp_entity.distance);
	check_box_01(SDK::FVector2D(menu_x + 305, menu_y + 70), &gvalue::esp_entity.line);
	check_box_01(SDK::FVector2D(menu_x + 345, menu_y + 70), &gvalue::esp_entity.extent);

	check_box_01(SDK::FVector2D(menu_x + 145, menu_y + 100), &gvalue::esp_item.enable);
	check_box_01(SDK::FVector2D(menu_x + 185, menu_y + 100), &gvalue::esp_item.box);
	check_box_01(SDK::FVector2D(menu_x + 225, menu_y + 100), &gvalue::esp_item.name);
	check_box_01(SDK::FVector2D(menu_x + 265, menu_y + 100), &gvalue::esp_item.distance);
	check_box_01(SDK::FVector2D(menu_x + 305, menu_y + 100), &gvalue::esp_item.line);
	check_box_01(SDK::FVector2D(menu_x + 345, menu_y + 100), &gvalue::esp_item.extent);

	check_box_01(SDK::FVector2D(menu_x + 145, menu_y + 130), &gvalue::esp_interact.enable);
	check_box_01(SDK::FVector2D(menu_x + 185, menu_y + 130), &gvalue::esp_interact.box);
	check_box_01(SDK::FVector2D(menu_x + 225, menu_y + 130), &gvalue::esp_interact.name);
	check_box_01(SDK::FVector2D(menu_x + 265, menu_y + 130), &gvalue::esp_interact.distance);
	check_box_01(SDK::FVector2D(menu_x + 305, menu_y + 130), &gvalue::esp_interact.line);
	check_box_01(SDK::FVector2D(menu_x + 345, menu_y + 130), &gvalue::esp_interact.extent);

	//left

	if (button_01(std::wstring(L"透视距离：" + std::to_wstring(gvalue::esp_distance) + L"米").c_str(), SDK::FVector2D(menu_x + 100, menu_y + 180), SDK::FVector2D(140, 20)))
	{
		const int dist_list[10] = {
			10,30,50,80,100,
			300,500,800,1000,9999
		};

		for (int i = 0; i < 10; i++)
		{
			if (gvalue::esp_distance == dist_list[i])
			{
				gvalue::esp_distance = i < 9 ? dist_list[i + 1] : dist_list[0];
				break;
			}
		}
	}

	text_01(L"绘制网格体", SDK::FVector2D(menu_x + 100, menu_y + 207), false, false);
	check_box_01(SDK::FVector2D(menu_x + 210, menu_y + 207), &gvalue::draw_mesh);

	if (button_01(std::wstring(L"绘制距离：" + std::to_wstring(gvalue::draw_mesh_distance) + L"米").c_str(), SDK::FVector2D(menu_x + 100, menu_y + 230), SDK::FVector2D(140, 20)))
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

	if (button_01(std::wstring(L"长度：" + std::to_wstring(gvalue::third_distance)).c_str(), SDK::FVector2D(menu_x + 270, menu_y + 255), SDK::FVector2D(110, 20)))
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

	text_01(L"无限耐力", SDK::FVector2D(menu_x + 100, menu_y + 22), false, false);
	check_box_01(SDK::FVector2D(menu_x + 160, menu_y + 22), &gvalue::inf_stamina);

	text_01(L"无限San值", SDK::FVector2D(menu_x + 100, menu_y + 52), false, false);
	check_box_01(SDK::FVector2D(menu_x + 170, menu_y + 52), &gvalue::inf_sanity);

	text_01(L"自动平衡", SDK::FVector2D(menu_x + 100, menu_y + 82), false, false);
	check_box_01(SDK::FVector2D(menu_x + 160, menu_y + 82), &gvalue::no_balance);

	text_01(L"灵魂出窍(非房主)", SDK::FVector2D(menu_x + 100, menu_y + 112), false, false);
	check_box_01(SDK::FVector2D(menu_x + 210, menu_y + 112), &gvalue::ghost_mode);

	if (button_01(std::wstring(L"行走速度：" + std::to_wstring(gvalue::walk_speed)).c_str(), SDK::FVector2D(menu_x + 100, menu_y + 140), SDK::FVector2D(150, 20)))
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

	if (button_01(std::wstring(L"跑步速度：" + std::to_wstring(gvalue::run_speed)).c_str(), SDK::FVector2D(menu_x + 100, menu_y + 170), SDK::FVector2D(150, 20)))
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

	if (button_01(std::wstring(L"蹲伏速度：" + std::to_wstring(gvalue::crouch_speed)).c_str(), SDK::FVector2D(menu_x + 100, menu_y + 200), SDK::FVector2D(150, 20)))
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

	if (button_01(std::wstring(L"通用加速：" + f_to_ws(gvalue::speedup_multi)).c_str(), SDK::FVector2D(menu_x + 100, menu_y + 230), SDK::FVector2D(150, 20)))
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

	text_01(L"无限跳跃", SDK::FVector2D(menu_x + 280, menu_y + 22), false, false);
	check_box_01(SDK::FVector2D(menu_x + 350, menu_y + 22), &gvalue::inf_jump);

	text_01(L"飞行模式", SDK::FVector2D(menu_x + 280, menu_y + 52), false, false);
	check_box_01(SDK::FVector2D(menu_x + 350, menu_y + 52), &gvalue::fly_mode);

	if (button_01(std::wstring(L"速度：" + f_to_ws(gvalue::fly_speed)).c_str(), SDK::FVector2D(menu_x + 280, menu_y + 80), SDK::FVector2D(100, 20)))
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

	text_01(L"X键删除", SDK::FVector2D(menu_x + 280, menu_y + 112), false, false);
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

#define ITEM_SPAWN(name,cls,x_pos,y_pos) \
if (button_01(L#name, SDK::FVector2D(menu_x + x_pos, menu_y + y_pos), SDK::FVector2D(80, 20))) \
{ \
	item::spawn(SDK::cls::StaticClass()); \
} \

	// line 1
	ITEM_SPAWN(果汁, ABP_DroppedItem_Juice_C, 100, 20);
	ITEM_SPAWN(杏仁水, ABP_DroppedItem_AlmondWater_C, 100, 50);
	ITEM_SPAWN(手电筒, ABP_DroppedItem_Flashlight_C, 100, 80);
	ITEM_SPAWN(液态痛苦, ABP_DroppedItem_LiquidPain_C, 100, 110);
	ITEM_SPAWN(能量棒, ABP_DroppedItem_EnergyBar_C, 100, 140);
	ITEM_SPAWN(潜水头盔, ABP_DroppedItem_DivingHelmet_C, 100, 170);
	ITEM_SPAWN(信号枪, ABP_DroppedItem_FlareGun_C, 100, 200);
	ITEM_SPAWN(绳子, ABP_DroppedItem_Rope_C, 100, 230);
	ITEM_SPAWN(对讲机, ABP_DroppedItem_WalkieTalkie_C, 100, 260);

	// line 2
	ITEM_SPAWN(电锯, ABP_DroppedItem_Chainsaw_C, 190, 20);
	ITEM_SPAWN(烟花, ABP_DroppedItem_Firework_C, 190, 50);
	ITEM_SPAWN(黄色荧光棒, ABP_DroppedItem_Glowstick_Yellow_C, 190, 80);
	ITEM_SPAWN(蓝色荧光棒, ABP_DroppedItem_Glowstick_Blue_C, 190, 110);
	ITEM_SPAWN(红色荧光棒, ABP_Item_Glowstick_Red_C, 190, 140);
	ITEM_SPAWN(荧光棒, ABP_DroppedItem_Glowstick_C, 190, 170);
	ITEM_SPAWN(杀虫喷雾, ABP_DroppedItem_BugSpray_C, 190, 200);
	ITEM_SPAWN(相机, ABP_DroppedItem_Camera_C, 190, 230);
	ITEM_SPAWN(撬棍, ABP_DroppedItem_Crowbar_C, 190, 260);

	// line 3
	ITEM_SPAWN(温度计, ABP_DroppedItem_Thermometer_C, 280, 20);
	ITEM_SPAWN(扫描仪, ABP_DroppedItem_LiDAR_C, 280, 50);
	ITEM_SPAWN(玩具, ABP_DroppedItem_Toy_C, 280, 80);
	ITEM_SPAWN(刀, ABP_DroppedItem_Knife_C, 280, 110);
	ITEM_SPAWN(果冻, ABP_DroppedItem_Jelly_C, 280, 140);
	ITEM_SPAWN(快速电锯, ABP_DroppedItem_Chainsaw_Fast_C, 280, 170);
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

			if (button_01(L"控制", pos + SDK::FVector2D(140, 5), SDK::FVector2D(40, 20)))
			{
				entity::poss(pawn);
			}

			if (button_01(L"删除", pos + SDK::FVector2D(190, 5), SDK::FVector2D(40, 20)))
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
		SDK::FVector2D(260 + 4, 70 + pawn_list.size() * 40 + 4),
		SDK::FLinearColor(0.2f, 0.2f, 0.2f, 1.0f)
	);

	render::fill_box(
		SDK::FVector2D(menu_x + 420, menu_y),
		SDK::FVector2D(260, 70 + pawn_list.size() * 40),
		SDK::FLinearColor(0.01f, 0.01f, 0.01f, 1.0f)
	);

	//left

	if (button_01(L"干死所有实体", SDK::FVector2D(menu_x + 100, menu_y + 20), SDK::FVector2D(100, 20)))
	{
		entity::kill_all();
	}

	if (button_01(L"删除细菌", SDK::FVector2D(menu_x + 100, menu_y + 50), SDK::FVector2D(100, 20)))
	{
		entity::kill("Bacteria_Roaming_BP_C");
		entity::kill("Bacteria_BP_C");
	}

	if (button_01(L"删除笑魇", SDK::FVector2D(menu_x + 100, menu_y + 80), SDK::FVector2D(100, 20)))
	{
		entity::kill("Smiler_BP2_C");
		entity::kill("BP_Roaming_Smiler_C");
		entity::kill("BP_Smiler_Dash_C");
	}

	if (button_01(L"删除派对客", SDK::FVector2D(menu_x + 100, menu_y + 110), SDK::FVector2D(100, 20)))
	{
		entity::kill("BP_RoamingPartygoer_Idle_C");
		entity::kill("BP_RoamingPartygoer_C");
		entity::kill("BP_RoamingPartygoer_Slow_C");
		entity::kill("Smiler_BP2_C");
		entity::kill("BP_DarkPartyGoer_C");
		entity::kill("BP_HidingPartyGoer_C");
	}

	if (button_01(L"删除死亡飞蛾", SDK::FVector2D(menu_x + 100, menu_y + 140), SDK::FVector2D(100, 20)))
	{
		entity::kill("BP_Moth_C");
		entity::kill("BP_Cave_Moth_C");
	}

	if (button_01(L"删除窃皮者", SDK::FVector2D(menu_x + 100, menu_y + 170), SDK::FVector2D(100, 20)))
	{
		entity::kill("BP_SkinStealer_C");
		entity::kill("BP_SkinStealer_Cave_C");
		entity::kill("BP_SkinStealer_Level07_C");
		entity::kill("BP_SkinStealer_Hotel_C");
	}

	if (button_01(L"删除猎犬", SDK::FVector2D(menu_x + 100, menu_y + 200), SDK::FVector2D(100, 20)))
	{
		entity::kill("BP_Hound_C");
		entity::kill("BP_Hound_Hotel_C");
	}

	if (button_01(L"删除悲尸", SDK::FVector2D(menu_x + 100, menu_y + 230), SDK::FVector2D(100, 20)))
	{
		entity::kill("BP_Wretch_C");
		entity::kill("BP_Wretch_House_C");
	}

#define ENTITY_SPAWN(name,cls,x_pos,y_pos) \
if (button_01(L#name, SDK::FVector2D(menu_x + x_pos, menu_y + y_pos), SDK::FVector2D(70, 20))) \
{ \
	entity::spawn(SDK::cls::StaticClass()); \
} \

	ENTITY_SPAWN(细菌1, ABacteria_BP_C, 230, 20);
	ENTITY_SPAWN(细菌2, ABacteria_Roaming_BP_C, 230, 50);
	ENTITY_SPAWN(窃皮者1, ABP_SkinStealer_C, 230, 80);
	ENTITY_SPAWN(窃皮者2, ABP_SkinStealer_Level07_C, 230, 110);
	ENTITY_SPAWN(笑魇, ABP_Roaming_Smiler_C, 310, 20);
	ENTITY_SPAWN(动画, ABP_Animation_C, 310, 50);
	ENTITY_SPAWN(死亡飞蛾, ABP_Moth_C, 310, 80);
	ENTITY_SPAWN(猎犬, ABP_Hound_C, 310, 110);

	//control
	if (button_01(L"刷新实体列表", SDK::FVector2D(menu_x + 430, menu_y + 10), SDK::FVector2D(240, 20)))
	{
		flush_list();
	}

	if (button_01(L"取消控制实体", SDK::FVector2D(menu_x + 430, menu_y + 40), SDK::FVector2D(240, 20)))
	{
		entity::unposs();
	}

	for (int i = 0; i < pawn_list.size(); i++)
	{
		entity_box(pawn_list[i], SDK::FVector2D(menu_x + 430, 70 + menu_y + 40 * i));
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

#define LEVEL_CHANGE(name,lv_name,x_pos,y_pos) \
if (button_01(L#name, SDK::FVector2D(menu_x + x_pos, menu_y + y_pos), SDK::FVector2D(80, 20))) \
{ \
	const std::wstring cmd = std::wstring(L"ServerTravel ") + std::wstring(L#lv_name); \
	SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, cmd.c_str(), gvalue::controller); \
} \

	//line 1
	LEVEL_CHANGE(Level0, Level0, 100, 20);
	LEVEL_CHANGE(Level1, TopFloor, 100, 50);
	LEVEL_CHANGE(Level2, Pipes, 100, 80);
	LEVEL_CHANGE(Level3, ElectricalStation, 100, 110);
	LEVEL_CHANGE(Level4, Office, 100, 140);
	LEVEL_CHANGE(Level5, Hotel, 100, 170);
	LEVEL_CHANGE(LevelFun, LevelFun, 100, 200);
	LEVEL_CHANGE(Level37, Poolrooms, 100, 230);
	LEVEL_CHANGE(Level!, LevelRun, 100, 260);

	//line 2
	LEVEL_CHANGE(LevelEnd, TheEnd, 190, 20);
	LEVEL_CHANGE(Level94, Level94, 190, 50);
	LEVEL_CHANGE(Level6, LightsOut, 190, 80);
	LEVEL_CHANGE(Level7, OceanMap, 190, 110);
	LEVEL_CHANGE(Level8, CaveLevel, 190, 140);
	LEVEL_CHANGE(Level0.11, Level05, 190, 170);
	LEVEL_CHANGE(Level9, Level9, 190, 200);
	LEVEL_CHANGE(Level10, Level10, 190, 230);
	LEVEL_CHANGE(Level3999, Level3999, 190, 260);

	//line 3
	LEVEL_CHANGE(Level0.2, Level07, 280, 20);
	LEVEL_CHANGE(零食屋, Snackrooms, 280, 50);
	LEVEL_CHANGE(Level!-!, LevelDash, 280, 80);
	LEVEL_CHANGE(Level188, Level188_Expanded, 280, 110);
	LEVEL_CHANGE(Level37.2, Poolrooms_Expanded, 280, 140);
	LEVEL_CHANGE(LevelFun+, LevelFun_Expanded, 280, 170);
	LEVEL_CHANGE(Level52, Level52, 280, 200);
	LEVEL_CHANGE(Level55.1, TunnelLevel, 280, 230);
	LEVEL_CHANGE(Level922, Level922, 280, 260);

	//line 4
	LEVEL_CHANGE(Level974, Level974, 370, 20);
	LEVEL_CHANGE(过度生长, GraffitiLevel, 370, 50);
	LEVEL_CHANGE(草屋, Grassrooms_Expanded, 370, 80);
}

void menu::misc()
{
	render::fill_box(
		SDK::FVector2D(menu_x + 90, menu_y + 10),
		SDK::FVector2D(menu_w - 100, menu_h - 20),
		SDK::FLinearColor(0.02f, 0.02f, 0.02f, 1.0f)
	);

	if (button_01(L"加载按键配置", SDK::FVector2D(menu_x + 100, menu_y + 20), SDK::FVector2D(120, 20)))
	{
		config::load("C:/LHY1339/escape_the_backrooms/key.txt");
	}

	if (button_01(L"打开配置文件", SDK::FVector2D(menu_x + 100, menu_y + 50), SDK::FVector2D(120, 20)))
	{
		system("start C:/LHY1339/escape_the_backrooms/key.txt");
	}
}
