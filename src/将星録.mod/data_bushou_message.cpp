#include "data_bushou_message.h"
#include "data_game_struct.h"
#include <string>

int get���BushouIDFromMessageBushou() {
	// ���L�����̃A�h���X�𒼐ڂ����Ă���
	int nBushouAddress = (int)(���b�Z�[�W�������.p��̕���);

	// �����̔z��̐擪�A�h���X�������
	int sub = nBushouAddress - (int)(�������A�h���X);

	// �������̍\���̂̃T�C�Y�Ŋ���΁A���Ԗڂ̕����Ȃ̂����킩��B
	int iBushouID = sub / sizeof(NB7�������^);
	if (isValidBushouID(iBushouID)) {
		return iBushouID;
	}

	return 0xFFFF;
}

int get����BushouIDFromMessageBushou() {
	// ���L�����̃A�h���X�𒼐ڂ����Ă���
	int nBushouAddress = (int)(���b�Z�[�W�������.p���蕐��);

	// �����̔z��̐擪�A�h���X�������
	int sub = nBushouAddress - (int)(�������A�h���X);

	// �������̍\���̂̃T�C�Y�Ŋ���΁A���Ԗڂ̕����Ȃ̂����킩��B
	int iBushouID = sub / sizeof(NB7�������^);
	if (isValidBushouID(iBushouID)) {
		return iBushouID;
	}

	return 0xFFFF;
}