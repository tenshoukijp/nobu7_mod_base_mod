#include <windows.h>
#include <string>
#include <vector>

#include "data_game_struct.h"
#include "output_debug_stream.h"
#include "game_screen.h"
#include "on_serihu_message.h"
#include "bushou_albedo.h"
#include "game_screen.h"
#include "message_albedo.h"

using namespace std;
using namespace ��;

extern vector<int> list�b��BushouID;

int get1stBushouIDFromMessageBushou() {

	int iBushouID = list�b��BushouID[0];

	if (isValidBushouID(iBushouID)) {
		return iBushouID;
	}

	return 0xFFFF;
}

int get2ndBushouIDFromMessageBushou() {
	int iBushouID = list�b��BushouID[1];

	if (isValidBushouID(iBushouID)) {
		return iBushouID;
	}

	return 0xFFFF;
}

int get3rdBushouIDFromMessageBushou() {
	int iBushouID = list�b��BushouID[2];

	if (isValidBushouID(iBushouID)) {
		return iBushouID;
	}

	return 0xFFFF;
}


void checkReplaceBushouSerifuMessage() {
	int status = get�Q�[����ʃX�e�[�^�X();
	if (status == �Q�[����ʃX�e�[�^�X::�헪��� || status == �Q�[����ʃX�e�[�^�X::����� || status == �Q�[����ʃX�e�[�^�X::�ď����) {
		// ��̕����Ƒ��蕐�������߂�B�l�͗L���ł���̕������̑O��̂��̂��c���Ă��邾����������Ȃ��B�����������o����b�Ȃ̂ł���Ύ�̕����͕K���Z�b�g�����B
		int i���BushouID = get1stBushouIDFromMessageBushou();
		if (isValidBushouID(i���BushouID)) {
			OutputDebugStream("����̂�%s��\n", nb7�������[i���BushouID].����);
			string message = (char*)(�Z���t���b�Z�[�W�A�h���X); // on_serihu_message
			if (nb7�������[i���BushouID].���� == getArubedoSeiMei()) {
				changeAlbedoMessage(i���BushouID, message);
			}
		}

		int i����BushouID = get2ndBushouIDFromMessageBushou();
		if (isValidBushouID(i����BushouID)) {
			OutputDebugStream("�������%s��\n", nb7�������[i����BushouID].����);
		}
	}
}