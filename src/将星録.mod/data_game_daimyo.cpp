#include "data_game_struct.h"

// �ƕ�ID���炻������L���Ă��镐��ID���擾����
int getBushouIDFromDaimyoID(int iDaimyoID) {
	if (0 <= iDaimyoID && iDaimyoID < �ő吔::�喼���::�z��) {
		// ���L�����̃A�h���X�𒼐ڂ����Ă���
		int nBushouAddress = (int)(nb7�喼���[iDaimyoID].p�喼����);

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
