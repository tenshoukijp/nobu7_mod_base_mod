#include <windows.h>

#include "data_game_struct.h"

int getBushouIDFromKanniID(int iKanniID) {
	if (0 <= iKanniID && iKanniID < �ő吔::���ʏ��::�z��) {
		// ���L�����̃A�h���X�𒼐ڂ����Ă���
		int nBushouAddress = (int)(nb7���ʏ��[iKanniID].p���L��);

		// �����̔z��̐擪�A�h���X�������
		int sub = nBushouAddress - (int)(�������A�h���X);

		// �������̍\���̂̃T�C�Y�Ŋ���΁A���Ԗڂ̕����Ȃ̂����킩��B
		int iBushouID = sub / sizeof(NB7�������^);
		if (0 <= iBushouID && iBushouID < �ő吔::�������::�z��) {
			return iBushouID;
		}
	}

	return 0xFFFF;

}

