#include <windows.h>
#include <string>


#include "data_game_struct.h"

using namespace std;

BOOL isValidBushouID(int iBushouID) {
	if ( 0 <= iBushouID && iBushouID < �ő吔::�������::�z��) {
		return TRUE;
	}
	return FALSE;
}

int getCastleIdFromBushouID(int iBushouID) {
	if (isValidBushouID(iBushouID)) {
		// ���L�����̃A�h���X�𒼐ڂ����Ă���
		int nCastleAddress = (int)(nb7�������[iBushouID].p����);
		// �����̔z��̐擪�A�h���X�������
		int sub = nCastleAddress - (int)(����A�h���X);

		// �������̍\���̂̃T�C�Y�Ŋ���΁A���Ԗڂ̕����Ȃ̂����킩��B
		int iCastleID = sub / sizeof(NB7����^);
		if (isValidCastleID(iCastleID)) {
			return iCastleID;
		}
	}
	return 0xFFFF;
}
	



std::string getBushou�c��FromBushouID(int iBushouID) {
	if (0 <= iBushouID && iBushouID < �ő吔::���j�b�g���::�z��) {
		return nb7�������[iBushouID].�c��;
	}

	return "";
}

std::string getBushou���OFromBushouID(int iBushouID) {
	if (0 <= iBushouID && iBushouID < �ő吔::���j�b�g���::�z��) {
		return nb7�������[iBushouID].���O;
	}

	return "";
}

std::string getBushou����FromBushouID(int iBushouID) {
	if (0 <= iBushouID && iBushouID < �ő吔::���j�b�g���::�z��) {
		return nb7�������[iBushouID].����;
	}

	return "";

}