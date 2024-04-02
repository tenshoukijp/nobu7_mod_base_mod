#include <windows.h>
#include <string>
#include <map>
#include "mng_���j���[��.h"
#include "mng_���j���[.h"
#include "game_menu.h"
#include "mng_������ϊ�.h"

extern HWND hNB7Wnd;



std::map<std::string, int> addMenuMap;

#define USER_MENUID_MIN 60001
#define USER_MENUID_MAX 60050
int menuMapCounter = USER_MENUID_MIN;
int �����^::�A�v���P�[�V����::���j���[::���ڒǉ�(System::String^ ���x��)
{
	HMENU hMenu = GetMenu(hNB7Wnd);
	std::string native_add_menu_name = to_native_string(���x��);

	int menuID = -1;
	// ���j���[�������łɑ��݂��Ă���
	if (addMenuMap.contains(native_add_menu_name)) {
		menuID = addMenuMap[native_add_menu_name];
	}
	else {
		menuID = menuMapCounter;
		addMenuMap[native_add_menu_name] = menuID;
		menuMapCounter++;
	}

	if (USER_MENUID_MIN <= menuID && menuID <= USER_MENUID_MAX) {
		// ���j���[��ǉ�����
		insertMenuItem(hMenu, native_add_menu_name.c_str(), RESOURCE_MENU_ID_KAIZOU_END, menuID);
	}

	return menuID;
}
