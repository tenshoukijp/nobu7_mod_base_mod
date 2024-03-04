#include <windows.h>
#include <string>

#include <map>

#include "data_game_struct.h"

using namespace std;

std::map<string, string> 漢字To外字;
std::map<string, string> 外字To漢字;

void AddBushouGaijiConvertMap() {
	if (漢字To外字.size() == 0 || 外字To漢字.size() == 0) {
		漢字To外字["長宗我部"] = "\xEB\x9F\xEB\xA0\xEB\xA1";
		漢字To外字["香宗我部"] = "\xEB\xA2\xEB\xA0\xEB\xA1";
		漢字To外字["五右衛門"] = "\xEB\xA3\xEB\xA4\xEB\xA5";
		漢字To外字["又右衛門"] = "\xEB\xA6\xEB\xA4\xEB\xA5";

		外字To漢字["\xEB\x9F\xEB\xA0\xEB\xA1"] = "長宗我部";
		外字To漢字["\xEB\xA2\xEB\xA0\xEB\xA1"] = "香宗我部";
		外字To漢字["\xEB\xA3\xEB\xA4\xEB\xA5"] = "五右衛門";
		外字To漢字["\xEB\xA6\xEB\xA4\xEB\xA5"] = "又右衛門";
	}
}

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

int* getBushouPtrFromBushouID(int iBushouID) {
	int iBushouAddress = (int)(武将情報アドレス)+iBushouID * sizeof(NB7武将情報型);
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


std::string getBushou苗字FromBushouID(int iBushouID) {
	if (isValidBushouID(iBushouID)) {
		return nb7武将情報[iBushouID].苗字;
	}

	return "";
}

extern BOOL setBushou姓名(int iBushouID, std::string str姓名);

BOOL setBushou苗字(int iBushouID, std::string str苗字) {
	if (isValidBushouID(iBushouID)) {
		char bufLarge[256] = "";
		int length = sizeof(bufLarge);
		strcpy_s(bufLarge, length, str苗字.c_str());
		bufLarge[6] = '\0'; // 6文字目は必ず\0にする
		strcpy_s(nb7武将情報[iBushouID].苗字, sizeof(nb7武将情報[iBushouID].苗字), str苗字.c_str());

		// 「姓名」のところも更新する
		setBushou姓名(iBushouID, string(nb7武将情報[iBushouID].苗字) + string(nb7武将情報[iBushouID].名前));
		return TRUE;
	}
	return FALSE;
}


std::string getBushou名前FromBushouID(int iBushouID) {
	if (isValidBushouID(iBushouID)) {
		return nb7武将情報[iBushouID].名前;
	}

	return "";
}

BOOL setBushou名前(int iBushouID, std::string str名前) {
	if (isValidBushouID(iBushouID)) {
		char bufLarge[256] = "";
		int length = sizeof(bufLarge);
		strcpy_s(bufLarge, length, str名前.c_str());
		bufLarge[6] = '\0'; // 6文字目は必ず\0にする
		strcpy_s(nb7武将情報[iBushouID].名前, sizeof(nb7武将情報[iBushouID].名前), str名前.c_str());

		// 「姓名」のところも更新する
		setBushou姓名(iBushouID, string(nb7武将情報[iBushouID].苗字) + string(nb7武将情報[iBushouID].名前));
		return TRUE;
	}
	return FALSE;
}


std::string getBushou姓名FromBushouID(int iBushouID) {
	if (isValidBushouID(iBushouID)) {
		return nb7武将情報[iBushouID].姓名;
	}

	return "";

}

BOOL setBushou姓名(int iBushouID, std::string str姓名) {
	if (isValidBushouID(iBushouID)) {
		char bufLarge[256] = "";
		int length = sizeof(bufLarge);
		strcpy_s(bufLarge, length, str姓名.c_str());
		bufLarge[6] = '\0'; // 6文字目は必ず\0にする
		strcpy_s(nb7武将情報[iBushouID].姓名, sizeof(nb7武将情報[iBushouID].姓名), str姓名.c_str());
		return TRUE;
	}
	return FALSE;
}

// 武将の居城を設定する
BOOL setBushouCastle(int iBushouID, int iCastleID) {
	if (isValidBushouID(iBushouID)) {
		if (isValidCastleID(iCastleID)) {
			nb7武将情報[iBushouID].p居城 = getCastlePtrFromCastleID(iCastleID);
			return TRUE;
		}
		else if (iCastleID == 0xFFFF) {
			nb7武将情報[iBushouID].p居城 = (int*)武将居城なし;
			return TRUE;
		}
	}

	return FALSE;
}
