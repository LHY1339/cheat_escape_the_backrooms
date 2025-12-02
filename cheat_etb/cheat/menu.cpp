#include "menu.h"

#include "render.h"
#include "_sdk.h"
#include "gvalue.h"
#include "gui.h"

#include <format>

class param
{
public:
	inline static SDK::FVector2D pos = SDK::FVector2D(100.0f, 100.0f);
	inline static SDK::FVector2D size = SDK::FVector2D(600.0f, 400.0f);
	inline static SDK::FVector2D drag_pos = SDK::FVector2D(0.0f, 0.0f);
	inline static bool is_drag = false;

#define Ã×°×

#ifdef À¶ºÚ
	inline static const SDK::FLinearColor normal_col = SDK::FLinearColor(0.04f, 0.04f, 0.12f, 1.0f);
	inline static const SDK::FLinearColor hover_col = SDK::FLinearColor(0.06f, 0.06f, 0.15f, 1.0f);
	inline static const SDK::FLinearColor press_col = SDK::FLinearColor(0.1f, 0.1f, 0.2f, 1.0f);
	inline static const SDK::FLinearColor check_col = SDK::FLinearColor(0.15f, 0.15f, 0.4f, 1.0f);
	inline static const SDK::FLinearColor bar_col = SDK::FLinearColor(0.15f, 0.15f, 0.4f, 1.0f);
	inline static const SDK::FLinearColor text_col = SDK::FLinearColor(0.9f, 0.9f, 1.0f, 1.0f);

	inline static const SDK::FLinearColor back_col = SDK::FLinearColor(0.01f, 0.01f, 0.03f, 1.0f);
	inline static const SDK::FLinearColor outline_col = SDK::FLinearColor(0.2f, 0.2f, 0.3f, 1.0f);
	inline static const SDK::FLinearColor pice_col = SDK::FLinearColor(0.02f, 0.02f, 0.06f, 1.0f);
	inline static const SDK::FLinearColor cursor_col = SDK::FLinearColor(0.9f, 0.9f, 0.9f, 1.0f);
#endif

#ifdef Èü²©×Ï
	inline static const SDK::FLinearColor normal_col = SDK::FLinearColor(0.05f, 0.00f, 0.10f, 1.0f);
	inline static const SDK::FLinearColor hover_col = SDK::FLinearColor(0.12f, 0.02f, 0.25f, 1.0f);
	inline static const SDK::FLinearColor press_col = SDK::FLinearColor(0.25f, 0.00f, 0.40f, 1.0f);
	inline static const SDK::FLinearColor check_col = SDK::FLinearColor(0.00f, 0.70f, 0.90f, 1.0f);
	inline static const SDK::FLinearColor bar_col = SDK::FLinearColor(0.00f, 0.55f, 0.85f, 1.0f);
	inline static const SDK::FLinearColor text_col = SDK::FLinearColor(0.90f, 0.80f, 1.00f, 1.0f);

	inline static const SDK::FLinearColor back_col = SDK::FLinearColor(0.01f, 0.00f, 0.02f, 1.0f);
	inline static const SDK::FLinearColor outline_col = SDK::FLinearColor(0.40f, 0.00f, 0.80f, 1.0f);
	inline static const SDK::FLinearColor pice_col = SDK::FLinearColor(0.02f, 0.00f, 0.04f, 1.0f);
	inline static const SDK::FLinearColor cursor_col = SDK::FLinearColor(0.00f, 0.90f, 0.80f, 1.0f);
#endif

#ifdef Ã×°×
	inline static const SDK::FLinearColor normal_col = SDK::FLinearColor(0.90f, 0.88f, 0.82f, 1.0f);
	inline static const SDK::FLinearColor hover_col = SDK::FLinearColor(0.94f, 0.92f, 0.86f, 1.0f);
	inline static const SDK::FLinearColor press_col = SDK::FLinearColor(0.82f, 0.80f, 0.75f, 1.0f);
	inline static const SDK::FLinearColor check_col = SDK::FLinearColor(0.55f, 0.45f, 0.20f, 1.0f);
	inline static const SDK::FLinearColor bar_col = SDK::FLinearColor(0.60f, 0.48f, 0.25f, 1.0f);
	inline static const SDK::FLinearColor text_col = SDK::FLinearColor(0.18f, 0.16f, 0.14f, 1.0f);

	inline static const SDK::FLinearColor back_col = SDK::FLinearColor(0.35f, 0.33f, 0.28f, 1.0f);
	inline static const SDK::FLinearColor outline_col = SDK::FLinearColor(0.70f, 0.68f, 0.62f, 1.0f);
	inline static const SDK::FLinearColor pice_col = SDK::FLinearColor(0.48f, 0.46f, 0.40f, 1.0f);
	inline static const SDK::FLinearColor cursor_col = SDK::FLinearColor(0.55f, 0.40f, 0.20f, 1.0f);
#endif

#ifdef ±ùÀ¶
	inline static const SDK::FLinearColor normal_col = SDK::FLinearColor(0.05f, 0.07f, 0.10f, 1.0f);
	inline static const SDK::FLinearColor hover_col = SDK::FLinearColor(0.08f, 0.10f, 0.15f, 1.0f);
	inline static const SDK::FLinearColor press_col = SDK::FLinearColor(0.12f, 0.15f, 0.20f, 1.0f);
	inline static const SDK::FLinearColor check_col = SDK::FLinearColor(0.10f, 0.70f, 0.95f, 1.0f);
	inline static const SDK::FLinearColor bar_col = SDK::FLinearColor(0.07f, 0.60f, 0.90f, 1.0f);
	inline static const SDK::FLinearColor text_col = SDK::FLinearColor(0.85f, 0.90f, 1.00f, 1.0f);

	inline static const SDK::FLinearColor back_col = SDK::FLinearColor(0.02f, 0.03f, 0.06f, 1.0f);
	inline static const SDK::FLinearColor outline_col = SDK::FLinearColor(0.15f, 0.40f, 0.55f, 1.0f);
	inline static const SDK::FLinearColor pice_col = SDK::FLinearColor(0.03f, 0.04f, 0.07f, 1.0f);
	inline static const SDK::FLinearColor cursor_col = SDK::FLinearColor(0.70f, 0.95f, 1.00f, 1.0f);
#endif

#ifdef ±¡ºÉÂÌ
	inline static const SDK::FLinearColor normal_col = SDK::FLinearColor(0.80f, 0.88f, 0.85f, 1.0f);
	inline static const SDK::FLinearColor hover_col = SDK::FLinearColor(0.86f, 0.94f, 0.90f, 1.0f);
	inline static const SDK::FLinearColor press_col = SDK::FLinearColor(0.72f, 0.82f, 0.78f, 1.0f);
	inline static const SDK::FLinearColor check_col = SDK::FLinearColor(0.20f, 0.65f, 0.50f, 1.0f);
	inline static const SDK::FLinearColor bar_col = SDK::FLinearColor(0.17f, 0.60f, 0.45f, 1.0f);
	inline static const SDK::FLinearColor text_col = SDK::FLinearColor(0.12f, 0.14f, 0.13f, 1.0f);

	inline static const SDK::FLinearColor back_col = SDK::FLinearColor(0.45f, 0.52f, 0.50f, 1.0f);
	inline static const SDK::FLinearColor outline_col = SDK::FLinearColor(0.55f, 0.75f, 0.62f, 1.0f);
	inline static const SDK::FLinearColor pice_col = SDK::FLinearColor(0.58f, 0.66f, 0.63f, 1.0f);
	inline static const SDK::FLinearColor cursor_col = SDK::FLinearColor(0.25f, 0.75f, 0.55f, 1.0f);
#endif

#ifdef Éî¿ÕÀ¶
	inline static const SDK::FLinearColor normal_col = SDK::FLinearColor(0.03f, 0.06f, 0.12f, 1.0f);
	inline static const SDK::FLinearColor hover_col = SDK::FLinearColor(0.06f, 0.10f, 0.18f, 1.0f);
	inline static const SDK::FLinearColor press_col = SDK::FLinearColor(0.10f, 0.14f, 0.22f, 1.0f);
	inline static const SDK::FLinearColor check_col = SDK::FLinearColor(0.10f, 0.45f, 0.90f, 1.0f);
	inline static const SDK::FLinearColor bar_col = SDK::FLinearColor(0.08f, 0.40f, 0.75f, 1.0f);
	inline static const SDK::FLinearColor text_col = SDK::FLinearColor(0.80f, 0.90f, 1.00f, 1.0f);

	inline static const SDK::FLinearColor back_col = SDK::FLinearColor(0.01f, 0.02f, 0.05f, 1.0f);
	inline static const SDK::FLinearColor outline_col = SDK::FLinearColor(0.12f, 0.25f, 0.45f, 1.0f);
	inline static const SDK::FLinearColor pice_col = SDK::FLinearColor(0.02f, 0.04f, 0.08f, 1.0f);
	inline static const SDK::FLinearColor cursor_col = SDK::FLinearColor(0.40f, 0.70f, 1.00f, 1.0f);
#endif 

#ifdef ÆÏÌÑ×Ï
	inline static const SDK::FLinearColor normal_col = SDK::FLinearColor(0.10f, 0.06f, 0.12f, 1.0f);
	inline static const SDK::FLinearColor hover_col = SDK::FLinearColor(0.15f, 0.10f, 0.18f, 1.0f);
	inline static const SDK::FLinearColor press_col = SDK::FLinearColor(0.20f, 0.12f, 0.25f, 1.0f);
	inline static const SDK::FLinearColor check_col = SDK::FLinearColor(0.60f, 0.45f, 0.95f, 1.0f);
	inline static const SDK::FLinearColor bar_col = SDK::FLinearColor(0.50f, 0.38f, 0.85f, 1.0f);
	inline static const SDK::FLinearColor text_col = SDK::FLinearColor(0.90f, 0.85f, 1.00f, 1.0f);

	inline static const SDK::FLinearColor back_col = SDK::FLinearColor(0.05f, 0.03f, 0.08f, 1.0f);
	inline static const SDK::FLinearColor outline_col = SDK::FLinearColor(0.30f, 0.15f, 0.45f, 1.0f);
	inline static const SDK::FLinearColor pice_col = SDK::FLinearColor(0.07f, 0.04f, 0.10f, 1.0f);
	inline static const SDK::FLinearColor cursor_col = SDK::FLinearColor(0.75f, 0.55f, 1.00f, 1.0f);
#endif

#ifdef ÑÒ½¬³È
	inline static const SDK::FLinearColor normal_col = SDK::FLinearColor(0.12f, 0.06f, 0.02f, 1.0f);
	inline static const SDK::FLinearColor hover_col = SDK::FLinearColor(0.16f, 0.08f, 0.03f, 1.0f);
	inline static const SDK::FLinearColor press_col = SDK::FLinearColor(0.22f, 0.11f, 0.05f, 1.0f);
	inline static const SDK::FLinearColor check_col = SDK::FLinearColor(1.00f, 0.45f, 0.10f, 1.0f);
	inline static const SDK::FLinearColor bar_col = SDK::FLinearColor(0.90f, 0.40f, 0.07f, 1.0f);
	inline static const SDK::FLinearColor text_col = SDK::FLinearColor(1.00f, 0.90f, 0.80f, 1.0f);

	inline static const SDK::FLinearColor back_col = SDK::FLinearColor(0.04f, 0.02f, 0.00f, 1.0f);
	inline static const SDK::FLinearColor outline_col = SDK::FLinearColor(0.50f, 0.25f, 0.08f, 1.0f);
	inline static const SDK::FLinearColor pice_col = SDK::FLinearColor(0.07f, 0.03f, 0.01f, 1.0f);
	inline static const SDK::FLinearColor cursor_col = SDK::FLinearColor(1.00f, 0.55f, 0.15f, 1.0f);
#endif

#ifdef °µºì
	inline static const SDK::FLinearColor normal_col = SDK::FLinearColor(0.10f, 0.02f, 0.02f, 1.0f);
	inline static const SDK::FLinearColor hover_col = SDK::FLinearColor(0.15f, 0.04f, 0.04f, 1.0f);
	inline static const SDK::FLinearColor press_col = SDK::FLinearColor(0.22f, 0.06f, 0.06f, 1.0f);
	inline static const SDK::FLinearColor check_col = SDK::FLinearColor(1.00f, 0.25f, 0.25f, 1.0f);
	inline static const SDK::FLinearColor bar_col = SDK::FLinearColor(0.85f, 0.20f, 0.20f, 1.0f);
	inline static const SDK::FLinearColor text_col = SDK::FLinearColor(0.95f, 0.80f, 0.80f, 1.0f);

	inline static const SDK::FLinearColor back_col = SDK::FLinearColor(0.03f, 0.00f, 0.00f, 1.0f);
	inline static const SDK::FLinearColor outline_col = SDK::FLinearColor(0.40f, 0.10f, 0.10f, 1.0f);
	inline static const SDK::FLinearColor pice_col = SDK::FLinearColor(0.05f, 0.01f, 0.01f, 1.0f);
	inline static const SDK::FLinearColor cursor_col = SDK::FLinearColor(1.00f, 0.35f, 0.35f, 1.0f);
#endif
};

class function
{
public:
	static void set_font(const int& size)
	{
		gvalue::engine->TinyFont->LegacyFontSize = size;
	}

	static SDK::FVector2D attach(const float& ref_x, const float& ref_y)
	{
		return SDK::FVector2D(param::pos.X + ref_x, param::pos.Y + ref_y);
	}

	static bool button_color(const std::string& name, const SDK::FVector2D& pos, const SDK::FVector2D& size, bool is_attach = true)
	{
		return gui::button_color(
			name,
			is_attach ? attach(pos.X, pos.Y) : pos, 
			SDK::FVector2D(size.X, size.Y), 
			param::normal_col,
			param::hover_col,
			param::press_col
		);
	}

	static bool button_text(const std::string& name, const SDK::FVector2D& pos, const SDK::FVector2D& size, const SDK::FString& str, bool is_attach = true)
	{
		return gui::button_color_text(
			name,
			is_attach ? attach(pos.X, pos.Y) : pos,
			SDK::FVector2D(size.X, size.Y),
			str,
			gvalue::engine->TinyFont,
			param::text_col,
			param::normal_col,
			param::hover_col,
			param::press_col
		);
	}

	static void check_box(const std::string& name, const SDK::FVector2D& pos, const SDK::FVector2D& size, const SDK::FVector2D& check_size, bool* ptr, bool is_attach = true)
	{
		gui::check_box(
			name,
			is_attach ? attach(pos.X, pos.Y) : pos,
			SDK::FVector2D(size.X, size.Y),
			SDK::FVector2D(check_size.X, check_size.Y),
			param::check_col,
			param::normal_col,
			param::hover_col,
			param::press_col,
			ptr
		);
	}

	static void drag_bar(const std::string& name, const SDK::FVector2D& pos, const SDK::FVector2D& size, const SDK::FVector2D& bar_size, float* ptr, bool is_attach = true)
	{
		gui::drag_bar(
			name,
			is_attach ? attach(pos.X, pos.Y) : pos,
			SDK::FVector2D(size.X, size.Y),
			SDK::FVector2D(bar_size.X, bar_size.Y),
			param::bar_col,
			param::normal_col,
			param::hover_col,
			param::press_col,
			ptr
		);
	}

	static void text(const SDK::FVector2D& pos, const SDK::FString& str, const bool& mid_x = false, const bool& mid_y = false, bool is_attach = true)
	{
		render::draw_text(
			gvalue::engine->TinyFont,
			str,
			is_attach ? attach(pos.X, pos.Y) : pos,
			SDK::FVector2D(1.0f, 1.0f),
			param::text_col,
			1.0f,
			SDK::FLinearColor(0.0f, 0.0f, 0.0f, 0.0f),
			SDK::FVector2D(0.0f, 0.0f),
			mid_x,
			mid_y,
			false,
			SDK::FLinearColor(0.0f, 0.0f, 0.0f, 0.0f)
		);
	}

	static void pice(const SDK::FVector2D& pos, const SDK::FVector2D& size)
	{
		render::fill_box(
			attach(pos.X, pos.Y),
			size,
			param::pice_col
		);
	}
};

void menu::init()
{

}

void menu::main()
{
	if (gvalue::menu_open)
	{
		pre_base();
		base();
		cursor();
	}
	lable();
}

void menu::lable()
{
	render::draw_text(
		gvalue::engine->TinyFont,
		L"°´ÏÂ Ins£¨Insert£©ÏÔÊ¾/Òþ²Ø²Ëµ¥\n°´ÏÂ Del£¨Delete£©ÍË³ö",
		SDK::FVector2D(10.0f, 10.0f),
		SDK::FVector2D(1.0f, 1.0f),
		param::text_col,
		1.0f,
		SDK::FLinearColor(0.0f, 0.0f, 0.0f, 0.0f),
		SDK::FVector2D(0.0f, 0.0f),
		false,
		false,
		false,
		SDK::FLinearColor(0.0f, 0.0f, 0.0f, 0.0f)
	);
}

void menu::pre_base()
{
	gui::drag(
		param::pos,
		param::size,
		param::drag_pos,
		param::is_drag
	);
}

void menu::base()
{
	render::fill_box(
		SDK::FVector2D(param::pos.X - 2, param::pos.Y - 2),
		SDK::FVector2D(param::size.X + 4, param::size.Y + 4),
		param::outline_col
	);
	render::fill_box(
		SDK::FVector2D(param::pos.X, param::pos.Y),
		SDK::FVector2D(param::size.X, param::size.Y),
		param::back_col
	);

	function::set_font(15);

	function::pice(SDK::FVector2D(10.0f, 10.0f), SDK::FVector2D(220.0f, param::size.Y - 20.0f));

	if (function::button_color("button_color", SDK::FVector2D(20.0f, 20.0f), SDK::FVector2D(100.0f, 30.0f)))
	{
		printf("gui::button_color click\n");
	}

	if (function::button_text("button_text", SDK::FVector2D(20.0f, 60.0f), SDK::FVector2D(100.0f, 30.0f), L"°´Å¥"))
	{
		printf("gui::button_color_text click\n");
	}

	static bool example_cb = false;
	function::check_box("check_box", SDK::FVector2D(20.0f, 100.0f), SDK::FVector2D(30.0f, 30.0f), SDK::FVector2D(20.0f, 20.0f), &example_cb);

	const std::wstring cb_str = L"²âÊÔÑ¡Ôñ¿ò£º" + std::wstring(example_cb ? L"true" : L"false");
	function::text(SDK::FVector2D(20.0f, 140.0f), cb_str.c_str());

	static float example_db = 0.2f;
	function::drag_bar("drag_bar", SDK::FVector2D(20.0f, 180.0f), SDK::FVector2D(200.0f, 30.0f), SDK::FVector2D(10.0f, 30.0f), &example_db);

	
	const std::wstring db_str = L"²âÊÔ½ø¶ÈÌõ£º" + std::format(L"{:.2f}", example_db);
	function::text(SDK::FVector2D(20.0f, 220.0f), db_str.c_str());
}

void menu::cursor()
{
	render::fill_box(
		SDK::FVector2D(gvalue::mouse.x - 2, gvalue::mouse.y - 2),
		SDK::FVector2D(4, 4),
		param::cursor_col
	);
}