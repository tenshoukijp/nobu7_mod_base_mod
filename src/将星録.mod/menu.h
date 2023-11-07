#pragma once

#include <shellapi.h>
#include <string>

/*
MENUITEM "終了(&X)",  181
*/

#define RESOURCE_MENU_ID_EXIT	181  // 「終了」のメニューのリソースIDは181 (Nobunaga7WPK.exe をリソースハッカーで見ろ)

#define ADDITIONAL_MENU_ID_MEMORYEDITOR	59000  // 59000　からの独自メニュースタート

HMENU getNB7MenuHandle(HWND hWnd);

extern HMENU hNB7Menu;

void addMenuItem(std::string menuname, int position, int wID);

BOOL onMenuPushed(int iMenuID);
