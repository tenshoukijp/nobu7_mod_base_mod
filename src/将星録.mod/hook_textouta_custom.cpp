#include <windows.h>
#include <string>

#include "window.h"

#include "bushou_retsuden.h"

using namespace std;


string bufferTextOut = "";
int nCheckTextOutYStart = -1;
int nCheckTextOutXStart = -1;

const string getBufferTextOut() {
	return bufferTextOut;
}


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

	// ������`�p�̓��ʂȃp�b�`����
	pathOfBushouRetsuden(hdc, nXStart, nYStart, lpString, cbString);

	return TRUE;
}
