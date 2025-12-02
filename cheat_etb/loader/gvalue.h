#pragma once

#include "_d2d.h"

struct s_mouse
{
	int x = 0;
	int y = 0;
	bool left = 0;
};

namespace gvalue
{
	inline HWND window = nullptr;
	inline ID2D1Factory* d2d1_factory = nullptr;
	inline ID2D1HwndRenderTarget* render_target = nullptr;
	inline ID2D1SolidColorBrush* brush = nullptr;
	inline IDWriteFactory* dwrite_factory = nullptr;
	inline IDWriteTextFormat* f15 = nullptr;
	inline IDWriteTextFormat* f30 = nullptr;
	inline s_mouse mouse;

	inline bool is_load = false;
}