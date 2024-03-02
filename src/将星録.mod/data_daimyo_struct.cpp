#include "data_game_struct.h"

BOOL isValidDaimyoID(int iDaimyoID) {
	if (0 <= iDaimyoID && iDaimyoID < �ő吔::�喼���::�z��) {
		return TRUE;
	}
	return FALSE;
}

int getDaimyoIDFromDaimyoPtr(int* iDaimyoPtr) {
	int nDaimyoAddress = (int)iDaimyoPtr;

	// �喼�̔z��̐擪�A�h���X�������
	int sub = nDaimyoAddress - (int)(�喼���A�h���X);

	// �喼���̍\���̂̃T�C�Y�Ŋ���΁A���Ԗڂ̑喼�Ȃ̂����킩��B
	int iDaimyoID = sub / sizeof(NB7�喼���^);
	if (isValidDaimyoID(iDaimyoID)) {
		return iDaimyoID;
	}

	return 0xFFFF;

}

int* getDaimyoPtrFromDaimyoID(int iDaimyoID) {
	int iDaimyoAddress = (int)(�喼���A�h���X)+iDaimyoID * sizeof(NB7�喼���^);
	return (int*)iDaimyoAddress;
}



// �喼ID���炻�̑喼�̕���ID���擾����
int getBushouIDFromDaimyoID(int iDaimyoID) {
	if (isValidDaimyoID(iDaimyoID)) {
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

BOOL setDaimyoBushouID(int iDaimyoID, int iBushouID) {
	if (isValidDaimyoID(iDaimyoID)) {

		if (isValidBushouID(iBushouID)) {
			// �������̃A�h���X���擾
			int iBushouAddress = (int)(�������A�h���X)+iBushouID * sizeof(NB7�������^);
			nb7�喼���[iDaimyoID].p�喼���� = (int*)iBushouAddress;
			return TRUE;
		}
		else {
			nb7�喼���[iDaimyoID].p�喼���� = (int*)�喼�����Ȃ�;
			return TRUE;
		}

	}

	return FALSE;
}


// �喼�̋����ݒ肷��
BOOL setDaimyoCastle(int iDaimyoID, int iCastleID) {
	if (isValidDaimyoID(iDaimyoID)) {
		if (isValidCastleID(iCastleID)) {
			nb7�喼���[iCastleID].p���� = getCastlePtrFromCastleID(iCastleID);
			return TRUE;
		}
		else if (iCastleID == 0xFFFF) {
			nb7�喼���[iCastleID].p���� = (int*)�喼����Ȃ�;
			return TRUE;
		}
	}

	return FALSE;
}





static const int �F�D�lArray[] = { 0, 10, 20, 30, 40, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 0xFFFF };
int get�F�D�lFrom�F�DID(int i�F�DID) {
	if ( 0 <= i�F�DID && i�F�DID < _countof(�F�D�lArray)) {
		return �F�D�lArray[i�F�DID];
	}
	return 0xFFFF;
}

int get�F�DIDFrom�F�D�l(int i�F�D�l) {
	if (i�F�D�l < 0) {
		return �F�D�lArray[0];
	}
	else if (i�F�D�l == 0xFFFF) {
		return _countof(�F�D�lArray) - 1; // �Ō��ID�l
	}
	else if (i�F�D�l > 100) {
		i�F�D�l = 100;
		for (int iID = 0; iID < _countof(�F�D�lArray); iID++) {
			if (�F�D�lArray[iID] == 100) {
				return iID;
			}
		}
	}
	else {
		for (int iID = 0; iID < _countof(�F�D�lArray); iID++) {
			if (�F�D�lArray[iID] > i�F�D�l) {
				return iID-1;
			}
		}
	}

	return _countof(�F�D�lArray) - 1; // �Ō��ID�l�B�����ɂ͗��_��A���ۂɂ͓͂��Ȃ��n�Y
}

int get�喼�F�DID(int iDaimyoID1, int iDaimyoID2) {
	if (!isValidDaimyoID(iDaimyoID1)) {
		return 0xFFFF;
	}
	if (!isValidDaimyoID(iDaimyoID2)) {
		return 0xFFFF;
	}

	return nb7�喼���[iDaimyoID1].�F�DID[iDaimyoID2];
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

int get�喼�����c(int iDaimyoID1, int iDaimyoID2) {
	if (!isValidDaimyoID(iDaimyoID1)) {
		return 0xFFFF;
	}
	if (!isValidDaimyoID(iDaimyoID2)) {
		return 0xFFFF;
	}

	return nb7�喼���[iDaimyoID1].�����c[iDaimyoID2];
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

BOOL get�喼����(int iDaimyouID1, int iDaimyouID2) {
	if (!isValidDaimyoID(iDaimyouID1)) {
		return FALSE;
	}
	if (!isValidDaimyoID(iDaimyouID2)) {
		return FALSE;
	}

	return nb7�喼���[iDaimyouID1].����[iDaimyouID2];
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

// ��x���l���Z�b�e�B���O����Ă��Ȃ��喼�ƂȂ��-1���ݒ肳��Ă��邪�A0xFF�ł����͂Ȃ��B
BOOL set�喼�Ɩ�ԍ�(int iDaimyoID, int iKamonID) {
	if (0 <= iKamonID && iKamonID <= �ő吔::�喼���::�Ɩ䐔-1) {
		nb7�喼���[iDaimyoID].�Ɩ�ԍ� = iKamonID;
		return TRUE;
	}
	else if (iKamonID == 255) {
		nb7�喼���[iDaimyoID].�Ɩ�ԍ� = 255;
		return TRUE;
	}
	else if (iKamonID == -1) {
		nb7�喼���[iDaimyoID].�Ɩ�ԍ� = 255;
		return TRUE;
	}
	return FALSE;
}
