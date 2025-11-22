#pragma once
#include <string>

namespace SDK
{
	struct FVector2D;
	struct FLinearColor;
	class USceneComponent;
	class AActor;
}

namespace UC
{
	class FString;
}

struct s_esp;

class visual
{
public:
	static void init();
	static void main();
	static std::wstring find_name(const std::wstring& in_name);
private:
	static void get_all();
	static void camera();

	static bool get_box(SDK::USceneComponent* comp, SDK::FVector2D& min, SDK::FVector2D& max);
	static void draw_extent(SDK::USceneComponent* comp, const SDK::FLinearColor& color);
	static void draw(SDK::USceneComponent* comp, const SDK::FLinearColor& color, const UC::FString& name, const s_esp& esp, const bool& use_map = true);
};

