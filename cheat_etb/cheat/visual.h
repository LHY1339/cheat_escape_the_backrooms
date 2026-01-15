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
	static visual* get();

	void init();
	void main();
	std::wstring find_name(const std::string& in_name);
private:
	visual() = default;

	void get_all();
	void camera();

	bool get_box(SDK::USceneComponent* comp, SDK::FVector2D& min, SDK::FVector2D& max);
	void draw_extent(SDK::USceneComponent* comp, const SDK::FLinearColor& color);
	void draw(
		SDK::USceneComponent* comp, 
		const SDK::FLinearColor& color, 
		const std::string& name, 
		const s_esp& esp, 
		const bool& use_map = true,
		const std::wstring& player_name = L""
	);
};

