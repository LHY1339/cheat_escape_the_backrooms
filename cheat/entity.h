#pragma once
#include "_sdk.h"
#include <string>

class entity
{
public:
	static void kill_all();
	static void kill(const std::string& name);
};