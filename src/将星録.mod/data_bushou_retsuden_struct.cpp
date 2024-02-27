
#include "data_game_struct.h"
#include "game_screen.h"

using namespace 列挙;

int getRetsudenBushouID() {
	int status = getゲーム画面ステータス();
	if (status == ゲーム画面ステータス::戦略画面 || status == ゲーム画面ステータス::野戦画面 || status == ゲーム画面ステータス::籠城戦画面) {
		// 所有武将のアドレスを直接さしている
		int nBushouAddress = *(int*)(武将列伝武将情報アドレス);

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