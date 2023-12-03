#include "data_game_struct.h"
#include "game_screen.h"

int getRetsudenKahouID() {
	ゲーム画面ステータス status = getゲーム画面ステータス();
	if (status == ゲーム画面ステータス::戦略画面 || status == ゲーム画面ステータス::野戦画面 || status == ゲーム画面ステータス::籠城戦画面) {
		// 家宝のアドレスを直接さしている
		int nKahouAddress = *(int*)(家宝列伝家宝情報アドレス);

		// 家宝の配列の先頭アドレスから引く
		int sub = nKahouAddress - (int)(家宝情報アドレス);

		// 家宝情報の構造体のサイズで割れば、何番目の武将なのかがわかる。
		int iBushouID = sub / sizeof(NB7家宝情報型);
		if (isValidBushouID(iBushouID)) {
			return iBushouID;
		}
	}

	return 0xFFFF;
}