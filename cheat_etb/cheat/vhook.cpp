#include "vhook.h"
#include "_sdk.h"
#include "gvalue.h"
#include "kismet.h"

vhook* vhook::get()
{
	static vhook inst;
	return &inst;
}

void vhook::hook_func(void* post_render, void* wnd_proc)
{
    do
    {
        gvalue::world = SDK::UWorld::GetWorld();
    } while (!gvalue::world);

    gvalue::vtb = *(void***)gvalue::world->OwningGameInstance->LocalPlayers[0]->ViewportClient;
    DWORD protect = 0;
    VirtualProtect(&gvalue::vtb[0x63], 8, PAGE_EXECUTE_READWRITE, &protect);

    gvalue::def_post_render = (fn_post_render)(gvalue::vtb[0x63]);
    gvalue::vtb[0x63] = post_render;

    gvalue::def_wnd_proc = (WNDPROC)SetWindowLongPtrA(kismet::get_window(), GWLP_WNDPROC, (LONG_PTR)wnd_proc);
}

void vhook::unhook_func()
{
    SetWindowLongPtrA(kismet::get_window(), GWLP_WNDPROC, (LONG_PTR)gvalue::def_wnd_proc);
    gvalue::vtb[0x63] = gvalue::def_post_render;
}