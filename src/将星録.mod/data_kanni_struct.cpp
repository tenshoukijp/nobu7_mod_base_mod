#include <windows.h>

#include "data_game_struct.h"

BOOL isValidKanniID(int iKanniID) {
	if (0 <= iKanniID && iKanniID < �ő吔::���ʏ��::�z��) {
		return TRUE;
	}
	return FALSE;
}

int getBushouIDFromKanniID(int iKanniID) {
	if (isValidKanniID(iKanniID)) {
		// ���L�����̃A�h���X�𒼐ڂ����Ă���
		int nBushouAddress = (int)(nb7���ʏ��[iKanniID].p���L��);

		// �����̔z��̐擪�A�h���X�������
		int sub = nBushouAddress - (int)(�������A�h���X);

		// �������̍\���̂̃T�C�Y�Ŋ���΁A���Ԗڂ̕����Ȃ̂����킩��B
		int iBushouID = sub / sizeof(NB7�������^);
		if (isValidBushouID(iBushouID)) {
			return iBushouID;
		}
	}

	return 0xFFFF;

}

BOOL setBushouIDToKanniID(int iKanniID, int iBushouID) {
	if (isValidKanniID(iKanniID)) {
		if (isValidBushouID(iBushouID)) {
			// �������̃A�h���X���擾
			int iBushouAddress = (int)(�������A�h���X)+iBushouID * sizeof(NB7�������^);

			// ���ʏ��̏��L�҂ɕ������̃A�h���X��ݒ�
			nb7���ʏ��[iKanniID].p���L�� = (int*)iBushouAddress;
			return TRUE;
		}
		else if (iBushouID == 0xFFFF) {
			// ���L�҂Ȃ�
			nb7���ʏ��[iKanniID].p���L�� = (int*)���ʏ��L�҂Ȃ�;
			return TRUE;

		}
	}
	return FALSE;

}


BOOL setKanniName(int iKanniID, std::string strKanniName) {
	if (isValidKanniID(iKanniID)) {
		char bufLarge[256] = "";
		int length = sizeof(bufLarge);
		strcpy_s(bufLarge, length, strKanniName.c_str());
		bufLarge[13] = '\0'; // 13�����ڂ͕K��\0�ɂ���
		// ���ʖ���ݒ�
		strcpy_s(nb7���ʏ��[iKanniID].���ʖ�, sizeof(nb7���ʏ��[iKanniID].���ʖ�), bufLarge);
		return TRUE;
	}
	return FALSE;
}

