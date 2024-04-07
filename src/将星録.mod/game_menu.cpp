#include <windows.h>
#include <string>
#include "output_debug_stream.h"
#include "game_menu.h"
#include "game_window.h"
#include "on_event.h"
#include "game_test.h"
#include "load_form_mod.h"

// #include "load_wpf_mod.h"
#include "usr_custom_mod.h"

#include "file_attribute.h"

#pragma comment(lib, "shell32.lib")

using namespace std;

HMENU hNB7MenuCheckChange = NULL;

void onMenuTestEditStart() {
	// Show_WpfMod("�e�X�g�G�f�B�^.mod.dll", "�����^.�e�X�g�G�f�B�^");
}
void onMenuBushouEditStart() {
	Show_FormMod("�����G�f�B�^.mod.dll", "�����^.�����G�f�B�^");
}

void onMenuDaimyoEditStart() {
	Show_FormMod("�喼�G�f�B�^.mod.dll", "�����^.�喼�G�f�B�^");
}

void onMenuCastleEditStart() {
	Show_FormMod("��G�f�B�^.mod.dll", "�����^.��G�f�B�^");
}

void onMenuUnitEditStart() {
	Show_FormMod("���j�b�g�G�f�B�^.mod.dll", "�����^.���j�b�g�G�f�B�^");
}

void onMenuKahouEditStart() {
	Show_FormMod("�ƕ�G�f�B�^.mod.dll", "�����^.�ƕ�G�f�B�^");
}

void onMenuKanniEditStart() {
	Show_FormMod("���ʃG�f�B�^.mod.dll", "�����^.���ʃG�f�B�^");
}

void onMenuYakusyokuEditStart() {
	Show_FormMod("��E�G�f�B�^.mod.dll", "�����^.��E�G�f�B�^");
}

void onMenuNenngetuSotaEditStart() {
	Show_FormMod("�N������G�f�B�^.mod.dll", "�����^.�N������G�f�B�^");
}

void onMenuYasenEditStart() {
	Show_FormMod("���G�f�B�^.mod.dll", "�����^.���G�f�B�^");
}

void onMenuYasenAttackButaiEditStart() {
	Show_FormMod("���U�������G�f�B�^.mod.dll", "�����^.���U�������G�f�B�^");
}

void onMenuYasenDefendButaiEditStart() {
	Show_FormMod("���h�䕔���G�f�B�^.mod.dll", "�����^.���h�䕔���G�f�B�^");
}

void onMenuRoujosenAttackButaiEditStart() {
	Show_FormMod("�ď��U�������G�f�B�^.mod.dll", "�����^.�ď��U�������G�f�B�^");
}

void onMenuRoujosenDefendButaiEditStart() {
	Show_FormMod("�ď��h�䕔���G�f�B�^.mod.dll", "�����^.�ď��h�䕔���G�f�B�^");
}

void onMenuModDebuggerLaunch() {
	if (isFileExists("moddebugger.exe")) {
		// ShellExecute(NULL, "open", "moddebugger.exe", NULL, NULL, SW_SHOW);
	}
}
// ���j���[(�ʏ�̃A�v���̃��j���[)�̃��j���[�A�C�e�������s�������A
// �ԍ��͎�Ƀ��\�[�X�G�f�B�^�Ŋm�F�ł���
BOOL onMenuPushed(HWND hWnd, int iMenuID) {

	try {
		System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
		dic->Add("���ڔԍ�", iMenuID);
		auto ret = InvokeUserMethod("on���j���[���ڎ��s��", dic);
	}
	catch (System::Exception^) {
		OutputDebugStream("on���j���[���ڎ��s�� �ŗ�O���������܂����B\n");
	}

	OutputDebugStream(iMenuID);
	OutputDebugStream("\r\n");
	switch (iMenuID) {
	case ADDITIONAL_MENU_ID_TEST_KAI:
		onMenuTestEditStart();
		return TRUE;
	case ADDITIONAL_MENU_ID_BUSYOUEDIT_KAI:
		onMenuBushouEditStart();
		return TRUE;
	case ADDITIONAL_MENU_ID_UNITEDIT_KAI:
		onMenuUnitEditStart();
		return TRUE;
	case ADDITIONAL_MENU_ID_DAIMYOEDIT_KAI:
		onMenuDaimyoEditStart();
		return TRUE;
	case ADDITIONAL_MENU_ID_CASTLEEDIT_KAI:
		onMenuCastleEditStart();
		return TRUE;
	case ADDITIONAL_MENU_ID_KAHOUEDIT_KAI:
		onMenuKahouEditStart();
		return TRUE;
	case ADDITIONAL_MENU_ID_KANNIEDIT_KAI:
		onMenuKanniEditStart();
		return TRUE;
	case ADDITIONAL_MENU_ID_YAKUSYOKUEDIT_KAI:
		onMenuYakusyokuEditStart();
		return TRUE;
	case ADDITIONAL_MENU_ID_NENNGETSUEDIT_KAI:
		onMenuNenngetuSotaEditStart();
		return TRUE;
	case ADDITIONAL_MENU_ID_YASENEDIT_KAI:
		onMenuYasenEditStart();
		return TRUE;
	case ADDITIONAL_MENU_ID_YASENATTACKBUTAI_EDIT_KAI:
		onMenuYasenAttackButaiEditStart();
		return TRUE;
	case ADDITIONAL_MENU_ID_YASENDEFENDBUTAI_EDIT_KAI:
		onMenuYasenDefendButaiEditStart();
		return TRUE;
	case ADDITIONAL_MENU_ID_ROUJOSENATTACKBUTAI_EDIT_KAI:
		onMenuRoujosenAttackButaiEditStart();
		return TRUE;
	case ADDITIONAL_MENU_ID_ROUJOSENDEFENDBUTAI_EDIT_KAI:
		onMenuRoujosenDefendButaiEditStart();
		return TRUE;
	case RESOURCE_MENU_ID_MODDEBUGGER:
		onMenuModDebuggerLaunch();
		return TRUE;
	case 313:
		onMenuOriginalBushouEditStart();
		return TRUE;
	case 314:
		onMenuOriginalShiroEditStart();
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

void ���[�U�J�X�^�����j���[() {
}

// �V�X�e�����j���[(�A�v���̍�����E�N���b�N�Ȃǂŏo�Ă��郁�j���[)�̃��j���[�A�C�e�������s�������A
BOOL onSystemMenuPushed(int iMenuID) {
	OutputDebugStream(iMenuID);
	OutputDebugStream("\r\n");

	try {
		System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
		dic->Add("���ڔԍ�", iMenuID);
		auto ret = InvokeUserMethod("on���j���[���ڎ��s��", dic);
	}
	catch (System::Exception^) {
		OutputDebugStream("on���j���[���ڎ��s�� �ŗ�O���������܂����B\n");
	}

	switch (iMenuID) {

		case ADDITIONAL_MENU_ID_NOTEPAD:
		{
#ifndef SUPER_RELEASE
			// ShellExecute(NULL, "open", "notepad.exe", NULL, NULL, SW_SHOW);

			doGameTest();


			return TRUE;
#endif
		}
		default: {
			
		}

	}
	return FALSE;
}

// ���j���[�A�C�e���̒ǉ�
// menuname ���j���[�A�C�e���̕�����B"---"���ƃZ�p���[�^�ƂȂ�B
void insertMenuItem(HMENU hTargetMenu, string menuname, int positionID, int menuID) {

	MENUITEMINFO info;

	// �쐬�������j���[���ڂ�ǉ�����
	ZeroMemory(&info, sizeof(info));
	info.cbSize = sizeof(info);

	// ID�ԍ��̎w�肪�����ꍇ
	if (menuID == -1) {
		info.fMask = MIIM_TYPE;
		// ID�ԍ��̎w�肪����ꍇ
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



// ���j���[�A�C�e���̒ǉ��B���h���[�t��(���j���[�A�C�e���͒ǉ����������ł͌����ڂ��ω����Ȃ��̂�)
void insertMenuItemAndRedraw(HMENU hTargetMenu, string menuname, int positionID, int menuID) {
	insertMenuItem(hTargetMenu, menuname, positionID, menuID);
	DrawMenuBar(hNB7Wnd);
}



// ���j���[�A�C�e���̕������ύX����֐�
void changeMenuItemString(HMENU hMenu, UINT iMenuID, const char* szNewString)
{
	MENUITEMINFO menuItemInfo;
	menuItemInfo.cbSize = sizeof(MENUITEMINFO);
	menuItemInfo.fMask = MIIM_STRING;
	menuItemInfo.dwTypeData = (LPSTR)szNewString;

	SetMenuItemInfoA(hMenu, iMenuID, FALSE, &menuItemInfo);
}

// ���j���[�A�C�e���̕������ύX����֐�
void changePopupString(HMENU hMenu, UINT iByPosition, const char* szNewString)
{
	MENUITEMINFO menuItemInfo;
	menuItemInfo.cbSize = sizeof(MENUITEMINFO);
	menuItemInfo.fMask = MIIM_STRING;
	menuItemInfo.dwTypeData = (LPSTR)szNewString;

	SetMenuItemInfoA(hMenu, iByPosition, TRUE, &menuItemInfo);
}

