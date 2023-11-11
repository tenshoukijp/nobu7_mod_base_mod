#include <windows.h>

#include "JavaScript.mod.h"
#include "output_debug_stream.h"

using namespace System;

// 将星録.mod.dllから呼ばれる関数。概ね初期時に呼ばれる。
extern "C" __declspec(dllexport) void WINAPI onInitialize() {
	OutputDebugStream("JavaScript/onInitialize\r\n");
}

// 将星録.mod.dllから呼ばれる関数。フォント要求時
extern "C" __declspec(dllexport) void WINAPI onRequestFont() {
	OutputDebugStream("JavaScript/onFontInitialize\r\n");
}

// 将星録.mod.dllから呼ばれる関数。フォント要求時
extern "C" __declspec(dllexport) void WINAPI onRequestBGM() {
	OutputDebugStream("JavaScript/onRequestBGM\r\n");
}

// 将星録.mod.dllから呼ばれる関数。フォント要求時
extern "C" __declspec(dllexport) void WINAPI onRequestSound() {
	OutputDebugStream("JavaScript/onRequestSound\r\n");
}

// 将星録.mod.dllから呼ばれる関数。概ね最後に呼ばれる。
extern "C" __declspec(dllexport) void WINAPI onFinalize() {
	OutputDebugStream("JavaScript/onFinalize\r\n");
}
