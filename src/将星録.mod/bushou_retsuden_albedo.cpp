#include <string>
#include "data_game_struct.h"
#include "bushou_albedo.h"

using namespace std;

std::pair<string, string> getAlbedoRetsuden(int iBushouID) {
	if (isValidBushouID(iBushouID)) {
		if (nb7�������[iBushouID].���� == getArubedoSeiMei()) {
			return { "�A���x�h ���ғ��� ????�`????" ,
					"�i�U���b�N�n���啭��̎��ғ����B��\xA"
					"������͂Q�{�̊p�A������͎����̗���\xA"
					"���₵���d���ȃT�L���o�X�B�u���ߐ[��\xA"
					"�����̈����v�ٖ̈������␢�̔����B"
			};
		}
	}

	return { "","" };
}
