#include "loader.h"

#include <TlHelp32.h>
#include <atlstr.h>
#include <iostream>

#include "gconst.h"

loader* loader::get()
{
    static loader inst;
    return &inst;
}

int loader::main()
{
    SetConsoleTitle(L"[LHY1339] 修改器");

    HWND hwnd = GetConsoleWindow();
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~WS_MAXIMIZEBOX;
    style &= ~WS_SIZEBOX;
    SetWindowLong(hwnd, GWL_STYLE, style);
    SetWindowPos(hwnd, NULL, 0, 0, 700, 500, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);

    print_log();

    while (true)
    {
        Sleep(1000);
        const DWORD pid = find_process(gconst::wnd_name);
        if (!pid)
        {
            continue;
        }
        std::wstring dll_path = get_abs_path(gconst::dll_name);
        if (is_load(pid, gconst::dll_name))
        {
            printf("[pid : %d] 请勿重复加载\n", static_cast<int>(pid));
            break;
        }
        if (inject(dll_path.c_str(), pid))
        {
            printf("[pid : %d] 加载成功\n", static_cast<int>(pid));
            break;
        }
    }
    return 0;
}

void loader::print_log()
{
    printf(R"(
 /##       /##   /## /##     /##  /##    /######   /######   /###### 
| ##      | ##  | ##|  ##   /##//####   /##__  ## /##__  ## /##__  ##
| ##      | ##  | ## \  ## /##/|_  ##  |__/  \ ##|__/  \ ##| ##  \ ##
| ##      | ########  \  ####/   | ##     /#####/   /#####/|  #######
| ##      | ##__  ##   \  ##/    | ##    |___  ##  |___  ## \____  ##
| ##      | ##  | ##    | ##     | ##   /##  \ ## /##  \ ## /##  \ ##
| ########| ##  | ##    | ##    /######|  ######/|  ######/|  ######/
|________/|__/  |__/    |__/   |______/ \______/  \______/  \______/ 

)");

    printf("--------------------------------------------------------\n\n");
    printf("- 请在启动本程序之前关闭所有杀毒软件（包括Windows自带的Defender）\n\n");
    printf("- 请不要运行任何反作弊程序（ACE等），不然可能会被误封\n\n");
    printf("- 请运行游戏，运行后自动加载修改器\n\n");
    printf("- 任何问题加QQ群：1071845133\n\n");
    printf("--------------------------------------------------------\n\n");
}

DWORD loader::find_process(const wchar_t* name)
{
    DWORD pid = 0;
    HWND hwnd = FindWindowW(L"UnrealWindow", name);
    if (!hwnd)
    {
        return FALSE;
    }
    GetWindowThreadProcessId(hwnd, &pid);
    return pid;
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
        } 
        while (Module32NextW(h_snap, &me32));
    }
    CloseHandle(h_snap);
    return false;
}
