#pragma once

#include <shellapi.h>
#include <string>

/*
MENUITEM "�I��(&X)",  181
*/

#define RESOURCE_MENU_ID_EXIT	181  // �u�I���v�̃��j���[�̃��\�[�XID��181 (Nobunaga7WPK.exe �����\�[�X�n�b�J�[�Ō���)

HMENU getNB7MenuHandle(HWND hWnd);

extern HMENU hNB7Menu;

void addMenuItem(std::string menuname, int position, int wID);
