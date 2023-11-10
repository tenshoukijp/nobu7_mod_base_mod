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
	HWND hWnd,  // �E�B���h�E�̃n���h��
	HDC hDC     // �f�o�C�X�R���e�L�X�g�̃n���h��
) {
	nTextOutProceedCounter = 0;

	// DC�ւ̕`�撆�ɗ��Ă͊e��t���O�́A����ReleaseDC�̃^�C�~���O�ł��낷�悤�ɂ���B
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
