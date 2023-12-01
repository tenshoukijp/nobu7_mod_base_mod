#include "data_bushou_message.h"
#include "data_game_struct.h"
#include <string>

int get主体BushouIDFromMessageBushou() {
	// 所有武将のアドレスを直接さしている
	int nBushouAddress = (int)(メッセージ武将情報.p主体武将);

	// 武将の配列の先頭アドレスから引く
	int sub = nBushouAddress - (int)(武将情報アドレス);

	// 武将情報の構造体のサイズで割れば、何番目の武将なのかがわかる。
	int iBushouID = sub / sizeof(NB7武将情報型);
	if (isValidBushouID(iBushouID)) {
		return iBushouID;
	}

	return 0xFFFF;
}

int get相手BushouIDFromMessageBushou() {
	// 所有武将のアドレスを直接さしている
	int nBushouAddress = (int)(メッセージ武将情報.p相手武将);

	// 武将の配列の先頭アドレスから引く
	int sub = nBushouAddress - (int)(武将情報アドレス);

	// 武将情報の構造体のサイズで割れば、何番目の武将なのかがわかる。
	int iBushouID = sub / sizeof(NB7武将情報型);
	if (isValidBushouID(iBushouID)) {
		return iBushouID;
	}

	return 0xFFFF;
}