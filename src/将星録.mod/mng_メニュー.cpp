#include <windows.h>
#include <string>
#include <map>
#include "mng_メニュー列挙.h"
#include "mng_メニュー.h"
#include "game_menu.h"
#include "mng_文字列変換.h"

extern HWND hNB7Wnd;



std::map<std::string, int> addMenuMap;

#define USER_MENUID_MIN 60001
#define USER_MENUID_MAX 60050
int menuMapCounter = USER_MENUID_MIN;
int 将星録::アプリケーション::メニュー::項目追加(System::String^ ラベル)
{
	HMENU hMenu = GetMenu(hNB7Wnd);
	std::string native_add_menu_name = to_native_string(ラベル);

	int menuID = -1;
	// メニュー名がすでに存在している
	if (addMenuMap.contains(native_add_menu_name)) {
		menuID = addMenuMap[native_add_menu_name];
	}
	else {
		menuID = menuMapCounter;
		addMenuMap[native_add_menu_name] = menuID;
		menuMapCounter++;
	}

	if (USER_MENUID_MIN <= menuID && menuID <= USER_MENUID_MAX) {
		// メニューを追加した
		insertMenuItem(hMenu, native_add_menu_name.c_str(), RESOURCE_MENU_ID_KAIZOU_END, menuID);
	}

	return menuID;
}
