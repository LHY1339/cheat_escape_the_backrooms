#pragma once
#include "_d2d.h"

namespace gconst
{
	inline constexpr int window_w = 400;
	inline constexpr int window_h = 400;

	inline constexpr wchar_t proc_name[] = L"Backrooms-Win64-Shipping.exe";
	inline constexpr wchar_t dll_name[] = L"cheat.dll";

	inline static const D2D1_COLOR_F normal_col = D2D1::ColorF(0.90f, 0.88f, 0.82f, 1.0f);
	inline static const D2D1_COLOR_F hover_col = D2D1::ColorF(0.94f, 0.92f, 0.86f, 1.0f);
	inline static const D2D1_COLOR_F press_col = D2D1::ColorF(0.82f, 0.80f, 0.75f, 1.0f);
	inline static const D2D1_COLOR_F text_col = D2D1::ColorF(0.18f, 0.16f, 0.14f, 1.0f);

	inline static const D2D1_COLOR_F back_col = D2D1::ColorF(0.35f, 0.33f, 0.28f, 1.0f);
	inline static const D2D1_COLOR_F outline_col = D2D1::ColorF(0.70f, 0.68f, 0.5f, 1.0f);
	inline static const D2D1_COLOR_F pice_col = D2D1::ColorF(0.58f, 0.56f, 0.50f, 1.0f);
}