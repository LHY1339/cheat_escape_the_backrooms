#include "cheat.h"

#include <iostream>
#include <Windows.h>

#include "_sdk.h"
#include "gui.h"
#include "gdefine.h"
#include "gvalue.h"
#include "gconst.h"
#include "menu.h"
#include "visual.h"

#pragma warning(disable:4996)

void cheat::main()
{
	console();
	init();
	hook();
    exit();
}

void cheat::console()
{
#ifdef CHEAT_DEBUG
    AllocConsole();
    FILE* value = freopen("CONOUT$", "w+", stdout);
#endif
}

void cheat::init()
{
    menu::init();
    visual::init();
}

void cheat::hook()
{
    SDK::UWorld* world = nullptr;
    do
    {
        world = SDK::UWorld::GetWorld();
    } 
    while (!world);

    gvalue::vtb = *(void***)world->OwningGameInstance->LocalPlayers[0]->ViewportClient;
    DWORD protect = 0;
    VirtualProtect(gvalue::vtb, 1, PAGE_EXECUTE_READWRITE, &protect);

    gvalue::def_post_render = (fn_post_render)(gvalue::vtb[gconst::post_render_index]);
    gvalue::vtb[gconst::post_render_index] = &hk_post_render;

    gvalue::def_wnd_proc = (WNDPROC)SetWindowLongPtrA(FindWindow(L"UnrealWindow", nullptr), GWLP_WNDPROC, (LONG_PTR)hk_wnd_proc);
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
        printf("error code : %d", GetExceptionCode());
    }
}

LRESULT cheat::hk_wnd_proc(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param)
{
    switch (u_msg)
    {
    case WM_KEYDOWN:
        if (w_param == VK_INSERT)
        {
            gvalue::menu_open = !gvalue::menu_open;
        }
        else if (w_param == VK_DELETE)
        {
            gvalue::is_exit = true;
        }
        break;
    case WM_MOUSEMOVE:
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(hwnd, &pt);
        gvalue::mouse.x = pt.x;
        gvalue::mouse.y = pt.y;
        break;
    case WM_LBUTTONDBLCLK:
    case WM_LBUTTONDOWN:
        gvalue::mouse.left = true;
        break;
    case WM_LBUTTONUP:
        gvalue::mouse.left = false;
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