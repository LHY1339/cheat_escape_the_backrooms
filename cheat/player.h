#pragma once

#include <string>

namespace SDK
{
	struct FLinearColor;
	class AActor;
}

class player
{
public:
	static void init();
	static void main();
private:
	static void get_player();

	static void property();

	static void draw_extent(SDK::AActor* actor, const SDK::FLinearColor& color, const std::wstring& name);
};