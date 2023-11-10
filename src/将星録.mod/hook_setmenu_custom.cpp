#include <windows.h>
#include <string>
#include "output_debug_stream.h"
#include "menu.h"
#include "on_event.h"

int nCheckMenuCount = 0;

BOOL Hook_SetMenuCustom(HWND hWnd, HMENU hMenu) {
	if (hMenu == NULL) {
		return FALSE;
	}

	int count = GetMenuItemCount(hMenu);

	if (count >= 8) {
		// 「ユニット」のメニューアイテムを全角に変更
		changeMenuItemString(hMenu, 226, "ユニット(&U)"); // 226はリソースエディタでわかる「ユニット」のメニューID

	}

	// 「ファイル」のPOPUPを全角に変更
	changePopupString(hMenu, 0, "ファイル(&F)");

	int menu_count = GetMenuItemCount(hMenu);

	// メニューのインスタンスが変更されている
	if (hMenu != hNB7MenuCheckChange) {
		hNB7MenuCheckChange = hMenu;

		OutputDebugStream(std::to_string(count).c_str());
		OutputDebugStream("個メニューが設定されます\r\n");

		OutputDebugStream("メニューが変わりました\r\n");

		// OpeningMovie時のメニューは2個
		if (menu_count == 2) {
			changePopupString(hMenu, 1, "ムービー中止(&M)");
			if (nCheckMenuCount != menu_count) {
				nCheckMenuCount = menu_count;
				onOpeningMovie();
			}
		}

		// ゲームが出来る状態になると、メニューが9個になる。一応8個以上で判定。
		if (menu_count >= 8) {
			// メニューを追加した
			addMenuItem(GetMenu(hWnd), "メモリエディタ起動(&M)", RESOURCE_MENU_ID_BUSHOUEDIT, ADDITIONAL_MENU_ID_MEMORYEDITOR);
			addMenuItem(GetMenu(hWnd), "---", RESOURCE_MENU_ID_BUSHOUEDIT, NULL);

			OutputDebugStream("メニューを追加した\n");
		}
	}

	return true;
}
