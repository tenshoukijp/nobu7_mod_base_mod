#include <windows.h>
#include <string>
using namespace std;

extern string bufferTextOut;
extern int nTextOutProceedCounter;

extern BOOL isOverrideTextOut;
extern BOOL isNextStartOverride;

extern BOOL isAlbedoRetsuden;

int Hook_ReleaseDCCustom(
	HWND hWnd,  // �E�B���h�E�̃n���h��
	HDC hDC     // �f�o�C�X�R���e�L�X�g�̃n���h��
) {
	if (bufferTextOut != "") {
		OutputDebugString(bufferTextOut.c_str());
		OutputDebugString("------------\n");
	}
	bufferTextOut = "";
	nTextOutProceedCounter = 0;

	// DC�ւ̕`�撆�ɗ��Ă͊e��t���O�́A����ReleaseDC�̃^�C�~���O�ł��낷�悤�ɂ���B
	isOverrideTextOut = false;
	isNextStartOverride = false;
	isAlbedoRetsuden = false;

	return 1;
}
