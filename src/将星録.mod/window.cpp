#include <windows.h>
#include "menu.h"
#include "font.h"

HWND hNB7Wnd = NULL;

HWND* referenceOfNB7Wnd = NULL;

void onCreateWindow(HWND hWnd) {

	hNB7Wnd = hWnd;

	*referenceOfNB7Wnd = hWnd; // 呼び出し元に、「今回の起動ではちゃんとウィンドウが生成されたよ」と伝える。よってゲーム本体が起動された。

	OutputDebugString("ウィンドウ生成\n");

	hNB7MenuCheckChange = GetMenu(hNB7Wnd);

	// changePopupString(GetMenu(hNB7Wnd), 0, "ファイル(&F)");

	// メニューを追加した
	addMenuItem(GetSystemMenu(hNB7Wnd, FALSE), "メモ帳起動(&M)", RESOURCE_MENU_ID_EXIT, ADDITIONAL_MENU_ID_NOTEPAD);

	OutputDebugString("メニューを追加した\n");

	OutputDebugString("将星録の開始\n");

	// onFontInitialize();
}


void onDestroyWindow() {
	OutputDebugString("ウィンドウ破棄\r\n");
}
