#include "color.h"

#include "gvalue.h"

color* color::get()
{
	static color inst;
	return &inst;
}

void color::load()
{
	gvalue::color_index -= 1;
	change();
}

void color::change()
{
	gvalue::color_index = (gvalue::color_index + 1) > 8 ? 0 : (gvalue::color_index + 1);
	switch (gvalue::color_index)
	{
	case 0:
		normal_col = SDK::FLinearColor(0.05f, 0.00f, 0.10f, 1.0f);
		hover_col = SDK::FLinearColor(0.12f, 0.02f, 0.25f, 1.0f);
		press_col = SDK::FLinearColor(0.25f, 0.00f, 0.40f, 1.0f);
		check_col = SDK::FLinearColor(0.00f, 0.70f, 0.90f, 1.0f);
		bar_col = SDK::FLinearColor(0.00f, 0.55f, 0.85f, 1.0f);
		text_col = SDK::FLinearColor(0.90f, 0.80f, 1.00f, 1.0f);

		back_col = SDK::FLinearColor(0.01f, 0.00f, 0.02f, 1.0f);
		outline_col = SDK::FLinearColor(0.40f, 0.00f, 0.80f, 1.0f);
		pice_col = SDK::FLinearColor(0.02f, 0.00f, 0.04f, 1.0f);
		break;
	case 1:
		normal_col = SDK::FLinearColor(0.80f, 0.88f, 0.85f, 1.0f);
		hover_col = SDK::FLinearColor(0.86f, 0.94f, 0.90f, 1.0f);
		press_col = SDK::FLinearColor(0.72f, 0.82f, 0.78f, 1.0f);
		check_col = SDK::FLinearColor(0.20f, 0.65f, 0.50f, 1.0f);
		bar_col = SDK::FLinearColor(0.17f, 0.60f, 0.45f, 1.0f);
		text_col = SDK::FLinearColor(0.12f, 0.14f, 0.13f, 1.0f);

		back_col = SDK::FLinearColor(0.45f, 0.52f, 0.50f, 1.0f);
		outline_col = SDK::FLinearColor(0.55f, 0.75f, 0.62f, 1.0f);
		pice_col = SDK::FLinearColor(0.58f, 0.66f, 0.63f, 1.0f);
		break;
	case 2:
		normal_col = SDK::FLinearColor(0.90f, 0.88f, 0.82f, 1.0f);
		hover_col = SDK::FLinearColor(0.94f, 0.92f, 0.86f, 1.0f);
		press_col = SDK::FLinearColor(0.82f, 0.80f, 0.75f, 1.0f);
		check_col = SDK::FLinearColor(0.55f, 0.45f, 0.20f, 1.0f);
		bar_col = SDK::FLinearColor(0.60f, 0.48f, 0.25f, 1.0f);
		text_col = SDK::FLinearColor(0.18f, 0.16f, 0.14f, 1.0f);

		back_col = SDK::FLinearColor(0.35f, 0.33f, 0.28f, 1.0f);
		outline_col = SDK::FLinearColor(0.70f, 0.68f, 0.62f, 1.0f);
		pice_col = SDK::FLinearColor(0.48f, 0.46f, 0.40f, 1.0f);
		break;
	case 3:
		normal_col = SDK::FLinearColor(0.05f, 0.07f, 0.10f, 1.0f);
		hover_col = SDK::FLinearColor(0.08f, 0.10f, 0.15f, 1.0f);
		press_col = SDK::FLinearColor(0.12f, 0.15f, 0.20f, 1.0f);
		check_col = SDK::FLinearColor(0.10f, 0.70f, 0.95f, 1.0f);
		bar_col = SDK::FLinearColor(0.07f, 0.60f, 0.90f, 1.0f);
		text_col = SDK::FLinearColor(0.85f, 0.90f, 1.00f, 1.0f);

		back_col = SDK::FLinearColor(0.02f, 0.03f, 0.06f, 1.0f);
		outline_col = SDK::FLinearColor(0.15f, 0.40f, 0.55f, 1.0f);
		pice_col = SDK::FLinearColor(0.03f, 0.04f, 0.07f, 1.0f);
		break;
	case 4:
		normal_col = SDK::FLinearColor(0.03f, 0.06f, 0.12f, 1.0f);
		hover_col = SDK::FLinearColor(0.06f, 0.10f, 0.18f, 1.0f);
		press_col = SDK::FLinearColor(0.10f, 0.14f, 0.22f, 1.0f);
		check_col = SDK::FLinearColor(0.10f, 0.45f, 0.90f, 1.0f);
		bar_col = SDK::FLinearColor(0.08f, 0.40f, 0.75f, 1.0f);
		text_col = SDK::FLinearColor(0.80f, 0.90f, 1.00f, 1.0f);

		back_col = SDK::FLinearColor(0.01f, 0.02f, 0.05f, 1.0f);
		outline_col = SDK::FLinearColor(0.12f, 0.25f, 0.45f, 1.0f);
		pice_col = SDK::FLinearColor(0.02f, 0.04f, 0.08f, 1.0f);
		break;
	case 5:
		normal_col = SDK::FLinearColor(0.04f, 0.04f, 0.12f, 1.0f);
		hover_col = SDK::FLinearColor(0.06f, 0.06f, 0.15f, 1.0f);
		press_col = SDK::FLinearColor(0.1f, 0.1f, 0.2f, 1.0f);
		check_col = SDK::FLinearColor(0.15f, 0.15f, 0.4f, 1.0f);
		bar_col = SDK::FLinearColor(0.15f, 0.15f, 0.4f, 1.0f);
		text_col = SDK::FLinearColor(0.9f, 0.9f, 1.0f, 1.0f);

		back_col = SDK::FLinearColor(0.01f, 0.01f, 0.03f, 1.0f);
		outline_col = SDK::FLinearColor(0.2f, 0.2f, 0.3f, 1.0f);
		pice_col = SDK::FLinearColor(0.02f, 0.02f, 0.06f, 1.0f);
		break;
	case 6:
		normal_col = SDK::FLinearColor(0.10f, 0.06f, 0.12f, 1.0f);
		hover_col = SDK::FLinearColor(0.15f, 0.10f, 0.18f, 1.0f);
		press_col = SDK::FLinearColor(0.20f, 0.12f, 0.25f, 1.0f);
		check_col = SDK::FLinearColor(0.60f, 0.45f, 0.95f, 1.0f);
		bar_col = SDK::FLinearColor(0.50f, 0.38f, 0.85f, 1.0f);
		text_col = SDK::FLinearColor(0.90f, 0.85f, 1.00f, 1.0f);

		back_col = SDK::FLinearColor(0.05f, 0.03f, 0.08f, 1.0f);
		outline_col = SDK::FLinearColor(0.30f, 0.15f, 0.45f, 1.0f);
		pice_col = SDK::FLinearColor(0.07f, 0.04f, 0.10f, 1.0f);
		break;
	case 7:
		normal_col = SDK::FLinearColor(0.12f, 0.06f, 0.02f, 1.0f);
		hover_col = SDK::FLinearColor(0.16f, 0.08f, 0.03f, 1.0f);
		press_col = SDK::FLinearColor(0.22f, 0.11f, 0.05f, 1.0f);
		check_col = SDK::FLinearColor(1.00f, 0.45f, 0.10f, 1.0f);
		bar_col = SDK::FLinearColor(0.90f, 0.40f, 0.07f, 1.0f);
		text_col = SDK::FLinearColor(1.00f, 0.90f, 0.80f, 1.0f);

		back_col = SDK::FLinearColor(0.04f, 0.02f, 0.00f, 1.0f);
		outline_col = SDK::FLinearColor(0.50f, 0.25f, 0.08f, 1.0f);
		pice_col = SDK::FLinearColor(0.07f, 0.03f, 0.01f, 1.0f);
		break;
	case 8:
		normal_col = SDK::FLinearColor(0.10f, 0.02f, 0.02f, 1.0f);
		hover_col = SDK::FLinearColor(0.15f, 0.04f, 0.04f, 1.0f);
		press_col = SDK::FLinearColor(0.22f, 0.06f, 0.06f, 1.0f);
		check_col = SDK::FLinearColor(1.00f, 0.25f, 0.25f, 1.0f);
		bar_col = SDK::FLinearColor(0.85f, 0.20f, 0.20f, 1.0f);
		text_col = SDK::FLinearColor(0.95f, 0.80f, 0.80f, 1.0f);

		back_col = SDK::FLinearColor(0.03f, 0.00f, 0.00f, 1.0f);
		outline_col = SDK::FLinearColor(0.40f, 0.10f, 0.10f, 1.0f);
		pice_col = SDK::FLinearColor(0.05f, 0.01f, 0.01f, 1.0f);
		break;
	}
}

std::wstring color::get_name()
{
	std::wstring name = L"";
	switch (gvalue::color_index)
	{
	case 0:
		name = L"Èü²©×Ï";
		break;
	case 1:
		name = L"±¡ºÉÂÌ";
		break;
	case 2:
		name = L"Ã×°×";
		break;
	case 3:
		name = L"±ùÀ¶";
		break;
	case 4:
		name = L"Éî¿ÕÀ¶";
		break;
	case 5:
		name = L"À¶ºÚ";
		break;
	case 6:
		name = L"ÆÏÌÑ×Ï";
		break;
	case 7:
		name = L"ÑÒ½¬³È";
		break;
	case 8:
		name = L"°µºì";
		break;
	}
	return L"ÅäÉ«£º" + name;
}
