#include "data_game_struct.h"

BOOL isValidDaimyoID(int iDaimyoID) {
	if (0 <= iDaimyoID && iDaimyoID < 最大数::大名情報::配列数) {
		return TRUE;
	}
	return FALSE;
}

// 大名IDからその大名の武将IDを取得する
int getBushouIDFromDaimyoID(int iDaimyoID) {
	if (0 <= iDaimyoID && iDaimyoID < 最大数::大名情報::配列数) {
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


static int 友好値Array[] = { 0, 10, 20, 30, 40, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 0xFFFF };
int get友好値From友好ID(int i友好ID) {
	if ( 0 <= i友好ID && i友好ID < _countof(友好値Array)) {
		return 友好値Array[i友好ID];
	}
	return 0xFFFF;
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