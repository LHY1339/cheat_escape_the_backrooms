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
	static player* get();

	void init();
	void main();
private:
	void get_player();

	void domain();

	void draw_extent(SDK::AActor* actor, const SDK::FLinearColor& color, const std::wstring& name);
};