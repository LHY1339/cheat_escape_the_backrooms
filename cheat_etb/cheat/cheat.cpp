#include "cheat.h"

#include <iostream>

#include "_sdk.h"
#include "gui.h"
#include "gdefine.h"
#include "gvalue.h"
#include "menu.h"
#include "visual.h"
#include "player.h"
#include "entity.h"
#include "command.h"
#include "config.h"
#include "color.h"
#include "kismet.h"
#include "network.h"
#include "quick.h"
#include "vhook.h"
#include "keybind.h"
#include "test.h"
#include "_minhook.h"

#include <filesystem>

#pragma warning(disable:4996)

cheat* cheat::get()
{
    static cheat inst;
    return& inst;
}

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
    while (!kismet::get_window())
    {
        Sleep(100);
    }

    std::filesystem::path folder_path = "C:\\LHY1339\\escape_the_backrooms";
    if (!std::filesystem::exists(folder_path))
    {
        std::filesystem::create_directories(folder_path);
    }

    menu::get()->init();
    player::get()->init();
    entity::get()->init();
    visual::get()->init();
    command::get()->init();
    network::get()->init();
    quick::get()->init();

    config::get()->load("C:\\LHY1339\\escape_the_backrooms\\config.cheat");
    config::get()->load("C:\\LHY1339\\escape_the_backrooms\\keybind.cheat");
    color::get()->load();
}
//
//typedef SDK::UCreateSessionCallbackProxyAdvanced* (__fastcall* fn_create_session)(
//    SDK::UObject* WorldContextObject,
//    const SDK::TArray<SDK::FSessionPropertyKeyPair>& ExtraSettings,
//    SDK::APlayerController* PlayerController, 
//    int PublicConnections, 
//    int PrivateConnections,
//    bool bUseLAN, 
//    bool bAllowInvites, 
//    bool bIsDedicatedServer, 
//    bool bUsePresence, 
//    bool bUseLobbiesIfAvailable, 
//    bool bAllowJoinViaPresence, 
//    bool bAllowJoinViaPresenceFriendsOnly, 
//    bool bAntiCheatProtected, 
//    bool bUsesStats, 
//    bool bShouldAdvertise, 
//    bool bUseLobbiesVoiceChatIfAvailable, 
//    bool bStartAfterCreate, 
//    bool bGameSession
//    );
//
//fn_create_session def_create_session = nullptr;
//
//SDK::UCreateSessionCallbackProxyAdvanced* __fastcall hk_create_session(
//    SDK::UObject* WorldContextObject,
//    const SDK::TArray<SDK::FSessionPropertyKeyPair>& ExtraSettings,
//    SDK::APlayerController* PlayerController,
//    int PublicConnections,
//    int PrivateConnections,
//    bool bUseLAN,
//    bool bAllowInvites,
//    bool bIsDedicatedServer,
//    bool bUsePresence,
//    bool bUseLobbiesIfAvailable,
//    bool bAllowJoinViaPresence,
//    bool bAllowJoinViaPresenceFriendsOnly,
//    bool bAntiCheatProtected,
//    bool bUsesStats,
//    bool bShouldAdvertise,
//    bool bUseLobbiesVoiceChatIfAvailable,
//    bool bStartAfterCreate,
//    bool bGameSession
//)
//{
//    printf("hook called create session\n");
//    return def_create_session(
//        WorldContextObject,
//        ExtraSettings,
//        PlayerController,
//        10,
//        10,
//        bUseLAN,
//        bAllowInvites,
//        bIsDedicatedServer,
//        bUsePresence,
//        bUseLobbiesIfAvailable,
//        bAllowJoinViaPresence,
//        bAllowJoinViaPresenceFriendsOnly,
//        bAntiCheatProtected,
//        bUsesStats,
//        bShouldAdvertise,
//        bUseLobbiesVoiceChatIfAvailable,
//        bStartAfterCreate,
//        bGameSession
//    );
//}

//LONG hk_create_session(_EXCEPTION_POINTERS* Info)
//{
//    printf("hook called create session\n");
//    return EXCEPTION_CONTINUE_EXECUTION;
//}

void cheat::hook()
{
    vhook::get()->hook_func(hk_post_render, hk_wnd_proc);

    //MH_Initialize();

    //SDK::UFunction* func = SDK::UCreateSessionCallbackProxyAdvanced::StaticClass()->GetFunction(
    //    "CreateSessionCallbackProxyAdvanced", 
    //    "CreateAdvancedSession"
    //);
    //std::cout << "addr : 0x" << std::hex << (uintptr_t)func->ExecFunction - (uintptr_t)GetModuleHandle(nullptr) << std::endl;
    //uintptr_t targetAddr = (uintptr_t)func->ExecFunction;

    //MH_CreateHook((LPVOID)targetAddr, &hk_create_session, reinterpret_cast<LPVOID*>(&def_create_session));
    //MH_EnableHook((LPVOID)targetAddr);
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
        gvalue::delta_time = SDK::UGameplayStatics::GetWorldDeltaSeconds(gvalue::world);

        network::get()->main();
        gui::main();
        visual::get()->main();
        player::get()->main();
        entity::get()->main();
        menu::get()->main();
        quick::get()->main();

        test::get()->main();

        gvalue::def_post_render(thisptr, canvas);

        if (gvalue::is_exit)
        {
            vhook::get()->unhook_func();
            gvalue::is_clean = true;
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        printf("error code : %d\n", GetExceptionCode());
    }
}

LRESULT cheat::hk_wnd_proc(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param)
{
    switch (u_msg)
    {
    case WM_INPUT:
    {
        if (!gvalue::menu_open && !gvalue::quick_menu_open)
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
        if (w_param == VK_INSERT || w_param == VK_F1)
        {
            gvalue::menu_open = !gvalue::menu_open;
            break;
        }
        if (w_param == VK_DELETE)
        {
            gvalue::is_exit = true;
            break;
        }

        keybind::get()->call_bind(w_param);

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
    case WM_RBUTTONDOWN:
    case WM_RBUTTONDBLCLK:
        gvalue::mouse.right = true;
        break;
    case WM_RBUTTONUP:
        gvalue::mouse.right = false;
        break;
    }

    if (gvalue::menu_open || gvalue::quick_menu_open)
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