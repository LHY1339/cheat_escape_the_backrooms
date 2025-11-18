#include "injector.h"

#include <TlHelp32.h>
#include <atlstr.h>

#include "gconst.h"

int injector::main()
{
    SetConsoleTitle(L"[LHY1339] 逃离后室修改器");

    HWND hwnd = GetConsoleWindow();
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~WS_MAXIMIZEBOX;
    style &= ~WS_SIZEBOX;
    SetWindowLong(hwnd, GWL_STYLE, style);
    SetWindowPos(hwnd, NULL, 0, 0, 600, 400, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);

    printf("请在启动本程序之前关闭所有杀毒软件（包括Windows自带的Defender）\n");
    printf("--------------------------------------------------------\n");
    printf("请运行游戏后按下 F5 加载\n");
    printf("--------------------------------------------------------\n");

    while (true)
    {
        static bool f5_down = false;
        if (GetAsyncKeyState(VK_F5) & 0x8000) 
        {
            if (!f5_down)
            {
                f5_down = true;

                const DWORD pid = find_process(gconst::proc_name);
                std::wstring dll_path = get_abs_path(gconst::dll_name);
                if (inject(dll_path.c_str(), pid))
                {
                    printf("[%d] 加载成功\n", static_cast<int>(pid));
                }
                else
                {
                    printf("[%d] 加载失败\n", static_cast<int>(pid));
                }
            }
        }
        else
        {
            f5_down = false;
        }
    }
    return 0;
}

DWORD injector::find_process(const wchar_t* name)
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

BOOL injector::inject(const wchar_t* dll_path, DWORD proc_id)
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

std::wstring injector::get_abs_path(const std::filesystem::path& rel_path)
{
    return std::filesystem::absolute(rel_path).wstring();
}
