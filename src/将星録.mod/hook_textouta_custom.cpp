#include <windows.h>
#include <string>

#include "window.h"

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

BOOL isNextStartOverride = false;  // ����TextOutA���Ă΂ꂽ�^�C�~���O�� isOverrideTextOut��TRUE�ɂ��邽�߂̃t���O
BOOL isOverrideTextOut = false;    // ���̃t���O��ON���ƁATextOut�͕`����X���[����悤�ɂ���B
int nTextOutProceedCounter = 0;    // TextOutA�̕`��������㏑�����邽�߂̃J�E���^


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

	string message = (char*)(�Z���t���b�Z�[�W�A�h���X); // on_serihu_message
	if (prevSerihuMessage != message) {
		onChangeSerifuMessage(message);
		prevSerihuMessage = message;
	}

	// ������`�p�̓��ʂȃp�b�`����
	patchOfBushouRetsuden(hdc, nXStart, nYStart, lpString, cbString);

	// �����Z���t�̓��ʂȃp�b�`����
	patchOfBushouMessage(hdc, nXStart, nYStart, lpString, cbString);

	return TRUE;
}
