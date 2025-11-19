#pragma once

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
		const SDK::FVector2D& pos,
		const SDK::FVector2D& size
	);

	static bool button_color(
		const SDK::FVector2D& pos,
		const SDK::FVector2D& size,
		const SDK::FLinearColor& normal_col,
		const SDK::FLinearColor& hover_col,
		const SDK::FLinearColor& press_col
	);

	static bool button_text(
		const SDK::FVector2D& pos,
		const SDK::FVector2D& size,
		const UC::FString& text,
		SDK::UFont* font,
		const SDK::FLinearColor& normal_col,
		const SDK::FLinearColor& hover_col,
		const SDK::FLinearColor& press_col
	);

	static bool button_color_text(
		const SDK::FVector2D& pos,
		const SDK::FVector2D& size,
		const UC::FString& text,
		SDK::UFont* font,
		const SDK::FLinearColor& text_col,
		const SDK::FLinearColor& normal_col,
		const SDK::FLinearColor& hover_col,
		const SDK::FLinearColor& press_col
	);

	static void check_box(
		const SDK::FVector2D& pos,
		const SDK::FVector2D& size,
		const SDK::FVector2D& check_size,
		const SDK::FLinearColor& check_col,
		const SDK::FLinearColor& normal_col,
		const SDK::FLinearColor& hover_col,
		const SDK::FLinearColor& press_col,
		bool* ptr
	);

private:
	static bool is_hover(
		const SDK::FVector2D& pos,
		const SDK::FVector2D& size
	);
};

