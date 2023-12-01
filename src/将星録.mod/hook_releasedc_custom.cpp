#include <windows.h>
#include <string>
#include "output_debug_stream.h"
#include "on_event.h"
#include "hook_textouta_custom.h"
#include "on_serihu_message.h"
#include "bushou_albedo.h"

using namespace std;

extern string bufferTextOut;
extern int nTextOutProceedCounter;


extern int nCheckTextOutXStart;
extern int nCheckTextOutYStart;

int Hook_ReleaseDCCustom(
	HWND hWnd,  // �E�B���h�E�̃n���h��
	HDC hDC     // �f�o�C�X�R���e�L�X�g�̃n���h��
) {
	nTextOutProceedCounter = 0;

	// DC�ւ̕`�撆�ɗ��Ă͊e��t���O�́A����ReleaseDC�̃^�C�~���O�ł��낷�悤�ɂ���B
	isOverrideTextOut = FALSE;
	isNextStartOverride = FALSE;
	isAlbedoRetsuden = FALSE;

	nCheckTextOutXStart = -1;
	nCheckTextOutYStart = -1;

	if (bufferTextOut != "") {
		OutputDebugStream(bufferTextOut);
		OutputDebugStream("------------\n");
	}

	// �A���x�h�̍s���J�E���^�����炷
	decreaseAlbedoKoudouCounter();

	dispatchEvent();
	bufferTextOut = "";

	return 1;
}
