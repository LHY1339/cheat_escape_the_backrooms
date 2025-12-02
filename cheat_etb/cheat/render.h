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

class render
{
public:
	static void draw_box(
		const SDK::FVector2D& pos,
		const SDK::FVector2D& size,
		float thick,
		const SDK::FLinearColor& color
	);

	static void fill_box(
		const SDK::FVector2D& pos,
		const SDK::FVector2D& size,
		const SDK::FLinearColor& color
	);

	static void draw_text(
		SDK::UFont* font,
		const UC::FString& text,
		const SDK::FVector2D& pos,
		const SDK::FVector2D& size,
		const SDK::FLinearColor& color,
		float kerning,
		const SDK::FLinearColor& shadow_color,
		const SDK::FVector2D& shadow_offset,
		bool center_x,
		bool center_y,
		bool outline,
		const SDK::FLinearColor& outline_color
	);

	static void draw_line(
		const SDK::FVector2D& pos1,
		const SDK::FVector2D& pos2,
		float thick,
		const SDK::FLinearColor& color
	);
};

