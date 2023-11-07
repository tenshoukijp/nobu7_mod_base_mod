#pragma once

#include <shellapi.h>
#include <string>

/*
 MENUITEM "大名一覧(&D)",  125
 */

#define RESOURCE_MENU_ID_DAIMYOICHIRAN_EXECUTE	125  // 大名一覧 のメニューのリソースIDは125 (Nobunaga7WPK.exe をリソースハッカーで見ろ)

HMENU getNB7MenuHandle(HWND hWnd);

extern HMENU hNB7Menu;

void addMenuItem(std::string menuname, int position, int wID);
