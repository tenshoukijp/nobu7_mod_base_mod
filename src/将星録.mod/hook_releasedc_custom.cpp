#include <windows.h>
#include <string>
#include "output_debug_stream.h"
#include "on_event.h"

using namespace std;

extern string bufferTextOut;


extern int nCheckTextOutXStart;
extern int nCheckTextOutYStart;
extern HANDLE hFileITEMDATA;
int Hook_ReleaseDCCustom(
	HWND hWnd,  // ウィンドウのハンドル
	HDC hDC     // デバイスコンテキストのハンドル
) {

	nCheckTextOutXStart = -1;
	nCheckTextOutYStart = -1;

	if (bufferTextOut != "") {
		OutputDebugStream("■OnReleaseDC■:" + bufferTextOut);
		OutputDebugStream("------------\n");
	}

	dispatchEvent();
	bufferTextOut = "";

	return 1;
}
