#include <windows.h>
#include <vector>

#include "data_game_struct.h"
#include "output_debug_stream.h"

BOOL isValidUnitID(int iUnitID) {
	if (0 <= iUnitID && iUnitID < 最大数::ユニット情報::配列数) {
		return TRUE;
	}
	return FALSE;
}

// ユニットIDからそれを率いている武将IDを取得する
int getBushouIDFromUnitID(int iUnitID) {
	if (isValidUnitID(iUnitID)) {
		// 所有武将のアドレスを直接さしている
		int nBushouAddress = (int)(nb7ユニット情報[iUnitID].p指揮武将);

		// 武将の配列の先頭アドレスから引く
		int sub = nBushouAddress - (int)(武将情報アドレス);

		// 武将情報の構造体のサイズで割れば、何番目の武将なのかがわかる。
		int iBushouID = sub / sizeof(NB7武将情報型);
		if (isValidUnitID(iBushouID)) { // ここは最大数::武将情報::配列(=732)ではなく、農民等も含めるため、最大数::ユニット情報::配列数 (=744)となる。
			return iBushouID;
		}
	}

	return 0xFFFF;
}

int getUnitIDFromUnitPtr(int* iUnitPtr) {
	int nUnitAddress = (int)(iUnitPtr);

	// 武将の配列の先頭アドレスから引く
	int sub = nUnitAddress - (int)(ユニット情報アドレス);

	// 武将情報の構造体のサイズで割れば、何番目の武将なのかがわかる。
	int iUnitID = sub / sizeof(NB7ユニット情報型);
	if (isValidUnitID(iUnitID)) {
		return iUnitID;
	}

	return 0xFFFF;
}



int get軍勢ユニット部隊最大兵数(int iUnitID) {
	if (isValidUnitID(iUnitID)) {
		int iBushouID = getBushouIDFromUnitID(iUnitID);
		if (0 <= iBushouID && iBushouID < 最大数::ユニット情報::配列数) {
			int status = nb7武将情報[iBushouID].状態;
			// 大名、独立勢力、一向一揆勢力、一揆勢力なら、１部隊は1000
			if (status == 0 || status == 2 || status == 6 || status == 7) {
				return 1000;
			}
			// 現役の時は身分で判定
			else if (status == 1) {
				int mibun = nb7武将情報[iBushouID].身分;
				if (mibun == 武将情報::身分::大名) {
					return 1000;
				}
				else if (mibun == 武将情報::身分::宿老) {
					return 900;
				}
				else if (mibun == 武将情報::身分::家老) {
					return 750;
				}
				else if (mibun == 武将情報::身分::部将) {
					return 600;
				}
				else if (mibun == 武将情報::身分::侍大将) {
					return 500;
				}
				else if (mibun == 武将情報::身分::足軽頭) {
					return 400;
				}
			}
		}
	}
	return 0;
}
