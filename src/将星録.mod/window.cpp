#include <windows.h>
#include "menu.h"
#include "font.h"

HWND hNB7Wnd = NULL;

HWND* referenceOfNB7Wnd = NULL;

void onCreateWindow(HWND hWnd) {

	hNB7Wnd = hWnd;

	*referenceOfNB7Wnd = hWnd; // 呼び出し元に、「今回の起動ではちゃんとウィンドウが生成されたよ」と伝える。よってゲーム本体が起動された。

	OutputDebugString("ウィンドウ生成\n");

	hNB7Menu = getNB7MenuHandle(hWnd);

	// メニューを追加した
	addMenuItem("メモリエディタ起動(&M)", RESOURCE_MENU_ID_EXIT, ADDITIONAL_MENU_ID_MEMORYEDITOR); // Position 1 にメニューを追加する。IDは59000

	OutputDebugString("メニューを追加した\n");

	OutputDebugString("将星録の開始\n");

	onFontInitialize();
}
