#pragma once
class menu
{
public:
	static menu* get();

	void init();
	void main();
private:
	menu() = default;

	void lable();
	void pre_base();
	void base();
	void cursor();

	void left();
	void visual();
	void player();
	void item();
	void entity();
	void level();
	void misc();
};

