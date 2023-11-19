#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "data_kahou_struct.h"
#include "data_kanni_struct.h"
#include "data_yakusyoku_struct.h"
#include "data_castle_struct.h"
#include "data_turn_struct.h"
#include "game_screen.h"
#include "game_process.h"
#include "on_serihu_message.h"
#include "hook_functions_direct.h"
#include "bushou_albedo.h"
using namespace std;


void WriteAsmJumperOnSSRExeMessageDetail();

void doGameTest() {


	OutputDebugStream("����%d", �^�[�����.����);
	OutputDebugStream("��%d", �^�[�����.��);

	for (int iBushouID = 0; iBushouID < �ő吔::�������::�z��; iBushouID++) {

		if (getBushou����FromBushouID(iBushouID) == "�D�c�M��") {
			OutputDebugStream("�D�c�M���̕����ԍ� %x\n", iBushouID);
		}
		if (getBushou����FromBushouID(iBushouID) == "����`��") {
			OutputDebugStream("����`���̕����ԍ� %x\n", iBushouID);
		}
		if (getBushou����FromBushouID(iBushouID) == "���c�M��") {
			OutputDebugStream("���c�M���̕����ԍ� %x\n", iBushouID);
		}

	}

	/*
	for (int iBushouID = 0; iBushouID < �ő吔::�������::�z��; iBushouID++) {
		OutputDebugStream(nb7�������[iBushouID].����);
		OutputDebugStream("\n");

		if (getBushou�c��FromBushouID(iBushouID) == "�ɑ�") {
			OutputDebugStream("����ID:" + getBushou����FromBushouID(iBushouID));
			OutputDebugStream("����:%d ", nb7�������[iBushouID].����);
			OutputDebugStream("�퓬:%d ", nb7�������[iBushouID].�퓬);
			OutputDebugStream("�m�d:%d ", nb7�������[iBushouID].�q�d);
			OutputDebugStream("�E��:%d ", nb7�������[iBushouID].�E��);
			OutputDebugStream("\n");

			for (int iKahouID = 0; iKahouID < �ő吔::�ƕ���::�z��; iKahouID++) {
				if (string(nb7�ƕ���[iKahouID].�ƕ�).find("����") != string::npos) {
					// strcpy(nb7�ƕ���[iKahouID].�ƕ�, "������������");
					// setBushouIDToKahouID(iKahouID, iBushouID);
				}
			}
		}

	}
	*/

	/*
	for (int iKahouID = 0; iKahouID < �ő吔::�ƕ���::�z��; iKahouID++) {
		OutputDebugStream("�ƕ�:%s ", nb7�ƕ���[iKahouID].�ƕ�);
		OutputDebugStream("���Ȍ���:%d ", nb7�ƕ���[iKahouID].���Ȍ���);
		OutputDebugStream("����:%d ", nb7�ƕ���[iKahouID].����);
		OutputDebugStream("�O���t�B�b�N�ԍ�:%d ", nb7�ƕ���[iKahouID].�O���t�B�b�N�ԍ�);
		OutputDebugStream("�㏸�\�͒l:%d ", nb7�ƕ���[iKahouID].�㏸�\�͒l);
		OutputDebugStream("�ƕ���:%d ", nb7�ƕ���[iKahouID].�ƕ���);
		int iBushouID = getBushouIDFromKahouID(iKahouID);
		if (0 <= iBushouID && iBushouID < �ő吔::�������::�z��) {
			OutputDebugStream("���L��:%s ", nb7�������[iBushouID].����);
		}
		OutputDebugStream("�ƕ�ԍ�:%d ", nb7�ƕ���[iKahouID].�ƕ�ԍ�);
		OutputDebugStream("�ƕ�ő吔:%d ", nb7�ƕ���[iKahouID].�ƕ�ő吔);
		OutputDebugStream("�\�͌���:%d ", (int)nb7�ƕ���[iKahouID].�\�͌���);
		OutputDebugStream("\n");
	}
		*/

		/*
		for (int iKanniID = 0; iKanniID < �ő吔::���ʏ��::�z��; iKanniID++) {
			OutputDebugStream("���ʖ�:%s ", nb7���ʏ��[iKanniID].���ʖ�);
			OutputDebugStream("���ʔԍ�:%d ", nb7���ʏ��[iKanniID].���ʔԍ�);
			OutputDebugStream("�K��:%d ", nb7���ʏ��[iKanniID].�K��);
			OutputDebugStream("\n");
			int iBushouID = getBushouIDFromKanniID(iKanniID);
			if (0 <= iBushouID && iBushouID < �ő吔::�������::�z��) {

				OutputDebugStream("���L��:%s ", nb7�������[iBushouID].����);
			}
		}
		*/

		/*
		for (int iYakusyokuID = 0; iYakusyokuID < �ő吔::��E���::�z��; iYakusyokuID++) {
			OutputDebugStream("��E��:%s ", nb7��E���[iYakusyokuID].��E��);
			OutputDebugStream("��E�ԍ�:%d ", nb7��E���[iYakusyokuID].��E�ԍ�);
			OutputDebugStream("����:%d ", nb7��E���[iYakusyokuID].����);
			int iBushouID = getBushouIDFromYakusyokuID(iYakusyokuID);
			OutputDebugStream("%d", iBushouID);
			if ( 0 <= iBushouID && iBushouID < �ő吔::�������::�z��) {

				OutputDebugStream("���L��:%s ", nb7�������[iBushouID].����);
			}
			OutputDebugStream("\n");
		}
		*/

	for (int iCastleID = 0; iCastleID < �ő吔::����::�z��; iCastleID++) {
		if (nb7����[iCastleID].unknown_flag == 1) {
			OutputDebugStream("%s\n", nb7����[iCastleID].�閼);
		}
		if (nb7����[iCastleID].�閼 == "�l��"s) {
			OutputDebugStream("�ϔC��� %d\n", nb7����[iCastleID].�ϔC���);
			OutputDebugStream("���� %d\n", nb7����[iCastleID].unknown_flag);
			OutputDebugStream("\t\n;");
		}
	}

	/*
	for (int iUnitID = 0; iUnitID < �ő吔::���j�b�g���::�z��; iUnitID++) {
		int iBushouID = getBushouIDFromUnitID(iUnitID);
		if (iBushouID != 0xFFFF) {
			OutputDebugStream("���j�b�g�ԍ�:%d ", nb7���j�b�g���[iUnitID].���j�b�g�ԍ�);
			OutputDebugStream("���j�b�g�x�z��:%s \n", (char*)(nb7���j�b�g���[iUnitID].p���j�b�g����));
			OutputDebugStream("���j�b�g��C:%d \n", nb7���j�b�g���[iUnitID].��C);
			OutputDebugStream("���j�b�g�S�b�D:%d \n", nb7���j�b�g���[iUnitID].�S�b�D);
			OutputDebugStream("���j�b�g���K:%d \n", nb7���j�b�g���[iUnitID].���K);
			OutputDebugStream("���j�b�g����:%d \n", nb7���j�b�g���[iUnitID].����);
		}
	}
	*/
	/*
	auto ret = get�Q�[����ʃX�e�[�^�X();
	OutputDebugStream("�Q�[����ʃX�e�[�^�X: %d", (int)ret);

	for (int iUnitID = 0; iUnitID < �ő吔::���j�b�g���::�z��; iUnitID++) {
		int iBushouID = getBushouIDFromUnitID(iUnitID);
		if (0 <= iBushouID && iBushouID < �ő吔::�������::�z��) {
			if (getBushou����FromBushouID(iBushouID) == getArubedoSeiMei()) {

				nb7���j�b�g���[iUnitID].�S�b�D = 1;
			}
		}
	}
	*/
}




