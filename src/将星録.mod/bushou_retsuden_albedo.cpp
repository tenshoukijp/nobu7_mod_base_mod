#include <string>
#include "data_game_struct.h"
#include "bushou_albedo.h"

using namespace std;

std::pair<string, string> getAlbedoRetsuden(int iBushouID) {
	if (isValidBushouID(iBushouID)) {
		if (nb7武将情報[iBushouID].姓名 == getArubedoSeiMei()) {
			return { "アルベド 守護者統括 ????～????" ,
					"ナザリック地下大墳墓の守護者統括。頭\xA"
					"部からは２本の角、腰からは漆黒の翼を\xA"
					"生やした妖艶なサキュバス。「慈悲深き\xA"
					"純白の悪魔」の異名を持つ絶世の美女。"
			};
		}
	}

	return { "","" };
}
