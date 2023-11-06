#include <windows.h>

BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved )
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

extern "C" __declspec(dllexport) void WINAPI onInitialize(void* reserved) {
    OutputDebugString("onInitialize\r\n");
}

extern "C" __declspec(dllexport) void WINAPI onGameInitialize() {
    OutputDebugString("onGameInitialize\r\n");
}

extern "C" __declspec(dllexport) void WINAPI onFinalize() {
    OutputDebugString("onFinalize\r\n");
}