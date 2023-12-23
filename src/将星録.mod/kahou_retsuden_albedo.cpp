#include <string>
#include "data_game_struct.h"
#include "bushou_albedo.h"
#include <windows.h>
#include <string>
#include <vector>

#include "mng_�ƕ��.h"
#include "output_debug_stream.h"

using namespace std;
using namespace �����^;

void initAlbedoKahou() {
	for (int iBushouID = 0; iBushouID < �ő吔::�������::�z��; iBushouID++) {
		// �A���x�h������
		if (nb7�������[iBushouID].���� == getArubedoSeiMei()) {
			// �璹�͓Ǝ��摜�ł͂Ȃ������ɂ��Ă���
			nb7�ƕ���[��::�ƕ�::�z��::���璹].�摜 = ��::�ƕ�::�摜::����;

			// �o���f�B�b�V���͐璹�摜�ɂ��Ă���
			nb7�ƕ���[��::�ƕ�::�z��::�S��].�摜 = ��::�ƕ�::�摜::�璹;
			break;
		}
	}

}

std::pair<string, string> getAlbedoKahouRetsuden(int iKahouID) {
	if (isValidBushouID(iKahouID)) {
		if (iKahouID == ��::�ƕ�::�z��::�S��) {
			if (nb7�ƕ���[iKahouID].�ƕ� == "�o����������"s) {
				OutputDebugStream("�����ɂ����H");
				return {
					"�o�����������@����ި���",
					"�i�U���b�N���ғ����E�A���x�h�����p\xA"
					"���鋐��ȕ����������B�ΐF�̔�����\xA"
					"�h�����̕����͎O�����̌`�����Ă���A\xA"
					"�A���x�h�̊Z�Ɠ��F�̍�����Ƃ���B"
				};
			}
		}
		else if (iKahouID == ��::�ƕ�::�z��::�����h�ܖ���) {
			if (nb7�ƕ���[iKahouID].�ƕ� == "������������"s) {
				return {
					"�������������@��ҽ��ؽҷ޽Ľ",
					"�������O�d���b�ɂȂ��Ă��鎽���̑S�g\xA"
					"�Z�B�A���x�h�̃_���[�W���Z�Ɏ󂯗���\xA"
					"�X�L���ɂ�蒴�ʖ��@����R��ς��鎖\xA"
					"���o����B���҂ɑ��������ŋ��̊Z�B"
				};
			}
		}
	}

	return { "","" };
}
