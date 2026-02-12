#include "menu.h"

#include "render.h"
#include "_sdk.h"
#include "gvalue.h"
#include "gui.h"
#include "entity.h"
#include "item.h"
#include "visual.h"
#include "config.h"
#include "color.h"
#include "resource.h"
#include "gdefine.h"
#include "kismet.h"
#include "session.h"

#include <format>
#include <fstream>
#include <filesystem>

enum class e_page
{
	visual,
	player,
	item,
	entity,
	level,
	misc,
};

class param
{
public:
	inline static SDK::FVector2D pos = SDK::FVector2D(100.0f, 100.0f);
	inline static SDK::FVector2D size = SDK::FVector2D(600.0f, 400.0f);
	inline static SDK::FVector2D drag_pos = SDK::FVector2D(0.0f, 0.0f);
	inline static bool is_drag = false;

	inline static e_page page = e_page::visual;

	inline static std::vector<SDK::ABPCharacter_Demo_C*> player_list;
	inline static std::vector<SDK::ACharacter*> entity_list;

	inline static SDK::UTexture2D* t_visual = nullptr;
	inline static SDK::UTexture2D* t_visual_newyear = nullptr;
};

class function
{
public:
	static SDK::FVector2D scale()
	{
		return SDK::FVector2D(gvalue::menu_scale, gvalue::menu_scale);
	}

	static void set_font(const int& size)
	{
		gvalue::engine->TinyFont->LegacyFontSize = size;
	}

	static SDK::FVector2D attach(const float& ref_x, const float& ref_y)
	{
		return SDK::FVector2D(param::pos.X + ref_x, param::pos.Y + ref_y);
	}

	static bool button_color(const std::string& name, SDK::FVector2D pos, SDK::FVector2D size, bool is_attach = true)
	{
		pos *= scale();
		size *= scale();
		return gui::button_color(
			name,
			is_attach ? attach(pos.X, pos.Y) : pos, 
			SDK::FVector2D(size.X, size.Y), 
			color::get()->normal_col,
			color::get()->hover_col,
			color::get()->press_col
		);
	}

	static bool button_text(const std::string& name, SDK::FVector2D pos, SDK::FVector2D size, const SDK::FString& str, bool is_attach = true)
	{
		pos *= scale();
		size *= scale();
		return gui::button_text(
			name,
			is_attach ? attach(pos.X, pos.Y) : pos,
			SDK::FVector2D(size.X, size.Y),
			str,
			gvalue::engine->TinyFont,
			color::get()->text_col,
			color::get()->text_col,
			color::get()->text_col,
			SDK::FVector2D(1.0f, 1.0f)
		);
	}

	static bool button_color_text(const std::string& name, SDK::FVector2D pos, SDK::FVector2D size, const SDK::FString& str, bool is_attach = true)
	{
		pos *= scale();
		size *= scale();
		return gui::button_color_text(
			name,
			is_attach ? attach(pos.X, pos.Y) : pos,
			SDK::FVector2D(size.X, size.Y),
			str,
			gvalue::engine->TinyFont,
			color::get()->text_col,
			color::get()->normal_col,
			color::get()->hover_col,
			color::get()->press_col,
			SDK::FVector2D(1.0f, 1.0f)
		);
	}

	static void check_box(const std::string& name, SDK::FVector2D pos, SDK::FVector2D size, SDK::FVector2D check_size, bool* ptr, bool is_attach = true)
	{
		pos *= scale();
		size *= scale();
		check_size *= scale();
		gui::check_box(
			name,
			is_attach ? attach(pos.X, pos.Y) : pos,
			SDK::FVector2D(size.X, size.Y),
			SDK::FVector2D(check_size.X, check_size.Y),
			color::get()->check_col,
			color::get()->normal_col,
			color::get()->hover_col,
			color::get()->press_col,
			ptr
		);
	}

	static void drag_bar(const std::string& name, SDK::FVector2D pos, SDK::FVector2D size, SDK::FVector2D bar_size, float* ptr, bool is_attach = true)
	{
		pos *= scale();
		size *= scale();
		bar_size *= scale();
		gui::drag_bar(
			name,
			is_attach ? attach(pos.X, pos.Y) : pos,
			SDK::FVector2D(size.X, size.Y),
			SDK::FVector2D(bar_size.X, bar_size.Y),
			color::get()->bar_col,
			color::get()->normal_col,
			color::get()->hover_col,
			color::get()->press_col,
			ptr
		);
	}

	static void text(SDK::FVector2D pos, const SDK::FString& str, const bool& mid_x = false, const bool& mid_y = false, bool is_attach = true)
	{
		pos *= scale();
		render::draw_text(
			gvalue::engine->TinyFont,
			str,
			is_attach ? attach(pos.X, pos.Y) : pos,
			SDK::FVector2D(1.0f, 1.0f), 
			color::get()->text_col,
			1.0f,
			SDK::FLinearColor(0.0f, 0.0f, 0.0f, 0.0f),
			SDK::FVector2D(0.0f, 0.0f),
			mid_x,
			mid_y,
			false,
			SDK::FLinearColor(0.0f, 0.0f, 0.0f, 0.0f)
		);
	}

	static void pice(SDK::FVector2D pos, SDK::FVector2D size)
	{
		pos *= scale();
		size *= scale();
		render::fill_box(
			attach(pos.X, pos.Y),
			size,
			color::get()->pice_col
		);
	}
};

menu* menu::get()
{
	static menu inst;
	return &inst;
}

void unzip_png(const LPCWSTR& name, const char* file_path)
{
	HRSRC h_res = FindResource(gvalue::dll_inst, name, L"PNG");
	HGLOBAL h_data = LoadResource(gvalue::dll_inst, h_res);
	void* p_data = LockResource(h_data);
	DWORD size = SizeofResource(gvalue::dll_inst, h_res);
	std::ofstream out(file_path, std::ios::binary);
	out.write(reinterpret_cast<char*>(p_data), size);
	out.close();
}

void menu::init()
{
	unzip_png(MAKEINTRESOURCE(IDB_PNG1), "C:\\LHY1339\\escape_the_backrooms\\visual.png");
	unzip_png(MAKEINTRESOURCE(IDB_PNG2), "C:\\LHY1339\\escape_the_backrooms\\visual_newyear.png");

	param::t_visual = SDK::UKismetRenderingLibrary::ImportFileAsTexture2D(gvalue::world, L"C:/LHY1339/escape_the_backrooms/visual.png");
	param::t_visual_newyear = SDK::UKismetRenderingLibrary::ImportFileAsTexture2D(gvalue::world, L"C:/LHY1339/escape_the_backrooms/visual_newyear.png");
}

void menu::main()
{
	if (gvalue::menu_open)
	{
		color::get()->flush_color();
		pre_base();
		base();
		cursor();
	}
	lable();
}

void menu::lable()
{
	if (!gvalue::draw_lable)
	{
		return;
	}

	function::set_font(12);

	const std::wstring lab_text =
		std::wstring(L"按下 Ins（Insert）或 F1 显示/隐藏菜单\n按下 Del（Delete）关闭修改器\n") +
		std::wstring(L"按下 Tab 打开快捷菜单\n\n可在 [杂项] 菜单中关闭此提示");

	render::draw_text(
		gvalue::engine->TinyFont,
		lab_text.c_str(),
		SDK::FVector2D(10.0f, 10.0f),
		SDK::FVector2D(1.0f, 1.0f),
		SDK::FLinearColor(1.0f, 1.0f, 1.0f, 1.0f),
		1.0f,
		SDK::FLinearColor(0.0f, 0.0f, 0.0f, 0.0f),
		SDK::FVector2D(0.0f, 0.0f),
		false,
		false,
		true,
		SDK::FLinearColor(0.0f, 0.0f, 0.0f, 1.0f)
	);
}

void menu::pre_base()
{
	SDK::FVector2D size = param::size * function::scale();
	gui::drag(
		param::pos,
		size,
		param::drag_pos, 
		param::is_drag
	);
}

void menu::base()
{
	function::set_font((int)12 * gvalue::menu_scale);

	render::fill_box(
		SDK::FVector2D(param::pos.X - 2 * gvalue::menu_scale, param::pos.Y - 2 * gvalue::menu_scale),
		SDK::FVector2D(param::size.X + 4, param::size.Y + 4) * function::scale(),
		color::get()->outline_col
	);
	render::fill_box(
		SDK::FVector2D(param::pos.X, param::pos.Y),
		SDK::FVector2D(param::size.X, param::size.Y) * function::scale(),
		color::get()->back_col
	);

	{
		render::fill_box(
			SDK::FVector2D(param::pos.X - 2 * gvalue::menu_scale, param::pos.Y + (param::size.Y + 8) * gvalue::menu_scale),
			SDK::FVector2D((param::size.X + 4) * gvalue::menu_scale, 39 * gvalue::menu_scale), 
			SDK::FLinearColor(0.3f, 0.1f, 0.0f, 1.0f)
		);
		render::fill_box(
			SDK::FVector2D(param::pos.X, param::pos.Y + (param::size.Y + 10) * gvalue::menu_scale),
			SDK::FVector2D(param::size.X * gvalue::menu_scale, 35 * gvalue::menu_scale), 
			SDK::FLinearColor(0.1f, 0.06f, 0.0f, 1.0f)
		);
		function::text(SDK::FVector2D(10, param::size.Y + 18), L"本修改器永久免费开源，问题反馈QQ群：1071845133");
	}

	if (gvalue::max_version != VERSION && gvalue::max_version != "")
	{
		render::fill_box(
			SDK::FVector2D(param::pos.X - 2 * gvalue::menu_scale, param::pos.Y + (param::size.Y + 58) * gvalue::menu_scale),
			SDK::FVector2D((170 + 4) * gvalue::menu_scale, 39 * gvalue::menu_scale), 
			SDK::FLinearColor(0.3f, 0.1f, 0.0f, 1.0f)
		);
		render::fill_box(
			SDK::FVector2D(param::pos.X, param::pos.Y + (param::size.Y + 60) * gvalue::menu_scale),
			SDK::FVector2D(170 * gvalue::menu_scale, 35 * gvalue::menu_scale),
			SDK::FLinearColor(0.1f, 0.06f, 0.0f, 1.0f)
		);
		function::text(SDK::FVector2D(10, param::size.Y + 68), L"有新版本可以下载！");
	}

	param::size = SDK::FVector2D(600, 400);

#define ETB_SWITCH(_name_) \
case e_page::_name_: \
	_name_(); \
	break; 

	switch (param::page)
	{
		ETB_SWITCH(visual);
	case e_page::player:
		__try
		{
			player();
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			param::player_list.clear();
			printf("player error : %d\n", GetExceptionCode());
		}
		break;
		ETB_SWITCH(item);
	case e_page::entity:
		__try
		{
			entity();
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			param::entity_list.clear();
			printf("entity error : %d\n", GetExceptionCode());
		}
		break;
		ETB_SWITCH(level);
		ETB_SWITCH(misc);
	}

	left();

#undef ETB_SWITCH
}

void menu::cursor()
{
	render::fill_box(
		SDK::FVector2D(gvalue::mouse.x - 3, gvalue::mouse.y - 3),
		SDK::FVector2D(6, 6),
		color::get()->normal_col
	);
	render::fill_box(
		SDK::FVector2D(gvalue::mouse.x - 2, gvalue::mouse.y - 2),
		SDK::FVector2D(4, 4),
		color::get()->text_col
	);
}

void menu::left()
{
	function::pice(SDK::FVector2D(0, 0), SDK::FVector2D(100, param::size.Y));

	static float current_y = 10.0f;
	const float target_y = 10 + (int)param::page * 40;
	current_y = current_y + (target_y - current_y) * 15 * gvalue::delta_time;
	render::fill_box(function::attach(10 * gvalue::menu_scale, current_y * gvalue::menu_scale), SDK::FVector2D(80, 30) * gvalue::menu_scale, color::get()->normal_col);

#define ETB_BUTTON(_page_,_name_,_ypos_) \
if (function::button_text(#_page_, SDK::FVector2D(10, _ypos_), SDK::FVector2D(80, 30), L#_name_)) \
{ \
	param::page = e_page::_page_; \
}

	ETB_BUTTON(visual, 视觉, 10);
	ETB_BUTTON(player, 玩家, 50);
	ETB_BUTTON(item, 物品, 90);
	ETB_BUTTON(entity, 实体, 130);
	ETB_BUTTON(level, 关卡, 170);
	ETB_BUTTON(misc, 杂项, 210);

#undef ETB_BUTTON

	if (function::button_text("", SDK::FVector2D(10, param::size.Y - 40), SDK::FVector2D(80, 30), L"LHY1339 "))
	{
		system("start https://afdian.com/a/lhy1339");
	}
}

void menu::visual()
{
	function::pice(SDK::FVector2D(110, 10), SDK::FVector2D(param::size.X - 120, 210));
	function::pice(SDK::FVector2D(110, 230), SDK::FVector2D(200, param::size.Y - 240));
	function::pice(SDK::FVector2D(320, 230), SDK::FVector2D(270, param::size.Y - 240));

#define ETB_TEXT(_x_,_text_) \
function::text(SDK::FVector2D(_x_ - 5, 20), L#_text_);

	ETB_TEXT(180, 启用);
	ETB_TEXT(240, 方框);
	ETB_TEXT(300, 名称);
	ETB_TEXT(360, 距离);
	ETB_TEXT(420, 连线);
	ETB_TEXT(480, 范围);

#undef ETB_TEXT

#define ETB_TEXT(_y_,_text_) \
function::text(SDK::FVector2D(120, _y_), L#_text_);

	ETB_TEXT(60, 玩家);
	ETB_TEXT(100, 实体);
	ETB_TEXT(140, 物品);
	ETB_TEXT(180, 互动);

#undef ETB_TEXT

#define ETB_CHECK(_y_,_type_) \
	function::check_box(" ", SDK::FVector2D(180, _y_), SDK::FVector2D(20, 20), SDK::FVector2D(10, 10), &gvalue::esp_##_type_.enable); \
	function::check_box(" ", SDK::FVector2D(240, _y_), SDK::FVector2D(20, 20), SDK::FVector2D(10, 10), &gvalue::esp_##_type_.box); \
	function::check_box(" ", SDK::FVector2D(300, _y_), SDK::FVector2D(20, 20), SDK::FVector2D(10, 10), &gvalue::esp_##_type_.name); \
	function::check_box(" ", SDK::FVector2D(360, _y_), SDK::FVector2D(20, 20), SDK::FVector2D(10, 10), &gvalue::esp_##_type_.distance); \
	function::check_box(" ", SDK::FVector2D(420, _y_), SDK::FVector2D(20, 20), SDK::FVector2D(10, 10), &gvalue::esp_##_type_.line); \
	function::check_box(" ", SDK::FVector2D(480, _y_), SDK::FVector2D(20, 20), SDK::FVector2D(10, 10), &gvalue::esp_##_type_.extent);

	ETB_CHECK(60, player);
	ETB_CHECK(100, entity);
	ETB_CHECK(140, item);
	ETB_CHECK(180, interact);

#undef ETB_CHECK

	{
		const int dist = 1000 * gvalue::esp_distance;
		const std::wstring wstr = L"透视距离：" + std::to_wstring(dist) + L"米";
		function::text(SDK::FVector2D(120, 240), wstr.c_str());
		function::drag_bar("visual_distance", SDK::FVector2D(120, 270), SDK::FVector2D(180, 20), SDK::FVector2D(10, 20), &gvalue::esp_distance);
	}

	{
		function::check_box(" ", SDK::FVector2D(120, 300), SDK::FVector2D(20, 20), SDK::FVector2D(10, 10), &gvalue::draw_mesh);
		function::text(SDK::FVector2D(150, 300), L"绘制周围网格体");
	}

	{
		const int dist = 1000 * gvalue::draw_mesh_distance;
		const std::wstring wstr = L"网格体距离：" + std::to_wstring(dist) + L"米";
		function::text(SDK::FVector2D(120, 330), wstr.c_str());
		function::drag_bar("draw_mesh_distance", SDK::FVector2D(120, 360), SDK::FVector2D(180, 20), SDK::FVector2D(10, 20), &gvalue::draw_mesh_distance);
	}

	{
		const int fov = 180 * gvalue::fov;
		const std::wstring wstr = L"视野：" + std::to_wstring(fov);
		function::text(SDK::FVector2D(330, 240), wstr.c_str());
		function::drag_bar("fov", SDK::FVector2D(420, 240), SDK::FVector2D(160, 20), SDK::FVector2D(10, 20), &gvalue::fov);
	}

	{
		function::check_box(" ", SDK::FVector2D(330, 270), SDK::FVector2D(20, 20), SDK::FVector2D(10, 10), &gvalue::disable_post);
		function::text(SDK::FVector2D(360, 270), L"禁用后期处理");
	}

	{
		function::check_box(" ", SDK::FVector2D(330, 300), SDK::FVector2D(20, 20), SDK::FVector2D(10, 10), &gvalue::third_person);
		function::text(SDK::FVector2D(360, 300), L"第三人称");
	}

	{
		function::text(SDK::FVector2D(330, 330), L"X");
		function::drag_bar("cam_x", SDK::FVector2D(350, 330), SDK::FVector2D(60, 20), SDK::FVector2D(10, 20), &gvalue::cam_x);

		function::text(SDK::FVector2D(420, 330), L"Y");
		function::drag_bar("cam_y", SDK::FVector2D(440, 330), SDK::FVector2D(60, 20), SDK::FVector2D(10, 20), &gvalue::cam_y);

		if (function::button_color_text(" ", SDK::FVector2D(520, 330), SDK::FVector2D(60, 20), L"重置"))
		{
			gvalue::cam_x = 0.5f;
			gvalue::cam_y = 0.5f;
			gvalue::cam_distance = 0.2f;
		}

		const int cam_distance = 1000 * gvalue::cam_distance;
		const std::wstring wstr = L"距离：" + std::to_wstring(cam_distance);
		function::text(SDK::FVector2D(330, 360), wstr.c_str());
		function::drag_bar("cam_distance", SDK::FVector2D(430, 360), SDK::FVector2D(150, 20), SDK::FVector2D(10, 20), &gvalue::cam_distance);
	}

	render::fill_box(
		function::attach((param::size.X + 18) * gvalue::menu_scale, -2 * gvalue::menu_scale), 
		SDK::FVector2D(404, 404)* function::scale(), 
		color::get()->outline_col
	);

	render::fill_box(
		function::attach((param::size.X + 20)* gvalue::menu_scale, 0), 
		SDK::FVector2D(400, 400)* function::scale(),
		color::get()->back_col
	);

	function::pice(SDK::FVector2D(param::size.X + 30, 10), SDK::FVector2D(380, 380));

	gvalue::canvas->K2_DrawTexture(
		gvalue::new_year_color ? param::t_visual_newyear : param::t_visual,
		function::attach(640 * gvalue::menu_scale, 20 * gvalue::menu_scale),
		SDK::FVector2D(360, 360)* function::scale(),
		SDK::FVector2D(0, 0),
		SDK::FVector2D(1, 1),
		SDK::FLinearColor(1.0f, 1.0f, 1.0f, 1.0f),
		SDK::EBlendMode::BLEND_Translucent,
		0.0f,
		SDK::FVector2D(0, 0)
	);

	{
		auto show_esp = [&](const s_esp& esp, SDK::FVector2D pos, SDK::FVector2D size, const SDK::FLinearColor& color,const std::wstring& name)
			{
				pos *= function::scale();
				size *= function::scale();

				if (!esp.enable)
				{
					return;
				}

				const SDK::FVector2D real_pos = function::attach((param::size.X + 20) * gvalue::menu_scale, 0) + pos;

				if (esp.box||esp.extent)
				{
					render::draw_box(real_pos, size, 1.0f, color);
				}
				if (esp.line)
				{
					render::draw_line(
						SDK::FVector2D(param::pos.X + param::size.X + 215, param::pos.Y + 10), 
						SDK::FVector2D(real_pos.X + size.X / 2, real_pos.Y),
						1.0f,
						color
					);
				}
				std::wstring draw_str;
				if (esp.name)
				{
					draw_str += name + L"\n";
				}
				if (esp.distance)
				{
					draw_str += L"10米\n";
				}
				render::draw_text(
					gvalue::engine->MediumFont,
					draw_str.c_str(),
					SDK::FVector2D(real_pos.X + size.X + 5.0f, real_pos.Y),
					SDK::FVector2D(1.0f, 1.0f),
					color,
					1.0f,
					SDK::FLinearColor(0.0f, 0.0f, 0.0f, 0.0f),
					SDK::FVector2D(0.0f, 0.0f),
					false,
					false,
					false,
					SDK::FLinearColor(0.0f, 0.0f, 0.0f, 0.0f)
				);
			};

		if (gvalue::new_year_color)
		{
			show_esp(
				gvalue::esp_entity,
				SDK::FVector2D(250, 70),
				SDK::FVector2D(100, 210),
				SDK::FLinearColor(1.0f, 0.0f, 0.0f, 1.0f),
				L"年兽夕"
			);
			show_esp(gvalue::esp_item, SDK::FVector2D(275, 290), SDK::FVector2D(70, 60), SDK::FLinearColor(0.0f, 1.0f, 1.0f, 1.0f), L"红包");
			show_esp(gvalue::esp_interact, SDK::FVector2D(40, 20), SDK::FVector2D(60, 180), SDK::FLinearColor(1.0f, 1.0f, 0.0f, 1.0f), L"鞭炮");
			show_esp(gvalue::esp_player, SDK::FVector2D(110, 40), SDK::FVector2D(130, 320), SDK::FLinearColor(0.0f, 1.0f, 0.0f, 1.0f), L"门神：神荼");
		}
		else
		{
			show_esp(gvalue::esp_entity, SDK::FVector2D(220, 80), SDK::FVector2D(100, 140), SDK::FLinearColor(1.0f, 0.0f, 0.0f, 1.0f), L"棍母");
			show_esp(gvalue::esp_item, SDK::FVector2D(235, 270), SDK::FVector2D(80, 80), SDK::FLinearColor(0.0f, 1.0f, 1.0f, 1.0f), L"咕咕嘎嘎");
			show_esp(gvalue::esp_interact, SDK::FVector2D(35, 120), SDK::FVector2D(100, 250), SDK::FLinearColor(1.0f, 1.0f, 0.0f, 1.0f), L"吉他");
			show_esp(gvalue::esp_player, SDK::FVector2D(110, 40), SDK::FVector2D(130, 320), SDK::FLinearColor(0.0f, 1.0f, 0.0f, 1.0f), L"玩家：千早爱音");
		}
	}
}

void menu::player()
{
	function::pice(SDK::FVector2D(110, 10), SDK::FVector2D(200, param::size.Y - 20));
	function::pice(SDK::FVector2D(320, 10), SDK::FVector2D(270, 200));
	function::pice(SDK::FVector2D(320, 220), SDK::FVector2D(270, param::size.Y - 230));

#define ETB_CHECK(_y_,_name_,_param_) \
{ \
	function::check_box(" ", SDK::FVector2D(120, _y_), SDK::FVector2D(20, 20), SDK::FVector2D(10, 10), &gvalue::_param_); \
	function::text(SDK::FVector2D(150, _y_), L#_name_); \
}

	ETB_CHECK(20, 无限耐力, inf_energy);
	ETB_CHECK(50, 无限SAN值[房主], inf_san);
	ETB_CHECK(80, 无敌模式[房主], inf_health);
	ETB_CHECK(110, 灵魂出窍[成员], ghost_mode);
	ETB_CHECK(140, 自动平衡, auto_balance);
	ETB_CHECK(170, 无限跳跃[房主], inf_jump);
	ETB_CHECK(200, 飞天遁地[房主], fly_mode);

	{
		const int speed = 100 * gvalue::fly_speed;
		const std::wstring wstr = L"飞行速度：" + std::to_wstring(speed);
		function::text(SDK::FVector2D(120, 230), wstr.c_str());
		function::drag_bar("fly_speed", SDK::FVector2D(120, 260), SDK::FVector2D(180, 20), SDK::FVector2D(10, 20), &gvalue::fly_speed);
	}

	ETB_CHECK(290, X键删除[房主], x_delete);
	ETB_CHECK(320, 右键移动[房主], rb_move);

#undef ETB_CHECK

#define ETB_DRAG(_y_,_max_,_text_,_param_) \
{ \
	const int speed = _max_ * gvalue::_param_; \
	const std::wstring wstr = L#_text_ + std::to_wstring(speed); \
	function::text(SDK::FVector2D(330, _y_), wstr.c_str()); \
	function::drag_bar(#_param_, SDK::FVector2D(460, _y_), SDK::FVector2D(120, 20), SDK::FVector2D(10, 20), &gvalue::_param_); \
}

	ETB_DRAG(20, 2750, 行走速度：, walk_speed);
	ETB_DRAG(50, 5500, 跑步速度：, run_speed);

	{
		const float speed = 10 * gvalue::global_speed;
		const std::wstring wstr = L"全局加速：" + std::format(L"{:.2f}", gvalue::global_speed * 10);
		function::text(SDK::FVector2D(330, 80), wstr.c_str());
		function::drag_bar("global_speed", SDK::FVector2D(460, 80), SDK::FVector2D(120, 20), SDK::FVector2D(10, 20), &gvalue::global_speed);
	}

	ETB_DRAG(110, 4000, 跳跃速度：, jump_speed);

	{
		const std::wstring wstr = L"空中控制：" + std::format(L"{:.2f}", gvalue::air_control * 5);
		function::text(SDK::FVector2D(330, 140), wstr.c_str());
		function::drag_bar("air_control", SDK::FVector2D(460, 140), SDK::FVector2D(120, 20), SDK::FVector2D(10, 20), &gvalue::air_control);
	}

	{
		if (function::button_color_text(" ", SDK::FVector2D(330, 170), SDK::FVector2D(250, 30), L"重置速度"))
		{
			gvalue::run_speed = 0.1f;
			gvalue::walk_speed = 0.1f;
			gvalue::global_speed = 0.1f;
			gvalue::jump_speed = 0.1f;
			gvalue::air_control = 0.01f;
		}
	}

	function::check_box(" ", SDK::FVector2D(330, 230), SDK::FVector2D(20, 20), SDK::FVector2D(10, 10), &gvalue::spin);
	function::text(SDK::FVector2D(360, 230), L"反瞄准[整活]");

	ETB_DRAG(260, 100, 旋转速度：, spin_speed);

#undef ETB_DRAG

	function::check_box(" ", SDK::FVector2D(330, 290), SDK::FVector2D(20, 20), SDK::FVector2D(10, 10), &gvalue::t_pos);
	function::text(SDK::FVector2D(360, 290), L"T字姿势[整活]");

	auto flush_player = [&]()
		{
			param::player_list.clear();
			SDK::TArray<SDK::AActor*> actor_list;
			SDK::UGameplayStatics::GetAllActorsOfClass(gvalue::world, SDK::ABPCharacter_Demo_C::StaticClass(), &actor_list);
			for (SDK::AActor* actor : actor_list)
			{
				SDK::ABPCharacter_Demo_C* cur_pawn = static_cast<SDK::ABPCharacter_Demo_C*>(actor);
				param::player_list.emplace_back(cur_pawn);
			}
		};

	auto player_box = [&](SDK::ABPCharacter_Demo_C* pawn, SDK::FVector2D pos)
		{
			if (!pawn || !pawn->IsA(SDK::ABPCharacter_Demo_C::StaticClass()))
			{
				flush_player();
				return;
			}
			function::pice(pos, SDK::FVector2D(400, 40));
			function::text(pos + SDK::FVector2D(10, 12), pawn->PlayerState->GetPlayerName());

			if (function::button_color_text(" ", pos + SDK::FVector2D(210, 5), SDK::FVector2D(40, 30), L"传送"))
			{
				gvalue::controller->Pawn->K2_SetActorLocation(pawn->K2_GetActorLocation(), false, nullptr, false);
			}

			if (function::button_color_text(" ", pos + SDK::FVector2D(260, 5), SDK::FVector2D(80, 30), L"传送到我"))
			{
				pawn->K2_SetActorLocation(gvalue::controller->Pawn->K2_GetActorLocation(), false, nullptr, false);
			}

			if (function::button_color_text(" ", pos + SDK::FVector2D(350, 5), SDK::FVector2D(40, 30), L"杀死"))
			{
				pawn->KillClient();
				pawn->KillServer(false);
				flush_player();
			}
		};

	render::fill_box(
		SDK::FVector2D(param::pos.X + (param::size.X + 18) * gvalue::menu_scale, param::pos.Y - 2 * gvalue::menu_scale),
		SDK::FVector2D((420 + 4)* gvalue::menu_scale, (90 + param::player_list.size() * 50 + 4)* gvalue::menu_scale), 
		color::get()->outline_col
	);

	render::fill_box(
		SDK::FVector2D(param::pos.X + (param::size.X + 20) * gvalue::menu_scale, param::pos.Y),
		SDK::FVector2D(420 * gvalue::menu_scale, (90 + param::player_list.size() * 50)* gvalue::menu_scale), 
		color::get()->back_col
	);

	if (function::button_color_text(" ", SDK::FVector2D(param::size.X + 30, 10), SDK::FVector2D(400, 30), L"刷新玩家列表"))
	{
		flush_player();
	}

	if (function::button_color_text(" ", SDK::FVector2D(param::size.X + 30, 50), SDK::FVector2D(400, 30), L"将所有人传送到我"))
	{
		for (int i = 0; i < param::player_list.size(); i++)
		{
			param::player_list[i]->K2_SetActorLocation(gvalue::controller->Pawn->K2_GetActorLocation(), false, nullptr, false);
		}
	}

	for (int i = 0; i < param::player_list.size(); i++)
	{
		player_box(param::player_list[i], SDK::FVector2D(param::size.X + 30, 90 + 50 * i));
	}
}

void menu::item()
{
	param::size.X = 670;

	function::pice(SDK::FVector2D(110, 10), SDK::FVector2D(400, param::size.Y - 20));

#define ETB_BUTTON(_name_,_class_,_x_,_y_) \
if (function::button_color_text(" ", SDK::FVector2D(_x_, _y_), SDK::FVector2D(120, 30),L#_name_)) \
{ \
	item::get()->spawn(SDK::_class_::StaticClass()); \
} \

	// line 1
	ETB_BUTTON(果汁, ABP_DroppedItem_Juice_C, 120, 20);
	ETB_BUTTON(杏仁水, ABP_DroppedItem_AlmondWater_C, 120, 60);
	ETB_BUTTON(手电筒, ABP_DroppedItem_Flashlight_C, 120, 100);
	ETB_BUTTON(液态痛苦, ABP_DroppedItem_LiquidPain_C, 120, 140);
	ETB_BUTTON(能量棒, ABP_DroppedItem_EnergyBar_C, 120, 180);
	ETB_BUTTON(潜水头盔, ABP_DroppedItem_DivingHelmet_C, 120, 220);
	ETB_BUTTON(信号枪, ABP_DroppedItem_FlareGun_C, 120, 260);
	ETB_BUTTON(绳子, ABP_DroppedItem_Rope_C, 120, 300);
	ETB_BUTTON(对讲机, ABP_DroppedItem_WalkieTalkie_C, 120, 340);

	// line 2
	ETB_BUTTON(电锯, ABP_DroppedItem_Chainsaw_C, 250, 20);
	ETB_BUTTON(烟花, ABP_DroppedItem_Firework_C, 250, 60);
	ETB_BUTTON(黄色荧光棒, ABP_DroppedItem_Glowstick_Yellow_C, 250, 100);
	ETB_BUTTON(蓝色荧光棒, ABP_DroppedItem_Glowstick_Blue_C, 250, 140);
	ETB_BUTTON(红色荧光棒, ABP_Item_Glowstick_Red_C, 250, 180);
	ETB_BUTTON(荧光棒, ABP_DroppedItem_Glowstick_C, 250, 220);
	ETB_BUTTON(杀虫喷雾, ABP_DroppedItem_BugSpray_C, 250, 260);
	ETB_BUTTON(相机, ABP_DroppedItem_Camera_C, 250, 300);
	ETB_BUTTON(撬棍, ABP_DroppedItem_Crowbar_C, 250, 340);

	// line 3
	ETB_BUTTON(温度计, ABP_DroppedItem_Thermometer_C, 380, 20);
	ETB_BUTTON(扫描仪, ABP_DroppedItem_LiDAR_C, 380, 60);
	ETB_BUTTON(玩具, ABP_DroppedItem_Toy_C, 380, 100);
	ETB_BUTTON(刀, ABP_DroppedItem_Knife_C, 380, 140);
	ETB_BUTTON(果冻, ABP_DroppedItem_Jelly_C, 380, 180);
	ETB_BUTTON(快速电锯, ABP_DroppedItem_Chainsaw_Fast_C, 380, 220);

#undef ETB_BUTTON

	function::pice(SDK::FVector2D(520, 10), SDK::FVector2D(140, param::size.Y - 20));

	if (function::button_color_text(" ", SDK::FVector2D(530, 20), SDK::FVector2D(120, 30), L"吸附所有磁带"))
	{
		item::get()->interact_all("Tape_BP_C");
	} 
}

void menu::entity()
{
	param::size.X = 560;

	function::pice(SDK::FVector2D(110, 10), SDK::FVector2D(160, param::size.Y - 20));
	function::pice(SDK::FVector2D(280, 10), SDK::FVector2D(270, param::size.Y - 20));

	if (function::button_color_text(" ", SDK::FVector2D(120, 20), SDK::FVector2D(140, 30), L"干死所有实体"))
	{
		entity::get()->kill_all();
	}

	if (function::button_color_text(" ", SDK::FVector2D(120, 60), SDK::FVector2D(140, 30), L"删除细菌"))
	{
		entity::get()->kill("Bacteria_Roaming_BP_C");
		entity::get()->kill("Bacteria_BP_C");
	}

	if (function::button_color_text(" ", SDK::FVector2D(120, 100), SDK::FVector2D(140, 30), L"删除笑魇"))
	{
		entity::get()->kill("Smiler_BP2_C");
		entity::get()->kill("BP_Roaming_Smiler_C");
		entity::get()->kill("BP_Smiler_Dash_C");
	}

	if (function::button_color_text(" ", SDK::FVector2D(120, 140), SDK::FVector2D(140, 30), L"删除派对客"))
	{
		entity::get()->kill("BP_RoamingPartygoer_Idle_C");
		entity::get()->kill("BP_RoamingPartygoer_C");
		entity::get()->kill("BP_RoamingPartygoer_Slow_C");
		entity::get()->kill("Smiler_BP2_C");
		entity::get()->kill("BP_DarkPartyGoer_C");
		entity::get()->kill("BP_HidingPartyGoer_C");
	}

	if (function::button_color_text(" ", SDK::FVector2D(120, 180), SDK::FVector2D(140, 30), L"删除死亡飞蛾"))
	{
		entity::get()->kill("BP_Moth_C");
		entity::get()->kill("BP_Cave_Moth_C");
	}

	if (function::button_color_text(" ", SDK::FVector2D(120, 220), SDK::FVector2D(140, 30), L"删除窃皮者"))
	{
		entity::get()->kill("BP_SkinStealer_C");
		entity::get()->kill("BP_SkinStealer_Cave_C");
		entity::get()->kill("BP_SkinStealer_Level07_C");
		entity::get()->kill("BP_SkinStealer_Hotel_C");
	}

	if (function::button_color_text(" ", SDK::FVector2D(120, 260), SDK::FVector2D(140, 30), L"删除猎犬"))
	{
		entity::get()->kill("BP_Hound_C");
		entity::get()->kill("BP_Hound_Hotel_C");
	}

	if (function::button_color_text(" ", SDK::FVector2D(120, 300), SDK::FVector2D(140, 30), L"删除悲尸"))
	{
		entity::get()->kill("BP_Wretch_C");
		entity::get()->kill("BP_Wretch_House_C");
	}

#define ETB_BUTTON(_name_,_class_,_x_,_y_) \
if (function::button_color_text(" ", SDK::FVector2D(_x_, _y_), SDK::FVector2D(120, 30), L#_name_)) \
{ \
	entity::get()->spawn(SDK::_class_::StaticClass()); \
}

	ETB_BUTTON(细菌1, ABacteria_BP_C, 290, 20);
	ETB_BUTTON(细菌2, ABacteria_Roaming_BP_C, 290, 60);
	ETB_BUTTON(窃皮者1, ABP_SkinStealer_C, 290, 100);
	ETB_BUTTON(窃皮者2, ABP_SkinStealer_Level07_C, 290, 140);
	ETB_BUTTON(笑魇, ABP_Roaming_Smiler_C, 420, 20);
	ETB_BUTTON(动画, ABP_Animation_C, 420, 60);
	ETB_BUTTON(死亡飞蛾, ABP_Moth_C, 420, 100);
	ETB_BUTTON(猎犬, ABP_Hound_C, 420, 140);

#undef ETB_BUTTON

#define ETB_BUTTON(_name_,_class_,_x_,_y_) \
if (function::button_color_text(" ", SDK::FVector2D(_x_, _y_), SDK::FVector2D(120, 30), L#_name_)) \
{ \
	entity::get()->spawn(SDK::UObject::FindClassFast(#_class_)); \
}

	ETB_BUTTON(Kitty[限定], BP_Entity974_C, 290, 180);
	ETB_BUTTON(派对客1[限定], BP_RoamingPartygoer_Idle_C, 290, 220);
	ETB_BUTTON(派对客2[限定], BP_RoamingPartygoer_C, 290, 260);
	ETB_BUTTON(派对客3[限定], BP_DarkPartyGoer_C, 290, 300);
	ETB_BUTTON(派对客4[限定], BP_HidingPartyGoer_C, 290, 340);
	ETB_BUTTON(大眼怪[限定], BP_NPC_Type01_C, 420, 180);
	ETB_BUTTON(池核肢团[限定], BP_Clump_Poolrooms_C, 420, 220);
	ETB_BUTTON(悲尸[限定], BP_Wretch_House_C, 420, 260);
	ETB_BUTTON(无面灵[限定], BP_Faceling_C, 420, 300);
	ETB_BUTTON(蜘蛛怪[限定], BP_Membri_C, 420, 340);

#undef ETB_BUTTON

	auto flush_entity=[&]()
	{
		param::entity_list.clear();
		SDK::TArray<SDK::AActor*> actor_list;
		SDK::UGameplayStatics::GetAllActorsOfClass(gvalue::world, SDK::ACharacter::StaticClass(), &actor_list);
		for (SDK::AActor* actor : actor_list)
		{
			if (actor->IsA(SDK::ABP_Explorer_C::StaticClass()) ||
				actor->IsA(SDK::ABPCharacter_Demo_C::StaticClass()))
			{
				continue;
			}
			SDK::ACharacter* cur_pawn = static_cast<SDK::ACharacter*>(actor);
			param::entity_list.emplace_back(cur_pawn);
		}
	};

	auto entity_box = [&](SDK::ACharacter* pawn, SDK::FVector2D pos)
		{
			if (!pawn || !pawn->IsA(SDK::ACharacter::StaticClass()))
			{
				flush_entity();
				return;
			}
			function::pice(pos, SDK::FVector2D(240, 40.0f));
			const std::wstring name = visual::get()->find_name(pawn->Class->Name.ToString());
			function::text(
				pos + SDK::FVector2D(10, 12),
				name.c_str()
			);

			if (function::button_color_text(" ", pos + SDK::FVector2D(140, 10), SDK::FVector2D(40, 20), L"控制"))
			{
				entity::get()->poss(pawn);
			}

			if (function::button_color_text(" ", pos + SDK::FVector2D(190, 10), SDK::FVector2D(40, 20), L"删除"))
			{
				pawn->K2_DestroyActor();
				flush_entity();
			}
		};

	render::fill_box(
		SDK::FVector2D(param::pos.X + (param::size.X + 18) * gvalue::menu_scale, param::pos.Y - 2 * gvalue::menu_scale),
		SDK::FVector2D((260 + 4) * gvalue::menu_scale, (150 + param::entity_list.size() * 50 + 4) * gvalue::menu_scale), 
		color::get()->outline_col
	);

	render::fill_box(
		SDK::FVector2D(param::pos.X + (param::size.X + 20) * gvalue::menu_scale, param::pos.Y),
		SDK::FVector2D(260 * gvalue::menu_scale, (150 + param::entity_list.size() * 50) * gvalue::menu_scale), 
		color::get()->back_col
	);

	if (function::button_color_text(" ", SDK::FVector2D(param::size.X + 30, 10), SDK::FVector2D(240, 30), L"刷新实体列表"))
	{
		flush_entity();
	}

	if (function::button_color_text(" ", SDK::FVector2D(param::size.X + 30, 50), SDK::FVector2D(240, 30), L"取消控制实体"))
	{
		entity::get()->unposs();
	}

	{
		const int speed = 4000 * gvalue::entity_speed;
		const std::wstring wstr = L"被控实体速度：" + std::to_wstring(speed);
		function::text(SDK::FVector2D(param::size.X + 30, 90), wstr.c_str());
		function::drag_bar("entity_speed", SDK::FVector2D(param::size.X + 30, 120), SDK::FVector2D(240, 20), SDK::FVector2D(10, 20), &gvalue::entity_speed);
	}

	for (int i = 0; i < param::entity_list.size(); i++)
	{
		entity_box(param::entity_list[i], SDK::FVector2D(param::size.X + 30, 150 + 50 * i));
	}
}

void menu::level()
{
	param::size.X = 650;

	function::pice(SDK::FVector2D(110, 10), SDK::FVector2D(param::size.X - 120, param::size.Y - 20));

#define ETB_BUTTON(_name_,_lvname_,_x_,_y_) \
if (function::button_color_text("", SDK::FVector2D(_x_, _y_), SDK::FVector2D(120, 30), L#_name_)) \
{ \
	const std::wstring cmd = std::wstring(L"ServerTravel ") + std::wstring(L#_lvname_); \
	SDK::UKismetSystemLibrary::ExecuteConsoleCommand(gvalue::world, cmd.c_str(), gvalue::controller); \
}

	//line 1
	ETB_BUTTON(Level0, Level0, 120, 20);
	ETB_BUTTON(Level1, TopFloor, 120, 60);
	ETB_BUTTON(Level2, Pipes, 120, 100);
	ETB_BUTTON(Level3, ElectricalStation, 120, 140);
	ETB_BUTTON(Level4, Office, 120, 180);
	ETB_BUTTON(Level5, Hotel, 120, 220);
	ETB_BUTTON(LevelFun, LevelFun, 120, 260);
	ETB_BUTTON(Level37, Poolrooms, 120, 300);
	ETB_BUTTON(Level!, LevelRun, 120, 340);

	//line 2
	ETB_BUTTON(LevelEnd, TheEnd, 250, 20);
	ETB_BUTTON(Level94, Level94, 250, 60);
	ETB_BUTTON(Level6, LightsOut, 250, 100);
	ETB_BUTTON(Level7, OceanMap, 250, 140);
	ETB_BUTTON(Level8, CaveLevel, 250, 180);
	ETB_BUTTON(Level0.11, Level05, 250, 220);
	ETB_BUTTON(Level9, Level9, 250, 260);
	ETB_BUTTON(Level10, Level10, 250, 300);
	ETB_BUTTON(Level3999, Level3999, 250, 340);

	//line 3
	ETB_BUTTON(Level0.2, Level07, 380, 20);
	ETB_BUTTON(零食屋, Snackrooms, 380, 60);
	ETB_BUTTON(Level!- !, LevelDash, 380, 100);
	ETB_BUTTON(Level188, Level188_Expanded, 380, 140);
	ETB_BUTTON(Level37.2, Poolrooms_Expanded, 380, 180);
	ETB_BUTTON(LevelFun + , LevelFun_Expanded, 380, 220);
	ETB_BUTTON(Level52, Level52, 380, 260);
	ETB_BUTTON(Level55.1, TunnelLevel, 380, 300);
	ETB_BUTTON(Level922, Level922, 380, 340);

	//line 4
	ETB_BUTTON(Level974, Level974, 510, 20);
	ETB_BUTTON(过度生长, GraffitiLevel, 510, 60);
	ETB_BUTTON(草屋, Grassrooms_Expanded, 510, 100);

#undef ETB_BUTTON
}

void menu::misc()
{	
	param::size.X = 650;
	param::size.Y = 550;

	function::pice(SDK::FVector2D(110, 10), SDK::FVector2D(160, 140));
	if (function::button_color_text(" ", SDK::FVector2D(120, 20), SDK::FVector2D(140, 30), color::get()->get_name().c_str()))
	{
		color::get()->change();
	}
	function::check_box(" ", SDK::FVector2D(120, 60), SDK::FVector2D(20, 20), SDK::FVector2D(10, 10), &gvalue::new_year_color);
	function::text(SDK::FVector2D(150, 61), L"使用新年主题");

	{
		const float calc_buffer = SDK::UKismetMathLibrary::Lerp(0.0f, 4.0f, gvalue::menu_scale_buffer);
		const float truncated = floor(calc_buffer * 10) / 10.0f;
		const std::wstring show_name = L"界面尺寸：" + std::format(L"{:.1f}", truncated) + L"X";
		function::text(SDK::FVector2D(120, 91), show_name.c_str());
		function::drag_bar("menu_scale_buffer", SDK::FVector2D(120, 120), SDK::FVector2D(140, 20), SDK::FVector2D(10, 20), &gvalue::menu_scale_buffer);
		if (!kismet::is_key_down(VK_LBUTTON))
		{
			gvalue::menu_scale = truncated;
		}
	}


	function::pice(SDK::FVector2D(110, 160), SDK::FVector2D(160, 130));
	if (function::button_color_text(" ", SDK::FVector2D(120, 170), SDK::FVector2D(140, 30), L"保存参数"))
	{
		config::get()->save();
	}
	if (function::button_color_text(" ", SDK::FVector2D(120, 210), SDK::FVector2D(140, 30), L"加载参数"))
	{
		config::get()->load("C:\\LHY1339\\escape_the_backrooms\\config.cheat");
	}
	if (function::button_color_text(" ", SDK::FVector2D(120, 250), SDK::FVector2D(140, 30), L"打开参数配置"))
	{
		system("start C:/LHY1339/escape_the_backrooms/config.cheat");
	}

	function::pice(SDK::FVector2D(110, 300), SDK::FVector2D(160, 90));
	if (function::button_color_text(" ", SDK::FVector2D(120, 310), SDK::FVector2D(140, 30), L"加载按键"))
	{
		config::get()->load("C:\\LHY1339\\escape_the_backrooms\\keybind.cheat");
	}
	if (function::button_color_text(" ", SDK::FVector2D(120, 350), SDK::FVector2D(140, 30), L"打开按键配置"))
	{
		system("start C:/LHY1339/escape_the_backrooms/keybind.cheat");
	}

	function::pice(SDK::FVector2D(110, 400), SDK::FVector2D(160, 40));
	function::check_box(" ", SDK::FVector2D(120, 410), SDK::FVector2D(20, 20), SDK::FVector2D(10, 10), &gvalue::draw_lable);
	function::text(SDK::FVector2D(150, 411), L"显示按键提示");

	function::pice(SDK::FVector2D(110, 450), SDK::FVector2D(160, 90));
	if (function::button_color_text(" ", SDK::FVector2D(120, 460), SDK::FVector2D(140, 30), L"源码下载"))
	{
		system("start https://github.com/LHY1339/cheat_escape_the_backrooms");
	}
	if (function::button_color_text(" ", SDK::FVector2D(120, 500), SDK::FVector2D(140, 30), L"新版本下载"))
	{
		system("start https://github.com/LHY1339/cheat_escape_the_backrooms/releases/");
	}

	function::pice(SDK::FVector2D(280, 10), SDK::FVector2D(param::size.X - 290, param::size.Y - 20));
	{
		const wchar_t* log = L"逃离后室修改器\n"
			VERSION_W
			GAME_VERSION
			L"作者：LHY1339\n"
			L"源代码：cheat_escape_the_backrooms\n"
			L"爱发电：LHY1339\n"
			L"交流群：1071845133\n"
			L"\n--------特别感谢--------\n"
			THANKS
			"\n--------其他--------\n"
			"祝各位在新的一年里\n"
			"多喜乐、长安宁，所愿皆所成\n"
			"心有所悦、业有所成，万事皆可期";

		function::text(SDK::FVector2D(290, 20), log);
	}
}