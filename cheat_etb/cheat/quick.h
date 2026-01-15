#pragma once

class quick
{
public:
	static quick* get();

	void init();
	void main();
private:
	quick() = default;

	void visual();
	void player();
	void entity();
	void item();
	void misc();

	void cursor();
};