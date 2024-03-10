#include <windows.h>
#include <string>
#include "output_debug_stream.h"
#include "on_event.h"

using namespace std;

extern string bufferTextOut;

extern void onDrawText(string text);

extern int nCheckTextOutXStart;
extern int nCheckTextOutYStart;
extern HANDLE hFileITEMDATA;
int Hook_ReleaseDCCustom(
	HWND hWnd,  // �E�B���h�E�̃n���h��
	HDC hDC     // �f�o�C�X�R���e�L�X�g�̃n���h��
) {

	nCheckTextOutXStart = -1;
	nCheckTextOutYStart = -1;

	if (bufferTextOut != "") {
		onDrawText(bufferTextOut);
	}

	dispatchEvent();
	bufferTextOut = "";

	return 1;
}
