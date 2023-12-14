/*
#include <windows.h>
#include <stdio.h>


void LogEsp() {
    // ESPレジスタの値を取得
    register int espValue;
    __asm {
        mov espValue, esp
    }

    // ログに出力
    printf("ESP: 0x%08X\n", espValue);
}

LONG WINAPI MyExceptionHandler(EXCEPTION_POINTERS *ExceptionInfo) {
    if (ExceptionInfo->ExceptionRecord->ExceptionCode == STATUS_GUARD_PAGE_VIOLATION) {
        // Guard Page Violationが発生するたびにESPをログに出力
        LogEsp();
        return EXCEPTION_CONTINUE_EXECUTION; // 続行
    }

    return EXCEPTION_CONTINUE_SEARCH; // 他のハンドラに任せる
}

int main() {
    BYTE *pMemory;
    SYSTEM_INFO si;
    GetSystemInfo(&si);

    // メモリアロケート
    pMemory = (BYTE*)VirtualAlloc(NULL, si.dwPageSize, MEM_COMMIT, PAGE_READWRITE);

    // ガードページとして設定
    DWORD oldProtect;
    VirtualProtect(pMemory, si.dwPageSize, PAGE_READWRITE | PAGE_GUARD, &oldProtect);

    // 自作の例外ハンドラを設定
    SetUnhandledExceptionFilter(MyExceptionHandler);

    // 特定のメモリアドレスに書き込み
    *pMemory = 0xFF; // ここで例外が発生する
    VirtualFree(pMemory, 0, MEM_RELEASE);

    return 0;
}
*/


