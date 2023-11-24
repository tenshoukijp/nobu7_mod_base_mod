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

