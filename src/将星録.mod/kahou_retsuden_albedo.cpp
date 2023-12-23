#include <string>
#include "data_game_struct.h"
#include "bushou_albedo.h"
#include <windows.h>
#include <string>
#include <vector>

#include "mng_家宝列挙.h"
#include "output_debug_stream.h"

using namespace std;
using namespace 将星録;

void initAlbedoKahou() {
	for (int iBushouID = 0; iBushouID < 最大数::武将情報::配列数; iBushouID++) {
		// アルベドが居る
		if (nb7武将情報[iBushouID].姓名 == getArubedoSeiMei()) {
			// 千鳥は独自画像ではなく茶釜にしておく
			nb7家宝情報[列挙::家宝::配列::青磁千鳥].画像 = 列挙::家宝::画像::茶釜;

			// バルディッシュは千鳥画像にしておく
			nb7家宝情報[列挙::家宝::配列::鬼丸].画像 = 列挙::家宝::画像::千鳥;
			break;
		}
	}

}

std::pair<string, string> getAlbedoKahouRetsuden(int iKahouID) {
	if (isValidBushouID(iKahouID)) {
		if (iKahouID == 列挙::家宝::配列::鬼丸) {
			if (nb7家宝情報[iKahouID].家宝名 == "バΒΓΔΕΖ"s) {
				OutputDebugStream("ここにきた？");
				return {
					"バΒΓΔΕΖ　ﾊﾞﾙﾃﾞｨｯｼｭ",
					"ナザリック守護者統括・アルベドが愛用\xA"
					"する巨大な斧頭を持つ斧。緑色の微光を\xA"
					"宿すその斧頭は三日月の形をしており、\xA"
					"アルベドの鎧と同色の黒を基調とする。"
				};
			}
		}
		else if (iKahouID == 列挙::家宝::配列::黒漆塗五枚胴) {
			if (nb7家宝情報[iKahouID].家宝名 == "ΚΗΘΛΙΜ"s) {
				return {
					"ΚΗΘΛΙΜ　ﾍﾙﾒｽ･ﾄﾘｽﾒｷﾞｽﾄｽ",
					"内部が三重装甲になっている漆黒の全身\xA"
					"鎧。アルベドのダメージを鎧に受け流す\xA"
					"スキルにより超位魔法すら３回耐える事\xA"
					"が出来る。守護者に相応しい最強の鎧。"
				};
			}
		}
	}

	return { "","" };
}
