#include "data_game_struct.h"
#include "game_screen.h"

int getRetsudenKahouID() {
	�Q�[����ʃX�e�[�^�X status = get�Q�[����ʃX�e�[�^�X();
	if (status == �Q�[����ʃX�e�[�^�X::�헪��� || status == �Q�[����ʃX�e�[�^�X::����� || status == �Q�[����ʃX�e�[�^�X::�ď����) {
		// �ƕ�̃A�h���X�𒼐ڂ����Ă���
		int nKahouAddress = *(int*)(�ƕ��`�ƕ���A�h���X);

		// �ƕ�̔z��̐擪�A�h���X�������
		int sub = nKahouAddress - (int)(�ƕ���A�h���X);

		// �ƕ���̍\���̂̃T�C�Y�Ŋ���΁A���Ԗڂ̕����Ȃ̂����킩��B
		int iBushouID = sub / sizeof(NB7�ƕ���^);
		if (isValidBushouID(iBushouID)) {
			return iBushouID;
		}
	}

	return 0xFFFF;
}