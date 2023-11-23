#include "data_game_struct.h"

// 家宝IDからそれを所有している武将IDを取得する
int getBushouIDFromDaimyoID(int iDaimyoID) {
	if (0 <= iDaimyoID && iDaimyoID < 最大数::大名情報::配列数) {
		// 所有武将のアドレスを直接さしている
		int nBushouAddress = (int)(nb7大名情報[iDaimyoID].p大名武将);

		// 武将の配列の先頭アドレスから引く
		int sub = nBushouAddress - (int)(武将情報アドレス);

		// 武将情報の構造体のサイズで割れば、何番目の武将なのかがわかる。
		int iBushouID = sub / sizeof(NB7武将情報型);
		if (0 <= iBushouID && iBushouID < 最大数::武将情報::配列数) {
			return iBushouID;
		}
	}

	return 0xFFFF;
}
