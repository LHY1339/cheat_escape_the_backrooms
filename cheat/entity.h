#pragma once
#include "_sdk.h"
#include <string>

class entity
{
public:
	static void init();
	static void main();
	static void kill_all();
	static void kill(const std::string& name);
	static void spawn(SDK::TSubclassOf<SDK::AActor> cls);
	static void poss(SDK::APawn* pawn);
	static void unposs();
};