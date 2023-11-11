#include <windows.h>
#include <string>
#include <shellapi.h>
#include "output_debug_stream.h"
#include "menu.h"
#include "window.h"
#include "on_event.h"

#pragma comment(lib, "shell32.lib")

using namespace std;

HMENU hNB7MenuCheckChange = NULL;

// メニュー(通常のアプリのメニュー)のメニューアイテムを実行した時、
// 番号は主にリソースエディタで確認できる
BOOL onMenuPushed(int iMenuID) {
	OutputDebugStream(iMenuID);
	OutputDebugStream("\r\n");
	switch (iMenuID) {
	case ADDITIONAL_MENU_ID_MEMORYEDITOR:
		ShellExecute(NULL, "open", "notepad.exe", NULL, NULL, SW_SHOW);
		return TRUE;
	case 313:
		onMenuBushouEditStart();
		return TRUE;
	case 314:
		onMenuShiroEditStart();
		return TRUE;
	case 302:
		onMenuNenpyoSengokushiStart();
		return TRUE;
	case 125:
		onMenuJyohoDaimyoIchiranStart();
		return TRUE;
	case 127:
		onMenuJyohoShiroIchiranStart();
		return TRUE;
	case 126:
		onMenuJyohoBushouIchiranStart();
		return TRUE;
	case 128:
		onMenuJyohoUnitIchiranStart();
		return TRUE;
	case 129:
		onMenuJyohoKahouIchiranStart();
		return TRUE;
	case 101:
		onMenuJyohoKanniIchiranStart();
		return TRUE;
	case 182:
		onMenuJyohoYakusyokuIchiranStart();
		return TRUE;
	case 115:
		onMenuCyuChizuStart();
		return TRUE;
	case 111:
		onMenuShiroIchiranStart();
		return TRUE;
	case 247:
		onMenuKashinBushoIchiranStart();
		return TRUE;
	case 226:
		onMenuKashinUnitIchiranStart();
		return TRUE;
	}
	return FALSE;
}

extern void setGameDataStructPointer();
// システムメニュー(アプリの左上を右クリックなどで出てくるメニュー)のメニューアイテムを実行した時、
BOOL onSystemMenuPushed(int iMenuID) {
	OutputDebugStream(iMenuID);
	OutputDebugStream("\r\n");
	switch (iMenuID) {
	case ADDITIONAL_MENU_ID_NOTEPAD:
		// ShellExecute(NULL, "open", "notepad.exe", NULL, NULL, SW_SHOW);

		setGameDataStructPointer();

		return TRUE;
	}
	return FALSE;
}


// メニューアイテムの追加
// menuname メニューアイテムの文字列。"---"だとセパレータとなる。
void addMenuItem(HMENU hTargetMenu, string menuname, int positionID, int menuID) {

	MENUITEMINFO info;

	// 作成したメニュー項目を追加する
	ZeroMemory(&info, sizeof(info));
	info.cbSize = sizeof(info);

	// ID番号の指定が無い場合
	if (menuID == -1) {
		info.fMask = MIIM_TYPE;
		// ID番号の指定がある場合
	}
	else {
		info.fMask = MIIM_TYPE | MIIM_ID;
		info.wID = menuID;
	}
	if (menuname == "---") {
		info.fType = MFT_SEPARATOR;
	}
	else {
		info.fType = MFT_STRING;
	}
	info.dwTypeData = (LPSTR)menuname.c_str();
	InsertMenuItem(hTargetMenu, positionID, FALSE, &info);
}

// メニューアイテムの追加。リドロー付き(メニューアイテムは追加しただけでは見た目が変化しないのだ)
void addMenuItemAndRedraw(HMENU hTargetMenu, string menuname, int positionID, int menuID) {
	addMenuItem(hTargetMenu, menuname, positionID, menuID);
	DrawMenuBar(hNB7Wnd);
}



// メニューアイテムの文字列を変更する関数
void changeMenuItemString(HMENU hMenu, UINT iMenuID, const char* szNewString)
{
	MENUITEMINFO menuItemInfo;
	menuItemInfo.cbSize = sizeof(MENUITEMINFO);
	menuItemInfo.fMask = MIIM_STRING;
	menuItemInfo.dwTypeData = (LPSTR)szNewString;

	SetMenuItemInfoA(hMenu, iMenuID, FALSE, &menuItemInfo);
}

// メニューアイテムの文字列を変更する関数
void changePopupString(HMENU hMenu, UINT iByPosition, const char* szNewString)
{
	MENUITEMINFO menuItemInfo;
	menuItemInfo.cbSize = sizeof(MENUITEMINFO);
	menuItemInfo.fMask = MIIM_STRING;
	menuItemInfo.dwTypeData = (LPSTR)szNewString;

	SetMenuItemInfoA(hMenu, iByPosition, TRUE, &menuItemInfo);
}

