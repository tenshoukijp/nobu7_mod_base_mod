#include <windows.h>
#include <string>
#include <shellapi.h>
#include "menu.h"
#include "window.h"

#pragma comment(lib, "shell32.lib")

using namespace std;

HMENU hNB7Menu = NULL;

HMENU getNB7MenuHandle(HWND hWnd) {
	hNB7Menu = GetSystemMenu(hWnd, FALSE);
	return hNB7Menu;
}

extern void WriteAsmJumperOnNb7FontnameAddressPush();

BOOL onMenuPushed(int iMenuID) {
	OutputDebugString(to_string(iMenuID).c_str());
	OutputDebugString("\r\n");
	switch (iMenuID) {
	case ADDITIONAL_MENU_ID_MEMORYEDITOR:
		ShellExecute(NULL, "open", "notepad.exe", NULL, NULL, SW_SHOW);
		return TRUE;
	}
	return FALSE;
}

// メニューアイテムの追加
// menuname メニューアイテムの文字列。"---"だとセパレータとなる。
void addMenuItem(string menuname, int position, int wID) {

	MENUITEMINFO info;

	// 作成したメニュー項目を追加する
	ZeroMemory(&info, sizeof(info));
	info.cbSize = sizeof(info);

	// ID番号の指定が無い場合
	if (wID == -1) {
		info.fMask = MIIM_TYPE;
		// ID番号の指定がある場合
	}
	else {
		info.fMask = MIIM_TYPE | MIIM_ID;
		info.wID = wID;
	}
	if (menuname == "---") {
		info.fType = MFT_SEPARATOR;
	}
	else {
		info.fType = MFT_STRING;
	}
	info.dwTypeData = (LPSTR)menuname.c_str();
	InsertMenuItem(hNB7Menu, position, FALSE, &info);
	DrawMenuBar(hNB7Wnd);
}
