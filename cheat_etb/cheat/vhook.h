#pragma once
class vhook
{
public:
	static vhook* get();

	void hook_func(void* post_render, void* wnd_proc);
	void unhook_func();

private:
	vhook() = default;
};

