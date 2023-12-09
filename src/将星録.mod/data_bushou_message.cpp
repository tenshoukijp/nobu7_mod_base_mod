#include <windows.h>
#include <string>
#include <vector>

#include "data_game_struct.h"
#include "output_debug_stream.h"
#include "game_screen.h"
#include "game_process.h"
#include "on_serihu_message.h"
#include "bushou_albedo.h"
#include "game_screen.h"
#include "message_albedo.h"
#include "onigwrap.h"

using namespace std;
using namespace 列挙;

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

void checkReplaceBushouSerifuMessage() {
	int status = getゲーム画面ステータス();
	if (status == ゲーム画面ステータス::戦略画面 || status == ゲーム画面ステータス::野戦画面 || status == ゲーム画面ステータス::籠城戦画面) {
		// 主体武将と相手武将を求める。値は有効でも主体武将自体前回のものが残っているだけかもしれない。ただし吹き出し会話なのであれば主体武将は必ずセットされる。
		int i主体BushouID = get主体BushouIDFromMessageBushou();
		if (isValidBushouID(i主体BushouID)) {
			OutputDebugStream("★主体は%s★\n", nb7武将情報[i主体BushouID].姓名);
			string message = (char*)(セリフメッセージアドレス); // on_serihu_message
			if (nb7武将情報[i主体BushouID].姓名 == getArubedoSeiMei()) {
				changeAlbedoMessage(i主体BushouID, message);
			}
		}

		int i相手BushouID = get相手BushouIDFromMessageBushou();
		if (isValidBushouID(i相手BushouID)) {
			OutputDebugStream("★相手は%s★\n", nb7武将情報[i相手BushouID].姓名);
		}
	}
}