#include <windows.h>
#include <string>



BOOL IsWow64()
{
    BOOL bIsWow64 = FALSE;

    // IsWow64Process は、サポートされている Windows のすべてのバージョンで使用できるわけではありません。
    // 関数を含むDLLへのハンドルを取得するにはGetModuleHandleを使用します。
    // GetProcAddressを使用して、関数へのポインタを取得します。

    using LPFN_ISWOW64PROCESS = BOOL(WINAPI*)(HANDLE, PBOOL);

    LPFN_ISWOW64PROCESS fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(
        GetModuleHandle("kernel32"), "IsWow64Process");

    if (NULL != fnIsWow64Process)
    {
        if (!fnIsWow64Process(GetCurrentProcess(), &bIsWow64))
        {
            //handle error
        }
    }
    return bIsWow64;
}


std::string GetCurrentProcessFullPath() {
    // 現在のプロセスをチェックする。なぜなら winmmは複数のプロセスから呼ばれてしまうであろうから。
    HANDLE hCurProc = GetCurrentProcess();
    char fullPathName[512] = "";
    GetModuleFileNameA(NULL, fullPathName, _countof(fullPathName));

    return fullPathName;
}