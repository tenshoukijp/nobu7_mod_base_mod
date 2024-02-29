#include <windows.h>
#include <string>


#include "data_game_struct.h"

using namespace std;

BOOL isValidBushouID(int iBushouID) {
	if ( 0 <= iBushouID && iBushouID < 最大数::武将情報::総配列数) {
		return TRUE;
	}
	return FALSE;
}

int getBushouIDFromBushouPtr(int* iBushouPtr) {
	int nBushouAddress = (int)iBushouPtr;

	// 武将の配列の先頭アドレスから引く
	int sub = nBushouAddress - (int)(武将情報アドレス);

	// 武将情報の構造体のサイズで割れば、何番目の武将なのかがわかる。
	int iBushouID = sub / sizeof(NB7武将情報型);
	if (isValidBushouID(iBushouID)) {
		return iBushouID;
	}

	return 0xFFFF;
}

int getCastleIdFromBushouID(int iBushouID) {
	if (isValidBushouID(iBushouID)) {
		// 所有武将のアドレスを直接さしている
		int nCastleAddress = (int)(nb7武将情報[iBushouID].p居城);
		// 武将の配列の先頭アドレスから引く
		int sub = nCastleAddress - (int)(城情報アドレス);

		// 武将情報の構造体のサイズで割れば、何番目の武将なのかがわかる。
		int iCastleID = sub / sizeof(NB7城情報型);
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


std::string getBushou苗字FromBushouID(int iBushouID) {
	if (0 <= iBushouID && iBushouID < 最大数::武将情報::総配列数) {
		return nb7武将情報[iBushouID].苗字;
	}

	return "";
}

std::string getBushou名前FromBushouID(int iBushouID) {
	if (0 <= iBushouID && iBushouID < 最大数::武将情報::総配列数) {
		return nb7武将情報[iBushouID].名前;
	}

	return "";
}

std::string getBushou姓名FromBushouID(int iBushouID) {
	if (0 <= iBushouID && iBushouID < 最大数::武将情報::総配列数) {
		return nb7武将情報[iBushouID].姓名;
	}

	return "";

}