
#include "data_game_struct.h"
#include "game_screen.h"

using namespace ��;

int getRetsudenBushouID() {
	int status = get�Q�[����ʃX�e�[�^�X();
	if (status == �Q�[����ʃX�e�[�^�X::�헪��� || status == �Q�[����ʃX�e�[�^�X::����� || status == �Q�[����ʃX�e�[�^�X::�ď����) {
		// ���L�����̃A�h���X�𒼐ڂ����Ă���
		int nBushouAddress = *(int*)(������`�������A�h���X);

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