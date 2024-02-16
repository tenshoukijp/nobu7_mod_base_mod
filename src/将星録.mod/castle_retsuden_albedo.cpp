#include <string>
#include "data_game_struct.h"
#include "bushou_albedo.h"
#include <windows.h>
#include <string>
#include <vector>
#include "mng_城列挙.h"
#include "output_debug_stream.h"

using namespace std;
using namespace 将星録;

void initAlbedoCastle() {
}

std::pair<string, string> getAlbedoCastleRetsuden(int iCastleID) {
	if (isValidCastleID(iCastleID)) {
		if (iCastleID == 列挙::城::配列::那古野) {
			for (int b = 0; b < 最大数::武将情報::配列数; b++) {
				if (nb7武将情報[b].姓名 == getArubedoSeiMei()) {
					return {
						"大墳墓　ﾅｻﾞﾘｯｸﾀﾞｲﾌﾝﾎﾞ",
						"ギルド「アインズ・ウール・ゴウン」が\n"
						"改造した巨大な本拠地。十層のフロアで\n"
						"構成され、第一～第八階層には階層守護\n"
						"者がいる。アルベドは彼らを統括する。"
					};
				}
			}
		}
	}

	return { "","" };
}
