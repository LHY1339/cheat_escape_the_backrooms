#pragma once
class hook
{
public:
	static hook* get();

	void hook_func(void* post_render, void* wnd_proc);
	void unhook_func();

private:
	hook() = default;
};

