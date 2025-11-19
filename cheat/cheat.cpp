#include "cheat.h"

#include <iostream>
#include <Windows.h>

#include "_sdk.h"
#include "gvalue.h"
#include "gconst.h"
#include "menu.h"
#include "visual.h"
#include "gui.h"
#include "player.h"
#include "gdefine.h"
#include "config.h"
#include "entity.h"

#pragma warning(disable:4996)

std::unordered_map<std::string, int> key_map = 
{
    {"ins", VK_INSERT},
    {"del", VK_DELETE},
    {"home", VK_HOME},
    {"end", VK_END},
    {"pgup", VK_PRIOR},
    {"pgdn", VK_NEXT},
    {"up", VK_UP},
    {"down", VK_DOWN},
    {"left", VK_LEFT},
    {"right", VK_RIGHT},
    {"esc", VK_ESCAPE},
    {"tab", VK_TAB},
    {"enter", VK_RETURN},
    {"space", VK_SPACE},
    {"back", VK_BACK},

    {"f1", VK_F1}, {"f2", VK_F2}, {"f3", VK_F3}, {"f4", VK_F4},
    {"f5", VK_F5}, {"f6", VK_F6}, {"f7", VK_F7}, {"f8", VK_F8},
    {"f9", VK_F9}, {"f10", VK_F10}, {"f11", VK_F11}, {"f12", VK_F12},

    {"0", '0'}, {"1", '1'}, {"2", '2'}, {"3", '3'}, {"4", '4'},
    {"5", '5'}, {"6", '6'}, {"7", '7'}, {"8", '8'}, {"9", '9'},

    {"a", 'A'}, {"b", 'B'}, {"c", 'C'}, {"d", 'D'}, {"e", 'E'},
    {"f", 'F'}, {"g", 'G'}, {"h", 'H'}, {"i", 'I'}, {"j", 'J'},
    {"k", 'K'}, {"l", 'L'}, {"m", 'M'}, {"n", 'N'}, {"o", 'O'},
    {"p", 'P'}, {"q", 'Q'}, {"r", 'R'}, {"s", 'S'}, {"t", 'T'},
    {"u", 'U'}, {"v", 'V'}, {"w", 'W'}, {"x", 'X'}, {"y", 'Y'},
    {"z", 'Z'},

    {"none", -114514}
};

void cheat::main()
{
	console();
	init();
	hook();
    exit();
}

void cheat::console()
{
#ifdef MY_DEBUG
    AllocConsole();
    FILE* value = freopen("CONOUT$", "w+", stdout);
#endif
}

void cheat::init()
{
    visual::init();
    player::init();
    if (!config::file_exists("C:/LHY1339/escape_the_backrooms/key.txt"))
    {
        config::create("C:/LHY1339/escape_the_backrooms/key.txt"); 
    }
    config::load("C:/LHY1339/escape_the_backrooms/key.txt");
}

void cheat::hook()
{
    while (true)
    {
        SDK::UWorld* world = SDK::UWorld::GetWorld();
        if (world)
        {
            gvalue::vtb = *(void***)world->OwningGameInstance->LocalPlayers[0]->ViewportClient;
            DWORD protect = 0;
            VirtualProtect(gvalue::vtb, 1, PAGE_EXECUTE_READWRITE, &protect);

            gvalue::def_post_render = (fn_post_render)(gvalue::vtb[gconst::post_render_index]);
            gvalue::vtb[gconst::post_render_index] = &hk_post_render;

            gvalue::def_wnd_proc = (WNDPROC)SetWindowLongPtrA(FindWindow(L"UnrealWindow", nullptr), GWLP_WNDPROC, (LONG_PTR)hk_wnd_proc);

            RAWINPUTDEVICE rid;
            rid.usUsagePage = 0x01;
            rid.usUsage = 0x02;       // 鼠标
            rid.dwFlags = RIDEV_INPUTSINK;
            rid.hwndTarget = FindWindow(L"UnrealWindow", nullptr);

            RegisterRawInputDevices(&rid, 1, sizeof(rid));

            break;
        }
    }
}

void cheat::exit()
{
    while (!gvalue::is_clean)
    {
        Sleep(1);
    }
    FreeLibraryAndExitThread(gvalue::dll_inst, 0);
}

void cheat::hk_post_render(void* thisptr, SDK::UCanvas* canvas)
{
    __try
    {
        gvalue::world = SDK::UWorld::GetWorld();
        gvalue::controller = SDK::UGameplayStatics::GetPlayerController(gvalue::world, 0);
        gvalue::canvas = canvas;
        gvalue::engine = SDK::UEngine::GetEngine();

        gui::main();
        visual::main();
        player::main();
        entity::main();
        menu::main();

        gvalue::def_post_render(thisptr, canvas);

        if (gvalue::is_exit)
        {
            SetWindowLongPtrA(FindWindow(L"UnrealWindow", nullptr), GWLP_WNDPROC, (LONG_PTR)gvalue::def_wnd_proc);

            gvalue::vtb[gconst::post_render_index] = gvalue::def_post_render;

            gvalue::is_clean = true;
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        // 获取异常代码
        DWORD code = GetExceptionCode();
        std::cout << "异常代码: 0x" << std::hex << code << std::endl;

        //// 获取异常信息结构
        //EXCEPTION_POINTERS* ep = GetExceptionInformation();
        //if (ep && ep->ExceptionRecord)
        //{
        //    std::cout << "异常地址: " << ep->ExceptionRecord->ExceptionAddress << std::endl;
        //}
    }
}

LRESULT cheat::hk_wnd_proc(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param)
{
    switch (u_msg)
    {
    case WM_INPUT:
    {
        if (!gvalue::menu_open)
        {
            UINT dwSize = sizeof(RAWINPUT);
            static BYTE lpb[sizeof(RAWINPUT)];

            GetRawInputData((HRAWINPUT)l_param, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));

            RAWINPUT* raw = (RAWINPUT*)lpb;

            if (raw->header.dwType == RIM_TYPEMOUSE)
            {
                gvalue::x_offset = raw->data.mouse.lLastX;
                gvalue::y_offset = raw->data.mouse.lLastY;
            }
        }
    }
    case WM_KEYDOWN:
        if (w_param == get_key(gvalue::key_open_menu))
        {
            gvalue::menu_open = !gvalue::menu_open;
            break;
        }
        if (w_param == get_key(gvalue::key_close_menu))
        {
            gvalue::is_exit = true;
            break;
        }
        if (w_param == get_key(gvalue::key_draw_mesh))
        {
            gvalue::draw_mesh = !gvalue::draw_mesh;
            break;
        }
        if (w_param == get_key(gvalue::key_third_person))
        {
            gvalue::third_person = !gvalue::third_person;
            break;
        }
        if (w_param == get_key(gvalue::key_ghost_mode))
        {
            gvalue::ghost_mode = !gvalue::ghost_mode;
            break;
        }
        if (w_param == get_key(gvalue::key_inf_jump))
        {
            gvalue::inf_jump = !gvalue::inf_jump;
            break;
        }
        if (w_param == get_key(gvalue::key_fly_mode))
        {
            gvalue::fly_mode = !gvalue::fly_mode;
            break;
        }
        if (w_param == get_key(gvalue::key_x_delete))
        {
            gvalue::x_delete = !gvalue::x_delete;
            break;
        }
        if (w_param == get_key(gvalue::key_kill_all))
        {
            entity::kill_all();
            break;
        }
    case WM_MOUSEMOVE:
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(hwnd, &pt);
        gvalue::mouse_input.x = pt.x;
        gvalue::mouse_input.y = pt.y;

        break;
    case WM_LBUTTONDOWN:
    case WM_LBUTTONDBLCLK:
        gvalue::mouse_input.left = true;
        break;
    case WM_LBUTTONUP:
        gvalue::mouse_input.left = false;
        break;
    }

    if (gvalue::menu_open)
    {
        switch (u_msg)
        {
        case WM_INPUT:
        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_LBUTTONDBLCLK:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_RBUTTONDBLCLK:
        case WM_MOUSEWHEEL:
            return TRUE;
        }
    }
    return CallWindowProcA(gvalue::def_wnd_proc, hwnd, u_msg, w_param, l_param);
}

int cheat::get_key(const std::string& key)
{
    auto it = key_map.find(key);
    if (it != key_map.end())
    {
        return it->second;
    }
    return -114514;
}
