#include "data_game_struct.h"

int getStrategyPlayerTurnCastleID() {
	// ���L�����̃A�h���X�𒼐ڂ����Ă���
	int nCastleAddress = (int)(�^�[������.p�^�[����);
	// �����̔z��̐擪�A�h���X�������
	int sub = nCastleAddress - (int)(����A�h���X);

	// �������̍\���̂̃T�C�Y�Ŋ���΁A���Ԗڂ̕����Ȃ̂����킩��B
	int iCastleID = sub / sizeof(NB7����^);
	if (isValidCastleID(iCastleID)) {
		return iCastleID;
	}
	return 0xFFFF;
}