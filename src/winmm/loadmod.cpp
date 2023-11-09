#include <windows.h>
#include "loadmod.h"

using PFNONINITIALIZE = void (WINAPI*)(void*);
extern PFNONINITIALIZE pMod_onInitialize;

using PFNONGAMEINITIALIZE = void (WINAPI*)(HWND);
extern PFNONGAMEINITIALIZE pMod_onGameInitialize;

using PFNONFINALIZE = void (WINAPI*)();
extern PFNONFINALIZE pMod_onFinalize;

PFNONINITIALIZE pMod_onInitialize = NULL;
PFNONGAMEINITIALIZE pMod_onGameInitialize = NULL;
PFNONFINALIZE   pMod_onFinalize = NULL;

// �����^Mod.dll�̓ǂݍ���
HMODULE hNB7ModDll = NULL;
BOOL loadNB7Mod() {

	hNB7ModDll = LoadLibrary("�����^.mod.dll");

	// ���݂��Ȃ�
	if (!hNB7ModDll) {
		MessageBoxA(NULL, "�����^Mod������", "�G���[", NULL);
		return FALSE;
	}

	return TRUE;
}

void freeNB7Mod() {
	if (hNB7ModDll) {
		FreeLibrary(hNB7ModDll);
		hNB7ModDll = NULL;
	}
}

HWND hNB7Wnd = NULL;
void Mod_onInitialize() {
	pMod_onInitialize = (PFNONINITIALIZE)GetProcAddress(hNB7ModDll, "onInitialize");
	if (hNB7ModDll && pMod_onInitialize) {
		pMod_onInitialize(&hNB7Wnd);
	}
}
