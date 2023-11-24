#include "data_game_struct.h"

// �喼ID���炻�̑喼�̕���ID���擾����
int getBushouIDFromDaimyoID(int iDaimyoID) {
	if (0 <= iDaimyoID && iDaimyoID < �ő吔::�喼���::�z��) {
		// ���L�����̃A�h���X�𒼐ڂ����Ă���
		int nBushouAddress = (int)(nb7�喼���[iDaimyoID].p�喼����);

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


static int �F�D�lArray[] = { 0, 10, 20, 30, 40, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 0xFFFF };
int get�F�D�lFrom�F�DID(int i�F�DID) {
	if ( 0 <= i�F�DID && i�F�DID < _countof(�F�D�lArray)) {
		return �F�D�lArray[i�F�DID];
	}
	return 0xFFFF;
}