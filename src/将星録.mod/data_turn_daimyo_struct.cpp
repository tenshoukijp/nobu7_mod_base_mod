#include "data_game_struct.h"

int getStrategyTurnDaimyoID() {
	int nDaimyoAddress = *(int*)(ターン大名情報アドレス);

	// 武将の配列の先頭アドレスから引く
	int sub = nDaimyoAddress - (int)(大名情報アドレス);

	// 大名情報の構造体のサイズで割れば、何番目の武将なのかがわかる。
	int iDaimyoID = sub / sizeof(NB7大名情報型);
	if (isValidDaimyoID(iDaimyoID)) {
		return iDaimyoID;

	}
	return 0xFFFF;
}


int getStrategyTurnDaimyoBushouID() {
	int iDaimyoID = getStrategyTurnDaimyoID();
	if (isValidDaimyoID(iDaimyoID)) {
		int iBushouID = getBushouIDFromDaimyoID(iDaimyoID);
		if (isValidBushouID(iBushouID)) {
			return iBushouID;
		}
	}

	return 0xFFFF;
}
