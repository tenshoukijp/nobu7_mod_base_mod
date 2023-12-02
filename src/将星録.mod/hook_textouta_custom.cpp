#include <windows.h>
#include <string>

#include "game_window.h"

#include "hook_textouta_custom.h"

#include "bushou_retsuden.h"
#include "on_serihu_message.h"

using namespace std;


string bufferTextOut = "";
int nCheckTextOutYStart = -1;
int nCheckTextOutXStart = -1;

const string getBufferTextOut() {
	return bufferTextOut;
}


extern string prevSerihuMessage;

BOOL Hook_TextOutACustom(
	HDC hdc,           // �f�o�C�X�R���e�L�X�g�̃n���h��
	int nXStart,       // �J�n�ʒu�i��_�j�� x ���W
	int nYStart,       // �J�n�ʒu�i��_�j�� y ���W
	LPCTSTR lpString,  // ������
	int cbString       // ������
) {
	// �S�~�������Ă���悤�Ȃ̂ŁAcbString�̎w�蕪�����Y���Memcpy����
	char buffer[1024] = { 0 };
	memcpy(buffer, lpString, cbString);
	bufferTextOut += buffer;

	return TRUE;
}
