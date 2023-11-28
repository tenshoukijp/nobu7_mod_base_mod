#include <windows.h>
#include <string>

#include "output_debug_stream.h"
#include "bushou_retsuden.h"
#include "hook_textouta_custom.h"
#include "on_serihu_message.h"
#include "bushou_albedo.h"
#include "onigwrap.h"
#include <time.h>

using namespace std;

// �t�b�N����֐��̃v���g�^�C�v���`
using PFNTEXTOUTA = BOOL(WINAPI*)(HDC, int, int, LPCTSTR, int);
extern PROC pfnOrigTextOutA;


/*
005D9638  8C 95 90 E6 82 A9 82 E7 89 CE 89 8A 82 AA 8F 6F  ���悩��Ή����o
005D9648  82 E9 82 C6 0A 82 A2 82 ED 82 EA 82 E9 82 ED 82  ���.�������E
005D9658  B5 82 CC 8C 95 82 F0 0A 8E F3 82 AF 82 C4 8C A9  ��̌���.�󂯂Č�
005D9668  82 E6 81 49 81 49 00 9F 82 C2 82 C1 82 C1 81 49  ��I�I.������I
005D9678  81 49 81 49 00 EA 82 E9 82 ED 81 49 00 82 B5 82  �I�I.����I.���E
005D9688  C4 82 AD 82 BE 82 B3 82 A2 00                    Ă�������.....
*/


extern std::string bufferTextOut;


char pszBufferYasenWeaponMessage1[256] = "����D���鎞�����ӂ��Ȃ���҂��Ȃ����n�@�[�b�I�@�@�@�@�@�@�@�@�@�@�@�@";
char pszBufferYasenWeaponMessage2[256] = "���̎��Ɏ��������Ȃǐg�̒���m��Ȃ����n�@�[�b�I�@�@�@�@�@�@�@�@�@�@�@�@";
char pszBufferYasenWeaponMessage3[256] = "������������������������ǂ��[�I���������������@�@�@�@�@�@�@�@�@�@�@�@";
char pszBufferYasenWeaponMessage[256] = "";
// char pszBufferYasenWeaponMessage[256] = "�o���f�B�b�V���̈ꌂ�A�󂯂Ƃ߂Ă݂�I�n�@�[�b�I�@�@�@�@�@�@�@�@�@�@�@�@";


//                                                     
char pszBufferYasenAttackMessage1[256] = "�����Ȑl�ԕ���@�o���f�B�b�V���̎K�ɂȂ肽���̂�����H������͎��ɂȂ����I�@�@�@�@�@�@�@";
char pszBufferYasenAttackMessage2[256] = "�l�Ԃ͐Ǝ�Ȑ������A�����������̂悤�ɓ��ݒׂ����班���̓L���C�ɂȂ邩����@�@�@�@�@�@�@�@";
char pszBufferYasenAttackMessage[256] = "";

char pszBufferYasenDefendMessage[256] = "����ȂɎ��ɂ����̂�����H�@���ŉ����ȑ��~�����@�@�@�@�킽�����Ɍ����Ă����Ȃ����@�@�@�@�@�@";


BOOL isNextSerifuStartOverride = false;  // ����TextOutA���Ă΂ꂽ�^�C�~���O�� isOverrideTextOut��TRUE�ɂ��邽�߂̃t���O
BOOL isOverrideSerifuTextOut = false;    // ���̃t���O��ON���ƁATextOut�͕`����X���[����悤�ɂ���B

BOOL isAlbedoSerifu = false; // �A���x�h�̃Z���t��\�����Ȃ���΂Ȃ�Ȃ����Ƃ����o���邽�߂̐�p�t���O

BOOL isAlbedoYasenWeaponMessage = FALSE;
BOOL isAlbedoYasenAttackMessage = FALSE;
BOOL isAlbedoYasenDefendMessage = FALSE;

string prevSerihuMessage = "";


BOOL patchOfBushouMessage(HDC hdc, int nXStart, int nYStart, LPCTSTR lpString, int cbString) {

	// �A���x�h����풆�ɉ�S�̈ꌂ���o�����ꍇ�A�A���x�h���[�h�ɂ���B
	if (bufferTextOut.ends_with(getArubedoMei() + "��")) {

		string message = (char*)(�Z���t���b�Z�[�W�A�h���X); // on_serihu_message
		if (message.find("���悩��Ή����o") != string::npos) {
			if (!isAlbedoYasenWeaponMessage) {
				// ���ɂ����ɗ�����I�[�o�[���C�h����Ƃ����t���O
				isOverrideTextOut = TRUE;
				isAlbedoYasenWeaponMessage = TRUE;

				// �����̊m���ŁA�A���x�h�̃Z���t��ύX����
				int rnd = rand();
				if (rnd % 3 == 0) {
					strcpy_s(pszBufferYasenWeaponMessage, pszBufferYasenWeaponMessage1);
				}
				else if (rnd % 3 == 1) {
					strcpy_s(pszBufferYasenWeaponMessage, pszBufferYasenWeaponMessage2);
				}
				else {
					strcpy_s(pszBufferYasenWeaponMessage, pszBufferYasenWeaponMessage3);
				}
			}
		}
	}


	// �A���x�h���������������ꍇ�̃Z���t�ŁA�A���x�h���[�h�ɂ���B
	if (bufferTextOut.ends_with(getArubedoMei() + "�r")) {

		string message = (char*)(�Z���t���b�Z�[�W�A�h���X); // on_serihu_message
		if (message.find("�r�ɂ͂����������M������܂�") != string::npos) {

			if (!isAlbedoYasenAttackMessage) {
				// ���ɂ����ɗ�����I�[�o�[���C�h����Ƃ����t���O
				isOverrideTextOut = TRUE;
				isAlbedoYasenAttackMessage = TRUE;

				// �����̊m���ŁA�A���x�h�̃Z���t��ύX����
				if (rand() % 2 == 0) {
					strcpy_s(pszBufferYasenAttackMessage, pszBufferYasenAttackMessage1);
				}
				else {
					strcpy_s(pszBufferYasenAttackMessage, pszBufferYasenAttackMessage2);
				}

			}
		}
	}

	// �A���x�h����풆�ɉ�S�̈ꌂ���o�����ꍇ�A�A���x�h���[�h�ɂ���B
	if (bufferTextOut.ends_with(getArubedoMei() + "��")) {

		string message = (char*)(�Z���t���b�Z�[�W�A�h���X); // on_serihu_message
		if (message.find("�������Ȃ��Ǝv�킸��") != string::npos) {

			if (!isAlbedoYasenDefendMessage) {
				// ���ɂ����ɗ�����I�[�o�[���C�h����Ƃ����t���O
				isOverrideTextOut = TRUE;
				isAlbedoYasenDefendMessage = TRUE;
			}
		}
	}


	if (isOverrideTextOut && isAlbedoYasenAttackMessage) {
		// �����^�̕`���1�������Ȃ̂ŁA1�������ʂ̕�����`�悷��`�ƂȂ�B
		((PFNTEXTOUTA)pfnOrigTextOutA)(hdc, nXStart, nYStart, (char*)(pszBufferYasenAttackMessage + nTextOutProceedCounter), 2);
		nTextOutProceedCounter += 2;
	}

	// �A���x�h���[�h�Ȃ�A��`�̕`��������A���x�h�̂��̂ŏ㏑��
	else if (isOverrideTextOut && isAlbedoYasenWeaponMessage) {
		// �����^�̕`���1�������Ȃ̂ŁA1�������ʂ̕�����`�悷��`�ƂȂ�B
		((PFNTEXTOUTA)pfnOrigTextOutA)(hdc, nXStart, nYStart, (char*)(pszBufferYasenWeaponMessage + nTextOutProceedCounter), 2);
		nTextOutProceedCounter += 2;
	}

	else if (isOverrideTextOut && isAlbedoYasenDefendMessage) {
		// �����^�̕`���1�������Ȃ̂ŁA1�������ʂ̕�����`�悷��`�ƂȂ�B
		((PFNTEXTOUTA)pfnOrigTextOutA)(hdc, nXStart, nYStart, (char*)(pszBufferYasenDefendMessage + nTextOutProceedCounter), 2);
		nTextOutProceedCounter += 2;
	}

	else {

		// �Q��܂����A�Ƃ����Ă���Ȃ�΁A�u���v���u��v�ɕύX����
		if (bufferTextOut.ends_with(getArubedoMei() + "�Q��܂���")) {
			// ���ɂ����ɗ�����I�[�o�[���C�h����Ƃ����t���O
			isOverrideTextOut = TRUE;
			// �����^�̕`���1�������Ȃ̂ŁA1�������ʂ̕�����`�悷��`�ƂȂ�B
			((PFNTEXTOUTA)pfnOrigTextOutA)(hdc, nXStart, nYStart, "��", 2);
		}

	}

	return TRUE;
}

// �Z���t�n��ڍא����n�̃��b�Z�[�W���ύX�ɂȂ������ɌĂ΂��
BOOL onChangeSerifuMessage(std::string message) {
	OutputDebugStream("���b�Z�[�W���ύX�ɂȂ�܂���:");
	OutputDebugStream(message);
	OutputDebugStream("\r\n");
	return TRUE;
}