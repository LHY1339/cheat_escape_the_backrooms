#pragma once
#include "_sdk.h"

class color
{
public:
	static color* get();

	void load();
	void change();
	void flush_color();
	std::wstring get_name();

private:
	color() = default;

public:
	SDK::FLinearColor normal_col = SDK::FLinearColor(0.05f, 0.00f, 0.10f, 1.0f);
	SDK::FLinearColor hover_col = SDK::FLinearColor(0.12f, 0.02f, 0.25f, 1.0f);
	SDK::FLinearColor press_col = SDK::FLinearColor(0.25f, 0.00f, 0.40f, 1.0f);
	SDK::FLinearColor check_col = SDK::FLinearColor(0.00f, 0.70f, 0.90f, 1.0f);
	SDK::FLinearColor bar_col = SDK::FLinearColor(0.00f, 0.55f, 0.85f, 1.0f);
	SDK::FLinearColor text_col = SDK::FLinearColor(0.90f, 0.80f, 1.00f, 1.0f);

	SDK::FLinearColor back_col = SDK::FLinearColor(0.01f, 0.00f, 0.02f, 1.0f);
	SDK::FLinearColor outline_col = SDK::FLinearColor(0.40f, 0.00f, 0.80f, 1.0f);
	SDK::FLinearColor pice_col = SDK::FLinearColor(0.02f, 0.00f, 0.04f, 1.0f);
};

