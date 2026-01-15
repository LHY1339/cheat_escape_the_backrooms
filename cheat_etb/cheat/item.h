#pragma once

#include "_sdk.h"

class item
{
public:
	static item* get();

	void spawn(SDK::TSubclassOf<SDK::AActor> actor_class);
	void interact_all(const std::string& name);

private:
	item() = default;
};