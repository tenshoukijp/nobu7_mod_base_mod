#include <string>
#include "data_game_struct.h"
#include "bushou_albedo.h"
#include <windows.h>
#include <string>
#include <vector>
#include "mng_���.h"
#include "output_debug_stream.h"

using namespace std;
using namespace �����^;

void initAlbedoCastle() {
}

std::pair<string, string> getAlbedoCastleRetsuden(int iCastleID) {
	if (isValidCastleID(iCastleID)) {
		if (iCastleID == ��::��::�z��::�ߌÖ�) {
			for (int b = 0; b < �ő吔::�������::�z��; b++) {
				if (nb7�������[b].���� == getArubedoSeiMei()) {
					return {
						"�啭��@Ż�د��޲����",
						"�M���h�u�A�C���Y�E�E�[���E�S�E���v��\n"
						"������������Ȗ{���n�B�\�w�̃t���A��\n"
						"�\������A���`�攪�K�w�ɂ͊K�w���\n"
						"�҂�����B�A���x�h�͔ނ�𓝊�����B"
					};
				}
			}
		}
	}

	return { "","" };
}
