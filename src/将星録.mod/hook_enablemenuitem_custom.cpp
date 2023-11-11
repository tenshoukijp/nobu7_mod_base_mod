#include <windows.h>

#include "output_debug_stream.h"

BOOL Hook_EnableMenuItemCustom(
	HMENU hMenu, // メニューのハンドル
	UINT uIDEnableItem, // メニュー項目の識別子または位置
	UINT uEnable // メニュー項目の状態
) {
	/*
	OutputDebugStream("uIDEnableItem:");
	OutputDebugStream((int)uIDEnableItem);
	*/

	char buffer[256] = "";
	if ((uEnable & 0x00000400) == 0x00000400) {
		// OutputDebugStream("MF_BYPOSITION\n");
		GetMenuString(hMenu, uIDEnableItem, (LPSTR)buffer, 100, MF_BYPOSITION);
		// OutputDebugStream(buffer);
	} else {
		// OutputDebugStream("MF_BYCOMMAND\n");
		GetMenuString(hMenu, uIDEnableItem, (LPSTR)buffer, 100, MF_BYCOMMAND);
		// OutputDebugStream(buffer);
	}

	if ((uEnable & 0x00000002) == 0x00000002) {
		// OutputDebugStream("MF_DISABLED\n");
	}
	else if ((uEnable & 0x00000001) == 0x00000001) {
		// OutputDebugStream("MF_GRAYED\n");
	}
	else {
		// OutputDebugStream("MF_ENABLED\n");
	}

	return TRUE;
}