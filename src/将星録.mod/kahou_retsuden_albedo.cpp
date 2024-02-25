#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "bushou_albedo.h"
#include <vector>

#include "mng_�ƕ��.h"
#include "output_debug_stream.h"

using namespace std;
using namespace �����^;

void initAlbedoKahou() {
	for (int iBushouID = 0; iBushouID < �ő吔::�������::�z��; iBushouID++) {
		// �A���x�h������
		if (nb7�������[iBushouID].���� == getArubedoSeiMei()) {
			// �������ʂȏ�����������K�v������Ȃ炱����
			break;
		}
	}

}

std::pair<string, string> getAlbedoKahouRetsuden(int iKahouID) {
	if (isValidKahouID(iKahouID)) {
		if (iKahouID == ��::�ƕ�::�z��::�S��) {
			if (nb7�ƕ���[iKahouID].�ƕ� == "�o����������"s) {
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
		else if (iKahouID == ��::�ƕ�::�z��::�\����) {
			if (nb7�ƕ���[iKahouID].�ƕ� == "�M�F�G�H�I�v"s) {
				return {
					"�M�F�G�H�I�v�@����ݶ޶���",
					"�u�^�Ȃ閳�v�B�L�͈͂ɕ��̂�j��ł�\xA"
					"�鐢�E���A�C�e���B�ό`���̓A���x�h��\xA"
					"�啐���ƂȂ�B�Ε��̂ł͐�ΓI���\��\xA"
					"�ւ邪�A�ΐ����ɂ͌��ʂ͌���I�B"
				};
			}
		}
	}

	return { "","" };
}
