#include <windows.h>
#include "data_game_struct.h"

#include "output_debug_stream.h"

int getBushouIDFromYakusyokuID(int iYakusyokuID) {
	if (0 <= iYakusyokuID && iYakusyokuID < 最大数::役職情報::配列数) {
		// 所有武将のアドレスを直接さしている
		int* pBushouAddress = nb7役職情報[iYakusyokuID].p所有者;
		int nBushouAddress = 0;
		if (pBushouAddress) {
			nBushouAddress = *pBushouAddress;
		}
		OutputDebugStream("★%x\n", nBushouAddress);

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

