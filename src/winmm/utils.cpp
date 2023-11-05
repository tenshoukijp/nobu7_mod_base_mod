#include <windows.h>
#include <string>

using LPFN_ISWOW64PROCESS = BOOL (WINAPI*)(HANDLE, PBOOL);
LPFN_ISWOW64PROCESS fnIsWow64Process;

BOOL IsWow64()
{
    BOOL bIsWow64 = FALSE;

    //IsWow64Process is not available on all supported versions of Windows.
    //Use GetModuleHandle to get a handle to the DLL that contains the function
    //and GetProcAddress to get a pointer to the function if available.

    fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(
        GetModuleHandle(TEXT("kernel32")), "IsWow64Process");

    if (NULL != fnIsWow64Process)
    {
        if (!fnIsWow64Process(GetCurrentProcess(), &bIsWow64))
        {
            //handle error
        }
    }
    return bIsWow64;
}

std::string GetSysWow64WinmmPath() {
    extern BOOL IsWow64();
    if (!IsWow64()) {
        MessageBox(NULL, "�G���[", "�uSysWow64�v���ł͂Ȃ��悤�ł��B", NULL);
        return "";
    }

    // C:\Windows\SysWow64�̃p�X���擾�B�قƂ�ǑS�Ă̐l��C�h���C�u����ύX���Ă��Ȃ��Ƃ͎v����...
    char sysWow64Path[512] = "";
    UINT hasWow64Path = GetSystemWow64DirectoryA(sysWow64Path, sizeof(sysWow64Path));
    if (hasWow64Path == 0) {
        MessageBox(NULL, "�G���[", "�uSysWow64�v�̃p�X���擾�ł��܂���ł����B", NULL);
        return "";
    }
    strcat_s(sysWow64Path, "\\winmm.dll");

    return sysWow64Path;
}