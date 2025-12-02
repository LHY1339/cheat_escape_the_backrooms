#include "loader.h"

#include "gvalue.h"
#include "gconst.h"
#include "gui.h"

#include <TlHelp32.h>
#include <atlstr.h>
#include <iostream>

#define GET_X_LPARAM(lParam) ((int)(short)LOWORD(lParam))
#define GET_Y_LPARAM(lParam) ((int)(short)HIWORD(lParam))

int loader::main()
{
	window();
	d2d();
	loop();
	return 0;
}

void loader::window()
{
	const wchar_t* wnd_class_name = L"LHY1339 Class";
	const wchar_t* wnd_name = L"LHY1339修改器";

	WNDCLASS wnd_class = {};
	wnd_class.hInstance = GetModuleHandle(nullptr);
	wnd_class.lpszClassName = wnd_class_name;
	wnd_class.lpfnWndProc = wnd_proc;
	RegisterClass(&wnd_class);

	gvalue::window = CreateWindow(
		wnd_class_name,
		wnd_name,
		WS_POPUP,
		100,
		100,
		gconst::window_w,
		gconst::window_h,
		nullptr,
		nullptr,
		GetModuleHandle(nullptr),
		nullptr
	);

	UnregisterClass(wnd_class_name, GetModuleHandleA(0));

	ShowWindow(gvalue::window, SW_SHOW);
}

void loader::d2d()
{
	D2D1CreateFactory(D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_SINGLE_THREADED, &gvalue::d2d1_factory);

	const D2D1_RENDER_TARGET_PROPERTIES rt_prop = D2D1::RenderTargetProperties();
	const D2D1_HWND_RENDER_TARGET_PROPERTIES rt_hwnd_prop = D2D1::HwndRenderTargetProperties(
		gvalue::window,
		D2D1::SizeU(gconst::window_w, gconst::window_h)
	);
	gvalue::d2d1_factory->CreateHwndRenderTarget(&rt_prop, &rt_hwnd_prop, &gvalue::render_target);

	gvalue::render_target->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), &gvalue::brush);

	DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED, 
		__uuidof(IDWriteFactory), 
		reinterpret_cast<IUnknown**>(&gvalue::dwrite_factory)
	);
	gvalue::dwrite_factory->CreateTextFormat(
		L"Arial",
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		15,
		L"",
		&gvalue::f15
	);
	gvalue::dwrite_factory->CreateTextFormat(
		L"Arial",
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		30,
		L"",
		&gvalue::f30
	);
}

void loader::loop()
{
	MSG msg = {};
	while (true)
	{
		if (gvalue::is_load)
		{
			break;
		}
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			gui::main();
			render();
		}
	}
	clean();
	MessageBox(nullptr, L"加载成功，请运行游戏", L"LHY1339", MB_OK);
	while (true)
	{
		const DWORD pid = find_process(gconst::proc_name);
		if (pid)
		{
			if (!is_load(pid, gconst::dll_name))
			{
				Sleep(1000);
				const std::wstring dll_path = get_abs_path(gconst::dll_name);
				inject(dll_path.c_str(), pid);
			}
			break;
		}
		Sleep(200);
	}
}

LRESULT loader::wnd_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	gvalue::mouse.left = (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
	switch (umsg)
	{
	case WM_MOUSEMOVE:
		gvalue::mouse.x = GET_X_LPARAM(lparam);
		gvalue::mouse.y = GET_Y_LPARAM(lparam);
		break;
	case WM_LBUTTONDOWN:
		PostMessage(gvalue::window, WM_NCLBUTTONDOWN, HTCAPTION, 0);
		break;
	case WM_SETCURSOR:
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		break;
	case WM_CLOSE:
		clean();
		exit(0);
	}
	return DefWindowProc(hwnd, umsg, wparam, lparam);
}

void loader::render()
{
	gvalue::render_target->BeginDraw();
	gvalue::render_target->Clear(gconst::outline_col);

	gvalue::brush->SetColor(gconst::back_col);
	gvalue::render_target->FillRectangle(D2D1::RectF(2, 2, gconst::window_w - 2, gconst::window_h - 2), gvalue::brush);

	gvalue::brush->SetColor(gconst::pice_col);
	gvalue::render_target->FillRectangle(D2D1::RectF(20, 20, gconst::window_w - 20, gconst::window_h - 20), gvalue::brush);

	gvalue::brush->SetColor(gconst::text_col);
	gvalue::f30->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	const wchar_t* title = L"LHY1339修改器";
	gvalue::render_target->DrawTextW(
		title,
		(UINT32)wcslen(title),
		gvalue::f30,
		D2D1::RectF(30, 30, gconst::window_w - 30, gconst::window_h - 30),
		gvalue::brush
	);

	gvalue::brush->SetColor(gconst::text_col);
	gvalue::f15->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	gvalue::f15->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	const wchar_t* tips =
		L"-- 加载方法 --\n"
		L"1.请关闭所有杀毒\n"
		L"2.点击加载修改器\n"
		L"3.启动游戏后自动加载修改器\n\n"
		L"-- 常见问题 --\n"
		L"问：怎么关杀毒？\n"
		L"答：退出火绒、360等杀毒软件，关闭Defender\n"
		L"问：能不能把DLL删了\n"
		L"答：不可以，删掉会加载失败\n\n"
		L"- 反馈QQ群：1071845133";
	gvalue::render_target->DrawTextW(
		tips,
		(UINT32)wcslen(tips),
		gvalue::f15,
		D2D1::RectF(30, 80, gconst::window_w - 30, gconst::window_h - 30),
		gvalue::brush
	);

	if (gui::button(D2D1::RectF(30, gconst::window_h - 60, gconst::window_w - 190, gconst::window_h - 30), L"加载修改器"))
	{
		gvalue::is_load = true;
	}

	if (gui::button(D2D1::RectF(gconst::window_w - 180, gconst::window_h - 60, gconst::window_w - 110, gconst::window_h - 30), L"更新"))
	{
		system("start https://github.com/LHY1339/cheat_escape_the_backrooms/releases");
	}

	if (gui::button(D2D1::RectF(gconst::window_w - 100, gconst::window_h - 60, gconst::window_w - 30, gconst::window_h - 30), L"退出"))
	{
		clean();
		exit(0);
	}

	gvalue::render_target->EndDraw();
}

void loader::clean()
{
	gvalue::d2d1_factory->Release();
	gvalue::dwrite_factory->Release();
	gvalue::f15->Release();
	gvalue::f30->Release();
	gvalue::render_target->Release();
	gvalue::brush->Release();
	DestroyWindow(gvalue::window);
}

DWORD loader::find_process(const wchar_t* name)
{
	HANDLE h_proc = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (!h_proc)
	{
		return FALSE;
	}
	PROCESSENTRY32 info;
	info.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(h_proc, &info))
	{
		return FALSE;
	}
	while (1)
	{
		if (_tcscmp(info.szExeFile, name) == 0)
		{
			return info.th32ProcessID;
		}
		if (!Process32Next(h_proc, &info))
		{
			return FALSE;
		}
	}
	return FALSE;
}

BOOL loader::inject(const wchar_t* dll_path, DWORD proc_id)
{
	HANDLE h_proc = OpenProcess(PROCESS_ALL_ACCESS, TRUE, proc_id);
	if (!h_proc)
	{
		return FALSE;
	}
	SIZE_T dll_path_len = (_tcslen(dll_path) + 1) * sizeof(wchar_t);
	LPVOID write_addr = VirtualAllocEx(h_proc, NULL, dll_path_len, MEM_COMMIT, PAGE_READWRITE);
	if (!write_addr)
	{
		return FALSE;
	}
	if (!WriteProcessMemory(h_proc, write_addr, dll_path, dll_path_len, NULL))
	{
		return FALSE;
	}
	PTHREAD_START_ROUTINE fn_addr = (PTHREAD_START_ROUTINE)GetProcAddress(
		GetModuleHandle(L"kernel32.dll"),
		"LoadLibraryW"
	);
	if (!fn_addr)
	{
		return FALSE;
	}
	HANDLE h_thread = CreateRemoteThreadEx(h_proc, NULL, NULL, fn_addr, write_addr, NULL, NULL, NULL);
	if (!h_thread)
	{
		return FALSE;
	}
	WaitForSingleObject(h_thread, INFINITE);
	CloseHandle(h_thread);
	CloseHandle(h_proc);
	return TRUE;
}

std::wstring loader::get_abs_path(const std::filesystem::path& rel_path)
{
	return std::filesystem::absolute(rel_path).wstring();
}

bool loader::is_load(DWORD pid, const wchar_t* dll_name)
{
	HANDLE h_snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	if (h_snap == INVALID_HANDLE_VALUE) return false;

	MODULEENTRY32W me32;
	me32.dwSize = sizeof(me32);

	if (Module32FirstW(h_snap, &me32))
	{
		do
		{
			if (_wcsicmp(me32.szModule, dll_name) == 0)
			{
				CloseHandle(h_snap);
				return true;
			}
		} while (Module32NextW(h_snap, &me32));
	}
	CloseHandle(h_snap);
	return false;
}