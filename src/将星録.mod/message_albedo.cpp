#include <string>
#include "data_game_struct.h"
#include "on_serihu_message.h"
using namespace std;

extern void replaceMessage(string message);

void changeAlbedoMessage(int iBushouID, string message) {
	if (message.find("�r�ɂ͂����������M") != string::npos) {
		int rnd = rand();
		if (rnd % 2 == 0) {
			replaceMessage("�����Ȑl�ԕ��\xA�o���f�B�b�V���̎K�ɂȂ肽���̂�����H\xA������͎���ł��Ȃ����I");
		}
		else {
			replaceMessage("�l�Ԃ͐Ǝ�Ȑ������A\xA�����������̂悤�ɓ��ݒׂ�����\xA�����̓L���C�ɂȂ邩����");
		}
	}
	else if (message.find("������͖��p�ł�") != string::npos && message.find("�������Ȃ��Ǝv�킸��") != string::npos) {
		replaceMessage("����ȂɎ��ɂ����̂�����H\xA���ŉ����ȑ��~����\xA�킽�����Ɍ����Ă����Ȃ���");
	}
	else if (message.find("���悩��Ή����o") != string::npos) {
		int rnd = rand();

		if (rnd % 3 == 2) {
			replaceMessage("����D���鎞��\xA���ӂ��Ȃ���҂��Ȃ���\xA�n�@�[�b�I");
		}
		else if (rnd % 3 == 1) {
			replaceMessage("�l�Ԃ����̎��Ɏ��������Ȃ�\xA�g�̒���m��Ȃ���\xA�n�@�[�b�I");
		}
		else {
			replaceMessage("����ǂ��[�I");
		}
	}
	else if (message.find("�Q��܂���") != string::npos) {
		string old_pattern = "�Q��܂���";
		string new_message = message.replace(message.find(old_pattern), old_pattern.size(), "�Q��܂���");
		replaceMessage(new_message);
	}
	else if (message.find("���ق�") != string::npos) {
		string old_pattern = "���ق�";
		string new_message = message.replace(message.find(old_pattern), old_pattern.size(), "���ӂ�");
		replaceMessage(new_message);
	}
	else if (message.find("�������Ă���") != string::npos) {
		string old_pattern = "�������Ă���";
		string new_message = message.replace(message.find(old_pattern), old_pattern.size(), "�������Ă�����Ⴂ");
		replaceMessage(new_message);
	}
}

