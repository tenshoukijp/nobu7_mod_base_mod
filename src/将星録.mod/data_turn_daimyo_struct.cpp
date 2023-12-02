#include "data_game_struct.h"

int getStrategyTurnDaimyoID() {
	int nDaimyoAddress = *(int*)(�^�[���喼���A�h���X);

	// �����̔z��̐擪�A�h���X�������
	int sub = nDaimyoAddress - (int)(�喼���A�h���X);

	// �喼���̍\���̂̃T�C�Y�Ŋ���΁A���Ԗڂ̕����Ȃ̂����킩��B
	int iDaimyoID = sub / sizeof(NB7�喼���^);
	if (isValidDaimyoID(iDaimyoID)) {
		return iDaimyoID;

	}
	return 0xFFFF;
}


int getStrategyTurnDaimyoBushouID() {
	int iDaimyoID = getStrategyTurnDaimyoID();
	if (isValidDaimyoID(iDaimyoID)) {
		int iBushouID = getBushouIDFromDaimyoID(iDaimyoID);
		if (isValidBushouID(iBushouID)) {
			return iBushouID;
		}
	}

	return 0xFFFF;
}
