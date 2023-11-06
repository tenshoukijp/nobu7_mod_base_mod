#include <windows.h>

#include "将星録.mod.h"


#pragma managed
extern "C" __declspec(dllexport) void WINAPI onInitialize(void* reserved) {
    OutputDebugString("onInitialize\r\n");
}

extern "C" __declspec(dllexport) void WINAPI onGameInitialize() {
    OutputDebugString("onGameInitialize\r\n");
}

extern "C" __declspec(dllexport) void WINAPI onFinalize() {
    OutputDebugString("onFinalize\r\n");
}
#pragma unmanaged