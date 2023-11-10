#include <windows.h>
#include <string>

#include "output_debug_stream.h"
#include "onigwrap.h"

using namespace std;

/*
005D9638  0�̖��B���̗v�����󂯂Ĉ�R�̏��ƂȂ�B���e����̒q�d�ƕ��E�����˔�����
005D967F  �B.I�����Ă�������...........
*/

/*
�i�U���b�N�n���啭��̎��ғ����B��������͂Q�{�̊p�A������͎����̗��𐶂₵���d���ȃT�L���o�X�B
�u���ߐ[�������̈����v�ٖ̈������␢�̔����B
*/

// �t�b�N����֐��̃v���g�^�C�v���`
using PFNTEXTOUTA = BOOL(WINAPI*)(HDC, int, int, LPCTSTR, int);
extern PROC pfnOrigTextOutA;


BOOL isNextStartOverride = false;  // ����TextOutA���Ă΂ꂽ�^�C�~���O�� isOverrideTextOut��TRUE�ɂ��邽�߂̃t���O
BOOL isOverrideTextOut = false;    // ���̃t���O��ON���ƁATextOut�͕`����X���[����悤�ɂ���B

BOOL isAlbedoRetsuden = false; // �A���x�h�̗�`��\�����Ȃ���΂Ȃ�Ȃ����Ƃ����o���邽�߂̐�p�t���O

char AlbedoRetsuden[256] = "�ɑ��B��������͂Q�{�̊p�A������͎����̗��𐶂₵���d���ȃT�L���o�X�B�u���ߐ[�������̈����v�ٖ̈������␢�̔����B�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@";
int nTextOutProceedCounter = 0;

extern std::string bufferTextOut;

BOOL pathOfBushouRetsuden(
	HDC hdc,           // �f�o�C�X�R���e�L�X�g�̃n���h��
	int nXStart,       // �J�n�ʒu�i��_�j�� x ���W
	int nYStart,       // �J�n�ʒu�i��_�j�� y ���W
	LPCTSTR lpString,  // ������
	int cbString       // ������
) {
	// �I�[�o�[���C�h�t���O�������Ă�����A�I�[�o�[���C�h����
	if (isNextStartOverride) {
		isOverrideTextOut = TRUE;
	}


	// �A���x�h�̕�����`�̏ꍇ�A�A���x�h���[�h�ɂ���B
	if (bufferTextOut.ends_with("������`������1535�`????")) {
		// ���ɂ����ɗ�����I�[�o�[���C�h����Ƃ����t���O
		isNextStartOverride = TRUE;
		isAlbedoRetsuden = TRUE;
		OutputDebugStream("�A���x�h�̕�����`\r\n");
	}

	// �A���x�h��`�ł͂Ȃ��B�����\�����Ȃ��悤�ɂ��Ă���
	if (!isAlbedoRetsuden) {

		if (OnigMatch(bufferTextOut, "������`.+�`\\?\\?\\?\\?��$", NULL)) {
		// if (bufferTextOut.ends_with("�`????��")) {
			char checkDummyRetsuden[256] = { 0 };

			// ��`�̒��g���R�s�[���Ă���
			strcpy_s(checkDummyRetsuden, 255, (char*)0x5D9638);
			// �u���������v��u���������v�������Ă�����A(�A���x�h�ȊO��)�����\�����Ȃ��B
			if (strstr(checkDummyRetsuden, "��������������������")) {
				isOverrideTextOut = TRUE;
			}
			if (strstr(checkDummyRetsuden, "��������������������")) {
				isOverrideTextOut = TRUE;
			}
		}
	}

	// �A���x�h���[�h�Ȃ�A��`�̕`��������A���x�h�̂��̂ŏ㏑��
	if (isOverrideTextOut && isAlbedoRetsuden) {
		// �����^�̕`���1�������Ȃ̂ŁA1�������ʂ̕�����`�悷��`�ƂȂ�B
		((PFNTEXTOUTA)pfnOrigTextOutA)(hdc, nXStart, nYStart, (char*)(AlbedoRetsuden + nTextOutProceedCounter), 2);
		nTextOutProceedCounter += 2;
	}

	return TRUE;
}