#include <windows.h>

#pragma unmanaged

HMODULE hè´êØò^ModDLL = NULL;

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        {
            hè´êØò^ModDLL = (HMODULE)hModule;
            break;
        }
        case DLL_THREAD_ATTACH:
        {
            break;
        }
        case DLL_THREAD_DETACH:
        {
            break;
        }
        case DLL_PROCESS_DETACH:
        {
            break;
        }
        default:
        {
            break;
        }

    } // switch

    return TRUE;
}

#pragma managed
