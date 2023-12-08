#include <windows.h>
#include "data_game_struct.h"

#include "output_debug_stream.h"

BOOL isValidYakusyokuID(int iYakusyokuID) {
	if (0 <= iYakusyokuID && iYakusyokuID < 最大数::役職情報::配列数) {
		return TRUE;
	}
	return FALSE;
}


int getDaimyoIDFromYakusyokuID(int iYakusyokuID) {
	if (0 <= iYakusyokuID && iYakusyokuID < 最大数::役職情報::配列数) {
		// 所有武将のアドレスを直接さしている
		int nDaimyoAddress = (int)nb7役職情報[iYakusyokuID].p所有大名;

		// 武将の配列の先頭アドレスから引く
		int sub = nDaimyoAddress - (int)(大名情報アドレス);

		// 武将情報の構造体のサイズで割れば、何番目の武将なのかがわかる。
		int iDaimyoID = sub / sizeof(NB7大名情報型);
		if (isValidDaimyoID(iDaimyoID)) {
			return iDaimyoID;
		}
	}

	return 0xFFFF;

}

BOOL setDaimyoIDToYakusyokuID(int iYakusyokuID, int iDaimyoID) {
	if (isValidYakusyokuID(iYakusyokuID)) {
		if (isValidDaimyoID(iDaimyoID)) {
			// 大名情報のアドレスを取得
			int iDaimyoAddress = (int)(大名情報アドレス)+iDaimyoID * sizeof(NB7大名情報型);
			// 役職情報の所有者に武将情報のアドレスを設定
			nb7役職情報[iYakusyokuID].p所有大名 = (int*)iDaimyoAddress;
			return TRUE;
		}
		else if (iDaimyoID == 0xFFFF) {
			// 所有者なし
			nb7役職情報[iYakusyokuID].p所有大名 = (int*)役職所有者なし;
			return TRUE;

		}
	}
	return FALSE;

}

BOOL setYakusyokuName(int iYakusyokuID, std::string strYakusyokuName) {
	if (isValidYakusyokuID(iYakusyokuID)) {
		char bufLarge[256] = "";
		int length = sizeof(bufLarge);
		strcpy_s(bufLarge, length, strYakusyokuName.c_str());
		bufLarge[length - 1] = '\0'; // 11文字目は必ず\0にする
		// 役職名を設定
		strcpy_s(nb7役職情報[iYakusyokuID].役職名, sizeof(nb7役職情報[iYakusyokuID].役職名), bufLarge);
		return TRUE;
	}
	return FALSE;
}

