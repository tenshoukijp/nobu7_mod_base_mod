#include <windows.h>

#include "data_game_struct.h"
#include "output_debug_stream.h"


// ���j�b�gID���炻��𗦂��Ă��镐��ID���擾����
int getBushouIDFromUnitID(int iUnitID) {
	if (0 <= iUnitID && iUnitID < �ő吔::���j�b�g���::�z��) {
		// ���L�����̃A�h���X�𒼐ڂ����Ă���
		int nBushouAddress = (int)(nb7���j�b�g���[iUnitID].p���j�b�g����);

		// �����̔z��̐擪�A�h���X�������
		int sub = nBushouAddress - (int)(�������A�h���X);

		// �������̍\���̂̃T�C�Y�Ŋ���΁A���Ԗڂ̕����Ȃ̂����킩��B
		int iBushouID = sub / sizeof(NB7�������^);
		if (0 <= iBushouID && iBushouID < �ő吔::���j�b�g���::�z��) { // �����͍ő吔::�������::�z��(=732)�ł͂Ȃ��A�_�������܂߂邽�߁A�ő吔::���j�b�g���::�z�� (=744)�ƂȂ�B
			return iBushouID;
		}
	}

	return 0xFFFF;
}
