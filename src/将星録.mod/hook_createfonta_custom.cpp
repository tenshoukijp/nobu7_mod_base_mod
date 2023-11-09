#include <windows.h>
#include <string>

#include "window.h"


BOOL Hook_CreateFontACustom(int, int, int, int, int, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, LPCSTR) {
	return TRUE;
}
