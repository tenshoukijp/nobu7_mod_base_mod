#include <windows.h>
#include <vector>

#include "data_game_struct.h"
#include "output_debug_stream.h"

BOOL isValidUnitID(int iUnitID) {
	if (0 <= iUnitID && iUnitID < �ő吔::���j�b�g���::�z��) {
		return TRUE;
	}
	return FALSE;
}

// ���j�b�gID���炻��𗦂��Ă��镐��ID���擾����
int getBushouIDFromUnitID(int iUnitID) {
	if (isValidUnitID(iUnitID)) {
		// ���L�����̃A�h���X�𒼐ڂ����Ă���
		int nBushouAddress = (int)(nb7���j�b�g���[iUnitID].p�w������);

		// �����̔z��̐擪�A�h���X�������
		int sub = nBushouAddress - (int)(�������A�h���X);

		// �������̍\���̂̃T�C�Y�Ŋ���΁A���Ԗڂ̕����Ȃ̂����킩��B
		int iBushouID = sub / sizeof(NB7�������^);
		if (isValidUnitID(iBushouID)) { // �����͍ő吔::�������::�z��(=732)�ł͂Ȃ��A�_�������܂߂邽�߁A�ő吔::���j�b�g���::�z�� (=744)�ƂȂ�B
			return iBushouID;
		}
	}

	return 0xFFFF;
}

int getUnitIDFromUnitPtr(int* iUnitPtr) {
	int nUnitAddress = (int)(iUnitPtr);

	// �����̔z��̐擪�A�h���X�������
	int sub = nUnitAddress - (int)(���j�b�g���A�h���X);

	// �������̍\���̂̃T�C�Y�Ŋ���΁A���Ԗڂ̕����Ȃ̂����킩��B
	int iUnitID = sub / sizeof(NB7���j�b�g���^);
	if (isValidUnitID(iUnitID)) {
		return iUnitID;
	}

	return 0xFFFF;
}



int get�R�����j�b�g�����ő啺��(int iUnitID) {
	if (isValidUnitID(iUnitID)) {
		int iBushouID = getBushouIDFromUnitID(iUnitID);
		if (0 <= iBushouID && iBushouID < �ő吔::���j�b�g���::�z��) {
			int status = nb7�������[iBushouID].���;
			// �喼�A�Ɨ����́A����Ꝅ���́A�Ꝅ���͂Ȃ�A�P������1000
			if (status == 0 || status == 2 || status == 6 || status == 7) {
				return 1000;
			}
			// �����̎��͐g���Ŕ���
			else if (status == 1) {
				int mibun = nb7�������[iBushouID].�g��;
				if (mibun == �������::�g��::�喼) {
					return 1000;
				}
				else if (mibun == �������::�g��::�h�V) {
					return 900;
				}
				else if (mibun == �������::�g��::�ƘV) {
					return 750;
				}
				else if (mibun == �������::�g��::����) {
					return 600;
				}
				else if (mibun == �������::�g��::���叫) {
					return 500;
				}
				else if (mibun == �������::�g��::���y��) {
					return 400;
				}
			}
		}
	}
	return 0;
}
