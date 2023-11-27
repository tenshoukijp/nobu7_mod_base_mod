#include "data_game_struct.h"

BOOL isValidDaimyoID(int iDaimyoID) {
	if (0 <= iDaimyoID && iDaimyoID < �ő吔::�喼���::�z��) {
		return TRUE;
	}
	return FALSE;
}

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

BOOL set�喼�F�DID(int iDaimyoID1, int iDaimyoID2, int i�F�DID) {
	if (!isValidDaimyoID(iDaimyoID1)) {
		return FALSE;
	}
	if (!isValidDaimyoID(iDaimyoID2)) {
		return FALSE;
	}

	nb7�喼���[iDaimyoID1].�F�DID[iDaimyoID2] = i�F�DID;
	nb7�喼���[iDaimyoID2].�F�DID[iDaimyoID1] = i�F�DID;
	return TRUE;
}

BOOL set�喼�����c(int iDaimyoID1, int iDaimyoID2, int �c��) {
	if (!isValidDaimyoID(iDaimyoID1)) {
		return FALSE;
	}
	if (!isValidDaimyoID(iDaimyoID2)) {
		return FALSE;
	}

	nb7�喼���[iDaimyoID1].�����c[iDaimyoID2] = �c��;
	nb7�喼���[iDaimyoID2].�����c[iDaimyoID1] = �c��;
	return TRUE;
}

BOOL set�喼����(int iDaimyouID1, int iDaimyouID2, BOOL ������) {
	if (!isValidDaimyoID(iDaimyouID1)) {
		return FALSE;
	}
	if (!isValidDaimyoID(iDaimyouID2)) {
		return FALSE;
	}

	nb7�喼���[iDaimyouID1].����[iDaimyouID2] = ������;
	nb7�喼���[iDaimyouID2].����[iDaimyouID1] = ������;
	return TRUE;
}