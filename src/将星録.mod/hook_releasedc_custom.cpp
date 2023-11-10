#include <windows.h>
#include <string>
using namespace std;

extern string bufferTextOut;
extern int nTextOutProceedCounter;

extern BOOL isOverrideTextOut;
extern BOOL isNextStartOverride;

extern BOOL isAlbedoRetsuden;

int Hook_ReleaseDCCustom(
	HWND hWnd,  // ウィンドウのハンドル
	HDC hDC     // デバイスコンテキストのハンドル
) {
	if (bufferTextOut != "") {
		OutputDebugString(bufferTextOut.c_str());
		OutputDebugString("------------\n");
	}
	bufferTextOut = "";
	nTextOutProceedCounter = 0;

	// DCへの描画中に立ては各種フラグは、このReleaseDCのタイミングでおろすようにする。
	isOverrideTextOut = false;
	isNextStartOverride = false;
	isAlbedoRetsuden = false;

	return 1;
}
