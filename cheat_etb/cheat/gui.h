#pragma once

#include <string>

namespace SDK
{
	struct FVector2D;
	struct FLinearColor;
	class UFont;
}

namespace UC
{
	class FString;
}

class gui
{
public:
	static void main();

	static bool button(
		const std::string& name,
		const SDK::FVector2D& pos,
		const SDK::FVector2D& size
	);

	static bool button_color(
		const std::string& name,
		const SDK::FVector2D& pos,
		const SDK::FVector2D& size,
		const SDK::FLinearColor& normal_col,
		const SDK::FLinearColor& hover_col,
		const SDK::FLinearColor& press_col
	);

	static bool button_text(
		const std::string& name,
		const SDK::FVector2D& pos,
		const SDK::FVector2D& size,
		const UC::FString& text,
		SDK::UFont* font,
		const SDK::FLinearColor& normal_col,
		const SDK::FLinearColor& hover_col,
		const SDK::FLinearColor& press_col,
		const SDK::FVector2D& text_size
	);

	static bool button_color_text(
		const std::string& name,
		const SDK::FVector2D& pos,
		const SDK::FVector2D& size,
		const UC::FString& text,
		SDK::UFont* font,
		const SDK::FLinearColor& text_col,
		const SDK::FLinearColor& normal_col,
		const SDK::FLinearColor& hover_col,
		const SDK::FLinearColor& press_col,
		const SDK::FVector2D& text_size
	);

	static void check_box(
		const std::string& name,
		const SDK::FVector2D& pos,
		const SDK::FVector2D& size,
		const SDK::FVector2D& check_size,
		const SDK::FLinearColor& check_col,
		const SDK::FLinearColor& normal_col,
		const SDK::FLinearColor& hover_col,
		const SDK::FLinearColor& press_col,
		bool* ptr
	);

	static void drag_bar(
		const std::string& name,
		const SDK::FVector2D& pos,
		const SDK::FVector2D& size,
		const SDK::FVector2D& bar_size,
		const SDK::FLinearColor& bar_col,
		const SDK::FLinearColor& normal_col,
		const SDK::FLinearColor& hover_col,
		const SDK::FLinearColor& press_col,
		float* ptr
	);

	static void drag(
		SDK::FVector2D& pos,
		const SDK::FVector2D& size,
		SDK::FVector2D& drag_pos,
		bool& is_drag
	);

private:
	static bool is_hover(
		const SDK::FVector2D& pos,
		const SDK::FVector2D& size,
		const std::string& name
	);

	static bool is_focus(const std::string& name);
};

