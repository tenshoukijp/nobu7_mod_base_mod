#pragma once

#include <shellapi.h>
#include <string>

/*
 MENUITEM "�喼�ꗗ(&D)",  125
 */

#define RESOURCE_MENU_ID_DAIMYOICHIRAN_EXECUTE	125  // �喼�ꗗ �̃��j���[�̃��\�[�XID��125 (Nobunaga7WPK.exe �����\�[�X�n�b�J�[�Ō���)

HMENU getNB7MenuHandle(HWND hWnd);

extern HMENU hNB7Menu;

void addMenuItem(std::string menuname, int position, int wID);
