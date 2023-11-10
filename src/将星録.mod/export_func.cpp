#include <windows.h>
#include <winuser.h>
#include <stdio.h>

#include "process.h"
#include "window.h"
#include "menu.h"
#include "font.h"

#include "hook_functions.h"

#pragma comment(lib, "user32.lib")

// WinMM.dllから呼ばれる関数。概ね初期時に呼ばれる。
extern "C" __declspec(dllexport) void WINAPI onInitialize(void* bufOfNB7Wnd) {
	// 本当に将星録本体のゲームが始まり、ウィンドウが描画されたのかのチェック。同じEXEでもランチャーへとバイパスされたりなど、色々あるためこのチェックが欠かせない。
	referenceOfNB7Wnd = (HWND *)bufOfNB7Wnd;

	hookFunctions();

	char buffer[256] = "";
	sprintf_s(buffer, _countof(buffer), "%x", nBaseAddress);
	OutputDebugString(buffer);

	OutputDebugString("onInitialize\r\n");
}

