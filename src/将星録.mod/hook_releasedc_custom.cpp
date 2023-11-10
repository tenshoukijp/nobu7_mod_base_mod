#include <windows.h>
#include <string>
#include "output_debug_stream.h"
using namespace std;

extern string bufferTextOut;
extern int nTextOutProceedCounter;

extern BOOL isOverrideTextOut;
extern BOOL isNextStartOverride;

extern BOOL isAlbedoRetsuden;

extern int nCheckTextOutXStart;
extern int nCheckTextOutYStart;

int Hook_ReleaseDCCustom(
	HWND hWnd,  // ウィンドウのハンドル
	HDC hDC     // デバイスコンテキストのハンドル
) {
	nTextOutProceedCounter = 0;

	// DCへの描画中に立ては各種フラグは、このReleaseDCのタイミングでおろすようにする。
	isOverrideTextOut = false;
	isNextStartOverride = false;
	isAlbedoRetsuden = false;

	nCheckTextOutXStart = -1;
	nCheckTextOutYStart = -1;

	if (bufferTextOut != "") {
		OutputDebugStream(bufferTextOut);
		OutputDebugStream("------------\n");
	}
	bufferTextOut = "";

	return 1;
}
