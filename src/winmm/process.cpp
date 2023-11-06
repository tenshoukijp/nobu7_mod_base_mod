#include <windows.h>
#include <string>


BOOL isTargetProcessing = FALSE;

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


//------------------------------------------------
// プロセスID ⇒ HWND への変換
// 引数:プロセスID
// 戻り値: HWND もしくは NULL
//------------------------------------------------
HWND GetWindowHandleFromProcessId(const DWORD TargetID) {
    HWND hWnd = GetTopWindow(NULL);
    do {
        if (GetWindowLong(hWnd, GWL_HWNDPARENT) != 0 || !IsWindowVisible(hWnd)) {
            continue;
        }
        DWORD ProcessID;
        GetWindowThreadProcessId(hWnd, &ProcessID);
        if (TargetID == ProcessID) {
            return hWnd;
        }
    } while ((hWnd = GetNextWindow(hWnd, GW_HWNDNEXT)) != NULL);

    return NULL;
}


//------------------------------------------------
// 現在のウィンドウハンドルを得る
//------------------------------------------------
HWND GetCurrentWindowHandle() {
    // 実行中のプロセスIDを得る
    DWORD pID = GetCurrentProcessId();
    // プロセスID⇒ウィンドウハンドル
    HWND hWnd = GetWindowHandleFromProcessId(pID);
    return hWnd;
}

// 現在のウィンドウハンドルが、確かに天翔記HDのものかどうかをチェック
BOOL IsMatchCurrentClass(const char *pszClassName) {

    // ゲームランチャーからゲーム本体かどちらかのウィンドウがあるはず。
    HWND hWndNB7HDHandle = NULL;

    if (!hWndNB7HDHandle) { hWndNB7HDHandle = ::FindWindow(pszClassName, NULL); }

    HWND hWndCurrentHandle = GetCurrentWindowHandle();
    if (hWndNB7HDHandle == hWndCurrentHandle) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}
