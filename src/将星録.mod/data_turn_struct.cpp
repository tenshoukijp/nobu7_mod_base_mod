#include "data_game_struct.h"

int getStrategyPlayerTurnCastleID() {
	// 所有武将のアドレスを直接さしている
	int nCastleAddress = (int)(ターン城情報.pターン城);
	// 武将の配列の先頭アドレスから引く
	int sub = nCastleAddress - (int)(城情報アドレス);

	// 武将情報の構造体のサイズで割れば、何番目の武将なのかがわかる。
	int iCastleID = sub / sizeof(NB7城情報型);
	if (isValidCastleID(iCastleID)) {
		return iCastleID;
	}
	return 0xFFFF;
}