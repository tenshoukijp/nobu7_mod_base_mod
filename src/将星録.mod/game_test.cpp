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

#include "mng_����.h"

using namespace std;

int testFlag = 0;

void doGameTest() {
	testFlag = 1;

	using namespace System::Collections::Generic;
	List<����^^>^ list = gcnew List<����^^>(�ő吔::����::�z��);
	for (int i = 0; i < �ő吔::����::�z��; i++) {
		list->Add(gcnew ����^(i));
	}

	auto rlist = list->AsReadOnly();

	for each (auto r in rlist) {
		if (r->�z��IX == �ő吔::����::�z�� - 1) {
			auto n1 = r->�閼;
			r->�閼 = n1;
			auto n2 = r->�閼;
			if (n1 == n2) {
				OutputDebugStream("�閼�Ə閼����v\n");
			}
			else {
				OutputDebugStream("�閼�Ə閼���s��v\n");
			}

			auto h1 = r->����;
			r->���� = h1;
			auto h2 = r->����;

			if (h1 == h2) {
				OutputDebugStream("�����ƕ�������v\n");
			}
			else {
				OutputDebugStream("�����ƕ������s��v\n");
			}

			auto h2_a = r->����;
			r->���� = h2_a;
			auto h2_b = r->����;

			if (h2_a == h2_b) {
				OutputDebugStream("���Ƃƕ��Ƃ���v\n");
			}
			else {
				OutputDebugStream("���Ƃƕ��Ƃ��s��v\n");
			}

			auto h3_a = r->���l;
			r->���l = h3_a;
			auto h3_b = r->���l;

			if (h3_a == h3_b) {
				OutputDebugStream("���l�Ə��l����v\n");
			}
			else {
				OutputDebugStream("���l�Ə��l���s��v\n");
			}

			auto h4_a = r->�K��;
			r->�K�� = h4_a;
			auto h4_b = r->�K��;

			if (h4_a == h4_b) {
				OutputDebugStream("��K�͂Ə�K�͂���v\n");
			}
			else {
				OutputDebugStream("��K�͂Ə�K�͂��s��v\n");
			}

			auto h5_a = r->��C;
			r->��C = h5_a;
			auto h5_b = r->��C;

			if (h5_a == h5_b) {
				OutputDebugStream("��C�Ƒ�C����v\n");
			}
			else {
				OutputDebugStream("��C�Ƒ�C���s��v\n");
			}

			auto h6_a = r->�ϔC�U��;
			r->�ϔC�U�� = h6_a;
			auto h6_b = r->�ϔC�U��;

			if (h6_a == h6_b) {
				OutputDebugStream("�ϔC�U���ƈϔC�U������v\n");
			}
			else {
				OutputDebugStream("�ϔC�U���ƈϔC�U�����s��v\n");
			}

			auto h7_a = r->�ϔC���;
			r->�ϔC��� = h7_a;
			auto h7_b = r->�ϔC���;

			if (h7_a == h7_b) {
				OutputDebugStream("�ϔC��ԂƈϔC��Ԃ���v\n");
			}
			else {
				OutputDebugStream("�ϔC��ԂƈϔC��Ԃ��s��v\n");
			}

			auto h8_a = r->��������;
			r->�������� = h8_a;
			auto h8_b = r->��������;

			if (h8_a == h8_b) {
				OutputDebugStream("���������ƕ�����������v\n");
			}
			else {
				OutputDebugStream("���������ƕ����������s��v\n");
			}

			auto h9_a = r->�R�n;
			r->�R�n = h9_a;
			auto h9_b = r->�R�n;

			if (h9_a == h9_b) {
				OutputDebugStream("�R�n�ƌR�n����v\n");
			}
			else {
				OutputDebugStream("�R�n�ƌR�n���s��v\n");
			}

			auto h10_a = r->���K;
			r->���K = h10_a;
			auto h10_b = r->���K;

			if (h10_a == h10_b) {
				OutputDebugStream("���K�Ƌ��K����v\n");
			}
			else {
				OutputDebugStream("���K�Ƌ��K���s��v\n");
			}

			auto h11_a = r->�S�C;
			r->�S�C = h11_a;
			auto h11_b = r->�S�C;

			if (h11_a == h11_b) {
				OutputDebugStream("�S�C�ƓS�C����v\n");
			}
			else {
				OutputDebugStream("�S�C�ƓS�C���s��v\n");
			}

			auto h12_a = r->�h��;
			r->�h�� = h12_a;
			auto h12_b = r->�h��;

			if (h12_a == h12_b) {
				OutputDebugStream("�h��Ɩh�䂪��v\n");
			}
			else {
				OutputDebugStream("�h��Ɩh�䂪�s��v\n");
			}

			auto h13_a = r->�ϔC�U���ڕW��z��IX;
			r->�ϔC�U���ڕW��z��IX = h13_a;
			auto h13_b = r->�ϔC�U���ڕW��z��IX;

			if (h13_a == h13_b) {
				OutputDebugStream("�ϔC�U���ڕW��z��IX�ƈϔC�U���ڕW��z��IX����v\n");
			}
			else {
				OutputDebugStream("�ϔC�U���ڕW��z��IX�ƈϔC�U���ڕW��z��IX���s��v\n");
			}

			r->�ϔC�U���ڕW��z��IX = 0xFFFF;
			auto h13_c = r->�ϔC�U���ڕW��z��IX;

			if (h13_c == 0xFFFF) {
				OutputDebugStream("�ϔC�U���ڕW��z��IX��0xFFFF����v\n");
			}
			else {
				OutputDebugStream("�ϔC�U���ڕW��z��IX��0xFFFF���s��v\n");
			}

			auto h14_a = r->�����喼�z��IX;
			r->�����喼�z��IX = h14_a;
			auto h14_b = r->�����喼�z��IX;

			if (h14_a == h14_b) {
				OutputDebugStream("�����喼�z��IX�Ə����喼�z��IX����v\n");
			}
			else {
				OutputDebugStream("�����喼�z��IX�Ə����喼�z��IX���s��v\n");
			}

			r->�����喼�z��IX = 0xFFFF;
			auto h14_c = r->�����喼�z��IX;

			if (h14_c == 0xFFFF) {
				OutputDebugStream("�����喼�z��IX��0xFFFF����v\n");
			}
			else {
				OutputDebugStream("�����喼�z��IX��0xFFFF���s��v\n");
			}


			auto h15_a = r->�J�n���j�b�g�z��IX;
			r->�J�n���j�b�g�z��IX = h15_a;
			auto h15_b = r->�J�n���j�b�g�z��IX;

			if (h15_a == h15_b) {
				OutputDebugStream("�J�n���j�b�g�z��IX�ƊJ�n���j�b�g�z��IX����v\n");
			}
			else {
				OutputDebugStream("�J�n���j�b�g�z��IX�ƊJ�n���j�b�g�z��IX���s��v\n");
			}
		}

	}
	/*
	for (int iCastleID = 0; iCastleID < �ő吔::����::�z��; iCastleID++) {
		if (nb7����[iCastleID].�閼 == "�l��"s) {
			OutputDebugStream("�l���̈ϔC:%d\n", (int)nb7����[iCastleID].�ϔC���);
			OutputDebugStream("�l���̈ϔC�U��:%d\n", (int)nb7����[iCastleID].�ϔC�U��);
			OutputDebugStream("�l���̈ϔC�H:%d\n", (int)nb7����[iCastleID].unused1);
		}
	}
	*/

	/*
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
	*/

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
		// OutputDebugStream("���Ȍ���:%d ", nb7�ƕ���[iKahouID].���Ȍ���);
		// OutputDebugStream("����:%d ", nb7�ƕ���[iKahouID].����);
		// OutputDebugStream("�摜:%d ", nb7�ƕ���[iKahouID].�摜);
		// OutputDebugStream("�㏸�\�͒l:%d ", nb7�ƕ���[iKahouID].�\�͏㏸);
		// OutputDebugStream("�ƕ���:%d", nb7�ƕ���[iKahouID].���);
		// if (nb7�ƕ���[iKahouID].���) OutputDebugStream("�s��3:%d", nb7�ƕ���[iKahouID].���);
		int iBushouID = getBushouIDFromKahouID(iKahouID);
		if (0 <= iBushouID && iBushouID < �ő吔::�������::�z��) {
			// OutputDebugStream("���L��:%s ", nb7�������[iBushouID].����);
		} else {
			OutputDebugStream("���L��:%x\n", nb7�ƕ���[iKahouID].p���L��);
		}	
		// OutputDebugStream("�ƕ�ԍ�:%d ", nb7�ƕ���[iKahouID].�ƕ�ԍ�);
		// OutputDebugStream("�ƕ�ő吔:%d ", nb7�ƕ���[iKahouID].�ƕ�ԍ�MAX);
		// OutputDebugStream("\n");
	}
	*/

	/*
	for (int iKanniID = 0; iKanniID < �ő吔::���ʏ��::�z��; iKanniID++) {
		OutputDebugStream("%s", nb7���ʏ��[iKanniID].���ʖ�);
		OutputDebugStream("�K��:%d\n", nb7���ʏ��[iKanniID].�K��);
		OutputDebugStream("���ʔԍ�:%d ", nb7���ʏ��[iKanniID].���ʔԍ�);
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

	/*
	for (int iCastleID = 0; iCastleID < �ő吔::����::�z��; iCastleID++) {
		OutputDebugStream("�閼:%s", nb7����[iCastleID].�閼);
		OutputDebugStream(get���(iCastleID) + "\n");
	}
	*/

	/*

	for (int iUnitID = 0; iUnitID < �ő吔::���j�b�g���::�z��; iUnitID++) {
		int iBushouID = getBushouIDFromUnitID(iUnitID);
		if (iBushouID != 0xFFFF) {
			OutputDebugStream("���j�b�g�ԍ�:%d ", nb7���j�b�g���[iUnitID].���j�b�g�ԍ�);
			int iBushouID = getBushouIDFromUnitID(iUnitID);
			if (isValidBushouID(iBushouID)) {
				OutputDebugStream("%s", nb7�������[iBushouID].����);
				OutputDebugStream("���j�b�g��C:%d \n", nb7���j�b�g���[iUnitID].��C);
				OutputDebugStream("���j�b�g�S�b�D:%d \n", nb7���j�b�g���[iUnitID].�S�b�D);
				OutputDebugStream("���j�b�g���K:%d \n", nb7���j�b�g���[iUnitID].���K);
				OutputDebugStream("���j�b�g����:%d \n", nb7���j�b�g���[iUnitID].����);
				int pNextUnit = (int)nb7���j�b�g���[iUnitID].p���̃��j�b�g;
				int iNextUnitID = getUnitIDFromUnitPtr(nb7���j�b�g���[iUnitID].p���̃��j�b�g);
				if (isValidUnitID(iNextUnitID)) {
					OutputDebugStream("���̃��j�b�g:%d \n", getUnitIDFromUnitPtr(nb7���j�b�g���[iUnitID].p���̃��j�b�g));
				} else {
					OutputDebugStream("�����̃��j�b�g�͂Ȃ�:%x\n", nb7���j�b�g���[iUnitID].p���̃��j�b�g);
				}
			}
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

	/*
	for (int iDaimyoID = 0; iDaimyoID < �ő吔::���j�b�g���::�z��; iDaimyoID++) {
		int iBushouID = getBushouIDFromDaimyoID(iDaimyoID);
		if ( isValidBushouID(iBushouID) ) {
			OutputDebugStream("����:%s\n", nb7�������[iBushouID].����);
		}
	}
	*/

	/*
	for (int iDaimyouID = 0; iDaimyouID < �ő吔::�喼���::�z��; iDaimyouID++) {
		// if (nb7�喼���[iDaimyouID].�v���C���S�� > 0) {
		if (nb7�喼���[iDaimyouID].unknown17) {
			OutputDebugStream("�ԍ�:%d\t", iDaimyouID);
			OutputDebugStream("�喼:%s\n", nb7�喼���[iDaimyouID].p�喼����);
			OutputDebugStream("unknown17:%d\n", nb7�喼���[iDaimyouID].unknown17);
		}
		if (nb7�喼���[iDaimyouID].unknown18) {
			OutputDebugStream("�ԍ�:%d\t", iDaimyouID);
			OutputDebugStream("�喼:%s\n", nb7�喼���[iDaimyouID].p�喼����);
			OutputDebugStream("unknown18:%d\n", nb7�喼���[iDaimyouID].unknown18);
		}
	}
	*/
}

