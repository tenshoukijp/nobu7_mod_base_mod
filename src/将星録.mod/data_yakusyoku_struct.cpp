#include <windows.h>
#include "data_game_struct.h"

#include "output_debug_stream.h"

int getBushouIDFromYakusyokuID(int iYakusyokuID) {
	if (0 <= iYakusyokuID && iYakusyokuID < �ő吔::��E���::�z��) {
		// ���L�����̃A�h���X�𒼐ڂ����Ă���
		int* pBushouAddress = nb7��E���[iYakusyokuID].p���L��;
		int nBushouAddress = 0;
		if (pBushouAddress) {
			nBushouAddress = *pBushouAddress;
		}
		OutputDebugStream("��%x\n", nBushouAddress);

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

