#include <windows.h>
#include <string>
#include "output_debug_stream.h"
#include "game_menu.h"
#include "on_event.h"
#include "game_screen.h"
#include "hook_functions_direct.h"

int nCheckMenuCount = 0;

int prevMenuCount = 0;


BOOL Hook_SetMenuCustom(HWND hWnd, HMENU hMenu) {
	if (hMenu == NULL) {
		return FALSE;
	}

	int menu_count = GetMenuItemCount(hMenu);

	if (menu_count >= 8) {
		// 「ユニット」のメニューアイテムを全角に変更
		changeMenuItemString(hMenu, 226, "ユニット(&U)"); // 226はリソースエディタでわかる「ユニット」のメニューID

	}

	// 「ファイル」のPOPUPを全角に変更
	changePopupString(hMenu, 0, "ファイル(&F)");

	menu_count = GetMenuItemCount(hMenu); // 一応変わらないはずだけど再度取得しておく。

	// メニューのインスタンスが変更されている
	if (hMenu != hNB7MenuCheckChange) {
		hNB7MenuCheckChange = hMenu;

		// OutputDebugStream(std::to_string(count).c_str());
		// OutputDebugStream("個メニューが設定されます\r\n");
		// OutputDebugStream("メニューが変わりました\r\n");

		// OpeningMovie時のメニューは2個
		if (menu_count == 2) {
			changePopupString(hMenu, 1, "ムービー中止(&M)");
			if (nCheckMenuCount != menu_count) {
				nCheckMenuCount = menu_count;
				onOpeningMovie();
			}
		}

		// ゲームが出来る状態になると、メニューが9個になる。一応8個以上で判定。
		if (menu_count == 9) {
			// メニューを追加した
			addMenuItem(GetMenu(hWnd), "武将エディタ", RESOURCE_MENU_ID_BUSHOUEDIT_ORIGINAL, ADDITIONAL_MENU_ID_BUSYOUEDIT_KAI);
			addMenuItem(GetMenu(hWnd), "ユニットエディタ", RESOURCE_MENU_ID_BUSHOUEDIT_ORIGINAL, ADDITIONAL_MENU_ID_UNITEDIT_KAI);
			addMenuItem(GetMenu(hWnd), "大名エディタ", RESOURCE_MENU_ID_BUSHOUEDIT_ORIGINAL, ADDITIONAL_MENU_ID_DAIMYOEDIT_KAI);
			addMenuItem(GetMenu(hWnd), "家宝エディタ", RESOURCE_MENU_ID_BUSHOUEDIT_ORIGINAL, ADDITIONAL_MENU_ID_KAHOUEDIT_KAI);
			addMenuItem(GetMenu(hWnd), "官位エディタ", RESOURCE_MENU_ID_BUSHOUEDIT_ORIGINAL, ADDITIONAL_MENU_ID_KANNIEDIT_KAI);
			addMenuItem(GetMenu(hWnd), "役職エディタ", RESOURCE_MENU_ID_BUSHOUEDIT_ORIGINAL, ADDITIONAL_MENU_ID_YAKUSYOKUEDIT_KAI);
			addMenuItem(GetMenu(hWnd), "年月エディタ", RESOURCE_MENU_ID_BUSHOUEDIT_ORIGINAL, ADDITIONAL_MENU_ID_NENNGETSUEDIT_KAI);
			addMenuItem(GetMenu(hWnd), "---", RESOURCE_MENU_ID_BUSHOUEDIT_ORIGINAL, NULL);
		}
	}

	if (prevMenuCount != menu_count) {

		if (menu_count == 3) {
			if (prevMenuCount == 9) {
				onCastleBattlePreStart();
			}
			OutputDebugStream("籠城戦スクリーン中である\n");
		}

		if (menu_count == 4) {
			if (prevMenuCount == 9) {
				onYasenBattlePreStart();
			}
			OutputDebugStream("戦闘スクリーン中である\n");
		}

		if (menu_count == 9) {


			if (prevMenuCount == 4) {
				onYasenBattleEnd();
			}
			else if (prevMenuCount == 3) {
				onCastleBattleEnd();
			}

			// 初期状態
			else {
				onStrategyScreen();
			}

			OutputDebugStream("戦術スクリーン中である\n");
		}

		prevMenuCount = menu_count;

	}

	return true;
}
