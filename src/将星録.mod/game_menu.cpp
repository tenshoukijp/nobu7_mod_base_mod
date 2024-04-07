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
	// Show_WpfMod("テストエディタ.mod.dll", "将星録.テストエディタ");
}
void onMenuBushouEditStart() {
	Show_FormMod("武将エディタ.mod.dll", "将星録.武将エディタ");
}

void onMenuDaimyoEditStart() {
	Show_FormMod("大名エディタ.mod.dll", "将星録.大名エディタ");
}

void onMenuCastleEditStart() {
	Show_FormMod("城エディタ.mod.dll", "将星録.城エディタ");
}

void onMenuUnitEditStart() {
	Show_FormMod("ユニットエディタ.mod.dll", "将星録.ユニットエディタ");
}

void onMenuKahouEditStart() {
	Show_FormMod("家宝エディタ.mod.dll", "将星録.家宝エディタ");
}

void onMenuKanniEditStart() {
	Show_FormMod("官位エディタ.mod.dll", "将星録.官位エディタ");
}

void onMenuYakusyokuEditStart() {
	Show_FormMod("役職エディタ.mod.dll", "将星録.役職エディタ");
}

void onMenuNenngetuSotaEditStart() {
	Show_FormMod("年月相場エディタ.mod.dll", "将星録.年月相場エディタ");
}

void onMenuYasenEditStart() {
	Show_FormMod("野戦エディタ.mod.dll", "将星録.野戦エディタ");
}

void onMenuYasenAttackButaiEditStart() {
	Show_FormMod("野戦攻撃部隊エディタ.mod.dll", "将星録.野戦攻撃部隊エディタ");
}

void onMenuYasenDefendButaiEditStart() {
	Show_FormMod("野戦防御部隊エディタ.mod.dll", "将星録.野戦防御部隊エディタ");
}

void onMenuRoujosenAttackButaiEditStart() {
	Show_FormMod("籠城戦攻撃部隊エディタ.mod.dll", "将星録.籠城戦攻撃部隊エディタ");
}

void onMenuRoujosenDefendButaiEditStart() {
	Show_FormMod("籠城戦防御部隊エディタ.mod.dll", "将星録.籠城戦防御部隊エディタ");
}

void onMenuModDebuggerLaunch() {
	if (isFileExists("moddebugger.exe")) {
		// ShellExecute(NULL, "open", "moddebugger.exe", NULL, NULL, SW_SHOW);
	}
}
// メニュー(通常のアプリのメニュー)のメニューアイテムを実行した時、
// 番号は主にリソースエディタで確認できる
BOOL onMenuPushed(HWND hWnd, int iMenuID) {

	try {
		System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
		dic->Add("項目番号", iMenuID);
		auto ret = InvokeUserMethod("onメニュー項目実行時", dic);
	}
	catch (System::Exception^) {
		OutputDebugStream("onメニュー項目実行時 で例外が発生しました。\n");
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

void ユーザカスタムメニュー() {
}

// システムメニュー(アプリの左上を右クリックなどで出てくるメニュー)のメニューアイテムを実行した時、
BOOL onSystemMenuPushed(int iMenuID) {
	OutputDebugStream(iMenuID);
	OutputDebugStream("\r\n");

	try {
		System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
		dic->Add("項目番号", iMenuID);
		auto ret = InvokeUserMethod("onメニュー項目実行時", dic);
	}
	catch (System::Exception^) {
		OutputDebugStream("onメニュー項目実行時 で例外が発生しました。\n");
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

// メニューアイテムの追加
// menuname メニューアイテムの文字列。"---"だとセパレータとなる。
void insertMenuItem(HMENU hTargetMenu, string menuname, int positionID, int menuID) {

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
void insertMenuItemAndRedraw(HMENU hTargetMenu, string menuname, int positionID, int menuID) {
	insertMenuItem(hTargetMenu, menuname, positionID, menuID);
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

