#include <windows.h>
#include <string>
#include "output_debug_stream.h"
#include "on_event.h"

using namespace std;

extern string bufferTextOut;

extern void onDrawText(string text);

extern HANDLE hFileITEMDATA;
int Hook_ReleaseDCCustom(
	HWND hWnd,  // ウィンドウのハンドル
	HDC hDC     // デバイスコンテキストのハンドル
) {

	if (bufferTextOut != "") {
		onDrawText(bufferTextOut);
	}

	dispatchEvent();
	bufferTextOut = "";

	return 1;
}
