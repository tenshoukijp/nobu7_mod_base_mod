#include <windows.h>
#include <string>
#include "output_debug_stream.h"
#include "on_event.h"
#include "hook_textouta_custom.h"
#include "on_serihu_message.h"
#include "bushou_albedo.h"
#include "data_game_struct.h"
#include "game_screen.h"
using namespace std;

extern string bufferTextOut;


extern int nCheckTextOutXStart;
extern int nCheckTextOutYStart;
int isKahouRetsudenMode = -1;

int Hook_ReleaseDCCustom(
	HWND hWnd,  // �E�B���h�E�̃n���h��
	HDC hDC     // �f�o�C�X�R���e�L�X�g�̃n���h��
) {

	nCheckTextOutXStart = -1;
	nCheckTextOutYStart = -1;

	if (bufferTextOut != "") {
		OutputDebugStream(bufferTextOut);
		OutputDebugStream("------------\n");
	}

	if (isKahouRetsudenMode > -1) {
		isKahouRetsudenMode--;
	}
	if (bufferTextOut == "�ƕ�ꗗ") {
		isKahouRetsudenMode = 3;
	}

	// �A���x�h�̍s���J�E���^�����炷
	decreaseAlbedoKoudouCounter();

	dispatchEvent();
	bufferTextOut = "";

	return 1;
}
