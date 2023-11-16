#include <windows.h>

#include "data_game_struct.h"
#include "output_debug_stream.h"


// ユニットIDからそれを率いている武将IDを取得する
int getBushouIDFromUnitID(int iUnitID) {
	if (0 <= iUnitID && iUnitID < 最大数::ユニット情報::配列数) {
		// 所有武将のアドレスを直接さしている
		int nBushouAddress = (int)(nb7ユニット情報[iUnitID].pユニット武将);

		// 武将の配列の先頭アドレスから引く
		int sub = nBushouAddress - (int)(武将情報アドレス);

		// 武将情報の構造体のサイズで割れば、何番目の武将なのかがわかる。
		int iBushouID = sub / sizeof(NB7武将情報型);
		if (0 <= iBushouID && iBushouID < 最大数::ユニット情報::配列数) { // ここは最大数::武将情報::配列(=732)ではなく、農民等も含めるため、最大数::ユニット情報::配列数 (=744)となる。
			return iBushouID;
		}
	}

	return 0xFFFF;
}
