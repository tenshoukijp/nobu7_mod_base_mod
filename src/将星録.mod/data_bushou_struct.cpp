#include <windows.h>
#include <string>

#include <map>

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

int* getBushouPtrFromBushouID(int iBushouID) {
	int iBushouAddress = (int)(�������A�h���X)+iBushouID * sizeof(NB7�������^);
	return (int*)iBushouAddress;
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
	if (isValidBushouID(iBushouID)) {
		return nb7�������[iBushouID].�c��;
	}

	return "";
}

extern BOOL setBushou����(int iBushouID, std::string str����);

BOOL setBushou�c��(int iBushouID, std::string str�c��) {
	if (isValidBushouID(iBushouID)) {
		char bufLarge[256] = "";
		int length = sizeof(bufLarge);
		strcpy_s(bufLarge, length, str�c��.c_str());
		bufLarge[6] = '\0'; // 6�����ڂ͕K��\0�ɂ���
		strcpy_s(nb7�������[iBushouID].�c��, sizeof(nb7�������[iBushouID].�c��), str�c��.c_str());

		// �u�����v�̂Ƃ�����X�V����
		setBushou����(iBushouID, string(nb7�������[iBushouID].�c��) + string(nb7�������[iBushouID].���O));
		return TRUE;
	}
	return FALSE;
}


std::string getBushou���OFromBushouID(int iBushouID) {
	if (isValidBushouID(iBushouID)) {
		return nb7�������[iBushouID].���O;
	}

	return "";
}

BOOL setBushou���O(int iBushouID, std::string str���O) {
	if (isValidBushouID(iBushouID)) {
		char bufLarge[256] = "";
		int length = sizeof(bufLarge);
		strcpy_s(bufLarge, length, str���O.c_str());
		bufLarge[6] = '\0'; // 6�����ڂ͕K��\0�ɂ���
		strcpy_s(nb7�������[iBushouID].���O, sizeof(nb7�������[iBushouID].���O), str���O.c_str());

		// �u�����v�̂Ƃ�����X�V����
		setBushou����(iBushouID, string(nb7�������[iBushouID].�c��) + string(nb7�������[iBushouID].���O));
		return TRUE;
	}
	return FALSE;
}


std::string getBushou����FromBushouID(int iBushouID) {
	if (isValidBushouID(iBushouID)) {
		return nb7�������[iBushouID].����;
	}

	return "";

}

BOOL setBushou����(int iBushouID, std::string str����) {
	if (isValidBushouID(iBushouID)) {
		char bufLarge[256] = "";
		int length = sizeof(bufLarge);
		strcpy_s(bufLarge, length, str����.c_str());
		bufLarge[6] = '\0'; // 6�����ڂ͕K��\0�ɂ���
		strcpy_s(nb7�������[iBushouID].����, sizeof(nb7�������[iBushouID].����), str����.c_str());
		return TRUE;
	}
	return FALSE;
}

// �����̋����ݒ肷��
BOOL setBushouCastle(int iBushouID, int iCastleID) {
	if (isValidBushouID(iBushouID)) {
		if (isValidCastleID(iCastleID)) {
			nb7�������[iCastleID].p���� = getCastlePtrFromCastleID(iCastleID);
			return TRUE;
		}
		else if (iCastleID == 0xFFFF) {
			nb7�������[iCastleID].p���� = (int*)��������Ȃ�;
			return TRUE;
		}
	}

	return FALSE;
}
