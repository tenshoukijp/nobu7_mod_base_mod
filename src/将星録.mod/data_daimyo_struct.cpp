#include "data_game_struct.h"

BOOL isValidDaimyoID(int iDaimyoID) {
	if (0 <= iDaimyoID && iDaimyoID < 最大数::大名情報::配列数) {
		return TRUE;
	}
	return FALSE;
}

int getDaimyoIDFromDaimyoPtr(int* iDaimyoPtr) {
	int nDaimyoAddress = (int)iDaimyoPtr;

	// 大名の配列の先頭アドレスから引く
	int sub = nDaimyoAddress - (int)(大名情報アドレス);

	// 大名情報の構造体のサイズで割れば、何番目の大名なのかがわかる。
	int iDaimyoID = sub / sizeof(NB7大名情報型);
	if (isValidDaimyoID(iDaimyoID)) {
		return iDaimyoID;
	}

	return 0xFFFF;

}

int* getDaimyoPtrFromDaimyoID(int iDaimyoID) {
	int iDaimyoAddress = (int)(大名情報アドレス)+iDaimyoID * sizeof(NB7大名情報型);
	return (int*)iDaimyoAddress;
}



// 大名IDからその大名の武将IDを取得する
int getBushouIDFromDaimyoID(int iDaimyoID) {
	if (isValidDaimyoID(iDaimyoID)) {
		// 所有武将のアドレスを直接さしている
		int nBushouAddress = (int)(nb7大名情報[iDaimyoID].p大名武将);

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

BOOL setDaimyoBushouID(int iDaimyoID, int iBushouID) {
	if (isValidDaimyoID(iDaimyoID)) {

		if (isValidBushouID(iBushouID)) {
			// 武将情報のアドレスを取得
			int iBushouAddress = (int)(武将情報アドレス)+iBushouID * sizeof(NB7武将情報型);
			nb7大名情報[iDaimyoID].p大名武将 = (int*)iBushouAddress;
			return TRUE;
		}
		else {
			nb7大名情報[iDaimyoID].p大名武将 = (int*)大名武将なし;
			return TRUE;
		}

	}

	return FALSE;
}


// 大名の居城を設定する
BOOL setDaimyoCastle(int iDaimyoID, int iCastleID) {
	if (isValidDaimyoID(iDaimyoID)) {
		if (isValidCastleID(iCastleID)) {
			nb7大名情報[iCastleID].p居城 = getCastlePtrFromCastleID(iCastleID);
			return TRUE;
		}
		else if (iCastleID == 0xFFFF) {
			nb7大名情報[iCastleID].p居城 = (int*)大名居城なし;
			return TRUE;
		}
	}

	return FALSE;
}





static const int 友好値Array[] = { 0, 10, 20, 30, 40, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 0xFFFF };
int get友好値From友好ID(int i友好ID) {
	if ( 0 <= i友好ID && i友好ID < _countof(友好値Array)) {
		return 友好値Array[i友好ID];
	}
	return 0xFFFF;
}

int get友好IDFrom友好値(int i友好値) {
	if (i友好値 < 0) {
		return 友好値Array[0];
	}
	else if (i友好値 == 0xFFFF) {
		return _countof(友好値Array) - 1; // 最後のID値
	}
	else if (i友好値 > 100) {
		i友好値 = 100;
		for (int iID = 0; iID < _countof(友好値Array); iID++) {
			if (友好値Array[iID] == 100) {
				return iID;
			}
		}
	}
	else {
		for (int iID = 0; iID < _countof(友好値Array); iID++) {
			if (友好値Array[iID] > i友好値) {
				return iID-1;
			}
		}
	}

	return _countof(友好値Array) - 1; // 最後のID値。ここには理論上、実際には届かないハズ
}

int get大名友好ID(int iDaimyoID1, int iDaimyoID2) {
	if (!isValidDaimyoID(iDaimyoID1)) {
		return 0xFFFF;
	}
	if (!isValidDaimyoID(iDaimyoID2)) {
		return 0xFFFF;
	}

	return nb7大名情報[iDaimyoID1].友好ID[iDaimyoID2];
}

BOOL set大名友好ID(int iDaimyoID1, int iDaimyoID2, int i友好ID) {
	if (!isValidDaimyoID(iDaimyoID1)) {
		return FALSE;
	}
	if (!isValidDaimyoID(iDaimyoID2)) {
		return FALSE;
	}

	nb7大名情報[iDaimyoID1].友好ID[iDaimyoID2] = i友好ID;
	nb7大名情報[iDaimyoID2].友好ID[iDaimyoID1] = i友好ID;
	return TRUE;
}

int get大名同盟残(int iDaimyoID1, int iDaimyoID2) {
	if (!isValidDaimyoID(iDaimyoID1)) {
		return 0xFFFF;
	}
	if (!isValidDaimyoID(iDaimyoID2)) {
		return 0xFFFF;
	}

	return nb7大名情報[iDaimyoID1].同盟残[iDaimyoID2];
}

BOOL set大名同盟残(int iDaimyoID1, int iDaimyoID2, int 残月) {
	if (!isValidDaimyoID(iDaimyoID1)) {
		return FALSE;
	}
	if (!isValidDaimyoID(iDaimyoID2)) {
		return FALSE;
	}

	nb7大名情報[iDaimyoID1].同盟残[iDaimyoID2] = 残月;
	nb7大名情報[iDaimyoID2].同盟残[iDaimyoID1] = 残月;
	return TRUE;
}

BOOL get大名婚姻(int iDaimyouID1, int iDaimyouID2) {
	if (!isValidDaimyoID(iDaimyouID1)) {
		return FALSE;
	}
	if (!isValidDaimyoID(iDaimyouID2)) {
		return FALSE;
	}

	return nb7大名情報[iDaimyouID1].婚姻[iDaimyouID2];
}

BOOL set大名婚姻(int iDaimyouID1, int iDaimyouID2, BOOL 婚姻化) {
	if (!isValidDaimyoID(iDaimyouID1)) {
		return FALSE;
	}
	if (!isValidDaimyoID(iDaimyouID2)) {
		return FALSE;
	}

	nb7大名情報[iDaimyouID1].婚姻[iDaimyouID2] = 婚姻化;
	nb7大名情報[iDaimyouID2].婚姻[iDaimyouID1] = 婚姻化;
	return TRUE;
}

// 一度も値がセッティングされていない大名家ならば-1が設定されているが、0xFFでも問題はない。
BOOL set大名家紋番号(int iDaimyoID, int iKamonID) {
	if (0 <= iKamonID && iKamonID <= 最大数::大名情報::家紋数-1) {
		nb7大名情報[iDaimyoID].家紋番号 = iKamonID;
		return TRUE;
	}
	else if (iKamonID == 255) {
		nb7大名情報[iDaimyoID].家紋番号 = 255;
		return TRUE;
	}
	else if (iKamonID == -1) {
		nb7大名情報[iDaimyoID].家紋番号 = 255;
		return TRUE;
	}
	return FALSE;
}
