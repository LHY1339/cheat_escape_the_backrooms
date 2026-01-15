#pragma once
#include <string>

class network
{
public:
	static network* get();

	void init();
	void main();
private:
	network() = default;

	void send(const std::string& str);
	void handle(const std::string& str);
};

