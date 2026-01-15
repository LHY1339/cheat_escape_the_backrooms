#pragma once
#include "_sdk.h"
#include <string>

class entity
{
public:
	static entity* get();

	void init();
	void main();
	void kill_all();
	void kill(const std::string& name);
	void spawn(SDK::TSubclassOf<SDK::AActor> cls);
	void poss(SDK::APawn* pawn);
	void unposs();

private:
	entity() = default;
	void domain();
};