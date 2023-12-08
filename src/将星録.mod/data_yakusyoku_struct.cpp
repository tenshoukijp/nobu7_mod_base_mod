#include <windows.h>
#include "data_game_struct.h"

#include "output_debug_stream.h"

BOOL isValidYakusyokuID(int iYakusyokuID) {
	if (0 <= iYakusyokuID && iYakusyokuID < �ő吔::��E���::�z��) {
		return TRUE;
	}
	return FALSE;
}


int getDaimyoIDFromYakusyokuID(int iYakusyokuID) {
	if (0 <= iYakusyokuID && iYakusyokuID < �ő吔::��E���::�z��) {
		// ���L�����̃A�h���X�𒼐ڂ����Ă���
		int nDaimyoAddress = (int)nb7��E���[iYakusyokuID].p���L�喼;

		// �����̔z��̐擪�A�h���X�������
		int sub = nDaimyoAddress - (int)(�喼���A�h���X);

		// �������̍\���̂̃T�C�Y�Ŋ���΁A���Ԗڂ̕����Ȃ̂����킩��B
		int iDaimyoID = sub / sizeof(NB7�喼���^);
		if (isValidDaimyoID(iDaimyoID)) {
			return iDaimyoID;
		}
	}

	return 0xFFFF;

}

BOOL setDaimyoIDToYakusyokuID(int iYakusyokuID, int iDaimyoID) {
	if (isValidYakusyokuID(iYakusyokuID)) {
		if (isValidDaimyoID(iDaimyoID)) {
			// �喼���̃A�h���X���擾
			int iDaimyoAddress = (int)(�喼���A�h���X)+iDaimyoID * sizeof(NB7�喼���^);
			// ��E���̏��L�҂ɕ������̃A�h���X��ݒ�
			nb7��E���[iYakusyokuID].p���L�喼 = (int*)iDaimyoAddress;
			return TRUE;
		}
		else if (iDaimyoID == 0xFFFF) {
			// ���L�҂Ȃ�
			nb7��E���[iYakusyokuID].p���L�喼 = (int*)��E���L�҂Ȃ�;
			return TRUE;

		}
	}
	return FALSE;

}

BOOL setYakusyokuName(int iYakusyokuID, std::string strYakusyokuName) {
	if (isValidYakusyokuID(iYakusyokuID)) {
		char bufLarge[256] = "";
		int length = sizeof(bufLarge);
		strcpy_s(bufLarge, length, strYakusyokuName.c_str());
		bufLarge[length - 1] = '\0'; // 11�����ڂ͕K��\0�ɂ���
		// ��E����ݒ�
		strcpy_s(nb7��E���[iYakusyokuID].��E��, sizeof(nb7��E���[iYakusyokuID].��E��), bufLarge);
		return TRUE;
	}
	return FALSE;
}

