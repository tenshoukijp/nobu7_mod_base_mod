#include <windows.h>
#include "loadmod.h"
#include "output_debug_stream.h"

using PFNONINITIALIZE = void (WINAPI*)(void*);
using PFNONFINALIZE = void (WINAPI*)();
using PFNONMMIOOPENA = void (WINAPI*)(char*, char*);

PFNONINITIALIZE pMod_onInitialize = NULL;
PFNONFINALIZE   pMod_onFinalize = NULL;
PFNONMMIOOPENA  pMod_onMmioOpenA = NULL;

// «¯^Mod.dllÌÇÝÝ
HMODULE hNB7ModDll = NULL;
BOOL loadNB7Mod() {

	hNB7ModDll = LoadLibrary("«¯^.mod.dll");

	// ¶ÝµÈ¢
	if (!hNB7ModDll) {
		// MessageBoxA(NULL, "«¯^Modª³¢", "G[", NULL);
		OutputDebugStream("«¯^Modª³¢\n");
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

void Mod_onMmioOpenA(char* pszFileName, char* bufOverrideFileName) {
	pMod_onMmioOpenA = (PFNONMMIOOPENA)GetProcAddress(hNB7ModDll, "onMmioOpenA");
	if (hNB7ModDll && pMod_onMmioOpenA) {
		pMod_onMmioOpenA(pszFileName, bufOverrideFileName);
	}
}

