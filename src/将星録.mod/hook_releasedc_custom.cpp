#include <windows.h>
#include <string>
#include "output_debug_stream.h"
#include "on_event.h"

using namespace std;

extern string bufferTextOut;

extern void onDrawText(string text);

extern HANDLE hFileITEMDATA;
int Hook_ReleaseDCCustom(
	HWND hWnd,  // �E�B���h�E�̃n���h��
	HDC hDC     // �f�o�C�X�R���e�L�X�g�̃n���h��
) {

	if (bufferTextOut != "") {
		onDrawText(bufferTextOut);
	}

	dispatchEvent();
	bufferTextOut = "";

	return 1;
}
