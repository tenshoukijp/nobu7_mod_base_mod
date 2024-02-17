#pragma once

#include <shellapi.h>
#include <string>

/*
MENUITEM "�I��(&X)",  181

MENUITEM "�����G�f�B�^(&B)",  313
MENUITEM "��G�f�B�^(&C)",  314
*/

#define RESOURCE_MENU_ID_EXIT		181  // �u�I���v�̃��j���[�̃��\�[�XID��181 (Nobunaga7WPK.exe �����\�[�X�n�b�J�[�Ō���)
#define RESOURCE_MENU_ID_BUSHOUEDIT_ORIGINAL	313  // �u�����ҏW�v�̃��j���[�̃��\�[�XID��313 (Nobunaga7WPK.exe �����\�[�X�n�b�J�[�Ō���)
#define RESOURCE_MENU_ID_CASTLEEDIT_ORIGINAL	314  // �u��ҏW�v�̃��j���[�̃��\�[�XID��314 (Nobunaga7WPK.exe �����\�[�X�n�b�J�[�Ō���)

#define RESOURCE_MENU_ID_KAIZOU_END			  59999  // �������j���[�̍Ō�̍���

#define ADDITIONAL_MENU_ID_NOTEPAD				59000  // 59000�@����̓Ǝ����j���[�X�^�[�g
#define ADDITIONAL_MENU_ID_BUSYOUEDIT_KAI		59001  
#define ADDITIONAL_MENU_ID_UNITEDIT_KAI			59002  
#define ADDITIONAL_MENU_ID_DAIMYOEDIT_KAI		59003  
#define ADDITIONAL_MENU_ID_KAHOUEDIT_KAI		59004  
#define ADDITIONAL_MENU_ID_KANNIEDIT_KAI		59005  
#define ADDITIONAL_MENU_ID_YAKUSYOKUEDIT_KAI	59006 
#define ADDITIONAL_MENU_ID_NENNGETSUEDIT_KAI	59007 



extern HMENU hNB7MenuCheckChange;

void insertMenuItem(HMENU hTargetMenu, std::string menuname, int positionID, int menuID);

BOOL onMenuPushed(HWND hWnd, int iMenuID);

BOOL onSystemMenuPushed(int iMenuID);

void changeMenuItemString(HMENU hMenu, UINT iMenuID, const char* szNewString);

void changePopupString(HMENU hMenu, UINT iByPosition, const char* szNewString);
