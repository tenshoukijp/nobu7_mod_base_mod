#include <windows.h>

#include "data_game_struct.h"

BOOL isValidKanniID(int iKanniID) {
	if (0 <= iKanniID && iKanniID < 最大数::官位情報::配列数) {
		return TRUE;
	}
	return FALSE;
}

int getBushouIDFromKanniID(int iKanniID) {
	if (isValidKanniID(iKanniID)) {
		// 所有武将のアドレスを直接さしている
		int nBushouAddress = (int)(nb7官位情報[iKanniID].p所有者);

		// 武将の配列の先頭アドレスから引く
		int sub = nBushouAddress - (int)(武将情報アドレス);

		// 武将情報の構造体のサイズで割れば、何番目の武将なのかがわかる。
		int iBushouID = sub / sizeof(NB7武将情報型);
		if (isValidBushouID(iBushouID)) {
			return iBushouID;
		}
	}

	return 0xFFFF;

}

BOOL setBushouIDToKanniID(int iKanniID, int iBushouID) {
	if (isValidKanniID(iKanniID)) {
		if (isValidBushouID(iBushouID)) {
			// 武将情報のアドレスを取得
			int iBushouAddress = (int)(武将情報アドレス)+iBushouID * sizeof(NB7武将情報型);

			// 官位情報の所有者に武将情報のアドレスを設定
			nb7官位情報[iKanniID].p所有者 = (int*)iBushouAddress;
			return TRUE;
		}
		else if (iBushouID == 0xFFFF) {
			// 所有者なし
			nb7官位情報[iKanniID].p所有者 = (int*)官位所有者なし;
			return TRUE;

		}
	}
	return FALSE;

}


BOOL setKanniName(int iKanniID, std::string strKanniName) {
	if (isValidKanniID(iKanniID)) {
		char bufLarge[256] = "";
		int length = sizeof(bufLarge);
		strcpy_s(bufLarge, length, strKanniName.c_str());
		bufLarge[13] = '\0'; // 13文字目は必ず\0にする
		// 官位名を設定
		strcpy_s(nb7官位情報[iKanniID].官位名, sizeof(nb7官位情報[iKanniID].官位名), bufLarge);
		return TRUE;
	}
	return FALSE;
}

