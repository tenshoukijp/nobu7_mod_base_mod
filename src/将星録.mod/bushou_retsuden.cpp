#include <windows.h>
#include <string>

#include "data_game_struct.h"
#include "output_debug_stream.h"
#include "onigwrap.h"
#include "hook_textouta_custom.h"
#include "bushou_albedo.h"
#include "on_serihu_message.h"
#include "hook_textouta_custom.h"

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



BOOL isAlbedoRetsuden = false; // �A���x�h�̗�`��\�����Ȃ���΂Ȃ�Ȃ����Ƃ����o���邽�߂̐�p�t���O

char pszAlbedoRetsuden[256] = "�ɑ��B��������͂Q�{�̊p�A������͎����̗��𐶂₵���d���ȃT�L���o�X�B�u���ߐ[�������̈����v�ٖ̈������␢�̔����B�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@";

extern std::string bufferTextOut;

BOOL patchOfBushouRetsuden(
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

	if (bufferTextOut.ends_with("������`")) {
		int iBushouID = getLatestRetsudenBushouID();
		if (isValidBushouID(iBushouID)) {
			OutputDebugStream("����������ID:%d:%s�̕�����`\n", iBushouID, nb7�������[iBushouID].����);
		}
	}

	// �A���x�h�̕�����`�̏ꍇ�A�A���x�h���[�h�ɂ���B
	if (bufferTextOut.ends_with("������`" + getArubedoMei() + "1535�`????")) {
		// ���ɂ����ɗ�����I�[�o�[���C�h����Ƃ����t���O
		isNextStartOverride = TRUE;
		isAlbedoRetsuden = TRUE;
		OutputDebugStream("�A���x�h�̕�����`\r\n");
	}

	// �A���x�h��`�ł͂Ȃ��B�����\�����Ȃ��悤�ɂ��Ă���
	if (!isAlbedoRetsuden) {

		if (OnigMatch(bufferTextOut, "������`.+�`\\?\\?\\?\\?��$", NULL)) {
		// if (bufferTextOut.ends_with("�`????��")) {

			// ��`�̒��g���R�s�[���Ă���
			string checkDummyRetsuden = (char *)(�Z���t���b�Z�[�W�A�h���X);
			// �u���������v��u���������v�������Ă�����A(�A���x�h�ȊO��)�����\�����Ȃ��B
			if (checkDummyRetsuden.find("��������������������") != string::npos) {
				isOverrideTextOut = TRUE;
			}
			if (checkDummyRetsuden.find("��������������������") != string::npos) {
				isOverrideTextOut = TRUE;
			}
		}
	}

	// �A���x�h���[�h�Ȃ�A��`�̕`��������A���x�h�̂��̂ŏ㏑��
	if (isOverrideTextOut && isAlbedoRetsuden) {
		// �����^�̕`���1�������Ȃ̂ŁA1�������ʂ̕�����`�悷��`�ƂȂ�B
		((PFNTEXTOUTA)pfnOrigTextOutA)(hdc, nXStart, nYStart, (char*)(pszAlbedoRetsuden + nTextOutProceedCounter), 2);
		nTextOutProceedCounter += 2;
	}

	return TRUE;
}