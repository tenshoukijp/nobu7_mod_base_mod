#include <windows.h>
#include <string>


#include "data_game_struct.h"

using namespace std;

BOOL isValidBushouID(int iBushouID) {
	if ( 0 <= iBushouID && iBushouID < �ő吔::�������::���z��) {
		return TRUE;
	}
	return FALSE;
}

int getBushouIDFromBushouPtr(int* iBushouPtr) {
	int nBushouAddress = (int)iBushouPtr;

	// �����̔z��̐擪�A�h���X�������
	int sub = nBushouAddress - (int)(�������A�h���X);

	// �������̍\���̂̃T�C�Y�Ŋ���΁A���Ԗڂ̕����Ȃ̂����킩��B
	int iBushouID = sub / sizeof(NB7�������^);
	if (isValidBushouID(iBushouID)) {
		return iBushouID;
	}

	return 0xFFFF;
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
	
int getDaimyoIDFromBushouID(int iBushouID) {
	if (isValidBushouID(iBushouID)) {
		int iCastleID = getCastleIdFromBushouID(iBushouID);
		if (isValidCastleID(iCastleID)) {
			int iDaimyoID = getDaimyoIDFromCastleID(iCastleID);
			if (isValidDaimyoID(iDaimyoID)) {
				return iDaimyoID;
			}
		}
	}

	return 0xFFFF;
}


std::string getBushou�c��FromBushouID(int iBushouID) {
	if (0 <= iBushouID && iBushouID < �ő吔::�������::���z��) {
		return nb7�������[iBushouID].�c��;
	}

	return "";
}

std::string getBushou���OFromBushouID(int iBushouID) {
	if (0 <= iBushouID && iBushouID < �ő吔::�������::���z��) {
		return nb7�������[iBushouID].���O;
	}

	return "";
}

std::string getBushou����FromBushouID(int iBushouID) {
	if (0 <= iBushouID && iBushouID < �ő吔::�������::���z��) {
		return nb7�������[iBushouID].����;
	}

	return "";

}